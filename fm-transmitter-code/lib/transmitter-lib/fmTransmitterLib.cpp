#include <fmTransmitterLib.h>

void transmitter_setup(){
    pinMode(BL, OUTPUT);
}

void lcd_blink(){
    digitalWrite(BL, HIGH);
    delay(200);
    digitalWrite(BL, LOW);
    delay(200);
}