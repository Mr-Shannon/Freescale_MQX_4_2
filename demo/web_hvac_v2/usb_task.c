/**HEADER********************************************************************
* 
* Copyright (c) 2010, 2013 - 2014 Freescale Semiconductor;
* All Rights Reserved
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: main.c$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains device driver for mass storage class. This code tests
*   the FAT functionalities.
*
*END************************************************************************/

/**************************************************************************
Include the OS and BSP dependent files that define IO functions and
basic types. You may like to change these files for your board and RTOS 
**************************************************************************/
/**************************************************************************
Include the USB stack header files.
**************************************************************************/
#include "hvac.h"
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#include "usb_host_hub_sm.h"
#include "usb_host_msd_bo.h"
#include "usb_host_msd_ufi.h"
//#include <mqx.h>
//#include <lwevent.h>
//#include <bsp.h>
#include "mfs.h"
//#include <part_mgr.h>
#include "usbmfs.h"
#include "usbmfspr.h"
//#include "mfs_usb.h"
#if DEMOCFG_ENABLE_USB_FILESYSTEM

#include <string.h>
#include <lwmsgq.h>
#include "usb_task.h"
#include "usb_file.h"

usb_host_handle                  g_host_handle;         /* global handle for calling host   */
volatile device_struct_t         g_mass_device[USBCFG_MAX_INSTANCE] = { 0 };   /* mass storage device struct */
usb_device_interface_struct_t*   g_interface_info[USBCFG_MAX_INSTANCE][USBCFG_HOST_MAX_INTERFACE_PER_CONFIGURATION];
uint8_t                          g_interface_number[USBCFG_MAX_INSTANCE] = {0};
volatile uint8_t                 g_mass_device_new_index = 0;
/* Store mounting point used. A: is the first one, bit #0 assigned, Z: is the last one, bit #25 assigned */
uint32_t                         g_fs_mountp = 0;

char                             g_drive[3];
char                             g_pm[8] = "PM_C1:";
char                             g_block[8] = "USB:";

LWSEM_STRUCT                     USB_Stick;
LWEVENT_STRUCT                   USB_Event;
/* The granularity of message queue is one message. Its size is the multiplier of _mqx_max_type. Get that multiplier */
void   usb_host_mass_device_event (usb_device_instance_handle,usb_interface_descriptor_handle,uint32_t);
/* Table of driver capabilities this application want to use */
static const usb_host_driver_info_t DriverInfoTable[] =
{  
   /* Vendor ID Product ID Class Sub-Class Protocol Reserved Application call back */
   /* Floppy drive */
   {{0x00,0x00}, {0x00,0x00}, USB_CLASS_MASS_STORAGE, USB_SUBCLASS_MASS_UFI, USB_PROTOCOL_MASS_BULK, 0, usb_host_mass_device_event },

   /* USB 2.0 hard drive */
   {{0x00,0x00}, {0x00,0x00}, USB_CLASS_MASS_STORAGE, USB_SUBCLASS_MASS_SCSI, USB_PROTOCOL_MASS_BULK, 0, usb_host_mass_device_event},

   /* USB hub */
   {{0x00,0x00}, {0x00,0x00}, USB_CLASS_HUB, USB_SUBCLASS_HUB_NONE, USB_PROTOCOL_HUB_ALL, 0, usb_host_hub_device_event},

   /* End of list */
   {{0x00,0x00}, {0x00,0x00}, 0,0,0,0, NULL}
};


int mfs_mount(uint8_t device_no)
{
    /* get free mountpoint as a string like "c:" */
    for (g_drive[0] = 'C'; g_drive[0] <= 'Z'; g_drive[0]++)
        if (!(g_fs_mountp & (1 << (g_drive[0] - 'A'))))
            break;
    g_drive[1] = ':';
    g_drive[2] = 0;
    
    g_pm[3] = g_drive[0];
    
    /* Install the file system, use device->ccs as a handle */
	g_mass_device[device_no].usb_mfs_handle = usb_filesystem_install( (void*)g_mass_device[device_no].CLASS_HANDLE, g_block, g_pm, g_drive );
    if (NULL != g_mass_device[device_no].usb_mfs_handle)
    {
        g_mass_device[device_no].mount = g_drive[0];        
        /* Mark file system as mounted */
        g_fs_mountp |= 1 << (g_mass_device[device_no].mount - 'A');
       
        return MQX_OK;
    }
    
    return MQX_ERROR;
}

usb_interface_descriptor_handle mass_get_interface(uint8_t num)
{
    return (usb_interface_descriptor_handle)(g_interface_info[num][0]);
}

int mfs_unmount(uint8_t device_no)
{
    if (g_mass_device[device_no].mount >= 'A' && g_mass_device[device_no].mount <= 'Z') 
    {
        /* Remove the file system  */
        usb_filesystem_uninstall(g_mass_device[device_no].usb_mfs_handle);
        /* Mark file system as unmounted */
        g_fs_mountp &= ~(1 << (g_mass_device[device_no].mount - 'A'));
        return 0;
    }
    return -1;
}

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_host_mass_device_event
* Returned Value : None
* Comments       :
*     called when a mass storage device has been attached, detached, etc.
*END*--------------------------------------------------------------------*/

void usb_host_mass_device_event
   (
      /* [IN] pointer to device instance */
      usb_device_instance_handle      dev_handle,

      /* [IN] pointer to interface descriptor */
      usb_interface_descriptor_handle intf_handle,

      /* [IN] code number for event causing callback */
      uint32_t           event_code
   )
{
   usb_device_interface_struct_t*      pHostIntf = (usb_device_interface_struct_t*)intf_handle;
   interface_descriptor_t*             intf_ptr = pHostIntf->lpinterfaceDesc;
   volatile device_struct_t*           mass_device_ptr = NULL;
   uint8_t                             i = 0;
   
   for(i = 0; i < USBCFG_MAX_INSTANCE;i++)
   {
       if(g_mass_device[i].dev_handle == dev_handle)
       {
           mass_device_ptr = &g_mass_device[i];
           break;
       }
   }
   
   if(NULL == mass_device_ptr)
   {
       for(i = 0; i < USBCFG_MAX_INSTANCE;i++)
       {
           if(USB_DEVICE_IDLE == g_mass_device[i].dev_state)
           {
               mass_device_ptr = &g_mass_device[i];
               break;
           }
       }
   }
   
   if(NULL == mass_device_ptr)
   {
       printf("Access devices is full.\r\n");
       return;
   }
   
   switch (event_code) 
   {
      case USB_ATTACH_EVENT:
         g_interface_info[i][g_interface_number[i]] = pHostIntf;
         g_interface_number[i]++;
         _lwevent_set(&USB_Event, USB_STATE_CHANGED);
         break;
         /* Drop through into attach, same processing */
         
      case USB_CONFIG_EVENT:
         if (mass_device_ptr->dev_state == USB_DEVICE_IDLE) 
         {
             mass_device_ptr->dev_handle = dev_handle;
             mass_device_ptr->intf_handle = mass_get_interface(i);
             mass_device_ptr->dev_state = USB_DEVICE_ATTACHED;
             _lwevent_set(&USB_Event, USB_STATE_CHANGED);
         } 
         else 
         {
            printf("Mass Storage Device is already attached - DEV_STATE = %d\r\n", mass_device_ptr->dev_state);
         } /* EndIf */
         break;
          
      case USB_INTF_OPENED_EVENT:
         mass_device_ptr->dev_state = USB_DEVICE_INTERFACE_OPENED;
         _lwevent_set(&USB_Event, USB_STATE_CHANGED);
         break ;
         
      case USB_DETACH_EVENT:
         /* Use only the interface with desired protocol */
         g_interface_number[i] = 0;
         mass_device_ptr->dev_state = USB_DEVICE_DETACHED;
         _lwevent_set(&USB_Event, USB_STATE_CHANGED);
         break;
      default:
         printf("Mass Storage Device state = %d??\r\n", mass_device_ptr->dev_state);
         mass_device_ptr->dev_state = USB_DEVICE_IDLE;
         _lwevent_set(&USB_Event, USB_STATE_CHANGED);
         break;
   } /* EndSwitch */
} 

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : USB_task
* Returned Value : None
* Comments       :
*     First function called. This routine just transfers control to host main
*END*--------------------------------------------------------------------*/

void USB_task(uint32_t param)
{ 
    usb_host_handle     host_handle;
    usb_status          status;
    void                *usb_fs_handle = NULL;
    /* Store mounting point used. A: is the first one, bit #0 assigned, Z: is the last one, bit #25 assigned */
    uint32_t            fs_mountp = 0;
    uint8_t             i = 0;
    static uint8_t      fat_task_flag[USBCFG_MAX_INSTANCE] = {0};
   
#if DEMOCFG_USE_POOLS && defined(DEMOCFG_MFS_POOL_ADDR) && defined(DEMOCFG_MFS_POOL_SIZE)
    _MFS_pool_id = _mem_create_pool((void *)DEMOCFG_MFS_POOL_ADDR, DEMOCFG_MFS_POOL_SIZE);
#endif

    /* This event will inform other tasks that the filesystem on USB was successfully installed */
    _lwsem_create(&USB_Stick, 0);

    /* create lwevent group */
    if (_lwevent_create(&USB_Event,0) != MQX_OK)
    {
        printf("\n _lwevent_create USB_Event failed.\n");
        _task_block();
    }
       
    status = usb_host_init(CONTROLLER_ID, &g_host_handle);
    if(status != USB_OK) 
    {
        printf("\r\nUSB Host Initialization failed! STATUS: 0x%x", status);
        return;
    }
    
    status = usb_host_register_driver_info(g_host_handle, (void *)DriverInfoTable);
    if(status != USB_OK) 
    {         
        printf("\r\nUSB Initialization driver info failed! STATUS: 0x%x", status);
        return;
    }


    if (status != USB_OK) {
        _task_block();
    }
      
    for(;;)
    {
        _lwevent_wait_ticks(&USB_Event,USB_STATE_CHANGED,FALSE,0);
        _lwevent_clear(&USB_Event,USB_STATE_CHANGED);
        for(i =0 ;i < USBCFG_MAX_INSTANCE; i++)
        {
            switch (g_mass_device[i].dev_state ) 
            {
            case USB_DEVICE_IDLE:
                break;
            case USB_DEVICE_ATTACHED:
                printf( "Mass Storage Device Attached\r\n" );
                g_mass_device[i].dev_state = USB_DEVICE_SET_INTERFACE_STARTED;
                status = usb_host_open_dev_interface(g_host_handle, g_mass_device[i].dev_handle, g_mass_device[i].intf_handle, (usb_class_handle*)&g_mass_device[i].CLASS_HANDLE);
                if (status != USB_OK)
                {
                    printf("\r\nError in _usb_hostdev_open_interface: %x\r\n", status);
                    return;
                } /* End if */
                /* Can run fat task */
                fat_task_flag[i] = 1;    
                break;
            case USB_DEVICE_SET_INTERFACE_STARTED:
                break;
            case USB_DEVICE_INTERFACE_OPENED:
                if(1 == fat_task_flag[i])
                {
                    g_mass_device_new_index = i;
                    if (MQX_OK == mfs_mount(i))
                    {
                        _lwsem_post(&USB_Stick);
                    }
                }
                /* Disable flag to run FAT task */
                fat_task_flag[i] = 0;
                break;
            case USB_DEVICE_DETACHED:
                printf ( "\r\nMass Storage Device Detached\r\n" );

                _lwsem_wait(&USB_Stick);
                mfs_unmount(i);
                
                status = usb_host_close_dev_interface(g_host_handle, g_mass_device[i].dev_handle, g_mass_device[i].intf_handle, g_mass_device[i].CLASS_HANDLE);
                if (status != USB_OK)
                {
                    printf("error in _usb_hostdev_close_interface %x\r\n", status);
                }
                g_mass_device[i].intf_handle = NULL;
                g_mass_device[i].CLASS_HANDLE = NULL;
                printf("Going to idle state\r\n");
                g_mass_device[i].dev_state = USB_DEVICE_IDLE;
                break;
            case USB_DEVICE_OTHER:
                break;
            default:
                printf ( "Unknown Mass Storage Device State = %d\r\n",\
                        g_mass_device[i].dev_state );
                break;
            } /* End switch */
        }
    }
}


#endif

/* EOF */
