/******************************************************************************
 *
 * LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : Timer.C
 *    Description  : This file describes some timer functions
 *
 *  Tool           : CCS 7.0
 *  Chip           : MSP430G2xxx
 *  History        : 30/05/2017
 *  Version        : 1.0
 *
 *  Author         : Nguyen Khoi Nguyen
 *  Email          : knguyentnh98@gmail.com
 *  Notes          :
 *      To apply these functions, you must include the header file Timer.h
 *      and add this code file to your project.
 *
******************************************************************************/

 /****************************************************************************
 * IMPORT
******************************************************************************/

#include <msp430.h>
#include "TIMER.h"

 /****************************************************************************
* FUNCTIONS
******************************************************************************/

void timer_init(int a, int b, int c, int d) // SMCLK/ACLK, stop/up/conti/updown, dv1/dv2/dv4/dv8, 1(enable interrupt)
{
   /*****************INITIATE TIMER A0*****************/
   TA0CCR0=20000;
      //TA0CCR1=200;
      //TA0CCR2=1600;

      TA0CTL |= a + b + c +TAIE + TAIFG;
         /* -TASSEL_x : select clock source
                  0: TACLK
                  1: ACLK
                  2: SMCLK
                  3: INCLK
            -ID_x : input divider
                  0: /1
                  1: /2
                  2: /4
                  3: /8
            -MC_x : mode control
                  0: stop mode: timer is halted
                  1: up mode: 0 -> TACCR0
                  2: continuous mode: 0 -> 0FFFFh
                  3: up/down mode: 0 -> TACCR0 -> 0
            -TAIE : timer interupt enable
            -TAIFG : interupt pending
            */
      if(c==1)
      {
          TA0CCTL1 |= CCIE+CCIFG; //interupt enable, interupt pending
          TA0CCTL2 |= CCIE+CCIFG;
      }
}

/******************************************************************************
 * END OF TIMER.C
*******************************************************************************/

