/* 
as good practice says, if we don't want this to be called multiple times
and allow program to cause havoc, we use #ifndef...#endif
to only call the library once 
*/

#ifndef _FM_TRANSMITTER_H_
#define _FM_TRANSMITTER_H_

/*
including required libraries for our Adafruit Si4713 transmitter 
and Nokia 5510 LCD to work, as well as Arduino.h for essential Arduino functions to work
and EEPROM.h for our EEPROM read/write handling 
*/

#include <Arduino.h>
#include <Nokia_LCD.h>
#include <Adafruit_Si4713.h>
#include <EEPROM.h>

/*
defining pins for fm transmitter - we need to at least define pins 
for SDA and SCL - courtesy of the Si4713 using I2C for communication with the board
and its reset pin - it'll be later used for its initiation in the code
*/

#define SDA A4
#define SCL A5
#define FM_RST 13

/*
pin definition for lcd - as usual, it requires reset pn, CE, DC, DIN and CLK pins.
BL pin also required, but we won't use it to declare Nokia_LCD object later on
since we'll be using PWM to control the backlight brightness
*/

#define LCD_RST 12
#define CE 11
#define BL 10
#define DC 9
#define DIN 8
#define CLK 7

/*
pin definition for buttons - the control scheme is simple:
left button - decreade broadcast frequency, right button - increase broadcast frequency,
middle button - save current frequency as default one, loaded at boot
*/

#define BTN_RIGHT 4
#define BTN_MID 3
#define BTN_LEFT 2

/*
reset pin definition - it resets the circuit, funcion used when transmitter does not work from cold boot
*/

#define RST_PIN 6
extern bool shouldNotReset;
/*
constants for maximum and minimum frequency (interpreted in kHz),frequency change step (also in kHz),
backlight dim timeout (in miliseconds) and default set message disappear timeout (also in nanoseconds)
*/

#define FREQ_MIN 8800
#define FREQ_MAX 10800
#define FREQ_STEP 100
#define DIM_TIME 5000
#define DEF_SET_TIME 2500


// lcd object declaration - later this object will be used for Nokia LCD control

extern Nokia_LCD lcd;

/*
radio object declaration - our main star of this project, this object will be used 
for setting up, broadcasting and switching frequencies
*/

extern Adafruit_Si4713 radio;

/*
time variables declaration for tracking current time passed since board boot,
capturing at which time backlight has been lit for further determination when it should be shut down
and capturing at which time message about saving 
*/

extern unsigned long currTime;
extern unsigned long backlightLightTime;
extern unsigned long defaultFreqMsgTime;

//frequency variable declaration - holds currently used frequency

extern unsigned short currFreq;

/*
button pressed tracker variables declaration - 
used for tracking previous button push states
*/

extern bool prevLBstate;
extern bool prevMBstate;
extern bool prevRBstate;

/*
remember that all the variables/constants that are not functions or #define directives
must be declared here as extern - otherwise the .cpp file and the program will not know
about those variables and due to that the compliation will fail
*/

//functions declaration - functions used by the program, explained in .cpp file

void freqToMHzConverter(unsigned short freq);
void transmitter_setup();
void frequencySwitchButtonHandler();
void frequencySwitchAndLcdOutput(bool incFreq);
void backlightFadeIn();
#endif