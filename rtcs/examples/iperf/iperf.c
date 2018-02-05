/*HEADER**********************************************************************
*
* Copyright (c) 2015, Freescale Semiconductor, Inc.
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

/*
 * Copyright (c) 2009, The Regents of the University of California, through
 * Lawrence Berkeley National Laboratory (subject to receipt of any required
 * approvals from the U.S. Dept. of Energy).  All rights reserved.
 */


#include <mqx.h>

#include "iperf_api.h"
#include "iperf_server_api.h"
#include "iperf_client_api.h"
#include "iperf_error.h"


int iperf_run(struct iperf_test *);

/**************************************************************************/

int32_t
iperf(int32_t argc, char **argv)
{
    struct iperf_test *test;

    test = iperf_new_test();
    if (!test) {
        iperf_error("create new test error");
        return(0);
    }
    iperf_defaults(test);	/* sets defaults */

    if (iperf_parse_arguments(test, argc, argv) < 0) {
        iperf_error("parameter error");
        usage_long();
        return(1);
    }

    if (iperf_run(test) < 0) {
        iperf_error("error");
        return(1);
    }

    iperf_free_test(test);


    return (0);
}

/**************************************************************************/
int
iperf_run(struct iperf_test * test)
{
    switch (test->role) {
        case 's':
            for (;;) {
                if (iperf_run_server(test) < 0) {
                    iperf_error("error");
                }
                iperf_reset_test(test);
            }
            break;
        case 'c':
            if (iperf_run_client(test) < 0) {
                iperf_error("error");
                return(1);
            }
            break;
        default:
            usage();
            break;
    }

    return (0);
}

