#include <avr/io.h>
#include <util/delay.h>

//analog_converter_init
void adc_set(){
	//voltage_ref
	ADMUX|=(1<<REFS0);
	//SET_prescaler
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//enable
	ADCSRA|=(1<<ADEN);

}

uint16_t AN_READ(uint8_t channel){
	//select_channel
	ADMUX|=(ADMUX&0xF0)|(channel<<MUX0);
	
	//converting
	ADCSRA|=(1<<ADSC);

	//wait
	while(ADCSRA&(1<<ADSC));

	//retrieve_val
	return(uint16_t)(ADCL|(ADCH<<8));

}


//usart_part

//init
void uart_init(){
	//baud_set
	UBRR0|=(uint8_t)(8>>8);
	UBRR0L|=(uint8_t)8;

	//enable_TR
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);

	//frame_set
	UCSR0C|=(3<<UCSZ00);
}


//sending_process:INT

//--------------conversion_section
// find_int_length
int num_length(uint16_t int_) {
	
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

	//sending_section:STR
	void transmit_(uint16_t num){
		char str_[num_length(num)+1];
		int_str(num,str_);
		for(int i=0; str_[i]!=0;i++){
			while(!(UCSR0A&(1<<UDRE0)));
			UDR0=(unsigned char)str_[i];

		}

	}




//8Bit_convert 
uint16_t scaling(uint16_t upper_MAX, uint16_t upper_MIN,uint16_t changes){
	int scaler=upper_MAX/upper_MIN;
	return (uint16_t)changes/scaler;
}


//PWM_section:
uint16_t PWM_set(){

	//enable_pwm_OC0A
	DDRD|=(1<<DDD6);
	//set_timer
	TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1);
	//PRE-SCALER
	TCCR0B|=(1<<CS00);

}

void PWM_send(uint16_t out_cmpREG){

	OCR0A=out_cmpREG;

}


int main(){

	uart_init();
	adc_set();
	PWM_set();

	while(1){

		uint16_t val_=AN_READ(0);

		PWM_send(scaling(1024,256,val_));
		transmit_(val_);
		_delay_ms(1000);

	}


	return 0;
}