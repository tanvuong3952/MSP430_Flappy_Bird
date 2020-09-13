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
#include "ADC.h"

 /****************************************************************************
* FUNCTIONS
******************************************************************************/

void ADC10_Init(Vref V_tham_chieu)
{
   // Set ENC=0 thi moi chinh sua duoc cac thanh ghi
   ADC10CTL0 &= ~ENC;
   // Cho cho ADC ranh
   while(ADC10CTL1 & ADC10BUSY);
   //ADC10 Control Register 0

   //Noi cac chan voi cong tuong tu
   ADC10AE0=PORT_ADC;
   // Thoi gian lay mau 64xADC10CLK,200ksps,
   ADC10CTL0 = ADC10SHT_3 + ADC10ON;

   //Xoa cai dat cu
   //ADC10CTL0&=~(SREF_7 + REFOUT + REFON + REF2_5V);
   //Chon dien ap tham chieu
   switch(V_tham_chieu)
   {
      case(ON2_5V):
      {
         ADC10CTL0|= SREF_1 + REFON + REF2_5V ;
         break;
      }
      case(ON1_5V):
      {
         ADC10CTL0|= SREF_1 + REFON ;
         break;
      }
      case(VCC):
      {
         ADC10CTL0|= SREF_0;
         break;
      }
      case(VeREF):
      {
         ADC10CTL0|= SREF_2 + REFOUT ;
         break;
      }
   }

   //Bien doi tung kenh
   ADC10CTL1  = CONSEQ_0;
   ADC10DTC0=0;   //Tat DTC
   ADC10DTC1=0;
   // Cho phep chuyen doi
   ADC10CTL0 |= ENC;
   // Bat dau chuyen doi
   ADC10CTL0 |= ADC10SC;
}

unsigned int ADC10_Read_Channel(unsigned char channel)
{
   //Neu kenh doc khac lan cuoi cung doc
   if(channel != Reading_channel)
   {
      //Disable chuyen doi
      ADC10CTL0&=~( ADC10SC + ENC );
      //Thay doi kenh can chuyen doi-chi dung trong che do don kenh
      ADC10CTL1 &= 0x0FFF;
      ADC10CTL1|=(channel<<12);
      Reading_channel = channel;

      ADC10CTL0 &= ~ADC10IFG;      //Tat co ngat
      ADC10CTL0|= (ADC10SC + ENC);
      //__bis_SR_register(CPUOFF + GIE); // Ngat CPU cho den khi chuyen doi xong
      while(!(ADC10CTL0 & ADC10IFG));      //Cho den khi chuyen doi xong
      return ADC10MEM;      //Lay gia tri ADC
   }
   else   //Neu channel giong channel da doc lan truoc
   {
      ADC10CTL0 &= ~ADC10IFG;      //Tat co ngat
      ADC10CTL0|= (ADC10SC + ENC);   //Cho phep chuyen doi
      //__bis_SR_register(CPUOFF  + GIE); // Ngat CPU cho den khi chuyen doi xong
      while(!(ADC10CTL0 & ADC10IFG));      //Cho den khi chuyen doi xong
      return ADC10MEM;      //Lay gia tri ADC
   }
}

// Neu sequence = 0 thi ghi 1 gia tri cua channel vao *pointer
// Neu sequence = 1 thi cac gia tri ghi vao cua cac channel tu channel ->A0
// Quet tu channel A(channel) ->A0 , che 1 chuyen giao 1 block
// Chu y la A(channel) dc ghi vao pointer[0]
void ADC10_DTC(unsigned char channel,unsigned int pointer[], unsigned char  sequence)
{
   //Giam dien tieu thu ,dam bao an toan
   P1DIR &=~PORT_ADC;      //Chon nhap du lieu
   P1OUT &=~PORT_ADC;        //Input
   P1REN &=~PORT_ADC;      //Khong co dien tro keo len

   // Set ENC=0 thi moi chinh sua duoc cac thanh ghi
   ADC10CTL0 &= ~ENC;
   // Cho cho ADC ranh
   while(ADC10CTL1 & ADC10BUSY);
   ADC10AE0=PORT_ADC;
   // Chon che do lay mau lap lai
   ADC10DTC0 = ADC10CT;
   // Chon so lan ghi vao trong 1 vong quet
   // Neu sequence = 0 thi cac gia tri ghi vao cua cung 1 channel
   // Neu sequence = 1 thi cac gia tri ghi vao cua cac channel tu channel ->A0
   ADC10DTC1 = sequence ? (channel+1) : 1;
   // Dia chi bien truyen qua DTC
   ADC10SA = ((unsigned int)pointer);
   // Thoi gian lay mau 1/64 ADC10CLK, Dien ap tham chieu noi 2_5V, Tu dong lay mau
   ADC10CTL0 |= ADC10SHT_3 | SREF_1 | REFON |REF2_5V|MSC|ADC10ON;
   // Chon Channel, ADC10CLK = 1/8 SMCLK , Lap lai lap lai nhieu kenh/1 kenh
   ADC10CTL1 = ((unsigned int)channel<<12) |ADC10DIV_7 | (sequence ? CONSEQ_3 : CONSEQ_2);
   // Cho phep chuyen doi
   ADC10CTL0 |= ENC;
   // Bat dau chuyen doi
   ADC10CTL0 |= ADC10SC;
}

/******************************************************************************
 * END OF TIMER.C
*******************************************************************************/




