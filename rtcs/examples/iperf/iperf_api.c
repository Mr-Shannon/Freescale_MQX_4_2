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
#include <shell.h>
#include <stdlib.h>


#include "net.h"
#include "iperf.h"
#include "iperf_api.h"
#include "iperf_udp.h"
#include "iperf_tcp.h"
#include "iperf_error.h"
#include "itimer.h"

#include "units.h"
#include "iperf_util.h"
#include "ilocale.h"


/*************************** Print usage functions ****************************/

void
usage()
{
    fprintf(stderr, usage_short);
}


void
usage_long()
{
    fprintf(stderr, usage_long1);
    fprintf(stderr, usage_long2);
}


/********************** Get/set test protocol structure ***********************/

struct protocol *
get_protocol(struct iperf_test *test, int prot_id)
{
    struct protocol *prot;

    SLIST_FOREACH(prot, &test->protocols, protocols) {
        if (prot->id == prot_id)
            break;
    }

    if (prot == NULL)
        i_errno = IEPROTOCOL;

    return (prot);
}

int
set_protocol(struct iperf_test *test, int prot_id)
{
    struct protocol *prot = NULL;

    SLIST_FOREACH(prot, &test->protocols, protocols) {
        if (prot->id == prot_id) {
            test->protocol = prot;
            return (0);
        }
    }

    i_errno = IEPROTOCOL;

    return (-1);
}


/************************** Iperf callback functions **************************/

void
iperf_on_new_stream(struct iperf_stream *sp)
{
    connect_msg(sp);
}

void
iperf_on_test_start(struct iperf_test *test)
{
    if (test->verbose) {
        if (test->settings->bytes) {
            printf(test_start_bytes, test->protocol->name, test->num_streams,
                test->settings->blksize, test->settings->bytes);
        } else {
            printf(test_start_time, test->protocol->name, test->num_streams,
                test->settings->blksize, test->duration);
        }
    }
}

void
iperf_on_connect(struct iperf_test *test)
{
    char ipr[INET6_ADDRSTRLEN];
    struct sockaddr temp;
    uint16_t len;

    if (test->role == 'c') {
        printf("Connecting to host %s, port %d\n", test->server_hostname,
            test->server_port);
    } else {
        len = sizeof(temp);
        getpeername(test->ctrl_sck, (struct sockaddr *) &temp, &len);
        getnameinfo(&temp, len, ipr, sizeof(ipr), 0, 0, NI_NUMERICSERV);
        printf("Accepted connection from %s, port %d\n", ipr, ntohs(((struct sockaddr_in *) &temp)->sin_port)); 
    }
    if (test->verbose) {
        printf("      Cookie: %s\n", test->cookie);

    }
}

void
iperf_on_test_finish(struct iperf_test *test)
{
    if (test->verbose) {
        printf("Test Complete. Summary Results:\n");
    }
}


/******************************************************************************/

int
iperf_parse_arguments(struct iperf_test *test, int argc, char **argv)
{
    SHELL_GETOPT_CONTEXT       gopt_context;
    int ch;

    Shell_getopt_init(&gopt_context);
    
    while ((ch = Shell_getopt(argc, argv, "c:p:st:uP:B:b:l:w:i:n:mRNTvh6VdM:f:", &gopt_context)) != -1) {
        switch (ch) {
            case 'c':
                if (test->role == 's') {
                    i_errno = IESERVCLIENT;
                    return (-1);
                } else {
                    test->role = 'c';
                    test->server_hostname = (char *) _mem_alloc(strlen(gopt_context.optarg)+1);
                    strncpy(test->server_hostname, gopt_context.optarg, strlen(gopt_context.optarg)+1);
                }
                break;
            case 'p':
                test->server_port = atoi(gopt_context.optarg);
                break;
            case 's':
                if (test->role == 'c') {
                    i_errno = IESERVCLIENT;
                    return (-1);
                } else {
                    test->role = 's';
                }
                break;
            case 't':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->duration = atoi(gopt_context.optarg);
                if (test->duration > MAX_TIME) {
                    i_errno = IEDURATION;
                    return (-1);
                }
                break;
            case 'u':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                set_protocol(test, Pudp);
                test->settings->blksize = DEFAULT_UDP_BLKSIZE;
                break;
            case 'P':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->num_streams = atoi(gopt_context.optarg);
                if (test->num_streams > MAX_STREAMS) {
                    i_errno = IENUMSTREAMS;
                    return (-1);
                }
                break;
            case 'B':
                test->bind_address = (char *) _mem_alloc(strlen(gopt_context.optarg)+1);
                strncpy(test->bind_address, gopt_context.optarg, strlen(gopt_context.optarg)+1);
                break;
            case 'b':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->settings->rate = (uint64_t)unit_atof(gopt_context.optarg);
                break;
            case 'l':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->settings->blksize = unit_atoi(gopt_context.optarg);
                if (test->settings->blksize > MAX_BLOCKSIZE) {
                    i_errno = IEBLOCKSIZE;
                    return (-1);
                }
                break;
            case 'w':
                // XXX: This is a socket buffer, not specific to TCP
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->settings->socket_bufsize = (int)unit_atof(gopt_context.optarg);
                if (test->settings->socket_bufsize > MAX_TCP_BUFFER) {
                    i_errno = IEBUFSIZE;
                    return (-1);
                }
                break;
            case 'i':
                /* XXX: could potentially want separate stat collection and reporting intervals,
                   but just set them to be the same for now */
                test->stats_interval = atoi(gopt_context.optarg);
                test->reporter_interval = atoi(gopt_context.optarg);
                if (test->stats_interval > MAX_INTERVAL) {
                    i_errno = IEINTERVAL;
                    return (-1);
                }
                break;
            case 'n':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->settings->bytes = unit_atoi(gopt_context.optarg);
                break;
            case 'm':
                test->print_mss = 1;
                break;
            case 'N':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->no_delay = 1;
                break;
            case 'M':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->settings->mss = atoi(gopt_context.optarg);
                if (test->settings->mss > MAX_MSS) {
                    i_errno = IEMSS;
                    return (-1);
                }
                break;
            case 'f':
                test->settings->unit_format = *gopt_context.optarg;
                break;
            case '6':
                test->settings->domain = AF_INET6;
                break;
            case 'V':
                test->verbose = 1;
                break;
            case 'R':
                if (test->role == 's') {
                    i_errno = IECLIENTONLY;
                    return (-1);
                }
                test->reverse = 1;
                break;
            case 'v':
                printf(version);
                return(0);
            case 'h':
            default:
                usage_long();
                return(1);
        }
    }
    gopt_context.optind = 0;

    if ((test->role != 'c') && (test->role != 's')) {
        i_errno = IENOROLE;
        return (-1);
    }

    return (0);
}

int
all_data_sent(struct iperf_test * test)
{
    if (test->settings->bytes > 0) {
        if (test->bytes_sent >= (test->num_streams * test->settings->bytes)) {
            return (1);
        }
    }

    return (0);
}

int
iperf_send(struct iperf_test *test, rtcs_fd_set *write_setP)
{
    iperf_size_t bytes_sent;
    struct iperf_stream *sp;
   
        SLIST_FOREACH(sp, &test->streams, streams) {
            if (RTCS_FD_ISSET(sp->socket, write_setP)) {
              if ((bytes_sent = sp->snd(sp)) < 0) {
                    i_errno = IESTREAMWRITE;
                    return (-1);
              }
                test->bytes_sent += bytes_sent;
                RTCS_FD_CLR(sp->socket, write_setP);
            }
        }

    return (0);
}

int
iperf_recv(struct iperf_test *test, rtcs_fd_set *read_setP)
{
    iperf_size_t bytes_sent;
    struct iperf_stream *sp;


        SLIST_FOREACH(sp, &test->streams, streams) {
            if (RTCS_FD_ISSET(sp->socket, read_setP)) {
                if ((bytes_sent = sp->rcv(sp)) < 0) {
                    i_errno = IESTREAMREAD;
                    return (-1);
                }
                test->bytes_sent += bytes_sent;
                RTCS_FD_CLR(sp->socket, read_setP);
            }
        }       

    return (0);
}

int
iperf_init_test(struct iperf_test *test)
{
    struct iperf_stream *sp;
    time_t sec;
    time_t usec;

    if (test->protocol->init) {
        if (test->protocol->init(test) < 0)
            return (-1);
    }

    /* Set timers */
    if (test->settings->bytes == 0) {
        test->timer = new_timer(test->duration, 0);
        if (test->timer == NULL)
            return (-1);
    } 

    if (test->stats_interval != 0) {
        sec = (time_t) test->stats_interval;
        usec = (test->stats_interval - sec) * SEC_TO_US;
        test->stats_timer = new_timer(sec, usec);
        if (test->stats_timer == NULL)
            return (-1);
    }
    if (test->reporter_interval != 0) {
        sec = (time_t) test->reporter_interval;
        usec = (test->reporter_interval - sec) * SEC_TO_US;
        test->reporter_timer = new_timer(sec, usec);
        if (test->reporter_timer == NULL)
            return (-1);
    }

    /* Set start time */
    SLIST_FOREACH(sp, &test->streams, streams) {
        if (gettimeofday(&sp->result->start_time, NULL) < 0) {
            i_errno = IEINITTEST;
            return (-1);
        }
    }

    if (test->on_test_start)
        test->on_test_start(test);

    return (0);
}

/*********************************************************/

int
package_parameters(struct iperf_test *test)
{
    char pstring[PSTRLEN];
    char optbuf[BUFLEN];
    
    memset(pstring, 0, sizeof(pstring));

    *pstring = ' ';

    if (test->protocol->id == Ptcp) {
        strncat(pstring, "-p ", sizeof(pstring));
    } else if (test->protocol->id == Pudp) {
        strncat(pstring, "-u ", sizeof(pstring));
    }

    snprintf(optbuf, sizeof(optbuf), "-P %d ", test->num_streams);
    strncat(pstring, optbuf, sizeof(pstring));
    
    if (test->reverse)
        strncat(pstring, "-R ", sizeof(pstring));
    
    if (test->settings->socket_bufsize) {
        snprintf(optbuf, sizeof(optbuf), "-w %d ", test->settings->socket_bufsize);
        strncat(pstring, optbuf, sizeof(pstring));
    }

    if (test->settings->rate) {
        snprintf(optbuf, sizeof(optbuf), "-b %llu ", test->settings->rate);
        strncat(pstring, optbuf, sizeof(pstring));
    }

    if (test->settings->mss) {
        snprintf(optbuf, sizeof(optbuf), "-m %d ", test->settings->mss);
        strncat(pstring, optbuf, sizeof(pstring));
    }

    if (test->no_delay) {
        snprintf(optbuf, sizeof(optbuf), "-N ");
        strncat(pstring, optbuf, sizeof(pstring));
    }

    if (test->settings->bytes) {
        snprintf(optbuf, sizeof(optbuf), "-n %llu ", test->settings->bytes);
        strncat(pstring, optbuf, sizeof(pstring));
    }

    if (test->duration) {
        snprintf(optbuf, sizeof(optbuf), "-t %d ", test->duration);
        strncat(pstring, optbuf, sizeof(pstring));
    }

    if (test->settings->blksize) {
        snprintf(optbuf, sizeof(optbuf), "-l %d ", test->settings->blksize);
        strncat(pstring, optbuf, sizeof(pstring));
    }

    *pstring = (char) (strlen(pstring) - 1);

    if (Nwrite(test->ctrl_sck, pstring, strlen(pstring), Ptcp) < 0) {
        i_errno = IESENDPARAMS;
        return (-1);
    }

    return 0;
}


int
parse_parameters(struct iperf_test *test)
{
    int n, ch;
    char *param, **params;
    char len;
    char pstring[PSTRLEN];
    SHELL_GETOPT_CONTEXT       gopt_context;
    

    _mem_zero(pstring, PSTRLEN * sizeof(char));

    if (Nread(test->ctrl_sck, (char*)&len, sizeof(char), Ptcp) < 0) {
        i_errno = IERECVPARAMS;
        return (-1);
    }

    if (Nread(test->ctrl_sck, pstring, len, Ptcp) < 0) {
        i_errno = IERECVPARAMS;
        return (-1);
    }    
    
    params = _mem_alloc(PSTRLEN);
    if (!params){
      i_errno = IERECVPARAMS;
      return (-1);
    }    
    
    for (param = strtok(pstring, " "), n = 1; param; param = strtok(NULL, " ")) {
        params[n] = param;
        n++;
    }
    
    //if (_mem_free_part(params, (n+1)*sizeof(char *))) {
     // i_errno = IERECVPARAMS;
     // _mem_free(params);
       //     return (-1);
  //  }

    // XXX: Should we check for parameters exceeding maximum values here?
    Shell_getopt_init(&gopt_context);
    while ((ch = Shell_getopt(n, params, "pt:n:m:uNP:Rw:l:b:", &gopt_context)) != -1) {
        switch (ch) {
            case 'p':
                set_protocol(test, Ptcp);
                break;
            case 't':
                test->duration = atoi(gopt_context.optarg);
                break;
            case 'n':
                break;
            case 'm':
                test->settings->mss = atoi(gopt_context.optarg);
                break;
            case 'u':
                set_protocol(test, Pudp);
                break;
            case 'N':
                test->no_delay = 1;
                break;
            case 'P':
                test->num_streams = atoi(gopt_context.optarg);
                break;
            case 'R':
                test->reverse = 1;
                break;
            case 'w':
                test->settings->socket_bufsize = atoi(gopt_context.optarg);
                break;
            case 'l':
                test->settings->blksize = atoi(gopt_context.optarg);
                break;
            case 'b':
                break;
        }
    }
    gopt_context.optind = 0;

    _mem_free(params);

    return (0);
}

/**
 * iperf_exchange_parameters - handles the param_Exchange part for client
 *
 */

int
iperf_exchange_parameters(struct iperf_test * test)
{
    int s;

    if (test->role == 'c') {

        if (package_parameters(test) < 0)
            return (-1);

    } else {

        if (parse_parameters(test) < 0)
            return (-1);

        if ((s = test->protocol->i_listen(test)) == RTCS_SOCKET_ERROR)
            return (-1);
        RTCS_FD_SET(s, &test->read_set);
        test->max_fd = (s > test->max_fd) ? s : test->max_fd;
        test->prot_listener = s;

        // Send the control message to create streams and start the test
        test->state = CREATE_STREAMS;
        if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
            i_errno = IESENDMESSAGE;
            return (-1);
        }

    }

    return (0);
}

/*************************************************************/

int
iperf_exchange_results(struct iperf_test *test)
{
    unsigned int size;
    char buf[BUFLEN];
    char *results;
    char jitter[10];
    struct iperf_stream *sp;
    iperf_size_t bytes_transferred;

    if (test->role == 'c') {
        /* Prepare results string and send to server */
        results = _mem_alloc(PSTRLEN);
        
        if ((results = _mem_alloc(PSTRLEN)) == NULL){
            i_errno = IEPACKAGERESULTS;
            return (-1);
        }
        size = 0;
        SLIST_FOREACH(sp, &test->streams, streams) {
            bytes_transferred = (test->reverse ? sp->result->bytes_received : sp->result->bytes_sent);
            snprintf(buf, BUFLEN, "%d:%llu,%d,%d,%d\n", sp->id, bytes_transferred,sp->jitter,
                sp->cnt_error, sp->packet_count);

            size += strlen(buf);

            if (sp == SLIST_FIRST(&test->streams))
                *results = '\0';
            strncat(results, buf, size+1);
        }
        
     //   if (_mem_free_part(results, (size+1))){
        //   i_errno = IERECVPARAMS;
       //     _mem_free(results);
         //   return (-1);
       // }
        
        size++;
        size = htonl(size);
        if (Nwrite(test->ctrl_sck, (char*)&size, sizeof(size), Ptcp) < 0) {
            i_errno = IESENDRESULTS;
            return (-1);
        }
        if (Nwrite(test->ctrl_sck, results, ntohl(size), Ptcp) < 0) {
            i_errno = IESENDRESULTS;
            return (-1);
        }
        _mem_free(results);

        /* Get server results string */
        if (Nread(test->ctrl_sck, (char*)&size, sizeof(size), Ptcp) < 0) {
            i_errno = IERECVRESULTS;
            return (-1);
        }
        size = ntohl(size);
        results = (char *) _mem_alloc(size * sizeof(char));
        if (results == NULL) {
            i_errno = IERECVRESULTS;
            return (-1);
        }
        if (Nread(test->ctrl_sck, results, size, Ptcp) < 0) {
            i_errno = IERECVRESULTS;
            return (-1);
        }

        // XXX: The only error this sets is IESTREAMID, which may never be reached. Consider making void.
        if (parse_results(test, results) < 0)
            return (-1);

        _mem_free(results);

    } else {
        /* Get client results string */
        if (Nread(test->ctrl_sck, (char*)&size, sizeof(size), Ptcp) < 0) {
            i_errno = IERECVRESULTS;
            return (-1);
        }
        size = ntohl(size);
        results = (char *) _mem_alloc(size * sizeof(char));
        if (results == NULL) {
            i_errno = IERECVRESULTS;
            return (-1);
        }
        if (Nread(test->ctrl_sck, results, size, Ptcp) < 0) {
            i_errno = IERECVRESULTS;
            return (-1);
        }

        // XXX: Same issue as with client
        if (parse_results(test, results) < 0)
            return (-1);

        _mem_free(results);

        /* Prepare results string and send to client */
        if ((results = _mem_alloc(PSTRLEN)) == NULL){
          i_errno = IEPACKAGERESULTS;
                return (-1);
        }
        size = 0;
        SLIST_FOREACH(sp, &test->streams, streams) {
            bytes_transferred = (test->reverse ? sp->result->bytes_sent : sp->result->bytes_received);
            double_to_string(sp->jitter, jitter);
            snprintf(buf, BUFLEN, "%d:%llu,%s,%d,%d\n", sp->id, bytes_transferred, jitter,
                sp->cnt_error, sp->packet_count);
            size += strlen(buf);         
            
            if (sp == SLIST_FIRST(&test->streams))
                *results = '\0';
            
            strncat(results, buf, size+1);
        }
      //  if (_mem_free_part(results, (size+1))){
        //    i_errno = IERECVPARAMS;
        //    _mem_free(results);
         //   return (-1);
        //    }
        size++;
        size = htonl(size);
        if (Nwrite(test->ctrl_sck, (char*)&size, sizeof(size), Ptcp) < 0) {
            i_errno = IESENDRESULTS;
            return (-1);
        }
        if (Nwrite(test->ctrl_sck, results, ntohl(size), Ptcp) < 0) {
            i_errno = IESENDRESULTS;
            return (-1);
        }
        _mem_free(results);

    }

    return (0);
}

/*************************************************************/

int
parse_results(struct iperf_test *test, char *results)
{
    int sid, cerror, pcount;
    double jitter;
    char sjitter[9];
    char *strp;
    unsigned long bytes_transferred;
    struct iperf_stream *sp;
    

    for (strp = results; *strp; strp = strchr(strp, '\n')+1) {
        sscanf(strp, "%d:%lu,%s,%d,%d\n", &sid, &bytes_transferred, &sjitter,
            &cerror, &pcount);
        
        jitter = atof(sjitter);

        SLIST_FOREACH(sp, &test->streams, streams)
            if (sp->id == sid) break;
        if (sp == NULL) {
            i_errno = IESTREAMID;
            return (-1);
        }
        if ((test->role == 'c' && !test->reverse) || (test->role == 's' && test->reverse)) {
            sp->jitter = jitter;
            sp->cnt_error = cerror;
            sp->packet_count = pcount;
            sp->result->bytes_received = bytes_transferred;
        } else
            sp->result->bytes_sent = bytes_transferred;
    }

    return (0);
}


/*************************************************************/
/**
 * add_to_interval_list -- adds new interval to the interval_list
 *
 */

void
add_to_interval_list(struct iperf_stream_result * rp, struct iperf_interval_results * new)
{
    struct iperf_interval_results *ip = NULL;

    ip = (struct iperf_interval_results *) _mem_alloc(sizeof(struct iperf_interval_results));
    _mem_copy(new, ip, sizeof(struct iperf_interval_results));
    ip->next = NULL;

    if (rp->interval_results == NULL) {	/* if 1st interval */
        rp->interval_results = ip;
        rp->last_interval_results = ip; /* pointer to last element in list */
    } else { /* add to end of list */
        rp->last_interval_results->next = ip;
        rp->last_interval_results = ip;
    }
}


/************************************************************/

/**
 * connect_msg -- displays connection message
 * denoting sender/receiver details
 *
 */

void
connect_msg(struct iperf_stream *sp)
{
    char ipl[INET6_ADDRSTRLEN], ipr[INET6_ADDRSTRLEN];
    int lport, rport, domain = sp->settings->domain;

    if (domain == AF_INET) {
        inet_ntop(domain, (void *) &((struct sockaddr_in *) &sp->local_addr)->sin_addr, ipl, sizeof(ipl));
        inet_ntop(domain, (void *) &((struct sockaddr_in *) &sp->remote_addr)->sin_addr, ipr, sizeof(ipr));
        lport = ntohs(((struct sockaddr_in *) &sp->local_addr)->sin_port);
        rport = ntohs(((struct sockaddr_in *) &sp->remote_addr)->sin_port);
    } else {
        inet_ntop(domain, (void *) &((struct sockaddr_in6 *) &sp->local_addr)->sin6_addr, ipl, sizeof(ipl));
        inet_ntop(domain, (void *) &((struct sockaddr_in6 *) &sp->remote_addr)->sin6_addr, ipr, sizeof(ipr));
        lport = ntohs(((struct sockaddr_in6 *) &sp->local_addr)->sin6_port);
        rport = ntohs(((struct sockaddr_in6 *) &sp->remote_addr)->sin6_port);
    }

    printf("[%3d] local %s port %d connected to %s port %d\n",
        sp->socket, ipl, lport, ipr, rport);
}


/**************************************************************************/

struct iperf_test *
iperf_new_test()
{
    struct iperf_test *test;

    test = (struct iperf_test *) _mem_alloc(sizeof(struct iperf_test));
    if (!test) {
        i_errno = IENEWTEST;
        return (NULL);
    }
    /* initialize everything to zero */
    _mem_zero(test, sizeof(struct iperf_test));

    test->settings = (struct iperf_settings *) _mem_alloc(sizeof(struct iperf_settings));
    _mem_zero(test->settings, sizeof(struct iperf_settings));

    return (test);
}

/**************************************************************************/
int
iperf_defaults(struct iperf_test * testp)
{
    testp->duration = DURATION;
    testp->server_port = PORT;
    testp->ctrl_sck = -1;
    testp->prot_listener = -1;

    testp->stats_callback = iperf_stats_callback;
    testp->reporter_callback = iperf_reporter_callback;

    testp->stats_interval = 0;
    testp->reporter_interval = 0;
    testp->num_streams = 1;

    testp->settings->domain = AF_INET;
    testp->settings->unit_format = 'a';
    testp->settings->socket_bufsize = DEFAULT_SOCK_SIZE;	/* use autotuning */
    testp->settings->blksize = DEFAULT_TCP_BLKSIZE;
    testp->settings->rate = RATE;	/* UDP only */
    testp->settings->mss = 0;
    testp->settings->bytes = 0;
    _mem_zero(testp->cookie, COOKIE_SIZE);

    /* Set up protocol list */
    SLIST_INIT(&testp->streams);
    SLIST_INIT(&testp->protocols);

    struct protocol *tcp, *udp;
    tcp = (struct protocol *) _mem_alloc(sizeof(struct protocol));
    if (!tcp)
        return (-1);
    _mem_zero(tcp, sizeof(struct protocol));
    udp = (struct protocol *) _mem_alloc(sizeof(struct protocol));
    if (!udp)
        return (-1);
    _mem_zero(udp, sizeof(struct protocol));

    tcp->id = Ptcp;
    tcp->name = "TCP";
    tcp->i_accept = iperf_tcp_accept;
    tcp->i_listen = iperf_tcp_listen;
    tcp->i_connect = iperf_tcp_connect;
    tcp->send = iperf_tcp_send;
    tcp->recv = iperf_tcp_recv;
    tcp->init = NULL;
    SLIST_INSERT_HEAD(&testp->protocols, tcp, protocols);

    udp->id = Pudp;
    udp->name = "UDP";
    udp->i_accept = iperf_udp_accept;
    udp->i_listen = iperf_udp_listen;
    udp->i_connect = iperf_udp_connect;
    udp->send = iperf_udp_send;
    udp->recv = iperf_udp_recv;
    udp->init = iperf_udp_init;
    SLIST_INSERT_AFTER(tcp, udp, protocols);

    set_protocol(testp, Ptcp);

    testp->on_new_stream = iperf_on_new_stream;
    testp->on_test_start = iperf_on_test_start;
    testp->on_connect = iperf_on_connect;
    testp->on_test_finish = iperf_on_test_finish;

    return (0);
}


/**************************************************************************/
void
iperf_free_test(struct iperf_test * test)
{
    struct protocol *prot;
    struct iperf_stream *sp;

    /* Close all stream sockets */
    SLIST_FOREACH(sp, &test->streams, streams) {
        shutdown(sp->socket, FLAG_ABORT_CONNECTION);
    }
    
    shutdown(test->ctrl_sck, FLAG_ABORT_CONNECTION);
    
    /* Free streams */
    while (!SLIST_EMPTY(&test->streams)) {
        sp = SLIST_FIRST(&test->streams);
        SLIST_REMOVE_HEAD(&test->streams, streams);
        iperf_free_stream(sp);
    }

    _mem_free(test->server_hostname);
    _mem_free(test->bind_address);
    _mem_free(test->settings);
    free_timer(test->timer);
    free_timer(test->stats_timer);
    free_timer(test->reporter_timer);

    /* Free protocol list */
    while (!SLIST_EMPTY(&test->protocols)) {
        prot = SLIST_FIRST(&test->protocols);
        SLIST_REMOVE_HEAD(&test->protocols, protocols);        
        _mem_free(prot);
    }

    /* XXX: Why are we setting these values to NULL? */
    test->stats_callback = NULL;
    test->reporter_callback = NULL;
    _mem_free(test);
}


void
iperf_reset_test(struct iperf_test *test)
{
    struct iperf_stream *sp;

    /* Free streams */
    while (!SLIST_EMPTY(&test->streams)) {
        sp = SLIST_FIRST(&test->streams);
        SLIST_REMOVE_HEAD(&test->streams, streams);
        iperf_free_stream(sp);
        shutdown(sp->socket, FLAG_ABORT_CONNECTION);
    }
    free_timer(test->timer);
    free_timer(test->stats_timer);
    free_timer(test->reporter_timer);
    test->timer = NULL;
    test->stats_timer = NULL;
    test->reporter_timer = NULL;

    SLIST_INIT(&test->streams);

    test->role = 's';
    set_protocol(test, Ptcp);
    test->duration = DURATION;
    test->state = 0;
    test->server_hostname = NULL;

    shutdown(test->listener, FLAG_ABORT_CONNECTION);
    shutdown(test->ctrl_sck, FLAG_ABORT_CONNECTION);
    shutdown(test->prot_listener, FLAG_ABORT_CONNECTION);
    test->ctrl_sck = -1;
    test->prot_listener = -1;

    test->bytes_sent = 0;

    test->reverse = 0;
    test->no_delay = 0;

    RTCS_FD_ZERO(&test->read_set);
    RTCS_FD_ZERO(&test->write_set);
    
    test->num_streams = 1;
    test->settings->socket_bufsize = 0;
    test->settings->blksize = DEFAULT_TCP_BLKSIZE;
    test->settings->rate = RATE;   /* UDP only */
    test->settings->mss = 0;
    _mem_zero(test->cookie, COOKIE_SIZE);
}


/**************************************************************************/

/**
 * iperf_stats_callback -- handles the statistic gathering for both the client and server
 *
 * XXX: This function needs to be updated to reflect the new code
 */


void
iperf_stats_callback(struct iperf_test * test)
{
    struct iperf_stream *sp;
    struct iperf_stream_result *rp = NULL;
    struct iperf_interval_results *ip = NULL, temp;

    SLIST_FOREACH(sp, &test->streams, streams) {
        rp = sp->result;

        if ((test->role == 'c' && !test->reverse) || (test->role == 's' && test->reverse))
            temp.bytes_transferred = rp->bytes_sent_this_interval;
        else
            temp.bytes_transferred = rp->bytes_received_this_interval;
     
        ip = sp->result->interval_results;
        /* result->end_time contains timestamp of previous interval */
        if ( ip != NULL ) /* not the 1st interval */
            _mem_copy(&sp->result->end_time, &temp.interval_start_time, sizeof(struct timeval));
        else /* or use timestamp from beginning */
            _mem_copy(&sp->result->start_time, &temp.interval_start_time, sizeof(struct timeval));
        /* now save time of end of this interval */
        gettimeofday(&sp->result->end_time, NULL);
        _mem_copy(&sp->result->end_time, &temp.interval_end_time, sizeof(struct timeval));
        timeval_diff(&temp.interval_start_time, &temp.interval_end_time, &temp.interval_duration);
        add_to_interval_list(rp, &temp);
        rp->bytes_sent_this_interval = rp->bytes_received_this_interval = 0;

    }

}

/**************************************************************************/

/**
 * iperf_reporter_callback -- handles the report printing
 *
 */

void
iperf_reporter_callback(struct iperf_test * test)
{
    int total_packets = 0, lost_packets = 0;
    char ubuf[UNIT_LEN];
    char nbuf[UNIT_LEN];
    struct iperf_stream *sp = NULL;
    iperf_size_t bytes = 0, bytes_sent = 0, bytes_received = 0;
    iperf_size_t total_sent = 0, total_received = 0;
    struct timeval start_time, end_time;
    double avg_jitter;
    int dec, frac;
    struct iperf_interval_results *ip = NULL;

    switch (test->state) {
        case TEST_RUNNING:
        case STREAM_RUNNING:
            /* print interval results for each stream */
            SLIST_FOREACH(sp, &test->streams, streams) {
                print_interval_results(test, sp);
                bytes += sp->result->interval_results->bytes_transferred; /* sum up all streams */
            }
            if (bytes <=0 ) { /* this can happen if timer goes off just when client exits */
                fprintf(stderr, "error: bytes <= 0!\n");
                break;
            }
            /* next build string with sum of all streams */
            if (test->num_streams > 1) {
                sp = SLIST_FIRST(&test->streams); /* reset back to 1st stream */
                ip = sp->result->last_interval_results;	/* use 1st stream for timing info */

                unit_snprintf(ubuf, UNIT_LEN, (double) (bytes), 'A');
                unit_snprintf(nbuf, UNIT_LEN, (double) (bytes / ip->interval_duration.tv_sec),
                        test->settings->unit_format);

                timeval_diff(&sp->result->start_time,&ip->interval_start_time, &start_time);
                timeval_diff(&sp->result->start_time,&ip->interval_end_time, &end_time);
                printf(report_sum_bw_format, start_time, end_time, ubuf, nbuf);
            }
            break;
        case DISPLAY_RESULTS:
            /* print final summary for all intervals */

          if (test->protocol->id == Ptcp)
            printf(report_bw_header);
          else
            printf(report_bw_jitter_loss_header);

            start_time.tv_sec = 0;
            start_time.tv_msec = 0;
            sp = SLIST_FIRST(&test->streams);
            timeval_diff(&sp->result->start_time, &sp->result->end_time, &end_time);
            SLIST_FOREACH(sp, &test->streams, streams) {
                bytes_sent = sp->result->bytes_sent;
                bytes_received = sp->result->bytes_received;
                total_sent += bytes_sent;
                total_received += bytes_received;

                if (test->protocol->id == Pudp) {
                    total_packets += sp->packet_count;
                    lost_packets += sp->cnt_error;
                    avg_jitter += sp->jitter;
                }

                if (bytes_sent > 0) {
                    unit_snprintf(ubuf, UNIT_LEN, (double) (bytes_sent), 'A');
                    unit_snprintf(nbuf, UNIT_LEN, (double) (bytes_sent / end_time.tv_sec), test->settings->unit_format);
                    if (test->protocol->id == Ptcp) {
                        printf("      Sent\n");
                        printf(report_bw_format, sp->socket, start_time.tv_sec, start_time.tv_msec, end_time.tv_sec, end_time.tv_msec, ubuf, nbuf);
                    } else {
                      dec = (int)(sp->jitter*1000);
                      frac = (int)(((sp->jitter*1000)-dec)*1000);
                      printf(report_bw_jitter_loss_format, sp->socket, start_time.tv_sec, start_time.tv_msec,
                                end_time.tv_sec, end_time.tv_msec, ubuf, nbuf, dec, frac, sp->cnt_error, 
                                sp->packet_count, (int) (100.0 * sp->cnt_error / sp->packet_count));
                        if (test->role == 'c') {
                            printf(report_datagrams, sp->socket, sp->packet_count);
                        }
                        if (sp->outoforder_packets > 0)
                            printf(report_sum_outoforder, start_time.tv_sec, end_time.tv_sec, sp->cnt_error);
                    }
                }
                if (bytes_received > 0) {
                    unit_snprintf(ubuf, UNIT_LEN, (double) bytes_received, 'A');
                    unit_snprintf(nbuf, UNIT_LEN, (double) (bytes_received / end_time.tv_sec), test->settings->unit_format);
                    if (test->protocol->id == Ptcp) {
                        printf("      Received\n");
                        printf(report_bw_format, sp->socket, start_time.tv_sec, start_time.tv_msec, end_time.tv_sec, end_time.tv_msec, ubuf, nbuf);
                    }
                }
            }

            if (test->num_streams > 1) {
                unit_snprintf(ubuf, UNIT_LEN, (double) total_sent, 'A');
                unit_snprintf(nbuf, UNIT_LEN, (double) total_sent / end_time.tv_sec, test->settings->unit_format);
                if (test->protocol->id == Ptcp) {
                    printf("      Total sent\n");
                    printf(report_sum_bw_format, start_time, end_time, ubuf, nbuf);
                    unit_snprintf(ubuf, UNIT_LEN, (double) total_received, 'A');
                    unit_snprintf(nbuf, UNIT_LEN, (double) (total_received / end_time.tv_sec), test->settings->unit_format);
                    printf("      Total received\n");
                    printf(report_sum_bw_format, start_time, end_time, ubuf, nbuf);
                } else {
                    avg_jitter /= test->num_streams;
                    printf(report_sum_bw_jitter_loss_format, start_time, end_time, ubuf, nbuf, avg_jitter,
                        lost_packets, total_packets, (double) (100.0 * lost_packets / total_packets));
                }

                if ((test->print_mss != 0) && (test->role == 'c')) {
                    printf("The TCP maximum segment size mss = %d\n", getsock_tcp_mss(sp->socket));
                }
            }
            break;
    } 

}

/**************************************************************************/
void
print_interval_results(struct iperf_test * test, struct iperf_stream * sp)
{
    char ubuf[UNIT_LEN];
    char nbuf[UNIT_LEN];
    struct timeval st, et;
    struct iperf_interval_results *ir = NULL;

    ir = sp->result->last_interval_results; /* get last entry in linked list */
    if (ir == NULL) {
        printf("print_interval_results Error: interval_results = NULL \n");
        return;
    }
    if (sp == SLIST_FIRST(&test->streams)) {
        printf(report_bw_header);
    }

    unit_snprintf(ubuf, UNIT_LEN, (double) (ir->bytes_transferred), 'A');
    unit_snprintf(nbuf, UNIT_LEN, (double) (ir->bytes_transferred / ir->interval_duration.tv_sec),
            test->settings->unit_format);
    
    timeval_diff(&sp->result->start_time,&ir->interval_start_time, &st);
    timeval_diff(&sp->result->start_time,&ir->interval_end_time, &et);
    
    printf(report_bw_format, sp->socket, st.tv_sec, st.tv_msec, et.tv_sec, et.tv_msec, ubuf, nbuf);

}

/**************************************************************************/
void
iperf_free_stream(struct iperf_stream * sp)
{
    struct iperf_interval_results *ip, *np;

    /* XXX: need to free interval list too! */
    _mem_free(sp->buffer);
    for (ip = sp->result->interval_results; ip; ip = np) {
        np = ip->next;
        _mem_free(ip);
    }
    _mem_free(sp->result);
    _mem_free(sp->send_timer);
    _mem_free(sp);
}

/**************************************************************************/
struct iperf_stream *
iperf_new_stream(struct iperf_test *test, int s)
{
    int i;
    struct iperf_stream *sp;

    sp = (struct iperf_stream *) _mem_alloc(sizeof(struct iperf_stream));
    if (!sp) {
        i_errno = IECREATESTREAM;
        return (NULL);
    }

    _mem_zero(sp, sizeof(struct iperf_stream));

    sp->buffer = (char *) _mem_alloc(test->settings->blksize);
    sp->result = (struct iperf_stream_result *) _mem_alloc(sizeof(struct iperf_stream_result));
    sp->settings = test->settings;

    if (!sp->buffer) {
        printf("Not enough memory! Buffer too big! Please set buffer length to lower value!\n");
        i_errno = IECREATESTREAM;
        return (NULL);
    }
    if (!sp->result) {
        i_errno = IECREATESTREAM;
        return (NULL);
    }

    _mem_zero(sp->result, sizeof(struct iperf_stream_result));
    
    /* Randomize the buffer */
    srand(5);
    for (i = 0; i < test->settings->blksize; ++i)
        sp->buffer[i] = rand();

    /* Set socket */
    sp->socket = s;

    sp->snd = test->protocol->send;
    sp->rcv = test->protocol->recv;

    /* Initialize stream */
    if (iperf_init_stream(sp, test) < 0)
        return (NULL);
    iperf_add_stream(test, sp);

    return (sp);
}

/**************************************************************************/
int
iperf_init_stream(struct iperf_stream * sp, struct iperf_test * testp)
{
    uint16_t len;

    len = sizeof(struct sockaddr);
    if (getsockname(sp->socket, (struct sockaddr *) &sp->local_addr, &len) < 0) {
        i_errno = IEINITSTREAM;
        return (-1);
    }
    len = sizeof(struct sockaddr);
    if (getpeername(sp->socket, (struct sockaddr *) &sp->remote_addr, &len) < 0) {
        i_errno = IEINITSTREAM;
        return (-1);
    }

    return (0);
}

/**************************************************************************/
void
iperf_add_stream(struct iperf_test * test, struct iperf_stream * sp)
{
    int i;
    struct iperf_stream *n, *prev;

    if (SLIST_EMPTY(&test->streams)) {
        SLIST_INSERT_HEAD(&test->streams, sp, streams);
        sp->id = 1;
    } else {
        i = 2;
        SLIST_FOREACH(n, &test->streams, streams) {
            prev = n;
            ++i;
        }
        SLIST_INSERT_AFTER(prev, sp, streams);
        sp->id = i;
    }
}


