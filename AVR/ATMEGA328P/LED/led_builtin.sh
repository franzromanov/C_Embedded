#!//bin/bash
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led_builtin.o led_builtin.c
avr-gcc -mmcu=atmega328p -o led_builtin led_builtin.o
avr-objcopy  -O ihex -R .eeprom led_builtin led_builtin.hex
avrdude -F -V -c arduino -p atmega328p -P /dev/ttyACM* -b 115200 -U flash:w:led_builtin.hex
