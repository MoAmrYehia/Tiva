#include "ports_init.h"
#include <TM4C123.h>
#define LCD_RS (*((volatile unsigned long *)0x40004200))
#define LCD_EN (*((volatile unsigned long *)0x40004100))
#define LCD_RW (*((volatile unsigned long *)0x40004080))

void Delay_Micro(unsigned long x)
{
	unsigned long i,k;
		for(i=0;i<x;i++)
				for(k=0;k<3;k++);  
}
