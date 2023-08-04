#!/bin/bash
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o ctcMode#1.o ctcMode#1.c
avr-gcc -mmcu=atmega328p -o ctcMode#1 ctcMode#1.o
avr-objcopy -O ihex -R .eeprom ctcMode#1 ctcMode#1.hex
avrdude -V -F -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:ctcMode#1.hex
