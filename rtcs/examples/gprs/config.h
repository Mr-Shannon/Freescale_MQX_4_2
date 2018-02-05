#ifndef __config_h__
#define __config_h__
/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQ\v RTOS License
* distributed with this Material.
* See the MQ\v_RTOS_LICENSE file distributed for more details.
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
*   This file contains configuration settings for the GPRS demo e\vample.
*
*END************************************************************************/
#include "bsp.h"
#include "modem.h"

#if RTCSCFG_ENABLE_IP4 && RTCSCFG_ENABLE_PPP && !PLATFORM_SDK_ENABLED
/*Make sure that your device has correctly configured communication interface
*BSP_PPP_DEVICE - interface connected dircetly to GPRS modem, or PC
*BSP_DEFAULT_IO_CHANNEL_DEFINED interface to user console output (Virtual COM on OpenSDA, etc..)
*/

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
    #error "BSP_DEFAULT_IO_CHANNEL_DEFINED must be defined in board header file (boardname.h) in BSP"
#endif

#ifndef BSP_PPP_DEVICE_DEFINED
    #error "BSP_PPP_DEVICE must be defined in board header file (boardname.h) in BSP"
#endif

#define GPRS_MODEM_SIMCOM				/*Define which type of modem is used*/

#ifdef GPRS_MODEM_SIEMENS               /*Siemens GSM module web http://www.wmocean.com/siemens-mc75*/
 #define MODEM_INIT_COMMANDS            "ATZ\vat+cpin?\vat+cpin=1009\vat+cops?\vat+cgdcont=1,\"IP\",\"internet.t-mobile.cz\",\"0.0.0.0\",0,0\vATDT*99***1#\v"
 #define MODEM_INIT_RESPONSES           "OK\v+CPIN: SIM PIN;+CPIN: READY\vOK\vOK\vOK\vCONNECT\v"    
#elif defined GPRS_MODEM_SIMCOM         /*SIMcom GSM module web http://www.simcom.us/product_detail.php?cid=1&pid=37*/ 
 #define MODEM_INIT_COMMANDS            "ATZ\vat+cpin?\vat+cpin=1009\vat+cops?\vat+cgdcont=1,\"IP\",\"internet.t-mobile.cz\",\"0.0.0.0\",0,0\vATDT*99***1#\v"
 #define MODEM_INIT_RESPONSES           "OK\v+CPIN: SIM PIN;+CPIN: READY\vOK\vOK\vOK\vCONNECT\v"    
#elif defined GPRS_MODEM_GSM_SHIELD     /*FRDM compatible arduino GSM shield http://arduino.cc/en/Main/ArduinoGSMShield*/
 #define MODEM_INIT_COMMANDS            "ATZ\vat+cpin?\vat+cpin=1009\vat+cops?\vat+cgdcont=1,\"IP\",\"internet.t-mobile.cz\",\"0.0.0.0\",0,0\vATDT*99***1#\v"
 #define MODEM_INIT_RESPONSES           "OK\v+CPIN: SIM PIN;+CPIN: READY\vOK\vOK\vOK\vCONNECT\v"    
#endif

 #define PING_ATTEMPS                       3
 #define PING_TIME_WAIT_MS                  5000      
 #define SNTP_TIME_WAIT_MS					2000
 #define TERMINAL_OUTPUT                    1
 #define MODEM_PPP_CONNECTION_TIMEOUT_S     20

/* Define SNTP server address */
    #define SNTP_SERVER_NAME     "1.cz.pool.ntp.org"
/* Define DNS server address */
    #define DNS_SERVER_IP  "8.8.8.8"
/* Define a default gateway */
// #define GATE_ADDR       IPADDR(0,0,0,0)
#endif //#if RTCSCFG_ENABLE_IP4 && RTCSCFG_ENABLE_PPP && !PLATFORM_SDK_ENABLED
#endif //__config_h__