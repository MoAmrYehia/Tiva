/*
 * LCD_display.c
 *
 *  Created on: May 28, 2021
 *      Author: ehab
 */
 /*
#include "ports_init.h"
#include <TM4C123.h>

#define LCD_RS (*((volatile unsigned long *)0x40004200))
#define LCD_EN (*((volatile unsigned long *)0x40004100))
#define LCD_RW (*((volatile unsigned long *)0x40004080))
*/
#include "LCD_display.h"

void Delay()
{
    unsigned long time;
    time =12000;
    while(time)
            time--;
    

}

void LCD_CMD(unsigned long cmd)
{

    GPIO_PORTB_DATA_R= cmd; //set PB7-0 as the passed command to the function
    LCD_RS = 0x00;   // set PA7 reg_select pin to low
    LCD_RW =0x00;  // set PA5 r/w pin to low
    LCD_EN = 0x40;  // set enable pin to high
    Delay();
    LCD_EN = 0x00;  //set enable pin to low
}

void LCD_WRITE(unsigned char data)
{
    GPIO_PORTB_DATA_R =data;
    LCD_RS= 0x80;   // set PA7 to high
    LCD_RW= 0x00;  // set PA5 to low
    LCD_EN = 0x40; // set the enable pin high
    Delay();
    LCD_EN = 0x00;  // set the enable pin to low

}


