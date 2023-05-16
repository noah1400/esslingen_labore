;   Mixed mode C - Assembler programming
;   Assembler side module
;   For a description see Lab 2 manual appendix B
;
;
;   Computerarchitektur 3
;   (C) 2018 J. Friedrich, W. Zimmermann
;   Hochschule Esslingen
;
;   Author:   W.Zimmermann, July 19, 2017
;
;

;***** Export symbols ***********************************************

        XDEF var1A, var2A       ; Export ASM variables

        XDEF function1A         ; Export ASM functions
        XDEF function2A
        XDEF function3A


;***** Import symbols ***********************************************

        XREF var1C, var2C       ; Import C variables

        XREF function1C         ; Import C function
        XREF function2C_wrapper

;***** Include derivative specific macros ***************************
        INCLUDE 'mc9s12dp256.inc'

;***** Defines ******************************************************


;***** RAM: Variable data section ***********************************
.data:  SECTION

var1A:  DS.W    1               ; Declare ASM variables
var2A:  DS.B    1

;***** ROM: Constant data *******************************************
.const: SECTION

;***** Interrupt vector table ***************************************
.intVect: SECTION


;********************************************************************
;***** ROM: Code section ********************************************
.init:  SECTION
;********************************************************************

; Program code for ASM function (no parameters, no return value)
function1A:MOVW #$3344, var1A   ; Initialize assembler variables
           MOVB #$66, var2A

           LDD  var1C           ; Use C variables
           ADDD #1
           STD  var1C
           LDAB #$0F
           STAB var2C

           JSR function1C       ; Call C function (no params or return value)

           RTS



; Program code for ASM function (two 16bit parameters in regs X and Y, return value in D)
; and returns a 16bit value in D
;
; Parameters X  parameter a
;            Y  parameter b
; Returns    D  a + b

function2A:TFR  X, D
           EMUL                 ; Multiply D x Y --> (D, X)
           RTS                  ; Return lower 16 bit of product



; Function calls a C function via a wrapper (two parameters in X and Y, return value in D)
function3A:LDX  #$1111          ; Pass parameters in X and Y
           LDY  #$7788
                                ; Call C function (via wrapper)
           JSR  function2C_wrapper

           STD  var1A           ; Store return value in reg D
           RTS


