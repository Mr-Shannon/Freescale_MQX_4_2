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

#include "iperf.h"
#include "iperf_api.h"
#include "iperf_client_api.h"
#include "iperf_error.h"
#include "iperf_util.h"
#include "net.h"
#include "itimer.h"

int
iperf_create_streams(struct iperf_test *test)
{
    int i, s;
    struct iperf_stream *sp;
    int option_udp_nonblock = 1;

    for (i = 0; i < test->num_streams; ++i) {

        if ((s = test->protocol->i_connect(test)) == RTCS_SOCKET_ERROR)
            return (-1);
        
        if (test->protocol->id == Pudp){ 
            if (setsockopt(s, SOL_UDP, RTCS_SO_UDP_NONBLOCK_RX, &option_udp_nonblock, sizeof(option_udp_nonblock)))
              return (-1);
        }

        RTCS_FD_SET(s, &test->read_set);
        RTCS_FD_SET(s, &test->write_set);
        test->max_fd = (test->max_fd < s) ? s : test->max_fd;

        sp = iperf_new_stream(test, s);
        if (!sp)
            return (-1);

        /* Perform the new stream callback */
        if (test->on_new_stream)
            test->on_new_stream(sp);
    }

    return (0);
}

int
iperf_handle_message_client(struct iperf_test *test)
{
    int rval;

    if ((rval = recv(test->ctrl_sck, &test->state, sizeof(char), 0)) <= 0) {
        if (rval == 0) {
            i_errno = IECTRLCLOSE;
            return (-1);
        } else {
            i_errno = IERECVMESSAGE;
            return (-1);
        }
    }

    switch (test->state) {
        case PARAM_EXCHANGE:
            if (iperf_exchange_parameters(test) < 0)
                return (-1);
            if (test->on_connect)
                test->on_connect(test);
            break;
        case CREATE_STREAMS:
            if (iperf_create_streams(test) < 0)
                return (-1);
            break;
        case TEST_START:
            if (iperf_init_test(test) < 0)
                return (-1);
            break;
        case TEST_RUNNING:
            break;
        case EXCHANGE_RESULTS:
            if (iperf_exchange_results(test) < 0)
                return (-1);
            break;
        case DISPLAY_RESULTS:
            if (test->on_test_finish)
                test->on_test_finish(test);
            iperf_client_end(test);
            break;
        case IPERF_DONE:
            break;
        case SERVER_TERMINATE:
            i_errno = IESERVERTERM;
            return (-1);
        case ACCESS_DENIED:
            i_errno = IEACCESSDENIED;
            return (-1);
        default:
            i_errno = IEMESSAGE;
            return (-1);
    }

    return (0);
}



/* iperf_connect -- client to server connection function */
int
iperf_connect(struct iperf_test *test)
{
    RTCS_FD_ZERO(&test->read_set);
    RTCS_FD_ZERO(&test->write_set);

    get_uuid(test->cookie);

    /* Create and connect the control channel */
    test->ctrl_sck = netdial(test->settings->domain, Ptcp, test->bind_address, test->server_hostname, test->server_port);
    if (test->ctrl_sck == RTCS_SOCKET_ERROR) {
        i_errno = IECONNECT;
        return (-1);
    }

    if (Nwrite(test->ctrl_sck, test->cookie, COOKIE_SIZE, Ptcp) < 0) {
        i_errno = IESENDCOOKIE;
        return (-1);
    }

    RTCS_FD_SET(test->ctrl_sck, &test->read_set);
    RTCS_FD_SET(test->ctrl_sck, &test->write_set);

    return (0);
}


int
iperf_client_end(struct iperf_test *test)
{
    struct iperf_stream *sp;

    /* Close all stream sockets */
    SLIST_FOREACH(sp, &test->streams, streams) {
        shutdown(sp->socket, FLAG_ABORT_CONNECTION);
    }

    /* show final summary */
    test->reporter_callback(test);

    test->state = IPERF_DONE;
    if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
        i_errno = IESENDMESSAGE;
        return (-1);
    }
    shutdown(test->ctrl_sck, FLAG_ABORT_CONNECTION);
    
    return (0);
}



int
iperf_run_client(struct iperf_test * test)
{
    int result;
    rtcs_fd_set temp_read_set, temp_write_set;
    uint32_t timeout = 15000;
    time_t sec, usec;

    /* Start the client and connect to the server */
    if (iperf_connect(test) < 0) {
        return (-1);
    }

    while (test->state != IPERF_DONE) {

        _mem_copy(&test->read_set, &temp_read_set, sizeof(rtcs_fd_set));
        _mem_copy(&test->write_set, &temp_write_set, sizeof(rtcs_fd_set));
        
        test->max_fd = (temp_read_set.fd_count>temp_write_set.fd_count) ? temp_read_set.fd_count : temp_write_set.fd_count;

        result = select(test->max_fd, &temp_read_set, &temp_write_set, NULL, timeout);
        if (result < 0) {
            i_errno = IESELECT;
            return (-1);
        } else if (result > 0) {
            if (RTCS_FD_ISSET(test->ctrl_sck, &temp_read_set)) {
                if (iperf_handle_message_client(test) < 0)
                    return (-1);
                RTCS_FD_CLR(test->ctrl_sck, &temp_read_set);
            }

            if (test->state == TEST_RUNNING) {
                
              if (!test->reverse) {
                // Regular mode. Client sends.
                if (iperf_send(test, &temp_write_set) < 0)
                    return (-1);
              } else {
                  // Reverse mode. Client receives.
                  if (iperf_recv(test, &temp_read_set) < 0)             
                        return (-1);
                }

                /* Perform callbacks */
                if (timer_expired(test->stats_timer)) {
                    test->stats_callback(test);
                    sec = (time_t) test->stats_interval;
                    usec = (test->stats_interval - sec) * SEC_TO_US;
                    if (update_timer(test->stats_timer, sec, usec) < 0)
                        return (-1);
                }
                if (timer_expired(test->reporter_timer)) {
                    test->reporter_callback(test);
                    sec = (time_t) test->reporter_interval;
                    usec = (test->reporter_interval - sec) * SEC_TO_US;
                    if (update_timer(test->reporter_timer, sec, usec) < 0)
                        return (-1);
                }

                /* Send TEST_END if all data has been sent or timer expired */
                if (all_data_sent(test) || timer_expired(test->timer)) {
                    test->stats_callback(test);
                    test->state = TEST_END;
                    if (Nwrite(test->ctrl_sck, &test->state, sizeof(char), Ptcp) < 0) {
                        i_errno = IESENDMESSAGE;
                        return (-1);
                    }
                }
            }
        }
    }

    return (0);
}
