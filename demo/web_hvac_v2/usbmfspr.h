
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
* $FileName: usbmfspr.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*   The file contains functions prototype, defines, structure 
*   definitions private to the USB mass storage link driver
*   to MFS.
*
*END************************************************************************/
#ifndef _usbmfspr_h_
#define _usbmfspr_h_

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

/* Error codes from lower layers */
#define USB_MFS_DEFAULT_SECTOR_SIZE  (512)

/*----------------------------------------------------------------------*/
/*
**                          ERROR CODES
*/

/* Error codes from lower layers */
/*
#define USB_MFS_NO_ERROR             MQX_OK
#define USB_MFS_READ_ERROR           IO_ERROR_READ
#define USB_MFS_WRITE_ERROR          IO_ERROR_WRITE
#define USB_MFS_INVALID_SECTOR       IO_ERROR_SEEK
*/

/*----------------------------------------------------------------------*/
/*
**                    DATATYPE DEFINITIONS
*/


/*
** USB_MFS_INFO_STRUCT
** Run time state information for each USB mass storage device
*/
typedef struct
{
   mass_command_struct_t                     COMMAND;    /* MUST BE FIRST */
#if PSP_HAS_DATA_CACHE
   unsigned char                             FILLER1[CACHE_LINE_FILLER(sizeof(mass_command_struct_t))];
#endif
   cbw_struct_t                              CBW;
#if PSP_HAS_DATA_CACHE
   unsigned char                             FILLER2[CACHE_LINE_FILLER(sizeof(cbw_struct_t))];
#endif
   csw_struct_t                              CSW;
#if PSP_HAS_DATA_CACHE
   unsigned char                             FILLER3[CACHE_LINE_FILLER(sizeof(csw_struct_t))];
#endif
   inquiry_data_format_struct_t              INQUIRY_DATA;
#if PSP_HAS_DATA_CACHE
   unsigned char                             FILLER4[CACHE_LINE_FILLER(sizeof(inquiry_data_format_struct_t))];
#endif
   mass_storage_read_capacity_cmd_struct_t   CAPACITY;
#if PSP_HAS_DATA_CACHE
   unsigned char                             FILLER5[CACHE_LINE_FILLER(sizeof(mass_storage_read_capacity_cmd_struct_t))];
#endif
   req_sense_data_format_struct_t            SENSE;
#if PSP_HAS_DATA_CACHE
   unsigned char                             FILLER6[CACHE_LINE_FILLER(sizeof(req_sense_data_format_struct_t))];
#endif
   /* Handle for mass storage class  calls */
   void*           MSC_STREAM;
   
   /* 8 bytes of ASCI Data identifying the vendor of the product */
   
   /* 16 bytes of ASCI Data defined by the vendor */
  
   /* 4 bytes of ASCI Data defined by the vendor */
   
   /* CBW tag used for commands */
   uint32_t        CBW_TAG;         
   
   /* Drive number to associate with this slot */
   uint8_t         LUN;
   
   uint32_t        BLENGTH;   /* logic block length */
   uint32_t        BCOUNT;    /* logic blocks count */

   /* Total size of Drive in bytes */
   uint32_t        SIZE_BYTES; 

   /* The number of heads as reported  */
   uint32_t        NUMBER_OF_HEADS;          

   /* The number of tracks as reported  */
   uint32_t        NUMBER_OF_TRACKS;

   /* The number of sectos per cylinder as reported */
   uint32_t        SECTORS_PER_TRACK;

   /* Light weight semaphore struct */
   os_sem_handle   LWSEM;
   
   /* The address of temp buffer */

   /* The current error code for the device */
   uint32_t        ERROR_CODE;
   
   /* Start CR 812 */
   /* Indicates if the device is running in block mode or character mode */
   bool            BLOCK_MODE;
   /* End   CR 812 */

   uint32_t        COMMAND_STATUS;
   os_sem_handle   COMMAND_DONE;
} io_usb_mfs_struct_t;

#ifdef __cplusplus
extern "C" {
#endif

extern _mqx_int _io_usb_mfs_open(MQX_FILE_PTR, char *, char *);
extern _mqx_int _io_usb_mfs_close(MQX_FILE_PTR);
extern _mqx_int _io_usb_mfs_read (MQX_FILE_PTR, char *, int32_t);
extern _mqx_int _io_usb_mfs_write(MQX_FILE_PTR, char *, int32_t);
extern _mqx_int _io_usb_mfs_ioctl(MQX_FILE_PTR, int32_t, void *);
extern int32_t _io_usb_mfs_uninstall(IO_DEVICE_STRUCT_PTR  io_dev_ptr);
   
#ifdef __cplusplus
}
#endif

#endif
/* EOF */
