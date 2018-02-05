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
*   This file contains source code of the VIU3 module driver
*
*END************************************************************************/



#include <mqx.h>
#include <bsp.h>
#include "config.h"

/******************************************************************************
* Global variables
******************************************************************************/

/* synchronization sempahore */
LWSEM_STRUCT isr_sem;

/*
* viu interrupt handler 
*/
void VIU_isr(void *data)
{
      /* disable VSYNC and DMA_END interrupts and clear VSYNC, DMA_END int flags */
     VIU3_SCR = VIU3_SCR & ~((1 << VIU3_SCR_VSYNC_EN_SHIFT) | (1 << VIU3_SCR_DMA_END_EN_SHIFT) | \
                             (1 << VIU3_SCR_VSYNC_IRQ_SHIFT) | (1 << VIU3_SCR_DMA_END_IRQ_SHIFT)); 
      
    _lwsem_post(&isr_sem);      
}


/*      
  Simplified/brief VIUtest
*/
void VIU_test(void) 
{
    uint32_t mode;
         
    
    VIU3_SCR |= 1 << VIU3_SCR_SOFT_RESET_SHIFT; /* reset module */
    
    /* input format YUV888 from VDEC, 720x288, image in OCRAM */
    mode = 0x82000006; /* set mode bits here: 32bit output, YUV2RGB, & output Format 3'b011: {B, G, R, alpha}, which  matches DCU1 - see ConfigureDCU1Layers */
    
    /* Set Input Data format  */
    VIU3_EXT_CONFIG = 0x003C;     /* Big endian 64 AHB bus, Input format 001 24bit parallel YUV, DE_VALID = 0 i.e. 
                                  DE IS valid, input format = 1 (YUV888), polarities:
                                  PCLK, VSYNC, HSYNC = active low,  DE = active high */
        	    
    VIU3_INVSZ = IMAGE_HEIGHT << 16 | (IMAGE_WIDTH + 0);    
    VIU3_VID_SIZE = IMAGE_HEIGHT << 16|(IMAGE_WIDTH + 0);    
    VIU3_DMA_ADDR = IMAGE_ADDRESS; 
    VIU3_DMA_INC = 0; /* no video deinterlace - fields land on top of each other 
                      - no separation of even & odd - 720@16bpp = 1440bytes */
     
    
    _lwsem_create(&isr_sem, 0);
    
    /* install VIU interrupt to interrupt table */
    if( !_int_install_isr(GIC_VIU, VIU_isr, NULL))
    {
        _task_block();
    }
    
    /* install BSP VIU interrupt */
    if (MQX_OK != _bsp_int_init(GIC_VIU, 2, 0, TRUE) )
    {
        _task_block();
    }
       
    /*  ID the Alpha field */
    VIU3_ALPHA = (VIU3_ALPHA & ~(VIU3_ALPHA_ALPHA_MASK << VIU3_ALPHA_ALPHA_SHIFT)) |\
      ((0xfd << VIU3_ALPHA_ALPHA_SHIFT) & (VIU3_ALPHA_ALPHA_MASK << VIU3_ALPHA_ALPHA_SHIFT));     
      
    /* clear VSYNC_IRQ and DMA_END_IRQ */
    VIU3_SCR = 0x00120000 | mode | (1 << VIU3_SCR_VSYNC_EN_SHIFT);

    while(1) /* comment out the while(1) to only grab the first field and stop */
    {       
        /* wait for VSYNC interrupt */
        _lwsem_wait(&isr_sem);
      
        /* Detect end of DMA after Vsync start: 
           now in blanking period - set DMA_ACT & start DMA */
        VIU3_SCR = 0x08000000 | mode | (1 << VIU3_SCR_DMA_END_EN_SHIFT);
        
        /* wait for DMA_END interrupt */
        _lwsem_wait(&isr_sem);        

        /* clear interrupts flags and enable VSYNC interrupt */
        VIU3_SCR = 0x00120000 | mode | (1 << VIU3_SCR_VSYNC_EN_SHIFT); 
    }
} /* Simplified VIUtest */
