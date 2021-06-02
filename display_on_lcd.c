#include "ports_init.h"
#include <TM4C123.h>
#define LCD_RS (*((volatile unsigned long *)0x40004200))
#define LCD_EN (*((volatile unsigned long *)0x40004100))
#define LCD_RW (*((volatile unsigned long *)0x40004080))

void Delay_Milli(unsigned long n)
{
    unsigned long i,j;
		for(i=0;i<n;i++)
				for(j=0;j<3180;j++);  

}
void Delay_Micro(unsigned long n)
{
	unsigned long i,j;
		for(i=0;i<n;i++)
				for(j=0;j<3;j++);  
}

void LCD_INIT(void)
{
	SYSCTL->RCGCGPIO |=0x01;
	SYSCTL->RCGCGPIO |=0x02;
	GPIOA->DIR |=0xE0;  // RS, E, RW  ---- PA7, PA6, PA5
	GPIOA->DEN |=0xE0;  
	GPIOB->DIR |=0xFF; 
	GPIOB->DEN |=0xFF;
	LCD_CMD(0x38);  //8bit 2displaylines, 5*7 font
	LCD_CMD(0x06); // increment automatically
	LCD_CMD(0x0F);  // turn on display
	LCD_CMD(0x01);  //clear display
}

void LCD_WRITE(unsigned char data)
{
		GPIOA->DATA =0x80;  //RS=1 , E=0,RW =0
    GPIOB->DATA =data;
    GPIOA->DATA |=0x40;
		GPIOA->DATA =0x00;
		Delay_Micro(0);


}
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
