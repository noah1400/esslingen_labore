
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
        XDEF Entry, main, PORTB, DDRB
        
        
        

; import symbols
        XREF __SEG_END_SSTACK           ; End of stack

; include derivative specific macros

        INCLUDE 'mc9s12dp256.inc'
        
        INCLUDE 'delay.asm'
        INCLUDE 'led.asm'
        
                      

; Defines
SPEED:  EQU     $FFFF                   ; Change this number to change counting speed

; RAM: Variable data section
.data: SECTION
counter: DS.W 1 ; declare variable        
        

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION



  

main:                                   ; Begin of the program
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger
        
        MOVW    #0, counter ; set counter to 0
        CALL    initLED
        
        
Loop:
        LDD       counter   ; load counter in D
        CALL      setLED
        
        CALL       delay_0_5sec ; wait
        
        ADDD      #2           ; add 2 to D
        STD       counter      ; store increased value in counter
        
        LDD       counter      ; load counter in D
        CMPB      #64          ; compare
        BLO       Loop
        
        MOVW      #0, counter  ; reset counter
        BRA       Loop         ; branch to loop
        




        


