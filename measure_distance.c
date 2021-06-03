/*
 * measure_distance.c
 *
 *  Created on: May 28, 2021
 *  Created by: Dina A.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "ports_init.h"
#include "measure_distance.h"

#define PI 3.14159265358979323846


// Delay function
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

// Convert degrees to radian
double toRadians(double degree)
{
    double r = degree * PI / 180;
    return r;
}

double getDistance(double lat1, double lon1, double lat2, double lon2)
{
    double a = 6378137, b = 6356752.314245, f = 1 / 298.257223563;
    double L = toRadians(lon2 - lon1);
