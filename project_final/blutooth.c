/*
 * blutooth.c
 *
 *  Created on: May 26, 2021
 *      Author: ehab
 */
//#include <TM4C123.h>
#include "blutooth.h"

void HC05_init(void)
{
	
	SYSCTL->RCGCUART |=  (1<<5);//4; //enable clock for UART5  port E
    SYSCTL->RCGCGPIO |=   (1<<4);  //  8;
	    
    GPIOE->AFSEL |=   0x30;//(1<<6)|(1<<7);   //port 6,7
    GPIOE->PCTL |= 0x00110000;//(GPIOD->PCTL& 0x00FFFFFF)+0x22000000;//|=   0xC0;
    GPIOE->DEN |=  0x30;   // (1<<6)|(1<<7);
		//GPIOD->AMSEL &=~0xC0;
		UART5->CTL &=~(1<<0);      //~(0x20);
	//after calculationg baudrate
    UART5->IBRD = 0x00000145;
    UART5->FBRD = 0x00000021;

    UART5->LCRH |=  0x70; //(0x3<<5)|(1<<4);       //0x60; //desired serial parameter
    UART5->CC= 0x0;        //select system clock
    UART5->CTL = 0x301;	 //(1<<0)|(1<<8)|(1<<9);			//0x301;  //enable UART by setting UARTEN bi in the UARTCTL REG
	
	
}

char Blutooth_Read(void)
{
	char data;
	while((UART5->FR&(1<<4))!=0);
	data =UART5->DR;
	return (unsigned char) data;
}
void Blutooth_Write(unsigned char data)
{
	while((UART5->FR&(1<<5))!=0);
	UART5->DR =data;
}

void Blutooth_Write_String(char *str)
{
	while(*str)
	{
		Blutooth_Write(*(str++));
	}
}