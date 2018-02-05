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
* $FileName: msd_mfs_demo.c$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file implements MAS FAT demo application.
*
*END************************************************************************/
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host_stack_interface.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#include <lwevent.h>
#include <bsp.h>
#include <mfs.h>
#include <part_mgr.h>
#include <usbmfs.h>
#include "mfs_usb.h"
#include "usb_file.h"

#include "usb_host_hub_sm.h"
#include "usb_host_msd_bo.h"
#include "usb_host_msd_ufi.h"

volatile device_struct_t   g_mass_device[USBCFG_MAX_INSTANCE] = { 0 };   /* mass storage device struct */
volatile uint8_t           g_mass_device_new_index = 0;

/* Store mounting point used. A: is the first one, bit #0 assigned, Z: is the last one, bit #25 assigned */
uint32_t                   g_fs_mountp = 0;

char                       g_drive[3];
char                       g_pm[8] = "PM_C1:";
char                       g_block[8] = "USB:";

#if THROUGHPUT_TEST_ENABLE

#ifndef  DEMCR
#define  DEMCR       *((volatile uint32_t *)0xE000EDFC)
#endif
#ifndef  DWT_CR
#define  DWT_CR      *((volatile uint32_t *)0xE0001000)                   /* Data Watchpoint and Trace (DWT) Control Register     */                
#endif
#ifndef  DWT_CYCCNT
#define  DWT_CYCCNT  *((volatile uint32_t *)0xE0001004)                   /* Data Watchpoint and Trace (DWT) Cycle Count Register */
#endif
#define  DEMCR_TRCENA                     (1 << 24)
#define  DWT_CR_CYCCNTENA                 (1 <<  0)

#define EACH_TRANSFOR_SECTORS                   (128)
uint32_t raw_size_arr[] = {100, 100}; /* 100M, unit M */
uint8_t test_buffer[EACH_TRANSFOR_SECTORS * 512];
uint32_t g_cpu_core_clk_khz = 120000;
void mfs_throughput_test(MQX_FILE_PTR fs_ptr)
{
    int32_t error = 0;
    MQX_FILE_PTR fd = NULL;
    uint32_t time = 0;
    uint32_t time_count = 0;
    uint64_t time_sum = 0;
    uint32_t i = 0, j = 0;
    uint64_t temp;
    int32_t size;
    uint8_t TEST_TIME = 0;
    uint32_t raw_size = 0;
    
    /* get core clock */
    extern const TCpuClockConfiguration PE_CpuClockConfigurations[];
    g_cpu_core_clk_khz = PE_CpuClockConfigurations[Cpu_GetClockConfiguration()].cpu_core_clk_hz / 1000;
    
    DEMCR |= DEMCR_TRCENA; /* enable DWT module counter */
    TEST_TIME = sizeof(raw_size_arr) / sizeof(uint32_t);
    
    /* init test buffer */
    for (int i = 0; i < EACH_TRANSFOR_SECTORS * 512; ++i)
        test_buffer[i] = i;

    USB_PRINTF("******************************************************************************\n");
    USB_PRINTF("*                   file.dat for write and read speed                        *\n");
    USB_PRINTF("******************************************************************************\n");
    for (time = 1; time <= TEST_TIME; ++time)
    {
        raw_size = raw_size_arr[time - 1];
        fd = fopen("C:\\file.dat", "w+");
        if(!fd)
        {
            USB_PRINTF("open fail\n");
            goto done;
        }
        /* write speed test. */
        USB_PRINTF("***************************%d write %dM test**********************************\n", time, raw_size);
        time_sum = 0;
        for (uint32_t i = 0;i < raw_size * 2048; i += EACH_TRANSFOR_SECTORS)
        {
            DWT_CYCCNT = (uint32_t)0u;
            DWT_CR |= DWT_CR_CYCCNTENA;
            size = write(fd, test_buffer, EACH_TRANSFOR_SECTORS << 9);
            if(size != (EACH_TRANSFOR_SECTORS << 9))
            {
                fflush(fd);
                fclose(fd);
                USB_PRINTF("write error\n");
                goto done;
            }
            time_sum += (uint64_t)DWT_CYCCNT;
            DWT_CR &= ~((uint32_t)DWT_CR_CYCCNTENA);
        }
        time_sum = time_sum / (g_cpu_core_clk_khz);
        temp = (uint64_t)((uint64_t)512*(uint64_t)(raw_size * 2048));
        temp = temp * 1000 / (uint64_t)time_sum;
        USB_PRINTF("write test results: time = %dms  speed = %dK/s\n", (uint32_t)time_sum, (uint32_t)(temp / 1024));
        
        /* read speed test. */
        USB_PRINTF("***************************%d read %dM test***********************************\n", time, raw_size);
        error = fseek(fd, 0, IO_SEEK_SET);
        if (error)
        {
            fflush(fd);
            fclose(fd);
            USB_PRINTF("fseek error\n");
            goto done;
        }
        time_sum = 0;
        for (i = 0; i < raw_size * 2048; i += EACH_TRANSFOR_SECTORS)
        {
            DWT_CYCCNT = (uint32_t)0u;
            DWT_CR |= DWT_CR_CYCCNTENA;
            size = read(fd, test_buffer, EACH_TRANSFOR_SECTORS << 9);
            if(size != (EACH_TRANSFOR_SECTORS << 9))
            {
                fflush(fd);
                fclose(fd);
                USB_PRINTF("read error or read less\n");
                goto done;
            }
            time_sum += (uint64_t)DWT_CYCCNT;
            DWT_CR &= ~((uint32_t)DWT_CR_CYCCNTENA);
        }
        time_sum = time_sum / (g_cpu_core_clk_khz);
        temp = (uint64_t)((uint64_t)512*(uint64_t)(raw_size * 2048));
        temp = temp * 1000 / (uint64_t)time_sum;
        USB_PRINTF("read test results: time = %dms  speed = %dK/s\n", (uint32_t)time_sum, (uint32_t)(temp / 1024));
        fflush(fd);
        error = fclose(fd);
        if (error)
        {
            USB_PRINTF("close error\n");
            goto done;
        }
    }

done:
    USB_PRINTF("******************************************************************************\n");
    USB_PRINTF("*                                TEST DONE                                   *\n");
    USB_PRINTF("******************************************************************************\n");
    return;
}
#endif

int mfs_mount(uint8_t device_no)
{
	/* get free mountpoint as a string like "c:" */
	for (g_drive[0] = 'C'; g_drive[0] <= 'Z'; g_drive[0]++)
		if (!(g_fs_mountp & (1 << (g_drive[0] - 'A'))))
			break;
	g_drive[1] = ':';
	g_drive[2] = 0;
	
	g_pm[3] = g_drive[0];
	
	/* Install the file system, use device->ccs as a handle */
	g_mass_device[device_no].usb_mfs_handle = usb_filesystem_install( (void*)g_mass_device[device_no].CLASS_HANDLE, g_block, g_pm, g_drive );
	
	if (NULL != g_mass_device[device_no].usb_mfs_handle)
	{
		g_mass_device[device_no].mount = g_drive[0];		
		/* Mark file system as mounted */
		g_fs_mountp |= 1 << (g_mass_device[device_no].mount - 'A');
                
                #if THROUGHPUT_TEST_ENABLE
                mfs_throughput_test(((usb_filesystem_struct_t*)(g_mass_device[device_no].usb_mfs_handle))->FS_FD_PTR);
                #endif
		
		return 0;
	}
	
	return -1;
}

int mfs_unmount(uint8_t device_no)
{
    if (g_mass_device[device_no].mount >= 'A' && g_mass_device[device_no].mount <= 'Z') 
    {
        /* Remove the file system  */
        usb_filesystem_uninstall(g_mass_device[device_no].usb_mfs_handle);
        /* Mark file system as unmounted */
        g_fs_mountp &= ~(1 << (g_mass_device[device_no].mount - 'A'));
        return 0;
    }
    return -1;
}

#endif /* (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX) */

/* EOF */
