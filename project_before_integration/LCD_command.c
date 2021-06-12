#include "ports_init.h"
#include <TM4C123.h>
#define LCD_RS (*((volatile unsigned long *)0x40004200))
#define LCD_EN (*((volatile unsigned long *)0x40004100))
#define LCD_RW (*((volatile unsigned long *)0x40004080))

void LCD_CMD(unsigned char cmd)
{
		GPIOA->DATA =0x00;
		GPIOB->DATA = cmd; //set PB7-0 as the passed command to the function
    
		GPIOA->DATA = 0x40;  // set enable pin to high
    Delay_Micro(0);
    GPIOA->DATA = 0x00;  //set enable pin to low
		if(cmd<4)
			Delay_Milli(2);
		else 
			Delay_Micro(37);
}
