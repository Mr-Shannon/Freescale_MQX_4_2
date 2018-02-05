/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
* Copyright 1989-2008 ARC International
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
*   This file contains the default initialization record for the NAND
*   flash.
*
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "nandflash_wl.h"
#include "nfc_wl.h"
#include "nfc_wl_dma.h"

extern const NANDFLASH_INIT_STRUCT _bsp_nandflash_init;

const NANDFLASH_WL_INIT_STRUCT _bsp_nandflash_wl_init =
{
   &_bsp_nandflash_init,
#if NANDWL_USE_DMA
   &_nandflash_nfc_wl_dma_devif
#else
   &_nandflash_nfc_wl_devif
#endif
};

/* EOF */
