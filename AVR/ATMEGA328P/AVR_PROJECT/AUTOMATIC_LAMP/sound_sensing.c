#include <sound_sensing.h>


uint16_t Analoghear(uint8_t adc_pin){

	//adc_init
	ADMUX=0;
	ADMUX|=(1<<6);
	ADMUX|=adc_pin;
	ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	ADCSRA|=(1<<ADEN);

	//start_readings
	ADCSRA|=(1<<ADSC);
	while(ADCSRA&(1<<ADSC));

	//return_adc
	return ADC;
}


uint8_t db_react(uint8_t adc_pin){
	float voltage_in=Analoghear(adc_pin)*(5/1023);
	float max_volt=,min_volt=;//kalibrasi spl
	if(voltage_in>=min_volt && voltage_in<=max_volt)return 1;
	else return 0;
}
