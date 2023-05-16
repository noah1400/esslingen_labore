    XDEF  decToASCII
    
    POSITIVE_SIGN:   equ   ' '
    NEGATIVE_SIGN:   equ   '-'
    DIGIT_OFFSET:    equ   '0'
 
.data: SECTION
  val:    DS.W  1 

.const: SECTION

.init: SECTION


  ; Description: This assembly function converts a 16-bit value passed in register D 
  ;              to its corresponding integer string representation and 
  ;              saves it to the location pointed to by the string pointer passed in register x.

  ; Parameters:

  ; Register D: A 16-bit value to be converted to its integer string representation.
  ; Register x: A pointer to a string where the resulting integer string will be stored.

  decToASCII:
    ; Save registers to stack
    PSHA
    PSHY
    PSHB
    PSHD
    PSHX  ; Save beginning of string
    
    STD   val
    
    ; Check sign of val
    TFR   D, Y
    CPY   #0
    BPL   decToASCII_positive
    BRA   decToASCII_negative
    
    
  decToASCII_positive:
    ; add positve sign ( #' ' )
    LDAA  #POSITIVE_SIGN
    STAA  1, X+
    BRA   decToASCII_loop
  
  decToASCII_negative:
    ; add negative sign ( #'-' )
    LDAA  #NEGATIVE_SIGN
    STAA  1, X+
    ; negate
    LDD val
    COMA
    COMB
    ADDD #1
    
    STD val    
    
    ; BRA   decToASCII_loop
    
  decToASCII_loop:
    LDD   val
    TFR   X, Y          ; backup string pointer
    LDX   #10000        ; set divisor
    IDIV                ; divide
    STD   val           ; store remainder in val
    TFR   X, A          ; transfer x to a
    ADDA  #DIGIT_OFFSET ; add offset
    STAA  1, Y+         ; append A to string
    
    LDD   val
    LDX   #1000
    IDIV
    STD   val
    TFR   X, A
    ADDA  #DIGIT_OFFSET
    STAA  1, Y+
    
    LDD   val
    LDX   #100
    IDIV
    STD   val
    TFR   X, A
    ADDA  #DIGIT_OFFSET
    STAA  1, Y+
    
    LDD   val
    LDX   #10
    IDIV
    STD   val
    TFR   X, A
    ADDA  #DIGIT_OFFSET
    STAA  1, Y+
    
    LDD   val
    ANDB  #$000F
    ADDB  #DIGIT_OFFSET
    STAB  1, Y+
    CLRA
    STAA  0, Y
    
       
    PULX  ; Restore beginning of string
    PULD
    PULB
    PULY
    PULA
    RTS