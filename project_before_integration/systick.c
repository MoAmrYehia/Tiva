#include "ports_init.h"

void Systic_init(void)
{
	NVIC_ST_CTRL_R =0;  //disable systic during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF;  //MAX RELOAD VALUE
	NVIC_ST_CURRENT_R = 0;  // ANY WRITE TO CURRENT CLEARS IT
	NVIC_ST_CTRL_R = 0x00000005;   // ENABLE SYSTIC WITH CORE CLOCK
	
}

void Systic_Wait(uint32_t delay)
{
	NVIC_ST_RELOAD_R = delay-1;  // number of count
	NVIC_ST_CURRENT_R = 0;  // ANY WRITE TO CURRENT CLEARS IT
	
	while((NVIC_ST_CTRL_R &0x00010000)==0);  // wait
}

//wait 10ms

void Systic_Wait_10ms(uint32_t delay)
{
	unsigned long i;
	for(i=0; i<delay;i++)
		Systic_Wait(800000);
}
