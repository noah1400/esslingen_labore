/*  Radio signal clock - C Main Program

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: 

*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines

#include "led.h"
#include "lcd.h"
#include "clock.h"
#include "dcf77.h"
#include "ticker.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

// ****************************************************************************
void main(void)
{   EnableInterrupts;                           // Allow interrupts

    initLED();                                  // Initialize LEDs on port B
    initLCD();                                  // Initialize LCD display
    initClock();                                // Initialize Clock module
    initDCF77();                                // Initialize DCF77 module
    initTicker();                               // Initialize the time ticker

    for(;;)                                     // Endless loop
    {   if (clockEvent != NOCLOCKEVENT)         // Process clock event
        {   processEventsClock(clockEvent);

            displayTimeClock();

            clockEvent=NOCLOCKEVENT;            // Reset clock event
        }

        if (dcf77Event != NODCF77EVENT)         // Process DCF77 events
        {   processEventsDCF77(dcf77Event);

            displayDateDcf77();

            dcf77Event = NODCF77EVENT;          // Reset dcf77 event
        }
    }
}



