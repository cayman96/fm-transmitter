# fm-transmitter
A simple FM transmitter with Arduino Nano, Nokia 5110 screen and Adafruit SI4713 module.
Written in **C/C++** with schematics in .fzz file that can be opened with Fritzing.

## Functions

The circuit functions as follows:
- During the boot, it initializes the screen and the transmitter module,
- if it is the first boot, it loads default transmit frequency at 100 MHz,
- the functions transmits the output from the audio jack on transmitter module,
- the frequency can be set from 88 MHz to 108 MHz with 1 MHz steps - left and right buttons,
- new default frequency can be set with middle button,
- the module can be powered by 18650 Li-Ion cell and USB.


## To be done
It's pretty much done, maybe I'll do some bug fixes if necessary.
