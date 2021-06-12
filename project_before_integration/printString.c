#include <TM4C123.h>
#include "test.h"

void Print_String(char * data)
{
	while(*data)
		Print_Char(*(data++));
}
