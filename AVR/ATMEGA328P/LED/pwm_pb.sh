#!/bin/bash
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o pwm_pb.o pwm_pb.c
avr-gcc -mmcu=atmega328p -o pwm_pb pwm_pb.o
avr-objcopy -O ihex -R .eeprom pwm_pb pwm_pb.hex
avrdude -V -F -c arduino -p atmega328p -P /dev/ttyACM* -b 115200 -U flash:w:pwm_pb.hex
