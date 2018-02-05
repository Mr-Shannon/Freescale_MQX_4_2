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
*   This file contains the task template list.
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "read.h"

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index,   Function,   Stack,  Priority,   Name,       Attributes,          Param, Time Slice */
    { WRITE_TASK,   write_task, 1000,   8,          "write",    MQX_USER_TASK,                   0,     0 },
    { READ_TASK,    read_task,  1000,   8,          "read",     MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/* EOF */
