;
;   Labor 1 - Test program for LCD driver
;
;   Computerarchitektur
;   (C) 2019-2022 J. Friedrich, W. Zimmermann, R. Keller
;   Hochschule Esslingen
;
;   Author:   	   J.Friedrich, W. Zimmermann
;   Last Modified: R. Keller, August 2022
; Export symbols
        XDEF Entry, main
        XDEF PORTB, DDRB

; Import symbols
        XREF __SEG_END_SSTACK                   ; End of stack
        XREF initLCD, writeLine, delay_10ms     ; LCD functions
        XREF decToASCII, hexToASCII
        XREF setLED, initLED
        XREF delay_0_5sec
; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION
 i: ds.w  1
 msgDec: ds.b 7  
 msgHex: ds.b 7
 
; ROM: Constant data
.const: SECTION
MSG1:   dc.b " Mach mal eine",0
MSG2:   dc.b " kleine Pause",0
msgA:   DC.B "ABCDEFGHIJKLMnopqrstuvwxyz1234567890",0  ;on line 0
msgB:   DC.B "is this OK?",0                           ;on line 1



; ROM: Code section
.init:  SECTION

main:
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger

        JSR  delay_10ms                 ; Delay 20ms during power up
        JSR  delay_10ms                 ; by Jump-Subroutine (use step-over)

        JSR  initLCD                    ; Initialize the LCD

        MOVW #60000, i
        
        
main_loop:
        LDX #msgDec
        LDD i
        JSR decToASCII
        
        LDX #msgHex
        LDD i
        JSR hexToASCII
        
        
        
        LDX #msgDec
        LDAB #0
        JSR writeLine
        
        LDX #msgHex
        LDAB #1
        JSR writeLine
        
        LDD i
        JSR setLED                                 
        
        ;increment i
        LDD i
        ADDD #1
        STD i
        
        JSR delay_0_5sec
        BRA main_loop
        
        
        

back:   BRA back

