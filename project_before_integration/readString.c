#include <TM4C123.h>
#include "test.h"

char *Read_String(char data)
{
	int string_size =0;
	char *string= (char*)calloc(10,sizeof(char));
	char c=Read_Char();
	Print_Char(c);
	
	while(c!=data)
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
