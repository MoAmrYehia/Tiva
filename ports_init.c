/*
 * ports_init.c
 *
 *  Created on: May 26, 2021
 *      Author: ehab
 */

#include "TM4C123.h"
//A
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *) 0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *) 0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *) 0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *) 0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *) 0x4000451C))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *) 0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *) 0x40004528))
//B
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *) 0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *) 0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *) 0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *) 0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *) 0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *) 0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *) 0x40005528))
void portA_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x01;  //enable port A
    while((SYSCTL_PRGPIO_R& 0x01)==0); //wait until port A activation
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R |=0xFC;   // control reg
    GPIO_PORTA_AFSEL_R &= 0x03;  // input &output
    GPIO_PORTA_PCTL_R &=0x03;  //no alternative function
    GPIO_PORTA_AMSEL &=0x03; // no analog function
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
    GPIO_PORTA_AMSEL =0; // no analog function
    GPIO_PORTA_DIR_R |= 0xFF; //output
    GPIO_PORTA_DEN_R =0xFF;   //Digital
    GPIO_PORTA_PUR_R =0;  //PULL UP RESISTOR
}

void portD_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x08;  //enable port D
    while((SYSCTL_PRGPIO_R& 0x08)==0); //wait until port A activation

    //GPIO_PORTB_CR_R |=0xFF;   // control reg
    GPIO_PORTD_AFSEL_R &=~0x4C;
    GPIO_PORTD_PCTL_R =0x00000000;  //clear
    GPIO_PORTD_AMSEL &=~0x4C; // no analog function
    GPIO_PORTD_DIR_R &= 0xFB; // set pin 2 as input
    GPIO_PORTD_DIR_R |=0x48; // set pin 3 as output
    GPIO_PORTD_DEN_R |=0x4C;   //enable bins
    GPIO_PORTD_PDR_R |=0x04;  //PULL down RESISTOR
}

void portE_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x10;  //enable port E
    while((SYSCTL_PRGPIO_R& 0x10)==0); //wait until port A activation

    //GPIO_PORTB_CR_R |=0xFF;   // control reg
    GPIO_PORTD_AFSEL_R &=~0x3F;
    GPIO_PORTD_PCTL_R =0x00000000;  //clear
    GPIO_PORTD_AMSEL &=~0x3F; // no analog function

    GPIO_PORTD_DIR_R |=0x3F; // set pin  as output
    GPIO_PORTD_DEN_R |=0x3F;   //enable bins

}

void portF_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;  //enable port F
    while((SYSCTL_PRGPIO_R& 0x20)==0); //wait until port A activation
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |=0x1F;   // control reg
    GPIO_PORTD_AFSEL_R =0;    //reset for bin 0-4
    GPIO_PORTD_AMSEL |=0; // no analog function
    GPIO_PORTA_PUR_R =0x11;  //PULL UP RESISTOR
    GPIO_PORTD_DIR_R |=0x0E; // set pin  as output
    GPIO_PORTD_DEN_R |=0x1F;   //enable bins

}


