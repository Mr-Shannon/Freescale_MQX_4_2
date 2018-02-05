/**HEADER********************************************************************
*
* Copyright (c) 2011, 2013 - 2015 Freescale Semiconductor;
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
* $FileName: audio_microphone.c$
* $Version :
* $Date    :
*
* Comments:
*
*   This file is an example of device drivers for the Audio host class. This example
*   demonstrates the audio transfer capability of audio host class with audio devices.
*
*END************************************************************************/
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#include "usb_host_audio.h"
#include "usb_host_hub_sm.h"
#include "audio_microphone.h"
//#include "sd_card.h"
#include <hwtimer.h>
#include "sh_audio.h"
#include "bsp.h"
#include "fio.h"
#include "mfs.h"
#include "sh_mfs.h"
#include "sh_audio.h"
#include "shell.h"


#include <spi.h>
#include <part_mgr.h>


#if defined BSP_SDCARD_ESDHC_CHANNEL
#if ! BSPCFG_ENABLE_ESDHC
#error This application requires BSPCFG_ENABLE_ESDHC \
    defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

#elif defined BSP_SDCARD_SDHC_CHANNEL

#if ! BSPCFG_ENABLE_SDHC
#error This application requires BSPCFG_ENABLE_SDHC defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

#elif defined (BSP_TWRMCF51CN) || defined (BSP_TWRPXS20) || defined (BSP_TWR_K20D72M) || defined (BSP_TWR_K22F120M256R) || defined (BSP_TWR_K24F120M)

#if ! BSPCFG_ENABLE_SPI1
#error This application requires BSPCFG_ENABLE_SPI1 defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

#else
#if ! BSPCFG_ENABLE_SPI0
#error This application requires BSPCFG_ENABLE_SPI0 \
    defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

#endif

#if defined (BSP_SDCARD_SPI_CHANNEL)
#define SDCARD_COM_CHANNEL BSP_SDCARD_SPI_CHANNEL
#elif defined (BSP_SDCARD_ESDHC_CHANNEL)
#define SDCARD_COM_CHANNEL BSP_SDCARD_ESDHC_CHANNEL
#elif defined (BSP_SDCARD_SDHC_CHANNEL)
#define SDCARD_COM_CHANNEL BSP_SDCARD_SDHC_CHANNEL
#else
#error "SDCARD low level communication device not defined!"
#endif
/***************************************
**
** Macros
****************************************/
#define NUMBER_OF_BUFFER  0x5
#define USB_EVENT_CTRL 0x01
#define USB_EVENT_DATA 0x02
#define timer_out_event           0x01

/***************************************
**
** Global functions
****************************************/

/***************************************
**
** Local functions
****************************************/
static usb_status check_device_type (
                                        usb_audio_ctrl_desc_it_t*,
                                        usb_audio_ctrl_desc_ot_t*,
                                        char **,
                                        char
                                    *);
static void Audio_Task(uint32_t);
static void Sdcard_task(uint32_t temp);
static void Shell_task(uint32_t temp);
extern void timer_task(uint32_t param);
extern void timer_task_stun(uint32_t param);

usb_host_handle        host_handle;

/***************************************
**
** Global variables
****************************************/
extern const SDCARD_INIT_STRUCT _bsp_sdcard0_init;

/* microphone or speaker */
char                                    device_direction = USB_AUDIO_DEVICE_DIRECTION_UNDEFINE;
/* buffer for receiving an audio data packet, must be cache line aligned */
char                                    *wav_recv_buff;
/* ping-pong buffer for accumulating audio data packets */
char                                    wav_sdcard_buff0[REC_BLOCK_SIZE];
/* ping-pong buffer for accumulating audio data packets */
char                                    wav_sdcard_buff1[REC_BLOCK_SIZE];
char                                    *wav_sdcard_buff = wav_sdcard_buff0;
/* audio packet size */
uint32_t                                 packet_size;
/* audio control device */
audio_control_device_struct_t    audio_control = { 0 };
/* audio stream device */
audio_control_device_struct_t    audio_stream  = { 0 };
/* audio stream descriptor */
usb_audio_stream_desc_format_type_t*   frm_type_desc = NULL;
/* block record ready event */
extern os_event_handle block_rec;
/* bytes remain for record */
extern uint32_t                          remainder;
/* final packet flag*/
extern bool                         final_packet;
/* end point descriptor */
endpoint_descriptor_t*                 endp;
/* hwtimer handle */
HWTIMER audio_timer;
extern const HWTIMER_DEVIF_STRUCT BSP_HWTIMER1_DEV;
extern bool                                        audio_recording;

audio_command_t audio_com;
static int16_t                  cur_volume, min_volume, max_volume;// res_volume;
//static int16_t                  physic_volume;
uint8_t                         host_cur_volume = 5;
int16_t                         device_volume_step;
uint8_t *g_cur_mute;
uint8_t *g_cur_vol;
uint8_t *g_max_vol;
uint8_t *g_min_vol;
uint8_t *g_res_vol;
uint8_t *g_cur_samp;
os_event_handle USB_ctr_Event;

os_event_handle                   usb_audio_fu_request;
usb_audio_ctrl_desc_fu_t*         fu_desc = NULL;

uint8_t                 g_interface_control_number = 0;
uint8_t                 g_interface_stream_number = 0;
os_event_handle                         usb_timer_event;

usb_device_interface_struct_t*   g_interface_control_info[USBCFG_HOST_MAX_INTERFACE_PER_CONFIGURATION];
usb_device_interface_struct_t*   g_interface_stream_info[USBCFG_HOST_MAX_INTERFACE_PER_CONFIGURATION];


/* MQX template list */
TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
    {10,    Audio_Task,         2500L,    10L, "Audio Task", MQX_AUTO_START_TASK},
    {11,    Sdcard_task,        2000L,    11L, "Sdcard Task",MQX_AUTO_START_TASK},
    {9,     timer_task_stun,    1000L,    9L,  "Timer",      MQX_AUTO_START_TASK},
    {12,    Shell_task,         2000L,    12L, "Shell Task", MQX_AUTO_START_TASK},
    {0L,    0L,                 0L,       0L,  0L,           0L }
};

/* Shell list */
const SHELL_COMMAND_STRUCT Shell_commands[] = {
    { "cd",        Shell_cd },
    { "del",       Shell_del },
    { "dir",       Shell_dir },
    { "help",      Shell_help },
    { "read",      Shell_read },
    { "mkdir",     Shell_mkdir },
    { "ren",       Shell_rename },
    { "rmdir",     Shell_rmdir },
    { "record",    Shell_record },
    { "mute",      Shell_mute },
    { "?",         Shell_command_list },
    { NULL,        NULL }
};

/***************************************
**
** Local variables
****************************************/
/* device type string*/
static char                         *device_string;

/* Transfer Types */
static const char *TransferType[TRANSFER_TYPE_NUM] =
{
    "Control",
    "Isochronous",
    "Bulk",
    "Interrupt"
};
/* Sync Types */
static const char *SyncType[SYNC_TYPE_NUM] =
{
    "No synchronization",
    "Asynchronous",
    "Adaptive",
    "Synchronous"
};
/* Data Types */
static const char *DataType[DATA_TYPE_NUM] =
{
    "Data endpoint",
    "Feedback endpoint",
    "Implicit feedback",
    "Reserved"
};

/* Table of driver capabilities this application wants to use */
static  usb_host_driver_info_t DriverInfoTable[] =
{
   {
      {0x00,0x00},                  /* Vendor ID per USB-IF             */
      {0x00,0x00},                  /* Product ID per manufacturer      */
      USB_CLASS_AUDIO,              /* Class code                       */
      USB_SUBCLASS_AUD_CONTROL,     /* Sub-Class code                   */
      0xFF,                         /* Protocol                         */
      0,                            /* Reserved                         */
      usb_host_audio_control_event  /* Application call back function   */
   },
   {
      {0x00,0x00},                  /* Vendor ID per USB-IF             */
      {0x00,0x00},                  /* Product ID per manufacturer      */
      USB_CLASS_AUDIO,              /* Class code                       */
      USB_SUBCLASS_AUD_STREAMING,   /* Sub-Class code                   */
      0xFF,                         /* Protocol                         */
      0,                            /* Reserved                         */
      usb_host_audio_stream_event   /* Application call back function   */
   },
   /* USB 1.1 hub */ 
   {

      {0x00,0x00},                  /* Vendor ID per USB-IF             */
      {0x00,0x00},                  /* Product ID per manufacturer      */
      USB_CLASS_HUB,                /* Class code                       */
      USB_SUBCLASS_HUB_NONE,        /* Sub-Class code                   */
      USB_PROTOCOL_HUB_ALL,          /* Protocol                         */
      0,                            /* Reserved                         */
      usb_host_hub_device_event     /* Application call back function   */
   }, 
   {
      {0x00,0x00},                  /* All-zero entry terminates        */
      {0x00,0x00},                  /* driver info list.                */
      0,
      0,
      0,
      0,
      NULL
   }
};
/* Input Terminal types */
static char *it_type_string[NUMBER_OF_IT_TYPE] =
{
    "Input Undefined",
    "Microphone",
    "Desktop Microphone",
    "Personal Microphone",
    "Omni directional Microphone",
    "Microphone array",
    "Processing Microphone array",
};

/* Output Terminal types */
static char *ot_type_string[NUMBER_OF_OT_TYPE] =
{
    "Output Undefined",
    "Speaker",
    "Headphones",
    "Head Mounted Display Audio",
    "Desktop Speaker",
    "Room Speaker",
    "Communication Speaker",
    "Low Frequency Effects Speaker",
};
usb_interface_descriptor_handle audio_control_get_interface()
{
    return (usb_interface_descriptor_handle)(g_interface_control_info[0]);
}

usb_interface_descriptor_handle audio_stream_get_interface()
{
    return (usb_interface_descriptor_handle)(g_interface_stream_info[0]);
}

extern usb_status usb_class_audio_get_alternative_interface_descriptors_and_sync
(
        /* [IN] pointer to device instance */
    usb_device_instance_handle      dev_handle,

    usb_device_interface_struct_t* default_intf_handle,

    /* [IN] pointer to interface descriptor */
    usb_device_interface_struct_t* intf_handle,

    void*                           alternative_interface_descriptor
 );
/*FUNCTION*---------------------------------------------------------------
*
* Function Name : audio_timer_isr
* Comments  : Callback called by hwtimer every elapsed period
*
*END*----------------------------------------------------------------------*/
static void audio_timer_isr(void *p)
{
   OS_Event_set(usb_timer_event, timer_out_event);
}

void timer_task(uint32_t param)
{    
    static uint16_t index = 0;
    //Do the stuff only if both USB and the sync mechanism are ready
    if (OS_Event_check_bit(usb_timer_event, timer_out_event))
    {
        OS_Event_clear(usb_timer_event, timer_out_event);
        if ((USB_DEVICE_INUSE == audio_stream.dev_state) && (block_rec != NULL))
        {
            /* the attached device is microphone */
            if(USB_AUDIO_DEVICE_DIRECTION_OUT == device_direction)
            {
                /* Recv data */
                audio_com.callback_fn = usb_host_audio_tr_callback;
                audio_com.callback_param = 0;
                usb_class_audio_recv_data(&audio_com,(uint8_t *)&wav_recv_buff[packet_size*index],packet_size);
                index ++;
                if(index == NUMBER_OF_BUFFER)
                    index = 0;
            }
        }
    }
}
/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_khci_task_stun
*  Returned Value : none
*  Comments       :
*        KHCI task
*END*-----------------------------------------------------------------*/
void timer_task_stun(uint32_t param)
{
    usb_timer_event = OS_Event_create(0);
    while(1)
    {
        OS_Event_wait(usb_timer_event, timer_out_event, FALSE, 0);
        timer_task(param);
    }
}

#ifdef BSP_SDCARD_GPIO_CS
/*FUNCTION*---------------------------------------------------------------
*
* Function Name : set_CS
* Comments  : This function sets chip select signal to enable/disable memory
*
*END*----------------------------------------------------------------------*/

static void set_CS (uint32_t cs_mask, uint32_t logic_level, void *user_data)
{
    LWGPIO_STRUCT_PTR gpiofd = user_data;

    if (cs_mask & BSP_SDCARD_SPI_CS)
    {
        lwgpio_set_value(gpiofd, logic_level ? LWGPIO_VALUE_HIGH : LWGPIO_VALUE_LOW);
    }
}
#endif
/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : check_device_type
* Returned Value : None
* Comments       :
*    This function check whether the attached device is out-device or in-device.
*
*END*--------------------------------------------------------------------*/
static usb_status check_device_type
    (
    /* [IN] Input terminal descriptor */
    usb_audio_ctrl_desc_it_t*      it_desc,

    /* [IN] Output terminal descriptor */
    usb_audio_ctrl_desc_ot_t*      ot_desc,

    /* [OUT] Terminal type name */
    char *                  *device_type,

    /* [OUT] device direction */
    char                        *direction
    )
{
    uint8_t it_type_high, it_type_low, ot_type_low;

    it_type_high = it_desc->wterminaltype[0];
    it_type_low  = it_desc->wterminaltype[1];
    ot_type_low  = ot_desc->wterminaltype[1];

    /* Input terminal associates with audio streaming */
    if (USB_TERMINAL_TYPE == it_type_low)
    {
        *direction = USB_AUDIO_DEVICE_DIRECTION_IN;
    }
    /* Input terminal type */
    else if (INPUT_TERMINAL_TYPE == it_type_low)
    {
        /* get type device name */
        *device_type = it_type_string[it_type_high];
    }
    else
    {
        return USBERR_ERROR;
    }

    /* Output terminal associates with audio streaming */
    if (USB_TERMINAL_TYPE == ot_type_low)
    {
        if (USB_AUDIO_DEVICE_DIRECTION_IN == (*direction))
        {
            *direction = USB_AUDIO_DEVICE_DIRECTION_UNDEFINE;
            return USBERR_ERROR;
        }
        else
        {
            *direction = USB_AUDIO_DEVICE_DIRECTION_OUT;
        }
    }
    /* Output terminal type */
    else if (OUTPUT_TERMINAL_TYPE == ot_type_low)
    {
        /* get type device name */
        *device_type = ot_type_string[it_type_high];
    }
    else
    {
        return USBERR_ERROR;
    }
    return USB_OK;
}

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : USB_Audio_Get_Packet_Size
* Returned Value : None
* Comments       :
*     This function gets the frequency supported by the attached device.
*
*END*--------------------------------------------------------------------*/
static uint32_t USB_Audio_Get_Packet_Size
(
/* [IN] Point to format type descriptor */
usb_audio_stream_desc_format_type_t* format_type_desc
)
{
    uint32_t packet_size_tmp;
    /* calculate packet size to send to the device each mS.*/
    /* packet_size = (sample frequency (Hz) /1000) * (bit resolution/8) * number of channels */
    packet_size_tmp = ((((format_type_desc->tsamfreq[0][2]) << 16)|
    ((format_type_desc->tsamfreq[0][1])<< 8) |
    ((format_type_desc->tsamfreq[0][0]) << 0) )
    *(format_type_desc->bbitresolution / 8)
    *(format_type_desc->bnrchannels) / 1000);
    return (packet_size_tmp);
}

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : Audio_Task
* Returned Value : none
* Comments       :
*     Execution starts here
*
*END*--------------------------------------------------------------------*/
static void Audio_Task ( uint32_t param )
{ /* Body */
    usb_status           status = USB_OK;
    feature_control_struct_t control_feature;
    uint8_t bsamfreqtype_index;

    /* _usb_otg_init needs to be done with interrupts disabled */
    _int_disable();
      /*
    ** It means that we are going to act like host, so we initialize the
    ** host stack. This call will allow USB system to allocate memory for
    ** data structures, it uses later (e.g pipes etc.).
    */
    status = usb_host_init(CONTROLLER_ID,                            /*  */
            &host_handle);                            /* Returned pointer */
    if (status != USB_OK) 
    {
        USB_PRINTF("\nUSB Host Initialization failed. STATUS: %x", status);
        fflush(stdout);
    }
    /*
    ** Since we are going to act as the host driver, register the driver
    ** information for wanted class/subclass/protocols
    */
    status = usb_host_register_driver_info (
    host_handle,
    DriverInfoTable
    );
    if (status != USB_OK) {
        USB_PRINTF("\nDriver Registration failed. STATUS: %x", status);
        fflush(stdout);
    }

    usb_audio_fu_request = OS_Event_create(0);/* manually clear */
   _int_enable();

   if (NULL == (wav_recv_buff = OS_Mem_alloc_uncached_zero(MAX_ISO_PACKET_SIZE)))
   {
      USB_PRINTF("\nMemory allocation for ISO buffer failed.\n");
      _task_block();
   }

   /* Initialization of hwtimer */
   if (MQX_OK != hwtimer_init(&audio_timer, &BSP_HWTIMER1_DEV, BSP_HWTIMER1_ID, 5))
   {
      USB_PRINTF("\nHwtimer initialization failed.\n");
      _task_block();
   }
   hwtimer_set_freq(&audio_timer, BSP_HWTIMER1_SOURCE_CLK, AUDIO_MICROPHONE_FREQUENCY);
   hwtimer_callback_reg(&audio_timer,(HWTIMER_CALLBACK_FPTR)audio_timer_isr, NULL);
   if (NULL == (g_cur_mute = OS_Mem_alloc_uncached_zero(4)))
   {
     USB_PRINTF("\nMemory allocation for mute buffer failed.\n");
     _task_block();
   }
   if (NULL == (g_cur_vol = OS_Mem_alloc_uncached_zero(4)))
   {
     USB_PRINTF("\nMemory allocation for current volume buffer failed.\n");
     _task_block();
   }
   if (NULL == (g_max_vol = OS_Mem_alloc_uncached_zero(4)))
   {
     USB_PRINTF("\nMemory allocation for max volume buffer failed.\n");
     _task_block();
   }
   if (NULL == (g_min_vol = OS_Mem_alloc_uncached_zero(4)))
   {
     USB_PRINTF("\nMemory allocation for min volume buffer failed.\n");
     _task_block();
   }
   if (NULL == (g_res_vol = OS_Mem_alloc_uncached_zero(4)))
   {
     USB_PRINTF("\nMemory allocation for volume resolution failed.\n");
     _task_block();
   }
   if (NULL == (g_cur_samp = OS_Mem_alloc_uncached_zero(4)))
   {
     USB_PRINTF("\nMemory allocation for current sampling failed.\n");
     _task_block();
   }
   
   if (NULL  == (endp = OS_Mem_alloc_uncached_zero(sizeof(endpoint_descriptor_t))))
   {
     USB_PRINTF("\nMemory allocation for current sampling failed.\n");
     _task_block();
   }
    
   USB_PRINTF("USB Host Audio Demo\n"
           "Waiting for USB Audio Microphone Device to be attached...\n");
   USB_ctr_Event = OS_Event_create(0);/* manually clear */
   
   for(;;)
    {
        /* Get information of audio interface */
        if (USB_DEVICE_INTERFACED == audio_stream.dev_state)
        {
            audio_com.class_control_handle = (usb_class_handle)audio_control.class_handle;
            audio_com.callback_fn = usb_host_audio_request_ctrl_callback;
            audio_com.callback_param = (void *)&control_feature;
            /* Get min volume */
            usb_class_audio_feature_command(&audio_com,0,(void *)g_min_vol,USB_AUDIO_GET_MIN_VOLUME);
            /* Get max volume */
            usb_class_audio_feature_command(&audio_com,0,(void *)g_max_vol,USB_AUDIO_GET_MAX_VOLUME);
            control_feature.FU = USB_AUDIO_CTRL_FU_VOLUME;
            /* Get res volume */
            usb_class_audio_feature_command(&audio_com,0,(void *)g_res_vol,USB_AUDIO_GET_RES_VOLUME);
            OS_Time_delay(10);
            min_volume = (g_min_vol[1]<<8)|(g_min_vol[0]);
            max_volume = (g_max_vol[1]<<8)|(g_max_vol[0]);
            //res_volume = (g_res_vol[1]<<8)|(g_res_vol[0]);
            
            OS_Event_clear(usb_audio_fu_request, FU_VOLUME_MASK);
            control_feature.FU = 0;
            /* Synchronize host volume and device volume */
            device_volume_step = (int16_t)(((int16_t)(max_volume) - (int16_t)(min_volume))/(HOST_MAX_VOLUME - HOST_MIN_VOLUME));
            cur_volume = (int16_t)(min_volume + device_volume_step*host_cur_volume);
            /* Calculate physical volume(dB) */
          //  physic_volume = ((int16_t)(cur_volume)*39)/10000;
            g_cur_vol[0] = (uint8_t)((int16_t)(cur_volume)&0x00FF);
            g_cur_vol[1] = (uint8_t)((int16_t)(cur_volume)>>8);
            /* Unmute and set volume for audio device*/
            
            /* Audio device information */
            USB_PRINTF("Audio device information:\n");
            USB_PRINTF("   - Device type    : %s\n", device_string);
            for (bsamfreqtype_index =0; bsamfreqtype_index < frm_type_desc->bsamfreqtype; bsamfreqtype_index++)
            {
                if(0 == bsamfreqtype_index)
                {
                  g_cur_samp[0] = frm_type_desc->tsamfreq[0][ 0];
                  g_cur_samp[1] = frm_type_desc->tsamfreq[0][ 1];
                  g_cur_samp[2] = frm_type_desc->tsamfreq[0][ 2];
                }
                USB_PRINTF("   - Frequency device support      : %d Hz\n", (frm_type_desc->tsamfreq[bsamfreqtype_index][2] << 16) |
                (frm_type_desc->tsamfreq[bsamfreqtype_index][1] << 8)  |
                (frm_type_desc->tsamfreq[bsamfreqtype_index][0] << 0));
            }
            /* Set current sampling frequency */
            audio_com.class_control_handle = (usb_class_handle)audio_control.class_handle;
            audio_com.callback_fn = usb_host_audio_request_ctrl_callback;
            audio_com.callback_param = (void *)&control_feature;
            usb_class_audio_endpoint_command(&audio_com,(void *)g_cur_samp,USB_AUDIO_SET_CUR_SAMPLING_FREQ);
            /* print device information */
            USB_PRINTF("   - Bit resolution : %d bits\n", frm_type_desc->bbitresolution);
            USB_PRINTF("   - Number of channels : %d channels\n", frm_type_desc->bnrchannels);
            USB_PRINTF("   - Transfer type : %s\n", TransferType[(endp->bmAttributes)&EP_TYPE_MASK]);
            USB_PRINTF("   - Sync type : %s\n", SyncType[(endp->bmAttributes>>2)&EP_TYPE_MASK]);
            USB_PRINTF("   - Usage type : %s\n", DataType[(endp->bmAttributes>>4)&EP_TYPE_MASK]);

            /* Check device type */
            if (device_direction != USB_AUDIO_DEVICE_DIRECTION_OUT)
            {
                USB_PRINTF("The device is unsupported!\n");
            }
            USB_PRINTF("Type \"record a:\\filename.wav 5\" to record the file"\
                    " with 5 (s) length \n");
            audio_stream.dev_state = USB_DEVICE_INUSE;
        }
        OS_Time_delay(1);
    }
    /* Symbolic deinitialization of hwtimer when program finish */
    //hwtimer_deinit(&audio_timer);
} /* Endbody */

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Sdcard_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
static void Sdcard_task(uint32_t temp)
{
    (void)          temp; /* suppress 'unused variable' warning */
    bool            inserted = TRUE, readonly = FALSE, last = FALSE;
    _mqx_int        error_code;
    _mqx_uint       param;
    MQX_FILE_PTR    com_handle, sdcard_handle, filesystem_handle, partition_handle;
    char            filesystem_name[] = "a:";
    char            partman_name[] = "pm:";
    char            partition_name[] = "pm:1";
#if defined BSP_SDCARD_GPIO_DETECT
    LWGPIO_STRUCT   sd_detect;
#endif
#if defined BSP_SDCARD_GPIO_PROTECT
    LWGPIO_STRUCT   sd_protect;
#endif
#ifdef BSP_SDCARD_GPIO_CS

    LWGPIO_STRUCT   sd_cs;
    SPI_CS_CALLBACK_STRUCT callback;

#endif

    /* Open low level communication device */
    com_handle = fopen(SDCARD_COM_CHANNEL, (void *)(SPI_FLAG_FULL_DUPLEX));

    if (NULL == com_handle)
    {
        USB_PRINTF("Error opening communication handle %s, check your user_config.h.\n", SDCARD_COM_CHANNEL);
        _task_block();
    }

#ifdef BSP_SDCARD_GPIO_CS

    /* Open GPIO file for SPI CS signal emulation */
    error_code = lwgpio_init(&sd_cs, BSP_SDCARD_GPIO_CS, LWGPIO_DIR_OUTPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with associated pins failed.\n");
        _task_block();
    }
    lwgpio_set_functionality(&sd_cs,BSP_SDCARD_CS_MUX_GPIO);
    lwgpio_set_attribute(&sd_cs, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
    /* Set CS call back */
    callback.MASK = BSP_SDCARD_SPI_CS;
    callback.CALLBACK = set_CS;
    callback.USERDATA = &sd_cs;
    if (SPI_OK != ioctl (com_handle, IO_IOCTL_SPI_SET_CS_CALLBACK, &callback))
    {
        USB_PRINTF ("Setting CS call back failed.\n");
        _task_block();
    }

#endif

#if defined BSP_SDCARD_GPIO_DETECT
    /* Init GPIO pins for other SD card signals */
    error_code = lwgpio_init(&sd_detect, BSP_SDCARD_GPIO_DETECT, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with sdcard detect pin failed.\n");
        _task_block();
    }
    /*Set detect and protect pins as GPIO Function */
    lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_GPIO);
#if defined(BSP_SDCARD_DETECT_ACTIVE_LOW)
    lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_DOWN, LWGPIO_AVAL_ENABLE);
#else
    lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif
#endif

#if defined BSP_SDCARD_GPIO_PROTECT
    /* Init GPIO pins for other SD card signals */
    error_code = lwgpio_init(&sd_protect, BSP_SDCARD_GPIO_PROTECT, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE);
    if (!error_code)
    {
        USB_PRINTF("Initializing GPIO with sdcard protect pin failed.\n");
        _task_block();
    }
    /*Set detect and protect pins as GPIO Function */
    lwgpio_set_functionality(&sd_protect,BSP_SDCARD_PROTECT_MUX_GPIO);
    lwgpio_set_attribute(&sd_protect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif

    /* Install SD card device */
    error_code = _io_sdcard_install("sdcard:", (void *)&_bsp_sdcard0_init, com_handle);
    if ( error_code != MQX_OK )
    {
        USB_PRINTF("Error installing SD card device (0x%x)\n", error_code);
        _task_block();
    }

    for (;;)
    {
#if defined BSP_SDCARD_GPIO_DETECT
        #ifdef BSP_MPC8308RDB
        /* Set function as GPIO to detect sdcard */
        lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_GPIO);
        lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
        #endif
        #if defined(BSP_SDCARD_DETECT_ACTIVE_LOW)
            inserted = lwgpio_get_value(&sd_detect);
        #else
            inserted = !lwgpio_get_value(&sd_detect);
        #endif /* BSP_SDCARD_DETECT_ACTIVE_LOW */
#endif

#if defined BSP_SDCARD_GPIO_PROTECT
        /* Get value of protect pin */
        readonly = lwgpio_get_value(&sd_protect);
#endif
#ifdef BSP_MPC8308RDB
        /* Set function as SD_CD which indicate that card is present in Present State Register */
        lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_SD_CD);
        lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif
        if (last != inserted)
        {
            last = inserted;
            if (inserted)
            {
                OS_Time_delay (200);
                /* Open the device which MFS will be installed on */
                sdcard_handle = fopen("sdcard:", 0);
                if ( sdcard_handle == NULL )
                {
                    USB_PRINTF("Unable to open SD card device.\n");
                    continue;
                }

                /* Set read only flag as needed */
                param = 0;
                if (readonly)
                {
                    param = IO_O_RDONLY;
                }
                if (IO_OK != ioctl(sdcard_handle, IO_IOCTL_SET_FLAGS, (char *) &param))
                {
                    USB_PRINTF("Setting device read only failed.\n");
                    continue;
                }

                /* Install partition manager over SD card driver */
                error_code = _io_part_mgr_install(sdcard_handle, partman_name, 0);
                if (error_code != MFS_NO_ERROR)
                {
                    USB_PRINTF("Error installing partition manager: %s\n", MFS_Error_text((uint32_t)error_code));
                    continue;
                }

                /* Open partition */
                partition_handle = fopen(partition_name, NULL);
                if (partition_handle != NULL)
                {
                    USB_PRINTF("Installing MFS over partition...\n");
                    
                    /* Validate partition */
                    error_code = _io_ioctl(partition_handle, IO_IOCTL_VAL_PART, NULL);
                    if (error_code != MFS_NO_ERROR)
                    {
                        USB_PRINTF("Error validating partition: %s\n", MFS_Error_text((uint32_t)error_code));
                        USB_PRINTF("Not installing MFS.\n");
                        continue;
                    }

                    /* Install MFS over partition */
                    error_code = _io_mfs_install(partition_handle, filesystem_name, 0);
                    if (error_code != MFS_NO_ERROR)
                    {
                        USB_PRINTF("Error initializing MFS over partition: %s\n", MFS_Error_text((uint32_t)error_code));
                    }

                } else {

                    USB_PRINTF("Installing MFS over SD card driver...\n");

                    /* Install MFS over SD card driver */
                    error_code = _io_mfs_install(sdcard_handle, filesystem_name, (_file_size)0);
                    if (error_code != MFS_NO_ERROR)
                    {
                        USB_PRINTF("Error initializing MFS: %s\n", MFS_Error_text((uint32_t)error_code));
                    }
                }

                /* Open file system */
                if (error_code == MFS_NO_ERROR) {
                    filesystem_handle = fopen(filesystem_name, NULL);
                    error_code = ferror(filesystem_handle);
                    if (error_code == MFS_NOT_A_DOS_DISK)
                    {
                        USB_PRINTF("NOT A DOS DISK! You must format to continue.\n");
                    }
                    else if (error_code != MFS_NO_ERROR)
                    {
                        USB_PRINTF("Error opening filesystem: %s\n", MFS_Error_text((uint32_t)error_code));
                        continue;
                    }

                    USB_PRINTF ("SD card installed to %s\n", filesystem_name);
                    if (readonly)
                    {
                        USB_PRINTF ("SD card is locked (read only).\n");
                    }
                }
            }
            else
            {
                /* Close the filesystem */
                if ((filesystem_handle != NULL) && (MQX_OK != fclose(filesystem_handle)))
                {
                    USB_PRINTF("Error closing filesystem.\n");
                }
                filesystem_handle = NULL;

                /* Uninstall MFS  */
                error_code = _io_dev_uninstall(filesystem_name);
                if (error_code != MFS_NO_ERROR)
                {
                    USB_PRINTF("Error uninstalling filesystem.\n");
                }
                
                /* Close partition */
                if ((partition_handle != NULL) && (MQX_OK != fclose(partition_handle)))
                {
                    USB_PRINTF("Error closing partition.\n");
                }
                partition_handle = NULL;

                /* Uninstall partition manager  */
                error_code = _io_dev_uninstall(partman_name);
                if (error_code != MFS_NO_ERROR)
                {
                    USB_PRINTF("Error uninstalling partition manager.\n");
                }

                /* Close the SD card device */
                if ((sdcard_handle != NULL) && (MQX_OK != fclose(sdcard_handle)))
                {
                    USB_PRINTF("Unable to close SD card device.\n");
                }
                sdcard_handle = NULL;

                USB_PRINTF ("SD card uninstalled.\n");
            }
        }
        OS_Time_delay (200);
    }
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
static void Shell_task(uint32_t temp)
{
    /* Run the shell on the serial port */
    Shell(Shell_commands, NULL);
    _task_block();
}

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_host_audio_mute_ctrl_callback
* Returned Value : None
* Comments       :
*     Called when a mute request is sent successfully.
*
*END*--------------------------------------------------------------------*/
void usb_host_audio_mute_ctrl_callback
   (
      /* [IN] pointer to pipe */
      usb_pipe_handle  pipe_handle,

      /* [IN] user-defined parameter */
      void             *user_parm,

      /* [IN] buffer address */
      uint8_t         *buffer,

      /* [IN] length of data transferred */
      uint32_t           buflen,

      /* [IN] status, hopefully USB_OK or USB_DONE */
      uint32_t           status
   )
{
   /* Body */
   USB_PRINTF("Successfully\n");
   fflush(stdout);

} /* Endbody */
/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_host_audio_request_ctrl_callback
* Returned Value : None
* Comments       :
*     Called when a mute request is sent successfully.
*
*END*--------------------------------------------------------------------*/
void usb_host_audio_request_ctrl_callback
(
    /* [IN] pointer to pipe */
    usb_pipe_handle  pipe_handle,

    /* [IN] user-defined parameter */
    void             *user_parm,

    /* [IN] buffer address */
    uint8_t         *buffer,

    /* [IN] length of data transferred */
    uint32_t           buflen,

    /* [IN] status, hopefully USB_OK or USB_DONE */
    uint32_t           status
)
{ /* Body */
#if CODING_
    static feature_control_struct_t_PTR control_feature_ptr;
    control_feature_ptr = (feature_control_struct_t_PTR)user_parm;

    switch (control_feature_ptr->FU)
    {
    case USB_AUDIO_CTRL_FU_MUTE:
        {
          OS_Event_set(usb_audio_fu_request, FU_MUTE_MASK);    
            break;
        }
    case USB_AUDIO_CTRL_FU_VOLUME:
        {
           OS_Event_set(usb_audio_fu_request, FU_VOLUME_MASK);    
            break;
        }
    default:
        break;
    }
    fflush(stdout);
#endif
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_host_audio_tr_callback
* Returned Value : None
* Comments       :
*     Called when a ISO packet is sent/received successfully.
*
*END*--------------------------------------------------------------------*/
void usb_host_audio_tr_callback
(
    /* [IN] pointer to pipe */
    usb_pipe_handle pipe_handle,

    /* [IN] user-defined parameter */
    void   *user_parm,

    /* [IN] buffer address */
    uint8_t *buffer,

    /* [IN] length of data transferred */
    uint32_t buflen,

    /* [IN] status, hopefully USB_OK or USB_DONE */
    uint32_t status
)
{
   static uint16_t packnum = 0;
   static uint16_t index = 0;
   if(USB_AUDIO_DEVICE_DIRECTION_OUT == device_direction)
   {
       unsigned int k;
       /* copy each packet data to the received buffer*/
       for(k = 0; k < buflen; k++)
       {
          wav_sdcard_buff[packnum++] = wav_recv_buff[packet_size*index+k];
          if (packnum >= REC_BLOCK_SIZE) {
             /* signal that one is ready for writing */
             OS_Event_set(block_rec, wav_sdcard_buff == wav_sdcard_buff0 ? EV_BLOCK0_W_READY : EV_BLOCK1_W_READY);
             /* switch to another buffer */
             wav_sdcard_buff = (wav_sdcard_buff == wav_sdcard_buff0) ? wav_sdcard_buff1 : wav_sdcard_buff0;
             packnum = 0;
          }
          else if (final_packet && (packnum == remainder)) {
             /* signal that one is ready for writing */
             OS_Event_set(block_rec, wav_sdcard_buff == wav_sdcard_buff0 ? EV_BLOCK0_W_READY : EV_BLOCK1_W_READY);
             /* reset to the default config */
             wav_sdcard_buff = wav_sdcard_buff0;
             packnum = 0;
          }
       }
        index ++;
        if(index == NUMBER_OF_BUFFER)
            index = 0;
   }
}

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_host_audio_control_event
* Returned Value : None
* Comments       :
*     Called when control interface has been attached, detached, etc.
*END*--------------------------------------------------------------------*/
void usb_host_audio_control_event
   (
      /* [IN] pointer to device instance */
      usb_device_instance_handle      dev_handle,

      /* [IN] pointer to interface descriptor */
      usb_interface_descriptor_handle intf_handle,

      /* [IN] code number for event causing callback */
      uint32_t                          event_code
   )
{
    usb_device_interface_struct_t* pHostIntf = (usb_device_interface_struct_t*)intf_handle;
    interface_descriptor_t* intf_ptr = pHostIntf->lpinterfaceDesc;
    usb_status status;

    fflush(stdout);
    switch (event_code) {
    case USB_CONFIG_EVENT:
        if((audio_control.dev_state == USB_DEVICE_ATTACHED) )
        {
            audio_control.dev_handle  = dev_handle;
            audio_control.intf_handle = audio_control_get_interface();
            audio_control.dev_state   = USB_DEVICE_CONFIGURED;
        }
        else
        {
            USB_PRINTF("Audio device already attached\n");
            fflush(stdout);
        }

        USB_PRINTF("----- Audio control interface: USB_CONFIG_EVENT -----\n");

        break;
        /* Drop through into attach, same processing */
        case USB_ATTACH_EVENT:
        if(TRUE == audio_recording)
        {
            hwtimer_start(&audio_timer);
        }
           
        /* initialize new interface members and select this interface */
        g_interface_control_info[g_interface_control_number] = pHostIntf;
        g_interface_control_number++;
        audio_control.dev_state   = USB_DEVICE_ATTACHED;    
        USB_PRINTF("----- Audio control interface: attach event -----\n");
        fflush(stdout);
        USB_PRINTF("State = attached");
        USB_PRINTF("  Class = %d", intf_ptr->bInterfaceClass);
        USB_PRINTF("  SubClass = %d", intf_ptr->bInterfaceSubClass);
        USB_PRINTF("  Protocol = %d\n", intf_ptr->bInterfaceProtocol);
        break;

    case USB_INTF_OPENED_EVENT:
    {
        usb_audio_ctrl_desc_header_t*   header_desc = NULL;
        usb_audio_ctrl_desc_it_t*       it_desc  = NULL;
        usb_audio_ctrl_desc_ot_t*       ot_desc  = NULL;
        usb_audio_ctrl_desc_fu_t*       fu_desc  = NULL;

        /* finds all the descriptors in the configuration */
        if (USB_OK != usb_class_audio_control_get_descriptors(
                                                             dev_handle,
                                                             intf_handle,
                                                             &header_desc,
                                                             &it_desc,
                                                             &ot_desc,
                                                             &fu_desc)
                                                          )
        {
            break;
        };

        /* set all info got from descriptors to the class interface struct */
        usb_class_audio_control_set_descriptors(audio_control.class_handle,
                    header_desc, it_desc, ot_desc, fu_desc);

        if(USB_OK != check_device_type(
                                     it_desc,
                                     ot_desc,
                                     &device_string,
                                     &device_direction)
                                    )
        {
            USB_PRINTF("----- Audio control interface: Error @@@@@\n");
        }

        USB_PRINTF("----- Audio control interface: attach event -----\n");
        fflush(stdout);
        USB_PRINTF("State = attached");
        USB_PRINTF("  Class = %d", intf_ptr->bInterfaceClass);
        USB_PRINTF("  SubClass = %d", intf_ptr->bInterfaceSubClass);
        USB_PRINTF("  Protocol = %d\n", intf_ptr->bInterfaceProtocol);
        break;
    }

    case USB_DETACH_EVENT:
    {
        if(TRUE == audio_recording)
        {
            hwtimer_stop(&audio_timer);
        }

        USB_PRINTF("----- Audio control interface: detach event -----\n");
        fflush(stdout);
        USB_PRINTF("State = detached");
        USB_PRINTF("  Class = %d", intf_ptr->bInterfaceClass);
        USB_PRINTF("  SubClass = %d", intf_ptr->bInterfaceSubClass);
        USB_PRINTF("  Protocol = %d\n", intf_ptr->bInterfaceProtocol);
        fflush(stdout);
        status = usb_host_close_dev_interface(host_handle, dev_handle, intf_handle, audio_control.class_handle);
        if (status != USB_OK)
        {
            USB_PRINTF("error in _usb_hostdev_close_interface %x\n", status);
        }
        audio_control.dev_handle = NULL;
        audio_control.intf_handle = NULL;
        audio_control.dev_state = USB_DEVICE_DETACHED; 
        device_direction = USB_AUDIO_DEVICE_DIRECTION_UNDEFINE;
        g_interface_control_number = 0; 
        break;
    }
    default:
        USB_PRINTF("Audio Device: unknown control event\n");
        fflush(stdout);
        break;
    } /* EndSwitch */
   fflush(stdout);
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_host_audio_stream_event
* Returned Value : None
* Comments       :
*     Called when stream interface has been attached, detached, etc.
*END*--------------------------------------------------------------------*/
void usb_host_audio_stream_event
   (
      /* [IN] pointer to device instance */
      usb_device_instance_handle      dev_handle,

      /* [IN] pointer to interface descriptor */
      usb_interface_descriptor_handle intf_handle,

      /* [IN] code number for event causing callback */
      uint32_t                          event_code
   )
{ /* Body */
   
    usb_device_interface_struct_t* pHostIntf = (usb_device_interface_struct_t*)intf_handle;
    interface_descriptor_t* intf_ptr = pHostIntf->lpinterfaceDesc;
    
    usb_status status;

    
    //if(intf_ptr->bAlternateSetting == 0)
    //{
   //     return;
   // }

    switch (event_code) {
        case USB_CONFIG_EVENT:
        {
            usb_audio_stream_desc_spepific_as_if_t*     as_itf_desc = NULL;
            usb_audio_stream_desc_specific_iso_endp_t*  iso_endp_spec_desc = NULL;
            uint32_t param1 = 0;
            uint32_t param2 = 0;
            //void*    descriptor = NULL;
            void*    alternative_interface_descriptor = NULL;
            
            g_interface_stream_info[g_interface_stream_number] = (usb_device_interface_struct_t*) OS_Mem_alloc_uncached_zero(sizeof(usb_device_interface_struct_t));
            param1 = (uint32_t)((uint32_t)(g_interface_stream_info[0]->lpinterfaceDesc->bInterfaceNumber << 8) | (0x00000001));
            usb_host_get_dev_descriptor(intf_handle, USB_DESC_TYPE_IF, &param1, &param2, &alternative_interface_descriptor);
            usb_class_audio_get_alternative_interface_descriptors_and_sync(dev_handle,intf_handle, g_interface_stream_info[g_interface_stream_number],alternative_interface_descriptor);
        
            if((USB_DEVICE_IDLE == audio_stream.dev_state) ||\
            (USB_DEVICE_DETACHED == audio_stream.dev_state))
            {
                audio_stream.dev_handle  = dev_handle;
                audio_stream.intf_handle = intf_handle;
                audio_stream.dev_state      = USB_DEVICE_ATTACHED;
            }
            else
            {
                USB_PRINTF("Audio device already attached\n");
                fflush(stdout);
            }

            /* finds all the descriptors in the configuration */
            if (USB_OK != usb_class_audio_stream_get_descriptors(
                                                                  dev_handle,
                                                                  g_interface_stream_info[g_interface_stream_number],
                                                                  &as_itf_desc,
                                                                  &frm_type_desc,
                                                                  &iso_endp_spec_desc)
                                                              )
            {
                break;
            };
            endp->bmAttributes = iso_endp_spec_desc->bmattributes;

            /* initialize new interface members and select this interface */
            if (USB_OK != usb_host_open_dev_interface(host_handle, dev_handle,
            intf_handle, (void *)&audio_stream.class_handle))
            {
              break;
            }
            audio_com.class_stream_handle = (usb_class_handle)audio_stream.class_handle;    
            packet_size = USB_Audio_Get_Packet_Size(frm_type_desc);

            /* set all info got from descriptors to the class interface struct */
            usb_class_audio_stream_set_descriptors(
                                                         audio_stream.class_handle,
                                                as_itf_desc,
                                                frm_type_desc,
                                                iso_endp_spec_desc
                                               );
            USB_PRINTF("----- Audio stream interface: attach event -----\n");
            fflush(stdout);
            USB_PRINTF("State = attached");
            USB_PRINTF("  Class = %d", intf_ptr->bInterfaceClass);
            USB_PRINTF("  SubClass = %d", intf_ptr->bInterfaceSubClass);
            USB_PRINTF("  Protocol = %d\n", intf_ptr->bInterfaceProtocol);
            fflush(stdout);

            break;
        }
        case USB_ATTACH_EVENT:
            g_interface_stream_info[g_interface_stream_number] = pHostIntf;
            g_interface_stream_number++;
            USB_PRINTF("----- Audio stream interface: attach event -----\n");
            fflush(stdout);
            USB_PRINTF("State = attached");    
            USB_PRINTF("  Class = %d", intf_ptr->bInterfaceClass);
            USB_PRINTF("  SubClass = %d", intf_ptr->bInterfaceSubClass);
            USB_PRINTF("  Protocol = %d\n", intf_ptr->bInterfaceProtocol);
            USB_PRINTF("  Class = %d", intf_ptr->bAlternateSetting);
            fflush(stdout);
            break;        

        case USB_INTF_OPENED_EVENT:
            USB_PRINTF("----- stream USB_INTF_OPENED_EVENT  -----\n");
            OS_Event_set(USB_ctr_Event, USB_EVENT_CTRL);
            if (USB_OK != usb_host_open_dev_interface(host_handle, audio_control.dev_handle,
                    audio_control.intf_handle, (void *)&audio_control.class_handle))
            {
                 _task_block();
            }
            audio_stream.dev_state = USB_DEVICE_INTERFACED;
            break;

        case USB_DETACH_EVENT:
        {
        if(intf_handle != audio_stream_get_interface())
                return;
            status = usb_host_close_dev_interface(host_handle, dev_handle, intf_handle, audio_stream.class_handle);
            if (status != USB_OK)
            {
                USB_PRINTF("error in _usb_hostdev_close_interface %x\n", status);
            }
            audio_stream.dev_handle = NULL;
            audio_stream.intf_handle = NULL;
            audio_stream.dev_state = USB_DEVICE_DETACHED;
            OS_Mem_free(g_interface_stream_info[g_interface_stream_number]);
            g_interface_stream_number = 0;
            OS_Event_set(block_rec,  EV_BLOCK0_W_READY);
            USB_PRINTF("----- Audio stream interface: detach event-----\n");
            fflush(stdout);
            break;
        }
        default:
            USB_PRINTF("Audio device: unknown data event\n");
            fflush(stdout);
        break;
   }
}
