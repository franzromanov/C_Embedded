#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// find_int_length
int num_length(int int_);

// conversion_int_to_str
void int_str(int int_, char* str_);

//uart_init
void uart_set(uint32_t baud_rate);

//transmit_process
void prtscrn(void* type_, char* specifier);