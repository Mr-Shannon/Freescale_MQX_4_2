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
*   
*
*END************************************************************************/


/* AFE module driver */
void AFE_DefaultConfig(void);
void AFE_Init(void);
void AFE_ATE_IDD_6(void);
void AFE_ATE_IDD_3(void);
void AFE_ATE_ADC_3(void);
void GoIntoVoltageClampingMode(void);
void GoIntoAlwaysOnCurrentClampingMode(void);
void TuneComparatorTiming(void);

/* VDEC module driver */
void VDEC_DefaultConfig(void);
void VDEC_Init(void);
void Lock(void);
uint32_t IsLocked(void);

/* VIU module driver */
void VIU_isr(void *data);
void VIU_test(void);
