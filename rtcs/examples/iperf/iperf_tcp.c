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


#include "iperf.h"
#include "iperf_api.h"
#include "iperf_tcp.h"
#include "iperf_error.h"
#include "net.h"

/* iperf_tcp_recv
 *
 * receives the data for TCP
 */
int
iperf_tcp_recv(struct iperf_stream *sp)
{
    int result = 0;
    int size = sp->settings->blksize;

    result = Nread(sp->socket, sp->buffer, size, Ptcp);

    if (result < 0) {
        return (-1);
    }

    sp->result->bytes_received += result;
    sp->result->bytes_received_this_interval += result;

    return (result);
}


/* iperf_tcp_send 
 *
 * sends the data for TCP
 */
int
iperf_tcp_send(struct iperf_stream *sp)
{
    int result;
    int size = sp->settings->blksize;

    result = Nwrite(sp->socket, sp->buffer, size, Ptcp);

    if (result < 0) {
        return (-1);
    }

    sp->result->bytes_sent += result;
    sp->result->bytes_sent_this_interval += result;

    return (result);
}


/* iperf_tcp_accept
 *
 * accept a new TCP stream connection
 */
int
iperf_tcp_accept(struct iperf_test * test)
{
    int     s;
    int     rbuf = ACCESS_DENIED;
    char    cookie[COOKIE_SIZE];
    uint16_t len;
    struct sockaddr_in addr;

    len = sizeof(addr);
    if ((s = accept(test->listener, (struct sockaddr *) &addr, &len)) == RTCS_ERROR) {
        i_errno = IESTREAMCONNECT;
        return (-1);
    }

    if (Nread(s, cookie, COOKIE_SIZE, Ptcp) < 0) {
        i_errno = IERECVCOOKIE;
        return (-1);
    }

    if (strcmp(test->cookie, cookie) != 0) {
        if (Nwrite(s, (char*)&rbuf, sizeof(char), Ptcp) < 0) {
            i_errno = IESENDMESSAGE;
            return (-1);
        }
        shutdown(s, FLAG_ABORT_CONNECTION);
    }

    return (s);
}


/* iperf_tcp_listen
 *
 * start up a listener for TCP stream connections
 */
int
iperf_tcp_listen(struct iperf_test *test)
{
    int s, opt;
    struct addrinfo hints, *res;
    unsigned char option_tos = 0;
    char portstr[PORTSTRLEN];
    s = test->listener;

    if (test->no_delay || test->settings->mss || test->settings->socket_bufsize) {
        RTCS_FD_CLR(s, &test->read_set);
        shutdown(s, FLAG_ABORT_CONNECTION);
        if ((s = socket(test->settings->domain, SOCK_STREAM, 0)) == RTCS_ERROR) {
            i_errno = IESTREAMLISTEN;
            return (-1);
        }
        if (test->no_delay) {
            opt = 1;
            if (setsockopt(s, SOL_TCP, OPT_NO_NAGLE_ALGORITHM, &opt, sizeof(opt)) == RTCS_ERROR) {
                i_errno = IESETNODELAY;
                return (-1);
            }
            printf("      TCP NODELAY: on\n");
        }
        if ((opt = test->settings->socket_bufsize)) {
            if (setsockopt(s, SOL_TCP, OPT_RBSIZE, &opt, sizeof(opt)) == RTCS_ERROR) {
                i_errno = IESETBUF;
                return (-1);
            }
            if (setsockopt(s, SOL_TCP, OPT_TBSIZE, &opt, sizeof(opt)) == RTCS_ERROR) {
                i_errno = IESETBUF;
                return (-1);
            }
        }
                
        if (setsockopt(s, SOL_IP, RTCS_SO_IP_TX_TOS, &option_tos, sizeof(option_tos)) == RTCS_ERROR) {
            i_errno = IESETBUF;
            return (-1);
        }

        snprintf(portstr, PORTSTRLEN, "%d", test->server_port);
        _mem_zero(&hints, sizeof(hints));
        hints.ai_family = test->settings->domain;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        // XXX: Check getaddrinfo for errors!
        if (getaddrinfo(test->bind_address, portstr, &hints, &res) == RTCS_ERROR) {
            i_errno = IESTREAMLISTEN;
            return (-1);
        }

        if (bind(s, (struct sockaddr *) res->ai_addr, res->ai_addrlen) == RTCS_ERROR) {
            shutdown(s, FLAG_ABORT_CONNECTION);
            i_errno = IESTREAMLISTEN;
            return (-1);
        }

        freeaddrinfo(res);

        if (listen(s, 5) < 0) {
            i_errno = IESTREAMLISTEN;
            return (-1);
        }

        test->listener = s;
    }
    
    return (s);
}


/* iperf_tcp_connect
 *
 * connect to a TCP stream listener
 */
int
iperf_tcp_connect(struct iperf_test *test)
{
    int s, opt;
    struct addrinfo hints, *res;
    char portstr[PORTSTRLEN];
    unsigned char option_tos = 0;

    if ((s = socket(test->settings->domain, SOCK_STREAM, 0)) == RTCS_ERROR) {
        i_errno = IESTREAMCONNECT;
        return (-1);
    }
    
    if (test->bind_address) {
        _mem_zero(&hints, sizeof(hints));
        hints.ai_family = test->settings->domain;
        hints.ai_socktype = SOCK_STREAM;
        // XXX: Check getaddrinfo for errors!
        if (getaddrinfo(test->bind_address, NULL, &hints, &res) == RTCS_ERROR) {
            i_errno = IESTREAMCONNECT;
            return (-1);
        }

        if (bind(s, (struct sockaddr *) res->ai_addr, res->ai_addrlen) == RTCS_ERROR) {
            i_errno = IESTREAMCONNECT;
            return (-1);
        }

        freeaddrinfo(res);
    }

    /* Set socket options */
    if (test->no_delay) {
        opt = 1;
        if (setsockopt(s, SOL_TCP, OPT_NO_NAGLE_ALGORITHM, &opt, sizeof(opt)) == RTCS_ERROR) {
            i_errno = IESETNODELAY;
            return (-1);
        }
    }
    if ((opt = test->settings->socket_bufsize)) {
        if (setsockopt(s, SOL_TCP, OPT_RBSIZE, &opt, sizeof(opt)) != RTCS_OK) {
            i_errno = IESETBUF;
            return (-1);
        }
        if (setsockopt(s, SOL_TCP, OPT_TBSIZE, &opt, sizeof(opt)) != RTCS_OK) {
            i_errno = IESETBUF;
            return (-1);
        }
    }
    
    if (setsockopt(s, SOL_IP, RTCS_SO_IP_TX_TOS, &option_tos, sizeof(option_tos)) == RTCS_ERROR) {
        i_errno = IESETBUF;
        return (-1);
    }

    _mem_zero(&hints, sizeof(hints));
    hints.ai_family = test->settings->domain;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICHOST;
    snprintf(portstr, PORTSTRLEN, "%d", test->server_port);
    // XXX: Check getaddrinfo for errors!
    if (getaddrinfo(test->server_hostname, portstr, &hints, &res) == RTCS_ERROR) {
        i_errno = IESTREAMCONNECT;
        return (-1);
    }

    if (connect(s, (struct sockaddr *) res->ai_addr, res->ai_addrlen) == RTCS_ERROR) {
        i_errno = IESTREAMCONNECT;
        return (-1);
    }

    freeaddrinfo(res);

    /* Send cookie for verification */
    if (Nwrite(s, test->cookie, COOKIE_SIZE, Ptcp) < 0) {
        i_errno = IESENDCOOKIE;
        return (-1);
    }

    return (s);
}

