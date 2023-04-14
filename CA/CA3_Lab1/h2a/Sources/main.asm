;  Computerarchitektur
;   (C) 2019-2022 J. Friedrich, W. Zimmermann, R. Keller
;   Hochschule Esslingen
;
;   Author:   R. Keller, Jul 4, 2019
;            (based on code provided by J. Friedrich, W. Zimmermann)
;   Modified: -
;

; export symbols
        XDEF Entry, main

; import symbols
        XREF  __SEG_END_SSTACK           ; End of stack
        XREF  hexToASCII

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION

; ROM: Constant data
.const: SECTION
 

; ROM: Code section
.init:  SECTION

main:                                   ; Begin of the program
Entry:

      LDS   #__SEG_END_SSTACK
      CLI
        
      LDD   #$F018
         
      JSR   hexToASCII
      
      nop  
