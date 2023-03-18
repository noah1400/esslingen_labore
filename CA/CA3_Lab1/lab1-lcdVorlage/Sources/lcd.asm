;
;   Simple LCD driver for Dragon12's 16 x 2 LCD
;                               (16 characters in 2 rows)
;
;   Computerarchitektur
;   (C) 2019-2022 J. Friedrich, W. Zimmermann, R. Keller
;   Hochschule Esslingen
;
;   Author:   	   J.Friedrich, W. Zimmermann
;   Last Modified: R. Keller, August 22, 2022
;
;   Usage:
;               JSR initLCD   --> Initialization
;                                 (Must be called once)
;
;               JSR writeLine --> Output a zero-termated string to LCD
;                                 Parameter:
;                                 X ... Pointer to string
;                                 B ... Row number (0 or 1)
;
;               JSR delay_10ms --> 10ms Delay (@24MHz bus clock)
;
;   Hardware interface of LCD display:
;   PORT K bit 0: Signal R/S    0=Command(instruction) 1=Data
;                               Indicates if output is a LCD command or data (ASCII character)
;          bit 1: Signal EN     1=Enable
;                               Toggled to 1 and back to 0 to generate a write signal for the LCD display
;                               (output R/S and data before toggling this bit)
;          bit 5...2: DB7...4   4bit Data bus
;                               The LCD Display uses a 4bit data bus.
;                               8bit values are transmitted as two 4bit nibbles
;                               in Big Endian sequence (higher 4bit first)
;
;   Internal operation of the LCD interface
;   The user can write commands (instructions) or data (ASCII characters) to the LCD display,
;   depending on the setting of the R/S signal. (The driver does not support reading back
;   data from the display).
;
;   The display can interprete a large number of commands, which are described in detail
;   in Hantronix's documentation LCD_Spec.pdf, page 44. Before data can be sent to the display,
;   it must be initialized via a sequence of commands. When writing to the LCD display,
;   several time delays have to be respected.
;
;   From a user's perspective, initialization is done by calling function initLCD(). Internally,
;   this function calls inidsp1() and inidsp2(), to write the required command sequence. After
;   initialization, the display is cleared.
;
;   After initialization, the user program can write strings to both lines of the LCD display
;   via function writeLine(). Before calling writeLine(), the user program has to copy a
;   point to the string into register X and the row number (0 or 1) in register B. The string
;   must be zero terminated.
;   Both rows of the LCD can display 16 characters. The output will start in the first column
;   and overwrite the previous output till the end of the row. If the string is longer than
;   16 characters, only the first 16 will be displayed.
;
;   Note: This driver does not show the cursor and does not provide any functions to move
;   the cursor or scroll the display horizontally or vertically. For the necessary command
;   sequences see the LCD's documentation if required.
;
; -----------------------------------------------------------------------------
;   LCD Display of the CodeWarrior debugger's True Time Simulation
;   The LCD display of the Dragon 12 Boards can be simulated,if you open the
;   LCD componente in the debugger (Component - Open - LCD)
;   and configure it: Right click on LCD - Setup - Data: 32 - Control: 0.
;   The simulated LCD display is not fully compatible with the LCD display
;   of the Dragon12 board. Therefore, the LCD driver has a special code section for the
;   simulated display, which must be activated. This is done via conditional assembly with
;   the symbol _HCS12_SERIALMON (defined when compiling for the MONITOR target (=real Dragon12
;   hardware) and symbol SIMULATOR (defined, when compiled for the SIMULATOR target).
  IFNDEF _HCS12_SERIALMON
    IFNDEF SIMULATOR 
SIMULATOR: EQU 1
    ENDIF
  ENDIF


; NOTE:  T H I S  S O F T W A R E  I S  B U G G Y
; This code has (at least) two bugs, which must be removed.
; Otherwise the software will not work as expected.

; export symbols
        XDEF initLCD, writeLine, delay_10ms

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; RAM: Variable data section
.data:  SECTION
reset_seq:
        ds.b 1
temp1:  ds.b 1

; ROM: Constant data
.const: SECTION

; Initialization command sequences
; Sequence 1 will output commands $3 - $3 - $3 - $2 as four nibbles to reset the LCD
; (see Hantroix LCD_Spec.pdf, pg. 4: Software Initialization for 4bit Interfaces
inidsp1:
  IFDEF  SIMULATOR
        dc.b 3          ; Nummer of commands
        dc.b $30        ; Reset char
        dc.b $30        ; Reset char
        dc.b $30        ; Reset char
  ELSE
        dc.b 2          ; Nummer of commands
        dc.b $33        ; Reset char
        dc.b $32        ; Reset char
  ENDIF
; Sequence 2 will output the commands described below
inidsp2:
        dc.b 4          ; Number of commands
  IFDEF  SIMULATOR
        dc.b $38        ; Command Function Set:    8 bit mode, 2 rows, 5 X 7 dot matrix
  ELSE
        dc.b $28        ; Command Function Set:    4 bit mode, 2 rows, 5 X 7 dot matrix
  ENDIF
        dc.b $0C        ; Command Display Control: display on, cursor off, non blinking
        dc.b $01        ; Command Clear display:   clear display memory, set cursor to home position
        dc.b $06        ; Command Entry Mode Set:  cursor increment, disable display shift

; Defines
ONE_MS:   equ   4000    ; 4000 x 250ns = 1 ms at 24 MHz bus speed
FIVE_MS:  equ   20000   ; 5 x above value
TEN_MS:   equ   40000   ; 10x above value
FIFTY_US: equ   200     ; 50 usecs = 200*250ns

LCD:      equ   PORTK   ; Port for LCD data bus
DATAMASK: equ   $3C     ; Bit 5...2 on LCD
REG_SEL:  equ   $01     ; Bit 0 on LCDCTRL: signal RS: 0=reg,    1=data

  IFDEF  SIMULATOR
        LCDCTRL:  equ   PORTA   ; Port LCD control signals
        ENABLE:   equ   $04     ; Bit 1 on LCDCTRL: signal E:  0=disable 1=enable,
  ELSE
        LCDCTRL:  equ   PORTK   ; Port LCD control signals
        ENABLE:   equ   $02     ; Bit 1 on LCDCTRL: signal E:  0=disable 1=enable,
  ENDIF

LCD_LINE0: equ   $80    ; LCD command: set cursor to begin of line 0 (Command Set Display Data RAM Address)
LCD_LINE1: equ   $C0    ; LCD command: set cursor to begin of line 1 (Command Set Display Data RAM Address)

; ROM: Code section
.init:  SECTION

;**************************************************************
; Public interface function: initLCD ... Initialize LCD (called once)
; Parameter: -
; Return:    -
initLCD:  pshd
          pshx

          jsr  delay_10ms

          movb #$ff, DDRK ; initialize port K as output
          movb #$00, LCDCTRL; ... and set to 0
  IFDEF  SIMULATOR        ; when running in debugger, vs. when running on real hardware
          movb #$ff, DDRA ; initialize port A as output
          movb #$00, LCD  ;   ... and set to 0
  ENDIF
          ldx  #inidsp1   ; x points to initialization command sequence 1
          movb #1, reset_seq; need more delay for first reset seq.

          jsr  sel_inst   ; --- output command sequence 1 ----
          ldab 0,x        ; get number of commands
          inx             ; x points to first command
inext1:   ldaa 0,x        ; get command
          jsr  outputByte ; initiate write pulse.
          inx             ; x points to next command
          jsr  delay_5ms  ; delay 5ms
          decb
          bne  inext1     ; if not last command, go to get next command
                          ; --- end of command sequence 1 ---

          ldx  #inidsp2   ; x points to initialization command sequence 2
          clr  reset_seq

          jsr  sel_inst     ; --- output command sequence 2 ---
          ldab 0,x          ; get number of commands
          inx               ; x points to first command
inext2:   ldaa 0,x          ; get command
          jsr  outputByte   ; initiate write pulse.
          inx               ; x points to next command
          decb
          bne  inext2       ; if not last command, go to get next command
          jsr  delay_5ms    ; delay 5ms
                            ; --- end of command sequence 2 ---
          pulx
          puld
          rts

;**************************************************************
; Public interface function: writeLine ... Write zero-terminated string to LCD
; Parameter: X ... pointer to string
;            B ... row number (0 or 1)
; Return:    -
writeLine:
          pshd
          pshx

          pshb
          jsr  sel_inst   ; select instruction
          pulb
          cmpb #1
          bne writeLine1
writeLine0:
          ldaa #LCD_LINE0 ; set cursor to begin of line 0
          bra  wDo
writeLine1:
          ldaa #LCD_LINE1 ; set cursor to begin of line 1
wDo:      jsr  outputByte

          jsr  sel_data   ; select data

msg_out:                  ; output the message character by character
          ldab #16        ; max. 16 characters
next:     ldaa 0,x        ; get character
          decb
          beq  wEnd       ; not more than 16 characters
          jsr  outputByte ; write character to LCD
          inx             ; continue with next character
          bra  next
wEnd:     pulx
          puld
          rts

;**************************************************************
; Public interface function: delay_10ms
; Parameter: -
; Return:    -
 delay_10ms:
          pshx
          ldx  #TEN_MS
          bsr  del1
          pulx
          rts

;**************************************************************
; The rest are private functions

; Internal function: delay_5ms
; Parameter: -
; Return:    -
delay_5ms:
          pshx
          ldx  #FIVE_MS
          bsr  del1
          pulx
          rts

;**************************************************************
; Internal function: delay_50us
; Parameter: -
; Return:    -
delay_50us:
          pshx
          ldx  #FIFTY_US
          bsr  del1
          pulx
          rts

;**************************************************************
; Internal function: 250ns delay at 24MHz bus speed
; Parameter: X ... number of loops, i.e. multiples of 250ns
; Return:    -
del1:     dex                   ; 1 cycle
          inx                   ; 1 cycle
          dex                   ; 1 cycle
          bne   del1            ; 3 cylce
          rts

;**************************************************************
; Set R/S=1, i.e. prepare for outputting data
; Parameter: -
; Return:    -
sel_data: bset LCDCTRL, REG_SEL
          rts

;**************************************************************
; Set R/S=0, i.e. prepare for outputting commands
; Parameter: -
; Return:    -
sel_inst: bclr LCDCTRL, REG_SEL
          rts

;**************************************************************
; Output single byte, split into two nibbles, to LCD display
; Parameter: a ... byte (data or command) to send to display
; Return:    -
  IFDEF  SIMULATOR
outputByte:
          bset LCDCTRL, ENABLE  ; set E = 1, i.e. write data to LCD
          staa LCD
          bclr LCDCTRL, ENABLE  ; set E = 0 again
          jsr  delay_50us       ; delay 50us
          rts
  ELSE
outputByte:
          psha              ; save it temporarily

          anda #$f0         ; upper nibble --> A.5...2
          lsra
          lsra              ;

          bclr LCD, DATAMASK; output data to PORTK.5..2 without
          bset LCDCTRL, ENABLE  ; set E = 1, i.e. write data to LCD
          oraa LCD          ; changing other bits in PORTK
          staa LCD          ; write data to LCD
          bclr LCDCTRL, ENABLE  ; set E = 0 again
          jsr  delay_50us       ; delay 50us

          ldaa reset_seq
          beq  wrtpls
          jsr  delay_5ms    ; delay for reset sequence
;
wrtpls:   pula              ; get the temporarily saved value
          anda #$0F         ; lower nibble --> A.5...2
          lsla
          lsla

          bclr LCD, DATAMASK; output data to PORTK.5..2 without
          bset LCDCTRL, ENABLE  ; set E = 1, i.e. write data to LCD
          oraa LCD          ; changing other bits in PORTK
          staa LCD          ; write data to LCD
          bclr LCDCTRL, ENABLE  ; set E = 0 again
          jsr  delay_50us       ; delay 50us

          rts
  ENDIF

