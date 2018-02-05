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

#include <mqx.h>
#include <bsp.h>
#include <rtcs.h>
#include <shell.h>
#include <sh_rtcs.h>
#include <ipcfg.h>

#include "main.h"
#include "iperf.h"

#if !BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


const SHELL_COMMAND_STRUCT Shell_commands[] = {
   /* RTCS commands */ 
   { "arpadd",    Shell_arpadd },
   { "arpdel",    Shell_arpdel },
   { "arpdisp",   Shell_arpdisp },
   { "exit",      Shell_exit },      
   { "gate",      Shell_gate },
   { "gethbn",    Shell_get_host_by_name }, 
   { "getrt",     Shell_getroute },
   { "help",      Shell_help }, 
   { "ipconfig",  Shell_ipconfig },      
   { "netstat",   Shell_netstat },   
#if RTCSCFG_ENABLE_ICMP      
   { "ping",      Shell_ping },      
#endif
   { "walkrt",    Shell_walkroute },
   { "?",         Shell_command_list },
   { "dns",       Shell_get_host_by_name }, /* DNS Resolver.*/ 
   { "iperf",     iperf },
   { NULL,        NULL } 
};


TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
/*  Task number, Entry point, Stack, Pri, String, Auto? */
   {MAIN_TASK,   Main_task,   3000,  9 /* //DM 9*/,   "main", MQX_AUTO_START_TASK},
   {0,           0,           0,     0,   0,      0}
};


/*TASK*-----------------------------------------------------------------
*
* Function Name  : Main_task
* Comments       :
*    This task initializes RTCS and starts SHELL.
*
*END------------------------------------------------------------------*/

void Main_task(uint32_t initial_data)
{
   uint32_t error;
   _enet_address            enet_address = BSP_DEFAULT_ENET_OUI;

#if 0 //DM
  _RTCSPCB_init = 4;       /* Default is 4.*/
  _RTCSPCB_grow = 2;       /* Default is 0.*/
  _RTCSPCB_max = 8;      /* Default is 4.*/
  _RTCS_msgpool_init = 4;  /* Default is 8.*/
  _RTCS_msgpool_grow = 2;  /* Default is 2.*/
  _RTCS_msgpool_max  = 8; /* Default is 8.*/
  _RTCS_socket_part_init = 4; /* Default is 3.*/
  _RTCS_socket_part_grow = 2; /* Default is 0.*/
  _RTCS_socket_part_max  = 8; /* Default is 3.*/  
#endif  

   error = RTCS_create();
   if (error != RTCS_OK) 
   {
      printf("\nRTCS failed to initialize, error = %X", error);
      _task_block();
   }

   _IP_forward = TRUE;
   ENET_get_mac_address (ENET_DEVICE, ENET_IPADDR, enet_address);

   /* IPCFG can be initialized from shell or by calling ipcfg_init_device() */ 

   /*******************************
   * 
   * START YOUR CODING HERE
   *
   ********************************/ 
    {
        IPCFG_IP_ADDRESS_DATA	ip_data;
        
        /* Initializing Ethernet device.*/
        ip_data.ip = ENET_IPADDR;
        ip_data.mask = ENET_IPMASK;
        ip_data.gateway = 0;
        
        
        ipcfg_init_device (ENET_DEVICE, enet_address);
        ipcfg_bind_staticip (ENET_DEVICE, &ip_data);
    
    }
   
   for (;;)  
   {
      /* Run the shell */
      Shell(Shell_commands, NULL);
   }
}

/* EOF */
