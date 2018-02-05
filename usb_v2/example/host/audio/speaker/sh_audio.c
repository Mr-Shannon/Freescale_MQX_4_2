/**HEADER********************************************************************
*
* Copyright (c) 2010, 2013 - 2014 Freescale Semiconductor;
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
* $FileName: sh_audio.c$
* $Version : 3.8.3.0$
* $Date    : Aug-9-2012$
*
* Comments:
*
*   This file contains the MQX shell commands for audio devices.
*
*END************************************************************************/
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#include "lwevent.h"
#include "bsp.h"
#else
#include "derivative.h"
#include "hidef.h"
#include "mem_util.h"
#endif

#include "usb_host_hub_sm.h"
#include "usb_host_audio.h"


#include "sh_audio.h"
#include "sd_card.h"
#include "wav.h"
#include "shell.h"
#include <string.h>
#include <hwtimer.h>
#include "audio_speaker.h"


/******************************************************************************
* Global variables
*****************************************************************************/
FILE_PTR file_ptr;
extern volatile audio_stream_device_struct_t audio_stream;
extern char  device_direction;  /* audio speaker or audio microphone */
extern uint32_t                                 packet_size;
extern usb_audio_stream_desc_format_type_t*   frm_type_desc;
extern uint8_t                                  audio_state;
extern uint8_t                                  sd_card_state;
extern uint8_t                                  file_open_count;
extern HWTIMER                                 audio_timer;
/******************************************************************************
* Local variables
*****************************************************************************/
extern audio_command_t audio_com;
extern uint8_t wav_buff[MAX_ISO_PACKET_SIZE];
/******************************************************************************
*   @name        Shell_play
*
*   @brief       Servers the play command
*
*   @param       None
*
*   @return      None
*
******************************************************************************
* This function is used to play an audio wav file
*****************************************************************************/
int32_t Shell_play(int32_t argc, char *argv[])
{
    bool print_usage, shorthelp = FALSE;
    uint8_t bsamfreqtype_index;
    uint32_t freq;
    print_usage = Shell_check_help_request (argc, argv, &shorthelp);

    if (!print_usage)
    {
        wave_file_header_t header;
        if (argc > 1)
        {
            /* stop the current file playing */
            if(AUDIO_PLAYING == audio_state)
            {
                audio_state = AUDIO_IDLE;
                hwtimer_stop(&audio_timer);
            }
            /* check the device is connected */
                device_direction = USB_AUDIO_DEVICE_DIRECTION_IN;
            if ((USB_DEVICE_INUSE != audio_stream.dev_state)||(device_direction != USB_AUDIO_DEVICE_DIRECTION_IN))
            {
                USB_PRINTF("  Error: Audio Speaker is not connected device_direction:%d state:%d\n",device_direction,audio_stream.dev_state);
                return (SHELL_EXIT_ERROR);
            }
            if (FillWaveHeader(argv[1], &header) != 0)
            {
                USB_PRINTF("  Error: Unable to open file: %s\n", argv[1]);
                return (SHELL_EXIT_ERROR);
            }
            if (strcmp(header.chunk_descriptor.format, "WAVE"))
            {
                USB_PRINTF("  Error: File is not WAVE file.\n");
                return (SHELL_EXIT_ERROR);
            }
            if (strcmp(header.fmt_subchunk.subchunk1id, "fmt "))
            {
                USB_PRINTF("  Error: File does not contain format subchunk.\n");
            }
            if (BYTESWAP16(header.fmt_subchunk.audioformat) != 1)
            {
                USB_PRINTF("  Error: File is compressed (not PCM).\n");
                return (SHELL_EXIT_ERROR);
            }
            if (strcmp(header.data_subchunk.subchunk2id, "data"))
            {
                USB_PRINTF("  Error: File does not contain data subchunk.\n");
          //      return (SHELL_EXIT_ERROR);
            }
            file_ptr = fopen(argv[1], "r");
            if (file_ptr == NULL)
            {
                USB_PRINTF("  Unable to open file: %s\n", argv[1]);
                return (SHELL_EXIT_ERROR);
            }
            file_open_count ++;
            USB_PRINTF("Audio file properties:\n");
            USB_PRINTF("   - Sample rate      : %d Hz\n", BYTESWAP32(header.fmt_subchunk.samplerate));
            USB_PRINTF("   - Sample size      : %d bits\n", BYTESWAP16(header.fmt_subchunk.bitspersample));
            USB_PRINTF("   - Number of channels : %d channels\n", BYTESWAP16(header.fmt_subchunk.numchannels));
            /* Compare the sample rate */
            for (bsamfreqtype_index =0; bsamfreqtype_index < frm_type_desc->bsamfreqtype; bsamfreqtype_index++)
            {
               freq = ((frm_type_desc->tsamfreq[bsamfreqtype_index][2] << 16) |
                            (frm_type_desc->tsamfreq[bsamfreqtype_index][1] << 8)  |
                            (frm_type_desc->tsamfreq[bsamfreqtype_index][0] << 0));
               if ( freq == BYTESWAP32(header.fmt_subchunk.samplerate))
                {
                    packet_size = USB_Audio_Get_Packet_Size(frm_type_desc,bsamfreqtype_index);
                    usb_class_audio_endpoint_command(&audio_com, &freq, USB_AUDIO_SET_CUR_SAMPLING_FREQ);
                    break;
                }
            }
            if (bsamfreqtype_index == frm_type_desc->bsamfreqtype)
            {
                USB_PRINTF("  The audio device doesn't support that audio sample rate \n");
                return (SHELL_EXIT_ERROR);
            }
            /* Compare the bits sample number */
            if (frm_type_desc->bbitresolution != BYTESWAP16(header.fmt_subchunk.bitspersample))
            {
                USB_PRINTF("  The audio device doesn't support that audio bit sample number \n");
                return (SHELL_EXIT_ERROR);
            }
            /* Compare the channel number */
            if (frm_type_desc->bnrchannels != BYTESWAP16(header.fmt_subchunk.numchannels))
            {
                USB_PRINTF("  The audio device doesn't support that audio channel number \n");
                return (SHELL_EXIT_ERROR);
            }
            fseek(file_ptr, WAVE_HEADER_SIZE, IO_SEEK_SET);
            audio_state = AUDIO_PLAYING;
            USB_PRINTF("  Playing...\n");
            hwtimer_start(&audio_timer);
        }
        else
        {
            if (AUDIO_PLAYING == audio_state)
            {
                USB_PRINTF("  The file is playing...\n");
            }
            else if (AUDIO_PAUSE == audio_state)
            {
                audio_state = AUDIO_PLAYING;
                hwtimer_start(&audio_timer);
                USB_PRINTF("  Playing...\n");
            }
            else if (AUDIO_IDLE == audio_state)
            {
                USB_PRINTF("  Not enough parameters.\n");
            }
        }
    }
    else
    {
        if (shorthelp)
        {
            USB_PRINTF("%s <filename>\n", argv[0]);
        }
        else
        {
            USB_PRINTF("Usage: %s <filename>\n", argv[0]);
            USB_PRINTF("   filename      = wav file to play\n");
        }
    }
    return(SHELL_EXIT_SUCCESS);
}
/******************************************************************************
*   @name        Shell_pause
*
*   @brief       Servers the pause command
*
*   @param       None
*
*   @return      None
*
******************************************************************************
* This function is used to pause the current playing file
*****************************************************************************/
int32_t Shell_pause_audio(int32_t argc, char *argv[])
{
    bool print_usage, shorthelp = FALSE;
    print_usage = Shell_check_help_request (argc, argv, &shorthelp);

    if (!print_usage)
    {
        if (argc > 1)
        {
            USB_PRINTF("  Error: This command doesn't need parameters\n");
            return (SHELL_EXIT_ERROR);
        }
        else
        {
            if(AUDIO_PLAYING == audio_state)
            {
                audio_state = AUDIO_PAUSE;
                USB_PRINTF("  Paused...\n");
                hwtimer_stop(&audio_timer);
            }
            else if (AUDIO_IDLE == audio_state)
            USB_PRINTF("  No file is playing!\n");
        }
    }

    if (print_usage)
    {
        if (shorthelp)
        {
            USB_PRINTF("%s\n", argv[0]);
        }
        else
        {
            USB_PRINTF("Usage: %s\n", argv[0]);
        }
    }
    return(SHELL_EXIT_SUCCESS);
}

/******************************************************************************
*   @name        Shell_mute
*
*   @brief       Servers the mute command
*
*   @param       None
*
*   @return      None
*
******************************************************************************
* This function is used to mute the audio device
*****************************************************************************/
int32_t Shell_mute(int32_t argc, char *argv[])
{
    bool         print_usage, shorthelp = FALSE;
    print_usage = Shell_check_help_request (argc, argv, &shorthelp);

    if (!print_usage)
    {
        if (argc > 1)
        {
            USB_PRINTF("  Error: This command doesn't need parameters\n");
            return (SHELL_EXIT_ERROR);
        }
        else
        {
            audio_mute_command();
        }
    }

    if (print_usage)
    {
        if (shorthelp)
        {
            USB_PRINTF("%s\n", argv[0]);
        }
        else
        {
            USB_PRINTF("Usage: %s\n", argv[0]);
        }
    }
    return(SHELL_EXIT_SUCCESS);
}

/******************************************************************************
*   @name        Shell_increase_volume
*
*   @brief       Servers the increase volume command
*
*   @param       None
*
*   @return      None
*
******************************************************************************
* This function is used to increase volume of the audio device
*****************************************************************************/
int32_t Shell_increase_volume(int32_t argc,char *argv[])
{
    bool         print_usage = FALSE, shorthelp = FALSE;
    print_usage = Shell_check_help_request (argc, argv, &shorthelp);
    if (!print_usage)
    {
        if (argc > 1)
        {
            USB_PRINTF ("  Error: Channel parameter is too large\n");
            return (SHELL_EXIT_ERROR);
        }
        else
        {
            audio_increase_volume_command(1);
        }
    }
    else
    {
        if (shorthelp)
        {
            USB_PRINTF("%s\n", argv[0]);
        }
        else
        {
            USB_PRINTF("Usage: %s\n", argv[0]);
        }
    }

    return(SHELL_EXIT_SUCCESS);
}

/******************************************************************************
*   @name        Shell_decrease_volume
*
*   @brief       Servers the decrease volume command
*
*   @param       None
*
*   @return      None
*
******************************************************************************
* This function is used to decrease volume of the audio device
*****************************************************************************/
int32_t Shell_decrease_volume(int32_t argc,char *argv[])
{
    bool         print_usage = TRUE, shorthelp = FALSE;
    volatile static uint16_t         cur_volume, min_volume;
    print_usage = Shell_check_help_request (argc, argv, &shorthelp);
    if (!print_usage)
    {
        if (argc > 1)
        {
            USB_PRINTF ("  Error: Channel parameter is too large\n");
            return (SHELL_EXIT_ERROR);
        }
        else
        {
            audio_decrease_volume_command(1);
        }
    }
    else
    {
        if (shorthelp)
        {
            USB_PRINTF("%s\n", argv[0]);
        }
        else
        {
            USB_PRINTF("Usage: %s\n", argv[0]);
        }
    }

    return(SHELL_EXIT_SUCCESS);
}
/* EOF */
