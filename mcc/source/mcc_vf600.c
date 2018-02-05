/*
 * This file contains Vybrid-specific functions of the MCC library
 *
 * Copyright (C) 2014 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause License for this file can be found in the COPYING.BSD file
 * included with this distribution or at
 * http://opensource.org/licenses/BSD-3-Clause
 */

#include "mcc_vf600.h"
#include "mcc_mqx.h"

/* This field contains CPU-to-CPU interrupt vector numbers for all device cores */
static const unsigned int mcc_cpu_to_cpu_vectors[] = { GIC_CPU_to_CPU_int0, NVIC_CPU_to_CPU_int0 };

/*!
 * \brief This function gets the CPU-to-CPU vector number for the particular core.
 *
 * Platform-specific inter-CPU vector numbers for each core are defined in the mcc_cpu_to_cpu_vectors[] field.
 *
 * \param[in] core Core number.
 *
 * \return vector number for the particular core
 * \return MCC_VECTOR_NUMBER_INVALID (vector number for the particular core number not found)
 */
unsigned int mcc_get_cpu_to_cpu_vector(unsigned int core)
{
    if (core < (sizeof(mcc_cpu_to_cpu_vectors)/sizeof(mcc_cpu_to_cpu_vectors[0]))) {
        return  mcc_cpu_to_cpu_vectors[core];

    }
    return MCC_VECTOR_NUMBER_INVALID;
}

/*!
 * \brief This function clears the CPU-to-CPU interrupt flag for the particular core.
 *
 * Implementation is platform-specific.
 *
 * \param[in] core Core number.
 */
void mcc_clear_cpu_to_cpu_interrupt(unsigned int core)
{
    if(core == 0) {
        /* clear the flag in the MSCM_IRCP0IR register */
        MSCM_IRCP0IR = MSCM_IRCP0IR_INT0_MASK;
    }
    else if(core == 1) {
        /* clear the flag in the MSCM_IRCP1IR register */
        MSCM_IRCP1IR = MSCM_IRCP1IR_INT0_MASK;
   }
}

/*!
 * \brief This function triggers the CPU-to-CPU interrupt.
 *
 * Platform-specific software triggering the inter-CPU interrupts.
 */
void mcc_triger_cpu_to_cpu_interrupt(void)
{
    /* set TLF filed of the MSCM_IRCPGIR to assert directed CPU interrupts for all processors except the requesting core */
    MSCM_IRCPGIR = MSCM_IRCPGIR_TLF(1) | MSCM_IRCPGIR_INTID(0);
}
