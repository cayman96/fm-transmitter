/*
since everything is include in the fmTransmitterLib, the only thing called in setup() and loop() functions
are transmitter_setup() and frequencySwitchButtonHandler() functions.
*/

#include <fmTransmitterLib.h>
void setup() {
  transmitter_setup();
}

void loop() {
  frequencySwitchButtonHandler();
}
