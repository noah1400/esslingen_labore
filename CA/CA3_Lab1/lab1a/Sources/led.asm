

 .led: SECTION        
    initLED:
       
          MOVB    #$FF, DDRB  ; set data direction to output
          
          MOVB    #$00, PORTB ; turn off all leds
          
          RTC

    setLED: ; Parameter in register B
          
          STAB    PORTB  ; output register B
          
          RTC

    getLED: ; return value in register B
          
          LDAB    PORTB
          
          RTC
          
    toggleLED: ; leds to toggle in register B
          
          EORB    PORTB
          
          RTC