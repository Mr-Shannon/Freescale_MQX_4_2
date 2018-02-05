/**HEADER********************************************************************
*
* Copyright (c) 2010, 2013 -2014 Freescale Semiconductor;
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
* $FileName: wav.h$
* $Version :
* $Date    :
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the WAVE file format that is a subset of Microsoft's
*   RIFF specification for the storage of multimedia files. .
*
*END************************************************************************/
#ifndef __wav_h_
#define __wav_h_



#define WAVE_HEADER_SIZE 44
#if PSP_ENDIAN
#define BYTESWAP16(x)      (uint16_t)((((x) & 0xFF00) >> 0x8) | (((x) & 0xFF) << 0x8))
#define BYTESWAP32(val)    (uint32_t)((BYTESWAP16((uint32_t)(val) & (uint32_t)0xFFFF) << 0x10) |  \
    (BYTESWAP16((uint32_t)((val) >> 0x10))))
#else
#define BYTESWAP16(x)       (uint16_t)(x)
#define BYTESWAP32(x)       (uint32_t)(x)
#endif

typedef struct wave_chunk_descriptor
{
    /* 
    ** chunkid. contains the letters "riff" in ascii form
    ** (0x52494646 big-endian form).
    */
    char chunkid[5];

    /* 
    ** chunksize. 4 + (8 + subchunk1size) + (8 + subchunk2size)
    ** this is the size of the rest of the chunk
    ** following this number.  this is the size of the
    ** entire file in bytes minus 8 bytes for the
    ** two fields not included in this count:
    ** chunkid and chunksize.
    */
    uint32_t chunksize;

    /* 
    ** format. contains the letters "wave"
    ** (0x57415645 big-endian form).
    */
    char format[5];

} wave_chunk_descriptor_t;

typedef struct wave_fmt_subchunk
{
    /*
    ** subchunk1id. contains the letters "fmt "
    ** (0x666d7420 big-endian form).
    */
    char subchunk1id[5];

    /*
    ** subchunk1size. 16 for pcm. this is the size of the
    ** rest of the subchunk which follows this number.
    */
    uint32_t subchunk1size;

    /*
    ** audioformat. pcm = 1 (i.e. linear quantization)
    ** values other than 1 indicate some
    ** form of compression.
    */
    uint16_t audioformat;

    /*
    ** numchannels. mono = 1, stereo = 2, etc.
    */
    uint16_t numchannels;

    /*
    ** samplerate. 8000, 44100, etc.
    */
    uint32_t samplerate;

    /*
    ** byterate. samplerate * numchannels * bitspersample/8
    */
    uint32_t byterate;

    /*
    ** blockalign. numchannels * bitspersample/8
    ** the number of bytes for one sample including
    ** all channels.
    */
    uint16_t blockalign;

    /*
    ** bitspersample. 8 bits = 8, 16 bits = 16, etc.
    */
    uint16_t bitspersample;

} wave_fmt_subchunk_t;

typedef struct wave_data_subchunk
{
    /*
    ** subchunk2id. contains the letters "data"
    ** (0x64617461 big-endian form).
    */
    char subchunk2id[5];

    /*
    ** subchunk2size. numsamples * numchannels * bitspersample/8
    ** this is the number of bytes in the data.
    ** you can also think of this as the size
    ** of the read of the subchunk following this number.
    */
    uint32_t subchunk2size;

} wave_data_subchunk_t;

typedef struct wave_file_header
{
    /* The RIFF chunk descriptor*/
    wave_chunk_descriptor_t chunk_descriptor;

    /* format subchunk */
    wave_fmt_subchunk_t fmt_subchunk;

    /* audio data */
    wave_data_subchunk_t data_subchunk;

} wave_file_header_t;

#ifdef __cplusplus
extern "C" {
#endif

    extern _mqx_int FillWaveHeader(char *filename, wave_file_header_t* header);

#ifdef __cplusplus
}
#endif
#endif
/* EOF */
