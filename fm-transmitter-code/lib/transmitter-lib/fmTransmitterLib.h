#ifndef _FM_TRANSMITTER_H_
#define _FM_TRANSMITTER_H_

// including required libraries
#include <Arduino.h>
#include <Nokia_LCD.h>
#include <Adafruit_Si4713.h>
// defining pins for fm transmitter
#define SDA A4
#define SCL A5
#define FM_RST 13

// pin definition for lcd
#define LCD_RST 12
#define CE 11
#define BL 10
#define DC 9
#define DIN 8
#define CLK 7

//pin definition for buttons
#define BTN_RIGHT 4
#define BTN_MID 3
#define BTN_LEFT 2

#define FREQ_MIN 8750
#define FREQ_MAX 10800
#define DIM_TIME 5000


//lcd object declaration
extern Nokia_LCD lcd;

//time variables declaration
extern unsigned long currTime;
extern unsigned long backlightLightTime;
extern const unsigned long backlightDimTreshold;

//frequency variable declaration
extern unsigned short currFreq;
extern unsigned short freqChangeStep;

//button pressed tracker variables declaration
extern bool prevLBstate;
extern bool prevMBstate;
extern bool prevRBstate;

//functions declaration
void transmitter_setup();
void frequencySwitchButtonHandler();
void frequencySwitchAndLcdOutput(bool incFreq);
#endif