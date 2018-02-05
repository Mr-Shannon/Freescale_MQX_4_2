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
* Comments:
*
*   
*
*END************************************************************************/

#ifndef __TIMER_H
#define __TIMER_H

#include <mqx.h>


typedef struct timeval {
  long tv_sec;
  long tv_msec;
} timeval;

struct timer {
    struct timeval begin;
    struct timeval end;
    int (*expired)(struct timer *timer);
};


struct timer *new_timer(time_t sec, time_t msec);

void timeval_diff(struct timeval *tv0, struct timeval *tv1, struct timeval *des);

int update_timer(struct timer *tp, time_t sec, time_t msec);

int64_t timer_remaining(struct timer *tp);

void free_timer(struct timer *tp);

int timer_expired(struct timer *);

#endif
