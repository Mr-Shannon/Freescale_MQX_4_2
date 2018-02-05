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
* $FileName: usb_file.c$
* $Version : $
* $Date    : $
*
* Comments:
*
*   This file contains the initialization and menu source code for
*   the USB mass storage MFS test example program using USB mass storage
*   link driver.
*
*END************************************************************************/

#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#include "lwevent.h"
#include "bsp.h"
#include "mfs.h"
#include "part_mgr.h"
#include "usbmfs.h"

#include "usb_host_hub_sm.h"
#include "usb_host_msd_bo.h"
#include "usb_host_msd_ufi.h"

#include "usbmfspr.h"

#include "hvac.h"
#include "usb_file.h"
#if DEMOCFG_ENABLE_USB_FILESYSTEM

void *usb_filesystem_install( 
    void       *usb_handle,
    char       *block_device_name,
    char       *partition_manager_name,
    char       *file_system_name )
{
    uint32_t                    partition_number;
    unsigned char               *dev_info;
    int32_t                     error_code;
    usb_filesystem_struct_t *   usb_fs_ptr;


    usb_fs_ptr = _mem_alloc_system_zero(sizeof(usb_filesystem_struct_t));
    if (usb_fs_ptr==NULL)
    {
        return NULL;
    }

    /* Install USB device */
    error_code = _io_usb_mfs_install(block_device_name, 0, (void *)usb_handle);
    if (error_code != MQX_OK)
    {
        printf("Error while installing USB device (0x%X)\r\n", error_code);
        return NULL;
    }
    usb_fs_ptr->DEV_NAME = block_device_name;

    /* Open the USB mass storage  device */
    _time_delay(500);
    usb_fs_ptr->DEV_FD_PTR = fopen(block_device_name, 0);

    if (usb_fs_ptr->DEV_FD_PTR == NULL)
    {
        printf("Unable to open USB device\r\n");
        usb_filesystem_uninstall(usb_fs_ptr);
        return NULL;
    } 

    _io_ioctl(usb_fs_ptr->DEV_FD_PTR, USB_MFS_IOCTL_SET_BLOCK_MODE, NULL);

    /* Get the vendor information and display it */
    printf("\r\n************************************************************************\r\n");
    _io_ioctl(usb_fs_ptr->DEV_FD_PTR, USB_MFS_IOCTL_GET_VENDOR_INFO, &dev_info);
    printf("Vendor Information:     %-1.8s Mass Storage Device\r\n",dev_info);
    _io_ioctl(usb_fs_ptr->DEV_FD_PTR, USB_MFS_IOCTL_GET_PRODUCT_ID, &dev_info);
    printf("Product Identification: %-1.16s\r\n",dev_info);
    _io_ioctl(usb_fs_ptr->DEV_FD_PTR, USB_MFS_IOCTL_GET_PRODUCT_REV, &dev_info);
    printf("Product Revision Level: %-1.4s\r\n",dev_info);
    printf("************************************************************************\r\n");

    /* Try to install the partition manager */
    error_code = _io_part_mgr_install(usb_fs_ptr->DEV_FD_PTR, partition_manager_name, 0);
    if (error_code != MFS_NO_ERROR)
    {
        printf("Error while initializing partition manager: %s\r\n", MFS_Error_text((uint32_t)error_code));
        usb_filesystem_uninstall(usb_fs_ptr);
        return NULL;
    } 
    usb_fs_ptr->PM_NAME = partition_manager_name;

    /* Open partition manager */
    usb_fs_ptr->PM_FD_PTR = fopen(partition_manager_name, NULL);
    if (usb_fs_ptr->PM_FD_PTR == NULL)
    {
        error_code = ferror(usb_fs_ptr->PM_FD_PTR);
        printf("Error while opening partition manager: %s\r\n", MFS_Error_text((uint32_t)error_code));
        usb_filesystem_uninstall(usb_fs_ptr);
        return NULL;
    } 

    /* Select partition */
    partition_number = 1;
    error_code = _io_ioctl(usb_fs_ptr->PM_FD_PTR, IO_IOCTL_SEL_PART, &partition_number);

    if (error_code == MFS_NO_ERROR)
    {
        printf("Installing MFS over partition...\r\n");

        /* Validate partition */
        error_code = _io_ioctl(usb_fs_ptr->PM_FD_PTR, IO_IOCTL_VAL_PART, NULL);
        if (error_code != MFS_NO_ERROR)
        {
            printf("Error while validating partition: %s\r\n", MFS_Error_text((uint32_t)error_code));
            printf("Not installing MFS.\r\n");
            usb_filesystem_uninstall(usb_fs_ptr);
            return NULL;
        }

        /* Install MFS over partition */
        error_code = _io_mfs_install(usb_fs_ptr->PM_FD_PTR, file_system_name, 0);
        if (error_code != MFS_NO_ERROR)
        {
            printf("Error initializing MFS over partition: %s\r\n", MFS_Error_text((uint32_t)error_code));
        }
    }
    else 
	{

        printf("Installing MFS over USB device...\r\n");

        /* Install MFS over USB device driver */
        error_code = _io_mfs_install(usb_fs_ptr->DEV_FD_PTR, file_system_name, 0);
        if (error_code != MFS_NO_ERROR)
        {
            printf("Error initializing MFS: %s\r\n", MFS_Error_text((uint32_t)error_code));
        }
    }

    /* Open file system */
    if (error_code == MFS_NO_ERROR)
    {
        usb_fs_ptr->FS_NAME = file_system_name;
        usb_fs_ptr->FS_FD_PTR = fopen(file_system_name, NULL);
        error_code = ferror(usb_fs_ptr->FS_FD_PTR);
        if (error_code == MFS_NOT_A_DOS_DISK)
        {
            printf("NOT A DOS DISK! You must format to continue.\r\n");
        }
        else if (error_code != MFS_NO_ERROR)
        {
            printf("Error opening filesystem: %s\r\n", MFS_Error_text((uint32_t)error_code));
            usb_filesystem_uninstall(usb_fs_ptr);
            return NULL;
        }

        printf("USB device installed to %s\r\n", file_system_name);  
    }
    else 
	{   
        usb_filesystem_uninstall(usb_fs_ptr);
        return NULL;
    }

    return (void*)usb_fs_ptr;
}

MQX_FILE_PTR usb_filesystem_handle( usb_filesystem_struct_t *  usb_fs_ptr)
{
    return usb_fs_ptr->FS_FD_PTR ;
}


void usb_filesystem_uninstall( usb_filesystem_struct_t *  usb_fs_ptr)
{
    uint32_t  error_code;

    if (usb_fs_ptr == NULL) 
	{
        return;
    }

    /* Close the filesystem */
    if (usb_fs_ptr->FS_FD_PTR != NULL)
    {
        printf("\r\n\r\nWaiting for tasks to close all files.\r\n");

        error_code = fclose(usb_fs_ptr->FS_FD_PTR);
        while (error_code == MFS_SHARING_VIOLATION)
        {
            /*
             * Filesystem could not be closed. There are probably still some files opened preventing it.
             * Wait for a while (give other tasks a chance to finish their job) and try again.
             */
            _time_delay(200);
            putchar('.');
            error_code = fclose(usb_fs_ptr->FS_FD_PTR);
        }

        if (error_code != MQX_OK)
        {
            printf("Error while closing filesystem.\r\n");
        }
    }

    /* Uninstall MFS */
    error_code = _io_dev_uninstall(usb_fs_ptr->FS_NAME);
    if (error_code != MFS_NO_ERROR)
    {
        printf("Error while uninstalling filesystem.\r\n");
    }

    /* Close partition */
    if ((usb_fs_ptr->PM_FD_PTR != NULL) && (MQX_OK != fclose(usb_fs_ptr->PM_FD_PTR)))
    {
        printf("Error while closing partition.\r\n");
    }

    /* Uninstall partition manager */
    error_code = _io_dev_uninstall(usb_fs_ptr->PM_NAME);
    if (error_code != MFS_NO_ERROR)
    {
        printf("Error while uninstalling partition manager.\r\n");
    }
    
    /* Close USB device */
    if ((usb_fs_ptr->DEV_FD_PTR != NULL) && (MQX_OK != fclose(usb_fs_ptr->DEV_FD_PTR)))
    {
        printf("Unable to close USB device.\r\n");
    }

    /* Uninstall USB device */
    error_code = _io_dev_uninstall(usb_fs_ptr->DEV_NAME);
    if (error_code != MQX_OK)
    {
        printf("Error while uninstalling USB device.\r\n");
    }

    _mem_free(usb_fs_ptr);

    printf("\r\nUSB device removed.\r\n");
}


#endif
/* EOF */
