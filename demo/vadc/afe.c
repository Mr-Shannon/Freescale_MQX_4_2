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
*   This file contains source code of the AFE module driver
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include "config.h"
#include "videoModules.h"


/*  AFE_defaultConfig()
    Default initialization of the AFE module.
*/
void AFE_DefaultConfig(void)
{
    *(uint32_t*)((uint32_t)AFE_BASE_PTR+(0x00000420)) = 0x25;
    *(uint32_t*)((uint32_t)AFE_BASE_PTR+(0x00000430)) = 0x05;
    *(uint32_t*)((uint32_t)AFE_BASE_PTR+(0x0000042C)) = 0x0f;    
    *(uint32_t*)((uint32_t)AFE_BASE_PTR+(0x00000440)) = 0x10;
    *(uint32_t*)((uint32_t)AFE_BASE_PTR+(0x00000444)) = 0x05;
}


/* AFE_Init() 
The AFE Driver Init routine, top level.
Defers Setting the Initial Tuning of the Comparator timing until after the call - this is done in main() 
Assumes that the clock frequency to the AFE & VDEC is already set to 133 MHz - done in Sysinit()
*/
void AFE_Init(void)
{
    AFE_DefaultConfig();
  
    AFE_ATE_IDD_3();

    _time_delay(200);  

    AFE_ATE_IDD_6(); /* start data_clk */
            
    /* set current controlled clamping, always on, low current */
    AFE_CLAMP = 0x11; /* bit 5 Enable low current mode, 
                                      set bit1 to 0: iClamping & 
                                      bit 0 is an enable - always has to be set 
                                      */
    
    AFE_CLMPAMP = 0x00; /* Bit 3 & 4 - can change how we map the 5 bit Albacore to 8bit Anacatum DAC. i.e. can cntrl gain in x2 steps .
     Bottom 3 bits of AFE_CLMPAMP set the 3 bits missing - best to set them to 0's  */
    
} 

/* voltage "clamping" - drive current into an onchip fixed R to generate a bias voltage
  you cannot run VADC for long in this mode, as its too dependant on the input signal offset     */
void GoIntoVoltageClampingMode(void)
{
    AFE_CLAMP = 0x07; /* set bit1 to 1:vClamp, 0=iClamp */
                         
    AFE_CLMPAMP = 0x60; /* 60 enable register override for current & clamp direction control bits */
    
    /* set voltage bias towards the top of the range, via the current through an onchip resistor */
    AFE_CLMPDAT = 0xF0; 
}

/* less noise than PulsedCurrentClampingMode */
void GoIntoAlwaysOnCurrentClampingMode(void)
{
    AFE_CLAMP = 0x15; 
    AFE_CLMPDAT = 0x08;
    /* bkpt to look for the lock, then...  */
    AFE_CLMPAMP = 0x00;
}

void AFE_ATE_ADC_3(void)
{  
    /* channel selectors */
    AFE_INPFLT = 0x12; /* differs from AFE_ATE_ADC_0 only in Input selector & input pull-downs // [KM] */
    AFE_OFFDRV = 0xd0;
}


/*******************************************************************************
AFE_ATE_IDD_3: Register initialisation
adapted for reversing camera demo.
Normally used to Measure power supply currents 
to pads ACAFE_VDD_IO and ACAFE_VDD_CORE.
*******************************************************************************/
void AFE_ATE_IDD_3(void)
{
    AFE_PDBUF     = 0x07;   /* Activate power to IP block, bandgap */
    AFE_PDADC     = 0x1f;   /* activate clamp circuitry, ADC */
    AFE_PDSARH    = 0x01;   /* Activate ADC */
    AFE_PDSARL    = 0xff;   /* Activate ADC */
    AFE_PDADCRFH  = 0x01;   /* Activate ADC */
    AFE_PDADCRFL  = 0xff;   /* Activate ADC */
    AFE_ADCGN     = 0x0c;   /* ADC gain setting */
    AFE_INPBUF    = 0x35;   /* Enable common mode input buffer, differential output buff 
                               connect clam node to analog input, select 15 MHz low-pass filter*/
    AFE_INPFLT    = 0x0a;   /* Enable low pass filter, analog input enable */
    AFE_ADCDGN    = 0x40;   /* ADC digital gain */
    AFE_OFFDRV    = 0xe0;   /* Input pull-down enable */
    AFE_ASAREG    = 0x08;   /* Enable sample acquisition to 9 */
    AFE_BGREG     = 0x00;   /* Matching band gap trim level to fuses */

       
    /* additional steps to allow the camera to work */
    AFE_ASCREG = 0x01;          /*  Turn off offset calibration */
 }


/*******************************************************************************
AFE_ATE_IDD_6: Register initialisation
adapted for reversing camera demo.
*******************************************************************************/
void AFE_ATE_IDD_6(void)
{
    /* Run start-up sequence described in test IDD_3 */
    AFE_BLCREG = 0x00;

    AFE_BLCREG = 0x02;
    /* data_clk is not generated until you initiate an acquisition/calibration 
      (by writing register AFE_BLCREG */
}


