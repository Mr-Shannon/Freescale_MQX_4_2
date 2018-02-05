/*HEADER**********************************************************************
*
* Copyright (c) 2015, Freescale Semiconductor, Inc.
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
*
*
*END************************************************************************/

#include "itimer.h"
#include "iperf_error.h"
#include "iperf_util.h"


void
timeval_diff(struct timeval * tv0, struct timeval * tv1, struct timeval * des)
{
    long time1, time2;
    
    time1 = tv1->tv_sec - tv0->tv_sec;
    time2 = tv1->tv_msec - tv0->tv_msec;
    
    if(time1<0){
      time1 = -time1;   
    }
    
    if(time2<0){
      time2 = -time2;    
    }
    
    des->tv_sec = time1;
    des->tv_msec = time2;
}

int
timer_expired(struct timer * tp)
{
    if (tp == NULL)
        return 0;

    struct timeval now;
    int64_t end = 0, current = 0;

    gettimeofday(&now, NULL);

    end += tp->end.tv_sec * 1000;
    end += tp->end.tv_msec;

    current += now.tv_sec * 1000;
    current += now.tv_msec;

    return current >= end;
}

int
update_timer(struct timer * tp, time_t sec, time_t msec)
{
    if (gettimeofday(&tp->begin, NULL) < 0) {
        i_errno = IEUPDATETIMER;
        return (-1);
    }

    tp->end.tv_sec = tp->begin.tv_sec + (time_t) sec;
    tp->end.tv_msec = tp->begin.tv_msec + (time_t) msec;

    tp->expired = timer_expired;
    return (0);
}

struct timer *
new_timer(time_t sec, time_t msec)
{
    struct timer *tp = NULL;
    tp = (struct timer *) _mem_alloc_zero(sizeof(struct timer));
    if (tp == NULL) {
        i_errno = IENEWTIMER;
        return (NULL);
    }

    if (gettimeofday(&tp->begin, NULL) < 0) {
        i_errno = IENEWTIMER;
        return (NULL);
    }

    tp->end.tv_sec = tp->begin.tv_sec + (time_t) sec;
    tp->end.tv_msec = tp->begin.tv_msec + (time_t) msec;

    tp->expired = timer_expired;

    return tp;
}

void
free_timer(struct timer * tp)
{
    _mem_free(tp);
}

int64_t
timer_remaining(struct timer * tp)
{
    struct timeval now;
    long int  end_time = 0, current_time = 0, diff = 0;

    gettimeofday(&now, NULL);

    end_time += tp->end.tv_sec * 1000;
    end_time += tp->end.tv_msec;

    current_time += now.tv_sec * 1000;
    current_time += now.tv_msec;

    diff = end_time - current_time;
    if (diff > 0)
        return diff;
    else
        return 0;
}
