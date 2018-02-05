/**HEADER********************************************************************
* 
* Copyright (c) 2008, 2013 - 2014 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
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
* $FileName: usbmfs.c$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains the USB MFS mass storage link driver.
*
*END************************************************************************/
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#include <mqx.h>
#include <lwevent.h>
#include <bsp.h>
#include <mfs.h>
#include <part_mgr.h>
#include <usbmfs.h>

#include <usb_types.h> /* USB error definitions */
#include <usb_desc.h>  /* USB descriptor macros */
#include <usb_misc.h>
#include <usb_opt.h>
#include <usb_error.h>

#include <usb_host_config.h>
#include <usb_host_stack_interface.h>
#include <usb_host_hub_sm.h>
#include <usb_host_msd_bo.h>
#include <usb_host_msd_ufi.h>

#include "usbmfs.h"
#include "usbmfspr.h"


#if ENDIANNESS == BIG_ENDIAN

#error ENDIANNESS should be set to LITTLE_ENDIAN, and rebulid usbh.

#endif

/* Function declaration */
static void _io_usb_mfs_callback
(
    usb_status,  /*status of this command*/
    void*,     /*pointer to USB_MASS_BULK_ONLY_REQUEST_STRUCT*/
    void*,     /*pointer to the command object*/
    uint32_t      /* length of the data transfered if any */
);

static int32_t _io_usb_mfs_open_internal(io_usb_mfs_struct_t * info_ptr,  usb_class_handle handle);
static int32_t _io_usb_mfs_ioctl_stop(io_usb_mfs_struct_t * info_ptr);
static int32_t _io_usb_mfs_read_sector_internal(io_usb_mfs_struct_t * info_ptr, uint32_t sector, uint16_t how_many_sectors, uint8_t * data_ptr);
static int32_t _io_usb_mfs_read_sector_long_internal(io_usb_mfs_struct_t * info_ptr, uint32_t sector, uint32_t how_many_sectors, uint8_t * data_ptr);
static int32_t _io_usb_mfs_write_sector_internal(io_usb_mfs_struct_t * info_ptr, uint32_t sector, uint16_t how_many_sectors, uint8_t * data_ptr);
static int32_t _io_usb_mfs_write_sector_long_internal(io_usb_mfs_struct_t * info_ptr, uint32_t sector, uint32_t how_many_sectors, uint8_t * data_ptr);
static int32_t _io_usb_mfs_read_write_sectors_internal(io_usb_mfs_struct_t * info_ptr, char * data_ptr, uint32_t num, bool write, MQX_FILE_PTR fd_ptr);
static void _io_usb_mfs_callback(usb_status command_status, void* p1, void* p2, uint32_t len);
static void _io_usb_ctrl_callback(void*, void*, uint8_t *, uint32_t, usb_status);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_install
* Returned Value   : uint32_t - a task error code or MQX_OK
* Comments         :
*    Install a  USB-MFS mass storage device driver.
*
*END*----------------------------------------------------------------------*/

uint32_t _io_usb_mfs_install
   (
      /* [IN] A string that identifies the device for fopen */
      char *                        identifier,

      /* [IN] Logical unit number which driver need to install */
      uint8_t                        logical_unit,

      /* [IN]  the class driver handle */
      void *                         handle
   )
{ /* Body */
   io_usb_mfs_struct_t *            info_ptr;
   usb_mass_class_struct_t *        mass_class = (usb_mass_class_struct_t *)handle;

   /* Pointer validity-checking, clear memory, init header */
   /* OS_Lock(); */
   
   if (mass_class == NULL)
   {
	  /* OS_Unlock(); */
      printf("_io_usb_mfs_install fail\n");
      return USBERR_ERROR;
   }
   
   info_ptr = (io_usb_mfs_struct_t *)OS_Mem_alloc_uncached_zero(sizeof(io_usb_mfs_struct_t));
   if (info_ptr == NULL)
   {
	   /* OS_Unlock(); */
       printf("_io_usb_mfs_install fail on memory allocation\n");
       return USBERR_ERROR;
   }

   /* OS_Unlock(); */

   /* Fill in the state structure with the info we know */
   info_ptr->LUN         = logical_unit;
   info_ptr->BLENGTH     = USB_MFS_DEFAULT_SECTOR_SIZE;
   info_ptr->ERROR_CODE  = IO_OK;
   info_ptr->BLOCK_MODE  = TRUE;

   info_ptr->COMMAND.CBW_PTR = (cbw_struct_t *) &info_ptr->CBW;
   info_ptr->COMMAND.CSW_PTR = (csw_struct_t *) &info_ptr->CSW;
   info_ptr->COMMAND.CLASS_PTR = handle;
   info_ptr->COMMAND.LUN = logical_unit;
   info_ptr->COMMAND.CALLBACK = _io_usb_mfs_callback;
   info_ptr->COMMAND_STATUS = MQX_OK;
   info_ptr->LWSEM = OS_Sem_create(0);
   info_ptr->COMMAND_DONE = OS_Sem_create(0);

   OS_Sem_post(info_ptr->LWSEM);

   return (_io_dev_install_ext(identifier,
      (int32_t (_CODE_PTR_)(MQX_FILE_PTR, char *,  char *))_io_usb_mfs_open,
      (int32_t (_CODE_PTR_)(MQX_FILE_PTR)                     )_io_usb_mfs_close,
      (int32_t (_CODE_PTR_)(MQX_FILE_PTR, char *,  int32_t)  )_io_usb_mfs_read,
      (int32_t (_CODE_PTR_)(MQX_FILE_PTR, char *,  int32_t)  )_io_usb_mfs_write,
      (int32_t (_CODE_PTR_)(MQX_FILE_PTR, uint32_t, void*) ) _io_usb_mfs_ioctl,
      _io_usb_mfs_uninstall,
      (void*)info_ptr /* instead of info_ptr */
      ));

} /* Endbody */



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_uninstall_internal
* Returned Value   : uint32_t error code
* Comments  :   Uninstalls the MSDOS File System and frees all memory allocated
*               to it.
*
*END*---------------------------------------------------------------------*/
int32_t _io_usb_mfs_uninstall
   (
       /* [IN] The device to uninstall */            
      IO_DEVICE_STRUCT_PTR   io_dev_ptr
   )
{ 
   io_usb_mfs_struct_t * info_ptr;

   /* Workaround for the issue with device file specific structure, which is later on accessed by the MFS:
   ** We will return pointer to allocated block rather than USB-host buffer pointer (see USB _usb_hostdev_get_buffer)
   */
   info_ptr = (io_usb_mfs_struct_t *)io_dev_ptr->DRIVER_INIT_PTR;

   OS_Sem_destroy(info_ptr->COMMAND_DONE);
   OS_Sem_destroy(info_ptr->LWSEM);
   /* The info_ptr will be disposed after device detach */
   OS_Mem_free(info_ptr);
   return MQX_OK;
}
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_open_internal
* Returned Value   : An error code or MQX_OK
* Comments         : Opens and initializes a USB-MFS mass storage device driver.
*                    Mass storage device should be initialized to prior to this
*                    this call.
*END*----------------------------------------------------------------------*/
static int32_t _io_usb_mfs_open_internal
   (

   io_usb_mfs_struct_t *            info_ptr,
   /* [IN]  the class driver handle */
   usb_class_handle                 handle
   )
{ /* Body */
   uint32_t     i;
   usb_status   error;

   error = usb_class_mass_getmaxlun_bulkonly(info_ptr->COMMAND.CLASS_PTR, (uint8_t *) &info_ptr->INQUIRY_DATA, _io_usb_ctrl_callback, info_ptr);
   if (error != MQX_OK) 
   {
      return IO_ERROR;
   } /* Endif */
   if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) != MQX_OK) 
   {
      /* Cancel the command */
      usb_mass_ufi_cancel(&info_ptr->COMMAND);
      return IO_ERROR_TIMEOUT;
   } /* Endif */

   error = usb_mass_ufi_inquiry(&info_ptr->COMMAND, (uint8_t *) &info_ptr->INQUIRY_DATA, sizeof(inquiry_data_format_struct_t));
   if (error != MQX_OK) 
   {
      return IO_ERROR_INQUIRE;
   } /* Endif */
   if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) != MQX_OK) 
   {
      /* Cancel the command */
      usb_mass_ufi_cancel(&info_ptr->COMMAND);
      return IO_ERROR_TIMEOUT;
   } /* Endif */


   if (info_ptr->COMMAND_STATUS != MQX_OK) 
   {
      return IO_ERROR_INQUIRE;
   } /* Endif */

   for (i = 0; i < USB_MFS_MAX_RETRIES; i++) 
   {
      if (i) 
      {
         /* Delay for a user-specified amount of time */
         _time_delay_ticks(USB_MFS_READ_CAPACITY_RETRY_DELAY);
      }
      
      /* Send the call now */
      error = usb_mass_ufi_read_capacity(&info_ptr->COMMAND, (uint8_t *) &info_ptr->CAPACITY,
         sizeof(mass_storage_read_capacity_cmd_struct_t));

      if (error!=MQX_OK)
      {
         return IO_ERROR_READ;
      } /* Endif */

      if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) != MQX_OK) 
      {
         usb_mass_ufi_cancel(&info_ptr->COMMAND);
         return IO_ERROR_TIMEOUT;
      } /* Endif */
      
      if (info_ptr->COMMAND_STATUS == MQX_OK)
         break;
      
      
      error = usb_mass_ufi_request_sense(&info_ptr->COMMAND, &info_ptr->SENSE, sizeof(req_sense_data_format_struct_t));

      if (error != MQX_OK)
      {
         return IO_ERROR_READ;
      }

      if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) != MQX_OK) 
      {
         usb_mass_ufi_cancel(&info_ptr->COMMAND);
         return IO_ERROR_TIMEOUT;
      }
   }
   
   if (info_ptr->COMMAND_STATUS == MQX_OK) 
   {
      info_ptr->BCOUNT = USB_LONG_BE_TO_HOST(*(uint32_t*)&info_ptr->CAPACITY.BLLBA);
      info_ptr->BLENGTH = USB_LONG_BE_TO_HOST(*(uint32_t*)&info_ptr->CAPACITY.BLENGTH);

      /* should read this to support  low level format */
      info_ptr->NUMBER_OF_HEADS   = 0;
      info_ptr->NUMBER_OF_TRACKS  = 0;
      info_ptr->SECTORS_PER_TRACK = 0;

      info_ptr->SIZE_BYTES = info_ptr->BLENGTH * info_ptr->BCOUNT;
   } /* Endif */
   
   return (int32_t)info_ptr->COMMAND_STATUS;
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_open
* Returned Value   : An error code or MQX_OK
* Comments         : Opens and initializes a USB-MFS mass storage device driver.
*                    Mass storage device should be initialized to prior to this
*                    this call.
*END*----------------------------------------------------------------------*/
int32_t _io_usb_mfs_open
   (
      /* [IN] the file handle for the device being opened */
      MQX_FILE_PTR       fd_ptr,

      /* [IN] the remaining portion of the name of the device */
      char *            open_name_ptr,

      /* [IN] USB mass storage class handle */
      char *            flags
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR             io_dev_ptr = fd_ptr->DEV_PTR;
   usb_mass_class_struct_t *        mass_class = NULL;
   int32_t                          io_error;
   io_usb_mfs_struct_t *            info_ptr;

   /* Workaround for the issue with device file specific structure, which is later on accessed by the MFS:
   ** We will return pointer to allocated block rather than USB-host buffer pointer (see USB _usb_hostdev_get_buffer)
   */
   info_ptr = (io_usb_mfs_struct_t *)io_dev_ptr->DRIVER_INIT_PTR;

   if(NULL == info_ptr)
   {
	   printf("_io_usb_mfs_open fail\n");
	   return IO_DEVICE_DOES_NOT_EXIST;
   }
   
   mass_class = (usb_mass_class_struct_t *)info_ptr->COMMAND.CLASS_PTR;
   
   if (mass_class == NULL)
   {
       printf("_io_usb_mfs_open fail\n");
       return IO_DEVICE_DOES_NOT_EXIST;
   }
   /* Save the mass storage class handle. */
   info_ptr->MSC_STREAM = (void*) mass_class;

   /* Send the call now */
   OS_Sem_wait(info_ptr->LWSEM, 0);
   io_error = _io_usb_mfs_open_internal(info_ptr, (usb_class_handle)mass_class);
   OS_Sem_post(info_ptr->LWSEM);

   return io_error;
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_close
* Returned Value   : ERROR CODE
* Comments         : Closes the USB mass storage link driver
*
*END*----------------------------------------------------------------------*/

int32_t _io_usb_mfs_close
   (
      /* [IN] the file handle for the device being closed */
      MQX_FILE_PTR fd_ptr
   )
{ /* Body */
   return(MQX_OK);

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_read
* Returned Value   : number of bytes read
* Comments         : Reads data from the USB mass storage device
*
*END*----------------------------------------------------------------------*/
int32_t _io_usb_mfs_read
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR          fd_ptr,
      /* [IN] where the outgoing data is store */
      char *                data_ptr,
      /* [IN] the number of bytes to output */
      int32_t               num
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR   io_dev_ptr = fd_ptr->DEV_PTR;
   int32_t                io_result;
   io_usb_mfs_struct_t *  info_ptr;

   /* Workaround for the issue with device file specific structure, which is later on accessed by the MFS:
   ** We will return pointer to allocated block rather than USB-host buffer pointer (see USB _usb_hostdev_get_buffer)
   */
   info_ptr = (io_usb_mfs_struct_t *)io_dev_ptr->DRIVER_INIT_PTR;

   OS_Sem_wait(info_ptr->LWSEM, 0);
   io_result = _io_usb_mfs_read_write_sectors_internal(info_ptr, data_ptr, (uint32_t)num, FALSE, fd_ptr);
   OS_Sem_post(info_ptr->LWSEM);
   return io_result;
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_write
* Returned Value   : number of bytes written
* Comments         : Writes data to the USB mass storage device
*
*END*----------------------------------------------------------------------*/
int32_t _io_usb_mfs_write
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR          fd_ptr,
      /* [IN] where the outgoing data is store */
      char *                data_ptr,
      /* [IN] the number of bytes to output */
      int32_t               num
   )
{ /* Body */
   IO_DEVICE_STRUCT_PTR   io_dev_ptr = fd_ptr->DEV_PTR;
   int32_t                results;
   io_usb_mfs_struct_t *  info_ptr;

   /* Workaround for the issue with device file specific structure, which is later on accessed by the MFS:
   ** We will return pointer to allocated block rather than USB-host buffer pointer (see USB _usb_hostdev_get_buffer)
   */
   info_ptr = (io_usb_mfs_struct_t *)io_dev_ptr->DRIVER_INIT_PTR;

   OS_Sem_wait(info_ptr->LWSEM, 0);

   results = _io_usb_mfs_read_write_sectors_internal(info_ptr, data_ptr, (uint32_t)num, TRUE, fd_ptr);

   OS_Sem_post(info_ptr->LWSEM);
   return(results);
} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_ioctl
* Returned Value   : int32_t
* Comments         :
*    Returns result of ioctl operation.
*
*END*-------------------------------------------------------------------------*/
static int32_t _io_usb_mfs_ioctl_stop
   (
   io_usb_mfs_struct_t *       info_ptr 
   )
{ /* Body */
   mass_storage_start_stop_unit_struct_t     start_stop = {0};
   usb_status                                error;
   int32_t                                   io_result = IO_ERROR;

   start_stop.START = 0;
   start_stop.LOEJ  = 0;
   error = usb_mass_ufi_start_stop(&info_ptr->COMMAND, start_stop.LOEJ, start_stop.START);
   if (error==MQX_OK) 
   {
      if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) == MQX_OK) 
      {
         if (info_ptr->COMMAND_STATUS == MQX_OK) 
         {
            io_result =  MQX_OK;
         } /* Endif */
      } 
      else 
      {
         usb_mass_ufi_cancel(&info_ptr->COMMAND);
      } /* Endif */
   } /* Endif */
   return(io_result);

} /* Endbody */


/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_ioctl
* Returned Value   : int32_t
* Comments         :
*    Returns result of ioctl operation.
*
*END*-------------------------------------------------------------------------*/
int32_t _io_usb_mfs_ioctl
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR  fd_ptr,

      /* [IN] the ioctl command */
      int32_t       command,

      /* [IN] the ioctl parameters */
      void*         input_param_ptr
   )
{ /* Body */
   USB_MFS_DRIVE_INFO_STRUCT_PTR drive_info_ptr;
   IO_DEVICE_STRUCT_PTR          io_dev_ptr = fd_ptr->DEV_PTR;
   int32_t                       result = MQX_OK;
   uint32_t*                     param_ptr = input_param_ptr;
   io_usb_mfs_struct_t *         info_ptr;

   /* Workaround for the issue with device file specific structure, which is later on accessed by the MFS:
   ** We will return pointer to allocated block rather than USB-host buffer pointer (see USB _usb_hostdev_get_buffer)
   */
   info_ptr = (io_usb_mfs_struct_t *)io_dev_ptr->DRIVER_INIT_PTR;

   switch (command) 
   {
      case IO_IOCTL_GET_NUM_SECTORS:
      case USB_MFS_IOCTL_GET_NUM_SECTORS:
         *param_ptr = info_ptr->BCOUNT;
         break;

      case IO_IOCTL_GET_BLOCK_SIZE:
      case USB_MFS_IOCTL_GET_BLOCK_SIZE:
         *param_ptr = info_ptr->BLENGTH;
         break;

      case USB_MFS_IOCTL_DEVICE_IDENTIFY:
      case IO_IOCTL_DEVICE_IDENTIFY:
         param_ptr[0] = IO_DEV_TYPE_PHYS_USB_MFS;
         param_ptr[1] = IO_DEV_TYPE_LOGICAL_MFS;
         param_ptr[2] = IO_DEV_ATTR_ERASE | IO_DEV_ATTR_POLL
                         | IO_DEV_ATTR_READ | IO_DEV_ATTR_REMOVE
                         | IO_DEV_ATTR_SEEK | IO_DEV_ATTR_WRITE;
         if (info_ptr->BLOCK_MODE) 
         {
            param_ptr[2] |= IO_DEV_ATTR_BLOCK_MODE;
         } /* Endif */
         break;

      case USB_MFS_IOCTL_GET_DRIVE_PARAMS:
         drive_info_ptr = (USB_MFS_DRIVE_INFO_STRUCT_PTR)((void*)param_ptr);
         drive_info_ptr->NUMBER_OF_HEADS   = info_ptr->NUMBER_OF_HEADS;
         drive_info_ptr->NUMBER_OF_TRACKS  = info_ptr->NUMBER_OF_TRACKS;
         drive_info_ptr->SECTORS_PER_TRACK = info_ptr->SECTORS_PER_TRACK;
         break;

      case USB_MFS_IOCTL_GET_VENDOR_INFO:
         *param_ptr = (uint32_t)&(info_ptr->INQUIRY_DATA.BVID);
         break;

      case USB_MFS_IOCTL_GET_PRODUCT_ID:
         *param_ptr = (uint32_t)&(info_ptr->INQUIRY_DATA.BPID);
         break;

      case USB_MFS_IOCTL_GET_PRODUCT_REV:
         *param_ptr = (uint32_t)&(info_ptr->INQUIRY_DATA.BPRODUCT_REV);
         break;

      case USB_MFS_IOCTL_DEVICE_STOP:
         /* Send the call now */
         OS_Sem_wait(info_ptr->LWSEM, 0);
         

         result = _io_usb_mfs_ioctl_stop(info_ptr);

            /* Wait for the completion*/
         OS_Sem_post(info_ptr->LWSEM);


         break;

         /* Start CR 812 */
      case IO_IOCTL_SET_BLOCK_MODE:
      case USB_MFS_IOCTL_SET_BLOCK_MODE:
         info_ptr->BLOCK_MODE = TRUE;
         break;
         /* End   CR 812 */

      default:
         result = IO_ERROR_INVALID_IOCTL_CMD;
         break;
   } /* Endswitch */
   return(result);

} /* Endbody */


/* Private functions */
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_read_sector
* Returned Value   : error code
* Comments         :
*
*
*END*----------------------------------------------------------------------*/
static int32_t _io_usb_mfs_read_sector_internal
   (
      /* [IN] USB MFS state structure */
      io_usb_mfs_struct_t *   info_ptr,

      /* [IN] The sector number to read */
      uint32_t                sector,

      /* [IN] How many sectors should read */
      uint16_t                how_many_sectors,


      /* [IN] Location to read data into */
      uint8_t *               data_ptr
   )
{ /* Body */
   uint32_t                   read_size;
   usb_status                 error;
   int32_t                    io_result = IO_ERROR;
   uint32_t                   tries;

   /* UFI_READ10 command  */
   read_size = info_ptr->BLENGTH * how_many_sectors;

   /* Send the call now */
   for (tries=0;tries<USB_MFS_MAX_RETRIES;tries++) 
   {
      error = usb_mass_ufi_read_10(
         &info_ptr->COMMAND, sector, data_ptr, read_size, how_many_sectors);
      if (error==MQX_OK) 
      {
         if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) == MQX_OK) 
         {
            if (info_ptr->COMMAND_STATUS == MQX_OK) 
            {
               io_result = (int32_t)how_many_sectors;
               break;
            } /* Endif */
         }
         else 
         {
            /* Wait for the completion*/
            usb_mass_ufi_cancel(&info_ptr->COMMAND);
         } /* Endif */
      }
      else 
      {
#ifdef _HOST_DEBUG_
          printf("\nUSBMFS retrying read sector");
#endif
      } /* Endif */

   } /* Endif */

   return(io_result);
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_read_sector_long
* Returned Value   : error code
* Comments         :
*
*
*END*----------------------------------------------------------------------*/
static int32_t _io_usb_mfs_read_sector_long_internal
   (
      /* [IN] USB MFS state structure */
      io_usb_mfs_struct_t *   info_ptr,

      /* [IN] The sector number to read */
      uint32_t                sector,

      /* [IN] How many sectors should read */
      uint32_t                how_many_sectors,

      /* [IN] Location to read data into */
      uint8_t *               data_ptr
   )
{ /* Body */
   uint32_t                   read_size;
   usb_status                 error;
   int32_t                    io_result = IO_ERROR;
   uint32_t                   tries;

   read_size = info_ptr->BLENGTH * how_many_sectors;

   /* Send the call now */
   for (tries=0;tries<USB_MFS_MAX_RETRIES;tries++) 
   {
      error = usb_mass_ufi_read_12(
         &info_ptr->COMMAND, sector, data_ptr, read_size, how_many_sectors);

      if (error==MQX_OK)
      {
         if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) == MQX_OK) 
         {
            if (info_ptr->COMMAND_STATUS == MQX_OK) 
            {
               io_result = (int32_t) how_many_sectors;
               break;
   } /* Endif */
         } 
         else 
         {
            usb_mass_ufi_cancel(&info_ptr->COMMAND);
         } /* Endif */
      } /* Endif */
      /* printf("\nUSBMFS retrying read sector long"); */
   } /* Endif */

   return (io_result);
} /* Endbody */




/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_write_sector
* Returned Value   : error code
* Comments         :
*
*
*END*----------------------------------------------------------------------*/
static int32_t _io_usb_mfs_write_sector_internal
   (
      /* [IN] USB MFS state structure */
      io_usb_mfs_struct_t *   info_ptr,

      /* [IN] The sector number to write */
      uint32_t                sector,

      /* [IN] How many sectors should read */
      uint16_t                how_many_sectors,

      /* [IN] Source data location */
      uint8_t *               data_ptr
   )
{ /* Body */
   uint32_t                   write_size;
   uint32_t                   tries;
   usb_status                 error;
   int32_t                    io_result = IO_ERROR;

   if (sector <= info_ptr->BCOUNT) 
   {

      write_size = info_ptr->BLENGTH * how_many_sectors;
      for (tries=0;tries<USB_MFS_MAX_RETRIES;tries++) 
      {
         error = usb_mass_ufi_write_10(&info_ptr->COMMAND,
               sector, data_ptr, write_size, how_many_sectors);
         if (error==MQX_OK)
         {
            if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) == MQX_OK) 
            {
               if (info_ptr->COMMAND_STATUS == MQX_OK) 
               {
                  io_result = (int32_t) how_many_sectors;
                  break;
               } /* Endif */
            } 
            else 
            {

               /* Send the call now */

               /* Wait for the completion*/
               usb_mass_ufi_cancel(&info_ptr->COMMAND);
            } /* Endif */
         } /* Endif */
         /* printf("\nUSBMFS retrying write sector"); */
      }
   } /* Endif */

   return (io_result);
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_write_sector_long
* Returned Value   : error code
* Comments         :
*
*
*END*----------------------------------------------------------------------*/
static int32_t _io_usb_mfs_write_sector_long_internal
   (
      /* [IN] USB MFS state structure */
      io_usb_mfs_struct_t *   info_ptr,

      /* [IN] The sector number to write */
      uint32_t                sector,

      /* [IN] How many sectors should read */
      uint32_t                how_many_sectors,

      /* [IN] Source data location */
      uint8_t *               data_ptr
   )
{ /* Body */
   uint32_t                   write_size;
   usb_status                 error;
   int32_t                    io_result = IO_ERROR;
   uint32_t                   tries;

   if (sector <= info_ptr->BCOUNT) 
   {

      write_size = info_ptr->BLENGTH * how_many_sectors;
      for (tries=0;tries<USB_MFS_MAX_RETRIES;tries++) 
      {
         error = usb_mass_ufi_write_12(&info_ptr->COMMAND,
            sector, data_ptr, write_size, how_many_sectors);
         if (error==MQX_OK) 
         {
            if (OS_Sem_wait(info_ptr->COMMAND_DONE, USB_MFS_LWSEM_TIMEOUT) == MQX_OK) 
            {
               if (info_ptr->COMMAND_STATUS == MQX_OK) 
               {
                  io_result = (int32_t) how_many_sectors;
                  break;
               } /* Endif */
            } 
            else 
            {

               /* Send the call now */
               usb_mass_ufi_cancel(&info_ptr->COMMAND);
            }
            /* Wait for the completion*/
         } /* Endif */
      }
   } /* Endif */

   return (io_result);
} /* Endbody */



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_read_write_blocks
* Returned Value   : error or number of blocks read/written
* Comments         : This function is used to read/write blocks when driver
*   is in block mode
*
*END*----------------------------------------------------------------------*/
static int32_t _io_usb_mfs_read_write_sectors_internal
   (
      /* [IN] USB MFS state structure */
      io_usb_mfs_struct_t *    info_ptr,

      /* [IN] where the newly-read bytes are to be stored */
      char *                   data_ptr,

      /* [IN] the number of sectors to read */
      uint32_t                 num,

      /* [IN] Read/write mode */
      bool                     write,
      
      /* [IN] File pointer for checking file LOCATION and setting ERROR */
      MQX_FILE_PTR             fd_ptr
   )
{ /* Body */
   int32_t (_CODE_PTR_ rw_func_long)(io_usb_mfs_struct_t *, uint32_t, uint32_t, uint8_t *);
   int32_t (_CODE_PTR_ rw_func)(io_usb_mfs_struct_t *, uint32_t, uint16_t, uint8_t *);
   int32_t             io_result = IO_ERROR;
   uint32_t            io_error; 

   if (write) 
   {
      io_error = IO_ERROR_WRITE_ACCESS;
      rw_func        = _io_usb_mfs_write_sector_internal;
      rw_func_long   = _io_usb_mfs_write_sector_long_internal;
   } 
   else 
   {
      io_error = IO_ERROR_READ_ACCESS;
      rw_func        = _io_usb_mfs_read_sector_internal;
      rw_func_long   = _io_usb_mfs_read_sector_long_internal;
   } /* Endif */


   if (fd_ptr->LOCATION >= info_ptr->BCOUNT) 
   {
      fd_ptr->ERROR = io_error;
   } 
   else 
   {
      if ((num + fd_ptr->LOCATION) >= info_ptr->BCOUNT) 
      {
         fd_ptr->ERROR = io_error;
         num = (uint32_t)(info_ptr->BCOUNT - fd_ptr->LOCATION + 1);
      } /* Endif */

      /* Read all the sectors, one at a time */
      if (num > 0xFFFE) 
      {
         /* Read all the sectors at once */
          io_result = rw_func_long(info_ptr, fd_ptr->LOCATION,
            num, (uint8_t *)data_ptr);
      } 
      else 
      {
          io_result = rw_func(info_ptr, fd_ptr->LOCATION,
            (uint16_t)num, (uint8_t *)data_ptr);
      } /* Endif */
      if (io_result == IO_ERROR ) 
      {
         fd_ptr->ERROR = io_error;
      } 
      else 
      {
         fd_ptr->LOCATION += num;
      } /* Endif */
   } /* Endif */
   return io_result;

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_mfs_callback
* Returned Value   : None
* Comments         : This function is called by lowlevel drivers
when a command call back is set
*
*END*----------------------------------------------------------------------*/
static void _io_usb_mfs_callback
   (
      usb_status command_status,      /*status of this command*/
      void*      p1,     /* pointer to USB_MASS_BULK_ONLY_REQUEST_STRUCT*/
      void*      p2,     /* pointer to the command object*/
      uint32_t   len     /* length of the data transfered if any */
   )
{ /* Body */
   io_usb_mfs_struct_t * info_ptr = (io_usb_mfs_struct_t *)p2;

   if (command_status == (usb_status)USB_MASS_FAILED_IN_DATA)
      info_ptr->COMMAND.CSW_PTR->BCSWSTATUS = CSW_STATUS_FAILED;
   if (info_ptr->COMMAND.CSW_PTR->BCSWSTATUS == CSW_STATUS_GOOD) 
   {
      info_ptr->COMMAND_STATUS = command_status;   /* set the status */
   } 
   else 
   {
      info_ptr->COMMAND_STATUS = (uint32_t)IO_ERROR;
   } 

   OS_Sem_post(info_ptr->COMMAND_DONE);
   
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_usb_ctrl_callback
* Returned Value   : None
* Comments         : This function is called by lowlevel drivers
* when a control pipe replies 
*
*END*----------------------------------------------------------------------*/
static void _io_usb_ctrl_callback(void* pipe_handle, void* user_param, uint8_t * buffer, uint32_t size, usb_status status)
{
   io_usb_mfs_struct_t * info_ptr = (io_usb_mfs_struct_t *)user_param;
   
   OS_Sem_post(info_ptr->COMMAND_DONE);
}

/* EOF */
