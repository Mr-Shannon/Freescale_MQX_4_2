/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
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
*   This file contains the source for the GPRS demo example.
*
*END************************************************************************/

#include <string.h>
#include <mqx.h>
#include <bsp.h>
#include <rtcs.h>
#include "config.h"  

#if RTCSCFG_ENABLE_IP4 && RTCSCFG_ENABLE_PPP && !PLATFORM_SDK_ENABLED

#if ! RTCSCFG_ENABLE_VIRTUAL_ROUTES
#error This application requires RTCSCFG_ENABLE_VIRTUAL_ROUTES defined non-zero in user_config.h. Please recompile libraries (BSP, RTCS) with this option.
#endif

#if ! RTCSCFG_ENABLE_GATEWAYS
#error This application requires RTCSCFG_ENABLE_GATEWAYS defined non-zero in user_config.h. Please recompile libraries (BSP, RTCS) with this option.
#endif

#if ! RTCSCFG_ENABLE_PPP
#error This application requires RTCSCFG_ENABLE_PPP defined non-zero in user_config.h. Please recompile libraries (BSP, RTCS) with this option.
#endif

#if ! RTCSCFG_ENABLE_DNS
#error This application requires RTCSCFG_ENABLE_DNS defined non-zero in user_config.h. Please recompile libraries (BSP, RTCS) with this option.
#endif

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#if PPP_SECRETS_NOT_SHARED
#error This application requires PPP_SECRETS_NOT_SHARED defined to zero in /src/rtcs/source/include/ppp.h. Please recompile RTCS with this option.
#endif

#define MAIN_TASK 1

void network_ping(struct addrinfo *addrinfo_res);
void network_time_sync(struct addrinfo *addrinfo_res);
void print_error(uint32_t error);
void Main_task (uint32_t);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index,   Function,   Stack,  Priority,   Name,   Attributes,          Param, Time Slice */
    { MAIN_TASK,    Main_task,  5000,   9,          "Main", MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};


/*TASK*-----------------------------------------------------------------
*
* Task Name      : Main_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void Main_task(uint32_t temp)
{  
    uint32_t            gprs_handle;
    uint32_t            error;
    struct addrinfo     *addrinfo_result;
    
    addrinfo_result = NULL;

    MODEM_PARAM_STRUCT          modem_params;
    PPP_PARAM_STRUCT            ppp_params;

    _mem_zero(&ppp_params, sizeof(ppp_params));
    _mem_zero(&modem_params, sizeof(modem_params));
    modem_params.terminal_device = BSP_DEFAULT_IO_CHANNEL;
    modem_params.modem_device = BSP_PPP_DEVICE;
    modem_params.commands = MODEM_INIT_COMMANDS;
    modem_params.responses = MODEM_INIT_RESPONSES;
    modem_params.ppp_connection_timeout = MODEM_PPP_CONNECTION_TIMEOUT_S; 
    modem_params.ppp_enable = TRUE;
    modem_params.ppp_init_params = &ppp_params;
    modem_params.dns_server_address = DNS_SERVER_IP;
    ppp_params.device = BSP_PPP_DEVICE;
    ppp_params.local_addr = 0;
    ppp_params.remote_addr = 0;
    ppp_params.listen_flag = 0;
   
    error = RTCS_create();
    if (error != RTCS_OK) 
    {
       fprintf(stdout, "\nRTCS failed to initialize, error = %X. Application blocked.\n", error);
    }
    _IP_forward = TRUE;
    fprintf(stdout, "GPRS modem connecting...\n");
    gprs_handle = MODEM_connect(&modem_params);
    
    if (gprs_handle)
    {
        fprintf(stdout, "GPRS modem connected successfuly\n");
        fprintf(stdout, "Trying to resolve hostname\n"); 
        if (getaddrinfo(SNTP_SERVER_NAME, NULL, NULL, &addrinfo_result) == 0)
        {
            fprintf(stdout, "Hostname resolution successful\n");
            network_ping(addrinfo_result);
            network_time_sync(addrinfo_result);        
        }
        else 
        {
            fprintf(stdout, "Hostname resolution failed\n");
        }
        MODEM_disconnect(gprs_handle);
    }
    else
    {
        printf("GPRS connection failed\n");
    }
    _mqx_exit(0);
     
}

void network_ping(struct addrinfo *addrinfo_res)
{    
  uint32_t            pingcount = 0;  
  uint32_t            error = 0;

  fprintf(stdout, "Pinging on address:%s\n", SNTP_SERVER_NAME);    
  while (pingcount <= PING_ATTEMPS) 
  {
    /* Set ping parameters.*/  
    PING_PARAM_STRUCT ping_params;
    /* Zero input parameters.*/
    _mem_zero(&ping_params, sizeof(ping_params));
    /* Set IPv4 addr. family */
    ping_params.addr = *addrinfo_res->ai_addr;
    /* Wait interval in milliseconds */
    ping_params.timeout = 1000;
    error = RTCS_ping(&ping_params);
    if (error!=RTCS_OK)
    {
        fprintf(stdout, "PING_ERROR: ");
        print_error(error);
    }
    else
    {
        if(ping_params.round_trip_time < 1)
        {
            fprintf(stdout, "Reply time<1ms\n"); 
        }
        else
        {
            fprintf(stdout, "Reply time=%ldms\n", ping_params.round_trip_time);
        }         
    }
    pingcount++;   
  }
}

void network_time_sync(struct addrinfo *addrinfo_res)
{ 
    DATE_STRUCT     time_rtc;
    TIME_STRUCT     time_mqx;
    uint32_t        error = 0;
    fprintf(stdout, "\nTrying to sync Time:\n");
    _ip_address     server;

    if (addrinfo_res->ai_addr->sa_family == AF_INET)
    {
        server = ((struct sockaddr_in *) addrinfo_res->ai_addr)->sin_addr.s_addr;
    }
    else
    {
        server = 0;
    }
    
    error = SNTP_oneshot(server, SNTP_TIME_WAIT_MS);
    if (error!=RTCS_OK)	
    {      
        fprintf(stdout, "SNTP_ERROR: ");
        print_error(error);
    }    
    else
    {
        fprintf(stdout, "Time sync complete:\n");
        _time_get(&time_mqx);
        _time_to_date(&time_mqx,&time_rtc);
        fprintf(stdout, "Current Time: %02d/%02d/%02d %02d:%02d:%02d\n",
        time_rtc.YEAR,time_rtc.MONTH,time_rtc.DAY,time_rtc.HOUR,time_rtc.MINUTE,time_rtc.SECOND);
    }
}

void print_error(uint32_t error)
{
        if(error==RTCSERR_TIMEOUT)
            fprintf(stdout, "RTCS_Timeout\n"); 
        else if(error==RTCSERR_INVALID_ADDRESS)
            fprintf(stdout, "RTCSERR_INVALID_ADDRESS\n");
        else if(error==RTCSERR_INVALID_PARAMETER)
            fprintf(stdout, "RTCSERR_INVALID_PARAMETER\n");
        else if(error==RTCSERR_READ_ABORTED)
            fprintf(stdout, "RTCSERR_READ_ABORTED\n");
        else if(error==RTCSERR_OUT_OF_BUFFERS)
            fprintf(stdout, "RTCSERR_OUT_OF_BUFFERS\n");
        else
            fprintf(stdout, "error = 0x%04lX\n", error);
}

#endif //RTCSCFG_ENABLE_IP4