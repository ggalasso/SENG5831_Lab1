/*******************************************
*
* Header file for Timer stuff.
*
*******************************************/
#ifndef __TIMER_H
#define __TIMER_H

#include <inttypes.h> //gives us uintX_t

// number of empty for loops to eat up about 1 ms
//My other program was around 5588, but re-ran in this app and the number was lower. 
#define FOR_COUNT_10MS 5394

volatile uint32_t __ii;

#define WAIT_10MS {for (__ii=0;__ii<FOR_COUNT_10MS; __ii++);}

#define G_TIMER_RESOLUTION 100
#define Y_TIMER_RESOLUTION 100

void init_timers();

#endif //__TIMER_H
