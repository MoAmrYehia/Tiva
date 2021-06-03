#include "TM4C123GH6PM.h"  //header files for TM4C123 device and sprintf library 
#include <stdio.h>
//Function prototype for Timer0A and UART module initialization 
uint32_t Measure_distance(void);
void Timer0ACapture_init(void);
void Delay_MicroSecond(int time);
void UART5_init(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void Delay(unsigned long counter);
// global variables to store and display distance in m 
uint32_t time;    //stores pulse on time 
uint32_t distance; //stores measured distance value
char mesg[20];     //string format of distance value
//main code to take distance measurement and send data to UART terminal
int main(void)
{
Timer0ACapture_init();  //initialize Timer0A in edge edge time
UART5_init();           //initialize UART5 module to transmit data to computer
	while(1)
	{
time = Measure_distance();    //take pulse duration measurement
distance = (time * 10625)/10000000;      //convert pulse duration into distance
sprintf(mesg, "\r\nDistance = %d m", distance); //convert float type distance data into string
printstring(mesg);  //transmit data to computer
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
	while(1)
	{
    TIMER0->ICR = 4;            
    while((TIMER0->RIS & 4) == 0) ;    
	  if(GPIOB->DATA & (1<<6)) 
		{
    lastEdge = TIMER0->TAR;     
    TIMER0->ICR = 4;            
    while((TIMER0->RIS & 4) == 0) ;    
    thisEdge = TIMER0->TAR;     
		return (thisEdge - lastEdge); 
		}
	}
}
	 
	  
}
