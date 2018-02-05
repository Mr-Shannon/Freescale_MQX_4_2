/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
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

/* import from maximum_config.h */

#undef MQX_CHECK_ERRORS
#define MQX_CHECK_ERRORS                            1

#undef MQX_CHECK_MEMORY_ALLOCATION_ERRORS
#define MQX_CHECK_MEMORY_ALLOCATION_ERRORS          1

#undef MQX_CHECK_VALIDITY
#define MQX_CHECK_VALIDITY                          1


#undef MQX_COMPONENT_DESTRUCTION
#define MQX_COMPONENT_DESTRUCTION                   1

#undef MQX_IO_COMPONENT_DESTRUCTION
#define MQX_IO_COMPONENT_DESTRUCTION                1

#undef MQX_DEFAULT_TIME_SLICE_IN_TICKS
#define MQX_DEFAULT_TIME_SLICE_IN_TICKS             0

#undef MQX_EXIT_ENABLED
#define MQX_EXIT_ENABLED                            1

#undef MQX_EXTRA_TASK_STACK_ENABLE
#define MQX_EXTRA_TASK_STACK_ENABLE                 1

#undef MQX_HAS_TIME_SLICE
#define MQX_HAS_TIME_SLICE                          1

#undef MQX_INCLUDE_FLOATING_POINT_IO
#define MQX_INCLUDE_FLOATING_POINT_IO               1

#undef MQX_IS_MULTI_PROCESSOR
#define MQX_IS_MULTI_PROCESSOR                      1

#undef MQX_KERNEL_LOGGING
#define MQX_KERNEL_LOGGING                          1

#undef MQX_LWLOG_TIME_STAMP_IN_TICKS
#define MQX_LWLOG_TIME_STAMP_IN_TICKS               0

#undef MQX_MEMORY_FREE_LIST_SORTED
#define MQX_MEMORY_FREE_LIST_SORTED                 1

#undef MQX_MONITOR_STACK
#define MQX_MONITOR_STACK                           1

#undef MQX_MUTEX_HAS_POLLING
#define MQX_MUTEX_HAS_POLLING                       1

#undef MQX_PROFILING_ENABLE
#define MQX_PROFILING_ENABLE                        1

#undef MQX_RUN_TIME_ERR_CHECK_ENABLE
#define MQX_RUN_TIME_ERR_CHECK_ENABLE               1

#undef MQX_THREAD_LOCAL_STORAGE_ENABLE
#define MQX_THREAD_LOCAL_STORAGE_ENABLE             1

#undef MQX_TAD_RESERVED_ENABLE
#define MQX_TAD_RESERVED_ENABLE                     1

#undef MQX_TASK_CREATION_BLOCKS
#define MQX_TASK_CREATION_BLOCKS                    1

#undef MQX_TASK_DESTRUCTION
#define MQX_TASK_DESTRUCTION                        1

#undef MQX_TIMER_USES_TICKS_ONLY
#define MQX_TIMER_USES_TICKS_ONLY                   1

#undef MQX_USE_32BIT_MESSAGE_QIDS
#define MQX_USE_32BIT_MESSAGE_QIDS                  0

#undef MQX_USE_32BIT_TYPES
#define MQX_USE_32BIT_TYPES                         0

#undef MQX_USE_EVENTS
#define MQX_USE_EVENTS                              1

#undef MQX_USE_IDLE_TASK
#define MQX_USE_IDLE_TASK                           1

#undef MQX_USE_IPC
#define MQX_USE_IPC                                 1

#undef MQX_USE_INLINE_MACROS
#define MQX_USE_INLINE_MACROS                       1

#undef MQX_USE_LWEVENTS
#define MQX_USE_LWEVENTS                            1

#undef MQX_USE_LOGS
#define MQX_USE_LOGS                                1

#undef MQX_USE_LWLOGS
#define MQX_USE_LWLOGS                              1

#undef MQX_USE_TLSF_ALLOCATOR
#define MQX_USE_TLSF_ALLOCATOR                      0

#undef MQX_ALLOCATOR_GARBAGE_COLLECTING
#define MQX_ALLOCATOR_GARBAGE_COLLECTING            1

#undef MQX_ALLOCATOR_ALLOW_IN_ISR
#define MQX_ALLOCATOR_ALLOW_IN_ISR                  1

#undef MQX_USE_MEM
#define MQX_USE_MEM                                 0

#undef MQX_USE_LWMEM_ALLOCATOR
#if !MQX_USE_MEM && !MQX_USE_TLSF_ALLOCATOR
#define MQX_USE_LWMEM_ALLOCATOR                     1
#else
#define MQX_USE_LWMEM_ALLOCATOR                     0
#endif

#undef MQX_USE_LWMEM
#define MQX_USE_LWMEM                               1

#undef MQX_USE_UNCACHED_MEM
#define MQX_USE_UNCACHED_MEM                        0

#undef MQX_USE_LWMSGQ
#define MQX_USE_LWMSGQ                              1

#undef MQX_USE_LWTIMER
#define MQX_USE_LWTIMER                             1

#undef MQX_USE_MESSAGES
#define MQX_USE_MESSAGES                            1

#undef MQX_USE_MUTEXES
#define MQX_USE_MUTEXES                             1

#undef MQX_USE_NAME
#define MQX_USE_NAME                                1

#undef MQX_USE_PARTITIONS
#define MQX_USE_PARTITIONS                          1

#undef MQX_USE_SEMAPHORES
#define MQX_USE_SEMAPHORES                          1

#undef MQX_USE_SW_WATCHDOGS
#define MQX_USE_SW_WATCHDOGS                        1

#undef MQX_USE_TIMER
#define MQX_USE_TIMER                               1

#undef MQX_VERIFY_KERNEL_DATA
#define MQX_VERIFY_KERNEL_DATA                      1

#undef MQX_ALLOW_TYPED_MEMORY
#define MQX_ALLOW_TYPED_MEMORY                      1

#undef MQX_ROM_VECTORS
#define MQX_ROM_VECTORS                             1

#undef MQX_SPARSE_ISR_TABLE
#define MQX_SPARSE_ISR_TABLE                        0

#undef MQX_USE_IO_OLD
#define MQX_USE_IO_OLD                              1

#undef MQX_GUERRILLA_INTERRUPTS_EXIST
#define MQX_GUERRILLA_INTERRUPTS_EXIST              0

#define CODESIZE_USER_CONFIG                        1

#include <psp_cpudef.h>

#undef BSPCFG_ENABLE_ADC
#undef BSPCFG_ENABLE_ADC0
#undef BSPCFG_ENABLE_ADC1
#undef BSPCFG_ENABLE_ADC2
#undef BSPCFG_ENABLE_ADC3
#undef BSPCFG_ENABLE_ADC4
#undef BSPCFG_ENABLE_LWADC
#undef BSPCFG_ENABLE_CPP
#undef BSPCFG_ENABLE_ENET_MULTICAST
#undef BSPCFG_ENABLE_ENET_STATS
#undef BSPCFG_ENABLE_FLASHX
#undef BSPCFG_ENABLE_FLASHX0
#undef BSPCFG_ENABLE_EXT_FLASH
#undef BSPCFG_ENABLE_GPIODEV
#undef BSPCFG_ENABLE_I2C0
#undef BSPCFG_ENABLE_I2C1
#undef BSPCFG_ENABLE_I2C5
#undef BSPCFG_ENABLE_II2C0
#undef BSPCFG_ENABLE_II2C1
#undef BSPCFG_ENABLE_II2C5
#undef BSPCFG_ENABLE_IO_SUBSYSTEM
#undef BSPCFG_ENABLE_ISPI0
#undef BSPCFG_ENABLE_ISPI1
#undef BSPCFG_ENABLE_ISPI2
#undef BSPCFG_ENABLE_ITTYA
#undef BSPCFG_ENABLE_ITTYB
#undef BSPCFG_ENABLE_ITTYC
#undef BSPCFG_ENABLE_ITTYD
#undef BSPCFG_ENABLE_ITTYE
#undef BSPCFG_ENABLE_ITTYF
#undef BSPCFG_ENABLE_PCFLASH
#undef BSPCFG_ENABLE_RTCDEV
#undef BSPCFG_ENABLE_SPI0
#undef BSPCFG_ENABLE_SPI1
#undef BSPCFG_ENABLE_SPI2
#undef BSPCFG_ENABLE_TTYA
#undef BSPCFG_ENABLE_TTYB
#undef BSPCFG_ENABLE_TTYC
#undef BSPCFG_ENABLE_TTYD
#undef BSPCFG_ENABLE_TTYE
#undef BSPCFG_ENABLE_TTYF
#undef BSPCFG_ENABLE_NANDFLASH
#undef BSPCFG_ENABLE_ESDHC
#undef BSPCFG_ENABLE_SDHC
#undef BSPCFG_ENABLE_QUADSPI0
#undef BSPCFG_ENABLE_II2S0
#undef BSPCFG_ENABLE_CRC

#undef MQXCFG_MEM_COPY
#undef PSP_HAS_SUPPORT_STRUCT
#undef RTCSCFG_ENABLE_ICMP
#undef RTCSCFG_ENABLE_UDP
#undef RTCSCFG_ENABLE_TCP
#undef RTCSCFG_ENABLE_STATS
#undef RTCSCFG_ENABLE_GATEWAYS
#undef FTPDCFG_USES_MFS
#undef RTCSCFG_ENABLE_SNMP
#undef TELNETDCFG_NOWAIT
#undef RTCSCFG_ENABLE_VIRTUAL_ROUTES
#undef SHELLCFG_USES_MFS
#undef SHELLCFG_USES_RTCS



#define BSPCFG_ENABLE_CRC                           1
#define BSPCFG_ENABLE_II2S0                         1

#define BSPCFG_ENABLE_I2C0                          1
#define BSPCFG_ENABLE_I2C1                          1
#define BSPCFG_ENABLE_II2C0                         1
#define BSPCFG_ENABLE_II2C1                         1
#define BSPCFG_ENABLE_IO_SUBSYSTEM                  1
#define BSPCFG_ENABLE_ISPI0                         1
#define BSPCFG_ENABLE_ISPI1                         1
#define BSPCFG_ENABLE_ISPI2                         1
#define BSPCFG_ENABLE_ITTYA                         1
#define BSPCFG_ENABLE_ITTYB                         1
#define BSPCFG_ENABLE_ITTYC                         1
#define BSPCFG_ENABLE_ITTYD                         1
#define BSPCFG_ENABLE_ITTYE                         1
#define BSPCFG_ENABLE_ITTYF                         1
#define BSPCFG_ENABLE_PCFLASH                       1
#define BSPCFG_ENABLE_RTCDEV                        1
#define BSPCFG_ENABLE_SPI0                          1
#define BSPCFG_ENABLE_SPI1                          1
#define BSPCFG_ENABLE_SPI2                          1
#define BSPCFG_ENABLE_TTYA                          1
#define BSPCFG_ENABLE_TTYB                          1
#define BSPCFG_ENABLE_TTYC                          1
#define BSPCFG_ENABLE_TTYD                          1
#define BSPCFG_ENABLE_TTYE                          1
#define BSPCFG_ENABLE_TTYF                          1
#define BSPCFG_ENABLE_NANDFLASH                     1
#define BSPCFG_ENABLE_ESDHC                         1
#define BSPCFG_ENABLE_ADC0                          1
#define BSPCFG_ENABLE_ADC1                          1
#define BSPCFG_ENABLE_FLASHX                        1
#define BSPCFG_ENABLE_GPIODEV                       0
#define BSPCFG_ENABLE_LWADC                         1

/*
** board-specific MQX settings - see for defaults mqx\source\include\mqx_cnfg.h
*/
#define BSPCFG_ENABLE_SDHC                          1
#define BSPCFG_ENABLE_QUADSPI0                      1

#define MQXCFG_MEM_COPY                             1
#define PSP_HAS_SUPPORT_STRUCT                      1
#define MQX_STD_TIME_API                            1

/*
** board-specific RTCS settings - see for defaults rtcs\source\include\rtcscfg.h
*/

#define RTCSCFG_ENABLE_ICMP                         1
#define RTCSCFG_ENABLE_UDP                          1
#define RTCSCFG_ENABLE_TCP                          1
#define RTCSCFG_ENABLE_STATS                        1
#define RTCSCFG_ENABLE_GATEWAYS                     1
#define FTPDCFG_USES_MFS                            1
#define RTCSCFG_ENABLE_SNMP                         1
#define TELNETDCFG_NOWAIT                           FALSE
#define RTCSCFG_ENABLE_VIRTUAL_ROUTES               1

#define SHELLCFG_USES_RTCS                          1
#define SHELLCFG_USES_MFS                           1

// SVF522R3K_A5
#if defined PSP_CPU_SVF522R3K_A5
#   if MQX_CPU == PSP_CPU_SVF522R3K_A5
#       undef BSPCFG_ENABLE_RTCDEV
#       define BSPCFG_ENABLE_RTCDEV 0
#   endif
#endif

// SVF522R3K_M4
#if defined PSP_CPU_SVF522R3K_M4
#   if MQX_CPU == PSP_CPU_SVF522R3K_M4
#       undef BSPCFG_ENABLE_RTCDEV
#       define BSPCFG_ENABLE_RTCDEV 0
#   endif
#endif

#endif /* __verif_enabled_config_h__ */
/* EOF */