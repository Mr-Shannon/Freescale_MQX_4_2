#include <mqx.h>
#include <bsp.h>
#include <fio.h>

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

/* This demo need FlexBusMRAM to be enabled, and the initialization for FlexBusMRAM has been set during system startup. */
#if (BSP_TWR_K65F180M && (!BSPCFG_ENABLE_FLEXBUS_MRAM))
#error This application requires BSPCFG_ENABLE_FLEXBUS_MRAM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#if (BSP_TWR_K65F180M && BSPCFG_ENABLE_SDRAMC)
#error This application requires BSPCFG_ENABLE_SDRAMC defined zero in user_config.h. Please recompile BSP with this option.
#endif

/* Keep the base address that mapping external MRAM. */
#ifndef BSP_EXTERNAL_MRAM_ROM_BASE
    #define BSP_EXTERNAL_MRAM_ROM_BASE   (void *)(0x60000000UL)
#endif /* BSP_MRAM_BASE */

/* Keep the memory size in byte of external MRAM. */
#ifndef BSP_EXTERNAL_MRAM_ROM_SIZE
    #define BSP_EXTERNAL_MRAM_ROM_SIZE   (0x00060000UL)
#endif /* BSP_MRAM_SIZE */

/* Keep the base address that mapping external MRAM. */
#ifndef BSP_EXTERNAL_MRAM_RAM_BASE
    #define BSP_EXTERNAL_MRAM_RAM_BASE   (void *)(0x60060000UL)
#endif /* BSP_MRAM_BASE */

/* Keep the memory size in byte of external MRAM. */
#ifndef BSP_EXTERNAL_MRAM_RAM_SIZE
    #define BSP_EXTERNAL_MRAM_RAM_SIZE   (0x00020000UL)
#endif /* BSP_MRAM_SIZE */

#define BSP_MRAM_BASE (BSP_EXTERNAL_MRAM_ROM_BASE)
#define BSP_MRAM_SIZE (BSP_EXTERNAL_MRAM_ROM_SIZE+BSP_EXTERNAL_MRAM_RAM_SIZE)

/* This word would be write to MRAM and read back to be validated.*/
#define MRAM_VALIDATE_DAT32_MASK (0x50505050UL)
/* Block size in size for validation. */
#define MRAM_VALIDATE_BLOCK_SIZE (1024U) /* 1 KB */
/* Block counts.  */
#define MRAM_VALIDATE_BLOCK_COUNTS ((BSP_EXTERNAL_MRAM_ROM_SIZE+BSP_EXTERNAL_MRAM_RAM_SIZE)/MRAM_VALIDATE_BLOCK_SIZE)

/* TASK IDs. */
#define MRAM_TASK    (5U)

extern void FlexBusMRAM_task(uint32_t);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{ 
    /* Task Index,   Function,   Stack,  Priority, Name,     Attributes,          Param, Time Slice */
    { MRAM_TASK, FlexBusMRAM_task, 3000,  8,    "FlexBusMRAM",  MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/* Write data to MRAM. The parameter of "addr" is the offset address inside the MRAM. */
void FlexBusMRAM_write_32bit(uint32_t addr, uint32_t dat)
{
    *((uint32_t *)((uint32_t)BSP_EXTERNAL_MRAM_ROM_BASE + addr)) = dat;
}

/* Read data from MRAM. The parameter of "addr" is the offset address inside the MRAM. */
uint32_t FlexBusMRAM_read_32bit(uint32_t addr)
{
    return (uint32_t)(*((uint32_t *)((uint32_t)BSP_EXTERNAL_MRAM_ROM_BASE + addr)));
}

/*TASK*-----------------------------------------------------
* 
* Task Name    : FlexBusMRAM_task
* Comments     :
*    This task prints validate the access to MRAM.
*
*END*-----------------------------------------------------*/
void FlexBusMRAM_task(uint32_t initial_data)
{
    (void)initial_data; /* disable 'unused variable' warning */

    uint32_t addr = 0U; /* Offset address mapping for external MRAM. */
    uint32_t blk_offset = 0U; /* Offset address in block. */
    uint32_t blk_counter = 0U; /* Block counter for external MRAM. */
    uint32_t blk_right_counter = 0U; /* Block counter for right blocks. */

    printf("\r\n MQX FlexBusMRAM DEMO EXAMPLE. \r\n");
    
    /* Write the block and read to validate the data. */
    while (blk_counter < MRAM_VALIDATE_BLOCK_COUNTS)
    {
        /* Write data into external MRAM. */
        for (blk_offset = 0U; blk_offset < MRAM_VALIDATE_BLOCK_SIZE; blk_offset += 4U)
        {
            FlexBusMRAM_write_32bit(addr + blk_offset, MRAM_VALIDATE_DAT32_MASK);
        }

        /* Validate the read back data from MRAM. */
        for (blk_offset = 0U; blk_offset < MRAM_VALIDATE_BLOCK_SIZE; blk_offset += 4U)
        {
            if (MRAM_VALIDATE_DAT32_MASK != FlexBusMRAM_read_32bit(addr + blk_offset) )
            {
                printf("MRAM access error at block %4d,  0x%8X\r\n",
                    blk_counter, (uint32_t)BSP_EXTERNAL_MRAM_ROM_BASE+addr+blk_offset);
                break;
            }
        }
        if (MRAM_VALIDATE_BLOCK_SIZE == blk_offset)
        {
            printf("Block validated: %6d\r\n", blk_counter);
            blk_right_counter += 1U;
        }
    
        addr += MRAM_VALIDATE_BLOCK_SIZE;
        blk_counter += 1U;
    }

    /* Validate the rest block of MRAM. */
    if (addr < BSP_MRAM_SIZE)
    {
        /* Write data into external MRAM. */
        for (blk_offset = 0U; blk_offset < BSP_MRAM_SIZE-addr; blk_offset += 4U)
        {
            FlexBusMRAM_write_32bit(addr + blk_offset, MRAM_VALIDATE_DAT32_MASK);
        }
        /* Validate the read back data from MRAM. */
        for (blk_offset = 0U; blk_offset < BSP_MRAM_SIZE-addr; blk_offset += 4U)
        {
            if (MRAM_VALIDATE_DAT32_MASK != FlexBusMRAM_read_32bit(addr + blk_offset) )
            {
                printf("MRAM access error at block %6d,  0x%8X\r\n",
                    blk_counter, (uint32_t)BSP_MRAM_BASE+addr+blk_offset);
                break;
            }
        }
        if ( (BSP_MRAM_SIZE-addr) == blk_offset)
        {
            printf("Block validated: %6d\r\n", blk_counter);
            blk_right_counter += 1U;
        }
    }

    
    printf("\r\n MRAM Validation Report \r\n");
    printf("MRAM start address: 0x%X\r\n", BSP_MRAM_BASE);
    printf("MRAM total size: %d\r\n", BSP_MRAM_SIZE);
    printf("Block size in Byte: %d\r\n", MRAM_VALIDATE_BLOCK_SIZE);
    printf("Total block count: %d\r\n", blk_counter);
    printf("Right block count: %d\r\n", blk_right_counter);
    printf("Error block count: %d\r\n", blk_counter - blk_right_counter);
    printf("\r\n");

    _task_block();
}


/* EOF */

