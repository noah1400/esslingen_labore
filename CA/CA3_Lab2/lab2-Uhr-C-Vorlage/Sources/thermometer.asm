    XDEF initThermo
    XDEF updateThermo
    XDEF temp
    
    XREF initADC
    XREF convertADC
    XREF writeLine
   
    
    INCLUDE 'mc9s12dp256.inc'
    



.data: SECTION
temp_string: ds.b 7
temp: ds.b 7 ;correctly formatted string


.init: SECTION

initThermo:
  JSR initADC  
  rts
  

updateThermo: ;once per second convertADC is called
  PSHB
  PSHY
  PSHX
  
  LDY #temp
  JSR convertADC
  
  ;LDX #temp
  ;LDAB  #1
  ;JSR writeLine

  PULX
  PULY
  PULB
 
  rts
  

  
