/*
 * sys_init.c
 *
 *  Created on: Oct 15, 2018
 *      Author: ASUS
 */
#include <msp430.h>
#include <math.h>
#include "flappy.h"

unsigned int t1=0, t2=0, distance=0, first_pulse=0;

uint8_t display_map[8];
int star,n,i,Location,min,max,k,a,b,collisiontest;
uint16_t adc_result;
uint16_t volt;
uint8_t counter;
uint8_t bird[8] = {0b11111111,0b11101111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111};
uint8_t birdposition = 0b11111111;
uint8_t birdposition1 = 0b11111111;

void sys_init(void)
{
    Config_stop_WDT();

    DCOCTL = 0;
    BCSCTL1 = CALBC1_16MHZ;          // set range
    DCOCTL = CALDCO_16MHZ;           // set DCO step + moudulation

    Config_SPI_A();

    P1SEL &= ~BIT3;
    P1SEL2 &= ~BIT3;
    P1DIR |= BIT3;                  //LAT pin
    P1OUT &= ~BIT3;
    P2SEL &=~(BTN2_1 + BTN2_2 +BTN2_3);
    P2SEL2 &= ~(BTN2_1 + BTN2_2 +BTN2_3);
    P2DIR &= ~(BTN2_1 + BTN2_2 +BTN2_3);
    P2IE  |= (BTN2_1 + BTN2_2 +BTN2_3);  // khai bao interrupt
    P2IES |= (BTN2_1 + BTN2_2 +BTN2_3);  // bat canh xuong
    P2IFG &= ~(BTN2_1 + BTN2_2 +BTN2_3); // keo co ve lai bang

    P2DIR |= trigger;      // trigger ouput
    P2SEL |= echo;         //connect P2.0 (echo) to CCI0A (capture/compare input )

    _BIS_SR(GIE);          //ngat toan cuc
}

void begin(volatile sys_params_t *params)
{
    for(i=0;i<8;i++)
    {
        Send_byte_A(params->led_control[i],1);
        Send_byte_A(params->begin_img[i],1);
        Send_byte_A(params->off_img[i],1);
        P1OUT |= BIT3;
        __delay_cycles(1000);
        P1OUT &= ~BIT3;
    }
}

void end(volatile sys_params_t *params)
{
    for(i=0;i<8;i++)
    {
        Send_byte_A(params->led_control[i],1);
        Send_byte_A(params->end_img[i],1);
        Send_byte_A(params->off_img[i],1);
        P1OUT |= BIT3;
        __delay_cycles(100);
        P1OUT &= ~BIT3;
    }
}

void play(volatile sys_params_t *params)
{
	uint8_t point=0;
	collisiontest=0;
    for(star=0;star<32;star++)
    {
    	point += 1;
    	if(collisiontest==1)
    		break;

    	else
    	{
    	   for(k=star;k<(star+8);k++)
   			   display_map[k-star] = params->game_map[k];

    	   position(display_map);

    	   for (n=0;n<500;n++)
    	   {
   			   for(i=0;i<8;i++)
   			   {
   				   Send_byte_A(params->led_control[i],1);
   				   Send_byte_A(bird[i],1);
   				   Send_byte_A(display_map[i],1);
   				   P1OUT |= BIT3;
   				   __delay_cycles(100);
   				   P1OUT &= ~BIT3;
   			   }
   			   __delay_cycles(1);
   		   }
    	  }
    	if(point >20)
    		break;
    }
    if (point>20)
    	sys_params.iState=0;
    else
    	sys_params.iState=2;
}

void position(uint8_t display_map[8])
{
	if(sys_params.jump > 0)
	{
		birdposition = bird[1];
//		birdposition = birdposition >> 1;
//		birdposition |= 0b10000000;
//		birdposition = birdposition << 1;
//		birdposition|= 0b00000001;
		birdposition = birdposition << 1;
		birdposition|= 0b00000001;
		bird[1] = birdposition;
		sys_params.jump = sys_params.jump - 1;
	}
	else
	{
		birdposition = bird[1];
		birdposition = birdposition >> 1;
		birdposition |= 0b10000000;
		bird[1] = birdposition;
		if (sys_params.jump != 0)
			sys_params.jump = sys_params.jump - 1;
	}
	birdposition1 = bird[1];
	for(i=0; i<8; i++)
	{
		if((birdposition1 & 0b00000001)==0)
		{
			a = 0;
			counter=i;
		}
		birdposition1 = birdposition1 >> 1;
		birdposition|= 0b10000000;
	}

	birdposition1 = display_map[1];
	birdposition1 = birdposition1 >> counter;

	if ((birdposition1 & 0b00000001)==0)
		b = 0;
	else
		b = 1;

    switch(counter)
        {
        case 0:
        	collisiontest = 1;
        case 7:
        	collisiontest = 1;
        }
	if(a==b)
	{
		collisiontest = 1;
	}
}
void init_timer(void){
   TA1CTL = TASSEL_2 + MC_2 ;                       // continuos mode, 0 --> FFFF
   TA1CCTL0 = CM_3 + CAP + CCIS_0 + SCS+ CCIE;      // falling edge & raising edge, capture mode, capture/compare interrupt enable
   TA1CCTL0 &= ~ CCIFG;
}

void image_copy(uint8_t *a, uint8_t *b)
{
    int i;
    for(i=0; i < 8;i++)
        a[i] = b[i];
}
void map_copy(uint8_t *a, uint8_t *b)
{
    int i;
    for(i=0; i < 32;i++)
        a[i] = b[i];
}

#pragma vector = PORT2_VECTOR// nho
__interrupt void BUTTON_Interrupt_Handle(void)// nho
{
    if ((P2IFG & BTN_1) == BTN_1)
    {
        sys_params.iState++;
        P2IFG &= ~BTN_1;
    }
    if ((P2IFG & BTN_2) == BTN_2)
    {
        sys_params.jump = 1;
        P2IFG &= ~BTN_2;
    }
    P2IFG = 0;

}
