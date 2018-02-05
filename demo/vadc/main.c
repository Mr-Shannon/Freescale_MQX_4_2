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
*       This file contains the source for a simple example of an application
*       that make use of DCU4 driver and AFE, VDEC and VIU modules.   
*
*END************************************************************************/


#include <string.h>
#include <mqx.h>
#include <bsp.h>
#include <dcu4.h>
#include "videoModules.h"
#include "config.h"



#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

#if ! BSPCFG_ENABLE_DCU4
#error This application requires BSPCFG_ENABLE_DCU4 defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


extern void main_task (uint32_t);
extern void test_task (uint32_t);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
    /* Task Index,   Function,   Stack,  Priority,   Name,   Attributes,          Param, Time Slice */
    { 10L,          main_task,  8192L,  8L,         "Main", MQX_AUTO_START_TASK, 0,     0  },
    { 0 }
};



void sys_init (void);

/*
* Function initialize clock for modules used in example
*/
void sys_init (void)
{
    /***** CLKCONFIG:
    CA5: 396MHz
    DDR: 396MHz
    BUS: 132MHz
    IPS: 66MHz
    CM4: 132MHz
    ******/ 
       
    /* changing PLL6 to 1064MHz allow 133MHz for VADC */
    ANADIG_PLL6_NUM       = 0x0AAAAA9E;   /* MFN */
    ANADIG_PLL6_DENOM     = 0x1FFFFFDA;   /* MFD */
    ANADIG_PLL6_CTRL      = 0x0000202C;
      
    /* wait to lock pll */
    while ((ANADIG_PLL_LOCK & ANADIG_PLL_LOCK_PLL6_MASK) != ANADIG_PLL_LOCK_PLL6_MASK);
         
    /* Set ARMCLKDIV = 1, BUSDIV=3, IPG_CLK_DIV=2 */
    CCM_CACRR |= 0x00600040;
   
    /* Enable all PFDs sources and set SYSCLK as PLL1 PFD3 for 396MHz */
    CCM_CCSR |= 0xF0000000;
    
    /* set divider to 4 (VADC CLK = 133MHz) */
    CCM_CSCDR1 |= 3 << 20;
    
    /* enable VADC clock, after AFE register initialisation */
    CCM_CSCDR1 |= 1 << 22;
       
    SRC_MISC2 |= 1 << 8; /* VADC enabled  - SRC_MISC8_MISC_SHIFT not defined */
    SRC_MISC2 |= 1 << 9; /* VIU fed from the internal VDEC */ 
}


static void setup_layer(MQX_FILE_PTR fd, int layer, DCU4_BPP_TYPE format, int bpp)
{
    DCU4_LAYER_IOCTL_STRUCT layer_control;  
    _mqx_int ret;

    _mem_zero(&layer_control, sizeof(layer_control));   

    layer_control.LAYER = layer;
    layer_control.DATA.REGION.X = LAYER_OFFSET_X;
    layer_control.DATA.REGION.Y = LAYER_OFFSET_Y;
    layer_control.DATA.REGION.WIDTH = LAYER_WIDTH;
    layer_control.DATA.REGION.HEIGHT = LAYER_HEIGHT;
    layer_control.DATA.REGION.FORMAT = format;
    ret = ioctl(fd, IO_IOCTL_DCU4_LAYER_SET_REGION, &layer_control);
    if (MQX_OK != ret) {
        printf ("Error set layer %d region, returned: 0x%08x\n", layer, ret);
        return;
    }
   
    layer_control.DATA.ADDRESS = (void*)IMAGE_ADDRESS;
    ret = ioctl(fd, IO_IOCTL_DCU4_LAYER_SET_ADDRESS, &layer_control);
    if (MQX_OK != ret) {
        printf ("Error set layer %d address, returned: 0x%08x\n", layer, ret);
        return;
    }

    layer_control.DATA.ENABLE = TRUE;
    ret = ioctl(fd, IO_IOCTL_DCU4_LAYER_ENABLE, &layer_control);
    if (MQX_OK != ret) {
        printf ("Error layer %d enable, returned: 0x%08x\n", layer, ret);
        return;
    }
}


/*TASK*-------------------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*
*END*----------------------------------------------------------------------*/
void main_task
   (
      uint32_t dummy
   )
{
    _mqx_int ret;
    MQX_FILE_PTR fd;
    uint32_t nWords = IMAGE_SIZE_IN_PIXELS*4/2;    
    DCU4_TIMING_STRUCT timing = {
       "800x480@60", 60,
        {
            1,      /* pulse width */
            88,     /* back porch */
            800,    /* resolution */
            166,    /* front porch */
            TRUE    /* invert   */
        },
        {
            1,      /* pulse width */
            32,     /* back porch */
            480,    /* resolution */
            11,     /* front porch */
            TRUE    /* invert */
        }
    };

    sys_init();         
    printf ("\n-------------- VADC demo --------------\n\n");
    
    /* Open the DCU4 driver */
    fd = fopen ("dcu0:", NULL);
    if (fd == NULL) {
        printf ("Error opening DCU4 driver!\n");
        goto OnError;
    }

    setup_layer(fd, 0, DCU_BPP_32, 4); /* check readreg in DCU0_UPDATE_MODE */
    memset((uint32_t *)BASE_GFX_MEM, 0x0, (nWords*4)/2); /* make it Black. */
    
    ret = ioctl(fd, IO_IOCTL_DCU4_SET_TIMING, &timing);
    if (MQX_OK != ret) {
        printf ("Error set timing, returned: 0x%08x\n", ret);
        goto OnError;
    }        
                
    AFE_Init();
    
    /*  pick the input source: AFE_ATE_ADC_0,3,4,5 select Video Input 3
        Alternative input config's are */
    AFE_ATE_ADC_3(); /* Video Input 1: Cust EVB: 0 & 82 Ohm */

    /* We are not in any Clamping mode yet, so we must set one,
      otherwise, video won't centralise in a bus magnitude on the LA */
    GoIntoVoltageClampingMode();
    VDEC_Init();

    do
    {
        Lock();
    }while(!IsLocked());

    /* move into CurrentClampingMode */
    GoIntoAlwaysOnCurrentClampingMode(); 
    VIU_test(); 
    
    /* shouldn't get here */
    _task_block();
    


OnError:
    _time_delay (200L);
    _task_block();
}

