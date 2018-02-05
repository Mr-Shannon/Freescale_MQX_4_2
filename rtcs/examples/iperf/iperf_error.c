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
#include "iperf_error.h"

int i_errno;

char *
iperf_strerror(int i_errnu)
{
    static char errstr[PSTRLEN];
    int len;

    len = sizeof(errstr);
    memset(errstr, 0, len);

    switch (i_errno) {
        case IENONE:
            snprintf(errstr, len, "No error");
            break;
        case IESERVCLIENT:
            snprintf(errstr, len, "Iperf cannot be both server and client");
            break;
        case IENOROLE:
            snprintf(errstr, len, "Iperf instance must either be a client (-c) or server (-s)");
            break;
        case IECLIENTONLY:
            snprintf(errstr, len, "Some option you are trying to set is client only");
            break;
        case IEDURATION:
            snprintf(errstr, len, "Test duration too long (maximum = %d seconds)", MAX_TIME);
            break;
        case IENUMSTREAMS:
            snprintf(errstr, len, "Number of parallel streams too large (maximum = %d)", MAX_STREAMS);
            break;
        case IEBLOCKSIZE:
            snprintf(errstr, len, "Block size too large (maximum = %d bytes)", MAX_BLOCKSIZE);
            break;
        case IEBUFSIZE:
            snprintf(errstr, len, "Socket buffer size too large (maximum = %d bytes)", MAX_TCP_BUFFER);
            break;
        case IEINTERVAL:
            snprintf(errstr, len, "Report interval too large (maximum = %d seconds)", MAX_INTERVAL);
            break;
        case IEMSS:
            snprintf(errstr, len, "TCP MSS too large (maximum = %d bytes)", MAX_MSS);
            break;
        case IENEWTEST:
            snprintf(errstr, len, "Unable to create a new test");
            break;
        case IEINITTEST:
            snprintf(errstr, len, "Test initialization failed");
            break;
        case IELISTEN:
            snprintf(errstr, len, "Unable to start listener for connections");
            break;
        case IECONNECT:
            snprintf(errstr, len, "Unable to connect to server");
            break;
        case IEACCEPT:
            snprintf(errstr, len, "Unable to accept connection from client");
            break;
        case IESENDCOOKIE:
            snprintf(errstr, len, "Unable to send cookie to server");
            break;
        case IERECVCOOKIE:
            snprintf(errstr, len, "Unable to receive cookie to server");
            break;
        case IECTRLWRITE:
            snprintf(errstr, len, "Unable to write to the control socket");
            break;
        case IECTRLREAD:
            snprintf(errstr, len, "Unable to read from the control socket");
            break;
        case IECTRLCLOSE:
            snprintf(errstr, len, "Control socket has closed unexpectedly");
            break;
        case IEMESSAGE:
            snprintf(errstr, len, "Received an unknown control message");
            break;
        case IESENDMESSAGE:
            snprintf(errstr, len, "Unable to send control message");
            break;
        case IERECVMESSAGE:
            snprintf(errstr, len, "Unable to receive control message");
            break;
        case IESENDPARAMS:
            snprintf(errstr, len, "Unable to send parameters to server");
            break;
        case IERECVPARAMS:
            snprintf(errstr, len, "Unable to receive parameters from client");
            break;
        case IEPACKAGERESULTS:
            snprintf(errstr, len, "Unable to package results");
            break;
        case IESENDRESULTS:
            snprintf(errstr, len, "Unable to send results");
            break;
        case IERECVRESULTS:
            snprintf(errstr, len, "Unable to receive results");
            break;
        case IESELECT:
            snprintf(errstr, len, "Select failed");
            break;
        case IECLIENTTERM:
            snprintf(errstr, len, "The client has terminated");
            break;
        case IESERVERTERM:
            snprintf(errstr, len, "The server has terminated");
            break;
        case IEACCESSDENIED:
            snprintf(errstr, len, "The server is busy running a test. try again later.");
            break;
        case IESETNODELAY:
            snprintf(errstr, len, "Unable to set TCP NODELAY");
            break;
        case IESETMSS:
            snprintf(errstr, len, "Unable to set TCP MSS");
            break;
        case IESETBUF:
            snprintf(errstr, len, "Unable to set socket buffer size");
            break;
        case IEREUSEADDR:
            snprintf(errstr, len, "Unable to reuse address on socket");
            break;
        case IENONBLOCKING:
            snprintf(errstr, len, "Unable to set socket to non-blocking");
            break;
        case IESETWINDOWSIZE:
            snprintf(errstr, len, "Unable to set socket window size");
            break;
        case IEPROTOCOL:
            snprintf(errstr, len, "Protocol does not exist");
            break;
        case IECREATESTREAM:
            snprintf(errstr, len, "Unable to create a new stream");
            break;
        case IEINITSTREAM:
            snprintf(errstr, len, "Unable to initialize stream");
            break;
        case IESTREAMLISTEN:
            snprintf(errstr, len, "Unable to start stream listener");
            break;
        case IESTREAMCONNECT:
            snprintf(errstr, len, "Unable to connect stream");
            break;
        case IESTREAMACCEPT:
            snprintf(errstr, len, "Unable to accept stream connection");
            break;
        case IESTREAMWRITE:
            snprintf(errstr, len, "Unable to write to stream socket");
            break;
        case IESTREAMREAD:
            snprintf(errstr, len, "Unable to read from stream socket");
            break;
        case IESTREAMCLOSE:
            snprintf(errstr, len, "Stream socket has closed unexpectedly");
            break;
        case IESTREAMID:
            snprintf(errstr, len, "Stream has an invalid id");
            break;
        case IENEWTIMER:
            snprintf(errstr, len, "Unable to create new timer");
            break;
        case IEUPDATETIMER:
            snprintf(errstr, len, "Unable to update timer");
            break;
    }

    return (errstr);
}

void
iperf_error(char *estr)
{
    fprintf(stderr, "%s: %s\n", estr, iperf_strerror(i_errno));
}
