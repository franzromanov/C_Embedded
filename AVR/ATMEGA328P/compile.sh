#!/bin/bash

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c

avr-gcc -o led_func.bin led.o

avr-objcopy -O ihex -R .eeprom led.bin led.hex

#avrdude -F -V -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex
