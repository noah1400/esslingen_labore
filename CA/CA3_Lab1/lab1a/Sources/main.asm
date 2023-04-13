
;   Labor 1 - Problem 2.2
;   Incrementing a value once per second and binary output to LEDs
;
;   Computerarchitektur
;   (C) 2019-2022 J. Friedrich, W. Zimmermann, R. Keller
;   Hochschule Esslingen
;
;   Author:   R. Keller, HS-Esslingen
;            (based on code provided by J. Friedrich, W. Zimmermann)
;   Modified: -
;

; export symbols
        XDEF Entry, main

; import symbols
        XREF __SEG_END_SSTACK           ; End of stack

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines
SPEED:  EQU     $FFFF                   ; Change this number to change counting speed

; RAM: Variable data section
.data: SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION




main:                                   ; Begin of the program
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger
        
        counter: DS.W 1 ; declare variable
        CLR     counter ; set to 0
        
        MOVB    #$FF, DDRB  ; set data direction to output
        MOVB    #$00, PORTB ; all leds 0
        
Loop:
        LDD       counter   ; load counter in D
        STD       PORTB     ; output counter/D 
        
        JSR       delay_0_5sec ; wait
        
        ADDD      #2           ; add 2 to D
        STD       counter      ; store increased value in counter
        
        LDD       counter      ; load counter in D
        CMPB      #64          ; compare
        BLO       Loop
        
        CLR       counter
        BRA       Loop
        
delay_0_5sec:
        LDY       #50000
        LDX       #20
        delay_loop:
        DBNE      Y, delay_loop
        LDY       #50000
        DBNE      X, delay_loop          
                 
        RTS



        


