/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : Basic_config.H
 *    Description  : This header file includes definitions and prototypes of
 *          timer functions
 *
 *  Tool           : CCS 7.0
 *  Chip           : MSP430G2xxx
 *  History        : 30/5/2017
 *  Version        : 1.0
 *
 *  Author         : Nguyen Khoi Nguyen
 *  Email          : knguyentnh98@gmail.com
 *  Notes          :
 *      To apply these functions, you must include the this header file and add
 *      the TIMER.c file to your project.
 *
******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

 /****************************************************************************
* DEFINITIONS
******************************************************************************/

// These definitions help you to notice the system clocks

#define SMCLK  TASSEL_2
#define ACLK   TASSEL_1
#define dv1    ID_0
#define dv2    ID_1
#define dv4    ID_2
#define dv8    ID_3
#define stop   MC_0
#define up     MC_1
#define conti  MC_2
#define updown MC_3

/****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/

void timer_init(int a, int b, int c, int d);

#endif /* TIMER_H_ */
/******************************************************************************
 * END OF TIMER.H
*******************************************************************************/
