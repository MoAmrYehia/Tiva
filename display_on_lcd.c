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
