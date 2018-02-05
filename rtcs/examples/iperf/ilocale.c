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

/*--------------------------------------------------------------- 
 * Copyright (c) 1999,2000,2001,2002,2003                              
 * The Board of Trustees of the University of Illinois            
 * All Rights Reserved.                                           
 *--------------------------------------------------------------- 
 * Permission is hereby granted, free of charge, to any person    
 * obtaining a copy of this software (Iperf) and associated       
 * documentation files (the "Software"), to deal in the Software  
 * without restriction, including without limitation the          
 * rights to use, copy, modify, merge, publish, distribute,        
 * sublicense, and/or sell copies of the Software, and to permit     
 * persons to whom the Software is furnished to do
 * so, subject to the following conditions: 
 *
 *     
 * Redistributions of source code must retain the above 
 * copyright notice, this list of conditions and 
 * the following disclaimers. 
 *
 *     
 * Redistributions in binary form must reproduce the above 
 * copyright notice, this list of conditions and the following 
 * disclaimers in the documentation and/or other materials 
 * provided with the distribution. 
 * 
 *     
 * Neither the names of the University of Illinois, NCSA, 
 * nor the names of its contributors may be used to endorse 
 * or promote products derived from this Software without
 * specific prior written permission. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE CONTIBUTORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 * ________________________________________________________________
 * National Laboratory for Applied Network Research 
 * National Center for Supercomputing Applications 
 * University of Illinois at Urbana-Champaign 
 * http://www.ncsa.uiuc.edu
 * ________________________________________________________________ 
 *
 * Locale.c
 * by Ajay Tirumala <tirumala@ncsa.uiuc.edu>
 * & Mark Gates <mgates@nlanr.net>
 * -------------------------------------------------------------------
 * Strings and other stuff that is locale specific.
 * ------------------------------------------------------------------- */

#include "version.h"


/* -------------------------------------------------------------------
 * usage
 * ------------------------------------------------------------------- */

const char usage_short[] = "Usage: iperf [-s|-c host] [options]\n"
                           "Try `iperf -h' for more information.\n";

const char usage_long1[] = "Usage: iperf [-s|-c host] [options]\n"
                           "       iperf [-h|--help] [-v|--version]\n\n"
                           "Client/Server:\n"
                           "  -f  [kmgKMG]  format to report: Kbits, Mbits, KBytes, MBytes\n"
                           "  -i  #         seconds between periodic bandwidth reports\n"
                           "  -l  #[KMG]    length of buffer to read or write (default 8 KB)\n"
                           "  -m            print TCP maximum segment size (MTU - TCP/IP header)\n"
                           "  -p  #         server port to listen on/connect to\n"                             
                           "  -u            use UDP rather than TCP\n"
                           "  -w  #[KMG]    TCP window size (socket buffer size)\n"
                           "  -M  #         set TCP maximum segment size (MTU - 40 bytes)\n"
                           "  -N            set TCP no delay, disabling Nagle's Algorithm\n"
                           "  -v            print version information and quit\n"
                           "  -V            more verbose output\n"
                           "  -6            use IPv6 rather than IPv4\n"
                           "Server specific:\n"
                           "  -s            run in server mode\n";

const char usage_long2[] = "Client specific:\n"
                           "  -b  #[KMG]    for UDP, bandwidth to send at in bits/sec\n"
                           "                (default 1 Mbit/sec, implies -u)\n"
                           "  -c  <host>    run in client mode, connecting to <host>\n"
                           "  -n  #[KMG]    number of bytes to transmit (instead of -t)\n"
                           "  -t  #         time in seconds to transmit for (default 10 secs)\n"
                           "  -P  #         number of parallel client threads to run\n"
                           "  -R            reverse mode\n"
                           "Miscellaneous:\n"
                           "  -h            print this message and quit\n\n"
                           "[KMG] Indicates options that support a K,M, or G suffix for kilo-, mega-, or giga-\n\n"
                           "Report bugs to <iperf-users@lists.sourceforge.net>\n";

const char version[] = "iperf version " IPERF_VERSION " (" IPERF_VERSION_DATE ") \n";

/* -------------------------------------------------------------------
 * settings
 * ------------------------------------------------------------------- */

const char seperator_line[] =
"------------------------------------------------------------\n";

const char server_port[] =
"Server listening on %s port %d\n";

const char client_port[] =
"Client connecting to %s, %s port %d\n";

const char bind_address[] =
"Binding to local address %s\n";

const char multicast_ttl[] =
"Setting multicast TTL to %d\n";

const char join_multicast[] =
"Joining multicast group  %s\n";

const char client_datagram_size[] =
"Sending %d byte datagrams\n";

const char server_datagram_size[] =
"Receiving %d byte datagrams\n";

const char tcp_window_size[] =
"TCP window size";

const char udp_buffer_size[] =
"UDP buffer size";

const char window_default[] =
"(default)";

const char wait_server_threads[] =
"Waiting for server threads to complete. Interrupt again to force quit.\n";

const char test_start_time[] =
"Starting Test: protocol: %s, %d streams, %d byte blocks, %d second test\n";

const char test_start_bytes[] =
"Starting Test: protocol: %s, %d streams, %d byte blocks, %llu bytes to send\n";


/* -------------------------------------------------------------------
 * reports
 * ------------------------------------------------------------------- */

const char report_read_lengths[] =
"[%3d] Read lengths occurring in more than 5%% of reads:\n";

const char report_read_length_times[] =
"[%3d] %5d bytes read %5d times (%.3g%%)\n";

const char report_bw_header[] =
"[ ID]       Interval        Transfer     Bandwidth\n";

const char report_bw_format[] =
"[%3d] %i.%02d-%i.%02d sec  %ss  %ss/sec\n";

const char report_sum_bw_format[] =
"[SUM] %i.%02d-%i.%02d sec  %ss  %ss/sec\n";

const char report_bw_jitter_loss_header[] =
"[ ID]       Interval        Transfer     Bandwidth       Jitter   Lost/Total \
Datagrams\n";

const char report_bw_jitter_loss_format[] =
"[%3d] %i.%02d-%i.%02d sec  %ss  %ss/sec  %d.%d ms %4d/%5d (%i%%)\n";

const char report_sum_bw_jitter_loss_format[] =
"[SUM] %4.2f-%4.2f sec  %ss  %ss/sec  %5.3f ms %4d/%5d (%.2g%%)\n";

const char report_outoforder[] =
"[%3d] %4.1f-%4.1f sec  %d datagrams received out-of-order\n";

const char report_sum_outoforder[] =
"[SUM] %4.1f-%4.1f sec  %d datagrams received out-of-order\n";

const char report_peer[] =
"[%3d] local %s port %u connected with %s port %u\n";

const char report_mss_unsupported[] =
"[%3d] MSS and MTU size unknown (TCP_MAXSEG not supported by OS?)\n";

const char report_mss[] =
"[%3d] MSS size %d bytes (MTU %d bytes, %s)\n";

const char report_datagrams[] =
"[%3d] Sent %d datagrams\n";

const char report_sum_datagrams[] =
"[SUM] Sent %d datagrams\n";

const char server_reporting[] =
"[%3d] Server Report:\n";

const char reportCSV_peer[] =
"%s,%u,%s,%u";


#ifdef HAVE_QUAD_SUPPORT
#ifdef HAVE_PRINTF_QD
const char reportCSV_bw_format[] =
"%s,%s,%d,%.1f-%.1f,%qd,%qd\n";

const char reportCSV_bw_jitter_loss_format[] =
"%s,%s,%d,%.1f-%.1f,%qd,%qd,%.3f,%d,%d,%.3f,%d\n";
#else // HAVE_PRINTF_QD
const char reportCSV_bw_format[] =
"%s,%s,%d,%.1f-%.1f,%lld,%lld\n";

const char reportCSV_bw_jitter_loss_format[] =
"%s,%s,%d,%.1f-%.1f,%lld,%lld,%.3f,%d,%d,%.3f,%d\n";
#endif // HAVE_PRINTF_QD
#else // HAVE_QUAD_SUPPORT

const char reportCSV_bw_format[] =
"%s,%s,%d,%.1f-%.1f,%d,%d\n";

const char reportCSV_bw_jitter_loss_format[] =
"%s,%s,%d,%.1f-%.1f,%d,%d,%.3f,%d,%d,%.3f,%d\n";
#endif //HAVE_QUAD_SUPPORT
/* -------------------------------------------------------------------
 * warnings
 * ------------------------------------------------------------------- */

const char warn_window_requested[] =
" (WARNING: requested %s)";

const char warn_window_small[] = "\
WARNING: TCP window size set to %d bytes. A small window size\n\
will give poor performance. See the Iperf documentation.\n";

const char warn_delay_large[] =
"WARNING: delay too large, reducing from %.1f to 1.0 seconds.\n";

const char warn_no_pathmtu[] =
"WARNING: Path MTU Discovery may not be enabled.\n";

const char warn_no_ack[]=
"[%3d] WARNING: did not receive ack of last datagram after %d tries.\n";

const char warn_ack_failed[]=
"[%3d] WARNING: ack of last datagram failed after %d tries.\n";

const char warn_fileopen_failed[]=
"WARNING: Unable to open file stream for transfer\n\
Using default data stream. \n";

const char unable_to_change_win[]=
"WARNING: Unable to change the window size\n";

const char opt_estimate[]=
"Optimal Estimate\n";

const char report_interval_small[] =
"WARNING: interval too small, increasing from %3.2f to 0.5 seconds.\n";

const char warn_invalid_server_option[] =
"WARNING: option -%c is not valid for server mode\n";

const char warn_invalid_client_option[] =
"WARNING: option -%c is not valid for client mode\n";

const char warn_invalid_compatibility_option[] =
"WARNING: option -%c is not valid in compatibility mode\n";

const char warn_implied_udp[] =
"WARNING: option -%c implies udp testing\n";

const char warn_implied_compatibility[] =
"WARNING: option -%c has implied compatibility mode\n";

const char warn_buffer_too_small[] =
"WARNING: the UDP buffer was increased to %d for proper operation\n";

const char warn_invalid_single_threaded[] =
"WARNING: option -%c is not valid in single threaded versions\n";

const char warn_invalid_report_style[] =
"WARNING: unknown reporting style \"%s\", switching to default\n";

const char warn_invalid_report[] =
"WARNING: unknown reporting type \"%c\", ignored\n valid options are:\n\t exclude: C(connection) D(data) M(multicast) S(settings) V(server) report\n\n";

#ifdef __cplusplus
} /* end extern "C" */
#endif

