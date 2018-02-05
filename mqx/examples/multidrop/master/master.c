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

#define MAX_LENGTH_DATA             (20)
#define SLAVE_NUM                   (2)


/* Task IDs */
#define MASTER_TASK                 (5)
#define START_ADDRESS               (0x00)

extern void master_task(uint32_t);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
    /* Task Index,   Function,    Stack,  Priority,  Name,      Attributes,           Param,  Time Slice */
    { MASTER_TASK,   master_task, 1500,   8,         "master",  MQX_AUTO_START_TASK,  0,      0 },
    { 0 }
};

/*TASK*-----------------------------------------------------
*
* Task Name    : master_task
* Comments     :
*    This task transmit data to slave use multi-drop mode
*
*END*-----------------------------------------------------*/
void master_task
    (
        uint32_t initial_data
    )
{
    MQX_FILE_PTR ser_dev   = NULL;
    uint32_t set_data      = IO_SERIAL_PARITY_MULTI_DATA;
    uint32_t set_address   = IO_SERIAL_PARITY_MULTI_ADDRESS;
    uint32_t retval        = 0;
    uint32_t i             = 0;
    char     address       = START_ADDRESS;
    char     length, str[MAX_LENGTH_DATA];

    /* Open device */
    ser_dev = fopen(BSP_SERIAL_MULTIDROP_DEVICE, NULL);
    if (ser_dev == NULL)
    {
        /* device could not be opened */
        printf("\nFatal Error: multidrop Device \"%s\" open fail.\n", BSP_SERIAL_MULTIDROP_DEVICE);
        printf("Please add proper configuration to user_config.h\n");
        printf("i.e #define BSPCFG_ENABLE_TTYA 1\n ");
        _task_block();
    }
    while (TRUE)
    {
        /* Set master send address */
        retval = ioctl(ser_dev, IO_IOCTL_SERIAL_SET_PARITY, &set_address);
        if (retval != MQX_OK)
        {
            printf("Could not configure device to MULTI-DROP MODE for send address\n");
            _task_block();
        }
        /* Send address */
        if( write(ser_dev, &address, 1) != 1 )
        {
            printf("\nCould not send address\n");
            _task_block();
        }

        /* Set master send data */
        retval = ioctl(ser_dev, IO_IOCTL_SERIAL_SET_PARITY, &set_data);
        if (retval != MQX_OK)
        {
            printf("Could not configure device to MULTI-DROP MODE for send data\n");
            _task_block();
        }

        printf("Sending to slave %d ...\n", address);

        /* Prepare data to send slave */
        sprintf(str, "%s%d", "Hello slave ", address);
        length = sizeof(str);

        /* Send data size - 1 byte */
        if(write(ser_dev, &length,1) != 1)
        {
            printf("\nCould not send sizeof(data) to slave\n");
            _task_block();
        }

        /*
         * Send data characters
         */
        if(write(ser_dev, (char*)&str, length) != length)
        {
            printf("\nCould not send data to slave\n");
            _task_block();
        }

        /*
         * Next slave address
         */
        if (++address == SLAVE_NUM)
        {
            address = START_ADDRESS;
        }
        _time_delay(100);
    }
}
/* EOF */
