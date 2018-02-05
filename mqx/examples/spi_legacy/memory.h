#ifndef __memory_h__
#define __memory_h__
/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   This file contains definitions for the SPI memory example.
*
*
*END************************************************************************/

/* The SPI serial memory test addresses */
#define SPI_MEMORY_ADDR1               0x0000F0 /* test address 1 */
#define SPI_MEMORY_ADDR2               0x0001F0 /* test address 2 */
#define SPI_MEMORY_ADDR3               0x0002F0 /* test address 3 */

/* Number of bytes used for addressing within memory */
#define SPI_MEMORY_ADDRESS_BYTES       3        

/* Memory page size - maximum bytes per write */
#define SPI_MEMORY_PAGE_SIZE           0x0100   

/* The SPI serial memory instructions */
#define SPI_MEMORY_WRITE_STATUS        0x01
#define SPI_MEMORY_WRITE_DATA          0x02
#define SPI_MEMORY_READ_DATA           0x03
#define SPI_MEMORY_WRITE_LATCH_DISABLE 0x04
#define SPI_MEMORY_READ_STATUS         0x05
#define SPI_MEMORY_WRITE_LATCH_ENABLE  0x06
#define SPI_MEMORY_CHIP_ERASE          0xC7

/* Common data variables */
extern unsigned char   send_buffer[];
extern unsigned char   recv_buffer[];

/* Funtion prototypes */
extern void    set_CS (uint32_t cs_mask, uint32_t logic_level, void *user_data);

extern void    memory_chip_erase (MQX_FILE_PTR spifd);
extern void    memory_set_write_latch (MQX_FILE_PTR spifd, bool enable);
extern void    memory_set_protection (MQX_FILE_PTR spifd, bool protect);
extern uint8_t  memory_read_status (MQX_FILE_PTR spifd);
extern void    memory_write_byte (MQX_FILE_PTR spifd, uint32_t addr, unsigned char data);
extern uint8_t  memory_read_byte (MQX_FILE_PTR spifd, uint32_t addr);
extern uint32_t memory_write_data (MQX_FILE_PTR spifd, uint32_t addr, uint32_t size, unsigned char *data);
extern uint32_t memory_read_data (MQX_FILE_PTR spifd, uint32_t addr, uint32_t size, unsigned char *data);

extern void    memory_chip_erase_interrupt (MQX_FILE_PTR spifd);
extern void    memory_set_write_latch_interrupt (MQX_FILE_PTR spifd, bool enable);
extern void    memory_set_protection_interrupt (MQX_FILE_PTR spifd, bool protect);
extern uint8_t  memory_read_status_interrupt (MQX_FILE_PTR spifd);
extern void    memory_write_byte_interrupt (MQX_FILE_PTR spifd, uint32_t addr, unsigned char data);
extern uint8_t  memory_read_byte_interrupt (MQX_FILE_PTR spifd, uint32_t addr);
extern uint32_t memory_write_data_interrupt (MQX_FILE_PTR spifd, uint32_t addr, uint32_t size, unsigned char *data);
extern uint32_t memory_read_data_interrupt (MQX_FILE_PTR spifd, uint32_t addr, uint32_t size, unsigned char *data);

#endif
/* EOF */
