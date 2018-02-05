                          GPRS connection application

1. Introduction
---------------
This is the RTCS example that is used to demonstrate GPRS modem library as part of RTCS.
The example allows to set up serial GPRS modem using series of preconfigured AT commands
and start internet connection. Succesfull connection is demonstrated by passing PING 
and SNTP feature for time synchronization of RTCS. 

1.1 Content of example directory
--------------------------------
Example directory consist of following folders and files:
  - build: This folder contains IDE projects and project configuration.
  - gprs_main.c: Main source file including modem initialization function 
                 call and internet connection testing example.
  - config.h: Configuration of an example. Initialization commands, network
              configuration.
  - _readme.txt: This README file.

2. Application configuration
----------------------------
This chapter contains description of all configuration options available in the 
GPRS example.

2.1 Default Example Configuration
---------------------------------
All example configuration is done in the file "config.h" in the example folder and "user_config.h" in the BSP.
By default following configuration is used:

- Modem vendor:
  - SIMCOM
- Modem initialization commands: 
  - MODEM_INIT_COMMANDS     "ATZ\v
                            at+cpin?\v
                            at+cpin=1009\v
                            at+cops?\v
                            at+cgdcont=1,\"IP\",\"internet.t-mobile.cz\",\"0.0.0.0\",0,0\v
                            ATDT*99***1#\v"

  - MODEM_INIT_RESPONSES    "OK\v
                            +CPIN: SIM PIN;+CPIN: READY\v
                            OK\v
                            OK\v
                            OK\v
                            CONNECT\v"

--------------------------------!CAUTION!---------------------------------------
Default example settings MUST be changed for each SIM card. In default 
configuration modem is set for T-mobile in Czech republic. Set modem commands 
properly according to YOUR GPRS connection provider. Do not forget to change 
SIM PIN (at+cpin=XXXX) and provider initialization command (at+cgdcont)!
--------------------------------------------------------------------------------

  - Number of ping atempts: 3
  - Ping function timeout in ms: 5000
  - Time synchronization timeout in ms: 2000
  - Terminal output used for debuging: 0
  - Point to point connection timeout in s: 20
  - SNTP server domain name: uk.pool.ntp.org
  - DNS server ip address: 8.8.8.8

Following is list of configuration macros in file "user_config.h" in the bsp_boardname.
  - Macro BSPCFG_ENABLE_TTYD:   0
  - Macro BSPCFG_ENABLE_ITTYD:  1
  - Macro RTCSCFG_ENABLE_PPP:   1
  - Macro RTCSCFG_ENABLE_DNS:   1
  - Macro BSPCFG_UARTX_QUEUE_SIZE: 128  
  - Macro BSPCFG_SCI3_QUEUE_SIZE: 128
  - Macro BSPCFG_SCI3_BAUD_RATE: 115200

2.2 Configuration macros
------------------------
Following is list of configuration macros in file "config.h"

 - Macro GPRS_MODEM_SIMCOM defines which type (vendor) of modem is used
 - Macro MODEM_INIT_COMMANDS defines AT commands sequence needed for modem initialization
 - Macro MODEM_INIT_RESPONSES defines expected responses on AT commands.
 - Macro PING_ATTEMPS defines number of pings to be send on specified domain name, or ip address
 - Macro PING_TIME_WAIT_MS defines ping function timeout, until it returns timeout error      
 - Macro SNTP_TIME_WAIT_MS defines time synchronization function timeout, until it returns timeout error
 - Macro MODEM_PPP_CONNECTION_TIMEOUT_S defines time to wait for network until connection will be established
 - Macro SNTP_SERVER_NAME defines domain name of sntp server, used for demo
 - Macro DNS_SERVER_IP defines DNS server IP address used for domain name resolution

3. Running the application
--------------------------

1) Prepare your evaluation board according to the "MQX Getting started" document.
   Pay special attention to correct jumper settings.
2) Connect your PC to the evaluation board using an usb cable.
3) Connect the evaluation board and your serial modem with RS232 interface cable.
4) Prepare your modem according to modem user guide (inser sim card, plug in power adapter, etc...) 
5) Start Terminal application on your PC. 
   Set serial port settings to 115200 baud rate, no parity and 8 bits.
6) Compile all required libraries (BSP, PSP, RTCS).
7) Compile, load and run the application. Following message should show up in 
   the terminal window:
   "GPRS modem connecting..."
8) After modem is connected, following message should show up in the terminal window:
   "GPRS modem connected successfuly"
9) Aplication will try to ping NTP server address and sync system time with it.
10) Modem is disconnected automaticaly at the end of demo.