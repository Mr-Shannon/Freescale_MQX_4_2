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

/* iperf_server_api.c: Functions to be used by an iperf server
*/


#include "iperf.h"
#include "iperf_server_api.h"
#include "iperf_api.h"
#include "iperf_udp.h"
#include "iperf_tcp.h"
#include "iperf_error.h"
#include "iperf_util.h"
#include "itimer.h"
#include "net.h"
#include "units.h"
#include "iperf_util.h"
#include "ilocale.h"


int
iperf_server_listen(struct iperf_test *test)
{

    if((test->listener = netannounce(test->settings->domain, Ptcp, test->bind_address, test->server_port)) == RTCS_SOCKET_ERROR) {
        i_errno = IELISTEN;
        return (-1);
    }

    printf("-----------------------------------------------------------\n");
    printf("Server listening on %d\n", test->server_port);
    printf("-----------------------------------------------------------\n");

    RTCS_FD_ZERO(&test->read_set);
    RTCS_FD_ZERO(&test->write_set);
    RTCS_FD_SET(test->listener, &test->read_set);
    RTCS_FD_SET(test->listener, &test->write_set);
    test->max_fd = (test->listener > test->max_fd) ? test->listener : test->max_fd;

    return 0;
}

int
iperf_accept(struct iperf_test *test)
{
    int s;
    int rbuf = ACCESS_DENIED;
    char cookie[COOKIE_SIZE];
    uint16_t len;
    struct sockaddr_in addr;

    len = sizeof(addr);
    if ((s = accept(test->listener, (struct sockaddr *) &addr, &len)) == RTCS_SOCKET_ERROR) {
        i_errno = IEACCEPT;
        return (-1);
    }

    if (test->ctrl_sck == -1) {
        /* Server free, accept new client */
        if (Nread(s, test->cookie, COOKIE_SIZE, Ptcp) < 0) {
            i_errno = IERECVCOOKIE;
            return (-1);
        }

        RTCS_FD_SET(s, &test->read_set);
        RTCS_FD_SET(s, &test->write_set);
        test->max_fd = (s > test->max_fd) ? s : test->max_fd;
        test->ctrl_sck = s;

        test->state = PARAM_EXCHANGE;
        if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
            i_errno = IESENDMESSAGE;
            return (-1);
        }
        if (iperf_exchange_parameters(test) < 0) {
            return (-1);
        }
        if (test->on_connect) {
            test->on_connect(test);
        }
    } else {
        // XXX: Do we even need to receive cookie if we're just going to deny anyways?
        if (Nread(s, cookie, COOKIE_SIZE, Ptcp) < 0) {
            i_errno = IERECVCOOKIE;
            return (-1);
        }
        if (Nwrite(s, (char*)&rbuf, sizeof(int), Ptcp) < 0) {
            i_errno = IESENDMESSAGE;
            return (-1);
        }
        shutdown(s, FLAG_ABORT_CONNECTION);
    }

    return (0);
}


/**************************************************************************/
int
iperf_handle_message_server(struct iperf_test *test)
{
    int rval;
    struct iperf_stream *sp;

    // XXX: Need to rethink how this behaves to fit API
    if ((rval = Nread(test->ctrl_sck, &test->state, sizeof(char), Ptcp)) <= 0) {
        if (rval <= 0) {
            fprintf(stderr, "The client has unexpectedly closed the connection.\n");
            SLIST_FOREACH(sp, &test->streams, streams) {              
                shutdown(sp->socket, FLAG_ABORT_CONNECTION);
            }
            i_errno = IECTRLCLOSE;
            test->state = IPERF_DONE;
            return (0);
        } else {
            i_errno = IERECVMESSAGE;
            return (-1);
        }
    }

    switch(test->state) {
        case TEST_START:
            break;
        case TEST_END:
            test->stats_callback(test);
            SLIST_FOREACH(sp, &test->streams, streams) {
                RTCS_FD_CLR(sp->socket, &test->read_set);
                RTCS_FD_CLR(sp->socket, &test->write_set);
                shutdown(sp->socket, FLAG_ABORT_CONNECTION);
            }
            test->state = EXCHANGE_RESULTS;
            if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
                i_errno = IESENDMESSAGE;
                return (-1);
            }
            if (iperf_exchange_results(test) < 0)
                return (-1);
            test->state = DISPLAY_RESULTS;
            if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
                i_errno = IESENDMESSAGE;
                return (-1);
            }
            if (test->on_test_finish)
                test->on_test_finish(test);
            test->reporter_callback(test);
            break;
        case IPERF_DONE:
            break;
        case CLIENT_TERMINATE:
            i_errno = IECLIENTTERM;

            // XXX: Remove this line below!
            fprintf(stderr, "The client has terminated.\n");
            SLIST_FOREACH(sp, &test->streams, streams) {
                RTCS_FD_CLR(sp->socket, &test->read_set);
                RTCS_FD_CLR(sp->socket, &test->write_set);
                shutdown(sp->socket, FLAG_ABORT_CONNECTION);
            }
            test->state = IPERF_DONE;
            break;
        default:
            i_errno = IEMESSAGE;
            return (-1);
    }

    return (0);
}

void
iperf_test_reset(struct iperf_test *test)
{
    struct iperf_stream *sp;

    shutdown(test->ctrl_sck, FLAG_ABORT_CONNECTION);

    /* Free streams */
    while (!SLIST_EMPTY(&test->streams)) {
        sp = SLIST_FIRST(&test->streams);
        SLIST_REMOVE_HEAD(&test->streams, streams);
        iperf_free_stream(sp);
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

    test->ctrl_sck = -1;
    test->prot_listener = -1;

    test->bytes_sent = 0;

    test->reverse = 0;
    test->no_delay = 0;

    RTCS_FD_ZERO(&test->read_set);
    RTCS_FD_ZERO(&test->write_set);
    RTCS_FD_SET(test->listener, &test->read_set);
    test->max_fd = test->listener;
    
    test->num_streams = 1;
    test->settings->socket_bufsize = 0;
    test->settings->blksize = DEFAULT_TCP_BLKSIZE;
    test->settings->rate = RATE;   /* UDP only */
    test->settings->mss = 0;
    memset(test->cookie, 0, COOKIE_SIZE); 
}

int
iperf_run_server(struct iperf_test *test)
{
    int result, s, streams_accepted;
    rtcs_fd_set temp_read_set, temp_write_set;
    struct iperf_stream *sp;
    time_t sec, usec;

    // Open socket and listen
    if (iperf_server_listen(test) < 0) {
        return (-1);
    }

    test->state = IPERF_START;
    streams_accepted = 0;

    while (test->state != IPERF_DONE) {

        memcpy(&temp_read_set, &test->read_set, sizeof(rtcs_fd_set));
        memcpy(&temp_write_set, &test->write_set, sizeof(rtcs_fd_set));

        test->max_fd = (temp_read_set.fd_count>temp_write_set.fd_count) ? temp_read_set.fd_count : temp_write_set.fd_count;
        
        result = select(test->max_fd, &temp_read_set, &temp_write_set, NULL, 0);
        // Try it once again
        if (result < 0)
          result = select(test->max_fd, &temp_read_set, &temp_write_set, NULL, 0);
        if (result < 0) {
            i_errno = IESELECT;
            return (-1);
        } else if (result > 0) {
            if (RTCS_FD_ISSET(test->listener, &temp_read_set)) {
                if (test->state != CREATE_STREAMS) {
                    if (iperf_accept(test) < 0) {
                        return (-1);
                    }
                    RTCS_FD_CLR(test->listener, &temp_read_set);
                    RTCS_FD_CLR(test->listener, &temp_write_set);
                }
            }
            if (RTCS_FD_ISSET(test->ctrl_sck, &temp_read_set)) {
                if (iperf_handle_message_server(test) < 0)
                    return (-1);
                RTCS_FD_CLR(test->ctrl_sck, &temp_read_set);                
            }

            if (test->state == CREATE_STREAMS) {
                if (RTCS_FD_ISSET(test->prot_listener, &temp_read_set)) {
    
                    if ((s = test->protocol->i_accept(test)) == RTCS_SOCKET_ERROR)
                        return (-1);

                    if (!is_closed(s)) {
                        sp = iperf_new_stream(test, s);
                        if (!sp)
                            return (-1);

                        RTCS_FD_SET(s, &test->read_set);
                        RTCS_FD_SET(s, &test->write_set);
                        test->max_fd = (s > test->max_fd) ? s : test->max_fd;

                        streams_accepted++;
                        if (test->on_new_stream)
                            test->on_new_stream(sp);
                    }
                    RTCS_FD_CLR(test->prot_listener, &temp_read_set);
                }

                if (streams_accepted == test->num_streams) {
                    if (test->protocol->id != Ptcp) {
                        RTCS_FD_CLR(test->prot_listener, &test->read_set);
                        shutdown(test->prot_listener, FLAG_ABORT_CONNECTION);
                    } else { 
                        if (test->no_delay || test->settings->mss || test->settings->socket_bufsize) {
                            RTCS_FD_CLR(test->listener, &test->read_set);
                            shutdown(test->listener, FLAG_ABORT_CONNECTION);
                            if ((s = netannounce(test->settings->domain, Ptcp, test->bind_address, test->server_port)) == RTCS_SOCKET_ERROR) {
                                i_errno = IELISTEN;
                                return (-1);
                            }
                            test->listener = s;
                            test->max_fd = (s > test->max_fd ? s : test->max_fd);
                            RTCS_FD_SET(test->listener, &test->read_set);
                        }
                    }
                    test->prot_listener = -1;
                    test->state = TEST_START;
                    if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
                        i_errno = IESENDMESSAGE;
                        return (-1);
                    }
                    if (iperf_init_test(test) < 0)
                        return (-1);
                    test->state = TEST_RUNNING;
                    if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
                        i_errno = IESENDMESSAGE;
                        return (-1);
                    }
                }
            }

            if (test->state == TEST_RUNNING) {
                if (!test->reverse) {
                  // Regular mode. Server receives.
                  if (iperf_recv(test, &temp_read_set) < 0)
                      return (-1);
                } else {
                    // Reverse mode. Server sends.
                    if (iperf_send(test, &temp_write_set) < 0)
                       return (-1);
                }

                /* Perform callbacks */
                if (timer_expired(test->stats_timer)) {
                    test->stats_callback(test);
                    sec = (time_t) test->stats_interval;
                    usec = (test->stats_interval - sec) * 1000;
                    if (update_timer(test->stats_timer, sec, usec) < 0)
                        return (-1);
                }
                if (timer_expired(test->reporter_timer)) {
                    test->reporter_callback(test);
                    sec = (time_t) test->reporter_interval;
                    usec = (test->reporter_interval - sec) * 1000;
                    if (update_timer(test->reporter_timer, sec, usec) < 0)
                        return (-1);
                }
            }
        }
    }

    shutdown(test->ctrl_sck, FLAG_ABORT_CONNECTION);
    shutdown(test->listener, FLAG_ABORT_CONNECTION);

    return (0);
}

