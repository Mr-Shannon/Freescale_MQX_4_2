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
Provide MFS file system on internal NAND Flash memory.
*
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <mfs.h>
#include <shell.h>
#include <part_mgr.h>
#include "nandflash_wl_ffs.h"

#if ! SHELLCFG_USES_MFS
#error This application requires SHELLCFG_USES_MFS defined non-zero in user_config.h. Please recompile libraries with this option.
#endif

extern const NANDFLASH_WL_INIT_STRUCT _bsp_nandflash_wl_init;

void shell_task(uint32_t);

int32_t shell_fs_open(int32_t argc, char * argv[] );
int32_t shell_fs_close(int32_t argc, char * argv[] );
int32_t shell_nand_erase(int32_t argc, char * argv[] );
int32_t shell_nand_erase_chip(int32_t argc, char * argv[] );
int32_t shell_nand_get_bad_block_table(int32_t argc, char * argv[] );
int32_t shell_nand_repair(int32_t argc, char * argv[] );
int32_t mfs_nandflash_wl_open(void);
int32_t mfs_nandflash_wl_close(void);

void nandflash_erase(void);
void nandflash_erase_chip(void);
void nandflash_get_bad_block_table(void);
void nandflash_repair(void);

TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
    /* Task Index,  Function,       Stack,  Priority,   Name,       Attributes,             Param,  Time Slice */
    { 1,            shell_task,     3000,  12,         "Shell",    MQX_AUTO_START_TASK,    0,      0 },
    { 0 }
};

const SHELL_COMMAND_STRUCT Shell_commands[] = {
    { "cd",             Shell_cd },
    { "copy",           Shell_copy },
    { "create",         Shell_create },
    { "del",            Shell_del },
    { "disect",         Shell_disect},
    { "dir",            Shell_dir },
    { "di",             Shell_di   },
    { "exit",           Shell_exit },
    { "format",         Shell_format },
    { "help",           Shell_help },
    { "mkdir",          Shell_mkdir },
    { "pwd",            Shell_pwd },
    { "read",           Shell_read },
    { "ren",            Shell_rename },
    { "rmdir",          Shell_rmdir },
    { "sh",             Shell_sh },
    { "type",           Shell_type },
    { "write",          Shell_write },
    { "fsopen",         shell_fs_open },
    { "fsclose",        shell_fs_close },
    { "nanderase",      shell_nand_erase },
    { "nandrepair",     shell_nand_repair },
    { "nanderasechip",  shell_nand_erase_chip },
    { "nandgetbbt",     shell_nand_get_bad_block_table },
    { "?",              Shell_command_list },
    { NULL,             NULL }
};

bool inserted = TRUE, readonly = FALSE, last = FALSE;
_mqx_int error_code;
_mqx_uint param;
MQX_FILE_PTR com_handle, nandflash_handle, filesystem_handle, partman_handle;
char filesystem_name[] = "a:";
char partman_name[] = "pm:";

#define FFS_DEVICE "nandflash_wl:"

/*TASK*-----------------------------------------------------------------
*
* Function Name  : nandflash_erase
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void nandflash_erase()
{
    if (nandflash_handle == NULL)
    {
        nandflash_handle = fopen(FFS_DEVICE, NANDWL_OPEN_FORCE_REPAIR_WHEN_FAILED);
    }

    printf("\nErasing nand drive ... \n");

    if (MQX_OK != ioctl(nandflash_handle, NANDFLASH_IOCTL_ERASE, (void*)0))
    {
        printf("\nSome errors occured. Please close the device and try again.\n");
        return;
    }
    else
    {
        if (filesystem_handle == NULL)
        {
            error_code = _io_mfs_install(nandflash_handle, filesystem_name, (_file_size)0);
            if (error_code != MFS_NO_ERROR)
            {
                printf("Error initializing MFS: %s\n", MFS_Error_text((uint32_t)error_code));
                _task_block();
            }
            /* Open file system */
            filesystem_handle = fopen(filesystem_name, NULL);
            error_code = ferror (filesystem_handle);
            if ((error_code != MFS_NO_ERROR) && (error_code != MFS_NOT_A_DOS_DISK))
            {
                printf("Error opening filesystem: %s\n", MFS_Error_text((uint32_t)error_code));
                _task_block();
            }

            if ( error_code == MFS_NOT_A_DOS_DISK )
            {
                printf("NOT A DOS DISK! You must format to continue.\n");
                return ;
            }
        }
        printf("\nNand drive was erased completely. Please run fsclose command to close device then run fsopen command to open again.\n");
    }
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : nandflash_erase_chip
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void nandflash_erase_chip()
{
    int i;

    if (nandflash_handle != NULL)
    {
        printf("\n Filesystem must be closed before erasing entire chip \n");
        return;
    }

    nandflash_handle = fopen(FFS_DEVICE, NANDWL_OPEN_IGNORE_INIT_MEDIA);

    printf("\nErasing entire chip ... \n");
    for (i = NANDFLASH_1ST_DATA_DRIVE_START_BLOCK; i < NANDFLASH_1ST_DATA_DRIVE_START_BLOCK + NANDFLASH_1ST_DATA_DRIVE_SIZE_IN_BLOCK; i++)
    {
        if (MQX_OK != ioctl(nandflash_handle, NANDFLASH_IOCTL_ERASE_BLOCK_FORCE, (void*) i))
        {
            printf("\nerase block %d FAILED", i);
        }
    }

    fclose(nandflash_handle);
    nandflash_handle = NULL;
    printf("\nPlease use fsopen command to re-open NAND flash device.\n");

    return;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : nandflash_get_bad_block_table
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void nandflash_get_bad_block_table()
{
    _mqx_int    i;
    uint8_t     *bbt;
    _mqx_uint   num_blocks, bad_count;

    if (nandflash_handle != NULL)
    {
        printf("\n Filesystem must be closed before getting bad block table \n");
        return;
    }
    
    nandflash_handle = fopen(FFS_DEVICE, NANDWL_OPEN_IGNORE_INIT_MEDIA);

    if(MQX_OK == ioctl(nandflash_handle, NANDFLASH_IOCTL_GET_NUM_BLOCKS, &num_blocks))
    printf("\nNumber of blocks: %d", num_blocks);
    else
    printf("\nNumber of blocks not obtained");

    /* Get Bad Block Table */
    bbt = (uint8_t *)_mem_alloc_zero(num_blocks);
    bad_count = 0;
    if(MQX_OK == ioctl(nandflash_handle, NANDFLASH_IOCTL_GET_BAD_BLOCK_TABLE, bbt))
    {
        for (i = 0; i < (_mqx_int)num_blocks; i++)
        {
            if(bbt[i] == 0)
            {
                bad_count++;
                printf("\nBlock #%d is bad", i);
            }
        }
    }
    else
    {
        printf("\nReading Bad block table not successful ");
    }
    printf("\nThere are %d bad blocks\n", bad_count);
    _mem_free(bbt);

    fclose(nandflash_handle);
    nandflash_handle = NULL;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : nandflash_repair
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void nandflash_repair()
{
    if (nandflash_handle != NULL)
    {
        fclose(nandflash_handle);
        nandflash_handle = NULL;
    }
    printf("\nRepairing...\n");

    /* Open nand flash wl in force_repair mode */
    nandflash_handle = fopen(FFS_DEVICE, NANDWL_OPEN_FORCE_REPAIR_WHEN_FAILED);

    if (nandflash_handle != NULL)
    {
        if (filesystem_handle == NULL)
        {
            error_code = _io_mfs_install(nandflash_handle, filesystem_name, (_file_size)0);
            if (error_code != MFS_NO_ERROR)
            {
                printf("Error initializing MFS: %s\n", MFS_Error_text((uint32_t)error_code));
                _task_block();
            }
            /* Open file system */
            filesystem_handle = fopen(filesystem_name, NULL);
            error_code = ferror (filesystem_handle);
            if ((error_code != MFS_NO_ERROR) && (error_code != MFS_NOT_A_DOS_DISK))
            {
                printf("Error opening filesystem: %s\n", MFS_Error_text((uint32_t)error_code));
                _task_block();
            }

            if ( error_code == MFS_NOT_A_DOS_DISK )
            {
                printf("NOT A DOS DISK! You must format to continue.\n");
                return ;
            }
        }
        printf("\nRepair successfully\n");
    } else {
        printf("\nYou must re-open\n");
    }
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : mfs_nandflash_wl_open
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t mfs_nandflash_wl_open()
{
    if (nandflash_handle == NULL)
    {
        /* Open nand flash wl in normal mode */
        nandflash_handle = fopen(FFS_DEVICE, NANDWL_OPEN_NORMAL);
        if ( nandflash_handle == NULL )
        {
            printf("Unable to open nandflash device.\n");
            printf("\nYou must run \"nandrepair\" command\n");
            return 0;
        }

        /* Install MFS over nand_wl driver */
        error_code = _io_mfs_install(nandflash_handle, filesystem_name, (_file_size)0);
        if (error_code != MFS_NO_ERROR)
        {
            printf("Error initializing MFS: %s\n", MFS_Error_text((uint32_t)error_code));
            _task_block();
        }

        if (filesystem_handle == NULL)
        {
            /* Open file system */
            filesystem_handle = fopen(filesystem_name, NULL);
            error_code = ferror (filesystem_handle);
            if ((error_code != MFS_NO_ERROR) && (error_code != MFS_NOT_A_DOS_DISK))
            {
                printf("Error opening filesystem: %s\n", MFS_Error_text((uint32_t)error_code));
                _task_block();
            }

            if ( error_code == MFS_NOT_A_DOS_DISK )
            {
                printf("NOT A DOS DISK! You must format to continue.\n");
                return 0;

            }

            printf ("NAND flash installed to %s\n", filesystem_name);
        }
        else
        {
            printf("\nNAND flash was installed.\n");
        }
    }
    else
    {
        printf("\nNAND flash device was opened.\n");
    }

    return 0;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : mfs_nandflash_wl_close
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t mfs_nandflash_wl_close()
{
    if (filesystem_handle != NULL)
    {
        /* Close the filesystem */
        if (MQX_OK != fclose (filesystem_handle))
        {
            printf("Error closing filesystem.\n");
            _task_block();
        }
        filesystem_handle = NULL;
    }

    if (nandflash_handle != NULL)
    {
        /* Uninstall MFS  */
        error_code = _io_dev_uninstall(filesystem_name);
        if (error_code != MFS_NO_ERROR)
        {
            printf("Error uninstalling filesystem.\n");
            _task_block();
        }

        /* Close the nand flash device */
        if (MQX_OK != fclose (nandflash_handle))
        {
            printf("Unable to close nandflash device.\n");
            _task_block();
        }
        nandflash_handle = NULL;

        printf ("nandflash uninstalled.\n");
    }

    return 0;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void shell_task(uint32_t temp)
{
    /* Run the shell on the serial port */
    printf("This is the Flash File System example, type help for list of available commands\n");
    printf("If this is the first time you use the demo, you should run \"nanderasechip\" command first.\n");

    if (_io_nandflash_wl_install(&_bsp_nandflash_wl_init, FFS_DEVICE) != MQX_OK)
    {
        printf("Can't install FFS!\n");
        _task_block();
    }

    for(;;)
    {
        Shell(Shell_commands, NULL);
        printf("Shell exited, restarting...\n");
    }
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_fs_open
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t  shell_fs_open(int32_t argc, char * argv[] )
{
    bool              print_usage, shorthelp = FALSE;
    int32_t               return_code = SHELL_EXIT_SUCCESS;

    print_usage = Shell_check_help_request(argc, argv, &shorthelp );

    if (!print_usage)  {
        if (argc != 1)
        {
            printf("Error, invalid number of parameters\n");
            return_code = SHELL_EXIT_ERROR;
            print_usage=TRUE;
        }
        else
        {
            mfs_nandflash_wl_open();
        }
    }

    if (print_usage)  {
        if (shorthelp)  {
            printf("%s \n", argv[0]);
        } else  {
            printf("Usage: %s\n", argv[0]);
            printf ("   Open the Flash file system\n");
        }
    }
    return return_code;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_fs_close
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t  shell_fs_close(int32_t argc, char * argv[] )
{
    bool              print_usage, shorthelp = FALSE;
    int32_t               return_code = SHELL_EXIT_SUCCESS;

    print_usage = Shell_check_help_request(argc, argv, &shorthelp );

    if (!print_usage)  {
        if (argc != 1)
        {
            printf("Error, invalid number of parameters\n");
            return_code = SHELL_EXIT_ERROR;
            print_usage=TRUE;
        }
        else
        {
            mfs_nandflash_wl_close();
        }
    }

    if (print_usage)  {
        if (shorthelp)  {
            printf("%s \n", argv[0]);
        } else  {
            printf("Usage: %s\n", argv[0]);
            printf ("   Close the Flash file system\n");
        }
    }
    return return_code;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_nand_erase
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t  shell_nand_erase(int32_t argc, char * argv[] )
{
    bool              print_usage, shorthelp = FALSE;
    int32_t               return_code = SHELL_EXIT_SUCCESS;

    print_usage = Shell_check_help_request(argc, argv, &shorthelp );

    if (!print_usage)  {
        if (argc != 1)
        {
            printf("Error, invalid number of parameters\n");
            return_code = SHELL_EXIT_ERROR;
            print_usage=TRUE;
        }
        else
        {
            nandflash_erase();
        }
    }

    if (print_usage)  {
        if (shorthelp)  {
            printf("%s \n", argv[0]);
        } else  {
            printf("Usage: %s\n", argv[0]);
            printf ("   Erase the Flash file system\n");
        }
    }
    return return_code;

}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_nand_erase_chip
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t  shell_nand_erase_chip(int32_t argc, char * argv[] )
{
    bool     print_usage, shorthelp = FALSE;
    int32_t      return_code = SHELL_EXIT_SUCCESS;

    print_usage = Shell_check_help_request(argc, argv, &shorthelp );

    if (!print_usage)  {
        if (argc != 1)
        {
            printf("Error, invalid number of parameters\n");
            return_code = SHELL_EXIT_ERROR;
            print_usage=TRUE;
        }
        else
        {
            nandflash_erase_chip();
        }
    }

    if (print_usage)  {
        if (shorthelp)  {
            printf("%s \n", argv[0]);
        } else  {
            printf("Usage: %s\n", argv[0]);
            printf("   Erase NAND chip completely\n");
        }
    }
    return return_code;

}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_nand_get_bad_block_table
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t shell_nand_get_bad_block_table(int32_t argc, char * argv[] )
{
    bool     print_usage, shorthelp = FALSE;
    int32_t      return_code = SHELL_EXIT_SUCCESS;

    print_usage = Shell_check_help_request(argc, argv, &shorthelp );

    if (!print_usage)  {
        if (argc != 1)
        {
            printf("Error, invalid number of parameters\n");
            return_code = SHELL_EXIT_ERROR;
            print_usage=TRUE;
        }
        else
        {
            nandflash_get_bad_block_table();
        }
    }

    if (print_usage)  {
        if (shorthelp)  {
            printf("%s \n", argv[0]);
        } else  {
            printf("Usage: %s\n", argv[0]);
            printf("   Erase NAND chip completely\n");
        }
    }
    return return_code;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_nand_repair
* Returned Value : int32_t
* Comments       :
*
*END------------------------------------------------------------------*/
int32_t  shell_nand_repair(int32_t argc, char * argv[] )
{
    bool              print_usage, shorthelp = FALSE;
    int32_t               return_code = SHELL_EXIT_SUCCESS;

    print_usage = Shell_check_help_request(argc, argv, &shorthelp );

    if (!print_usage)  {
        if (argc != 1)
        {
            printf("Error, invalid number of parameters\n");
            return_code = SHELL_EXIT_ERROR;
            print_usage=TRUE;
        }
        else
        {
            nandflash_repair();
        }
    }

    if (print_usage)  {
        if (shorthelp)  {
            printf("%s \n", argv[0]);
        } else  {
            printf("Usage: %s\n", argv[0]);
            printf("    Repair the Flash file system\n");
        }
    }
    return return_code;
}

/* EOF */
