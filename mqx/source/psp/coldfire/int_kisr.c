
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
* See license agreement file for full license terms including other restrictions.
*****************************************************************************
*
* Comments:
*
*   This file contains the function for installing a kernel level isr.
*
*
*END************************************************************************/

#include "mqx_inc.h"

#if MQX_USE_INTERRUPTS


/*!
 * \brief Installs the kernel ISR handler. The kernel ISR depends on the PSP.
 *
 * Some real-time applications need special event handling to occur outside the
 * scope of MQX. The need might arise that the latency in servicing an interrupt
 * be less than the MQX interrupt latency. If this is the case, an application can
 * use _int_install_kernel_isr() to bypass MQX and let the interrupt be serviced
 * immediately.
 * \n Because the function returns the previous kernel ISR, applications can
 * temporarily install an ISR or chain ISRs so that each new one calls the one
 * installed before it.
 * \n A kernel ISR must save the registers that it needs and must service the
 * hardware interrupt. When the kernel ISR is finished, it must restore the
 * registers and perform a return-from-interrupt instruction.
 * \n A kernel ISR cannot call MQX functions. However, it can put data in global
 * data, which a task can access.
 *
 * \note The function is not available for all PSPs.
 *
 * \param[in] vector  Vector where the ISR is to be installed.
 * \param[in] isr_ptr Pointer to the ISR to install into the vector table.
 *
 * \return Pointer to the previous kernel ISR for the vector (Success.).
 * \return NULL
 *
 * \warning On failure, calls _task_set_error() to set one of the following task
 * error codes:
 * \li MQX_INVALID_CONFIGURATION
 * \li MQX_INVALID_VECTORED_INTERRUPT
 *
 * \see _int_kernel_isr
 * \see _int_get_kernel_isr
 */
INT_KERNEL_ISR_FPTR _int_install_kernel_isr
(
      uint32_t             vector,
      INT_KERNEL_ISR_FPTR isr_ptr

)
{ /* Body */
#if !MQX_ROM_VECTORS
   _KLOGM(KERNEL_DATA_STRUCT_PTR kernel_data);
   INT_KERNEL_ISR_FPTR    old_isr_ptr;
   uint32_t                result_code = MQX_OK;
   uint32_t                vbr;
   uint32_t            *vbr_ptr;

   _KLOGM(_GET_KERNEL_DATA(kernel_data));
   _KLOGE3(KLOG_int_install_kernel_isr, vector, isr_ptr);

#if MQX_CHECK_ERRORS
   old_isr_ptr = NULL;

   if ( vector >= PSP_MAXIMUM_INTERRUPT_VECTORS ) {
      result_code = MQX_INVALID_VECTORED_INTERRUPT;
   } else {
#endif

      _PSP_GET_VBR(vbr);
      vbr_ptr =  (uint32_t *)vbr;
      old_isr_ptr = (INT_KERNEL_ISR_FPTR)vbr_ptr[vector];
      vbr_ptr[vector] = (uint32_t)isr_ptr;

#if MQX_CHECK_ERRORS
   } /* Endif */

   /* Set result code and return result. */
   _task_set_error(result_code);
#endif

   _KLOGX3(KLOG_int_install_kernel_isr, old_isr_ptr, result_code);

   return (old_isr_ptr);
#else

#if MQX_CHECK_ERRORS
   /* Set result code and return result. */
   _task_set_error(MQX_INVALID_CONFIGURATION);
#endif

   return NULL;
#endif

} /* Endbody */

#endif
/* EOF */
