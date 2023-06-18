;
;   Ticker Interrupt, calling an Interrupt Service Routine every 10ms
;   Uses Enhanced Capture Timer ECT channel 4
;
;   Computerarchitektur 3
;   (C) 2018 J. Friedrich, W. Zimmermann
;   Hochschule Esslingen
;
;   Author:   J.Friedrich
;   Modified: W.Zimmermann, Jun  10, 2016
;
;   Usage:
;               JSR initTicker --> Initialize ticker
;                                 (must be called once)
;
;   Description:
;   The timer is initialized in such a way, that the ISR isrECT4 will be called every 10ms.
;   In the ISR a user-provided callback function
;                               void tick10ms(void)
;   will be called. This function must end before the next timer interrupt event, i.e.
;   the callbacks run time must be less than 10ms!
;

; Export symbols
        XDEF initTicker

; Import symbols
        XREF tick10ms           ; External function void tick10ms(void) called
                                ; every 10ms in interrupt context

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines
TENMS       equ 1875            ; 10 ms
TIMER_ON    equ $80             ; tscr1 value to turn ECT on
TIMER_CH4   equ $10             ; Bit position for channel 4
TCTL1_CH4   equ $03             ; Mask corresponds to TCTL1 OM4, OL4

; RAM: Variable data section
.data:  SECTION

; ROM: Constant data
.const: SECTION

.intVect: SECTION
        ORG $FFE6
int12:  DC.W isrECT4


; ROM: Code section
.init:  SECTION

;********************************************************************
; Public interface function: initLCD ... Initialize Ticker (called once)
; Parameter: -
; Return:    -
initTicker:
;       JSR  pllInit            ; Initalize PLL generator (not really necessary with serial monitor)

        ldab #TIMER_ON          ; Timer master ON switch
        stab TSCR1
        bset TIOS,#TIMER_CH4    ; Set channel 4 in "output compare" mode

        bset TIE,#TIMER_CH4     ; Enable channel 4 interrupt; bit 4 corresponds to channel 4

        ; Set timer prescaler (bus clock : prescale factor)
        ; In our case: divide by 2^7 = 128. This gives a timer
        ; driver frequency of 187500 Hz or 5.3333 us time interval
        ldab TSCR2
        andb #$f8
    ifdef SIMULATOR
        orab #5                 ; Speedup clock for debugging in simulator
    else
        orab #7
    endif
        stab TSCR2
        bclr TCTL1,#TCTL1_CH4   ; Switch timer on
        rts

;********************************************************************
; Internal function: isrECT4 ... Interrupt service routine, called by the timer ticker every 10ms
; Parameter: -
; Return:    -
isrECT4:
        ldd  TC4                ; Schedule the next ISR period
        addd #TENMS
        std  TC4
        ldab #TIMER_CH4         ; Clear the interrupt flag, write a 1 to bit 4
        stab TFLG1

        jsr  tick10ms           ; external function called every 10ms

notYet: rti

;********************************************************************
; Internal function: pllInit ... Initialize the PLL of the clock generator
; (This is already done by the serial monitor program on the Dragon12 board, but
; necessary, if the boards runs in stand alone mode (EEPROM mode))
; Parameter: -
; Return:    -
pllInit:BCLR CLKSEL, #$80               ; Disconnect PLL from CPU (only in case)
        BSET PLLCTL, #$40               ; Turn on PLL
        MOVB #$05,SYNR                  ; Set PLL multiplier
        MOVB #$00,REFDV                 ; Set PLL divider
        MOVB #$00,REFDV                 ; Set PLL divider (4MHz Quartz Draong12 board)
;       MOVB #$01,REFDV                 ; Set PLL divider (8MHz Quartz Dragon12 Plus board)
        NOP
        NOP
pllWait:BRCLR CRGFLG, #$08, pllWait     ; Wait till PLL has locked
        BSET  CLKSEL, #$80              ; Connect PLL to CPU
        RTS

