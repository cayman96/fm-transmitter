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

//lcd object declaration
extern Nokia_LCD lcd;

//time variables declaration
extern unsigned long currTime;
extern unsigned long backlightLightTime;
extern const unsigned long backlightDimTreshold;

//functions declaration
void transmitter_setup();
void lcd_blink();
void button_lcd_output_test();
void btn_screen_changer(int pin, int x, int y);


#endif