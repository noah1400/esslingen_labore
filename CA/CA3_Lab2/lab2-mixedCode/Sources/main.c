/*  Mixed mode C - Assembler programming
    C side module
    For a description see Lab 2 manual appendix B

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann
    Hochschule Esslingen

    Author:  W.Zimmermann, July 19, 2017
*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


//***** Function prototype(s) *************************************************
//***** Normal C function prototypes
void function1C(void);
int function2C(int param1, int param2);
void wait(void);


//***** Function prototypes for ASM functions (with no parameters or return values)
void function1A(void);
void function2A(void);
void function3A(void);


//***** Wrapper functions
//***** Wrapper for ASM function to be called from C (with params and return value)
int function2A_wrapper(int param1, int param2)
{   int returnVal;

    // Copy parameters to registers
    asm LDX param1;
    asm LDY param2      ;

    // Call ASM function
    function2A();

    // Copy return value
    asm STD returnVal;
    return returnVal;
}


//***** Wrapper for C function to be called from assembler (with params and return value)
void function2C_wrapper(void)
{   int param1, param2, retVal;

    // Get parameters from regs
    asm STX param1
    asm STY param2

    // Call C function
    retVal = function2C(param1, param2);

    // Copy return value to reg
    asm LDD retVal;
}


// ****************************************************************************
// Global variables
// ****************************************************************************

// Declare C variables
int  var1C = 0x55AA;
char var2C = 0;


// Reference ASM variables
extern int  var1A;
extern char var2A;



// ****************************************************************************
// Helper functions
// ****************************************************************************
void initLED(void)
{   DDRJ_DDRJ1 = 1;
    PTIJ_PTIJ1 = 0;
    DDRB       = 0xFF;
    PORTB      = 0;
}

void setLED(unsigned char val)
{   PORTB = val;
}


// ****************************************************************************
// Execute this program step by step in the debugger
// ****************************************************************************
void main(void)
{   EnableInterrupts;                   // Global interrupt enable

    initLED();                          // Call ASM functions

    // Output C variables to LED
    setLED(var1C >> 8);                 // --- var1C upper 8 bits
    wait();
    setLED(var1C & 0x00FF);             // --- var2C lower 8 bits
    wait();
    setLED(var2C);
    wait();

    function1A();                       // Call assembler function, which changes var1C
                                        // ... calls functionC, which outputs variables to LEDs
                                        // ... and finally changes variables var1A

    // Output assembler variables to LED
    setLED(var1A >> 8);                 // --- var1A upper 8 bits
    wait();
    setLED(var1A & 0x00FF);             // --- var2A lower 8 bits
    wait();
    setLED(var2A);

    // Call assembler function with parameters and return value via wrapper function
    var1C = function2A_wrapper(0x1122, 2);

    setLED(var1C >> 8);                 // --- var1C upper 8 bits
    wait();
    setLED(var1C & 0x00FF);             // --- var2C lower 8 bits
    wait();

    // Call assembler function, which calls a C function with params and return value
    function3A();

    setLED(var1A >> 8);                 // --- var1A upper 8 bits
    wait();
    setLED(var1A & 0x00FF);             // --- var2A lower 8 bits
    wait();

    for(;;)                             // Endless loop
    {
    }
}


// This function will be called directly from assembler
void function1C(void)
{
    // Output C variables to LEDs
    setLED(var1C >> 8);                 // --- var1C upper 8 bits
    wait();
    setLED(var1C & 0x00FF);             // --- var2C lower 8 bits
    wait();
    setLED(var2C);
    wait();
}


// This function will be called from assembler via wrapper function function2C_wrapper
int function2C(int param1, int param2)
{   return param1 + param2;
}


// Wait loop
void wait(void)
{   long i;
    for(i = 1000000;i>0;i--)
    {
    }
}

