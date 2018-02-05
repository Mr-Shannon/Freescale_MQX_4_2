/**HEADER********************************************************************
* 
* Copyright (c) 2008, 2013 Freescale Semiconductor;
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
* $FileName: usbmfs.h$
* $Version : 3.8.12.0$
* $Date    : Sep-19-2011$
*
* Comments:
*
*   The file contains functions prototype, defines, structure 
*   definitions specific for USB MFS mass storage link driver.
*
*END************************************************************************/
#ifndef _usbmfs_h_
#define _usbmfs_h_

#include "io.h"
#include "ioctl.h"

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

/*
** USB_MFS IOCTL calls
*/
#define USB_MFS_IOCTL_GET_NUM_SECTORS      _IO(IO_TYPE_USBMFS,0x02)
#define USB_MFS_IOCTL_GET_BLOCK_SIZE       _IO(IO_TYPE_USBMFS,0x03)
#define USB_MFS_IOCTL_GET_SECTOR_SIZE      _IO(IO_TYPE_USBMFS,0x04)
#define USB_MFS_IOCTL_GET_DRIVE_PARAMS     _IO(IO_TYPE_USBMFS,0x05)
#define USB_MFS_IOCTL_DEVICE_STOP          _IO(IO_TYPE_USBMFS,0x09)
#define USB_MFS_IOCTL_SET_BLOCK_MODE       _IO(IO_TYPE_USBMFS,0x0A)
#define USB_MFS_IOCTL_DEVICE_IDENTIFY      _IO(IO_TYPE_USBMFS,0x0B)

#define USB_MFS_IOCTL_GET_VENDOR_INFO      _IO(IO_TYPE_USBMFS,0x16)
#define USB_MFS_IOCTL_GET_PRODUCT_ID       _IO(IO_TYPE_USBMFS,0x17)
#define USB_MFS_IOCTL_GET_PRODUCT_REV      _IO(IO_TYPE_USBMFS,0x18)

#define USB_MFS_VERY_LARGE_DRIVE           (3)

#ifdef PSP_CACHE_LINE_SIZE
   #define CACHE_LINE_FILLER(x)    (PSP_CACHE_LINE_SIZE-(x%PSP_CACHE_LINE_SIZE))
#else
   #define CACHE_LINE_FILLER(x)
#endif

#ifndef USB_MFS_LWSEM_TIMEOUT
#define USB_MFS_LWSEM_TIMEOUT              (_time_get_ticks_per_sec() * 20)
#endif

#ifndef USB_MFS_MAX_RETRIES
#define USB_MFS_MAX_RETRIES                (5)
#endif

#ifndef USB_MFS_READ_CAPACITY_RETRY_DELAY
#define USB_MFS_READ_CAPACITY_RETRY_DELAY  (_time_get_ticks_per_sec() * 1)
#endif

/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

typedef struct usb_mfs_drive_info_struct
{
   uint32_t  NUMBER_OF_HEADS; 
   uint32_t  NUMBER_OF_TRACKS;
   uint32_t  SECTORS_PER_TRACK;
} USB_MFS_DRIVE_INFO_STRUCT, * USB_MFS_DRIVE_INFO_STRUCT_PTR;
    
/*----------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

uint32_t _io_usb_mfs_install(char * , uint8_t, void*);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
