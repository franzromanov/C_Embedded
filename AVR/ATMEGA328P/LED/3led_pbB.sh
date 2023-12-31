#!/bin/bash

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o 3led_pbB.o 3led_pbB.c

avr-gcc -mmcu=atmega328p -o 3led_pbB 3led_pbB.o

avr-objcopy -O ihex -R .eeprom 3led_pbB 3led_pbB.hex

avrdude -F -V -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:3led_pbB.hex
