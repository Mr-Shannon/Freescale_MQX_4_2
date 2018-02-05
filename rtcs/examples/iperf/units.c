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

/*---------------------------------------------------------------
 * Copyright (c) 1999,2000,2001,2002,2003
 * The Board of Trustees of the University of Illinois
 * All Rights Reserved.
 *---------------------------------------------------------------
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software (Iperf) and associated
 * documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 *
 * Redistributions of source code must retain the above
 * copyright notice, this list of conditions and
 * the following disclaimers.
 *
 *
 * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimers in the documentation and/or other materials
 * provided with the distribution.
 *
 *
 * Neither the names of the University of Illinois, NCSA,
 * nor the names of its contributors may be used to endorse
 * or promote products derived from this Software without
 * specific prior written permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE CONTIBUTORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ________________________________________________________________
 * National Laboratory for Applied Network Research
 * National Center for Supercomputing Applications
 * University of Illinois at Urbana-Champaign
 * http://www.ncsa.uiuc.edu
 * ________________________________________________________________
 *
 * stdio.c
 * by Mark Gates <mgates@nlanr.net>
 * and Ajay Tirumalla <tirumala@ncsa.uiuc.edu>
 * -------------------------------------------------------------------
 * input and output numbers, converting with kilo, mega, giga
 * ------------------------------------------------------------------- */


#include <ctype.h>
#include <stdlib.h>

#include "iperf.h"


#ifdef __cplusplus
extern    "C"
{
#endif
  
    const long KILO_UNIT = 1024;
    const long MEGA_UNIT = 1024 * 1024;
    const long GIGA_UNIT = 1024 * 1024 * 1024;

    const long KILO_UNIT_SI = 1000;
    const long MEGA_UNIT_SI = 1000 * 1000;
    const long GIGA_UNIT_SI = 1000 * 1000 * 1000;

/* -------------------------------------------------------------------
 * unit_atof
 *
 * Given a string of form #x where # is a number and x is a format
 * character listed below, this returns the interpreted integer.
 * Gg, Mm, Kk are giga, mega, kilo respectively
 * ------------------------------------------------------------------- */

    double    unit_atof(char *s)
    {
	double    n;
	char      suffix = '\0';


	/* scan the number and any suffices */
	          sscanf(s, "%lf%c", &n, &suffix);

	/* convert according to [Gg Mm Kk] */
	switch    (suffix)
	{
	case 'G':
	    n *= GIGA_UNIT;
	    break;
	case 'M':
	    n *= MEGA_UNIT;
	    break;
	case 'K':
	    n *= KILO_UNIT;
	    break;
	case 'g':
	    n *= GIGA_UNIT_SI;
	    break;
	case 'm':
	    n *= MEGA_UNIT_SI;
	    break;
	case 'k':
	    n *= KILO_UNIT_SI;
	    break;
	default:
	    break;
	}
	          return n;
    }				/* end unit_atof */

/* -------------------------------------------------------------------
 * unit_atoi
 *
 * Given a string of form #x where # is a number and x is a format
 * character listed below, this returns the interpreted integer.
 * Gg, Mm, Kk are giga, mega, kilo respectively
 * ------------------------------------------------------------------- */

    iperf_size_t unit_atoi(char *s)
    {
	double    n;
        char      str[9];
	char      suffix = '\0';


	/* scan the number and any suffices */
	          sscanf(s, "%s", &str);
                  n = atof(str);
                  suffix = str[strlen(str)-1];

	/* convert according to [Gg Mm Kk] */
	switch    (suffix)
	{
	case 'G':
	    n *= GIGA_UNIT;
	    break;
	case 'M':
	    n *= MEGA_UNIT;
	    break;
	case 'K':
	    n *= KILO_UNIT;
	    break;
	case 'g':
	    n *= GIGA_UNIT_SI;
	    break;
	case 'm':
	    n *= MEGA_UNIT_SI;
	    break;
	case 'k':
	    n *= KILO_UNIT_SI;
	    break;
	default:
	    break;
	}
	          return (iperf_size_t) n;
    }				/* end unit_atof */

/* -------------------------------------------------------------------
 * constants for byte_printf
 * ------------------------------------------------------------------- */

/* used as indices into conversion_bytes[], label_byte[], and label_bit[] */
    enum
    {
	UNIT_CONV,
	KILO_CONV,
	MEGA_CONV,
	GIGA_CONV
    };

/* factor to multiply the number by */
    const double conversion_bytes[] =
    {
	1.0,			/* unit */
	1.0 / 1024,		/* kilo */
	1.0 / 1024 / 1024,	/* mega */
	1.0 / 1024 / 1024 / 1024/* giga */
    };

/* factor to multiply the number by for bits*/
    const double conversion_bits[] =
    {
	1.0,			/* unit */
	1.0 / 1000,		/* kilo */
	1.0 / 1000 / 1000,	/* mega */
	1.0 / 1000 / 1000 / 1000/* giga */
    };


/* labels for Byte formats [KMG] */
    const char *label_byte[] =
    {
	"Byte",
	"KByte",
	"MByte",
	"GByte"
    };

/* labels for bit formats [kmg] */
    const char *label_bit[] =
    {
	"bit",
	"Kbit",
	"Mbit",
	"Gbit"
    };

/* -------------------------------------------------------------------
 * unit_snprintf
 *
 * Given a number in bytes and a format, converts the number and
 * prints it out with a bits or bytes label.
 *   B, K, M, G, A for Byte, Kbyte, Mbyte, Gbyte, adaptive byte
 *   b, k, m, g, a for bit,  Kbit,  Mbit,  Gbit,  adaptive bit
 * adaptive picks the "best" one based on the number.
 * s should be at least 11 chars long
 * (4 digits + space + 5 chars max + null)
 * ------------------------------------------------------------------- */

    void      unit_snprintf(char *s, int inLen,
			              double inNum, char inFormat)
    {
	int       conv;
	const char *suffix;
	const char *format;
        int dec;
        int frac;

	/* convert to bits for [bkmga] */
	if        (!isupper((int) inFormat))
	{
	    inNum *= 8;
	}
	switch    (toupper(inFormat))
	{
	case 'B':
	    conv = UNIT_CONV;
	    break;
	case 'K':
	    conv = KILO_CONV;
	    break;
	case 'M':
	    conv = MEGA_CONV;
	    break;
	case 'G':
	    conv = GIGA_CONV;
	    break;

	default:
	case 'A':
	    {
		double    tmpNum = inNum;
		conv = UNIT_CONV;

		if (isupper((int) inFormat))
		{
		    while (tmpNum >= 1024.0 && conv <= GIGA_CONV)
		    {
			tmpNum /= 1024.0;
			conv++;
		    }
		} else
		{
		    while (tmpNum >= 1000.0 && conv <= GIGA_CONV)
		    {
			tmpNum /= 1000.0;
			conv++;
		    }
		}
		break;
	    }
	}

	if (!isupper((int) inFormat))
	{
	    inNum *= conversion_bits[conv];
	    suffix = label_bit[conv];
	} else
	{
	    inNum *= conversion_bytes[conv];
	    suffix = label_byte[conv];
	}
        
        format = "%d.%d %s";/* #.## */

	/* print such that we always fit in 4 places */
	if (inNum < 9.995)
	{			/* 9.995 would be rounded to 10.0 */
            dec = (int)inNum;
            frac = (int)((inNum-dec)*100);           
	} else if (inNum < 99.95)
	{			/* 99.95 would be rounded to 100 */
	    dec = (int)inNum;
            frac = (int)((inNum-dec)*10);           
	} else if (inNum < 999.5)
	{			/* 999.5 would be rounded to 1000 */
	    dec = (int)inNum;
            frac = 0;
	} else
	{			/* 1000-1024 fits in 4 places If not using
				 * Adaptive sizes then this code will not
				 * control spaces */
	    dec = (int)inNum;
            frac = 0;           
	}
	snprintf(s, inLen, format, dec, frac, suffix);
    }				/* end unit_snprintf */

/* -------------------------------------------------------------------
 * double_to_string
 *
 * Converts given double number to string. Used because PC needs to
 * receive jitter in this format: #.###### 
 * ------------------------------------------------------------------- */    
void double_to_string(double n, char *res)
    {
      int temp;
      int exp = 0;
      
      
      while(n<=1000 && n>0)
      {
        n = n*10; 
        exp++;
      }
      
      temp = (int)n;
      
      switch(exp){
      case 0:
        snprintf(res, 9, "%d000.0", temp);
        break;
      case 1:
        snprintf(res, 9, "%d00.0", temp);
        break;
      case 2:
        snprintf(res, 9, "%d0.0", temp);
        break;
      case 3:
        snprintf(res, 9, "%d.0", temp);
        break;
      case 4:
        snprintf(res, 9, "0.%d", temp);
        break;
      case 5:
        snprintf(res, 9, "0.0%d", temp);
        break;
      case 6:
        snprintf(res, 9, "0.00%d", temp);
        break;
      case 7:
        snprintf(res, 9, "0.000%d", temp);
        break;      
      }             
    }    
    
#ifdef __cplusplus
}				/* end extern "C" */

#endif
