    XDEF initClock
    XDEF tickClock
    
    XREF initLED, clrLED, toggleLED
    
.data: SECTION

seconds:    DS.B  1
minutes:    DS.B  1
hours:      DS.B  1

mode:       DS.B  1 ;0 = Normal Mode, 1 = Set Mode

outputStr:  DS.B  9 ;HH:MM:SS\n 


.init: SECTION

initClock:
  JSR   initLED ; Initialize LEDs
  rts
  

tickClock:
  PSHB
  
  ; LED0 toggles once per second
  ; LED7 on in setmode
  
  ; toggling LED0
  LDAB  #$80
  JSR   toggleLED
  ; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  ; TODO: check correctness of setLED
  ; Output whole register B?
  ; Or just set single bits
  ; Same for clrLED
  ; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  LDAB  mode
  CMPB  #1
  BEQ   exitTick ; If in Set Mode exit tick
  
  ; tick clock
  ; Increment seconds
  JSR   incrementAndCheckSecondOverflow
  
  ; output string
  PULB
  rts
  
updateOutputStr:
  
  rts  

; ###########################################################
; tick section  
incrementAndCheckSecondOverflow:
  LDAB  seconds
  INCB
  STAB  seconds
  CMPB  #60
  BEQ   incrementAndCheckMinuteOverflow
  RTS
incrementAndCheckMinuteOverflow:
  ; seconds overflowed
  ; reset seconds
  LDAB  #0
  STAB  seconds
  ; increment minutes
  LDAB  minutes
  INCB
  STAB  minutes
  CMPB  #60
  BEQ   incrementAndCheckHourOverflow
  RTS
incrementAndCheckHourOverflow:
  ; minutes overflowed
  ; reset minutes
  LDAB  #0
  STAB  minutes
  ; increment hours
  LDAB  hours
  INCB
  STAB  hours
  CMPB  #24
  BEQ   resetHours
  RTS
resetHours:
  ; hours overflowed
  ; reset hours
  LDAB  #0
  STAB  hours
  RTS
; end tick section
; ###########################################################


  
exitTick:
  PULB
  rts