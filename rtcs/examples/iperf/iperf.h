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
   Copyright (c) 2009, The Regents of the University of California, through
   Lawrence Berkeley National Laboratory (subject to receipt of any required
   approvals from the U.S. Dept. of Energy).  All rights reserved.
*/

#ifndef __IPERF_H
#define __IPERF_H

#include <rtcs.h>
#include <mqx.h>
#include <fio.h>

#include "iqueue.h"
#include "itimer.h"

int32_t
iperf(int32_t argc, char *argv[]);

typedef uint64_t iperf_size_t;

struct iperf_interval_results
{
    iperf_size_t bytes_transferred; /* bytes transfered in this interval */
    struct timeval interval_start_time;
    struct timeval interval_end_time;
    struct timeval interval_duration;
    char *tcpInfo;	/* just a placeholder */
    struct iperf_interval_results *next;
    void     *custom_data;
};

struct iperf_stream_result
{
    iperf_size_t bytes_received;
    iperf_size_t bytes_sent;
    iperf_size_t bytes_received_this_interval;
    iperf_size_t bytes_sent_this_interval;
    struct timeval start_time;
    struct timeval end_time;
    struct iperf_interval_results *interval_results;      // head of list
    struct iperf_interval_results *last_interval_results; // end of list
    void     *data;
};

#define COOKIE_SIZE 37              /* size of an ascii uuid */
struct iperf_settings
{
    int       domain;               /* AF_INET or AF_INET6 */
    int       socket_bufsize;       /* window size for TCP */
    int       blksize;              /* size of read/writes (-l) */
    uint64_t  rate;                 /* target data rate, UDP only */
    int       mss;                  /* for TCP MSS */
    int       ttl;                  /* IP TTL option */
    int       tos;                  /* type of service bit */
    iperf_size_t bytes;             /* number of bytes to send */
    char      unit_format;          /* -f */
};

struct iperf_stream
{
    /* configurable members */
    int       local_port;
    int       remote_port;
    int       socket;
    int       id;
	/* XXX: is settings just a pointer to the same struct in iperf_test? if not, 
		should it be? */
    struct iperf_settings *settings;	/* pointer to structure settings */

    /* non configurable members */
    struct iperf_stream_result *result;	/* structure pointer to result */
    struct timer *send_timer;
    char      *buffer;		/* data to send */

    /*
     * for udp measurements - This can be a structure outside stream, and
     * stream can have a pointer to this
     */
    int       packet_count;
    double    jitter;
    int    prev_transit;
    int       outoforder_packets;
    int       cnt_error;
    uint64_t  target;

    struct sockaddr local_addr;
    struct sockaddr remote_addr;

    int       (*rcv) (struct iperf_stream * stream);
    int       (*snd) (struct iperf_stream * stream);

    SLIST_ENTRY(iperf_stream) streams;

    void     *data;
};

struct iperf_test;

struct protocol {
    int       id;
    char      *name;
    int       (*i_accept)(struct iperf_test *);
    int       (*i_listen)(struct iperf_test *);
    int       (*i_connect)(struct iperf_test *);
    int       (*send)(struct iperf_stream *);
    int       (*recv)(struct iperf_stream *);
    int       (*init)(struct iperf_test *);
    SLIST_ENTRY(protocol) protocols;
};

struct iperf_test
{
    char      role;                             /* c' lient or 's' erver */
    struct protocol *protocol;
    char      state;
    char     *server_hostname;                  /* -c option */
    char     *bind_address;                     /* -B option */
    int       server_port;
    int       duration;                         /* total duration of test (-t flag) */

    int       ctrl_sck;
    int       listener;
    int       prot_listener;

    /* boolean variables for Options */
    int       daemon;                           /* -D option */
    int       no_delay;                         /* -N option */
    int       output_format;                    /* -O option */
    int       print_mss;                        /* -m option */
    int       reverse;                          /* -R option */
    int       v6domain;                         /* -6 option */
    int	      verbose;                          /* -V option - verbose mode */

    /* Select related parameters */
    int       max_fd;
    rtcs_fd_set    read_set;                         /* set of read sockets */
    rtcs_fd_set    write_set;                        /* set of write sockets */

    /* Interval related members */ 
    int    stats_interval;
    int    reporter_interval;
    void      (*stats_callback) (struct iperf_test *);
    void      (*reporter_callback) (struct iperf_test *);
    struct timer *timer;
    struct timer *stats_timer;
    struct timer *reporter_timer;


    int       num_streams;                      /* total streams in the test (-P) */

    iperf_size_t bytes_sent;
    char      cookie[COOKIE_SIZE];
    SLIST_HEAD(slisthead, iperf_stream) streams;
    struct iperf_settings *settings;

    SLIST_HEAD(plisthead, protocol) protocols;

    /* callback functions */
    void      (*on_new_stream)(struct iperf_stream *);
    void      (*on_test_start)(struct iperf_test *);
    void      (*on_connect)(struct iperf_test *);
    void      (*on_test_finish)(struct iperf_test *);
};

#define Ptcp SOCK_STREAM
#define Pudp SOCK_DGRAM

#define PSTRLEN 256
#define BUFLEN  128
#define PORTSTRLEN 6

enum
{
    /* default settings */
    PORT = 5201,  /* default port to listen on (don't use the same port as iperf2) */
    uS_TO_NS = 1000,
    SEC_TO_US = 1000000,
    RATE = 1024 * 1024, /* 1 Mbps */
    DURATION = 10, /* seconds */
    DEFAULT_UDP_BLKSIZE = 1450, /* 1 packet per ethernet frame, IPV6 too */
    DEFAULT_TCP_BLKSIZE = 2 * 1024,  /* default read/write block size */
    DEFAULT_SOCK_SIZE = 4 * 1024,

    /* other usefull constants */
    TEST_START = 1,
    TEST_RUNNING = 2,
    RESULT_REQUEST = 3,
    TEST_END = 4,
    STREAM_BEGIN = 5,
    STREAM_RUNNING = 6,
    STREAM_END = 7,
    ALL_STREAMS_END = 8,
    PARAM_EXCHANGE = 9,
    CREATE_STREAMS = 10,
    SERVER_TERMINATE = 11,
    CLIENT_TERMINATE = 12,
    EXCHANGE_RESULTS = 13,
    DISPLAY_RESULTS = 14,
    IPERF_START = 15,
    IPERF_DONE = 16,
    ACCESS_DENIED = -1,
};

#define SEC_TO_NS 1000000000	/* too big for enum on some platforms */
#define MAX_RESULT_STRING 4096
#define INET6_ADDRSTRLEN             (48)

/* constants for command line arg sanity checks
*/
#define MB 1024 * 1024
#define MAX_TCP_BUFFER 128 * MB
#define MAX_BLOCKSIZE MB
#define MAX_INTERVAL 60
#define MAX_TIME 3600
#define MAX_MSS 9 * 1024
#define MAX_STREAMS 5

#endif

