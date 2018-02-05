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


#define BASE_GFX_MEM    0x3f400000U         /*  Memory address to store image from  
                                                from video-subsystem module */


#define IMAGE_ADDRESS   BASE_GFX_MEM
#define IMAGE_HEIGHT    340
#define IMAGE_WIDTH     720

#define LAYER_HEIGHT    340     /* DCU layer heigh */
#define LAYER_WIDTH     720     /* DCU layer width */

#define LAYER_OFFSET_X  60      /* horizontal offset for DCU layer */
#define LAYER_OFFSET_Y  90      /* vertical offset for DCU layer */

#define IMAGE_SIZE_IN_PIXELS (IMAGE_HEIGHT*IMAGE_WIDTH)
