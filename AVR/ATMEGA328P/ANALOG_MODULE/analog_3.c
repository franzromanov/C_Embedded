#include <avr/io.h>
#include <util/delay.h>

//func_===============================

//8Bit_convert 
uint16_t scaling(uint16_t upper_MAX, uint16_t upper_MIN,uint16_t changes){
	int scaler=upper_MAX/upper_MIN;
	return (uint16_t)changes/scaler;
}

// find_int_length
uint16_t num_length(uint16_t int_) {
	
    if (int_ / 10 > 0) return 1 + num_length(int_ / 10);
    else return 1;
}

// conversion_int_to_str
void int_str(uint16_t int_, char* str_) {

    uint16_t bag_1 = int_ % 10;
    uint16_t bag_2 = int_ / 10;

    if (bag_2 > 0)int_str(bag_2, str_);

    if((char)bag_2>=0x30 || (char)bag_2<=0x57){

	    *(str_ + (num_length(int_) - 1)) = '0' + bag_1;
	    *(str_ + num_length(int_)) = '\0';

	}

}

//uart_init
void uart_set(){
	//baud_rate
	UBRR0H=(uint8_t)(8>>8);
	UBRR0L=8;
	//enable_TxR
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
	//frame_set
	UCSR0C|=(3<<UCSZ00);
}

//timer_set
void pwm_mode(){
	//timer_session
	//FAST_MODE_5[ prescaler_&_mode_pick ]-----TIMER_1
	TCCR1A|=(1<<COM1A1)|(1<<WGM10)|(1<<COM1B1);//OCR1A_&_OCR1B
	TCCR1B|=(1<<CS10)|(1<<WGM12);

	//TIMER_2[PRESCALER_&_MODE_PICK]
	TCCR2A|=(1<<COM2A1)|(1<<WGM21)|(1<<WGM20);
	TCCR2B|=(1<<CS20);
}

//ADC_INIT
void adc_init(){
	//set_voltage_ref
	ADMUX|=(1<<REFS0);
	//set_channel
	ADMUX|=(ADMUX&0xF0)|(0<<MUX0);
	//set_prescaler
	ADCSRA|=(7<<ADPS0)|(1<<ADEN);
}


uint16_t AN_READ(){
	//start_conversion
	ADCSRA|=(1<<ADSC);
	//Wait_for_conversion
	while(ADCSRA&(1<<ADSC));
	return(uint16_t)(ADCL|(ADCH<<8));
}


void transmit_uart(char* str){
	for(int i=0;str[i]!='\0';i++){
		while(!(UCSR0A&(1<<UDRE0)));
		UDR0=(unsigned char)str[i];
	}
}

void play_(uint16_t AN_val){
	//LED_SESSION
	uint8_t conv = (uint8_t)scaling(1024,256,AN_val);
	if(conv<=63){
		DDRB|=(1<<DDB1);
		DDRB&=(0<<DDB2)|(0<<DDB3);
		OCR1A=conv;
	}if(conv>63 && conv<=127){
		DDRB|=(1<<DDB2);
		DDRB&=(0<<DDB1)|(0<<DDB3);
		OCR1B=conv;
	}if(conv>127 && conv<=255){
		DDRB|=(1<<DDB3);
		DDRB&=(0<<DDB2)|(0<<DDB1);
		OCR2A=conv;
	}

	//serial_comms_session
	char str_[num_length(conv)];
	int_str(conv, str_);
	transmit_uart(str_);
  transmit_uart("\n");

}





//end=======================================

//main_parts
int main(){
	//init
	uart_set();
	pwm_mode();
	adc_init();

	//infinite_loop
	while(1){
		uint16_t AN_IN=AN_READ();
		//_delay_ms(50);
		play_(AN_IN);
	}

	//esc
	return 0;
}