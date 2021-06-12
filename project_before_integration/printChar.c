#include <TM4C123.h>
#include "test.h"

void Print_Char(char data)
{
	while((UART0->FR &0x20)!=0);  //WAIT UNTILL TX BUFFER IS NOT FULL
	UART0->DR = data;
}
