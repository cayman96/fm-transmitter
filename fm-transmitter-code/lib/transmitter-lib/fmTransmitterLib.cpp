#include <fmTransmitterLib.h>

Nokia_LCD lcd(CLK, DIN, DC, CE, LCD_RST);
unsigned long currTime;
unsigned long backlightLightTime;
const unsigned long backlightDimTreshold = 5000;

void transmitter_setup(){
    currTime = millis();
    pinMode(BL, OUTPUT);
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_MID, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    lcd.begin();
    lcd.setContrast(60);
    lcd.clear();
    lcd.setCursor(30, 1);
    lcd.print("Test");
    lcd.setCursor(4, 2);
    lcd.print("Dzaju to chuj");
}

// test function for simple backlight fading in and out
void lcd_blink(){
    for(int i = 0; i < 255; i++){
        analogWrite(BL, i);
        delay(20);
    }
    for(int i = 255; i > 0; i--){
        analogWrite(BL, i);
        delay(20);
    }
}

//test function for buttons read and writing output to the screen
void button_lcd_output_test(){
    btn_screen_changer(BTN_LEFT, 20, 3);
    btn_screen_changer(BTN_MID, 40, 3);
    btn_screen_changer(BTN_RIGHT, 60, 3);
    currTime = millis();
    if (currTime - backlightLightTime >=  backlightDimTreshold){
        analogWrite(BL, 0);
    }
}

void btn_screen_changer(int pin, int x, int y){
    if (digitalRead(pin) == HIGH){
        lcd.setCursor(x, y);
        lcd.print("1");
        analogWrite(BL, 100);
        backlightLightTime = currTime;
    } else {
        lcd.setCursor(x, y);
        lcd.print("0");
    }
}