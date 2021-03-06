
#include "SPI.h"

/*
 * SPI.c
 *
 *  Created on: Nov 22, 2012
 *      Author: TranHai PIF_member
 */
void Config_SPI_A(void) // Config module SPI USCIA
{
	//Config PIN
	P1SEL |= BIT1 + BIT2 + BIT4;
	P1SEL2 |= BIT1 + BIT2 + BIT4;
	//Config SPI
	UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  
		/*	UCSYNC     Sync-Mode
		 *  UCCKPH     Mode: Clock Phase
		 *	UCCKPL     Mode: Clock Polarity
		 *	UCMST      Mode: Master Select
		 *  UC7BIT     Mode: Data Bits  0:8-bits / 1:7-bits
		 *  UCMSB	   Mode: MSB first  0:LSB / 1:MSB
		 *	UCMST      Mode: Master Select
		 *  UCMODE_0   Mode: USCI Mode: 0; 3pin SPI default
		 *	UCMODE_1    Mode: USCI Mode: 1; 4pin SPI
		 *	UCMODE_2    Mode: USCI Mode: 2; 4pin SPI
		 */
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
		/*UCSSEL_1 ACLK
		 *UCSSEL_2 SMCLK
		 *UCSSEL_3 SMCLK
		 */
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	UCA0BR0 |= 0x02;                          // f/2    for your choice
	UCA0BR1 = 0;                              //

	UCA0MCTL = 0;                             // No modulation

//	IE2 |= UCA0TXIE;                          // Enable USCI0 RX interrupt
	__delay_cycles(75);                       // Wait for slave to initialize
}


void Config_SPI_B(void) // Config module SPI USCIB
{
	//Config PIN
	P1SEL |= BIT5 + BIT6 + BIT7;
	P1SEL2 |= BIT5 + BIT6 + BIT7;
	//Config SPI
	UCB0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  
	/*	UCSYNC     Sync-Mode
	 *  UCCKPH     Mode: Clock Phase
	 *	UCCKPL     Mode: Clock Polarity
	 *	UCMST      Mode: Master Select
	 *  UC7BIT     Mode: Data Bits  0:8-bits / 1:7-bits
	 *  UCMSB	   Mode: MSB first  0:LSB / 1:MSB
	 *	UCMST      Mode: Master Select
	 *  UCMODE_0   Mode: USCI Mode: 0; 3pin SPI default
	 *	UCMODE_1    Mode: USCI Mode: 1; 4pin SPI
	 *	UCMODE_2    Mode: USCI Mode: 2; 4pin SPI
	 */
	UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	/*UCSSEL_1 ACLK
	 *UCSSEL_2 SMCLK
	 *UCSSEL_3 SMCLK
	 */
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	UCB0BR0 |= 0x02;                         // f/2   for your choice
	UCB0BR1 = 0;                              
//	IE2 |= UCA0TXIE;                         // Enable USCI0 RX interrupt
	__delay_cycles(75);                      // Wait for slave to initialize
}


void Send_byte_A(int data, int time_ms)     // Send 1 byte for module SPI USCIA
{
	  int i_delay;
	  while (!(IFG2 & UCA0TXIFG));          // USCI_A0 TX buffer ready?
	  UCA0TXBUF = data;                     // Send next value
	  for (i_delay = 0; i_delay<time_ms; i_delay++ )
	  {
		_delay_cycles(1000);
	  }
}

void Send_byte_B(int data, int time_ms)     // Send 1 byte for module SPI USCIB
{
	  int i_delay;
	  while (!(IFG2 & UCA0TXIFG));          // USCI_A0 TX buffer ready?
	  UCB0TXBUF = data;                     // Send next value
	  for (i_delay = 0; i_delay<time_ms; i_delay++ )
	  {
		_delay_cycles(1000);
	  }
}

void Config_93LC46B(void)
{

	char i;
	P1DIR |= BIT6 + BIT2 + BIT4;
	P1DIR &= ~BIT1;
	
	P1OUT &= ~0x40; //bit 6 chip select 
	P1OUT &= ~0x04; //bit 2 data in
	P1OUT &= ~0x10; //bit 4 clock
	
	P1OUT |= 0x40; //bit 6 on
	
	for(i=0; i<9; i++)
	{
		if(i==0 || i== 3 || i==4)
		{
			P1OUT |= 0x04;
		}
		else
		{
			P1OUT &= ~0x04;
		}
		P1OUT |= 0x10;
		__delay_cycles(75);
		P1OUT &= ~0x10;
		__delay_cycles(75);
	}
	P1OUT &= ~0x40; //bit 6 chip select off
	P1OUT &= ~0x04; //bit 2 data in off
}

void write_93LC46B(char address, long data)
{
	long cmd[5];
	int j = 0;
	int bit = 0;
	long point = 0;
	// address, and 16 bits of data. This is 25 bits, total.
	cmd[4] = (data<<7)&0x007FFF80;
	cmd[1] = address;
	cmd[1] = (cmd[1]<<23)&0x1F800000;
	cmd[2] = 0x05; 
	cmd[3] = (0xA0000000)|cmd[1]|cmd[4];
	point = 0x80000000;
	P1OUT |= 0x40; //bit 6 chip select on
	for(j =0 ; j<25 ; j++)
	{

		bit = ((cmd[3]&point)>>31)&0x00000001;
		cmd[3] = cmd[3]<<1;
		if( bit == 0x0001)
		{ 
			P1OUT |= 0x04; //bit 2 data in off
		}
		else
		{
			P1OUT &= ~0x04; //bit 2 data in off
		}
		P1OUT |= 0x10;
		__delay_cycles(75);
		P1OUT &= ~0x10;
		__delay_cycles(75);

	}
	P1OUT &= ~0x40; //bit 6 chip select off
	P1OUT &= ~0x04; //bit 2 data in on
	__delay_cycles(11000);
}


long read_93LC46B(char address)
{
	long cmd[5];
	int j = 0;
	int bit = 0;
	long point = 0;
	long data;
	// address, and 16 bits of data. This is 25 bits, total.
	cmd[4] = 0;
	cmd[1] = address;
	cmd[1] = (cmd[1]<<23)&0x1F800000;
	cmd[2] = 0; 
	cmd[3] = (0xC0000000)|cmd[1];
	point = 0x80000000;
	P1OUT |= 0x40; //bit 6 chip select on
	for(j =0 ; j<25 ; j++)
	{

		bit = ((cmd[3]&point)>>31)&0x00000001;
		cmd[3] = cmd[3]<<1;
		if( bit == 0x0001)
		{
			P1OUT |= 0x04; //bit 2 data in on
		}
		else
		{
			P1OUT &= ~0x04; //bit 2 data in off
		}
		if(j > 8)
		{
			if ((0x02 & P1IN))
			{
				data = data|0x00000001;
				data = data<<1;
			}
			else
			{
				data = data&(~0x00000001);
				data = data<<1;
			}
		}
		P1OUT |= 0x10;
		__delay_cycles(75);
		P1OUT &= ~0x10;
		__delay_cycles(75);

	}
	P1OUT &= ~0x40; //bit 6 chip select off
	return(data);
}
