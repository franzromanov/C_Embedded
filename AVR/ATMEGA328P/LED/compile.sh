#!/bin/bash

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led_func.o led_func.c

avr-gcc -mmcu=atmega328p -o led_func led_func.o

avr-objcopy -O ihex -R .eeprom led_func led_func.hex

avrdude -F -V -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:led_func.hex
