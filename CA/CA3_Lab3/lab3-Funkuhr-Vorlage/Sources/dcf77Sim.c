/*  Simulation of the DCF77 impulse signals
    for testing the radio signal clock withoud DCF77 radio signal receiver.

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: -

    Function readPort() must be called periodically once every 10ms. The function returns
    the value of the (simulated) DCF77 impulse signal. The simulation provides a time range
    of 8 minutes, then the signals repeat.
*/


long dcf77Data[16] =
{
    0x46120000, 0x005C2492,				// DCF77 simulation data        12:31 09.01.2017
    0x56320000, 0x005C2492,
    0x56520000, 0x005C2492,
    0x46720000, 0x005C2492,
    0x56920000, 0x005C2492,
    0x46B20000, 0x005C2492,
    0x46D20000, 0x005C2492,
    0x56F20000, 0x005C2492
};
int dcf77DataMin = 8;                   // ... for 8 minutes

char readPortSim(void)
{   static int i10ms = 9;               // Time counter, counts  10ms increments of a 100ms period
    static int i100ms =9;               //               counts 100ms increments of a 1s    period
    static int iSec  = 50;              //               counts 1s    increments of a 1min  period
    static int iMin  = 0;
    char signal = 0x01;                 // Default output signal is a High

    i10ms  = (i10ms +1) % 10;           // Update the time counters
    if (i10ms == 0)
    {   i100ms = (i100ms+1) % 10;
        if (i100ms == 0)
        {   iSec = (iSec + 1) % 60;
            if (iSec == 0)
                iMin = (iMin + 1) % 60;
        }

    }

    if (iSec < 59)                      // If it is not the last second of a minute
    {   if (i100ms < 1)                 // ... and if we are at the first 100ms of a second
        {   signal = 0;                 // ...... output Low
        } else if (i100ms < 2)          // ... if we are at the second 200ms of a second
        {   char n = (char) (iMin % dcf77DataMin);
            char i = (char) (iSec / 32);
            char j = (char) (iSec % 32);
            long temp = dcf77Data[n*2+i];
            temp = (temp >> j) & 0x01;
            if (temp)                   // ...... and if the data bit is 1 output another Low
                signal = 0;
        }
    }
    return signal;
}

void initializePortSim(void)
{
}