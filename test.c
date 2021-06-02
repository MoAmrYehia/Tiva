#include <TM4C123.h>
#include "test.h"

char Read_Char(void)
{
	char c;
	while((UART0->FR &(1<<4))!=0);  //WAIT UNTILL RX BUFFER NOT FULL
	c=UART0->DR;
	return c;
}

void Print_Char(char c)
{
	while((UART0->FR &0x20)!=0);  //WAIT UNTILL TX BUFFER NOT FULL
	UART0->DR = c;
}

void Print_String(char * s)
{
	while(*s)
		Print_Char(*(s++));
}

char *Read_String(char d)
{
	int string_size =0;
	char *string= (char*)calloc(10,sizeof(char));
	char c=Read_Char();
	Print_Char(c);
	
	while(c!=d)
	{
		*(string+string_size)= c;  //push at the end of the array
		string_size++;
		
		if((string_size%10)==0)      //memory exceed
			string =(char*)realloc(string,(string_size+10)*sizeof(char));
		c= Read_Char();
		Print_Char(c);
		
	}
	if(string_size==0)
		return '\0';   //null
	return string;
}
