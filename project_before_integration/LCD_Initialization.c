#include "ports_init.h"
#include <TM4C123.h>
#define LCD_RS (*((volatile unsigned long *)0x40004200))
#define LCD_EN (*((volatile unsigned long *)0x40004100))
#define LCD_RW (*((volatile unsigned long *)0x40004080))

void LCD_INIT(void)
{
	SYSCTL->RCGCGPIO |=0x01;
	SYSCTL->RCGCGPIO |=0x02;
	GPIOA->DIR |=0xE0;  // RS, E, RW  ---- PA7, PA6, PA5
	GPIOA->DEN |=0xE0;  
	GPIOB->DIR |=0xFF; 
	GPIOB->DEN |=0xFF;
  // requires lcd command function
	LCD_CMD(0x38);  //8bit 2displaylines, 5*7 font
	LCD_CMD(0x06); // increment automatically
	LCD_CMD(0x0F);  // turn on display
	LCD_CMD(0x01);  //clear display
}
