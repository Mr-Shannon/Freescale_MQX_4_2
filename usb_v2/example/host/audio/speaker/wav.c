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

#include "wav.h"

extern uint8_t                           file_open_count;
_mqx_int FillWaveHeader(char *filename, wave_file_header_t* header)
{
    FILE_PTR file;
    uint8_t numread = 0;
    unsigned char def[] = {sizeof(header->chunk_descriptor.chunksize), 0};
    /* CHUNK DESCRIPTOR */
    wave_chunk_descriptor_t* ch_des = &(header->chunk_descriptor);
    /* FMT SUBCHUNK */
    wave_fmt_subchunk_t* fmt_sch = &(header->fmt_subchunk);
    /* DATA SUBCHUNK */
    wave_data_subchunk_t* data_sch = &(header->data_subchunk);
    file = fopen(filename, "r");
    if (file == NULL)
    {

        return(-1);
    }
    file_open_count ++;
    /* read Chunk ID */
    numread = fread(&(ch_des->chunkid), 1, 4, file);
    if( numread == 0 )
    {
        return(-1);
    }    
    ch_des->chunkid[4] = '\0';
    /* read  Chunk Size */
    numread = fread(&(ch_des->chunksize), 1, 4, file);
    _mem_swap_endian(def, &(ch_des->chunksize));
    /* read  Chunk format */
    numread = fread(&(ch_des->format), 1, 4, file);
    ch_des->format[4] = '\0';
    /* read  Sub chunk1 ID */
    numread = fread(&(fmt_sch->subchunk1id), 1, 4, file);
    fmt_sch->subchunk1id[4] = '\0';
    /* read  Sub chunk1 Size */
    numread = fread(&(fmt_sch->subchunk1size), 1, 4, file);
    def[0] = sizeof(fmt_sch->subchunk1size);
    _mem_swap_endian(def, &(fmt_sch->subchunk1size));
    /* read  Audio format */
    numread = fread(&(fmt_sch->audioformat), 1, 2, file);
    def[0] = sizeof(fmt_sch->audioformat);
    _mem_swap_endian(def, &(fmt_sch->audioformat));
    /* read  Num Channels */
    numread = fread(&(fmt_sch->numchannels), 1, 2, file);
    def[0] = sizeof(fmt_sch->numchannels);
    _mem_swap_endian(def, &(fmt_sch->numchannels));
    /* read  Sample Rate */
    numread = fread(&(fmt_sch->samplerate), 1, 4, file);
    def[0] = sizeof(fmt_sch->samplerate);
    _mem_swap_endian(def, &(fmt_sch->samplerate));
    /* read  Byte Rate */
    numread = fread(&(fmt_sch->byterate), 1, 4, file);
    def[0] = sizeof(fmt_sch->byterate);
    _mem_swap_endian(def, &(fmt_sch->byterate));
    /* read  Block Align */
    numread = fread(&(fmt_sch->blockalign), 1, 2, file);
    def[0] = sizeof(fmt_sch->blockalign);
    _mem_swap_endian(def, &(fmt_sch->blockalign));
    /* read  Bits Per Sample*/
    numread = fread(&(fmt_sch->bitspersample), 1, 2, file);
    def[0] = sizeof(fmt_sch->bitspersample);
    _mem_swap_endian(def, &(fmt_sch->bitspersample));
    /* read  Sub chunk2 ID*/
    numread = fread(&(data_sch->subchunk2id), 1, 4, file);

    data_sch->subchunk2id[4] = '\0';
    /* read  Sub chunk2 Size*/
    numread = fread(&(data_sch->subchunk2size), 1, 4, file);
    def[0] = sizeof(data_sch->subchunk2size);
    _mem_swap_endian(def, &(data_sch->subchunk2size));
    fclose(file);
    file_open_count --;
    return(0);
}
/* EOF */
