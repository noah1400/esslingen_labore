 XDEF delay_0_5sec

delay_0_5sec:

    PSHX      ; push x to stack
    PSHY      ; push y to stack
    
    LDY       #50000
    LDX       #20
    delay_loop:
    DBNE      Y, delay_loop
    LDY       #50000
    DBNE      X, delay_loop
    
    PULY      ; restore y and x by pulling from stack
    PULX
    
    RTS       ;  return from subroutine