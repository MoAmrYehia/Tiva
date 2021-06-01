/*
 * ports_init.h
 *
 *  Created on: May 26, 2021
 *      Author: ehab
 */
#include <TM4C123.h>
 #include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>


#include "C:\Keil\EE319Kware\inc/tm4c123gh6pm.h"

#ifndef PORTS_INIT_H_
#define PORTS_INIT_H_

void portA_init(void);
void portB_init(void);
void portD_init(void);
void portE_init(void);
void portF_init(void);
void Systic_Wait_10ms(uint32_t delay);
void Systic_Wait(uint32_t delay);
void Systic_init(void);




#endif /* PORTS_INIT_H_ */
