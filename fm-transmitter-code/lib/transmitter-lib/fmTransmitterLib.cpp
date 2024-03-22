#include <fmTransmitterLib.h>

Nokia_LCD lcd(CLK, DIN, DC, CE, LCD_RST);


void transmitter_setup(){
    pinMode(BL, OUTPUT);
    lcd.begin();
    lcd.setContrast(60);
    lcd.clear();
    lcd.setCursor(30, 1);
    lcd.print("Test");
}

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