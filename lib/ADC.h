/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : ADC.H
 *    Description  : This header file includes definitions and prototypes of
 *          ADC functions
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
 *      the ADC.c file to your project.
 *
******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/****************************************************************************
* DEFINITIONS
******************************************************************************/

// These definitions help you to notice the system clocks


/****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/

volatile unsigned char PORT_ADC=(BIT0);
//Chu y thach anh ngoai khong mo phong bang protues duoc
typedef enum {    ON2_5V,      //Dien ap tham chieu noi 2.5V
            ON1_5V,      //Dien ap tham chieu noi 2.5V
            VCC,//Dien ap nguon,luu y phai loc nhieu tot cho nguon neu dung che do nay
            VeREF
            } Vref;

/******************************************************************************\
*               Prototype (nguyen mau ham)                             *
\******************************************************************************/
//Doc ket qua o thanh ghi ADC10_MEM
volatile unsigned char Reading_channel=0;
//Kenh dang doc trong lan cuoi cung

//Khoi tao ADC
void ADC10_Init(Vref V_tham_chieu);
//Doc 1 kenh ADC
unsigned int ADC10_Read_Channel(unsigned char channel);   //1->16
//Che do chuyen doi lien tuc
// Neu sequence = 0 thi ghi 1 gia tri cua channel vao *pointer
// Neu sequence = 1 thi cac gia tri ghi vao cua cac channel tu channel ->A0
// Quet tu channel A(channel) ->A0 , che 1 chuyen giao 1 block
// Chu y la A(channel) dc ghi vao pointer[0]
void ADC10_DTC(unsigned char channel,unsigned int pointer[], unsigned char sequence);




#endif /* ADC_H_ */
/******************************************************************************
 * END OF ADC.H
*******************************************************************************/

