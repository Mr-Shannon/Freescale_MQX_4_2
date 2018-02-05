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

/* netdial and netannouce code comes from libtask: http://swtch.com/libtask/
 * Copyright: http://swtch.com/libtask/COPYRIGHT
*/

#include <rtcs.h>

#include "iperf.h"
#include "net.h"
#include "itimer.h"
#include "iperf_error.h"


/* make connection to server */
int
netdial(int domain, int proto, char *local, char *server, int port)
{
    int s;
    struct addrinfo hints, *res;
    unsigned char option_tos = 0;

    s = socket(domain, proto, 0);
    if (s == RTCS_SOCKET_ERROR) {
        return (-1);
    }
    
    if (local) {
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = domain;
        hints.ai_socktype = proto;

        // XXX: Check getaddrinfo for errors!
        if (getaddrinfo(local, NULL, &hints, &res) != 0)
            return (-1);

        if (bind(s, (struct sockaddr *) res->ai_addr, res->ai_addrlen) != RTCS_OK)
            return (-1);

        freeaddrinfo(res);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = domain;
    hints.ai_socktype = proto;
    hints.ai_flags = AI_NUMERICHOST;

    // XXX: Check getaddrinfo for errors!
    if (getaddrinfo(server, NULL, &hints, &res) != 0)
        return (-1);

    ((struct sockaddr_in *) res->ai_addr)->sin_port = port;
       
    if (setsockopt(s, SOL_IP, RTCS_SO_IP_TX_TOS, &option_tos, sizeof(option_tos)) != RTCS_OK) {
        i_errno = IESETBUF;
        return (-1);
    }

    if (connect(s, (struct sockaddr *) res->ai_addr, res->ai_addrlen) != RTCS_OK) {
        return (-1);
    }

    freeaddrinfo(res);

    return (s);
}

/***************************************************************/

int
netannounce(int domain, int proto, char *local, int port)
{
    uint32_t s;
    struct addrinfo hints, *res;
    char portstr[PORTSTRLEN];

    s = socket(domain, proto, 0);
    if (s == RTCS_SOCKET_ERROR) {
        return (-1);
    }
    
    snprintf(portstr, PORTSTRLEN, "%d", port);
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = domain;
    hints.ai_socktype = proto;
    hints.ai_flags = AI_PASSIVE;
    // XXX: Check getaddrinfo for errors!
    if (getaddrinfo(local, portstr, &hints, &res) != 0)
        return (-1); 

    if (bind(s, (struct sockaddr *) res->ai_addr, res->ai_addrlen) != RTCS_OK) {
        shutdown(s, FLAG_ABORT_CONNECTION);
        return (-1);
    }

    freeaddrinfo(res);
    
    if (proto == SOCK_STREAM) {
        if (listen(s, 5) < 0) {
            return (-1);
        }
    }

    return (s);
}


/*******************************************************************/
/* reads 'count' byptes from a socket  */
/********************************************************************/

int
Nread(int fd, char *buf, int count, int prot)
{
    register int r;
    register int nleft = count;

    while (nleft > 0) {
        r = recv(fd, buf, nleft, 0);
        if (r < 0) {
                return NET_HARDERROR;
        } else if (r == 0)
            break;

        nleft -= r;
        buf += r;
    }
    return count - nleft;
}


/*
 *                      N W R I T E
 *
 * XXX: After updating this function to use read/write, the only difference between
 *      TCP and UDP is that udp handles ENOBUFS. Should we merge the two?
 */

int
Nwrite(int fd, char *buf, int count, int prot)
{
    register size_t r;
    register size_t nleft = count;

    while (nleft > 0) {
	r = send(fd, buf, nleft, 0);
	if (r == RTCS_ERROR)
           return count - nleft;
        
        else if (r == 0)
	    return NET_SOFTERROR;
	nleft -= r;
	buf += r;
    }
    return count;
}

/*************************************************************************/

/**
 * getsock_tcp_mss - Returns the MSS size for TCP
 *
 */

int
getsock_tcp_mss(int inSock)
{

    return 0;
}


