/*  Lab 2 - Main C file for Clock program

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann
    Hochschule Esslingen

    Author:  W.Zimmermann, July 19, 2017
*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


// PLEASE NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:
// Files lcd.asm and ticker.asm do contain SOFTWARE BUGS. Please overwrite them
// with the lcd.asm file, which you bug fixed in lab 1, and with file ticker.asm
// which you bug fixed in prep task 2.1 of this lab 2.
//
// To use decToASCII you must insert file decToASCII from the first lab into
// this project
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// ****************************************************************************
// Function prototype(s)
// Note: Only void Fcn(void) assembler functions can be called from C directly.
//       For non-void functions a C wrapper function is required.
void initTicker(void);

void initClock(void);
void tickClock(void);
void checkButtons(void);


// Prototypes and wrapper functions for dec2ASCII (from lab 1)
void decToASCII(void);

void decToASCII_Wrapper(char *txt, int val)
{   asm
    {  	LDX txt
        LDD val
        JSR decToASCII
    }
}

// Prototypes and wrapper functions for LCD driver (from lab 1)
void initLCD(void);
void writeLine(void);

void WriteLine_Wrapper(char *text, char line)
{   asm
    {	LDX  text
        LDAB line
        JSR  writeLine
    }
}

// ****************************************************************************

void initLED_C(void)
{   DDRJ_DDRJ1  = 1;	  	// Port J.1 as output
    PTIJ_PTIJ1  = 0;		
    DDRB        = 0xFF;		// Port B as output
    PORTB       = 0x55;
}

int LCD_state = 0; // 0 = Name of all members, 1 =  � IT W2021/22

void toggleLCD_state(void) {
    LCD_state = ~LCD_state; 
}

void outputLCD_state(void) {
  toggleLCD_state();
  if (LCD_state==0) {
    WriteLine_Wrapper("Noah, Mateusz",0); 
  } else  {
    WriteLine_Wrapper("� IT SS2023",0); 
  }
}



// ****************************************************************************
// Global variables
unsigned char clockEvent = 0;

// ****************************************************************************
void main(void) 
{   EnableInterrupts;                           // Global interrupt enable

    initLED_C();                    		// Initialize the LEDs

    initLCD();                    		// Initialize the LCD   

    initTicker();                               // Initialize the time ticker


    initClock();

    

    for(;;)                                     // Endless loop
    {   if (clockEvent)
    	{   clockEvent = 0;
    
        tickClock();
        outputLCD_state();
    	}
    	checkButtons();
    }
}
