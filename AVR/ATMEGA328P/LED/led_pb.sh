#!/bin/bash
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o -c led_pb.o led_pb.c
avr-gcc -mmcu=atmega328p -o led_pb led_pb.o
avr-objcopy -O ihex -R .eeprom led_pb led_pb.hex
avrdude -V -F -c arduino -P /dev/ttyACM* -b 115200 -U flash:w:led_pb.hex
