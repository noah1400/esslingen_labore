    XDEF initClock
    XDEF tickClock
    XDEF scnds, mins, hrs, time
    
    XREF initLED, clrLED, toggleLED
    XREF decToASCII
    XREF writeLine
    
.data: SECTION

scnds:    DS.B  1
scndsTXT: DS.B  3 ; e.g. 35 -> "35\n"
mins:     DS.B  1
minsTXT:  DS.B  3
hrs:      DS.B  1
hrsTXT:   DS.B  3

mode:       DS.B  1 ;0 = Normal Mode, 1 = Set Mode

time:  DS.B  9 ;HH:MM:SS\n 


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
  
  ; update output string
  JSR   updateTime
  
  ; output string
  JSR   outputTime
  
  PULB
  rts

exitTick:
  PULB
  rts
  
updateTime:
  CLRA
  LDAB  scnds
  JSR   decToASCII  ; ASCII String now in X
  LDY   #scndsTXT
  JSR   onlyLastTwoChars
  
  LDAB  mins
  JSR   decToASCII
  LDY   #minsTXT
  JSR   onlyLastTwoChars
  
  LDAB  hrs
  JSR   decToASCII
  LDY   #hrsTXT
  JSR   onlyLastTwoChars
  
  rts
  
outputTime:
  
  LDX   #time
  LDAB  #1
  JSR   writeLine 

  rts
  
  
onlyLastTwoChars:   ; decToASCII: "0035" -> "35"
  ; Register X: original String
  ; Register Y pointer to resulting string
  PSHB
  PSHA
  PSHX
  PSHY
  LDAB  #2 ; Counter to remove two characters
  lastTwoChars_loop:
     LDAA   2, X
     STAA   0, Y
     INX
     INY
     DECB
     BNE  lastTwoChars_loop
  CLRA        ; Set the null character
  STAA  0, Y  ; null terminate the resulting string
  
  PULY
  PULX
  PULA
  PULB
  rts
  
combineStrings:
   ; Uses  variables scndsTXT, minsTXT, hrsTXT
   ; And combines them to HH:MM:SS\n
   PSHB
   PSHA
   PSHX
   PSHY
   
   LDY  #time     ; Address to resulting string here time
   LDX  #hrsTXT   ; Address to first string
   JSR  combineStrings_loop
   LDX  #minsTXT  ; Address to second string
   JSR  combineStrings_loop
   LDX  #scndsTXT ; Address to last string
   JSR  combineStrings_loop
   JSR  combineStrings_loop_end
   
   PULY
   PULX
   PULA
   PULB
   
   rts
   
   combineStrings_loop:
      LDAA  0, X    ; Load a character from the current string
      CMPA  #0   ; Check if the end of the current string is reached
      BEQ   combineStrings_loop_rts ; If yes, exit and continue with next string
      
      STAA  0, Y    ; Store the character in the resulting string
      INX           ; Increment the current string pointer
      INY           ; Increment the resulting string pointer
      
      LDAA  #':'    ; Load the delimiter ":"
      STAA  0, Y    ; Store the delimiter in the resulting string
      INY           ; Increment the resulting string pointer
      
      BRA   combineStrings_loop ; Repeat for the next character
      
   combineStrings_loop_rts:
      rts
      
   combineStrings_loop_end:
      DEY           ; Decrement the resulting string pointer to remove the last delimiter ':'
      CLRA          ; Set the null character
      STAA  0, Y    ; Null terminate the resulting string
      rts
      
  
  

; ###########################################################
; tick section  
incrementAndCheckSecondOverflow:
  LDAB  scnds
  INCB
  STAB  scnds
  CMPB  #60
  BEQ   incrementAndCheckMinuteOverflow
  RTS
incrementAndCheckMinuteOverflow:
  ; seconds overflowed
  ; reset seconds
  LDAB  #0
  STAB  scnds
  ; increment minutes
  LDAB  mins
  INCB
  STAB  mins
  CMPB  #60
  BEQ   incrementAndCheckHourOverflow
  RTS
incrementAndCheckHourOverflow:
  ; minutes overflowed
  ; reset minutes
  LDAB  #0
  STAB  mins
  ; increment hours
  LDAB  hrs
  INCB
  STAB  hrs
  CMPB  #24
  BEQ   resetHours
  RTS
resetHours:
  ; hours overflowed
  ; reset hours
  LDAB  #0
  STAB  hrs
  RTS
; end tick section
; ###########################################################


  
