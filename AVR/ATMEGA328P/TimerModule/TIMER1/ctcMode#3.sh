#!/bin/bash 
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o ctcMode#3.o ctcMode#3.c
avr-gcc -mmcu=atmega328p -o ctcMode#3 ctcMode#3.o
avr-objcopy -O ihex -R .eeprom  ctcMode#3 ctcMode#3.hex
avrdude -V -F -c arduino -p atmega328p  -P /dev/ttyACM0 -b 115200 -U flash:w:ctcMode#3.hex

