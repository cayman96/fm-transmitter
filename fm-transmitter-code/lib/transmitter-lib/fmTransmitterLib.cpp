#include <fmTransmitterLib.h>

Nokia_LCD lcd(CLK, DIN, DC, CE, LCD_RST);
Adafruit_Si4713 radio = Adafruit_Si4713(FM_RST);
unsigned long currTime;
unsigned long backlightLightTime;
unsigned long defaultFreqMsgTime;
unsigned short currFreq;
bool prevLBstate;
bool prevMBstate;
bool prevRBstate;

void freqToMHzConvertAndDisplay(unsigned short freq){
    int freqToMHz = currFreq / 100;
    if (freqToMHz <= 99){
        lcd.setCursor(22, 3);
        lcd.print(" ");
        lcd.setCursor(28, 3);
    } else {
        lcd.setCursor(22, 3);
    }
    lcd.print(freqToMHz);
}

void transmitter_setup(){
    radio.begin();
    currFreq = EEPROM.read(0) * 100;
    if (currFreq == 0){
        currFreq = 10000;
    }
    currTime = millis();
    pinMode(BL, OUTPUT);
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_MID, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    prevLBstate = digitalRead(BTN_LEFT);
    prevMBstate = digitalRead(BTN_MID);
    prevRBstate = digitalRead(BTN_RIGHT);
    for(int i = 0; i <=100; i++){
        analogWrite(BL, i);
        delay(1);
    }
    lcd.begin();
    lcd.setContrast(60);
    lcd.clear();
    lcd.setCursor(20, 1);
    lcd.print("Frequency");
    freqToMHzConvertAndDisplay(currFreq);
    lcd.setCursor(40, 3);
    lcd.print(".00 MHz");
    radio.setTXpower(115);
    radio.tuneFM(currFreq);
    radio.beginRDS();
}

void frequencySwitchButtonHandler(){
    if (!digitalRead(BTN_RIGHT) && digitalRead(BTN_LEFT) != prevLBstate){
        if(digitalRead(BTN_LEFT)) frequencySwitchAndLcdOutput(false);
    } 
    else if (!digitalRead(BTN_LEFT) && digitalRead(BTN_RIGHT) != prevRBstate){
        if(digitalRead(BTN_RIGHT)) frequencySwitchAndLcdOutput(true);
    }
    else if (!digitalRead(BTN_LEFT) && !digitalRead(BTN_RIGHT) && digitalRead(BTN_MID) != prevMBstate){
        if(digitalRead(BTN_MID)) {
            EEPROM.update(0, currFreq/100);
            analogWrite(BL, 100);
            lcd.setCursor(10, 5);
            lcd.print("Freq saved!");
            backlightLightTime = currTime;
            defaultFreqMsgTime = currTime;
        }
    }
    prevLBstate = digitalRead(BTN_LEFT);
    prevMBstate = digitalRead(BTN_MID);
    prevRBstate = digitalRead(BTN_RIGHT);
    currTime = millis();
    if (currTime - backlightLightTime >=  DIM_TIME){
        analogWrite(BL, 0);
    }
    if (currTime - defaultFreqMsgTime >= DEF_SET_TIME){
        lcd.setCursor(10,5);
        lcd.print("           ");
    }
}

void frequencySwitchAndLcdOutput(bool incFreq){
    unsigned short tempFreq;
    if (incFreq){
            tempFreq = currFreq + FREQ_STEP;
        } 
    else {
            tempFreq = currFreq - FREQ_STEP;
        }
    if(tempFreq >= FREQ_MIN && tempFreq <= FREQ_MAX){
        currFreq = tempFreq;
        radio.tuneFM(currFreq);
        freqToMHzConvertAndDisplay(currFreq);
    }
    analogWrite(BL, 100);
    backlightLightTime = currTime;
};