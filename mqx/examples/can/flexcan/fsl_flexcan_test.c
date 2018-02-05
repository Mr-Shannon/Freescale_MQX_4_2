/*HEADER**********************************************************************
*
* Copyright 2008-2014 Freescale Semiconductor, Inc.
* Copyright 1989-2008 ARC International
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
*   This file contains the source for the FlexCAN example program.
*
*   NOTE: This is a two node test. It requires the software to be loaded
*   onto two boards, one board programmed as NODE 1 and the other programmed
*   as NODE 2.  A properly terminated CAN cable (120 ohms on either end) is
*   used to connect both boards together.  When running, the boards will
*   exchange a CAN message once per second, and the following output
*   should be repetitively displayed (where <x> and <y> increment):
*
*       Data transmit: <x>
*       FLEXCAN tx update message. result: 0x0
*       Received data: <y>
*       ID is: 0x321
*       DLC is: 0x1
*
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <fsl_flexcan_driver.h>

// Set NODE to 1 or 2 depending on which endpoint you are running. See notes in fsl_flexcan_test.c
#define NODE 1


#define MY_EVENT_GROUP 123

/* Task define */
#define MAIN_TASK   1
#define TX_TASK     2
#define RX_TASK     3

/* Tasks */
void Main_Task(uint32_t parameter);
void Tx_Task(uint32_t parameter);
void Rx_Task(uint32_t parameter);

/* Global variables */
uint32_t TX_identifier;
uint32_t RX_identifier;
uint32_t TX_remote_identifier;
uint32_t RX_remote_identifier;
uint32_t TX_mailbox_num;
uint32_t RX_mailbox_num;
uint32_t TX_remote_mailbox_num;
uint32_t RX_remote_mailbox_num;
flexcan_id_table_t id_table;
flexcan_mb_t rx_fifo;
flexcan_mb_t rx_mb;
uint8_t instance;
static const flexcan_config_t flexcan_data = {
/* The number of Message Buffers needed        */ 16,
/* The maximum number of Message Buffers       */ 16,
/* The number of total RXIMR registers         */ kFlexCanTotalRxImrNumber,
/* The number of RX FIFO ID filters needed     */ kFlexCanRxFifoIDFilters_8,
/* RX fifo needed?                             */ FALSE,
/* RX message buffer needed?                   */ TRUE
};


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

#ifndef BSP_CAN_DEVICE
    #error This application requires BSP_CAN_DEVICE defined non-zero in [board name].h. Please recompile BSP with this option.
#endif

/* Task template list */
TASK_TEMPLATE_STRUCT MQX_template_list[] = {
    { MAIN_TASK, Main_Task, 1000L, 8L, "Main task", MQX_AUTO_START_TASK},
    { TX_TASK, Tx_Task, 1000L, 7L, "TX task", 0, 0, 0},
    { RX_TASK, Rx_Task, 1000L, 7L, "RX task", 0, 0, 0},
    { 0L, 0L, 0L, 0L, 0L, 0L }
};

/*TASK*-----------------------------------------------------------
*
* Task Name : Main_Task
* Comments :
*
*
*END*-----------------------------------------------------------*/
void Main_Task(uint32_t parameter)
{
    _task_id     created_task;
    uint32_t result;
    uint32_t rx_fifo_id[8];
    uint32_t i;
    uint32_t bitrate_get = 0;

    instance = BSP_CAN_DEVICE;

    printf("\n*********FLEXCAN TEST PROGRAM.*********");
    printf("\n   Message format: Standard (11 bit id)");
    printf("\n   Message buffer 9 used for Rx.");
    printf("\n   Message buffer 13 used for Tx.");
    printf("\n   Interrupt Mode: Enabled");
    printf("\n   Operation Mode: TX and RX --> Normal");
    printf("\n***************************************\n");

    printf("\n\nNODE is %d\n", NODE);

    id_table.is_extended_mb = 0;
    id_table.is_remote_mb = 0;
    rx_fifo_id[0] = 0x666;
    rx_fifo_id[1] = 0x667;
    rx_fifo_id[2] = 0x676;
    rx_fifo_id[3] = 0x66E;
    rx_fifo_id[4] = 0x66F;
    for (i = 5; i < 8; i++)
        rx_fifo_id[i] = 0x6E6;
    id_table.id_filter = rx_fifo_id;

    /* Select mailbox number */
    RX_mailbox_num = 9;
    TX_mailbox_num = 13;
    RX_remote_mailbox_num = 10;
    TX_remote_mailbox_num = 11;

#if NODE==1
    RX_identifier = 0x123;
    TX_identifier = 0x321;
    RX_remote_identifier = 0x0F0;
    TX_remote_identifier = 0x00F;
#else
    RX_identifier = 0x321;
    TX_identifier = 0x123;
    RX_remote_identifier = 0x00F;
    TX_remote_identifier = 0x0F0;
#endif

    result = flexcan_init(instance, &flexcan_data, FALSE);
    if (result)
        printf("\nFLEXCAN initilization. result: 0x%lx", result);

    result = flexcan_set_bitrate(instance, 1000000);
    if (result)
        printf("\nFLEXCAN set bitrate. result: 0x%lx", result);

    result = flexcan_get_bitrate(instance, &bitrate_get);
    if (result)
    {
        printf("\r\nFLEXCAN get bitrate failed. result: 0x%lx", result);
    }
    else
    {
        printf("\r\nFLEXCAN get bitrate: %d Hz", bitrate_get);
    }

    result = flexcan_set_mask_type(instance, kFlexCanRxMask_Global);
    if (result)
        printf("\nFLEXCAN set mask type. result: 0x%lx", result);

    if (flexcan_data.is_rx_fifo_needed)
    {
        result = flexcan_set_rx_fifo_global_mask(instance, kFlexCanMbId_Std, 0x7FF);
        if (result)
            printf("\nFLEXCAN set rx fifo global mask. result: 0x%lx", result);
    }

    if (flexcan_data.is_rx_mb_needed)
    {
        result = flexcan_set_rx_mb_global_mask(instance, kFlexCanMbId_Std, 0x123);
        if (result)
            printf("\nFLEXCAN set rx MB global mask. result: 0x%lx", result);
    }

    created_task = _task_create(0, RX_TASK, 0);
    if (created_task == MQX_NULL_TASK_ID)
    {
        printf("\nRx task: task creation failed.");
    }

    created_task = _task_create(0, TX_TASK, 0);
    if (created_task == MQX_NULL_TASK_ID)
    {
        printf("\nTx task: task creation failed.");
    }

    // start the ping pong
    while(1){}
}

/*TASK*-----------------------------------------------------------
*
* Task Name : Tx_Task
* Comments :
*
*
*END*-----------------------------------------------------------*/
void Tx_Task(uint32_t parameter)
{
    uint8_t   data;
    uint32_t result;

#if NODE==1
    data = 0x0;
#else
    data = 0xF;
#endif

    //Standard ID
    flexcan_mb_code_status_tx_t tx_cs1;
    tx_cs1.code = kFlexCanTX_Data;
    tx_cs1.msg_id_type = kFlexCanMbId_Std;
    tx_cs1.data_length = 1;
    tx_cs1.substitute_remote = 0;
    tx_cs1.remote_transmission = 0;
    tx_cs1.local_priority_enable = 0;
    tx_cs1.local_priority_val = 0;

    printf("\nFlexCAN send config");
    result = flexcan_tx_mb_config(instance, &flexcan_data, TX_mailbox_num, &tx_cs1, TX_identifier);
    if (result)
        printf("\nTransmit MB config error. Error Code: 0x%lx", result);
    else
    {
        while(1)
        {
            _time_delay(1000);

            data++;

            result = flexcan_send(instance, &flexcan_data, TX_mailbox_num, &tx_cs1, TX_identifier,
                                  1, &data);
            if (result)
                printf("\nTransmit error. Error Code: 0x%lx", result);
            else
            {
                printf("\nData transmit: 0x%02x", data);
            }
        }
    }
}

/*TASK*-----------------------------------------------------------
*
* Task Name : Rx_Task
* Comments :
*
*
*END*-----------------------------------------------------------*/
void Rx_Task(uint32_t parameter)
{
    uint32_t result, temp;
    bool is_rx_mb_data = FALSE;
    bool is_rx_fifo_data = FALSE;
    flexcan_mb_code_status_rx_t rx_cs1;
    rx_cs1.code = kFlexCanRX_Ranswer;
    rx_cs1.msg_id_type = kFlexCanMbId_Std;
    rx_cs1.data_length = 1;
    rx_cs1.substitute_remote = 0;
    rx_cs1.remote_transmission = 0;
    rx_cs1.local_priority_enable = 0;
    rx_cs1.local_priority_val = 0;

    printf("\nFlexCAN receive config");

    if (flexcan_data.is_rx_fifo_needed)
    {
        // Configure RX FIFO fields
        result = flexcan_rx_fifo_config(instance, &flexcan_data, kFlexCanRxFifoIdElementFormat_A,
                                        &id_table);
        if (result)
            return;
    }

    if (flexcan_data.is_rx_mb_needed)
    {
        // Configure RX MB fields
        result = flexcan_rx_mb_config(instance, &flexcan_data, RX_mailbox_num, &rx_cs1,
                                      RX_identifier);
        if (result)
            return;
    }

    // Start receiving data
    while(1)
    {
        is_rx_mb_data = FALSE;
        is_rx_fifo_data = FALSE;
        result = (flexcan_start_receive(instance, &flexcan_data, RX_mailbox_num, RX_identifier, 1,
                                  &is_rx_mb_data, &is_rx_fifo_data, &rx_mb, &rx_fifo));
        if (result)
            printf("\nFLEXCAN receive error. Error code: 0x%lx", result);
        else
        {
            if (is_rx_mb_data)
            {
                temp = ((rx_mb.cs) >> 16) & 0xF;
                printf("\nDLC=%d, mb_idx=%d", temp, RX_mailbox_num);
                printf("\nRX MB data: 0x");
                for (result = 0; result < temp; result++)
                    printf ("%02x ", rx_mb.data[result]);

                printf("\nID: 0x%x", rx_mb.msg_id);
            }

            if (is_rx_fifo_data)
            {
                temp = ((rx_fifo.cs) >> 16) & 0xF;
                printf("\nDLC=%d", temp);
                printf("\nRX FIFO data: 0x");
                for (result = 0; result < temp; result++)
                    printf ("%02x ", rx_fifo.data[result]);

                printf("\nID: 0x%x", rx_fifo.msg_id);
            }
        }
    }
}

/* EOF */
