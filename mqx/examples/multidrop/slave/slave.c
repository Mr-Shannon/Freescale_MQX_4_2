/*HEADER**********************************************************************
*
* Copyright 2013 Freescale Semiconductor, Inc.
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
*   This file contains the source for the multidrop example program.
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <fio.h>

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

#ifndef BSP_SERIAL_MULTIDROP_DEVICE
#error This application requires BSP_SERIAL_MULTIDROP_DEVICE defined. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

/* Define slave address */
#warning Please set SLAVE_ADDRESS before run application.
#define SLAVE_ADDRESS               0x00

/* Task IDs */
#define SLAVE_TASK                  10
#define MAX_LENGTH_DATA             (20)

/* Function Prototype */
extern void slave_task(uint32_t);

/* Task template */
const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
    /* Task Index,   Function,     Stack,  Priority,   Name,          Attributes,           Param,  Time Slice */
    { SLAVE_TASK,    slave_task,   1500,   9,          "slave",       MQX_AUTO_START_TASK,   0,      0 },
    { 0 }
};

/*TASK*-----------------------------------------------------
*
* Task Name    : serial_task
* Comments     :
*    This task waits for a data from master
*    Upon receiving the data is printed to serial port default
*
*END*-----------------------------------------------------*/

void slave_task
    (
        uint32_t initial_data
    )
{
    MQX_FILE_PTR   ser_dev  = NULL;
    uint32_t       param    = IO_SERIAL_PARITY_MULTI_DATA;
    uint32_t       retval, num_dat;
    uint32_t       address  = SLAVE_ADDRESS;
    char           data[MAX_LENGTH_DATA], size_fr;

    /* Open device */
    ser_dev = fopen(BSP_SERIAL_MULTIDROP_DEVICE, NULL);
    if (ser_dev == NULL)
    {   /* device could not be opened */
        printf("\nFatal Error: multidrop Device \"%s\" open fail.\n", BSP_SERIAL_MULTIDROP_DEVICE);
        printf("Please add proper configuration to user_config.h\n");
        printf("i.e #define BSPCFG_ENABLE_TTYA 1\n ");
        _task_block();
    }

    /* Set multi-drop mode for device */
    retval = ioctl(ser_dev, IO_IOCTL_SERIAL_SET_PARITY, &param);
    if (retval != MQX_OK)
    {
        printf("\nCould not configure device to MULTI-DROP mode\n");
        _task_block();
    }

    /* Set address for device */
    retval = ioctl(ser_dev, IO_IOCTL_SERIAL_SET_ADDRESS_DEVICE, (void*)&address);
    if (retval != MQX_OK)
    {
        printf("\nCould not set address for device\n");
        _task_block();
    }

    while(TRUE)
    {
        /* Read the size of data */
        if( IO_ERROR == read( ser_dev, &size_fr, 1 ) )
        {
            printf("\nCould not read data from master \n");
            _task_block();
        }

        /* Read block data */
        do
        {
            num_dat = read(ser_dev, (&data + num_dat), size_fr);
            size_fr -= num_dat;
        } while (size_fr > 0);  /* Loop until all bytes are received */

        /* Print received data on terminal */
        printf("\nReceive data : %s\n", data);
    }
}

/* EOF */
