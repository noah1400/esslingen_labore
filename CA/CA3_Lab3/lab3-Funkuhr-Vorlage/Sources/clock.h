/*  Header for Clock module

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: -
*/

// Data type for clock events
typedef enum { NOCLOCKEVENT, SECONDTICK } CLOCKEVENT;

// Global variable holding the last clock event
extern CLOCKEVENT clockEvent;

// Public functions, for details see clock.c
void initClock(void);
void processEventsClock(CLOCKEVENT event);
void setClock(char hours, char minutes, char seconds);
void displayTimeClock(void);
