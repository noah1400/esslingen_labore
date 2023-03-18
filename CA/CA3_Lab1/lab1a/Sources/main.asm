
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

;       ... ??? ...                     ; Add your code here


