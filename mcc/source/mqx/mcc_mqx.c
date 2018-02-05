/*
 * This file contains MQX-specific MCC library functions
 *
 * Copyright (C) 2014 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause License for this file can be found in the COPYING.BSD file
 * included with this distribution or at
 * http://opensource.org/licenses/BSD-3-Clause
 */

#include "mcc_config.h"
#include "mcc_common.h"
#include "mcc_mqx.h"
#if PSP_MQX_CPU_IS_VYBRID
#include "mcc_vf600.h"
#elif PSP_MQX_CPU_IS_IMX6SX
#include "mcc_imx6sx.h"
#endif

/* Global variables */
CORE_MUTEX_PTR cm_ptr;
LWEVENT_STRUCT lwevent_buffer_queued[MCC_MQX_LWEVENT_COMPONENTS_COUNT];
LWEVENT_STRUCT lwevent_buffer_freed;
static unsigned int cpu_to_cpu_isr_vector = MCC_VECTOR_NUMBER_INVALID; 
MCC_BOOKEEPING_STRUCT * bookeeping_data;
/*!
 * \brief This function is the CPU-to-CPU interrupt handler.
 *
 * Each core can interrupt the other. There are two logical signals:
 * \n - Receive data available for (Node,Port) - signaled when a buffer is queued to a Receive Data Queue.
 * \n - Buffer available - signaled when a buffer is queued to the Free Buffer Queue.
 * \n It is possible that several signals can occur while one interrupt is being processed.
 *  Therefore, a Receive Signal Queue of received signals is also required - one for each core.
 *  The interrupting core queues to the tail and the interrupted core pulls from the head.
 *  For a circular file, no semaphore is required since only the sender modifies the tail and only the receiver modifies the head.
 *
 * \param[in] param Pointer to data being passed to the ISR.
 */
static void mcc_cpu_to_cpu_isr(void *param)
{
    MCC_SIGNAL serviced_signal;

    /* Try to lock the core mutex. If successfully locked, perform mcc_dequeue_signal(), release the gate and 
       finally clear the interrupt flag. If trylock fails (HW semaphore already locked by another core), 
       do not clear the interrupt flag - this way the CPU-to-CPU isr is re-issued again until 
       the HW semaphore is locked. Higher priority ISRs will be serviced while issued at the time 
       we are waiting for the unlocked gate. To prevent trylog failure due to core mutex currently locked by our own core
       (a task), the cpu-to-cpu isr is temporarily disabled when mcc_get_semaphore() is called and re-enabled again
       when mcc_release_semaphore() is issued. */
    if(COREMUTEX_LOCKED == _core_mutex_trylock(cm_ptr)) {
        while(MCC_SUCCESS == mcc_dequeue_signal(MCC_CORE_NUMBER, &serviced_signal)) {
            if((serviced_signal.type == BUFFER_QUEUED) &&
               (serviced_signal.destination.core == MCC_CORE_NUMBER)) {
                /* Unblock receiver, in case of asynchronous communication */
                _lwevent_set(&lwevent_buffer_queued[serviced_signal.destination.port / MCC_MQX_LWEVENT_GROUP_SIZE], 1<<(serviced_signal.destination.port % MCC_MQX_LWEVENT_GROUP_SIZE));
            }
            else if(serviced_signal.type == BUFFER_FREED) {
                /* Unblock sender, in case of asynchronous communication */
                _lwevent_set(&lwevent_buffer_freed, 1);
            }
        }
        
        /* Unlocks the core mutex */ 
        _core_mutex_unlock(cm_ptr);
        
        /* Clear the interrupt flag */
        mcc_clear_cpu_to_cpu_interrupt(MCC_CORE_NUMBER);
    }
}

/*!
 * \brief This function initializes the hw semaphore (SEMA4).
 *
 * Calls MQX core-mutex driver to create a core mutex.
 *
 * \param[in] sem_num SEMA4 gate number.
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_SEMAPHORE (failure)
 *
 * \see mcc_deinit_semaphore
 */
int mcc_init_semaphore(unsigned int sem_num)
{
    /* Create a core mutex */
    cm_ptr = _core_mutex_create(0, sem_num, MQX_TASK_QUEUE_FIFO);

    if(NULL == cm_ptr)
        return MCC_ERR_SEMAPHORE;
    else
        return MCC_SUCCESS;
}

/*!
 * \brief This function de-initializes the hw semaphore (SEMA4).
 *
 * Calls MQX core-mutex driver to destroy a core mutex.
 *
 * \param[in] sem_num SEMA4 gate number.
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_SEMAPHORE (failure)
 *
 * \see mcc_init_semaphore
 */
int mcc_deinit_semaphore(unsigned int sem_num)
{
    /* Destroy the core mutex */
    if(COREMUTEX_OK == _core_mutex_destroy(cm_ptr))
        return MCC_SUCCESS;
    else
        return MCC_ERR_SEMAPHORE;
}

/*!
 * \brief This function locks the specified core mutex.
 *
 * Calls MQX core-mutex driver to lock the core mutex.
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_SEMAPHORE (failure)
 *
 * \see mcc_release_semaphore
 *
 */
int mcc_get_semaphore(void)
{
    _bsp_int_disable(cpu_to_cpu_isr_vector);
    if(COREMUTEX_OK == _core_mutex_lock(cm_ptr)) {
        return MCC_SUCCESS;
    }
    else {
        _bsp_int_enable(cpu_to_cpu_isr_vector);
        return MCC_ERR_SEMAPHORE;
    }
}

/*!
 * \brief This function unlocks the specified core mutex.
 *
 * Calls MQX core-mutex driver to unlock the core mutex.
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_SEMAPHORE (failure)
 *
 * \see mcc_init_semaphore
 *
 */
int mcc_release_semaphore(void)
{
    if(COREMUTEX_OK == _core_mutex_unlock(cm_ptr)) {
        /* Enable the cpu-to-cpu isr just in case _core_mutex_unlock function has not woke up another task waiting for the core mutex. */
        if (*cm_ptr->GATE_PTR != (MCC_CORE_NUMBER + 1))
            _bsp_int_enable(cpu_to_cpu_isr_vector);
        return MCC_SUCCESS;
    }
    else
        return MCC_ERR_SEMAPHORE;
}

/*!
 * \brief This function registers the CPU-to-CPU interrupt.
 *
 * Calls MQX interrupt component functions to install and enable the CPU-to-CPU interrupt.
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_INT (failure)
 *
 */
int mcc_register_cpu_to_cpu_isr(void)
{
    unsigned int vector_number;

    vector_number = mcc_get_cpu_to_cpu_vector(MCC_CORE_NUMBER);

    if(vector_number != MCC_VECTOR_NUMBER_INVALID) {
#if PSP_MQX_CPU_IS_IMX6SX
        /*
         * on PELE, cpu to cpu interrupt is in MU and should be enabled explicitly
         */
        mcc_enable_cpu_to_cpu_interrupt(MCC_CORE_NUMBER);
#endif
        _int_install_isr((_mqx_uint)vector_number, mcc_cpu_to_cpu_isr, NULL);
        mcc_clear_cpu_to_cpu_interrupt(MCC_CORE_NUMBER);
        /* Priority of the cpu-to-cpu isr must be lower than the core mutex isr priority */
        _bsp_int_init(vector_number, BSPCFG_CORE_MUTEX_PRIORITY + 1, 0, TRUE);
        _bsp_int_enable(vector_number);
        cpu_to_cpu_isr_vector = vector_number;
        return MCC_SUCCESS;
    }
    else {
        return MCC_ERR_INT;
    }
}

/*!
 * \brief This function triggers an interrupt to other core(s).
 *
 * \return MCC_SUCCESS
 *
 */
int mcc_generate_cpu_to_cpu_interrupt(void)
{
    /* Assert directed CPU interrupts for all processors except the requesting core */
    mcc_triger_cpu_to_cpu_interrupt();

    return MCC_SUCCESS;
}

/*!
 * \brief This function copies data.
 *
 * Copies the number of single-addressable units from the source address to destination address.
 *
 * \param[in] src Source address.
 * \param[in] dest Destination address.
 * \param[in] size Number of single-addressable units to copy.
 */
void mcc_memcpy(void *src, void *dest, unsigned int size)
{
    _mem_copy((void *)src, (void *)dest, (_mem_size)size);
}

/*!
 * \brief This function initializes Operating System-dependent synchronization modules.
 *
 * The OS synchronization modules initialized by this function are used for unblocking 
 * OS tasks waiting for new received data and for unblocking OS tasks waiting for a free buffer .
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_OSSYNC (OS synchronization module(s) initialization failed)
 *
 * \see mcc_deinit_os_sync
 * \see mcc_clear_os_sync_for_ep
 * \see mcc_wait_for_buffer_freed
 * \see mcc_wait_for_buffer_queued
 *
 */
int mcc_init_os_sync(void)
{
    int i;
    
    for(i=0; i<MCC_MQX_LWEVENT_COMPONENTS_COUNT; i++) {
        if(MQX_OK != _lwevent_create(&lwevent_buffer_queued[i],0)) {
            return MCC_ERR_OSSYNC;
        }
    }
    if(MQX_OK != _lwevent_create(&lwevent_buffer_freed, LWEVENT_AUTO_CLEAR)) {
        return MCC_ERR_OSSYNC;
    }
    return MCC_SUCCESS;
}

/*!
 * \brief This function de-initializes Operating System-dependent synchronization modules.
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_OSSYNC (OS synchronization module(s) deinitialization failed)
 *
 * \see mcc_init_os_sync
 * \see mcc_clear_os_sync_for_ep
 * \see mcc_wait_for_buffer_freed
 * \see mcc_wait_for_buffer_queued
 *
 */
int mcc_deinit_os_sync(void)
{
    int i;
    
    for(i=0; i<MCC_MQX_LWEVENT_COMPONENTS_COUNT; i++) {
        if(MQX_OK != _lwevent_destroy(&lwevent_buffer_queued[i])) {
            return MCC_ERR_OSSYNC;
        }
    }
    if(MQX_OK != _lwevent_destroy(&lwevent_buffer_freed)) {
        return MCC_ERR_OSSYNC;
    }
    return MCC_SUCCESS;
}

/*!
 * \brief This function clears the buffer queued event bit for the particular endpoint.
 *
 * \param[in] endpoint Pointer to the endpoint to clear the buffer queued event bit for.
 *
 * \see mcc_init_os_sync
 * \see mcc_wait_for_buffer_queued
 *
 */
void mcc_clear_os_sync_for_ep(MCC_ENDPOINT *endpoint)
{
    unsigned int lwevent_index = endpoint->port / MCC_MQX_LWEVENT_GROUP_SIZE;
    unsigned int lwevent_group_index = endpoint->port % MCC_MQX_LWEVENT_GROUP_SIZE;
    
    _lwevent_clear(&lwevent_buffer_queued[lwevent_index], 1<<lwevent_group_index);

}

/*!
 * \brief This function waits for the buffer freed event.
 *
 * The OS task is blocked until the buffer freed event occurs or the timeout is reached.
 * If the timeout is reached and there is no free buffer available the null pointer is returned,
 * otherwise the valid pointer to the MCC buffer is returned.
 *
 * \param[out] buffer Pointer to the MCC buffer dequeued from the free list.
 * \param[in] timeout_ms Timeout, in milliseconds, to wait for a free buffer. A value of 0 means don't wait (non-blocking call). A value of 0xffffffff means wait forever (blocking call).
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_TIMEOUT (Buffer not freed before the timeout)
 *
 */
int mcc_wait_for_buffer_freed(MCC_RECEIVE_BUFFER **buffer, unsigned int timeout_ms)
{
    int return_value, end_time_set_flag = 0;
    MQX_TICK_STRUCT tick_time;
    MCC_RECEIVE_BUFFER * buf = null;

    while(buf == null) {
        /* Blocking calls: CPU-to-CPU ISR sets the event and thus resumes tasks waiting for a free MCC buffer.
         * As the interrupt request is send to all cores when a buffer is freed it could happen that several
         * tasks from different cores/nodes are waiting for a free buffer and all of them are notified that the buffer
         * has been freed. This function has to check (after the wake up) that a buffer is really available and has not been already
         * grabbed by another "competitor task" that has been faster. If so, it has to wait again for the next notification. */
        /* wait forever */
        if(timeout_ms == 0xFFFFFFFF) {
            _lwevent_wait_ticks(&lwevent_buffer_freed, 1, TRUE, 0);
        }
        /* timeout_ms > 0 */
        else {
            if(!end_time_set_flag) {
                _time_get_ticks(&tick_time);
                _time_add_msec_to_ticks(&tick_time, timeout_ms);
                end_time_set_flag = 1;
            }
            return_value = _lwevent_wait_until(&lwevent_buffer_freed, 1, TRUE, &tick_time);
            if(return_value == LWEVENT_WAIT_TIMEOUT) {
                /* Buffer not freed before the timeout */
                *buffer = null;
                return MCC_ERR_TIMEOUT;
            }
        }
        /* Semaphore-protected section start */
        mcc_get_semaphore();

        /* Dequeue the buffer from the free list */
        MCC_DCACHE_INVALIDATE_MLINES((void*)&bookeeping_data->free_list, sizeof(MCC_RECEIVE_LIST*));
        buf = mcc_dequeue_buffer(&bookeeping_data->free_list);

        /* Semaphore-protected section end */
        mcc_release_semaphore();
    }
    *buffer = buf;
    return MCC_SUCCESS;
}

/*!
 * \brief This function waits for the buffer queued event.
 *
 * The OS task is blocked until the buffer queued event occurs or the timeout is reached.
 *
 * \param[in] endpoint Pointer to the endpoint the buffer queued event is associated with.
 * \param[in] timeout_ms Timeout, in milliseconds, to wait for a free buffer. A value of 0 means don't wait (non-blocking call). A value of 0xffffffff means wait forever (blocking call).
 *
 * \return MCC_SUCCESS
 * \return MCC_ERR_TIMEOUT (Buffer not queued before the timeout)
 *
 */
int mcc_wait_for_buffer_queued(MCC_ENDPOINT *endpoint, unsigned int timeout_ms)
{
    unsigned int lwevent_index = endpoint->port / MCC_MQX_LWEVENT_GROUP_SIZE;
    unsigned int lwevent_group_index = endpoint->port % MCC_MQX_LWEVENT_GROUP_SIZE;
    MQX_TICK_STRUCT tick_time;
    int return_value, end_time_set_flag = 0;;
    MCC_RECEIVE_LIST *tmp_list;

    /* Semaphore-protected section start */
    mcc_get_semaphore();

    /* Get list of buffers kept by the particular endpoint */
    tmp_list = mcc_get_endpoint_list(*endpoint);

    /* Semaphore-protected section end */
    mcc_release_semaphore();

    while(tmp_list->head == (MCC_RECEIVE_BUFFER*)0) {
        if(timeout_ms == 0xFFFFFFFF) {
            _lwevent_wait_ticks(&lwevent_buffer_queued[lwevent_index], 1<<lwevent_group_index, TRUE, 0);
        }
        /* timeout_ms > 0 */
        else {
            if(!end_time_set_flag) {
                _time_get_ticks(&tick_time);
                _time_add_msec_to_ticks(&tick_time, timeout_ms);
                end_time_set_flag = 1;
            }
            return_value = _lwevent_wait_until(&lwevent_buffer_queued[lwevent_index], 1<<lwevent_group_index, TRUE, &tick_time);
            if(return_value == LWEVENT_WAIT_TIMEOUT) {
                /* Buffer not dequeued before the timeout */
                return MCC_ERR_TIMEOUT;
            }
        }
        /* It is necessary to invalidate the cache and to check the receive list head here
           beacause the coherence between the receive list, signal queue and the buffer queued event
           is not ensured on the sender side (the cpu-to-cpu interrupt can't be generated together with
           writing to the receive list/buffer and to the signal queue in one MCC semaphore protected section )
           and it could happen under certain conditions that the buffer queued event is set although the receive
           list is empty/null */
        /* Semaphore-protected section start */
        mcc_get_semaphore();

        MCC_DCACHE_INVALIDATE_MLINES((void*)tmp_list, sizeof(MCC_RECEIVE_LIST*));

        /* Semaphore-protected section end */
        mcc_release_semaphore();
    }
    return MCC_SUCCESS;
}

MCC_BOOKEEPING_STRUCT *mcc_get_bookeeping_data(void)
{
    MCC_BOOKEEPING_STRUCT * bookeeping_data;

    bookeeping_data = (MCC_BOOKEEPING_STRUCT *)MCC_BASE_ADDRESS;

    return bookeeping_data;
}
