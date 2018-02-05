/**HEADER********************************************************************
 *
 * Copyright (c) 2013 Freescale Semiconductor;
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
 * $FileName: sd.c$
 * $Version :
 * $Date    :
 *
 * Comments:
 *
 *
 *END************************************************************************/

#include "usb_device_config.h"
#include "mqx.h"
#include "bsp.h"
#include "fio.h"

#include "sd.h"

#if SD_CARD_APP

#include "sdcard.h"




#if defined BSP_SDCARD_ESDHC_CHANNEL
    #if ! BSPCFG_ENABLE_ESDHC
    #error "This application requires BSPCFG_ENABLE_ESDHC defined non-zero in user_config.h. Please recompile libraries with this option."
    #else
    #define SDCARD_COM_CHANNEL BSP_SDCARD_ESDHC_CHANNEL
    #endif

#elif defined BSP_SDCARD_SDHC_CHANNEL
    #if ! BSPCFG_ENABLE_SDHC
    #error "This application requires BSPCFG_ENABLE_SDHC defined non-zero in user_config.h. Please recompile libraries with this option."
    #else
    #define SDCARD_COM_CHANNEL BSP_SDCARD_SDHC_CHANNEL
    #endif

#elif defined BSP_SDCARD_SPI_CHANNEL
    #define SDCARD_COM_CHANNEL BSP_SDCARD_SPI_CHANNEL

#else
    #error "SDCARD low level communication device not defined!"

#endif

#if defined BSP_SDCARD_GPIO_DETECT
    static LWGPIO_STRUCT              sd_detect;
#endif
#if defined BSP_SDCARD_GPIO_PROTECT
    static LWGPIO_STRUCT              sd_protect;
#endif

MQX_FILE_PTR sd_init( void )
{
    MQX_FILE_PTR  com_handle, sdcard_handle;
    
    uint32_t                   error_code;
    _mqx_uint                  param;
    
    /* Open low level communication device */
    com_handle = fopen(SDCARD_COM_CHANNEL, (void *)(SPI_FLAG_FULL_DUPLEX));

    if (NULL == com_handle)
    {
        USB_PRINTF("Error opening communication handle %s, check your user_config.h.\n", SDCARD_COM_CHANNEL);
        return NULL;
    }

#if defined BSP_SDCARD_GPIO_DETECT
    /* Init GPIO pins for other SD card signals */
    error_code = lwgpio_init(&sd_detect, BSP_SDCARD_GPIO_DETECT, \
                             LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with sdcard detect pin failed.\n");
        return NULL;
    }
    /*Set detect and protect pins as GPIO Function */
    lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_GPIO);
#if BSP_SDCARD_DETECT_ACTIVE_LOW
    lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_DOWN, LWGPIO_AVAL_ENABLE);
#else
    lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif
#endif

#if defined BSP_SDCARD_GPIO_PROTECT
    /* Init GPIO pins for other SD card signals */
    error_code = lwgpio_init(&sd_protect, BSP_SDCARD_GPIO_PROTECT, \
                             LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with sdcard protect pin failed.\n");
        return NULL;
    }
    /*Set detect and protect pins as GPIO Function */
    lwgpio_set_functionality(&sd_protect,BSP_SDCARD_PROTECT_MUX_GPIO);
    lwgpio_set_attribute(&sd_protect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif
    
    /* Install SD card device */
    error_code = _io_sdcard_install("sdcard:", (void *)&_bsp_sdcard0_init, com_handle);
    if ( error_code != MQX_OK )
    {
        USB_PRINTF("Error installing SD card device (0x%x)\n", error_code);
        return NULL;
    }

    while(false == sd_detect_check())
    {
        _time_delay(1000);
        USB_PRINTF(".");
    }
    
    _time_delay(200);
    /* Open the SD card device */
	sdcard_handle = fopen("sdcard:", 0);
    if ( NULL == sdcard_handle )
    {
        USB_PRINTF("Unable to open SD card device.\n");
        return NULL;
    }

    /* Set read only flag as needed */
    param = 0;
    if (sd_protect_check())
    {
        param = IO_O_RDONLY;
    }
    if (IO_OK != ioctl(sdcard_handle, IO_IOCTL_SET_FLAGS, (char *) &param))
    {
        USB_PRINTF("Setting device read only failed.\n");
        //_task_block();
    }
    
#if 0
    
    /* Install partition manager over SD card driver */
    error_code = _io_part_mgr_install(sdcard_handle, partman_name, 0);
    if (error_code != MFS_NO_ERROR)
    {
        USB_PRINTF("Error installing partition manager: %s\n", MFS_Error_text((uint32_t)error_code));
        //continue;
    }

    /* Open partition */
    partition_handle = fopen(partition_name, NULL);
    if (partition_handle != NULL)
    {
        USB_PRINTF("Installing MFS over partition...\n");
        
        /* Validate partition */
        error_code = _io_ioctl(partition_handle, IO_IOCTL_VAL_PART, NULL);
        if (error_code != MFS_NO_ERROR)
        {
            USB_PRINTF("Error validating partition: %s\n", MFS_Error_text((uint32_t)error_code));
            USB_PRINTF("Not installing MFS.\n");
            //continue;
        }

        /* Install MFS over partition */
        error_code = _io_mfs_install(partition_handle, filesystem_name, 0);
        if (error_code != MFS_NO_ERROR)
        {
            USB_PRINTF("Error initializing MFS over partition: %s\n", MFS_Error_text((uint32_t)error_code));
        }

    } else {

        USB_PRINTF("Installing MFS over SD card driver...\n");
        
        /* Install MFS over SD card driver */
        error_code = _io_mfs_install(sdcard_handle, filesystem_name, (_file_size)0);
        if (error_code != MFS_NO_ERROR)
        {
            USB_PRINTF("Error initializing MFS: %s\n", MFS_Error_text((uint32_t)error_code));
        }
    }

    /* Open file system */
    if (error_code == MFS_NO_ERROR) {
        filesystem_handle = fopen(filesystem_name, NULL);
        error_code = ferror(filesystem_handle);
        if (error_code == MFS_NOT_A_DOS_DISK)
        {
            USB_PRINTF("NOT A DOS DISK! You must format to continue.\n");
        }
        else if (error_code != MFS_NO_ERROR)
        {
            USB_PRINTF("Error opening filesystem: %s\n", MFS_Error_text((uint32_t)error_code));
            //continue;
        }

        USB_PRINTF ("SD card installed to %s\n", filesystem_name);
//        if (readonly)
//        {
//            USB_PRINTF ("SD card is locked (read only).\n");
//        }
    }
            
#endif
    return sdcard_handle;
}

bool sd_detect_check()
{
    LWGPIO_VALUE inserted = LWGPIO_VALUE_LOW;
#if defined BSP_SDCARD_GPIO_DETECT
    /* Get value of protect pin */
    inserted = lwgpio_get_value(&sd_detect);
#endif
#if BSP_SDCARD_DETECT_ACTIVE_LOW
    return ((LWGPIO_VALUE_HIGH == inserted) ? true : false);
#else
    return ((LWGPIO_VALUE_LOW == inserted) ? true : false);
#endif
}

bool sd_protect_check()
{
    LWGPIO_VALUE readonly = LWGPIO_VALUE_LOW;
#if defined BSP_SDCARD_GPIO_PROTECT
    /* Get value of protect pin */
    readonly = lwgpio_get_value(&sd_protect);
#endif
    return ((LWGPIO_VALUE_HIGH == readonly) ? true : false);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    :  sd_read_device_sectors
* Returned Value   :  error_code
* Comments  :
*     Reads consecutive sectors into given buffer
*END*---------------------------------------------------------------------*/
_mqx_uint sd_read_device_sectors
    (
    MQX_FILE_PTR             drive_ptr,
    uint32_t                 sector_number,  /*[IN] first sector to read/write from/to file system medium */
    uint32_t                 sector_count,   /*[IN] number of sectors to read/write from/to file system medium */
    uint32_t                 max_retries,    /*[IN] number of retries of the same low level operation if it fails */
    uint8_t                  *buffer_ptr,     /*[IN/OUT] address of where data is to be stored/written */
    uint32_t                 *processed       /*[OUT] number of sector successfully processed */
    )
{
    _mqx_uint   error = MQX_OK;
    uint32_t    attempts;
    int32_t     num, expect_num;
    //uint8_t *   buffer;
    
    expect_num = sector_count;
    
    if (sd_detect_check() == false)
    {
        return IO_DEVICE_DOES_NOT_EXIST;
    }
  
    fseek(drive_ptr, sector_number, IO_SEEK_SET);
    
    attempts = 0;
    
    //buffer = _mem_alloc_system_align((sector_count << SDCARD_BLOCK_SIZE_POWER), 4);
    while ( expect_num > 0 && attempts <= max_retries )
    {
        num = read(drive_ptr, buffer_ptr, expect_num);
        
        if ( num == IO_ERROR )
        {
            error = IO_ERROR;
            break;
        }
        
        if ( num > 0 )
        {
            expect_num -= num;
            buffer_ptr += num << SDCARD_BLOCK_SIZE_POWER;
            //_mem_copy(buffer, buffer_ptr, (num << SDCARD_BLOCK_SIZE_POWER));
            attempts = 0; /* there is a progress, reset attempts counter */
        }
        attempts++;
    }

    //_mem_free(buffer);
    
    if ( expect_num > 0 )
    {
        error = drive_ptr->ERROR;
    }

    if (processed)
    {
        *processed = sector_count - expect_num;
    }

    return error;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    :  sd_write_device_sectors
* Returned Value   :  error_code
* Comments  :
*     Reads or writes consecutive sectors.
*END*---------------------------------------------------------------------*/
_mqx_uint sd_write_device_sectors
    (
    MQX_FILE_PTR             drive_ptr,
    uint32_t                 sector_number,  /*[IN] first sector to read/write from/to file system medium */
    uint32_t                 sector_count,   /*[IN] number of sectors to read/write from/to file system medium */
    uint32_t                 max_retries,    /*[IN] number of retries of the same low level operation if it fails */
    uint8_t                  *buffer_ptr,     /*[IN/OUT] address of where data is to be stored/written */
    uint32_t                 *processed       /*[OUT] number of sector successfully processed */
    )
{
    uint32_t    attempts;
    int32_t     num, expect_num;
    _mqx_uint   error = MQX_OK;

    if (sd_detect_check() == false)
    {
        return IO_DEVICE_DOES_NOT_EXIST;
    }
    
    if (sd_protect_check() == true)
    {
        return IO_ERROR_WRITE_PROTECTED;
    }

    expect_num = sector_count;

    fseek(drive_ptr, sector_number, IO_SEEK_SET);

    attempts = 0;
    while ( expect_num > 0 && attempts <= max_retries)
    {
        num = write(drive_ptr, buffer_ptr, expect_num);
        
        if ( num == IO_ERROR )
        {
            error = IO_ERROR;
            break;
        }
        if ( num > 0 )
        {
            expect_num -= num;
            buffer_ptr += num << SDCARD_BLOCK_SIZE_POWER;
            attempts = 0; /* there is a progress, reset attempts counter */
        }
        attempts++;
    }

    if ( expect_num > 0 )
    {
        error = drive_ptr->ERROR;
    }

    if (processed)
    {
        *processed = sector_count - expect_num;
    }

    return error;
}

_mqx_uint sd_get_block_size(MQX_FILE_PTR drive_ptr, uint32_t * block_size_ptr)
{
    _mqx_int error = MQX_OK;
    if(NULL == block_size_ptr)
    {
        return MQX_INVALID_POINTER;
    }
    error = ioctl(drive_ptr, IO_IOCTL_GET_BLOCK_SIZE, (char *) block_size_ptr);
    
    if (IO_OK != error)
    {
        USB_PRINTF("Get device block size failed.\n");
        //_task_block();
        return error;
    }
    
    return error;
}


_mqx_uint sd_get_blocks_num(MQX_FILE_PTR drive_ptr, uint32_t * max_blocks_ptr)
{
    _mqx_int error = MQX_OK;
    if(NULL == max_blocks_ptr)
    {
        return MQX_INVALID_POINTER;
    }
    error = ioctl(drive_ptr, IO_IOCTL_GET_NUM_SECTORS, (char *) max_blocks_ptr);
    
    if (IO_OK != error)
    {
        USB_PRINTF("Get device blocks num failed.\n");
        //_task_block();
        return error;
    }
    
    return error;
}

#endif

/* EOF */
