/*
 * ports_init.c
 *
 *  Created on: May 26, 2021
 *      Author: ehab
 */
//#include <TM4C123.h>
#include "ports_init.h"
//#include "C:\Keil\EE319Kware\inc/tm4c123gh6pm.h"
//PORTA
/*
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *) 0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *) 0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *) 0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *) 0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *) 0x4000451C))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *) 0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *) 0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *) 0x4000452C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *) 0x40004520))
//PORTB
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *) 0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *) 0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *) 0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *) 0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *) 0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *) 0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *) 0x40005528))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *) 0x40005520))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *) 0x4000552C))
//PORTD
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *) 0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *) 0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *) 0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *) 0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *) 0x4000751C))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *) 0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *) 0x40007528))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *) 0x40007520))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *) 0x4000752C))
//PORTE
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *) 0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *) 0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *) 0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *) 0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *) 0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *) 0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *) 0x40024528))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *) 0x40024520))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *) 0x4002452C))
//PORTF
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *) 0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *) 0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *) 0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *) 0x40025528))
<<<<<<< HEAD

//=======
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *) 0x40025520))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *) 0x4002552C))

>>>>>>> 0f9a515d5f2e8b5c88fa5dc4047a65d3d5fefc55
*/

void portA_init(void)
{

    SYSCTL_RCGCGPIO_R |= 0x01;  //enable port A
    while((SYSCTL_PRGPIO_R& 0x01)==0); //wait until port A activation
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R |=0xFC;   // control reg
    GPIO_PORTA_AFSEL_R &= ~0xE0;  //0x03;  // input &output
    GPIO_PORTA_PCTL_R &= ~0xE0;   //0x03;  //no alternative function
    GPIO_PORTA_AMSEL_R &= ~0xE0;    //0x03; // no analog function
    GPIO_PORTA_DIR_R |= 0xFC; //output
    GPIO_PORTA_DEN_R |=0xFC;   //Digital
    GPIO_PORTA_PUR_R &=0x03;  //PULL UP RESISTOR
}


void portB_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x00000002;  //enable port B
    while((SYSCTL_PRGPIO_R& 0x00000002)==0); //wait until port A activation
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |=0xFF;   // control reg
    GPIO_PORTB_AFSEL_R =0;
    GPIO_PORTB_PCTL_R =0;  //no alternative function
    GPIO_PORTB_AMSEL_R =0; // no analog function
    GPIO_PORTB_DIR_R |= 0xFF; //output
    GPIO_PORTB_DEN_R |=0xFF;   //Digital
    GPIO_PORTB_PUR_R =0;  //PULL UP RESISTOR
}

void portD_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x08;  //enable port D
    while((SYSCTL_PRGPIO_R& 0x08)==0); //wait until port A activation
	
		GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R |=0xFC;   // control reg
    GPIO_PORTD_AFSEL_R &= ~0xE0;  //0x03;  // input &output
    GPIO_PORTD_PCTL_R &= ~0xE0;   //0x03;  //no alternative function
    GPIO_PORTD_AMSEL_R &= ~0xE0;    //0x03; // no analog function
    GPIO_PORTD_DIR_R |=0xFC; //output
    GPIO_PORTD_DEN_R |=0xFC;   //Digital
    GPIO_PORTD_PUR_R &=0x03;  //PULL UP RESISTOR
	/*
		
	  GPIO_PORTD_LOCK_R = 0x4C4F434B;

    GPIO_PORTD_CR_R |=0x3C;   // control reg
    GPIO_PORTD_AFSEL_R &=~0x0C;
    GPIO_PORTD_PCTL_R = ~0x00;  //clear
    GPIO_PORTD_AMSEL_R &=~0x30; // no analog function
    GPIO_PORTD_DIR_R |= 0x3F; // set pin 2 as input
    GPIO_PORTD_DEN_R |=0x3F;   //enable bins
    GPIO_PORTD_PDR_R |=0x04;  //PULL down RESISTOR*/
}

void portE_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x10;  //enable port E
    while((SYSCTL_PRGPIO_R& 0x10)==0); //wait until port A activation

    //GPIO_PORTB_CR_R |=0xFF;   // control reg
    GPIO_PORTE_AFSEL_R &=~0x3F;
    GPIO_PORTE_PCTL_R =0x00000000;  //clear
    GPIO_PORTE_AMSEL_R &=~0x3F; // no analog function

    GPIO_PORTE_DIR_R |=0x3F; // set pin  as output
    GPIO_PORTE_DEN_R |=0x3F;   //enable bins

}

void portF_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;  //enable port F
    while((SYSCTL_PRGPIO_R& 0x20)==0); //wait until port A activation
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |=0x1F;   // control reg
    GPIO_PORTF_AFSEL_R =0;    //reset for bin 0-4
    GPIO_PORTF_AMSEL_R |=0; // no analog function
    GPIO_PORTF_PUR_R =0x11;  //PULL UP RESISTOR
    GPIO_PORTF_DIR_R |=0x0E; // set pin  as output
    GPIO_PORTF_DEN_R |=0x1F;   //enable bins

}

// systick initialization
void Systic_init(void)
{
	NVIC_ST_CTRL_R =0;  //disable systic during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF;  //MAX RELOAD VALUE
	NVIC_ST_CURRENT_R = 0;  // ANY WRITE TO CURRENT CLEARS IT
	NVIC_ST_CTRL_R = 0x00000005;   // ENABLE SYSTIC WITH CORE CLOCK
	
}

void Systic_Wait(uint32_t delay)
{
	NVIC_ST_RELOAD_R = delay-1;  // number of count
	NVIC_ST_CURRENT_R = 0;  // ANY WRITE TO CURRENT CLEARS IT
	
	while((NVIC_ST_CTRL_R &0x00010000)==0);  // wait
}

//wait 10ms

void Systic_Wait_10ms(uint32_t delay)
{
	unsigned long i;
	for(i=0; i<delay;i++)
		Systic_Wait(800000);
}


