/*
 * This file contains function prototypes for Vybrid-specific 
 * MCC library functions
 *
 * Copyright (C) 2014 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause License for this file can be found in the COPYING.BSD file
 * included with this distribution or at
 * http://opensource.org/licenses/BSD-3-Clause
 */

#ifndef __MCC_VF600__
#define __MCC_VF600__

#define MCC_VECTOR_NUMBER_INVALID     (0)

unsigned int mcc_get_cpu_to_cpu_vector(unsigned int);
void mcc_clear_cpu_to_cpu_interrupt(unsigned int);
void mcc_triger_cpu_to_cpu_interrupt(void);

#endif /* __MCC_VF600__ */
