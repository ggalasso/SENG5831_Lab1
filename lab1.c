#define ECHO2LCD

#include <pololu/orangutan.h>

#include "LEDs.h"
#include "timer.h"
#include "menu.h"

//Gives us uintX_t (e.g. uint32_t - unsigned 32 bit int)
//On the ATMega128 int is actually 16 bits, so it is better to use
//  the int32_t or int16_t so you know exactly what is going on
#include <inttypes.h> //gives us uintX_t

// useful stuff from libc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GLOBALS
volatile uint32_t G_yellow_ticks = 0;
volatile uint32_t G_ms_ticks = 0;

volatile uint16_t G_red_period = 1000;
volatile uint16_t G_green_period = 1000;
volatile uint16_t G_yellow_period = 10;

volatile uint16_t G_release_red = 0;

volatile uint32_t G_red_toggles = 0;
volatile uint32_t G_green_toggles = 0;
volatile uint32_t G_yellow_toggles = 0;

volatile uint8_t G_flag = 0; // generic flag for debugging

int main(void) {
	// -------------------------------------------------------------
	// This program teaches you about the various ways to "schedule" tasks.
	// You can think of the three blinking LEDs as separate tasks with 
	// strict timing constraints.
	//
	// As you build your program, think about the guarantees that you can 
	// make regarding the meeting of deadlines. Think about how the CPU
	// is "communicating" with the LEDs. Obviously, everything is output,
	// but what if it was input? Also think about how data can be passed
	// among tasks and how conflicts might arise.
	//
	// You will construct this program in pieces.
	// First, establish WCET analysis on a for loop to use for timing.
	// Use the for loop to blink the red LED.
	// Next, set up a system 1 ms software timer, and use that to "schedule" the blink
	// inside a cyclic executive.
	//
	// Blink the yellow LED using a separate timer with a 100ms resolution.
	// Blink the LED inside the ISR.
	//
	// Finally, blink the green LED by toggling the output on a pin using
	// a Compare Match. This is the creation of a PWM signal with a very long period.
	//	
	// --------------------------------------------------------------

	int i;

	// Used to print to serial comm window
	char tempBuffer[32];
	int length = 0;
	
	// Initialization here.
	lcd_init_printf();	// required if we want to use printf() for LCD printing
	init_LEDs();
	init_timers();
	init_menu();	// this is initialization of serial comm through USB
	
	clear();	// clear the LCD
    
    //Check the loop timer. This seems off, for some reason seems to optimize as it gets higher.
    volatile uint32_t count;
    unsigned long start;
    unsigned long end;
    start = get_ms();
    /*for (count = 0; count <= 5394; count++) {
    }*/
    //end = get_ms();
    int len;
    char tBuffer[32];
    //len = sprintf( tBuffer, "Start: %lu\r\n", start);
    //print_usb( tBuffer, len);
    //len = sprintf( tBuffer, "End: %lu\r\n", end);
    //print_usb( tBuffer, len);*/
    

	//enable interrupts
	sei();
	
	while (1) {
        /*if (start >= 60000) {
            len = sprintf( tBuffer, "End: %lu\r\n", start);
            print_usb( tBuffer, len);
            len = sprintf( tBuffer, "RED Toggles: %lu\r\n", G_red_toggles);
            print_usb( tBuffer, len);
            len = sprintf( tBuffer, "YELLOW Toggles: %lu\r\n", G_yellow_toggles);
            print_usb( tBuffer, len);
            len = sprintf( tBuffer, "GREEN Toggles: %lu\r\n", G_green_toggles);
            print_usb( tBuffer, len);
            break;
        } else {
            start = get_ms();
        }*/
        
		/* BEGIN with a simple toggle using for-loops. No interrupt timers */
        
        /*for (i=0;i<100;i++) {
            WAIT_10MS;
            if(i == 99) {
                LED_TOGGLE(RED);
                G_red_toggles++;
            }
        }*/

		// toggle the LED. Increment a counter.
		//LED_TOGGLE(RED);
		//G_red_toggles++;
		//length = sprintf( tempBuffer, "R toggles %lu\r\n", G_red_toggles );
		//print_usb( tempBuffer, length );
        /*#ifdef ECHO2LCD
		lcd_goto_xy(0,0);
		printf("R:%lu ",G_red_toggles);
        #endif*/

		// create a for-loop to kill approximately 1 second
		/*for (i=0;i<100;i++) {
			WAIT_10MS;
		}*/
		// ONCE THAT WORKS, Comment out the above and use a software timer
		//	to "schedule" the RED LED toggle.

		if (G_release_red) {
			LED_TOGGLE(RED);
			G_red_toggles++;
			G_release_red = 0; 
		}

		// Whenever you are ready, add in the menu task.
		// Think of this as an external interrupt "releasing" the task.
		serial_check();
		check_for_new_bytes_received();
					
	} //end while loop
} //end main

