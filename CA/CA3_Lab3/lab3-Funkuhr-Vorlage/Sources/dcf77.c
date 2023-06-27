/*  Radio signal clock - DCF77 Module

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: -
*/

/*
; A C H T U N G:  D I E S E  S O F T W A R E  I S T  U N V O L L S T ? N D I G
; Dieses Modul enth?lt nur Funktionsrahmen, die von Ihnen ausprogrammiert werden
; sollen.
*/


#include <hidef.h>                                      // Common defines
#include <mc9s12dp256.h>                                // CPU specific defines
#include <stdio.h>

#include "dcf77.h"
#include "led.h"
#include "clock.h"
#include "lcd.h"

//defines
#define LED0 0x01
#define LED1 0x02
#define LED2 0x04
#define LED3 0x08 

// Global variable holding the last DCF77 event
DCF77EVENT dcf77Event = NODCF77EVENT;
int dataOK = 0;
char lastSig = 0;
int Tlow = 0;
int Tpulse = 0;
int Tcur = 0;
int timedata[60];
int secCounter = 0;
const char dow[8][4] = { {"ERR"}, {"Mon"}, {"Tue"}, {"Wed"}, {"Thu"}, {"Fri"}, {"Sat"}, {"Sun"}};
unsigned char us_on = 0;
const int maxDayofMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


// Modul internal global variables
static int  dcf77Dow = 6, dcf77Year=2017, dcf77Month=1, dcf77Day=1, dcf77Hour=0, dcf77Minute=0;       //dcf77 Date and time as integer values

// Prototypes of functions simulation DCF77 signals, when testing without
// a DCF77 radio signal receiver
void initializePortSim(void);                   // Use instead of initializePort() for testing
char readPortSim(void);                         // Use instead of readPort() for testing

// ****************************************************************************
// Initalize the hardware port on which the DCF77 signal is connected as input
// Parameter:   -
// Returns:     -
void initializePort(void) {
  DDRH = 0x00; // Port H as input
  PIEH = 0x00; // no Interrupts
}

// ****************************************************************************
// Read the hardware port on which the DCF77 signal is connected as input
// Parameter:   -
// Returns:     0 if signal is Low, >0 if signal is High
char readPort(void) {
  if(PTH & 0x01) {
    return 1;
  } 
  else {  
    return 0;
  }
}

// ****************************************************************************
//  Initialize DCF77 module
//  Called once before using the module
void initDCF77(void)
{   setClock((char) dcf77Hour, (char) dcf77Minute, 0);
    displayDateDcf77();
    initializePortSim();
    //initializePort();
}

// ****************************************************************************
// Display the date derived from the DCF77 signal on the LCD display, line 1
// Parameter:   -
// Returns:     -
void displayDateDcf77(void)
{   char date[32];
    
    (void) sprintf(date, "%s: %02d.%02d.%04d", dow[dcf77Dow], dcf77Day, dcf77Month, dcf77Year);
    writeLine(date, 1);
}

// ****************************************************************************
//  Read and evaluate DCF77 signal and detect events
//  Must be called by user every 10ms
//  Parameter:  Current CPU time base in milliseconds
//  Returns:    DCF77 event, i.e. second pulse, 0 or 1 data bit or minute marker
DCF77EVENT sampleSignalDCF77(int currentTime) {
    DCF77EVENT event = NODCF77EVENT;
    
    char signal = readPortSim() | readPort();
    
    //char signal = readPort(); // For real Board use readPort() <------------------------------------------------------------------
    
    
    //clrLED(LED2);
    
    if (signal != lastSig && signal == 0) {         // signal is low - falling edge
        Tpulse = currentTime - Tcur;
        Tcur = currentTime;
        Tlow = 0;
        setLED(LED1);
        
        if (Tpulse >= 900 && Tpulse <= 1100) {           // check if window is 1sec
            event = VALIDSECOND;
        } 
        else if (Tpulse >= 1900 && Tpulse <= 2100) {     // check if Window is 2 sec --> Min has passed
            event = VALIDMINUTE;
        } 
        else {
            //setLED(LED2);                                 // Error detected
            event = INVALID;
        }
    } 
    else if (signal != lastSig && signal > 0) {
        Tlow = currentTime - Tcur;
        clrLED(LED1);  
        if (Tlow >= 70 && Tlow <= 130) {
            event = VALIDZERO;
        } 
        else if (Tlow >= 170 && Tlow <= 230) {
            event = VALIDONE;
        } 
        else {
            //setLED(LED2);                                 // Error detected
            event = INVALID;
        }      
    }
    lastSig = signal;
    return event;
}


// ****************************************************************************
// Process the DCF77 events
// Contains the DCF77 state machine
// Parameter:   Result of sampleSignalDCF77 as parameter
// Returns:     -
void processEventsDCF77(DCF77EVENT event) {
  if(event == VALIDONE) {
    timedata[secCounter] = 1;
  } 
  else if(event == VALIDZERO) {
    timedata[secCounter] = 0;
  } 
  else if(event == VALIDSECOND) {
    secCounter++;
  }
  else if(event == INVALID) {
    timedata[secCounter] = -1;
  } 
  else if(event == VALIDMINUTE) {
    secCounter = 0;
    eventMinute();
    if(dataOK) {
      if(us_on) {
        USDE();
      }
    setClock(dcf77Hour, dcf77Minute, 0); 
    displayDateDcf77();
    }
  }
}

// ****************************************************************************
// Handles a VALIDMINUTE event
// Parameter:
// Returns:     
void eventMinute(void) {
  int bitValue[] = {1, 2, 4, 8, 10, 20, 40, 80};
  int i = 0;     
  int cnt = 0;
  int year = 2000;
  int month = 0;
  int dow = 0; //DayOfWeek
  int day = 0;
  int hours = 0;
  int min = 0;
  int parMin = 0;
  int parHrs = 0;
  int parDat = 0;
  
  //Decode Year
  for(i = 50; i <= 57; i++) {
    if(timedata[i]) {
      year = year + bitValue[cnt];
    }
    cnt++;
  }
  cnt = 0;
  
  //Decode Month
  for(i = 45; i <= 49; i++) {
    if(timedata[i]) {
      month = month + bitValue[cnt];
    }
    cnt++;
  }
  cnt = 0;
  //Check Month
  if(month < 1 || month > 12) {
    dataOK = -1;
    setLED(LED2);
  }
  
  //Decode DayOfWeek
  for(i = 42; i <= 44; i++) {
    if(timedata[i]) {
      dow = dow + bitValue[cnt];
    }
    cnt++;
  }
  cnt = 0;
  //Check DayOfWeek
  if(dow < 1 || dow > 7) {
    dataOK = -1;
    setLED(LED2);
  }
  
  //Decode Day
  for(i = 36; i <= 41; i++) {
    if(timedata[i]) {
      day = day + bitValue[cnt];
    }
    cnt++;
  }
  cnt = 0;
  //Check Day
  if(day < 1 || day > 31) {
    dataOK = -1;
    setLED(LED2);
  }
  
  //Decode Hours
  for(i = 29; i <= 34; i++) {
    if(timedata[i]) {
      hours = hours + bitValue[cnt];
    }
    cnt++;
  }
  cnt = 0;
  //Check Hours
  if(hours < 0 || hours > 23) {
    dataOK = -1;
    setLED(LED2);
  }
  
  //Decode Minutes
  for(i = 21; i <= 27; i++) {
    if(timedata[i]) {
      min = min + bitValue[cnt];
    }
    cnt++;
  }
  cnt = 0;
  //Check Minutes
  if(min < 0 || min > 59) {
    dataOK = -1;
    setLED(LED2);
  }
  
  //Parity Check
  //Parity Check Minutes
  for(i = 21; i <= 27; i++) {
    parMin = parMin + timedata[i];
  }
  //Parity Check Hours
  for(i = 29; i <= 34; i++) {
    parHrs = parHrs + timedata[i];
  }
  //Parity Check Date
  for(i = 36; i <= 57; i++) {
    parDat = parDat + timedata[i];
  }
   
  if(parMin % 2 == timedata[28] && parHrs % 2 == timedata[35] && parDat % 2 == timedata[58] && dataOK != -1) {
    dcf77Year = year;
    dcf77Month = month;
    dcf77Dow = dow;
    dcf77Day = day;
    dcf77Hour = hours;
    dcf77Minute = min;
    clrLED(LED2);
    setLED(LED3);
    dataOK = 1;
  } 
  else {
    clrLED(LED3);
    setLED(LED2);
    dataOK = 0;
  }
}

// ****************************************************************************
// Check if H.3 is pressed
// Parameter:  
// Returns:
void USDE_Pressed() {
  if(PTH & 0x08) {      // '~PTH' for board!!!
          us_on = ~us_on;
          USDE();          
          setClock(dcf77Hour, dcf77Minute, secCounter);
          displayDateDcf77();
  }         
}

// ****************************************************************************
// Change US and DE Time
// Check if H.3 is pressed to do so
// Parameter:  
// Returns:
void USDE(int tempVal) { 
  if(us_on) {                     
    if(dcf77Hour < 6) {         
      dcf77Hour += 18;
      if(dcf77Dow < 2) {
        dcf77Dow = 7;
      } 
      else {
        dcf77Dow--;
      }
      if(dcf77Day < 2) {       
        if(dcf77Month < 2) {
          dcf77Year--;
          dcf77Month = 12;
          dcf77Day = 31;
        } 
        else {
          dcf77Month--;
          if(dcf77Year % 4 == 0 && dcf77Year % 1000 != 0 && dcf77Month == 2) {
            dcf77Day = 29;
          } 
          else if(dcf77Month == 1) {
            dcf77Day = 31;
          }
          else if(dcf77Month == 2) {
            dcf77Day = 28;
          }
          else if(dcf77Month == 3) {
            dcf77Day = 31;
          }
          else if(dcf77Month == 4) {
            dcf77Day = 30;
          }
          else if(dcf77Month == 5) {
            dcf77Day = 31;
          }
          else if(dcf77Month == 6) {
            dcf77Day = 30;
          }
          else if(dcf77Month == 7) {
            dcf77Day = 31;
          }
          else if(dcf77Month == 8) {
            dcf77Day = 31;
          }
          else if(dcf77Month == 9) {
            dcf77Day = 30;      
          }
          else if(dcf77Month == 10) {
            dcf77Day = 31;
          }
          else if(dcf77Month == 11) {
            dcf77Day = 30;
          }
          else if(dcf77Month == 12) {
            dcf77Day = 31;
          }
        }
      }         
    }
    else {
      dcf77Hour -= 6;      
    }
  } 
  else {
    if(dcf77Hour > 17) {
      dcf77Hour -= 18;
      dcf77Day++;
      if(dcf77Dow > 6) {
        dcf77Dow = 1;
      }
      else {
        dcf77Dow--;
      }
      if(dcf77Day > maxDayofMonth[dcf77Month]) {
        if(dcf77Month > 11) {
          dcf77Month = 1;
          dcf77Year++;
          dcf77Day = 1;
        }
        else {
          dcf77Month++;          
        }
      }
    }
    else {
      dcf77Hour += 6;
    }     
  }
}
 


