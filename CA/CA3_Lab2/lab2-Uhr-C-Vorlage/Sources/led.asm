  XDEF  initLED, setLED, getLED, toggleLED, clrLED, setBitsLED, clrBitsLED
  
  INCLUDE 'mc9s12dp256.inc'
  
  
  .data: SECTION
  
  .const: SECTION

 .init: SECTION        
    initLED:

          BSET    DDRJ, #2
          BCLR    PTJ,  #2
       
          MOVB    #$FF, DDRB  ; set data direction to output
          
          MOVB    #$00, PORTB ; turn off all leds
          
          RTS

    setLED: ; Parameter in register B
          
          STAB    PORTB  ; output register B
          
          
          RTS
          
    setBitsLED:
    
          ORAB    PORTB
          
          STAB    PORTB
    
          RTS

    getLED: ; return value in register B
          
          LDAB    PORTB
          
          RTS
          
    toggleLED: ; leds to toggle in register B
          
          EORB    PORTB
          
          STAB    PORTB
          
          RTS
          
    clrLED:
          LDAB    #$00
          STAB    PORTB
          RTS
          
    clrBitsLED:
    
        COMB
        ANDB    PORTB
        STAB    PORTB
        RTS