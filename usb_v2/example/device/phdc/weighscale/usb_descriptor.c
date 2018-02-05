/**HEADER********************************************************************
 * 
 * Copyright (c) 2008, 2013- 2014 Freescale Semiconductor;
 * All Rights Reserved
 *
 * Copyright (c) 1989 - 2008 ARC International;
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
 * $FileName: usb_descriptor.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file contains USB descriptor functions
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "usb_descriptor.h"

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
/* structure containing details of all the endpoints used by this device */
usb_ep_struct_t g_ep[PHDC_DESC_ENDPOINT_COUNT] =
{
    {
        PHDC_BULK_OUT_EP,
        USB_BULK_PIPE,
        USB_RECV,
        PHDC_BULK_OUT_EP_SIZE,
    },
    {
        PHDC_BULK_IN_EP,
        USB_BULK_PIPE,
        USB_SEND,
        PHDC_BULK_IN_EP_SIZE,
    },
    {
        PHDC_INT_IN_EP,
        USB_INTERRUPT_PIPE,
        USB_SEND,
        PHDC_INT_IN_EP_SIZE,
    }
};

usb_endpoints_t g_usb_desc_ep =
{
    PHDC_DESC_ENDPOINT_COUNT,
    g_ep
};

static usb_if_struct_t g_usb_if[1];

usb_class_struct_t g_usb_dec_class =
{
    USB_CLASS_PHDC,
    {
        1,
        g_usb_if
    }
};

uint8_t g_qos[PHDC_DESC_ENDPOINT_COUNT] =
{
    PHDC_BULK_OUT_QOS,
    PHDC_BULK_IN_QOS,
    PHDC_INT_IN_QOS
};
uint8_t g_device_descriptor[DEVICE_DESCRIPTOR_SIZE] =
{
    /* Device Descriptor Size */
    DEVICE_DESCRIPTOR_SIZE,
    /* Device" Type of descriptor */
    USB_DEVICE_DESCRIPTOR,
    /*  BCD USB version  */
    USB_uint_16_low(BCD_USB_VERSION), USB_uint_16_high(BCD_USB_VERSION),
    /* Device Class is indicated in the interface descriptors */
    DEVICE_DESC_DEVICE_CLASS,
    /*  Device Subclass is indicated in the interface descriptors  */
    DEVICE_DESC_DEVICE_SUBCLASS,
    /*  Device Protocol  */
    DEVICE_DESC_DEVICE_PROTOCOL,
    /* Max Packet size */
    CONTROL_MAX_PACKET_SIZE,
    /* Vendor ID */
    0xa2, 0x15,
    /* Product ID */
    0x00, 0x04, /* for basic demo of phdc */
    /* BCD Device version */
    0x02, 0x00,
    /* Manufacturer string index */
    0x01,
    /* Product string index */
    0x02,
    /*  Serial number string index */
    0x00,
    /*  Number of configurations */
    DEVICE_DESC_NUM_CONFIG_SUPPOTED
};

uint8_t g_config_descriptor[CONFIG_DESC_SIZE] =
{
    /* Configuration Descriptor Size - always 9 bytes*/
    CONFIG_ONLY_DESC_SIZE,
    /* "Configuration" type of descriptor */
    USB_CONFIG_DESCRIPTOR,
    /*  Total length of the Configuration descriptor */
    USB_uint_16_low(CONFIG_DESC_SIZE), USB_uint_16_high(CONFIG_DESC_SIZE),
    /*  NumInterfaces */
    CONFIG_DESC_NUM_INTERFACES_SUPPOTED,
    /*  Configuration Value */
    1,
    /* Configuration Description String Index */
    0,
    /*  Attributes.support RemoteWakeup and self power */
    (USB_DESC_CFG_ATTRIBUTES_D7_POS) | USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_POS | USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_POS,
    /*  Current draw from bus */
    CONFIG_DESC_CURRENT_DRAWN,

    /* Interface Descriptor */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    0x00,
    0x00,
    /* no. of endpoints - one BULK OUT, one BULK IN,one INTERRUPT IN EP */
    PHDC_DESC_ENDPOINT_COUNT,
    /* class code for PHDC */
    PHDC_CLASS,
    /* subclass code -- does not assign a subclass */
    0x00,
    /* protocol code -- does not assign a protocol */
    0x00,
    0x00,

    /* PHDC class function descriptor */
    USB_PHDC_CLASSFUNCTION_DESC_SIZE,
    /* descriptor type */
    USB_PHDC_CLASSFUNCTION_DESCRIPTOR,
    /* data and messaging formats not defined by 
     vendor DATA FORMAT -PHDC_11073_20601*/
    0x02,
    0x00 | (META_DATA_MSG_PRE_IMPLEMENTED),

    /*PHDC function extension descriptor */
    USB_PHDC_FUNCTION_EXT_DESC_SIZE,
    PHDC_11073PHD_FUNCTION_DESCRIPTOR,
    0x00,
    0x01,
    0x34, 0x12,

    /*Endpoint descriptor -- BULK IN */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_SEND << 7) | PHDC_BULK_IN_EP,
    USB_BULK_PIPE,
    USB_uint_16_low(PHDC_BULK_IN_EP_SIZE),
    USB_uint_16_high(PHDC_BULK_IN_EP_SIZE),
    /*  polling interval */
    0x00,

    /* PHDC QoS descriptor for BULK IN */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    /* qos encoding version */
    0x01,
    /*  latency/reliability bin */
    PHDC_BULK_IN_QOS,

    /* PHDC Meta Data descriptor for BULK IN */
    USB_METADATA_BULK_IN_DESC_SIZE,
    PHDC_METADATA_DESCRIPTOR,
    /* opaque meta data */
    0xAB,
    0xCD,
    0xEF,
    0x01,
    0x02,
    /*Endpoint descriptor -- BULK OUT */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_RECV << 7) | PHDC_BULK_OUT_EP,
    USB_BULK_PIPE,
    USB_uint_16_low(PHDC_BULK_OUT_EP_SIZE),
    USB_uint_16_high(PHDC_BULK_OUT_EP_SIZE),
    /*  polling interval   */
    0x00,

    /* PHDC QoS descriptor for BULK OUT */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    /* qos encoding version */
    0x01,
    /*  latency/reliability bin */
    PHDC_BULK_OUT_QOS,

    /* PHDC Meta Data descriptor for BULK OUT */
    USB_METADATA_BULK_OUT_DESC_SIZE,
    PHDC_METADATA_DESCRIPTOR,
    0xCC, /* opaque meta data */
    0xDD,

    /*Endpoint descriptor -- INTERRUPT IN */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_SEND << 7) | PHDC_INT_IN_EP,
    USB_INTERRUPT_PIPE,
    USB_uint_16_low(PHDC_INT_IN_EP_SIZE),
    USB_uint_16_high(PHDC_INT_IN_EP_SIZE),
    /*  polling interval  */
    0x0A,

    /* PHDC QoS descriptor for INTERRUPT IN */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    /* qos encoding version */
    0x01,
    /*  latency/reliability bin    */
    PHDC_INT_IN_QOS,
};

#if HIGH_SPEED
uint8_t g_device_qualifier_descriptor[DEVICE_QUALIFIER_DESCRIPTOR_SIZE] =
{
    /* Device Qualifier Descriptor Size */
    DEVICE_QUALIFIER_DESCRIPTOR_SIZE,
    /* Type of Descriptor */
    USB_DEVQUAL_DESCRIPTOR,
    /*  BCD USB version  */
    USB_uint_16_low(BCD_USB_VERSION), USB_uint_16_high(BCD_USB_VERSION),
    /* bDeviceClass */
    DEVICE_DESC_DEVICE_CLASS,
    /* bDeviceSubClass */
    DEVICE_DESC_DEVICE_SUBCLASS,
    /* bDeviceProtocol */
    DEVICE_DESC_DEVICE_PROTOCOL,
    /* bMaxPacketSize0 */
    CONTROL_MAX_PACKET_SIZE,
    /* bNumConfigurations */
    DEVICE_OTHER_DESC_NUM_CONFIG_SUPPOTED,
    /* Reserved : must be zero */
    0x00
};

uint8_t g_other_speed_config_descriptor[OTHER_SPEED_CONFIG_DESCRIPTOR_SIZE] =
{
    /* Length of this descriptor */
    CONFIG_ONLY_DESC_SIZE,
    /* This is a Other speed config descr */
    USB_OTHER_SPEED_DESCRIPTOR,
    /*  Total length of the Configuration descriptor */
    USB_uint_16_low(CONFIG_DESC_SIZE), USB_uint_16_high(CONFIG_DESC_SIZE),
    CONFIG_DESC_NUM_INTERFACES_SUPPOTED,
    /*value used to select this configuration : Configuration Value */
    1,
    /*  Configuration Description String Index*/
    0,
    /*Attributes.support RemoteWakeup and self power*/
    (USB_DESC_CFG_ATTRIBUTES_D7_POS) | DEVICE_REMOTE_WAKEUP|DEVICE_POWER,
    /*  Current draw from bus */
    CONFIG_DESC_CURRENT_DRAWN,

    /* Interface Descriptor */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    0x00,
    0x00,
    /* no. of endpoints - one BULK OUT, one BULK IN,one INTERRUPT IN EP */
    PHDC_DESC_ENDPOINT_COUNT,
    /* class code for PHDC */
    0x0F,
    /* subclass code -- does not assign a subclass */
    0x00,
    /* protocol code -- does not assign a protocol */
    0x00,
    0x00,

    /* PHDC class function descriptor */
    USB_PHDC_CLASSFUNCTION_DESC_SIZE,
    /* descriptor type */
    USB_PHDC_CLASSFUNCTION_DESCRIPTOR,
    /* data and messaging formats not defined by 
     vendor DATA FORMAT -PHDC_11073_20601*/
    0x02,
    0x00|(META_DATA_MSG_PRE_IMPLEMENTED),

    /*PHDC function extension descriptor */
    USB_PHDC_FUNCTION_EXT_DESC_SIZE,
    PHDC_11073PHD_FUNCTION_DESCRIPTOR,
    0x00,
    0x01,
    0x34, 0x12,

    /*Endpoint descriptor -- BULK IN */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_SEND << 7) | PHDC_BULK_IN_EP,
    USB_BULK_PIPE,
    USB_uint_16_low(OTHER_SPEED_PHDC_BULK_IN_EP_SIZE),
    USB_uint_16_high(OTHER_SPEED_PHDC_BULK_IN_EP_SIZE),
    /*  polling interval */
    0x00,

    /* PHDC QoS descriptor for BULK IN */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    /* qos encoding version */
    0x01,
    /*  latency/reliability bin */
    PHDC_BULK_IN_QOS,

    /* PHDC Meta Data descriptor for BULK IN */
    USB_METADATA_BULK_IN_DESC_SIZE,
    PHDC_METADATA_DESCRIPTOR,
    /* opaque meta data */
    0xAB,
    0xCD,
    0xEF,
    0x01,
    0x02,

    /*Endpoint descriptor -- BULK OUT */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_RECV << 7) | PHDC_BULK_OUT_EP,
    USB_BULK_PIPE,
    USB_uint_16_low(OTHER_SPEED_PHDC_BULK_OUT_EP_SIZE),
    USB_uint_16_high(OTHER_SPEED_PHDC_BULK_OUT_EP_SIZE),
    /*  polling interval   */
    0x00,

    /* PHDC Meta Data descriptor for BULK OUT */
    USB_METADATA_BULK_OUT_DESC_SIZE,
    PHDC_METADATA_DESCRIPTOR,
    /* opaque meta data */
    0xCC,
    0xDD,

    /*Endpoint descriptor -- INTERRUPT IN */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_SEND << 7) | PHDC_INT_IN_EP,
    USB_INTERRUPT_PIPE,
    USB_uint_16_low(PHDC_INT_IN_EP_SIZE),
    USB_uint_16_high(PHDC_INT_IN_EP_SIZE),
    /*  polling interval  */
    0xF0,

    /* PHDC QoS descriptor for INTERRUPT IN */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    /* qos encoding version */
    0x01,
    /*  latency/reliability bin    */
    PHDC_INT_IN_QOS,
};
#endif

uint8_t USB_STR_0[USB_STR_0_SIZE + USB_STR_DESC_SIZE] =
{
    sizeof(USB_STR_0),
    USB_STRING_DESCRIPTOR,
    0x09,
    0x04
};

uint8_t USB_STR_1[USB_STR_1_SIZE + USB_STR_DESC_SIZE] =
{
    sizeof(USB_STR_1),
    USB_STRING_DESCRIPTOR,
    'F', 0,
    'R', 0,
    'E', 0,
    'E', 0,
    'S', 0,
    'C', 0,
    'A', 0,
    'L', 0,
    'E', 0,
    ' ', 0,
    'S', 0,
    'E', 0,
    'M', 0,
    'I', 0,
    'C', 0,
    'O', 0,
    'N', 0,
    'D', 0,
    'U', 0,
    'C', 0,
    'T', 0,
    'O', 0,
    'R', 0,
    ' ', 0,
    'I', 0,
    'N', 0,
    'C', 0,
    '.', 0
};

uint8_t USB_STR_2[USB_STR_2_SIZE + USB_STR_DESC_SIZE] =
{
    sizeof(USB_STR_2),
    USB_STRING_DESCRIPTOR,
    ' ', 0,
    'U', 0,
    'S', 0,
    'B', 0,
    ' ', 0,
    'P', 0,
    'H', 0,
    'D', 0,
    'C', 0,
    ' ', 0,
    'D', 0,
    'E', 0,
    'M', 0,
    'O', 0,
    ' ', 0
};

uint8_t USB_STR_n[USB_STR_n_SIZE + USB_STR_DESC_SIZE] =
{
    sizeof(USB_STR_n),
    USB_STRING_DESCRIPTOR,
    'B', 0,
    'A', 0,
    'D', 0,
    ' ', 0,
    'S', 0,
    'T', 0,
    'R', 0,
    'I', 0,
    'N', 0,
    'G', 0,
    ' ', 0,
    'I', 0,
    'N', 0,
    'D', 0,
    'E', 0,
    'X', 0
};

uint32_t g_std_desc_size[USB_MAX_STD_DESCRIPTORS + 1] =
{
    0,
    DEVICE_DESCRIPTOR_SIZE,
    CONFIG_DESC_SIZE,
    0, /* string */
    0, /* Interface */
    0, /* Endpoint */
#if HIGH_SPEED
    DEVICE_QUALIFIER_DESCRIPTOR_SIZE,
    OTHER_SPEED_CONFIG_DESCRIPTOR_SIZE,
#else
    0, /* Device Qualifier */
    0, /* other speed config */
#endif
};

uint8_t *g_std_descriptors[USB_MAX_STD_DESCRIPTORS + 1] =
{
    NULL,
    g_device_descriptor,
    g_config_descriptor,
    NULL, /* string */
    NULL, /* Interface */
    NULL, /* Endpoint */
#if HIGH_SPEED
    g_device_qualifier_descriptor,
    g_other_speed_config_descriptor,
#else
    NULL, /* Device Qualifier */
    NULL, /* other speed config*/
#endif
};

uint8_t g_string_desc_size[USB_MAX_STRING_DESCRIPTORS + 1] =
{
    sizeof(USB_STR_0),
    sizeof(USB_STR_1),
    sizeof(USB_STR_2),
    sizeof(USB_STR_n)
};

uint8_t *g_string_descriptors[USB_MAX_STRING_DESCRIPTORS + 1] =
{
    USB_STR_0,
    USB_STR_1,
    USB_STR_2,
    USB_STR_n
};
usb_language_t usb_lang[USB_MAX_SUPPORTED_LANGUAGES] =
{
    {
        (uint16_t) 0x0409,
        g_string_descriptors,
        g_string_desc_size
    }
};
usb_all_languages_t g_languages =
{
    USB_STR_0, sizeof(USB_STR_0),
    USB_MAX_SUPPORTED_LANGUAGES,
    usb_lang
};

uint8_t g_valid_config_values[USB_MAX_CONFIG_SUPPORTED + 1] = { 0, 1 };
/****************************************************************************
 * Global Variables
 ****************************************************************************/
static uint8_t g_alternate_interface[USB_MAX_SUPPORTED_INTERFACES];

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes 
 *****************************************************************************/

/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Descriptor
 *
 * @brief The function returns the corresponding descriptor
 *
 * @param handle:        handle     
 * @param type:          type of descriptor requested     
 * @param sub_type:      string index for string descriptor     
 * @param index:         string descriptor language Id     
 * @param descriptor:    output descriptor pointer
 * @param size:          size of descriptor returned
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Desc_Get_Descriptor
(
    phdc_handle_t handle,
    uint8_t type,
    uint8_t str_num,
    uint16_t index,
    uint8_t **descriptor,
    uint32_t *size
)
{
    UNUSED_ARGUMENT (handle)

    /* string descriptors are handled separately */
    if (type == USB_STRING_DESCRIPTOR)
    {
        if (index == 0)
        {
            /* return the string and size of all languages */
            *descriptor = (uint8_t *) g_languages.languages_supported_string;
            *size = g_languages.languages_supported_size;
        }
        else
        {
            uint8_t lang_id = 0;
            uint8_t lang_index = USB_MAX_SUPPORTED_LANGUAGES;

            for (; lang_id < USB_MAX_SUPPORTED_LANGUAGES; lang_id++)
            {
                /* check whether we have a string for this language */
                if (index == g_languages.usb_language[lang_id].language_id)
                { /* check for max descriptors */
                    if (str_num < USB_MAX_STRING_DESCRIPTORS)
                    { /* setup index for the string to be returned */
                        lang_index = str_num;
                    }
                    break;
                }
            }
            /* set return val for descriptor and size */
            *descriptor = (uint8_t *)
            g_languages.usb_language[lang_id].lang_desc[lang_index];
            *size =
            g_languages.usb_language[lang_id].lang_desc_size[lang_index];
        }
    }
    else if (type < USB_MAX_STD_DESCRIPTORS + 1)
    {
        /* set return val for descriptor and size*/
        *descriptor = (uint8_t *) g_std_descriptors[type];

        /* if there is no descriptor then return error */
        if (*descriptor == NULL)
        {
            return USBERR_INVALID_REQ_TYPE;
        }
        *size = g_std_desc_size[type];
    }
    else /* invalid descriptor */
    {
        return USBERR_INVALID_REQ_TYPE;
    }

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Interface
 *
 * @brief The function returns the alternate interface
 *
 * @param handle:         handle     
 * @param interface:      interface number     
 * @param alt_interface:  output alternate interface     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Desc_Get_Interface
(
    phdc_handle_t handle,
    uint8_t interface,
    uint8_t * alt_interface
)
{
    UNUSED_ARGUMENT (handle)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get alternate interface*/
        *alt_interface = g_alternate_interface[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Interface
 *
 * @brief The function sets the alternate interface
 *
 * @param handle:         handle     
 * @param interface:      interface number     
 * @param alt_interface:  input alternate interface     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Desc_Set_Interface
(
    phdc_handle_t handle,
    uint8_t interface,
    uint8_t alt_interface)
{
    UNUSED_ARGUMENT (handle)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set alternate interface*/
        g_alternate_interface[interface] = alt_interface;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Set_Configation
 *
 * @brief The function checks whether the configuration parameter 
 *        input is valid or not
 *
 * @param handle          handle     
 * @param config_val      configuration value     
 *
 * @return TRUE           When Valid
 *         FALSE          When Error
 *****************************************************************************/
uint8_t USB_Set_Configation
(
    phdc_handle_t handle,
    uint8_t config
)
{
    UNUSED_ARGUMENT (handle)
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Remote_Wakeup
 *
 * @brief The function checks whether the remote wakeup is supported or not
 *
 * @param handle            handle     
 *
 * @return REMOTE_WAKEUP_SUPPORT (TRUE) - if remote wakeup supported
 *****************************************************************************/
uint8_t USB_Desc_Get_Entity
(
    phdc_handle_t handle,
    entity_type type,
    uint32_t * object
)
{
    switch(type)
    {
    case USB_CLASS_INFO:
        g_usb_if[0].index = 1;
        g_usb_if[0].endpoints = g_usb_desc_ep;
        *object = (unsigned long) &g_usb_dec_class;
        break;
    case USB_PHDC_QOS_INFO:
        *object = (unsigned long) g_qos;
    default:
        break;
    }/* End Switch */
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Speed
 *
 * @brief The function is used to set device speed
 *
 * @param handle:         handle     
 * @param speed:          speed    
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Desc_Set_Speed
(
    uint32_t handle,
    uint16_t speed
)
{
    descriptor_union_t ptr1, ptr2;
    uint16_t bulk_in = 0;
    uint16_t bulk_out = 0;
    uint16_t interrupt_size = 0;
    uint8_t interrupt_interval = 0;

    UNUSED_ARGUMENT(handle);

    if (USB_SPEED_HIGH == speed)
    {
        bulk_in = HS_PHDC_BULK_IN_EP_SIZE;
        bulk_out = HS_PHDC_BULK_OUT_EP_SIZE;
        interrupt_size = HS_PHDC_INT_IN_EP_SIZE;
        interrupt_interval = HS_PHDC_INT_IN_EP_INTERVAL;
    }
    else
    {
        bulk_in = FS_PHDC_BULK_IN_EP_SIZE;
        bulk_out = FS_PHDC_BULK_OUT_EP_SIZE;
        interrupt_size = FS_PHDC_INT_IN_EP_SIZE;
        interrupt_interval = FS_PHDC_INT_IN_EP_INTERVAL;
    }

    ptr1.pntr = g_config_descriptor;
    ptr2.pntr = g_config_descriptor + CONFIG_DESC_SIZE;

    while (ptr1.word < ptr2.word)
    {
        if (ptr1.common->bDescriptorType == USB_DESC_TYPE_EP)
        {
            if (PHDC_INT_IN_EP == (ptr1.ndpt->bEndpointAddress & 0x7F))
            {
                ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(interrupt_size);
                ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(interrupt_size);
                ptr1.ndpt->iInterval = interrupt_interval;
            }
            else
            {
                if (ptr1.ndpt->bEndpointAddress & 0x80)
                {
                    ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(bulk_in);
                    ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(bulk_in);
                }
                else
                {
                    ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(bulk_out);
                    ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(bulk_out);
                }
            }
        }
        ptr1.word += ptr1.common->bLength;
    }

    for (int i = 0; i < PHDC_DESC_ENDPOINT_COUNT; i++)
    {
        if (PHDC_INT_IN_EP == g_ep[i].ep_num)
        {
            g_ep[i].size = interrupt_size;
        }
        else
        {
            if (USB_SEND == g_ep[i].direction)
            {
                g_ep[i].size = bulk_in;
            }
            else
            {
                g_ep[i].size = bulk_out;
            }
        }
    }
    return USB_OK;
}

usb_desc_request_notify_struct_t g_desc_callback =
{
    USB_Desc_Get_Descriptor,
    USB_Desc_Get_Interface,
    USB_Desc_Set_Interface,
    USB_Set_Configation,
    USB_Desc_Get_Entity
};
/* EOF */
