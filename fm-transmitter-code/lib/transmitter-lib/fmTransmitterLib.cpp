/*
first, importing out fmTransmitterLib which will check if declared functions and variables
are matched to what is in the .h file content. Also, it imports everything that is declared
in #define directives.
*/ 

#include <fmTransmitterLib.h>

// declaring the Nokia_LCD object, this time with pin declaration.

Nokia_LCD lcd(CLK, DIN, DC, CE, LCD_RST);

//declaring Adafruit_Si4713 with reset pin declaration

Adafruit_Si4713 radio = Adafruit_Si4713(FM_RST);

//initializing, but not assigning variables for time tracking, current frequency and button states

unsigned long currTime;
unsigned long backlightLightTime;
unsigned long defaultFreqMsgTime;
unsigned short currFreq;
bool prevLBstate;
bool prevMBstate;
bool prevRBstate;
bool shouldNotReset;

// function converting kHz to MHz for displaying on the screen 
void freqToMHzConvertAndDisplay(unsigned short freq){
    int freqToMHz = currFreq / 100; // convert kHz to MHz by dividing by 100
    /*
    if MHz below 100, to prevent one digit from staying frozen on the screen and wrongly displaying, 
    for example 199 MHz - replace first digit at cursor position x 22 y 3 with empty space
    */
    if (freqToMHz <= 99){
        lcd.setCursor(22, 3);
        lcd.print(" ");
        lcd.setCursor(28, 3);
    } else {
        lcd.setCursor(22, 3);
    }
    lcd.print(freqToMHz); // display converted MHz value
}

void transmitter_setup(){
    currTime = millis();
    pinMode(BL, OUTPUT);
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_MID, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    // get default button press states
    prevLBstate = digitalRead(BTN_LEFT);
    prevMBstate = digitalRead(BTN_MID);
    prevRBstate = digitalRead(BTN_RIGHT);
    // initialize radio
    radio.reset(); // THIS is the actual fix for the radio not playing from cold boot - and with frequency not loading!!!
    radio.begin();
    // initialize lcd, set contrast and clear the screen
    lcd.begin();
    lcd.setContrast(60);
    lcd.clear();
    // writing out default frequency to the screen
    // neat fluent backlight lit sequence, for the sake of bootup
    backlightFadeIn();
    currFreq = EEPROM.read(0) * 100; // read EEPROM value at address 0 and multiply it by 100 to match kHz rate
    // if value read from EEPROM does not match between min and max frequencies, set default at 10000 kHz
    if (currFreq < FREQ_MIN && currFreq > FREQ_MAX){
        currFreq = 10000;
    }
    lcd.setCursor(20,0);
    lcd.setCursor(20, 1);
    lcd.print("Frequency");
    freqToMHzConvertAndDisplay(currFreq);
    lcd.setCursor(40, 3);
    lcd.print(".00 MHz");
    //set radio to the loaded frequency
    radio.tuneFM(currFreq);
    // begin broadcasting
    radio.beginRDS();
    // setting transmission power to MAX = 115dB, according to the Si4713 documentation
    radio.setTXpower(115);
}

/*
function watching and handling button presses, what it does 
for left and right I'll describe below, in frequencySwitchAndLcdOutput
*/ 
void frequencySwitchButtonHandler(){
    if (!digitalRead(BTN_RIGHT) && digitalRead(BTN_LEFT) != prevLBstate){
        if(digitalRead(BTN_LEFT)) frequencySwitchAndLcdOutput(false);
    } 
    else if (!digitalRead(BTN_LEFT) && digitalRead(BTN_RIGHT) != prevRBstate){
        if(digitalRead(BTN_RIGHT)) frequencySwitchAndLcdOutput(true);
    }
    else if (!digitalRead(BTN_LEFT) && !digitalRead(BTN_RIGHT) && digitalRead(BTN_MID) != prevMBstate){
        if(digitalRead(BTN_MID)) {
            // updates EEPROM value at address 0 with current frequency divided by 100
            EEPROM.update(0, currFreq/100);
            analogWrite(BL, 100); // lights up the display
            // prints message about default freq saved
            lcd.setCursor(10, 5);
            lcd.print("Freq saved!");
            // saves at which time screen has been lit and message has been shown
            backlightLightTime = currTime;
            defaultFreqMsgTime = currTime;
        }
    }
    prevLBstate = digitalRead(BTN_LEFT);
    prevMBstate = digitalRead(BTN_MID);
    prevRBstate = digitalRead(BTN_RIGHT);
    // gets current time and determines whether backlight should be dimmed and default message should disappear
    currTime = millis();
    if (currTime - backlightLightTime >=  DIM_TIME){
        analogWrite(BL, 0);
    }
    if (currTime - defaultFreqMsgTime >= DEF_SET_TIME){
        lcd.setCursor(10,5);
        // since Nokia_LCD.h has no function clearing single lines, I'm just replacing it with blank spaces
        lcd.print("           ");
    }
}

// function changing current frequency and tuning radio adequately to it
void frequencySwitchAndLcdOutput(bool incFreq){
    // declaring temporary variable for holding new frequency
    unsigned short tempFreq;
    /*
    the incFreq is set depends on which button is pressed. if left = 0, if right = 1
    thus, if 0 - decrease frequency by FREQ_STEP, 1 = increase by FREQ_STEP
    */
    if (incFreq){
            tempFreq = currFreq + FREQ_STEP;
        } 
    else {
            tempFreq = currFreq - FREQ_STEP;
        }
    /*
    checking if new frequency is between min and max, if yes - save it to currFreq, tune radio to it
    and display new frequency on the screen in place of old one
    */
    if(tempFreq >= FREQ_MIN && tempFreq <= FREQ_MAX){
        currFreq = tempFreq;
        radio.tuneFM(currFreq);
        freqToMHzConvertAndDisplay(currFreq);
    }
    // light up screen and track at which time it was lit
    analogWrite(BL, 100);
    backlightLightTime = currTime;
};

void backlightFadeIn(){
    for(int i = 0; i <=100; i++){
        analogWrite(BL, i);
        delay(1);
    }
};