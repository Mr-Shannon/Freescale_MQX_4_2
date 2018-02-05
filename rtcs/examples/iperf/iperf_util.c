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

/* iperf_util.c
 *
 * Iperf utility functions
 *
 */

#include "iperf.h"
#include "iperf_util.h" 


/* get_uuid
 *
 * Generate and return a UUID string
 *
 * Iperf uses this function to create test "cookies" which
 * server as unique test identifiers. These cookies are also
 * used for the authentication of stream connections.
 */

void
get_uuid(char *temp)
{

}


/* is_closed
 *
 * Test if the file descriptor fd is closed.
 * 
 * Iperf uses this function to test whether a TCP stream socket
 * is closed, because accepting and denying an invalid connection
 * in iperf_tcp_accept is not considered an error.
 */

int
is_closed(int fd)
{
    rtcs_fd_set readset;

    RTCS_FD_ZERO(&readset);
    RTCS_FD_SET(fd, &readset);

    if (select(1 , NULL, &readset, NULL, 0) < 0) {
            return (1);
    }
    return (0);
}

int gettimeofday(struct timeval *tv, void* x){

  TIME_STRUCT     mqx_time;
  
  
 _time_get(&mqx_time);
 
 tv->tv_sec = mqx_time.SECONDS;
 tv->tv_msec = mqx_time.MILLISECONDS;
 
  return 0;
}
