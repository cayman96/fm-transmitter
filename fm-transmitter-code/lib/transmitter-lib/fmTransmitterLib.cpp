#include <fmTransmitterLib.h>

Nokia_LCD lcd(CLK, DIN, DC, CE, LCD_RST);
unsigned long currTime;
unsigned long backlightLightTime;
unsigned short currFreq = 10000;
unsigned short freqChangeStep = 100;
bool prevLBstate;
bool prevMBstate;
bool prevRBstate;

void transmitter_setup(){
    currTime = millis();
    pinMode(BL, OUTPUT);
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_MID, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    prevLBstate = digitalRead(BTN_LEFT);
    prevMBstate = digitalRead(BTN_MID);
    prevRBstate = digitalRead(BTN_RIGHT);
    lcd.begin();
    lcd.setContrast(60);
    lcd.clear();
    lcd.setCursor(20, 1);
    lcd.print("Frequency");
    lcd.setCursor(60, 3);
    lcd.print("MHz");
    
}

void frequencySwitchButtonHandler(){
    if (!digitalRead(BTN_RIGHT) && digitalRead(BTN_LEFT) != prevLBstate){
        if(digitalRead(BTN_LEFT)) frequencySwitchAndLcdOutput(false);
    } 
    if (!digitalRead(BTN_LEFT) && digitalRead(BTN_RIGHT) != prevRBstate){
        if(digitalRead(BTN_RIGHT)) frequencySwitchAndLcdOutput(true);
    }
    prevLBstate = digitalRead(BTN_LEFT);
    prevMBstate = digitalRead(BTN_MID);
    prevRBstate = digitalRead(BTN_RIGHT);
    currTime = millis();
    if (currTime - backlightLightTime >=  DIM_TIME){
        analogWrite(BL, 0);
    }
}

void frequencySwitchAndLcdOutput(bool incFreq){
    unsigned short tempFreq;
    if (incFreq){
            tempFreq = currFreq + freqChangeStep;
        } 
    else {
            tempFreq = currFreq - freqChangeStep;
        }
    if(tempFreq >= FREQ_MIN && tempFreq <= FREQ_MAX){
        currFreq = tempFreq;
        double freqToMHz = currFreq / 100;
        lcd.setCursor(22, 3);
        lcd.print(freqToMHz);
    }
    analogWrite(BL, 100);
    backlightLightTime = currTime;
};