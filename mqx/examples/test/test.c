/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
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
*   This file contains the source for the test example program.
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>

#if defined(MQX_USE_LWMEM) && !MQX_USE_LWMEM
#error "This application requires LWMEM component to be active in MQX.\
	Please set MQX_USE_LWMEM to 1 in user_config.h and recompile kernel."
#endif

#include <fio.h>
#include <event.h>
#include <log.h>
#include <lwevent.h>
#include <lwlog.h>
#include <lwmem.h>
#include <lwtimer.h>
#include <message.h>
#include <mutex.h>
#include <name.h>
#include <partition.h>
#include <sem.h>
#include <timer.h>
#include <watchdog.h>


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


extern void background_test_task(uint32_t);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index, Function,             Stack,  Priority,   Name,     Attributes,          Param, Time Slice */
    { 10,         background_test_task, 2000,   8,          "Main",   MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/*TASK*----------------------------------------------------------
*
* Task Name : background_test_task
* Comments  :
*   This task is meant to run in the background testing for
* integrity of MQX component datastructures.
*END*-----------------------------------------------------------*/

void background_test_task
   (
      uint32_t  parameter
   )
{
   _partition_id  partition;
   _lwmem_pool_id lwmem_pool_id;
   void          *error_ptr;
   void          *error2_ptr;
   _mqx_uint      error;
   _mqx_uint      result;

   printf("\nTesting component:");
   while (TRUE) {
      printf("\nevent");
      result = _event_test(&error_ptr);
      if (result != MQX_OK){
         printf("\nFailed _event_test: 0x%X.", result);
         _task_block();
      }
      printf("\nlog");
      result = _log_test(&error);
      if (result != MQX_OK){
         printf("\nFailed _log_test: 0x%X.", result);
         _task_block();
      }
      printf("\nlwevent");
      result = _lwevent_test(&error_ptr, &error2_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwevent_test: 0x%X.", result);
         _task_block();
      }
      printf("\nlwlog");
      result = _lwlog_test(&error);
      if (result != MQX_OK){
         printf("\nFailed _lwlog_test: 0x%X.", result);
         _task_block();
      }
      printf("\nlwsem");
      result = _lwsem_test(&error_ptr, &error2_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwsem_test: 0x%X.", result);
         _task_block();
      }
      printf("\nlwmem");
      result = _lwmem_test(&lwmem_pool_id, &error_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwmem_test: 0x%X.", result);
         _task_block();
      }
      printf("\nlwtimer");
      result = _lwtimer_test(&error_ptr, &error2_ptr);
      if (result != MQX_OK){
         printf("\nFailed _lwtimer_test: 0x%X.", result);
         _task_block();
      }
      
#if !MQX_USE_LWMEM_ALLOCATOR && !MQX_USE_TLSF_ALLOCATOR

      printf("\nmem");
      result = _mem_test_all(&error_ptr);
      if (result != MQX_OK){
         printf("\nFailed _mem_test_all,");
         printf("\nError = 0x%X, pool = 0x%X.", result,
            (_mqx_uint)error_ptr);
         _task_block();
      }
#endif
      /*
      ** Create the message component.
      ** Verify the integrity of message pools and message queues.
      */
      printf("\nmsg");
      if (_msg_create_component() != MQX_OK){
         printf("\nError creating the message component.");
         _task_block();
      }
      printf("\nmsgpool");
      if (_msgpool_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _msgpool_test.");
         _task_block();
      }
      printf("\nmsgq");
      if (_msgq_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _msgq_test.");
         _task_block();
      }
      printf("\nmutex");
      if (_mutex_test(&error_ptr) != MQX_OK){
         printf("\nFailed _mutex_test.");
         _task_block();
      }
      printf("\nname");
      if (_name_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _name_test.");
         _task_block();
      }
      printf("\npartition");
      if (_partition_test(&partition, &error_ptr, &error2_ptr) 
         != MQX_OK)
      {
         printf("\nFailed _partition_test.");
         _task_block();
      }
      printf("\nsem");
      if (_sem_test(&error_ptr) != MQX_OK){
         printf("\nFailed _sem_test.");
         _task_block();
      }
      printf("\ntaskq");
      if (_taskq_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _takq_test.");
         _task_block();
      }
      printf("\ntimer");
      if (_timer_test(&error_ptr) != MQX_OK){
         printf("\nFailed _timer_test.");
         _task_block();
      }
      printf("\nwatchdog");
      if (_watchdog_test(&error_ptr, &error2_ptr) != MQX_OK){
         printf("\nFailed _watchlog_test.");
         _task_block();
      }
      printf("\nAll tests passed.");
      _task_block();
   }

}

/* EOF */
