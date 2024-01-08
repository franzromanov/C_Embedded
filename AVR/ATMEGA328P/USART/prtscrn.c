//#include "prtscrn.h"
#include <avr/io.h>


// find_int_length
int num_length(int int_) {
    if (int_ / 10 > 0) return 1 + num_length(int_ / 10);
    else return 1;
}
/*
.
.
.
*/
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
/*
.
.
*/
//uart_init
void uart_set(uint32_t baud_rate){
	//initiate
	uint8_t baud_code=(uint32_t)16000000/(16*baud_rate);
	//register_section
	//baud
	UBRR0H|=(baud_code>>8);
	UBRR0L|=baud_code;

	//enable T&R
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);

	//frame_set
	UCSR0C|=(3<<UCSZ00);
}
/*
.
.
.
.
*/
//uart_transmit
void prtscrn(void* type_, char* specifier){
	char data[256]={};
	uint8_t set=0;
	uint8_t len_;
	char* specifier_[]={"int","float","char","str"};
	len_=sizeof(specifier_)/2;
	for(uint8_t i=0;i<len_;i++){
		if(strcmp(*(specifier_+i),specifier)==0){
			set=i;
			break;
		}
	}

	switch(set){
		case  0:		
			int_str(*((int*)type_),data);
			len_=strlen(data);
			for(int i=0; i<len_;i++){
				while(!(UCSR0A&(1<<UDRE0)));
				UDR0=(unsigned char)(*(data+i));
			}
			break;

		case 1:
			dtostrf(*((float*)type_),5,5,data);
			len_=strlen(data);
			for(int i=0; i<len_;i++){
				while(!(UCSR0A&(1<<UDRE0)));
				UDR0=(unsigned char)(*(data+i));
			}
			break;

		case 2:
			while(!(UCSR0A&(1<<UDRE0)));
			UDR0= *((unsigned char*)type_);
			break;

		case 3:
			char *str=(char*)type_;
			len_=strlen(type_);
			for(int i=0; i<len_;i++){
				while(!(UCSR0A&(1<<UDRE0)));
				UDR0=(unsigned char)(*(str+i));
			}
			break;
	}

}
