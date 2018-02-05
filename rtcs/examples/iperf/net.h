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

#ifndef __NET_H
#define __NET_H

int netdial(int, int, char *, char *, int);
int netannounce(int, int, char *, int);
int Nwrite(int, char *, int, int);
int Nread(int fd, char *buf, int count, int prot);
int getsock_tcp_mss(int);
int set_tcp_options(int, int, int);
int setnonblocking(int);

#define NET_SOFTERROR -1
#define NET_HARDERROR -2

unsigned long long htonll(unsigned long long);
unsigned long long ntohll(unsigned long long);

/* XXX: Need a better check for byte order */
#if BYTE_ORDER == BIG_ENDIAN
#define HTONLL(n) (n)
#define NTOHLL(n) (n)
#else
#define HTONLL(n) ((((unsigned long long)(n) & 0xFF) << 56) | \
                   (((unsigned long long)(n) & 0xFF00) << 40) | \
                   (((unsigned long long)(n) & 0xFF0000) << 24) | \
                   (((unsigned long long)(n) & 0xFF000000) << 8) | \
                   (((unsigned long long)(n) & 0xFF00000000) >> 8) | \
                   (((unsigned long long)(n) & 0xFF0000000000) >> 24) | \
                   (((unsigned long long)(n) & 0xFF000000000000) >> 40) | \
                   (((unsigned long long)(n) & 0xFF00000000000000) >> 56))

#define NTOHLL(n) ((((unsigned long long)(n) & 0xFF) << 56) | \
                   (((unsigned long long)(n) & 0xFF00) << 40) | \
                   (((unsigned long long)(n) & 0xFF0000) << 24) | \
                   (((unsigned long long)(n) & 0xFF000000) << 8) | \
                   (((unsigned long long)(n) & 0xFF00000000) >> 8) | \
                   (((unsigned long long)(n) & 0xFF0000000000) >> 24) | \
                   (((unsigned long long)(n) & 0xFF000000000000) >> 40) | \
                   (((unsigned long long)(n) & 0xFF00000000000000) >> 56))
#endif

#define htonll(n) HTONLL(n)
#define ntohll(n) NTOHLL(n)

#endif

