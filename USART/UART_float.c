#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

void set_uart(){

	//bd_rate
	UBRR0H=(uint8_t)(103>>8);
	UBRR0L=(uint8_t)103;

	//enable T&R
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);

	//frame_set
	UCSR0C|=(3<<UCSZ00);

}




void transmit_float(float float_){
	char str_[256]={};
	dtostrf(float_, 5, 5, str_);
	for(int i=0; i<strlen(str_);i++){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0=(unsigned char)str_[i];	
	}
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=(unsigned char)'\n';
}


float num_=23.4567;

int main(){

	set_uart();

	while(1){

		transmit_float(num_);
		_delay_ms(1000);

	}

	return 0;
}