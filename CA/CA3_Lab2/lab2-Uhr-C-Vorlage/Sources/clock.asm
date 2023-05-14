    XDEF initClock
    XDEF tickClock
    XDEF scnds, mins, hrs, time
    
    XREF initLED, clrLED, toggleLED
    XREF decToASCII
    XREF writeLine
    
    INCLUDE 'mc9s12dp256.inc'
    
    SELECT12HOURS: equ 1
    
.data: SECTION

scnds:    DS.B  1
scndsTXT: DS.B  3 ; e.g. 35 -> "35\n"
mins:     DS.B  1
minsTXT:  DS.B  3
hrs:      DS.B  1
hrsTXT:   DS.B  3

tempTXT:  DS.B  7

mode:       DS.B  1 ;0 = Normal Mode, 1 = Set Mode



  IF SELECT12HOURS == 1
     time:  DS.B  11 ;HH:MM:SSam\n
     am:  DS.B  1 ; AM?
  ELSE
     time:  DS.B  9 ;HH:MM:SS\n
  ENDIF

 
.const: SECTION


.init: SECTION

;**************************************************************
; Public interface function: initClock ... Initialize Clock (called once)
; Parameter: -
; Return:    -
initClock:
  JSR   initLED ; Initialize LEDs
  
  PSHA
  LDAA  #12
  STAA  hrs
  LDAA  #59
  STAA  mins
  LDAA  #59
  STAA  scnds
  LDAA  #1
  STAA  am
  PULA
  
  rts
  
;**************************************************************
; Public interface function: tickClock ... called every second
; Parameter: -
; Return:    -
;
; BEGIN SECTION TICKCLOCK
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
  LDX   #tempTXT
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
  
  JSR   combineStrings
  
  rts
  
outputTime:
  
  LDX   #time
  LDAB  #1
  JSR   writeLine 

  rts
;
; END SECTION TICKCLOCK
;**************************************************************


  
;**************************************************************
; Private function: Returns the last two chars of a string returned by decToASCII
; Parameter:  X ... Pointer to string returned by decToASCII " 00035"
;             Y ... Pointer to where the resulting string should be stored
; Return:     -
;
; BEGIN SECTION LASTTWOCHARS  
onlyLastTwoChars:   ; decToASCII: "0035" -> "35"
  ; Register X: original String
  ; Register Y pointer to resulting string
  PSHB
  PSHA
  PSHX
  PSHY
  LDAB  #2 ; Counter to remove two characters
  INX      ; Skip two characters
  INX
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
;
; END SECTION LASTTWOCHARS  
;**************************************************************


  
;**************************************************************
; Internal function: Combines seconds, mins, hrs to time string
; Updates time variable
; Parameter:  -
; Return:     -
;
; BEGIN SECTION COMBINESTRINGS  
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
      BEQ   combineStrings_loop_delimiter ; If yes, add delimiter, exit and continue with next string
      
      STAA  0, Y    ; Store the character in the resulting string
      INX           ; Increment the current string pointer
      INY           ; Increment the resulting string pointer
      
      BRA   combineStrings_loop ; Repeat for the next character
      
   combineStrings_loop_delimiter:
      LDAA  #':'    ; Load the delimiter ":"
      STAA  0, Y    ; Store the delimiter in the resulting string
      INY           ; Increment the resulting string pointer
      rts
      
   combineStrings_loop_end:
      DEY           ; Decrement the resulting string pointer to remove the last delimiter ':'
      IF SELECT12HOURS == 1
           JSR  addAMPM
      ENDIF
      CLRA          ; Set the null character
      STAA  0, Y    ; Null terminate the resulting string
      rts
      
   IF SELECT12HOURS == 1
   addAMPM:
      LDAA  am            ; Load am variable
      CMPA  #1            ; Check if am is set
      BEQ   addAM         ; If yes branch
      addPM:
      LDAA  #'p'          ; Load 'p'
      BRA   addAMPM_end
      addAM:
      LDAA  #'a'          ; Load 'a'
      addAMPM_end:
      STAA  0, Y          ; Store previous character ( 'a' or 'b' ) in resulting string
      INY                 ; Increase resulting string pointer
      LDAA  #'m'          ; Load 'm'
      STAA  0, Y          ; Store 'm' in resulting string
      INY
      rts
   ENDIF
;
; END SECTION COMBINESTRINGS  
;**************************************************************      
  
  

;**************************************************************
; Internal functions to increase clock value
;
; BEGIN SECTION OVERFLOW  
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
  IF SELECT12HOURS==0
    CMPB #24
    BEQ   resetHours
  ELSE
    LDAA  am  ; load am variable
    CMPA  #0
    BEQ   checkPMOverflow
    checkAMOverflow:
      CMPB  #13
      BEQ   am12to13_overflow   ; hours overflowed from 12 to 13; 12:59:59am -> 01:00:00am
      CMPB  #12
      BEQ   am11to12_overflow   ; hours overflowed from 11 to 12; 11:59:59am -> 12:00:00pm
      BRA   AMPMOverflow_end    ; no overflow
    
      am11to12_overflow:        ; keep hrs the same but change am to pm
        LDAA  #0
        STAA  am
        BRA   AMPMOverflow_end
      
      am12to13_overflow:        ; stay with AM but set hrs to 1
        LDAA  #1                
        STAA  hrs
        BRA   AMPMOverflow_end
    
    checkPMOverflow:
      CMPB  #13
      BEQ   pm12to13_overflow   ; hours overflowed from 12 to 13; 12:59:59pm -> 01:00:00pm
      CMPB  #12
      BEQ   pm11to12_overflow   ; hours overflowed from 11 to 12; 11:59:59pm -> 12:00:00am 
      BRA   AMPMOverflow_end
      
      pm11to12_overflow:        ; keep hrs the same but change from pm to am
        LDAA  #1
        STAA  am
        BRA   AMPMOverflow_end  
      
      pm12to13_overflow:        ; stay with pm but set hrs to 1
        LDAA  #1
        STAA  hrs
        ; BRA AMPMOverflow_end
        
    
    AMPMOverflow_end:
  ENDIF
  RTS
  
  IF SELECT12HOURS==0 
  
resetHours:
  ; hours overflowed
  ; reset hours
  LDAB  #0
  STAB  hrs
  RTS
  
  ENDIF
;
; END SECTION OVERFLOW  
;**************************************************************

  
