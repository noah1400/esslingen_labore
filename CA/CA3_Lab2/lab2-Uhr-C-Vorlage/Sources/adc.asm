    XDEF initADC
    XDEF convertADC
    
    XREF decToASCII
    
    INCLUDE 'mc9s12dp256.inc'
    

.data: SECTION
  ;initial_measure: ds.w 1
  degree_string: ds.b 7 ;wrongly formatted string
 

.init: SECTION

initADC:
  MOVB #$C0, ATD0CTL2 ; Enable ATD, no interrupt
  MOVB #$08, ATD0CTL3 ; Single conversion only
  MOVB #$05, ATD0CTL4 ; 10 bit, 2 MHz ATD0 clock
  rts
  

convertADC:

  MOVB #$87, ATD0CTL5 ; Start conversion on channel 7

wait1:
;Wait for End of Conversion (EOC), busy waiting:
  BRCLR ATD0STAT0, #$80, wait1
  LDD ATD0DR0 ; Read conversion result à D  




;######################### Calculation happens here ##################################
  
  ;STD #initial_measure ;to view value in debugger

;Register D holds 10 bit analog value
  
  LDX #4
  IDIV 
  ;DIVIDE with 4 because 10 bits -> we are working with 8 bit registers
  TFR X, A
    
  LDAB #100  ;multiply by 100
  MUL
    
  ;now divide by 1023
  LDX #1023
  IDIV ;X holds result
    
  TFR X, D
    
    
  ;undo division from before by multiplying
    
  LDAA #4
  MUL
    
  SUBD #30
  
;################################################################################
  

;convert to ASCII String (wrongly formatted)
  LDX #degree_string
  JSR decToASCII
     
    
  ;LDY #result_string
  JSR formatString
  nop

  ;LDY #result_string
  RTS 

   
  
  
  
  
formatString:

  LDAA #' '  
  STAA 1, Y+
  
  LDAA 1, X+  ;copy sign
  STAA 1, Y+
    
  LDAA 3, +X  ;copy first digit
  STAA 1, Y+
    
  LDAA 1, +X  ;second digit
  STAA 1, Y+
    
  
    
  LDAA #'C'
  STAA 1, Y+
    
  LDAA #'°'
  STAA 1, Y+
    
  LDAA #0    ;null terminator
  STAA 1, Y+
  RTS






  

  
