#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// find_int_length
int num_length(int int_) {
	
    if (int_ / 10 > 0) return 1 + num_length(int_ / 10);
    else return 1;
}

// conversion_int_to_str
void int_str(int int_, char* str_) {

    int bag_1 = int_ % 10;
    int bag_2 = int_ / 10;

    if (bag_2 > 0)int_str(bag_2, str_);

    if((char)bag_2>=0x30 || (char)bag_2<=0x57){

	    *(str_ + (num_length(int_) - 1)) = '0' + bag_1;
	    *(str_ + num_length(int_)) = '\0';

	}

}

// init_uart
void init_uart() {
    // set_baudrate:9600
    UBRR0H = (uint8_t)(103 >> 8);
    UBRR0L = (uint8_t)103;

    // enable T&R
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

    // frame_set
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

// transmit
void transmit_int(int int_) {
    char str_[num_length(int_) + 1] = {};
    int_str(int_, str_);
    for (int i = 0; i < num_length(int_); i++) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = (unsigned char)str_[i];
    }
}

int main() {
    init_uart();

    //loop_
    while (1) {
        transmit_int(9999);
        _delay_ms(1000);
    }

    //esc
    return 0;
}