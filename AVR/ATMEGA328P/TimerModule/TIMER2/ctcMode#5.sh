#!/bin/bash

#compile
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o ctcMode#5.o ctcMode#5.c
avr-gcc -mmcu=atmega328p -o ctcMode#5 ctcMode#5.o
avr-objcopy -O ihex -R .eeprom ctcMode#5 ctcMode#5.hex

#flash
avrdude -V -F -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 - U flash:w:ctcMode#5.hex
