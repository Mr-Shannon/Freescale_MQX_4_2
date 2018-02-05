/**HEADER********************************************************************
 *
 * Copyright (c) 2013 Freescale Semiconductor;
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
 * $FileName: sd.h$
 * $Version :
 * $Date    :
 *
 * Comments:
 *
 *
 *END************************************************************************/
 
#ifndef __SD_H__
#define __SD_H__
#include "usb_device_stack_interface.h"

#include "disk.h"

#if SD_CARD_APP
#define SDCARD_BLOCK_SIZE_POWER   (9)
#define SDCARD_BLOCK_SIZE         (1 << SDCARD_BLOCK_SIZE_POWER)

extern MQX_FILE_PTR sd_init( void );
extern bool sd_detect_check();
extern bool sd_protect_check();
extern _mqx_uint sd_read_device_sectors(MQX_FILE_PTR, uint32_t, uint32_t, uint32_t, uint8_t*, uint32_t*);
extern _mqx_uint sd_write_device_sectors(MQX_FILE_PTR, uint32_t, uint32_t, uint32_t, uint8_t*, uint32_t*);
extern _mqx_uint sd_get_block_size(MQX_FILE_PTR, uint32_t *);
extern _mqx_uint sd_get_blocks_num(MQX_FILE_PTR, uint32_t *);

#endif

#endif /* __SD_H__ */

/* EOF */
