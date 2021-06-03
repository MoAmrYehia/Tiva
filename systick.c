#include "ports_init.h"

void Systic_init(void)
{
	NVIC_ST_CTRL_R =0;  //disable systic during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF;  //MAX RELOAD VALUE
	NVIC_ST_CURRENT_R = 0;  // ANY WRITE TO CURRENT CLEARS IT
	NVIC_ST_CTRL_R = 0x00000005;   // ENABLE SYSTIC WITH CORE CLOCK
	
}
