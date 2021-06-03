#include "TM4C123GH6PM.h"
#include <stdio.h>
uint32_t Measure_distance(void);
void Timer0ACapture_init(void);
void Delay_MicroSecond(int time);
void UART5_init(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void Delay(unsigned long counter);
uint32_t time;
uint32_t distance; 
char mesg[20];  
int main(void)
{
Timer0ACapture_init();  
UART5_init();
	while(1)
	{
time = Measure_distance();  
distance = (time * 10625)/10000000; 
sprintf(mesg, "\r\nDistance = %d cm", distance); 
printstring(mesg); 
Delay(2000);

	}
	
}
uint32_t Measure_distance(void)
{
    int lastEdge, thisEdge;
	
	  GPIOA->DATA &= ~(1<<4); 
	  Delay_MicroSecond(10); 
	  GPIOA->DATA |= (1<<4); 
	  Delay_MicroSecond(10); 
	  GPIOA->DATA &= ~(1<<4);
	  
}
