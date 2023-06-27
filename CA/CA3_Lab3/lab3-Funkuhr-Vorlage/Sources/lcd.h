/*  Header for LCD module

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: 
*/

// Public functions, for details see lcd.asm
void initLCD(void);
void writeLine(char* text, unsigned char zeilennummer);
void delay_10ms(void);
