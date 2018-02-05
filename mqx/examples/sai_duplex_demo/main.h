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

#ifndef __main_h_
#define __main_h_

#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>
#include <message.h>

extern void Init_task(uint32_t);
extern void Run_task(uint32_t);

#define AUDIO_SAMPLE_RATE   (44100)
#ifdef BSPCFG_ENABLE_SAI
#define CLK_MULT             (384)
#else
#define CLK_MULT             (256)
#endif

#define INIT_TASK 1
#define RUN_TASK 2

#define WRITE_QUEUE 8
#define REC_BLOCK_SIZE 512

#endif /* __main_h_ */

/* EOF */
