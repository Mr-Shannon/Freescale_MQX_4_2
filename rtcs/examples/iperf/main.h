/*HEADER**********************************************************************
*
* Copyright (c) 2015, Freescale Semiconductor, Inc.
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
*
*
*END************************************************************************/

#ifndef __main_h_
#define __main_h_


#define MAIN_TASK   1
#define ENET_DEVICE 0
#define ENET_IPADDR IPADDR(192,168,0,22) 
#define ENET_IPMASK IPADDR(255,255,255,0) 


extern void Main_task (uint32_t);


#endif /* __main_h_ */

