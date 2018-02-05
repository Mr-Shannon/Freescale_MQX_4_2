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
*   User configuration for MQX components
*
*
*END************************************************************************/

#ifndef __user_config_h__
#define __user_config_h__

/* mandatory CPU identification */
#define MQX_CPU                 PSP_CPU_MCF52259

/*
** BSP settings - for defaults see mqx\source\bsp\<board_name>\<board_name>.h
*/
#define BSPCFG_ENABLE_RTCDEV     0
#define BSPCFG_ENABLE_TTYA       0
#define BSPCFG_ENABLE_TTYB       1
#define BSPCFG_ENABLE_TTYC       0
#define BSPCFG_ENABLE_ITTYA      0
#define BSPCFG_ENABLE_ITTYB      0
#define BSPCFG_ENABLE_ITTYC      0
#define BSPCFG_ENABLE_I2C0       0
#define BSPCFG_ENABLE_I2C1       0
#define BSPCFG_ENABLE_II2C0      0
#define BSPCFG_ENABLE_II2C1      0
#define BSPCFG_ENABLE_SPI0       0
#define BSPCFG_ENABLE_ISPI0      0
#define BSPCFG_ENABLE_ADC        1
#define BSPCFG_ENABLE_TCHSRES    0
#define BSPCFG_ENABLE_PCFLASH    0
#define BSPCFG_ENABLE_FLASHX     0

#define BSPCFG_RX_RING_LEN       4
#define BSPCFG_TX_RING_LEN       2

/*
** board-specific MQX settings - see for defaults mqx\source\include\mqx_cnfg.h
*/

#define MQX_HAS_TIME_SLICE       1

/*
** board-specific RTCS settings - see for defaults rtcs\source\include\rtcscfg.h
*/

#define RTCSCFG_ENABLE_ICMP      1
#define RTCSCFG_ENABLE_UDP       1
#define RTCSCFG_ENABLE_TCP       1
#define RTCSCFG_ENABLE_STATS     1
#define RTCSCFG_ENABLE_GATEWAYS  1
#define FTPDCFG_USES_MFS         1

#define TELNETDCFG_NOWAIT        FALSE 

#define MQX_TASK_DESTRUCTION     1

/*
** include common settings
*/

/* use the rest of defaults from small-RAM-device profile */
#include "small_ram_config.h"

/* and enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif
/* EOF */
