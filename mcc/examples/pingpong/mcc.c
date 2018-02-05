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
*   This file contains the source for one of the MCC pingpong examples.
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "mcc.h"
#include "mcc_config.h"
#include "mcc_common.h"
#include "mcc_api.h"
#include "mcc_mqx.h"
#include <string.h>

#include <core_mutex.h>

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

/* Application-specific settings */
/* 1: Blocking mode (task is blocked when no new message is available)
 * 0: Non-blocking mode (task is waiting for a new message in a spin loop) */
#define MCC_APP_BLOCKING_MODE  (1)

/* 1: Non-copy-send mode (mcc_get_buffer and mcc_send_nocopy functions used for message sending)
 * 0: Send with copy mode (mcc_send functions used for message sending) */
#define MCC_APP_NON_COPY_SEND_MODE  (1)

/* 1: Non-copy-recv mode (mcc_recv_nocopy function used for message receiving)
 * 0: Recv with copy mode (mcc_recv function used for message receiving) */
#define MCC_APP_NON_COPY_RECV_MODE  (1)

extern void main_task(uint32_t);
extern void responder_task(uint32_t);

#if PSP_MQX_CPU_IS_VYBRID_A5
const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
   /* Task Index,    Function,       Stack,  Priority, Name,        Attributes,          Param, Time Slice */
    { MAIN_TTN,      main_task,      2000,   9,        "Main",      MQX_AUTO_START_TASK, MCC_MQX_NODE_A5,   0 },
    { 0 }
};
#else
TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
   /* Task Index,    Function,       Stack,  Priority,  Name,        Attributes,          Param, Time Slice */
    { RESPONDER_TTN, responder_task, 2000,   9,         "Responder", MQX_AUTO_START_TASK, MCC_MQX_NODE_M4,  0 },
    { 0 }
};
#endif

MCC_ENDPOINT    mqx_endpoint_a5 = {0,MCC_MQX_NODE_A5,MCC_MQX_SENDER_PORT};
MCC_ENDPOINT    mqx_endpoint_m4 = {1,MCC_MQX_NODE_M4,MCC_MQX_RESPONDER_PORT};

/*TASK*----------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*     This task creates a message pool and a message queue then
*     sends a message to a queue on the second CPU.
*     It waits for a return message, validating the message before
*     sending a new message.
*END*-----------------------------------------------------------*/

void main_task(uint32_t node_num)
{
    THE_MESSAGE     msg;
    MCC_MEM_SIZE    num_of_received_bytes, mcc_buffer_size;
    CORE_MUTEX_PTR  coremutex_app_ptr;
    MCC_INFO_STRUCT mcc_info;
    int             ret_value;
    MCC_ENDPOINT    mqx_endpoint_sender = {0,0,0};
#if !MCC_APP_BLOCKING_MODE
    unsigned int    num_available_msgs;
#endif
#if MCC_APP_NON_COPY_SEND_MODE
    void           *msg_buffer_s_ptr = null;
#endif
#if MCC_APP_NON_COPY_RECV_MODE
    void           *msg_buffer_r_ptr = null;
#endif

    /* create core mutex used in the app. for accessing the serial console */
    coremutex_app_ptr = _core_mutex_create( 0, MCC_PRINTF_SEMAPHORE_NUMBER, MQX_TASK_QUEUE_FIFO );

/* In case of the MCC_APP_NON_COPY_SEND_MODE check that the size of data structure 
   to be sent does not exceed the MCC_ATTR_BUFFER_SIZE_IN_BYTES size */
#if MCC_APP_NON_COPY_SEND_MODE
    if(sizeof(THE_MESSAGE) > MCC_ATTR_BUFFER_SIZE_IN_BYTES) {
        _core_mutex_lock(coremutex_app_ptr);
        printf("\nError, data to be sent exceeds the MCC_ATTR_BUFFER_SIZE_IN_BYTES size");
        _core_mutex_unlock(coremutex_app_ptr);
        _task_block();
    }
#endif

    msg.DATA = 1;
    ret_value = mcc_initialize(node_num);
    if(MCC_SUCCESS != ret_value) {
        _core_mutex_lock(coremutex_app_ptr);
        printf("\n\n\nError, attempting to initialize the MCC library failed! Application is stopped now. Error code = %i\n", ret_value);
        _core_mutex_unlock(coremutex_app_ptr);
        mcc_destroy(node_num);
        _task_block();
    }
    ret_value = mcc_get_info(node_num, &mcc_info);

    ret_value = mcc_create_endpoint(&mqx_endpoint_a5, MCC_MQX_SENDER_PORT);

    _core_mutex_lock(coremutex_app_ptr);
    printf("\n\n\nMain task started, MCC version is %s\n", mcc_info.version_string);
    _core_mutex_unlock(coremutex_app_ptr);

    while (1) {
#if MCC_APP_NON_COPY_SEND_MODE
        ret_value = mcc_get_buffer((void**)&msg_buffer_s_ptr, &mcc_buffer_size, 0xffffffff);
        if(MCC_SUCCESS == ret_value) {
            if(mcc_buffer_size < sizeof(THE_MESSAGE)) {
                _core_mutex_lock(coremutex_app_ptr);
                printf("\nError, the MCC buffer size is smaller than the amount of data to be sent");
                _core_mutex_unlock(coremutex_app_ptr);
            } else {
                mcc_get_semaphore();
                MCC_DCACHE_INVALIDATE_MLINES((void*)msg_buffer_s_ptr, sizeof(THE_MESSAGE));
                _mem_copy((void *)&msg, msg_buffer_s_ptr, (_mem_size)sizeof(THE_MESSAGE));
                MCC_DCACHE_FLUSH_MLINES((void*)msg_buffer_s_ptr, sizeof(THE_MESSAGE));
                mcc_release_semaphore();
                while(MCC_ERR_ENDPOINT == mcc_send_nocopy(&mqx_endpoint_a5, &mqx_endpoint_m4, msg_buffer_s_ptr, sizeof(THE_MESSAGE))) {
                    _time_delay(1);
                }
            }
        } else {
            _core_mutex_lock(coremutex_app_ptr);
            printf("\nError, mcc_get_buffer() function call failed");
            _core_mutex_unlock(coremutex_app_ptr);
        }
#else
        /* wait until the remote endpoint is created by the other core */
        while(MCC_ERR_ENDPOINT == mcc_send(&mqx_endpoint_a5, &mqx_endpoint_m4, &msg, sizeof(THE_MESSAGE), 0xffffffff)) {
            _time_delay(1);
        }
#endif
#if MCC_APP_BLOCKING_MODE
#if MCC_APP_NON_COPY_RECV_MODE
        ret_value = mcc_recv_nocopy(&mqx_endpoint_sender, &mqx_endpoint_a5, (void**)&msg_buffer_r_ptr, &num_of_received_bytes, 0xffffffff);
        if(MCC_SUCCESS == ret_value) {
            _mem_copy(msg_buffer_r_ptr, (void *)&msg, (_mem_size)num_of_received_bytes);
            mcc_free_buffer(msg_buffer_r_ptr);
        }
#else
        ret_value = mcc_recv(&mqx_endpoint_sender, &mqx_endpoint_a5, &msg, sizeof(THE_MESSAGE), &num_of_received_bytes, 0xffffffff);
#endif /* MCC_APP_NON_COPY_RECV_MODE */
#else
        mcc_msgs_available(&mqx_endpoint_a5, &num_available_msgs);
        while(num_available_msgs==0) {
        	mcc_msgs_available(&mqx_endpoint_a5, &num_available_msgs);
        }
#if MCC_APP_NON_COPY_RECV_MODE
        ret_value = mcc_recv_nocopy(&mqx_endpoint_sender, &mqx_endpoint_a5, (void**)&msg_buffer_r_ptr, &num_of_received_bytes, 0);
        if(MCC_SUCCESS == ret_value) {
            _mem_copy(msg_buffer_r_ptr, (void *)&msg, (_mem_size)num_of_received_bytes);
            mcc_free_buffer(msg_buffer_r_ptr);
        }
#else
        ret_value = mcc_recv(&mqx_endpoint_sender, &mqx_endpoint_a5, &msg, sizeof(THE_MESSAGE), &num_of_received_bytes, 0);
#endif /* MCC_APP_NON_COPY_RECV_MODE */
#endif /* MCC_APP_BLOCKING_MODE */
        if(MCC_SUCCESS != ret_value) {
            _core_mutex_lock(coremutex_app_ptr);
            printf("Main task receive error: %i\n", ret_value);
            _core_mutex_unlock(coremutex_app_ptr);
        } else {
            _core_mutex_lock(coremutex_app_ptr);
            printf("Main task received a msg from [%i,%i,%i] endpoint\n", mqx_endpoint_sender.core, mqx_endpoint_sender.node, mqx_endpoint_sender.port);
            printf("Message: Size=%x, DATA = %x\n", num_of_received_bytes, msg.DATA);
            _core_mutex_unlock(coremutex_app_ptr);
            msg.DATA++;
        }
    }
}

/*TASK*----------------------------------------------------------
*
* Task Name : responder_task
* Comments  :
*     This task creates a message queue then waits for a message.
*     Upon receiving the message the data is incremented before
*     the message is returned to the sender.
*END*-----------------------------------------------------------*/

void responder_task(uint32_t node_num)
{
    THE_MESSAGE     msg;
    MCC_MEM_SIZE    num_of_received_bytes, mcc_buffer_size;
    CORE_MUTEX_PTR  coremutex_app_ptr;
    MCC_INFO_STRUCT mcc_info;
    int             ret_value;
    MCC_ENDPOINT    mqx_endpoint_sender = {0,0,0};
#if !MCC_APP_BLOCKING_MODE
    unsigned int    num_available_msgs;
#endif
#if MCC_APP_NON_COPY_SEND_MODE
    void           *msg_buffer_s_ptr = null;
#endif
#if MCC_APP_NON_COPY_RECV_MODE
    void           *msg_buffer_r_ptr = null;
#endif

#if MQX_CPU == PSP_CPU_IMX6SX_M4
    char control_char;

    /*
     * Wait For A9 Side Become Ready
     */
    printf("\n\n\n\n***** MCC PINGPANG EXAMPLE *****\n");
    printf("Please wait :\n");
    printf("    1) A9 peer is ready\n");
    printf("Then press \"S\" to start the demo\n");
    printf("********************************\n");

    while (TRUE) {
        printf("\nPress \"S\" to start the demo : ");
        control_char = getchar();
        if ((control_char == 's') || (control_char == 'S')) {
            break;
        }
    }
#endif

    /* create core mutex used in the app. for accessing the serial console */
    coremutex_app_ptr = _core_mutex_create( 0, MCC_PRINTF_SEMAPHORE_NUMBER, MQX_TASK_QUEUE_FIFO );

/* In case of the MCC_APP_NON_COPY_SEND_MODE check that the size of data structure 
   to be sent does not exceed the MCC_ATTR_BUFFER_SIZE_IN_BYTES size */
#if MCC_APP_NON_COPY_SEND_MODE
    if(sizeof(THE_MESSAGE) > MCC_ATTR_BUFFER_SIZE_IN_BYTES) {
        _core_mutex_lock(coremutex_app_ptr);
        printf("\nError, data to be sent exceeds the MCC_ATTR_BUFFER_SIZE_IN_BYTES size");
        _core_mutex_unlock(coremutex_app_ptr);
        _task_block();
    }
#endif

    msg.DATA = 1;
    ret_value = mcc_initialize(node_num);
    if(MCC_SUCCESS != ret_value) {
        _core_mutex_lock(coremutex_app_ptr);
        printf("\n\n\nError, attempting to initialize the MCC library failed! Application is stopped now. Error code = %i\n", ret_value);
        _core_mutex_unlock(coremutex_app_ptr);
        mcc_destroy(node_num);
        _task_block();
    }

    ret_value = mcc_get_info(node_num, &mcc_info);

    ret_value = mcc_create_endpoint(&mqx_endpoint_m4, MCC_MQX_RESPONDER_PORT);

    _core_mutex_lock(coremutex_app_ptr);
    printf("\n\n\nResponder task started, MCC version is %s\n", mcc_info.version_string);
    _core_mutex_unlock(coremutex_app_ptr);
    while (TRUE) {
#if MCC_APP_BLOCKING_MODE
#if MCC_APP_NON_COPY_RECV_MODE
        ret_value = mcc_recv_nocopy(&mqx_endpoint_sender, &mqx_endpoint_m4, (void**)&msg_buffer_r_ptr, &num_of_received_bytes, 0xffffffff);
        if(MCC_SUCCESS == ret_value) {
            _mem_copy(msg_buffer_r_ptr, (void *)&msg, (_mem_size)num_of_received_bytes);
            mcc_free_buffer(msg_buffer_r_ptr);
        }
#else
        ret_value = mcc_recv(&mqx_endpoint_sender, &mqx_endpoint_m4, &msg, sizeof(THE_MESSAGE), &num_of_received_bytes, 0xffffffff);
#endif /* MCC_APP_NON_COPY_RECV_MODE */
#else
        mcc_msgs_available(&mqx_endpoint_m4, &num_available_msgs);
        while(num_available_msgs==0) {
            mcc_msgs_available(&mqx_endpoint_m4, &num_available_msgs);
        }
#if MCC_APP_NON_COPY_RECV_MODE
        ret_value = mcc_recv_nocopy(&mqx_endpoint_sender, &mqx_endpoint_m4, (void**)&msg_buffer_r_ptr, &num_of_received_bytes, 0);
        if(MCC_SUCCESS == ret_value) {
            _mem_copy(msg_buffer_r_ptr, (void *)&msg, (_mem_size)num_of_received_bytes);
            mcc_free_buffer(msg_buffer_r_ptr);
        }
#else
        ret_value = mcc_recv(&mqx_endpoint_sender, &mqx_endpoint_m4, &msg, sizeof(THE_MESSAGE), &num_of_received_bytes, 0);
#endif /* MCC_APP_NON_COPY_RECV_MODE */
#endif /* MCC_APP_BLOCKING_MODE */
        if(MCC_SUCCESS != ret_value) {
            _core_mutex_lock(coremutex_app_ptr);
            printf("Responder task receive error: %i\n", ret_value);
            _core_mutex_unlock(coremutex_app_ptr);
        } else {
            _core_mutex_lock(coremutex_app_ptr);
            printf("Responder task received a msg from [%i,%i,%i] endpoint\n", mqx_endpoint_sender.core, mqx_endpoint_sender.node, mqx_endpoint_sender.port);
            printf("Message: Size=%x, DATA = %x\n", num_of_received_bytes, msg.DATA);
            _core_mutex_unlock(coremutex_app_ptr);
            msg.DATA++;
#if MCC_APP_NON_COPY_SEND_MODE
            ret_value = mcc_get_buffer((void**)&msg_buffer_s_ptr, &mcc_buffer_size, 0xffffffff);
            if(MCC_SUCCESS == ret_value) {
                if(mcc_buffer_size < sizeof(THE_MESSAGE)) {
                    _core_mutex_lock(coremutex_app_ptr);
                    printf("\nError, the MCC buffer size is smaller than the amount of data to be sent");
                    _core_mutex_unlock(coremutex_app_ptr);
                } else {
                    mcc_get_semaphore();
                    MCC_DCACHE_INVALIDATE_MLINES((void*)msg_buffer_s_ptr, sizeof(THE_MESSAGE));
                    _mem_copy((void *)&msg, msg_buffer_s_ptr, (_mem_size)sizeof(THE_MESSAGE));
                    MCC_DCACHE_FLUSH_MLINES((void*)msg_buffer_s_ptr, sizeof(THE_MESSAGE));
                    mcc_release_semaphore();
                    ret_value = mcc_send_nocopy(&mqx_endpoint_m4, &mqx_endpoint_sender, msg_buffer_s_ptr, sizeof(THE_MESSAGE));
                    if(MCC_SUCCESS != ret_value) {
                        _core_mutex_lock(coremutex_app_ptr);
                        printf("\nError, sending the message using the nocopy send function failed");
                        _core_mutex_unlock(coremutex_app_ptr);
                    }
                }
            } else {
                _core_mutex_lock(coremutex_app_ptr);
                printf("\nError, mcc_get_buffer() function call failed");
                _core_mutex_unlock(coremutex_app_ptr);
                mcc_destroy(node_num);
                _task_block();
            }
#else
            ret_value = mcc_send(&mqx_endpoint_m4, &mqx_endpoint_sender, &msg, sizeof(THE_MESSAGE), 0xffffffff);
            if(MCC_SUCCESS != ret_value) {
                _core_mutex_lock(coremutex_app_ptr);
                printf("\nError, sending the message using the send function failed");
                _core_mutex_unlock(coremutex_app_ptr);
            }
#endif
        }
    }
}
