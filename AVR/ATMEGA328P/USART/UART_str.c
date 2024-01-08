//add_lib
#include <avr/io.h>
#include <util/delay.h>


//UART_INIT
void uart_set(){
	//set_baud_rate:115200
	UBRR0H=(uint8_t)(103>>8);
	UBRR0L=(uint8_t)103;

	//enable_T&R
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);

	//DATA_FRAME:8 BIT :: 1 STOP_BIT
	UCSR0C|=(1<<UCSZ00);
}

//transmit_char_type
void transmit_char(unsigned char char_){

	while(!(UCSR0A & (1<<UDRE0)));//wait_for_empty_buffer
	UDR0=char_;//if_buffer_empty_putOnBuffer
}

//str_fragmentation
void transmit_str(char *str_){
	for(int i=0;str_[i]!='\0';i++)transmit_char((unsigned char*)(*(str_+i)));

}

//main_parts
int main(){
	//init
	uart_set()

	while(1){
		//send_text
		transmit_str("hello_world\n");
	}
	
	//esc
	return 0;
}