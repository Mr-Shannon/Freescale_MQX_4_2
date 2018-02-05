#include <mqx.h>
#include <bsp.h>
#include <fio.h>

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

/* This demo need SDRAMC to be enabled, and the initialization for SDRAMC has been set during system startup. */
#if (!BSPCFG_ENABLE_SDRAMC)
#error This application requires BSPCFG_ENABLE_SDRAMC defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

/* Keep the base address that mapping external SDRAM. */
#ifndef BSP_SDRAM_BASE
    #define BSP_SDRAM_BASE   (0x70000000UL)
#endif /* BSP_SDRAM_BASE */

/* Keep the memory size in byte of external SDRAM. */
#ifndef BSP_SDRAM_SIZE
    #define BSP_SDRAM_SIZE   (0x0080000UL)
#endif /* BSP_SDRAM_SIZE */

/* This word would be write to SDRAM and read back to be validated.*/
#define SDRAM_VALIDATE_DAT32_MASK (0x50505050UL)
/* Block size in size for validation. */
#define SDRAM_VALIDATE_BLOCK_SIZE (1024U) /* 1 KB */
/* Block counts.  */
#define SDRAM_VALIDATE_BLOCK_COUNTS (BSP_SDRAM_SIZE/SDRAM_VALIDATE_BLOCK_SIZE)

/* TASK IDs. */
#define SDRAM_TASK    (5U)

extern void sdramc_task(uint32_t);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{ 
    /* Task Index,   Function,   Stack,  Priority, Name,     Attributes,          Param, Time Slice */
    { SDRAM_TASK, sdramc_task, 3000,  8,    "sdramc",  MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/* Write data to SDRAM. The parameter of "addr" is the offset address inside the SDRAM. */
void sdramc_write_32bit(uint32_t addr, uint32_t dat)
{
    *((uint32_t *)(BSP_SDRAM_BASE + addr)) = dat;
}

/* Read data from SDRAM. The parameter of "addr" is the offset address inside the SDRAM. */
uint32_t sdramc_read_32bit(uint32_t addr)
{
    return (uint32_t)(*((uint32_t *)(BSP_SDRAM_BASE + addr)));
}

/*TASK*-----------------------------------------------------
* 
* Task Name    : sdramc_task
* Comments     :
*    This task prints validate the access to SDRAM.
*
*END*-----------------------------------------------------*/
void sdramc_task(uint32_t initial_data)
{
    (void)initial_data; /* disable 'unused variable' warning */

    uint32_t addr = 0U; /* Offset address mapping for external SDRAM. */
    uint32_t blk_offset = 0U; /* Offset address in block. */
    uint32_t blk_counter = 0U; /* Block counter for external SDRAM. */
    uint32_t blk_right_counter = 0U; /* Block counter for right blocks. */

    printf("\r\n MQX SDRAMC DEMO EXAMPLE. \r\n");
    
    /* Write the block and read to validate the data. */
    while (blk_counter < SDRAM_VALIDATE_BLOCK_COUNTS)
    {
        /* Write data into external SDRAM. */
        for (blk_offset = 0U; blk_offset < SDRAM_VALIDATE_BLOCK_SIZE; blk_offset += 4U)
        {
            sdramc_write_32bit(addr + blk_offset, SDRAM_VALIDATE_DAT32_MASK);
        }

        /* Validate the read back data from SDRAM. */
        for (blk_offset = 0U; blk_offset < SDRAM_VALIDATE_BLOCK_SIZE; blk_offset += 4U)
        {
            if (SDRAM_VALIDATE_DAT32_MASK != sdramc_read_32bit(addr + blk_offset) )
            {
                printf("SDRAM access error at block %4d,  0x%8X\r\n",
                    blk_counter, BSP_SDRAM_BASE+addr+blk_offset);
                break;
            }
        }
        if (SDRAM_VALIDATE_BLOCK_SIZE == blk_offset)
        {
            printf("Block validated: %6d\r\n", blk_counter);
            blk_right_counter += 1U;
        }
    
        addr += SDRAM_VALIDATE_BLOCK_SIZE;
        blk_counter += 1U;
    }

    /* Validate the rest block of SDRAM. */
    if (addr < BSP_SDRAM_SIZE)
    {
        /* Write data into external SDRAM. */
        for (blk_offset = 0U; blk_offset < BSP_SDRAM_SIZE-addr; blk_offset += 4U)
        {
            sdramc_write_32bit(addr + blk_offset, SDRAM_VALIDATE_DAT32_MASK);
        }
        /* Validate the read back data from SDRAM. */
        for (blk_offset = 0U; blk_offset < BSP_SDRAM_SIZE-addr; blk_offset += 4U)
        {
            if (SDRAM_VALIDATE_DAT32_MASK != sdramc_read_32bit(addr + blk_offset) )
            {
                printf("SDRAM access error at block %6d,  0x%8X\r\n",
                    blk_counter, BSP_SDRAM_BASE+addr+blk_offset);
                break;
            }
        }
        if ( (BSP_SDRAM_SIZE-addr) == blk_offset)
        {
            printf("Block validated: %6d\r\n", blk_counter);
            blk_right_counter += 1U;
        }
    }

    
    printf("\r\n SDRAM Validation Report \r\n");
    printf("SDRAM start address: 0x%X\r\n", BSP_SDRAM_BASE);
    printf("SDRAM total size: %d\r\n", BSP_SDRAM_SIZE);
    printf("Block size in Byte: %d\r\n", SDRAM_VALIDATE_BLOCK_SIZE);
    printf("Total block count: %d\r\n", blk_counter);
    printf("Right block count: %d\r\n", blk_right_counter);
    printf("Error block count: %d\r\n", blk_counter - blk_right_counter);
    printf("\r\n");

    _task_block();
}


/* EOF */

