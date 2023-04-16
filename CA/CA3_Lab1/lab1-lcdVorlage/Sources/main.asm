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

; Import symbols
        XREF __SEG_END_SSTACK                   ; End of stack
        XREF initLCD, writeLine, delay_10ms     ; LCD functions
        XREF hexToASCII
        XREF decToASCII
        XREF delay_0_5sec
        XREF toLower
        

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION
i DS.W 1
msgDec DS.B 7
msgHex DS.B 7

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
        
        MOVW #5, i
        
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

                                        ; MSG1 for line 0, X points to MSG1
        ;LDX #MSG1
        ;LDAB #0                         ; Write to line 0
        ;JSR  writeLine

                                        ; MSG2 for line 1, X points to MSG2
        ;LDX #MSG2
        ;LDAB #1                         ; Write to line 1
        ;JSR  writeLine
        
        ;LDX #msgA
        ;LDAB #0                         
        ;JSR  writeLine

        ;LDX #msgB
        ;LDAB #1                         ; Write to line 1
        ;JSR  writeLine

back:   BRA back

