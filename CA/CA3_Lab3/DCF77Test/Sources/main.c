/*  Test Program for DCF77 Signal

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann
    Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: -

*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines

#include "led.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

// ****************************************************************************
unsigned char val;

void main(void)
{   EnableInterrupts;                           // Allow interrupts

    initLED();                                  // Initialize LEDs on port B
    clrLED(0xFF);                               // Turn all LEDs off

    for(;;)                                     // Endless loop
    {   if (PTH & 0x01) setLED(0x02); else clrLED(0x02);// Output state of port H.0 on LED B.1

        if (PTS & 0x04) setLED(0x01); else clrLED(0x01);// Output state of port S.2 on LED B.0

    }
}



