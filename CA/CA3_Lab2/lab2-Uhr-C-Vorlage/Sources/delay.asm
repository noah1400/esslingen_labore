;   Labor 1 
;   delay 0.5 sec
;   Subroutine hexToASCII
;
;   Computerarchitektur
;   (C) 2019-2022 J. Friedrich, W. Zimmermann, R. Keller
;   Hochschule Esslingen
;
;   Author:   Noah Scholz
;   Modified: Noah Scholz, May 2023

; export symbols
  XDEF delay_0_5sec

; Defines
SPEED:  EQU     $07D0                   ; Change this number to change counting speed

; ROM: Code section
.init: SECTION

; Public inferface function: hexToASCII
;   delay the program by 0.5 seconds
; Parameter:
;  Y    used as counter
;  X    used as counter
; Returns: -
; Registers: X, Y = 0
delay_0_5sec:
    LDX #SPEED          ; 2 cycles nur 1mal
    waitO:
      LDY #SPEED        ; 2 cycles x-mal
    waitI:
      DBNE Y, waitI     ; 3 cycles x-mal y-mal
      DBNE X, waitO     ; 3 cycles x-mal
      RTS               ; 5 cycles