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
* $FileName: main.c$
* $Version : 4.1.0$
* $Date    : Sep-26-2013$
*
* Comments:
*
*   This file contains the source for the rnga example program.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h> 
#include <fio.h>


#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


/* Task IDs */
#define MAIN_TASK 1

extern void main_task(uint32_t);


const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{ 
    /* Task Index,   Function,   Stack,  Priority, Name,     Attributes,          Param, Time Slice */
    { MAIN_TASK,   main_task, 1500,   8,        "Main",  MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/*TASK*-----------------------------------------------------
* 
* Task Name    : main_task
_task
* Comments     :
*    This task show how rnga work(generate randam data)
*
*END*-----------------------------------------------------*/
void main_task
    (
        uint32_t initial_data
    )
{
    uint32_t randout, seed;
    uint32_t value;
    uint16_t i;
    RNGA_STRUCT rnga_handle;
    (void)initial_data; /* disable 'unused variable' warning */

    printf ("\n-------------- RNGA driver example --------------\n\n");
    printf ("This example application demonstrates usage of RNGA driver.\n");
    printf ("It is used to generate random data.\n");
    printf ("Entropy can be inserted into rnga to seed its pseudorandom algorithm.\n");

    _rnga_init(&rnga_handle);

    i = 10;
    while (i--) {
      value = _rnga_get_random_data(&rnga_handle, &randout);
      if (value == RNGA_OK)
        printf("Get N.O %d random data %08x.\n", 10-i, randout);
      else
	  	printf("N.O %d random data generating failed!\n", 10-i);
    }
	
    seed = 0x12;
    _rnga_insert_entropy(&rnga_handle, seed);

    value = _rnga_get_random_data(&rnga_handle, &randout);
    if (value == MQX_OK)
      printf("Get a random data %08x after rnga being seeded.\n", randout);
    else
      printf("Random data generating failed after rnga being seeded!\n");
	
    seed = 0xff;
    _rnga_insert_entropy(&rnga_handle, seed);
	
    value = _rnga_get_random_data(&rnga_handle, &randout);
    if (value == MQX_OK)
      printf("Get another random data %08x after rnga being seeded.\n", randout);
    else
      printf("Random data generating failed after rnga being seeded again!\n");
	
    printf("rnga falls into sleep mode.\n");
    _rnga_set_mode(&rnga_handle, SLEEP_MODE);

    if (_rnga_get_mode(&rnga_handle) == SLEEP_MODE)
      printf("SUCCESS, rnga in sleep mode.\n");
    else
      printf("FAILED, rnga still in normal mode!\n");
    
    value = _rnga_get_random_data(&rnga_handle, &randout);
    if (value == MQX_OK)
      printf("First reading in sleep mode, still get a random data %08x.\n", randout);
    else
      printf("First reading, Random data generating failed!\n");

    value = _rnga_get_random_data(&rnga_handle, &randout);
    if (value == MQX_OK)
      printf("FAILED, second reading should not get random data!\n");
    else
      printf("Second reading in sleep mode, no random data any more.\n");

    printf("rnga quits from sleep mode.\n");
    _rnga_set_mode(&rnga_handle, NORMAL_MODE);

    if (_rnga_get_mode(&rnga_handle) == NORMAL_MODE)
      printf("SUCCESS, rnga in normal mode.\n");
    else
      printf("FAILED, rnga still in sleep mode!\n");

    printf("rnga generates random data after waking up.\n");
    i = 10;
    while (i--) {
      value = _rnga_get_random_data(&rnga_handle, &randout);
      if (value == MQX_OK)
        printf("Get N.O %d random data %08x.\n", 10-i, randout);
      else
        printf("N.O %d random data generating failed!\n", 10-i);
    }
    
     printf("rnga driver test finished.\n");
    _task_block();
}

/* EOF */
