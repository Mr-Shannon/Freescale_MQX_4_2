/*HEADER**********************************************************************
*
* Copyright 2015 Freescale Semiconductor, Inc.
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
*   This file contains the source for the context_switch_callback example program.
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

#if !MQX_HAS_CONTEXT_SWITCH_HANDLER
#error This application requires MQX_HAS_CONTEXT_SWITCH_HANDLER defined non-zero in user_config.h. Please recompile PSP with this option.
#endif

#define STACK_SIZE      1500
#define STACK_OVERHEAD  128

/* Task IDs */
#define INIT_TASK       3
#define OVERFLOWED_TASK 4
#define HELLO_TASK      5
#define WORLD_TASK      6


void init_task(uint32_t);
void overflowed_task(uint32_t);
void hello_task(uint32_t);
void world_task(uint32_t);
void task_switch_callback(_task_id, _task_id, bool);
void func(volatile uint32_t*);

_task_id hello_task_id;
_task_id world_task_id;
_task_id overflowed_task_id;
uint32_t task_alive;
int32_t hello_count;
int32_t world_count;
LWSEM_STRUCT sync;
bool wait;
char stack_ptr[STACK_SIZE + STACK_OVERHEAD];

const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
   /* Task Index,       Function,       Stack,        Priority, Name,         Attributes,          Param, Time Slice */
    { INIT_TASK,        init_task,      STACK_SIZE,   8,        "init",       MQX_AUTO_START_TASK, 0,     0 },
    { OVERFLOWED_TASK,  overflowed_task,STACK_SIZE,   9,        "overflowed", 0,                   0,     0 },
    { WORLD_TASK,       world_task,     STACK_SIZE,   9,        "world",      0,                   0,     0 },
    { HELLO_TASK,       hello_task,     STACK_SIZE,   8,        "hello",      0,                   0,     0 },
    { 0 }
};

/*FUNCTION*-----------------------------------------------------
*
* Func Name    : task_switch_callback
* Comments     :
*    The context switch handler
*
*END*-----------------------------------------------------*/
void task_switch_callback
    (
        /* The task ID of restored task */
        _task_id tid_restored, 

        /* The task ID of saved task */
        _task_id tid_saved, 

        /* Flag indicate stack error */
        bool stack_error
    )
{
    if (tid_saved == hello_task_id)
    {
        hello_count--;
    }
    else if (tid_saved == world_task_id)
    {
        world_count--;
    }

    if (tid_restored == hello_task_id)
    {
        hello_count++;
    }
    else if (tid_restored == world_task_id)
    {
        world_count++;
    }

    if (stack_error)
    {
       overflowed_task_id = tid_saved;
    }
}

/*FUNCTION*-----------------------------------------------------
*
* Func Name    : func
* Comments     :
*    The recursive function to make the calling task overflowed.
*
*END*-----------------------------------------------------*/
void func
    (
        volatile uint32_t *param
    )
{
    volatile uint32_t val;

    val = *param + 1;

    if (_task_check_stack())
    {
        /* Wait here for task switching */
        while (wait){param--;};
    }
    else
    {
        /* Keep calling itselft until stack overflowed */
        func(&val);
    }
}

/*TASK*-----------------------------------------------------
*
* Task Name    : init_task
* Comments     :
*    This task creates overflowed_task and then block.
*
*END*-----------------------------------------------------*/

void init_task
   (
      uint32_t initial_data
   )
{
    /* Create the overflowed_task at the static memory stack_ptr,
       the memory range of stack_ptr is large enough, so that 
       if the task is overflowed, it would not effect to other memory area 
       which is in used */
    if (MQX_NULL_TASK_ID == _task_create_at(0, OVERFLOWED_TASK, 0, stack_ptr, STACK_SIZE))
    {
        printf ("\n Could not create overflowed_task\n");
    }
    _task_block();
}

/*TASK*-----------------------------------------------------
*
* Task Name    : overflowed_task
* Comments     :
*    This task creates hello_task and world_task then make its stack overflowed.
*
*END*-----------------------------------------------------*/

void overflowed_task
   (
      uint32_t initial_data
   )
{
   volatile uint32_t temp = 0;

   /* Initialize global variables */
   task_alive = 0;
   wait = true;
   overflowed_task_id = MQX_NULL_TASK_ID;
   hello_count = 0;
   world_count = 0;

   if (MQX_OK != _lwsem_create(&sync, 0))
   {
       printf ("\n Could not create lwsem\n");
   }

   /* Set callback for context switching */
   _mqx_set_context_switch_handler(task_switch_callback);

   world_task_id = _task_create(0, WORLD_TASK, 0);
   if (world_task_id == MQX_NULL_TASK_ID) {
      printf ("\n Could not create world_task\n");
   }

   hello_task_id = _task_create(0, HELLO_TASK, 0);
   if (hello_task_id == MQX_NULL_TASK_ID) {
      printf ("\n Could not create hello_task\n");
   }

   while (1)
   {
       func(&temp);
       task_alive++;
   }
}

/*TASK*-----------------------------------------------------
*
* Task Name    : world_task
* Comments     :
*    This task prints " World ".
*
*END*-----------------------------------------------------*/

void world_task
   (
      uint32_t initial_data
   )
{
   while (1)
   {
       _lwsem_wait(&sync);

       printf(" World \n");

       if (world_count == 0)
       {
           printf("\n[FAIL]: callback has not been called\n");
       }
       else
       {
           if (hello_count)
               printf("\n[FAIL]: hello_task switching sequence is not correct\n");
       }
   }
}

/*TASK*-----------------------------------------------------
*
* Task Name    : hello_task
* Comments     :
*    This task prints " Hello".
*
*END*-----------------------------------------------------*/

void hello_task
   (
      uint32_t initial_data
   )
{
   while (1)
   {
      _time_delay(1000);
      wait = false;

      if (overflowed_task_id != MQX_NULL_TASK_ID)
      {
          if (overflowed_task_id == _task_get_creator()) printf("\n[OK]:");
          else printf("\n[FAIL]:");

          printf(" Stack overflowed - task id: 0x%x \n", overflowed_task_id);
          overflowed_task_id = MQX_NULL_TASK_ID;
      }

      if (task_alive)
      {
          printf("\n[FAIL]: Overflowed task is still alive \n");
          task_alive = 0;
      }

      if (hello_count == 0)
      {
          printf("\n[FAIL]: callback has not been called\n");
      }
      else
      {
          if (world_count)
              printf("\n[FAIL]: world_task switching sequence is not correct\n");
      }

      printf("\n Hello\n");

      _lwsem_post(&sync);
   }
}

/* EOF */
