/*
 * measure_distance.c
 *
 *  Created on: May 28, 2021
 *      Author: Dina
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "ports_init.h"

#define PI 3.14159265358979323846
#include "measure_distance.h"

void delay_us(uint32_t delay)
{
    // using clk freq 80M will make a delay with unit of usecond
    uint8_t x=0;
    SYSCTL_RCGCTIMER_R |=1;    //Connect timer to clock
    x+=5;   // to make sure the clock is connected
    TIMER0_CTL_R &=~1; // disable the timer to config it
    TIMER0_CFG_R=0;   //32-bit timer mode
    TIMER0_TAMR_R=2; //periodic mode
     TIMER0_TAMR_R |=0x10;  // up select
    TIMER0_TAILR_R = 80*delay-1;   // interval value to count
    TIMER0_ICR_R |=1;  //clear the timeout flag
    TIMER0_CTL_R |=1; // timer enable and counting starts
    while(!TIMER0_RIS_R &1);  // wait to finish the interval
}
double toRadians(double degree)
{
    double r = degree * PI / 180;
    return r;
}
