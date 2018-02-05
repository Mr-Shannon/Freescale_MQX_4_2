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
#include "iperf_udp.h"
#include "iperf_error.h"
#include "iperf_util.h"
#include "itimer.h"
#include "net.h"


/* iperf_udp_recv
 *
 * receives the data for UDP
 */
int
iperf_udp_recv(struct iperf_stream *sp)
{
    int       result;
    int       size = sp->settings->blksize;
    int       sec, usec, pcount;
    int    d = 0;
    struct timeval sent_time, arrival_time, transit;

    result = Nread(sp->socket, sp->buffer, size, Pudp);

    if (result < 0) {
        return (-1);
    }

    sp->result->bytes_received += result;
    sp->result->bytes_received_this_interval += result;

    _mem_copy(sp->buffer, &sec, sizeof(sec));
    _mem_copy(sp->buffer+4, &usec, sizeof(usec));
    _mem_copy(sp->buffer+8, &pcount, sizeof(pcount));
    sec = ntohl(sec);
    usec = ntohl(usec);
    pcount = ntohl(pcount);
    sent_time.tv_sec = sec;
    sent_time.tv_msec = usec;

    /* Out of order packets */
    if (pcount >= sp->packet_count + 1) {
        if (pcount > sp->packet_count + 1) {
            sp->cnt_error += (pcount - 1) - sp->packet_count;
        }
        sp->packet_count = pcount;
    } else {
        sp->outoforder_packets++;
        printf("OUT OF ORDER - incoming packet = %d and received packet = %d AND SP = %d\n", pcount, sp->packet_count, sp->socket);
    }

    /* jitter measurement */
    gettimeofday(&arrival_time, NULL);

    timeval_diff(&sent_time, &arrival_time, &transit);
    d = transit.tv_sec - sp->prev_transit;
    if (d < 0)
        d = -d;
    sp->prev_transit = transit.tv_sec;
    // XXX: This is NOT the way to calculate jitter
    //      J = |(R1 - S1) - (R0 - S0)| [/ number of packets, for average]
    sp->jitter += (d - sp->jitter) / 16.0;

    return (result);
}


/* iperf_udp_send
 *
 * sends the data for UDP
 */
int
iperf_udp_send(struct iperf_stream *sp)
{
    size_t   result = 0;
    int64_t   dtargus;
    int64_t   adjustus = 0;
    uint64_t  sec, msec, pcount;
    int       size = sp->settings->blksize;
    struct timeval before, after;


        dtargus = (int64_t) (sp->settings->blksize) * SEC_TO_US * 8;
        dtargus /= sp->settings->rate;
      
        gettimeofday(&before, 0);

        ++sp->packet_count;
        sec = htonl(before.tv_sec);
        msec = htonl(before.tv_msec);
        pcount = htonl(sp->packet_count);

        _mem_copy(&sec, sp->buffer, sizeof(sec));
        _mem_copy(&msec, sp->buffer+4, sizeof(msec));
        _mem_copy(&pcount, sp->buffer+8, sizeof(pcount));
        
        result = Nwrite(sp->socket, sp->buffer, size, Pudp);
 
        if (result < 0)
            return (-1);

        sp->result->bytes_sent += result;
        sp->result->bytes_sent_this_interval += result;

        gettimeofday(&after, 0);

        adjustus = dtargus;
        adjustus += (before.tv_sec - after.tv_sec) * SEC_TO_US;
        adjustus += (before.tv_msec - after.tv_msec);

        if (adjustus > 0) {
            dtargus = adjustus;
        }

        //if (update_timer(sp->send_timer, 0, dtargus) < 0)
            //return (-1);

    //}


    return (result);
}


/**************************************************************************/

/* iperf_udp_accept
 *
 * accepts a new UDP connection
 */
int
iperf_udp_accept(struct iperf_test *test)
{
    struct sockaddr_in sa_peer;
    int       buf;
    uint16_t len;
    int      s;

    s = test->prot_listener;

    len = sizeof sa_peer;
    if ((recvfrom(test->prot_listener, &buf, sizeof(buf), 0, (struct sockaddr *) &sa_peer, &len)) < 0) {
        i_errno = IESTREAMACCEPT;
        return (-1);
    }
    
    if (connect(s, (struct sockaddr *) &sa_peer, len) == RTCS_SOCKET_ERROR) {
        i_errno = IESTREAMACCEPT;
        return (-1);
    }

    test->prot_listener = netannounce(test->settings->domain, Pudp, test->bind_address, test->server_port);
    if (test->prot_listener == RTCS_SOCKET_ERROR) {
        //shutdown(test->, FLAG_ABORT_CONNECTION);
        i_errno = IESTREAMLISTEN;
        return (-1);
    }

    RTCS_FD_SET(test->prot_listener, &test->read_set);
    test->max_fd = (test->max_fd < test->prot_listener) ? test->prot_listener : test->max_fd;

    /* Let the client know we're ready "accept" another UDP "stream" */
    if (send(s, &buf, sizeof(buf), 0) < 0) {
        i_errno = IESTREAMWRITE;
        return (-1);
    }

    return (s);
}


/* iperf_udp_listen
 *
 * start up a listener for UDP stream connections
 */
int
iperf_udp_listen(struct iperf_test *test)
{
    int s;

    if ((s = netannounce(test->settings->domain, Pudp, test->bind_address, test->server_port)) == RTCS_SOCKET_ERROR) {
        i_errno = IESTREAMLISTEN;
        return (-1);
    }

    return (s);
}


/* iperf_udp_connect
 *
 * connect to a TCP stream listener
 */
int
iperf_udp_connect(struct iperf_test *test)
{
    int s, buf;

    if ((s = netdial(test->settings->domain, Pudp, test->bind_address, test->server_hostname, test->server_port)) == RTCS_SOCKET_ERROR) {
        i_errno = IESTREAMCONNECT;
        return (-1);
    }

    /* Write to the UDP stream to give the server this stream's credentials */
    if (send(s, &buf, sizeof(buf), 0) < 0) {
        // XXX: Should this be changed to IESTREAMCONNECT? 
        i_errno = IESTREAMWRITE;
        return (-1);
    }
    /* Wait until the server confirms the client UDP write */
    // XXX: Should this read be TCP instead?

    return (s);
}


/* iperf_udp_init
 *
 * initializer for UDP streams in TEST_START
 */
int
iperf_udp_init(struct iperf_test *test)
{
    int64_t dtargus;
    struct iperf_stream *sp;

    /* Calculate the send delay needed to hit target bandwidth (-b) */
    dtargus = (int64_t) test->settings->blksize * SEC_TO_US * 8;
    dtargus /= test->settings->rate;


    SLIST_FOREACH(sp, &test->streams, streams) {
        sp->send_timer = new_timer(dtargus / SEC_TO_US, dtargus % SEC_TO_US);
        if (sp->send_timer == NULL)
            return (-1);
    }

    return (0);
}
