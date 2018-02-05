/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   This include file is used to provide information needed by
*   applications using the SAI I/O functions.
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include "main.h"
#include "sgtl5000.h"

#if !BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
    /*  Task number, Entry point, Stack, Pri, String,   Auto? */
    { RUN_TASK,       Run_task,       2000,  10,  "run", 0 },
    { INIT_TASK,         Init_task,         1000,   9,    "init", MQX_AUTO_START_TASK },
    { 0, 0, 0, 0, 0, 0 }
};

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Init_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void Init_task
(
    uint32_t temp
)
{

    MQX_TICK_STRUCT time;
    _mqx_int errcode = 0;
    /* Install MQX default unexpected ISR routines */
    _int_install_unexpected_isr();
    /* Setup time */
    printf("Setting up time......................");
    time.TICKS[0] = 0L;
    time.TICKS[1] = 0L;
    time.HW_TICKS = 0;
    _time_set_ticks(&time);
    printf("[OK]\n");

    /* Initialize audio codec */
    printf("Initializing audio codec.............");
    errcode = InitCodec();
    if (errcode != 0)
    {
        printf("[FAIL]\n");
        printf("  Error 0x%X\n", errcode);
    }
    else
    {
        printf("[OK]\n");
    }
    errcode = _task_create(0, RUN_TASK,0);
    printf("Creating Run task................");
    if (errcode == MQX_NULL_TASK_ID)
    {
        printf("[FAIL]\n");
        printf("  Error 0x%X.\n");
    }
    else
    {
        printf("[OK]\n");
    }
    _task_abort(MQX_NULL_TASK_ID);
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Sdcard_write_task
* Returned Value : void
* Comments       : Task that write recorded data to SD card
*
*END------------------------------------------------------------------*/
void Run_task
(
    uint32_t temp
)
{
    MQX_FILE_PTR device_ptr;
    device_ptr = fopen("sai:", "rw");
    if (device_ptr == NULL)
    {
        printf(" Open SAI failed!\n ");
        return;
    }
    /* Audio foramt settings */
    AUDIO_DATA_FORMAT audio_format;
    audio_format.ENDIAN = AUDIO_LITTLE_ENDIAN;
    audio_format.ALIGNMENT = AUDIO_ALIGNMENT_LEFT;
    audio_format.BITS = 16;
    audio_format.SIZE = 2;
    audio_format.CHANNELS = 2;
    audio_format.SAMPLE_RATE= 44100;
    uint32_t mclk_freq = audio_format.SAMPLE_RATE * 384;

     if(ioctl(device_ptr, IO_IOCTL_I2S_SET_MCLK_FREQ, &mclk_freq) != I2S_OK)
     {
         printf("  Error: Unable to setup sai driver.\n");
         fclose(device_ptr);
         return;
     }
    /* Setup audio data format in device */
    if (ioctl(device_ptr, IO_IOCTL_AUDIO_SET_TX_DATA_FORMAT, &audio_format) != I2S_OK)
    {
        printf("  Error: Input data format not supported.\n");
        fclose(device_ptr);
        return;
    }
    if (ioctl(device_ptr, IO_IOCTL_AUDIO_SET_RX_DATA_FORMAT, &audio_format) != I2S_OK)
    {
        printf("  Error: Input data format not supported.\n");
        fclose(device_ptr);
        return;
    }
    SetupCodec(device_ptr, &audio_format);

    I2S_STATISTICS_STRUCT tx_stats, rx_stats;
    ioctl(device_ptr, IO_IOCTL_I2S_GET_RX_STATISTICS, &rx_stats);
    uint8_t *Data = _mem_alloc_uncached(rx_stats.SIZE);

    /* Start Rx first. */
    ioctl(device_ptr, IO_IOCTL_I2S_START_RX, NULL);
    /* Record and play now */
    while(1)
    {
        ioctl(device_ptr, IO_IOCTL_I2S_WAIT_RX_EVENT, NULL);
        ioctl(device_ptr, IO_IOCTL_I2S_GET_RX_STATISTICS, &rx_stats);
        _mem_copy(rx_stats.OUT_BUFFER,Data,rx_stats.SIZE);
        ioctl(device_ptr, IO_IOCTL_I2S_UPDATE_RX_STATUS, &rx_stats.SIZE);

        /* From Data to Tx. */
        ioctl(device_ptr, IO_IOCTL_I2S_WAIT_TX_EVENT,NULL);
        ioctl(device_ptr, IO_IOCTL_I2S_GET_TX_STATISTICS, &tx_stats);
        _mem_copy(Data, tx_stats.IN_BUFFER, tx_stats.SIZE);
        ioctl(device_ptr, IO_IOCTL_I2S_UPDATE_TX_STATUS, &tx_stats.SIZE);
    }
    //fclose(device_ptr);   // Instruction is unreachable
}

/* EOF */

