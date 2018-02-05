/**HEADER********************************************************************
* 
* Copyright (c) 2011, 2013 - 2014 Freescale Semiconductor;
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
* $FileName: wav.c$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains code for operations with WAVE files 
*
*END************************************************************************/
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#include <lwevent.h>
#include <bsp.h>
#else
#include "derivative.h"
#include "hidef.h"
#include "mem_util.h"
#endif
#include "usb_host_hub_sm.h"
#include "usb_host_audio.h"
#include "wav.h"
#include "audio_microphone.h"
/***************************************
**
** Global variables
****************************************/
extern usb_audio_stream_desc_format_type_t*  frm_type_desc;

/*FUNCTION****************************************************************
* 
* Function Name    : SetWaveHeader
* Returned Value   : Zero if everything is ok, non zero otherwise
* Comments         :
*    This function creates header according to format and writes it into
*    output file.
*    Returns 0 if everything passed, any other value = IO error
*
*END*********************************************************************/

_mqx_int SetWaveHeader
   (
    /* [OUT] header pointer to save header */
    wave_file_header_t* header, 
    
    /* [IN] file for writing */
    char *filename,
    /* length in seconds*/
    uint8_t *length
   )
{
   uint32_t tmp32 = 0;
   uint16_t tmp16 = 0;
   uint32_t vlength;
   FILE_PTR file_ptr;
   /* chunk descriptor */
   wave_chunk_descriptor_t* ch_des = &(header->chunk_descriptor);
   /* sub chunk */
   wave_fmt_subchunk_t* fmt_sch = &(header->fmt_subchunk);
   /* data chunk */
   wave_data_subchunk_t* data_sch = &(header->data_subchunk);
   /* open file to write */
   file_ptr = fopen(filename, "wb");
   if (NULL == file_ptr)
   {
      return(-1);
   }               
   /* Fill header */
   strncpy(ch_des->chunkid, "RIFF", sizeof(ch_des->chunkid));
   strncpy(ch_des->format, "WAVE", sizeof(ch_des->format));
   strncpy(fmt_sch->subchunk1id, "fmt ", sizeof(fmt_sch->subchunk1id));
   /* Sub chunk1 Size */
   fmt_sch->subchunk1size = 16;
   fmt_sch->audioformat = 1; /* PCM */
   /* Sample rate */
   fmt_sch->samplerate = ((frm_type_desc->tsamfreq[0][2] << BYTE2_SHIFT) |
                          (frm_type_desc->tsamfreq[0][1] << BYTE1_SHIFT) |
                          (frm_type_desc->tsamfreq[0][0] << BYTE0_SHIFT)) ;
   /* Bits per sample */
   fmt_sch->bitspersample = frm_type_desc->bbitresolution;
   /* Number of Channels */
   fmt_sch->numchannels = frm_type_desc->bnrchannels;
   fmt_sch->byterate = fmt_sch->samplerate * fmt_sch->numchannels *\
                       fmt_sch->bitspersample/8;
   /* Block Align*/
   fmt_sch->blockalign = fmt_sch->numchannels * fmt_sch->bitspersample/8;
   strncpy(data_sch->subchunk2id, "data", sizeof(data_sch->subchunk2id));
   /* Sub chunk2 Size*/
   vlength = atoi(length);
   data_sch->subchunk2size = vlength * fmt_sch->samplerate * \
                             fmt_sch->numchannels * fmt_sch->bitspersample/8;
   ch_des->chunksize = 4 + (8 + fmt_sch->subchunk1size) + (8 + data_sch->subchunk2size);
   
   /* Write header to file */
   /* Chunk descriptor */
   if (sizeof(ch_des->chunkid) != fwrite(&ch_des->chunkid, 1, sizeof(ch_des->chunkid), file_ptr))
      goto write_error;
   tmp32 = HOST_TO_LE_LONG(ch_des->chunksize);
   if (sizeof(tmp32) != fwrite(&tmp32, 1, sizeof(tmp32), file_ptr))
      goto write_error;
   if (sizeof(ch_des->format) != fwrite(&ch_des->format, 1, sizeof(ch_des->format), file_ptr))
       goto write_error;
   /* write format sub chunk */
   if (sizeof(fmt_sch->subchunk1id) != fwrite(&fmt_sch->subchunk1id, 1, sizeof(fmt_sch->subchunk1id), file_ptr))
       goto write_error;
   /* write Sub chunk1 Size*/
   tmp32 = HOST_TO_LE_LONG(fmt_sch->subchunk1size);
   if (sizeof(tmp32) != fwrite(&tmp32, 1, sizeof(tmp32), file_ptr))
       goto write_error;
   /* write Audio format*/
   tmp16 = HOST_TO_LE_SHORT(fmt_sch->audioformat);
   if (sizeof(tmp16) != fwrite(&tmp16, 1, sizeof(tmp16), file_ptr))
       goto write_error;
   /* write Num Channels*/
   tmp16 = HOST_TO_LE_SHORT(fmt_sch->numchannels);
   if (sizeof(tmp16) != fwrite(&tmp16, 1, sizeof(tmp16), file_ptr))
       goto write_error;
   /* write Sample Rate*/
   tmp32 = HOST_TO_LE_LONG(fmt_sch->samplerate);
   if (sizeof(tmp32) != fwrite(&tmp32, 1, sizeof(tmp32), file_ptr))
       goto write_error;
   /* write Byte Rate*/
   tmp32 = HOST_TO_LE_LONG(fmt_sch->byterate);
   if (sizeof(tmp32) != fwrite(&tmp32, 1, sizeof(tmp32), file_ptr))
       goto write_error;
   /* write Block Align*/
   tmp16 = HOST_TO_LE_SHORT(fmt_sch->blockalign);
   if (sizeof(tmp16) != fwrite(&tmp16, 1, sizeof(tmp16), file_ptr))
       goto write_error;
   /* write Bits Per Sample*/
   tmp16 = HOST_TO_LE_SHORT(fmt_sch->bitspersample);
   if (sizeof(tmp16) != fwrite(&tmp16, 1, sizeof(tmp16), file_ptr))
       goto write_error;
   /* data sub chunk */
   if (sizeof(data_sch->subchunk2id) != fwrite(&data_sch->subchunk2id, 1, sizeof(data_sch->subchunk2id), file_ptr))
       goto write_error;
   /* Sub chunk2 Size*/
   tmp32 = HOST_TO_LE_LONG(data_sch->subchunk2size);
   if (sizeof(tmp32) != fwrite(&tmp32, 1, sizeof(tmp32), file_ptr))
       goto write_error;
   
   fclose(file_ptr);
   return(0);

write_error:
   fclose(file_ptr);
   return -1;
}

/* EOF */
