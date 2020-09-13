
/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : Basic_config.H
 *    Description  : This header file includes definitions and prototypes of
 *          basic configuration functions such as Initialization clock or delay
 *
 *  Tool           : CCS 5.1
 *  Chip           : MSP430G2xxx
 *  History        : 28/5/2017
 *  Version        : 1
 *
 *  Author         : Nguyen Khoi Nguyen (1612287@hcmut.edu.vn)
 *  Notes          :
 *      To apply these functions, you must include the this header file and add
 *      the Basic_config.c file to your project.
 *
 *      To use delay functions, pay attention to "#define MCLK"
******************************************************************************/
#ifndef GPIO_CLOCK_H_
#define GPIO_CLOCK_H_

/****************************************************************************
* DEFINITIONS
******************************************************************************/
#define P1    0x01
#define P2    0x10
#define INP   0x00
#define OUTP  0x01
#define UP    0x01
#define DOWN  0x00
#define RISE  0x01
#define FALL  0x00
#define CRYSTAL32768 LFXT1S_0
#define RESERVE      LFXT1S_1
#define VLOCLK       LFXT1S_2
#define DECS         LFXT1S_3
#define VLO          SELM_3
#define DEC          SELM_2

/****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/
void Interrupt_Config (int a, int b, int c);
void GPIO_Config (int a, int b,int c,int d);
void Config_stop_WDT(void);
void Clock_config_HF (int a);
void Clock_config_LF (int a, int b);

#endif /* GPIO_CLOCK_H_ */
/******************************************************************************
 * END OF GPIO_CLOCK.H
*******************************************************************************/
















