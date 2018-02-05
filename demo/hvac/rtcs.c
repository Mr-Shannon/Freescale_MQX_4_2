/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
* Copyright 2004-2008 Embedded Access Inc.
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
*   Example of HVAC using RTCS.
*
*
*END************************************************************************/

#include "hvac.h"

#if DEMOCFG_USE_WIFI
#include "string.h"
#endif

#if DEMOCFG_ENABLE_RTCS

#include <ipcfg.h>
#include <hvac.h>
#if (DEMOCFG_ENABLE_FTP_SERVER+DEMOCFG_ENABLE_TELNET_SERVER) != 1
#warning Please enable one of the network services. The restriction is only for RAM size limited devices.
#endif

// ftp root dir
#define FTPSRV_ROOTDIR "c:\\";

/* Server parameters */
FTPSRV_PARAM_STRUCT ftpsrv_params;

/* FTP users */
const FTPSRV_AUTH_STRUCT ftpsrv_users[] =
{
    {"developer", "freescale", NULL},
    {0, 0, 0}
};

extern const SHELL_COMMAND_STRUCT Telnetsrv_commands[];

void HVAC_initialize_networking(void) 
{
   int32_t                  error;
   IPCFG_IP_ADDRESS_DATA   ip_data;
   _enet_address           enet_address;

#if DEMOCFG_USE_POOLS && defined(DEMOCFG_RTCS_POOL_ADDR) && defined(DEMOCFG_RTCS_POOL_SIZE)
    /* use external RAM for RTCS buffers */
    _RTCS_mem_pool = _mem_create_pool((void *)DEMOCFG_RTCS_POOL_ADDR, DEMOCFG_RTCS_POOL_SIZE);
#endif

   /* runtime RTCS configuration for devices with small RAM, for others the default BSP setting is used */
   _RTCSPCB_init = 4;
   _RTCSPCB_grow = 2;
   _RTCSPCB_max = 20;
   _RTCS_msgpool_init = 4;
   _RTCS_msgpool_grow = 2;
   _RTCS_msgpool_max  = 20;
   _RTCS_socket_part_init = 4;
   _RTCS_socket_part_grow = 2;
   _RTCS_socket_part_max  = 20;

    error = RTCS_create();

    LWDNS_server_ipaddr = ENET_IPGATEWAY;

    ip_data.ip = ENET_IPADDR;
    ip_data.mask = ENET_IPMASK;
    ip_data.gateway = ENET_IPGATEWAY;
    
    ENET_get_mac_address (DEMOCFG_DEFAULT_DEVICE, ENET_IPADDR, enet_address);
    error = ipcfg_init_device (DEMOCFG_DEFAULT_DEVICE, enet_address);
#if DEMOCFG_USE_WIFI
    iwcfg_set_essid (DEMOCFG_DEFAULT_DEVICE,DEMOCFG_SSID);
    if ((strcmp(DEMOCFG_SECURITY,"wpa") == 0)||strcmp(DEMOCFG_SECURITY,"wpa2") == 0)
    {
        iwcfg_set_passphrase (DEMOCFG_DEFAULT_DEVICE,DEMOCFG_PASSPHRASE);

    }
    if (strcmp(DEMOCFG_SECURITY,"wep") == 0)
    {
      iwcfg_set_wep_key (DEMOCFG_DEFAULT_DEVICE,DEMOCFG_WEP_KEY,strlen(DEMOCFG_WEP_KEY),DEMOCFG_WEP_KEY_INDEX);
    }
    iwcfg_set_sec_type (DEMOCFG_DEFAULT_DEVICE,DEMOCFG_SECURITY);
    iwcfg_set_mode (DEMOCFG_DEFAULT_DEVICE,DEMOCFG_NW_MODE);
    iwcfg_commit(DEMOCFG_DEFAULT_DEVICE);
#endif  
    error = ipcfg_bind_staticip (DEMOCFG_DEFAULT_DEVICE, &ip_data);

#if DEMOCFG_ENABLE_FTP_SERVER
   {
      /* FTP server parameters are global variables. */
      ftpsrv_params.root_dir = FTPSRV_ROOTDIR;
      #if RTCSCFG_ENABLE_IP4
      ftpsrv_params.af |= AF_INET;
      #endif
      #if RTCSCFG_ENABLE_IP6
      ftpsrv_params.af |= AF_INET6;
      #endif
      ftpsrv_params.auth_table = (FTPSRV_AUTH_STRUCT*) ftpsrv_users;
      
      if (FTPSRV_init(&ftpsrv_params) != 0)
      {
         printf("FTP Server Started. Root directory is set to \"%s\", login: \"%s\", password: \"%s\".\n",
        		 ftpsrv_params.root_dir,
        		 ftpsrv_users[0].uid,
        		 ftpsrv_users[0].pass);
      }
   }
#endif

#if DEMOCFG_ENABLE_TELNET_SERVER
   TELNETSRV_PARAM_STRUCT telnet_params = {0};

   telnet_params.shell_commands = (void *) Telnetsrv_commands;
   telnet_params.shell = (TELNET_SHELL_FUNCTION) Shell;
   TELNETSRV_init(&telnet_params);
#endif

#if DEMOCFG_ENABLE_KLOG && MQX_KERNEL_LOGGING
   RTCSLOG_enable(RTCSLOG_TYPE_FNENTRY);
   RTCSLOG_enable(RTCSLOG_TYPE_PCB);
#endif

}

#else /* DEMOCFG_ENABLE_RTCS */

#if (DEMOCFG_ENABLE_FTP_SERVER+DEMOCFG_ENABLE_TELNET_SERVER) > 0
#warning RTCS network stack is disabled, the selected service will not be available.
#endif

#endif /* DEMOCFG_ENABLE_RTCS */

/* EOF */
