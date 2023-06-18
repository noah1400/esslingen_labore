/*  Header for LED module

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:  W.Zimmermann, Jun 10, 2016
*/

// Public functions, for details see led.asm
void initLED(void);
void toggleLED(unsigned char mask);
void setLED(unsigned char mask);
void clrLED(unsigned char mask);
