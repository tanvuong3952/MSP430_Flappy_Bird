/******************************************************************************
 *
 ******************************************************************************
 *
 * LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : GPIO_CLOCK.C
 *    Description  : This file describes some basic configuration functions
 *                   such as Initialization clock or delay
 *
 *  Tool           : CCS 7.0
 *  Chip           : MSP430G2xxx
 *  History        : 28/5/2017
 *  Version        : 1
 *
 *  Author         : Nguyen Khoi Nguyen (1612287@hcmut.edu.vn)
 *  Notes          :
 *      To apply these functions, you must include the header file GPIO_CLOCK.h
 *      and add this code file to your project.
 *
******************************************************************************/

 /****************************************************************************
 * IMPORT
******************************************************************************/
#include <msp430.h>
#include "GPIO_CLOCK.h"

/****************************************************************************
* FUNCTIONS
******************************************************************************/

//*****************************************************************************
// Stop Watch-dog Timer
//*****************************************************************************
void Config_stop_WDT(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer
    // WDTCTL WatchdogTimer+Register
        // WDTPW   = Watchdog timer + password.
            //Must be written as 05Ah, or a PUC (Power-Up Clear) is generated
        // WDTHOLD = Watchdog timer + hold.This bit stops the watchdog timer+
}

//*****************************************************************************
// GPIO Configurations
//*****************************************************************************
void GPIO_Config (int a, int b,int c,int d) // PortX, INP/OUTP, UP/DOWN, BITX
{
    if(a==0x01)                      // Port1 configurations
    {
        P1SEL=0;                     // GPIO mode
        P1SEL2=0;
        if(b==OUTP)                  // OUTPUT configurations
        {
            P1DIR |= d;
        }
        if(b==INP)                   // INPUT configurations
        {
            P1DIR &= ~d;
            P1REN |= d;              // Enable resistor pull
            if(c==UP)                // Resistor pull up
            {
                P1OUT |= d;
            }
            if(c==DOWN)               // Resistor pull down
            {
                P1OUT &= ~d;
            }
        }
    }
    if(a==0x01)                       // Port2 configurations
    {
        P2SEL=0;                      // GPIO mode
        P2SEL2=0;
        if(b==OUTP)                   // OUTPUT configurations
        {
            P2DIR |= d;
        }
        if(b==INP)                    // INPUT configurations
        {
            P2DIR &= ~d;
            P2REN |= d;               // Enable resistor pull
            if(c==UP)                 // Resistor pull up
            {
                P2OUT |= d;
            }
            if(c==DOWN)               // Resistor pull down
            {
                P2OUT &= ~d;
            }
        }
    }
}

//*****************************************************************************
// Interrupt Configurations
//*****************************************************************************

void Interrupt_Config (int a, int b, int c) // PortX, BITx, Rising/Falling Edge
{
    if(a==0x01)                           //Port1
    {
        P1IE  |= b;
        if(c==FALL)                       //Falling Edge
        {
            P1IES |= b;                   //Falling Edge
            P1IFG &= ~b;                  //Clear Interrupt Flag
            __bis_SR_register(GIE);       //Enable globe interrupt
        }
        if(c==RISE)
        {
            P1IES &= b;                   //Rising Edge
            P1IFG &= ~b;                  //Clear Interrupt Flag
            __bis_SR_register(GIE);       //Enable globe interrupt
        }
    }
    if(a==0x010)                          //Port2
    {
        P2IE  |= b;
        if(c==FALL)                       //Falling Edge
        {
            P2IES |= b;                   //Falling Edge
            P2IFG &= ~b;                  //Clear Interrupt Flag
            __bis_SR_register(GIE);       //Enable globe interrupt
        }
        if(c==RISE)
        {
            P2IES &= b;                   //Rising Edge
            P2IFG &= ~b;                  //Clear Interrupt Flag
            __bis_SR_register(GIE);       //Enable globe interrupt
        }
    }

}

//*****************************************************************************
// Clocks Configurations
//*****************************************************************************

void Clock_config_HF (int a)      // Frequent CALBC1_1MHZ - CALBC1_8MHZ - CALBC1_12MHZ - CALBC1_16MHZ
{

    if  (a == 0xff){    //if calibration constant erased
        while(1);                 //do not load, trap cpu
        }
    DCOCTL  = 0;                  // High frequent Clock - DCO
    BCSCTL1 = a;                  // set range
    DCOCTL  = a;                  // set DCO step + moudulation
}

void Clock_config_LF (int a, int b) // CRYSTAL32768-RESERVE-VLOCLK-DECS (digital external clock source), VLO - DEC
{
    BCSCTL3 |= XT2S_0 + a;         // Set range 0.4 - 1MHz + Choose clock type
    IFG1 &= ~OFIFG;                // clear flag
    BCSCTL2 |= b;                  // choose clock for cpu
}                                  // VLO = 12000 HZ

