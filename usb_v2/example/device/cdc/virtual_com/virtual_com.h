/**HEADER********************************************************************
* 
* Copyright (c) 2008, 2015 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
* All Rights Reserved
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: virtual_com.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains Macro's and functions needed by the virtual com 
*        application
*
*****************************************************************************/

#ifndef _VIRTUAL_COM_H
#define _VIRTUAL_COM_H  1

#include "usb_descriptor.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
        
#if HIGH_SPEED
#define CONTROLLER_ID         USB_CONTROLLER_EHCI_0
#define DATA_BUFF_SIZE        (HS_DIC_BULK_OUT_ENDP_PACKET_SIZE)
#else
#define CONTROLLER_ID         USB_CONTROLLER_KHCI_0
#define DATA_BUFF_SIZE        (FS_DIC_BULK_OUT_ENDP_PACKET_SIZE)
#endif

/* Implementation Specific Macros */
#define LINE_CODING_SIZE              (0x07)
#define COMM_FEATURE_DATA_SIZE        (0x02)

#define LINE_CODE_DTERATE_IFACE      (115200) /*e.g 9600 is 0x00002580 */
#define LINE_CODE_CHARFORMAT_IFACE   (0x00)   /* 1 stop bit */
#define LINE_CODE_PARITYTYPE_IFACE   (0x00)  /* No Parity */
#define LINE_CODE_DATABITS_IFACE     (0x08)  /* Data Bits Format */

#define STATUS_ABSTRACT_STATE_IFACE  (0x0000) /* Disable Multiplexing ENDP in
                                                  this interface will continue
                                                  to accept/offer data*/
#define COUNTRY_SETTING_IFACE        (0x0000) /* Country Code in the format as 
                                                  defined in [ISO3166]- 
                                                  - PLEASE CHECK THESE VALUES*/                                                                                                   
/*****************************************************************************
 * Global variables
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void TestApp_Init(void);
extern void Virtual_Com_App(void);

#endif 


/* EOF */
