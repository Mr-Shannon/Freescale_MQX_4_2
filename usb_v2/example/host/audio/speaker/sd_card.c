/**HEADER********************************************************************
*
* Copyright (c) 2010, 2013 -2015 Freescale Semiconductor;
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
* $FileName: sd_card.c$
* $Version :
* $Date    :
*
* Comments:
*
*   This file is an example of device drivers for the Audio host class. This example
*   demonstrates the audio transfer capability of audio host class with audio devices.
*
*END************************************************************************/
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#else
#include "derivative.h"
#include "hidef.h"
#include "mem_util.h"
#endif

#include "usb_host_hub_sm.h"
#include "usb_host_audio.h"

#include "bsp.h"
#include "fio.h"
#include "mfs.h"
#include "sh_mfs.h"
#include "sh_audio.h"
#include "shell.h"
#include "sd_card.h"
#include <lwevent.h>
#include <spi.h>
#include <part_mgr.h>

#if ! SHELLCFG_USES_MFS
#error This application requires SHELLCFG_USES_MFS defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

#if defined BSP_SDCARD_ESDHC_CHANNEL
#if ! BSPCFG_ENABLE_ESDHC
#error This application requires BSPCFG_ENABLE_ESDHC defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

#elif defined BSP_SDCARD_SDHC_CHANNEL

#if ! BSPCFG_ENABLE_SDHC
#error This application requires BSPCFG_ENABLE_SDHC defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

#endif

#if defined (BSP_SDCARD_SPI_CHANNEL)
#define SDCARD_COM_CHANNEL BSP_SDCARD_SPI_CHANNEL
#elif defined (BSP_SDCARD_ESDHC_CHANNEL)
#define SDCARD_COM_CHANNEL BSP_SDCARD_ESDHC_CHANNEL
#elif defined (BSP_SDCARD_SDHC_CHANNEL)
#define SDCARD_COM_CHANNEL BSP_SDCARD_SDHC_CHANNEL
#else
#error "SDCARD low level communication device not defined!"
#endif

/***************************************
**
** Macros
****************************************/
extern const SDCARD_INIT_STRUCT _bsp_sdcard0_init;
uint8_t                                  sd_card_state = SD_CARD_NOT_INSERTED;
uint8_t                                  file_open_count = 0;
extern LWEVENT_STRUCT                   sd_card_event;
/***************************************
**
** Global functions
****************************************/

/***************************************
**
** Local functions
****************************************/
void sdcard_task(uint32_t temp);
void shell_task(uint32_t temp);

/* Shell list */
const SHELL_COMMAND_STRUCT Shell_commands[] = {
    { "cd",        Shell_cd },
    { "del",       Shell_del },
    { "dir",       Shell_dir },
    { "help",      Shell_help },
    { "read",      Shell_read },
    { "mkdir",     Shell_mkdir },
    { "ren",       Shell_rename },
    { "rmdir",     Shell_rmdir },
    { "play",      Shell_play },
    { "pause",     Shell_pause_audio },
    { "mute",      Shell_mute },
    { "up",        Shell_increase_volume },
    { "down",      Shell_decrease_volume },
    { "?",         Shell_command_list },
    { NULL,        NULL }
};

#ifdef BSP_SDCARD_GPIO_CS
/*FUNCTION*---------------------------------------------------------------
*
* Function Name : set_CS
* Comments  : This function sets chip select signal to enable/disable memory
*
*END*----------------------------------------------------------------------*/

static void set_CS (uint32_t cs_mask, uint32_t logic_level, void *user_data)
{
    LWGPIO_STRUCT_PTR gpiofd = user_data;

    if (cs_mask & BSP_SDCARD_SPI_CS)
    {
        lwgpio_set_value(gpiofd, logic_level ? LWGPIO_VALUE_HIGH : LWGPIO_VALUE_LOW);
    }
}
#endif

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Sdcard_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void sdcard_task(uint32_t temp)
{
    (void)          temp; /* suppress 'unused variable' warning */
    bool            inserted = TRUE, readonly = FALSE, last = FALSE;
    _mqx_int        error_code;
    _mqx_uint       param;
    MQX_FILE_PTR    com_handle, sdcard_handle, filesystem_handle, partition_handle;
    char            filesystem_name[] = "a:";
    char            partman_name[] = "pm:";
    char            partition_name[] = "pm:1";
#if defined BSP_SDCARD_GPIO_DETECT
    LWGPIO_STRUCT   sd_detect;
#endif
#if defined BSP_SDCARD_GPIO_PROTECT
    LWGPIO_STRUCT   sd_protect;
#endif
#ifdef BSP_SDCARD_GPIO_CS

    LWGPIO_STRUCT   sd_cs;
    SPI_CS_CALLBACK_STRUCT callback;

#endif

    /* Open low level communication device */
    com_handle = fopen(SDCARD_COM_CHANNEL, (void *)(SPI_FLAG_FULL_DUPLEX));

    if (NULL == com_handle)
    {
        USB_PRINTF("Error opening communication handle %s, check your user_config.h.\n", SDCARD_COM_CHANNEL);
        _task_block();
    }

#ifdef BSP_SDCARD_GPIO_CS

    /* Open GPIO file for SPI CS signal emulation */
    error_code = lwgpio_init(&sd_cs, BSP_SDCARD_GPIO_CS, LWGPIO_DIR_OUTPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with associated pins failed.\n");
        _task_block();
    }
    lwgpio_set_functionality(&sd_cs,BSP_SDCARD_CS_MUX_GPIO);
    lwgpio_set_attribute(&sd_cs, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
    /* Set CS call back */
    callback.MASK = BSP_SDCARD_SPI_CS;
    callback.CALLBACK = set_CS;
    callback.USERDATA = &sd_cs;
    if (SPI_OK != ioctl (com_handle, IO_IOCTL_SPI_SET_CS_CALLBACK, &callback))
    {
        USB_PRINTF ("Setting CS call back failed.\n");
        _task_block();
    }

#endif

#if defined BSP_SDCARD_GPIO_DETECT
    /* Init GPIO pins for other SD card signals */
    error_code = lwgpio_init(&sd_detect, BSP_SDCARD_GPIO_DETECT, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with sdcard detect pin failed.\n");
        _task_block();
    }
    /*Set detect and protect pins as GPIO Function */
    lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_GPIO);
#if defined(BSP_SDCARD_DETECT_ACTIVE_LOW)
    lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_DOWN, LWGPIO_AVAL_ENABLE);
#else
    lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif
#endif

#if defined BSP_SDCARD_GPIO_PROTECT
    /* Init GPIO pins for other SD card signals */
    error_code = lwgpio_init(&sd_protect, BSP_SDCARD_GPIO_PROTECT, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with sdcard protect pin failed.\n");
        _task_block();
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
        _task_block();
    }

    for (;;)
    {
#if defined BSP_SDCARD_GPIO_DETECT
        #ifdef BSP_MPC8308RDB
        /* Set function as GPIO to detect sdcard */
        lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_GPIO);
        lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
        #endif
        #if defined(BSP_SDCARD_DETECT_ACTIVE_LOW)
            inserted = lwgpio_get_value(&sd_detect);
        #else
            inserted = !lwgpio_get_value(&sd_detect);
        #endif /* BSP_SDCARD_DETECT_ACTIVE_LOW */
#endif

#if defined BSP_SDCARD_GPIO_PROTECT
        /* Get value of protect pin */
        readonly = lwgpio_get_value(&sd_protect);
#endif
#ifdef BSP_MPC8308RDB
        /* Set function as SD_CD which indicate that card is present in Present State Register */
        lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_SD_CD);
        lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif
        if (last != inserted)
        {
            last = inserted;
            if (inserted)
            {
                sd_card_state = SD_CARD_INSERTED;
                OS_Time_delay (200);
                /* Open the device which MFS will be installed on */
                sdcard_handle = fopen("sdcard:", 0);
                if ( sdcard_handle == NULL )
                {
                    USB_PRINTF("Unable to open SD card device.\n");
                    continue;
                }

                /* Set read only flag as needed */
                param = 0;
                if (readonly)
                {
                    param = IO_O_RDONLY;
                }
                if (IO_OK != ioctl(sdcard_handle, IO_IOCTL_SET_FLAGS, (char *) &param))
                {
                    USB_PRINTF("Setting device read only failed.\n");
                    continue;
                }

                /* Install partition manager over SD card driver */
                error_code = _io_part_mgr_install(sdcard_handle, partman_name, 0);
                if (error_code != MFS_NO_ERROR)
                {
                    USB_PRINTF("Error installing partition manager: %s\n", MFS_Error_text((uint32_t)error_code));
                    continue;
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
                        continue;
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
                        continue;
                    }

                    USB_PRINTF ("SD card installed to %s\n", filesystem_name);
                    sd_card_state = SD_CARD_READY;
                    if (readonly)
                    {
                        USB_PRINTF ("SD card is locked (read only).\n");
                    }
                }
            }
            else
            {
                sd_card_state = SD_CARD_NOT_INSERTED;
                if (0 != file_open_count)
                {
                    /* Wait for all files is closed*/
                    _lwevent_wait_ticks(&sd_card_event, SD_CARD_EVENT_CLOSE, FALSE, 0);
                }
                OS_Time_delay(200);
                /* Close the filesystem */
                if ((filesystem_handle != NULL) && (MQX_OK != fclose(filesystem_handle)))
                {
                    USB_PRINTF("Error closing filesystem.\n");
                }
                filesystem_handle = NULL;

                /* Uninstall MFS  */
                error_code = _io_dev_uninstall(filesystem_name);
                if (error_code != MFS_NO_ERROR)
                {
                    USB_PRINTF("Error uninstalling filesystem.\n");
                }
                
                /* Close partition */
                if ((partition_handle != NULL) && (MQX_OK != fclose(partition_handle)))
                {
                    USB_PRINTF("Error closing partition.\n");
                }
                partition_handle = NULL;

                /* Uninstall partition manager  */
                error_code = _io_dev_uninstall(partman_name);
                if (error_code != MFS_NO_ERROR)
                {
                    USB_PRINTF("Error uninstalling partition manager.\n");
                }

                /* Close the SD card device */
                if ((sdcard_handle != NULL) && (MQX_OK != fclose(sdcard_handle)))
                {
                    USB_PRINTF("Unable to close SD card device.\n");
                }
                sdcard_handle = NULL;

                USB_PRINTF ("SD card uninstalled.\n");
            }
        }
        OS_Time_delay (1);
    }
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void shell_task(uint32_t temp)
{
    /* Run the shell on the serial port */
    Shell(Shell_commands, NULL);
    _task_block();
}
/* EOF */
