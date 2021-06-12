#include "ports_init.h"
#include <TM4C123.h>
#define LCD_RS (*((volatile unsigned long *)0x40004200))
#define LCD_EN (*((volatile unsigned long *)0x40004100))
#define LCD_RW (*((volatile unsigned long *)0x40004080))

void LCD_WRITE(unsigned char character)
{
		GPIOA->DATA =0x80;  //RS=1 , E=0,RW =0
    GPIOB->DATA =character;
    GPIOA->DATA |=0x40;
		GPIOA->DATA =0x00;
    // requires delay micro function
		Delay_Micro(0);
}
