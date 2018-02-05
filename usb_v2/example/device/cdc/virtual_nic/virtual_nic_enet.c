/**HEADER********************************************************************
 *
 * Copyright (c) 2008, 2013 - 2014 Freescale Semiconductor;
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
 * $FileName: virtual_nic_enet.c$
 * $Version :
 * $Date    :
 *
 * Comments:
 *
 * @brief The file contains functions needed by the Network
 *        Interface for Virtual NIC Application
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "virtual_nic_enet.h"
#if (!CDC_RNDIS_SUPPORT)
#error This application requires CDC_RNDIS_SUPPORT defined one in usb_cdc_config.h. Please recompile usbd with this option.
#endif
#if !defined(BSP_DEFAULT_ENET_DEVICE)
#error This application requires BSP_DEFAULT_ENET_DEVICE defined one in bsp. Please recompile bsp with this option.
#endif
/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
#define ENET_TASK_PRIORITY                 (6)
#define ENET_TASK_STACKSIZE                (3500)
#define ENET_TASK_NAME                     "Enet Task"
#define ENET_TASK_ATTRIBUTES               (0)
#define ENET_TASK_CREATION_PARAMETER       (0)
#define ENET_TASK_DEFAULT_TIME_SLICE       (0)
#define ENET_TASK_ADDRESS                  Ethernet_Task
#define MSG_SIZE_IN_MAX_TYPE               (1 + (sizeof(uint32_t) - 1) / sizeof(uint32_t))

enet_address_t nic_mac_addr;
_ip_address nic_ip_addr = (_ip_address) ENET_IPADDR;

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
extern cdc_handle_t g_nic_handle;

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void Ethernet_Callback (PCB_PTR enet_pcb, void* handle);
static void VNIC_Send_PCB_Free (PCB_PTR nic_pcb);

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
_enet_handle g_enet_handle;
static ENET_HEADER g_enet_hdr;
static os_msgq_handle s_enet_service_que;

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : Ethernet_Callback
 *  Returned Value : ENET or error code
 *  Comments       :
 *        Services an IP packet.
 *
 *END*-----------------------------------------------------------------*/
void Ethernet_Callback
(
    PCB_PTR enet_pcb,
    /* [IN] the received packet */
    void* handle
    /* [IN] the IP interface structure */
    )
{
    /* Body */
    uint32_t event;
    event = (uint32_t) enet_pcb;

    if (0 != OS_MsgQ_send(s_enet_service_que, (void *) &event, 0))
    {
#if _DEBUG
        USB_PRINTF("OS_MsgQ_send fail\r\n");
#endif
    }
    return;
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : enet_task
 *  Returned Value : None
 *  Comments       :
 *        Enet task
 *END*-----------------------------------------------------------------*/
static void Ethernet_Task
(
    void* handle
)
{
    while (1)
    {
        static uint32_t msg = 0;

        while (!OS_MsgQ_recv(s_enet_service_que, (uint32_t *) &msg, OS_MSGQ_RECEIVE_BLOCK_ON_EMPTY, 10))
        {
            PCB_PTR enet_pcb;
            uint8_t status = USB_OK;

            enet_pcb = (PCB_PTR) msg;
            uint32_t length = enet_pcb->FRAG[0].LENGTH;
            uint8_t *nic_data_ptr = enet_pcb->FRAG[0].FRAGMENT;

            status = RNDIS_Get_Device_Status((*(cdc_handle_t*) handle));
            if (status == RNDIS_DATA_INITIALIZED)
            {
                VNIC_USB_Send(nic_data_ptr, length, enet_pcb);
            }
            else
            {
                PCB_free(enet_pcb);
            }
        }
    }
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : enet_task_create
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        Create device task
 *END*-----------------------------------------------------------------*/
static usb_status Ethernet_Task_Create
(
    void* handle
)
{
    uint32_t task_id;

    /* Initialize the Enet receive queue */
    s_enet_service_que = (os_msgq_handle) OS_MsgQ_create(16, MSG_SIZE_IN_MAX_TYPE);

    task_id = OS_Task_create(ENET_TASK_ADDRESS, (void*) handle, (uint32_t) ENET_TASK_PRIORITY, ENET_TASK_STACKSIZE, ENET_TASK_NAME, NULL);

    if (task_id == (uint32_t) OS_TASK_ERROR)
    {
        return USBERR_ERROR;
    }

    return USB_OK;
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/******************************************************************************
 *
 *    @name       VNIC_FEC_Init
 *
 *    @brief
 *
 *    @param      arg : handle to Identify the controller
 *
 *    @return     None
 *
 *****************************************************************************/
uint32_t VNIC_FEC_Init (cdc_config_struct_t * cdc_config_ptr)
{
    uint32_t error;
    bool flag = FALSE;

    Ethernet_Task_Create(&g_nic_handle);

    ENET_get_mac_address((uint32_t) ENET_DEVICE, nic_ip_addr, nic_mac_addr);

    error = ENET_initialize(ENET_DEVICE, nic_mac_addr, flag, &g_enet_handle);
    if (error != ENET_OK)
    {
#if _DEBUG
        USB_PRINTF("ENET_Initialization Failed\n");
#endif
        return ENETERR_INIT_FAILED;
    }

    error = ENET_open(g_enet_handle, ENETPROT_IP, Ethernet_Callback, (void*) &g_nic_handle);
    error |= ENET_open(g_enet_handle, ENETPROT_ARP, Ethernet_Callback, (void*) &g_nic_handle);
    if (error != ENET_OK)
    {
#if _DEBUG
        USB_PRINTF("ENET_open Failed.\n");
#endif
        return ENETERR_OPEN_PROT;
    }

    return error;
}

/******************************************************************************
 *
 *    @name       VNIC_FEC_Send
 *
 *    @brief
 *
 *    @param      arg :
 *    @param      enet_hdr_ptr:
 *
 *    @return     None
 *
 *****************************************************************************/
uint32_t VNIC_FEC_Send (void* arg, uint8_t * ethernet_frame_ptr, uint32_t payload_size)
{
    uint16_t protocol;
    uint8_t * nic_pcb = NULL;
    uint32_t error;
    PCB_FRAGMENT_PTR frag = NULL;
    UNUSED_ARGUMENT(arg)

    OS_Mem_copy(ethernet_frame_ptr,
    g_enet_hdr.DEST, MAC_ADDR_SIZE);
    OS_Mem_copy(ethernet_frame_ptr + MAC_ADDR_SIZE,
    g_enet_hdr.SOURCE, MAC_ADDR_SIZE);
    OS_Mem_copy(ethernet_frame_ptr + 2 * MAC_ADDR_SIZE,
    g_enet_hdr.TYPE, 2);

    protocol = *((uint16_t *) (((ENET_HEADER_PTR) ethernet_frame_ptr)->TYPE));
    protocol = htons(protocol);

    nic_pcb = _mem_alloc_system_zero(sizeof(PCB) + sizeof(PCB_FRAGMENT));
    if (nic_pcb == NULL)
    {
#if _DEBUG
        USB_PRINTF("Memalloc Failed in VNIC_FEC_Send\n");
#endif
        return ENETERR_ALLOC_PCB;
    }

    frag = ((PCB_PTR) nic_pcb)->FRAG;
    ((PCB_PTR) nic_pcb)->FREE = (void (_CODE_PTR_) (PCB_PTR)) VNIC_Send_PCB_Free;
    ((PCB_PTR) nic_pcb)->PRIVATE = NULL;
    frag[0].LENGTH = payload_size;

    frag[0].FRAGMENT = ethernet_frame_ptr;

    frag[1].LENGTH = 0;
    frag[1].FRAGMENT = NULL;

    error = ENET_send(g_enet_handle, (PCB_PTR) nic_pcb, protocol,
    ((ENET_HEADER_PTR) ethernet_frame_ptr)->DEST, 0);  //flag passed as Zero

    return error;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : VNIC_Send_PCB_Free
 *  Returned Value : None
 *  Comments       :
 *        Free nic_pcb
 *
 *END*-----------------------------------------------------------------*/
void VNIC_Send_PCB_Free (PCB_PTR nic_pcb)
{
    if (nic_pcb != NULL)
    {
        /* ethernet_frame_ptr is ((PCB_PTR)nic_pcb)->FRAG[0].FRAGMENT used in VNIC_FEC_Send
         rndis_pkt_msg_data_ptr is ethernet_frame_ptr - RNDIS_USB_OVERHEAD_SIZE
         used in USB_Notif_Callback*/
        OS_Mem_free(((PCB_PTR)nic_pcb)->FRAG[0].FRAGMENT - RNDIS_USB_OVERHEAD_SIZE);
        OS_Mem_free((void* )nic_pcb);
    }
}

/* EOF */
