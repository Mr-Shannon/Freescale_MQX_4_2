/**HEADER********************************************************************
* 
* Copyright (c) 2009, 2013 - 2014 Freescale Semiconductor;
* All Rights Reserved
*
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
* @file sd_esdhc_kinetis.h
*
* @author
*
* @version
*
* @date 
*
* @brief  This file is SD Card Driver Header File
*****************************************************************************/
#ifndef __SD_esdhc_kinetis__
#define __SD_esdhc_kinetis__


/* Includes */
#include "derivative.h"
#include "esdhc_kinetis.h"
#include "usb_class_msc.h"

#if SD_CARD_APP
/* User definitions */
#define SD_BLOCK_512
#define SD_WAIT_CYCLES 10

#ifdef SD_BLOCK_512
#define SD_BLOCK_SIZE   (0x00000200)
#define SD_BLOCK_SHIFT  (9)
#define BLOCK_SIZE      512
#endif


/* TypeDefs */
typedef union
{
   uint8_t  bytes[4];
   uint32_t lword;
}T32_8;


typedef union
{
   uint8_t  u8[2];
   uint16_t u16;
}T16_8;


/* Prototypes */
uint8_t SD_Init(void);
extern void   SD_Write_Block(lba_app_struct_t*);
extern void   SD_Read_Block(lba_app_struct_t*);
extern void SD_Card_Info(uint32_t * max_blocks_ptr, uint32_t * block_size_ptr);

#endif

#endif /* __SD_esdhc_kinetis__ */

