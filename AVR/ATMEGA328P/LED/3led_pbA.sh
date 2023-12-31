#!/bin/bash

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o 3led_pbA.o 3led_pbA.c

avr-gcc -mmcu=atmega328p -o 3led_pbA 3led_pbA.o

avr-objcopy -O ihex -R .eeprom 3led_pbA 3led_pbA.hex

avrdude -F -V -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:3led_pbA.hex
