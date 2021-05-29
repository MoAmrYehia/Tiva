#include "ports_init.h"


#define LCD_RS (*((volatile unsigned long *)0x40004200))
#define LCD_EN (*((volatile unsigned long *)0x40004100))
#define LCD_RW (*((volatile unsigned long *)0x40004080))


void Delay();
void LCD_CMD(unsigned long cmd);
void LCD_WRITE(unsigned char data);