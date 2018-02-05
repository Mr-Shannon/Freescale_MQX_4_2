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
*   This file contains source code of the VDEC module driver
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <string.h>
#include "config.h"
#include "videoModules.h"



/*
  VDEC_DefaultConfig()
  Default initialization of the VDEC module.
*/
void VDEC_DefaultConfig(void)
{    
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x14*4)) = 0x10;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x13*4)) = 0x13;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x04*1)) = 0x34;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x02*4)) = 0x01;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x03*4)) = 0x18;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x04*4)) = 0x34;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x0f*4)) = 0x20;                   
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x49*4)) = 0x02;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x4a*4)) = 0x20;  
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x4b*4)) = 0x08;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x4c*4)) = 0x08;  
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x20*4)) = 0x20; 
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x1d*4)) = 0x90;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x33*4)) = 0xa0;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x3d*4)) = 0x41;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x40*4)) = 0x81;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x3a*4)) = 0x80;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x07*4)) = 0x02;
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x0c*4)) = 0x04; 
    *(uint32_t*)((uint32_t)VDEC_BASE_PTR+(0x3c*4)) = 0xFF;  
}


/* 
VDEC_Init()
Initialises the VDEC registers
This is just simple linear register setup code - there are no waits until bits flip
Returns: nothing

*/

void VDEC_Init(void)
{
    VDEC_DefaultConfig();
  
    /* These set the Hsync length between them. */
    VDEC_HACTS = 0x8A; 
    VDEC_HACTE = 0x04; 

    /* These set the Vsync length between them. */
    VDEC_VACTS = 0x33; 
    VDEC_VACTE = 0x00;

    /* set H shift */
    VDEC_HZPOS = 0x60;

    /* set V shift */
    VDEC_VRTPOS = 0x02;

    /* set V ignore start (decimal -32): 16 (HSync Ignore) */
    VDEC_HSIGS = 0xf8;

    /* set V ignore start (decimal 32) */
    VDEC_HSIGE = 0x18;

    /* set the vcr detect threshold high - Override VCR detect mode: automatic detections */
    VDEC_VSCON2 = 0;

    /* set the YC relative delay */
    VDEC_YCDEL = 0x90;

    /* set the start of the colourburst gate */
    VDEC_BRSTGT = 0x30; 

    /* turn up the colour with the new colour gain reg
       this is not one in order to convert U to Cb */
    VDEC_CBGN = 0xb4;
                
    /* setup the luma gain (contrast) */
    VDEC_CNTR = 0x80; 

    /* setup the signed black level register */
    VDEC_BRT = 0x00; 

    /* filter the standard detection
     enable the comb for the ntsc443 */
    VDEC_STDDBG = 0x23; 

    /* setup chroma kill thresh for no chroma */
    VDEC_CHBTH = 0xd0; 

    /* set chroma loop to wider BW
    no set it to normal BW */
    VDEC_YCDEL = 0x00; 
    VDEC_BLSCRCR = 0x51; 
    VDEC_BLSCRCB = 0x3f; 
    
    /* disable the active blanking */
    VDEC_VSCON1 = 0x00;
    
    
    /* setup the luma agc for automatic  gain. */
    VDEC_LMAGC2 = 0x5e; 
    
    /* setup chroma agc */
    VDEC_CHAGC2 = 0xA0;
    
    VDEC_SHPIMP = 0x00;         /* setup the loss of lock detector */

    /* setup the vsync block */
    VDEC_VSCON1 = 0x87; 
    
    
    /* set the vsync threshold */
    VDEC_VSSGTH = 0x35; /* length & no sig threshold */
     
    VDEC_MINTH = 0x40;
    
    VDEC_MANOVR = 0x20; /* stop it detecting SECAM i.e. override SECAM detection & force SECAM off
    but allow it to autodetect PAL and NTSC */

  
  /* this fixes the fine (1 pixel wide)
    45 degree diagonal black lines otherwise seen in areas of 75% saturated colour
    on both NTSC & PAL. This firmly disables the 3d comb filter, which separates the colour from luma. */
      
  /* Disable VDEC VCR detect mode to decrease sensitivity to noise */
    VDEC_VSCON2 = 4; /* Disable VCR detect */ 
       
} 

void Lock(void)
{
    /* camera will lock without this block. Sources with a smaller swing like DVD players, don't.*/
    unsigned char i = 0xf0; 
  
    AFE_CLMPDAT = i;
    _time_delay(40);
  
    /* Ramp Voltage offset down until we get lock */
    while (!(VDEC_VIDMOD & 0x00000002))
    {
        AFE_CLMPDAT = --i; 
        _time_delay(40);       
    }   
}

/* 
IsLocked()

Tests VDEC_VIDMOD.Hlocked & CH_Locked
was just VDEC_VIDMOD_havesignal_MASK

returns 0 or 1.
1 means Locked.
*/
uint32_t IsLocked(void)
{
    return (VDEC_VIDMOD & VDEC_VIDMOD_Hlocked_MASK);   
}
