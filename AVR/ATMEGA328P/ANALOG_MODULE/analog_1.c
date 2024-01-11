#include <avr/io.h>
#include <util/delay.h>

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


/*

--------------ADC_CONVERTER---------------
-configure pin
-configure ADC
-select reference Voltage 
-select ADC prescaler
-Start Conversion
-wait_for_Conversion
-read_result
-------------------------------------------
*/

//func
void ADC_INIT(){

	//ref_voltage
	ADMUX|=(1<<REFS0);
	//set_prescaler
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//ENABLE_ADC
	ADCSRA|=(1<<ADEN);	


}

uint16_t analogRead(uint8_t channel){
	//select_channel
	ADMUX|=(ADMUX&0xF0)|(channel<<MUX0);
	//start_conversion
	ADCSRA|=(1<<ADSC);
	//wait_conversion
	while(ADCSRA&(1<<ADSC));
	return(uint16_t)(ADCL|(ADCH<<8));

}
void uart_set(){
	//baud
	UBRR0H=(uint8_t)(8>>8);
	UBRR0L=(uint8_t)8;

	//enable_T/R
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);

	//bit_frame
	UCSR0C|=(3<<UCSZ00);
}

void transmit_(char* text){

	for(int i=0; i!='\0';i++){
		while(!(UCSR0A&(UDRE0)));
		UDR0=(unsigned char)text[i];
	}


}


char str_[256];
uint16_t adc_;
//main_parts
int main(){
	uart_set();
	ADC_INIT();

	while(1){
		adc_=analogRead(0);
		int_str(adc_,str_);
		transmit_(str_);
	}


	return 0;
}
