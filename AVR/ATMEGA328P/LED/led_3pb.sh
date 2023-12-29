#!/bin/bash


avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led_3pb.o led_3pb.c
avr-gcc -mmcu=atmega328p -o led_3pb led_3pb.o
avr-objcopy -O ihex -R .eeprom led_3pb led_3pb.hex
avrdude -V -F -c arduino -p atmega328p -P /dev/ttyACM* -b 115200 -U flash:w:led_3pb.hex
