

delay_0_5sec:
    PSHY
    PSHX

    LDY #50
    del1:
        DEY 
        CPY #0
        LDX #4000
        BRA delay
        BNE del1

    PULY
    PULY
    RTS
    

delay:     
    dex                   ; 1 cycle
    inx                   ; 1 cycle
    dex                   ; 1 cycle
    bne   del1            ; 3 cylce
    rts