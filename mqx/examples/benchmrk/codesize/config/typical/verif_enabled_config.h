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
*   MQX configuration set: verification options enabled
*
*
*END************************************************************************/

#ifndef __verif_enabled_config_h__
#define __verif_enabled_config_h__

#ifndef MQX_CHECK_VALIDITY
#define MQX_CHECK_VALIDITY                          1
#endif

#ifndef MQX_MONITOR_STACK
#define MQX_MONITOR_STACK                           1
#endif

#ifndef MQX_CHECK_ERRORS
#define MQX_CHECK_ERRORS                            1
#endif

#ifndef MQX_TASK_CREATION_BLOCKS
#define MQX_TASK_CREATION_BLOCKS                    1
#endif

#ifndef MQX_CHECK_MEMORY_ALLOCATION_ERRORS
#define MQX_CHECK_MEMORY_ALLOCATION_ERRORS          1
#endif

#ifndef MQX_VERIFY_KERNEL_DATA
#define MQX_VERIFY_KERNEL_DATA                      1
#endif

#define CODESIZE_USER_CONFIG                        1

#include <psp_cpudef.h>
#undef BSPCFG_ENABLE_TTYA
#undef BSPCFG_ENABLE_ITTYA
#undef BSPCFG_ENABLE_TTYB
#undef BSPCFG_ENABLE_ITTYB
#undef BSPCFG_ENABLE_TTYC
#undef BSPCFG_ENABLE_ITTYC
#undef BSPCFG_ENABLE_TTYD
#undef BSPCFG_ENABLE_ITTYD
#undef BSPCFG_ENABLE_TTYE
#undef BSPCFG_ENABLE_ITTYE
#undef BSPCFG_ENABLE_TTYF
#undef BSPCFG_ENABLE_ITTYF
#undef BSPCFG_ENABLE_I2C0
#undef BSPCFG_ENABLE_II2C0
#undef BSPCFG_ENABLE_I2C1
#undef BSPCFG_ENABLE_II2C1
#undef BSPCFG_ENABLE_SPI0
#undef BSPCFG_ENABLE_ISPI0
#undef BSPCFG_ENABLE_SPI1
#undef BSPCFG_ENABLE_ISPI1
#undef BSPCFG_ENABLE_SPI2
#undef BSPCFG_ENABLE_ISPI2
#undef BSPCFG_ENABLE_GPIODEV
#undef BSPCFG_ENABLE_RTCDEV
#undef BSPCFG_ENABLE_PCFLASH
#undef BSPCFG_ENABLE_ADC0
#undef BSPCFG_ENABLE_ADC1
#undef BSPCFG_ENABLE_FLASHX
#undef BSPCFG_RX_RING_LEN
#undef BSPCFG_TX_RING_LEN
#undef MQX_USE_LWMSGQ
#undef MQX_USE_LWEVENTS
#undef MQX_USE_MESSAGES
#undef MQX_USE_LWTIMER
#undef MQX_HAS_TIME_SLICE
#undef MQX_USE_TIMER
#undef MQX_USE_IDLE_TASK
#undef MQXCFG_MEM_COPY
#undef RTCSCFG_ENABLE_ICMP
#undef RTCSCFG_ENABLE_UDP
#undef RTCSCFG_ENABLE_TCP
#undef RTCSCFG_ENABLE_STATS
#undef RTCSCFG_ENABLE_GATEWAYS
#undef FTPDCFG_USES_MFS
#undef RTCSCFG_ENABLE_SNMP
#undef TELNETDCFG_NOWAIT
#undef PSP_HAS_SUPPORT_STRUCT


#define BSPCFG_ENABLE_TTYA                          0
#define BSPCFG_ENABLE_ITTYA                         0
#define BSPCFG_ENABLE_TTYB                          0
#define BSPCFG_ENABLE_ITTYB                         0
#define BSPCFG_ENABLE_TTYC                          0
#define BSPCFG_ENABLE_ITTYC                         0
#define BSPCFG_ENABLE_TTYD                          0
#define BSPCFG_ENABLE_ITTYD                         0
#define BSPCFG_ENABLE_TTYE                          0
#define BSPCFG_ENABLE_ITTYE                         0
#define BSPCFG_ENABLE_TTYF                          0
#define BSPCFG_ENABLE_ITTYF                         0
#define BSPCFG_ENABLE_I2C0                          1
#define BSPCFG_ENABLE_II2C0                         0
#define BSPCFG_ENABLE_I2C1                          0
#define BSPCFG_ENABLE_II2C1                         1
#define BSPCFG_ENABLE_SPI0                          1
#define BSPCFG_ENABLE_ISPI0                         0
#define BSPCFG_ENABLE_SPI1                          0
#define BSPCFG_ENABLE_ISPI1                         0
#define BSPCFG_ENABLE_SPI2                          0
#define BSPCFG_ENABLE_ISPI2                         0
#define BSPCFG_ENABLE_GPIODEV                       0
#define BSPCFG_ENABLE_RTCDEV                        0
#define BSPCFG_ENABLE_PCFLASH                       1
#define BSPCFG_ENABLE_ADC0                          0
#define BSPCFG_ENABLE_ADC1                          1
#define BSPCFG_ENABLE_FLASHX                        0

#define BSPCFG_RX_RING_LEN                          4
#define BSPCFG_TX_RING_LEN                          2

#define MQX_USE_LWMSGQ                              1
#define MQX_USE_LWEVENTS                            1
#define MQX_USE_MESSAGES                            1
#define MQX_USE_LWTIMER                             1
#define MQX_HAS_TIME_SLICE                          1
#define MQX_USE_TIMER                               1
#define MQX_USE_IDLE_TASK                           1
#define MQXCFG_MEM_COPY                             1
#define PSP_HAS_SUPPORT_STRUCT                      1

#define RTCSCFG_ENABLE_ICMP                         1
#define RTCSCFG_ENABLE_UDP                          1
#define RTCSCFG_ENABLE_TCP                          1
#define RTCSCFG_ENABLE_STATS                        1
#define RTCSCFG_ENABLE_GATEWAYS                     1
#define FTPDCFG_USES_MFS                            1
#define RTCSCFG_ENABLE_SNMP                         0

#define TELNETDCFG_NOWAIT                           FALSE

#endif
/* EOF */
