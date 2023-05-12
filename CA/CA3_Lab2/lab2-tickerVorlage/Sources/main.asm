;
;   Lab 2 - Testprogram for Ticker Interrupt
;
;   Computerarchitektur 3
;   (C) 2018 J. Friedrich, W. Zimmermann
;   Hochschule Esslingen
;
;   Author:   J.Friedrich
;   Modified: W.Zimmermann, Jun  10, 2016
;

; Export symbols
        XDEF Entry, main

; Import symbols
        XREF __SEG_END_SSTACK           ; End of stack
        XREF initTicker                 ; Ticker function

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init:  SECTION

main:
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger

        ldaa #$FF
        staa DDRB                       ; Initialize port B as outputs
        clr  PORTB

        jsr  initTicker                 ; Initialize the ticker

back:   bra back




