/*
 * ports_init.h
 *
 *  Created on: May 26, 2021
 *      Author: ehab
 */

 

#include "ports_init.h"
#include <stdio.h>





void HC05_init(void);
void Blutooth_Write(unsigned char data);
void Blutooth_Write_String(char *str);
char Blutooth_Read(void);




