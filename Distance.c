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
