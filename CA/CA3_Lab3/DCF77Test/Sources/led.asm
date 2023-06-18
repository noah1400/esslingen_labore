;
;   Simple LED driver for Dragon12 Evaluation Board
;
;   Computerarchitektur 3
;   (C) 2018 J. Friedrich, W. Zimmermann
;   Hochschule Esslingen
;
;   Author:   W.Zimmermann, Jun  10, 2016
;   Modified: -
;

; Export symbols
        XDEF initLED, toggleLED, setLED, clrLED

; Import symbols

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines
SEVEN_SEGS_OFF  EQU 1                   ; Uncomment this to turn seven segment display off

; RAM: Variable data section
.data:  SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init:  SECTION


;**************************************************************
; initLED ... Initialize LEDs (called once)
; Parameter: -
; Return:    -
initLED:
        BSET DDRJ, #2                   ; Bit Set:   Port J.1 as output
        BCLR PTJ,  #2                   ; Bit Clear: J.1=0 --> Activate LEDs

        MOVB #$FF, DDRB                 ; Initialize port B as outputs
        CLR  PORTB                      ; and turn LEDs off

   ifdef SEVEN_SEGS_OFF
        MOVB #$0F, DDRP                 ; Port P.3..0 as outputs (seven segment display control)
        MOVB #$0F, PTP                  ; Turn off seven segment display
   endif
        RTS


; toggleLED ... Toggle LEDs specified by bitmask
; Parameter: B ... bitmask (1 ... toggle, 0 ... unchanged)
; Return:    -
toggleLED:
        EORB PORTB
        STAB PORTB
        RTS

; setLED ... Set LEDs specified by bitmask
; Parameter: B ... bitmask (1 ... set, 0 ... unchanged)
; Return:    -
setLED:
        ORAB  PORTB
        STAB PORTB
        RTS

; clrLED ... Clear LEDs specified by bitmask
; Parameter: B ... bitmask (1 ... clear, 0 ... unchanged)
; Return:    -
clrLED:
        COMB
        ANDB PORTB
        STAB PORTB
        RTS


