  XDEF  initLED, setLED, getLED, toggleLED, clrLED
  XREF  PORTB, DDRB, DDRJ, PTJ
  
  .data: SECTION
  
  .const: SECTION

 .init: SECTION        
    initLED:

          MOVW    #$FF, DDRJ
          MOVW    #2, PTJ
       
          MOVB    #$FF, DDRB  ; set data direction to output
          
          MOVB    #$00, PORTB ; turn off all leds
          
          RTS

    setLED: ; Parameter in register B
          
          STAB    PORTB  ; output register B
          
          
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