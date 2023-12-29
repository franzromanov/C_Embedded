#include<avr/io.h>

int main(){


	//set_out[PORTD[7,6,5]]
	DDRD|=(1<<DDD7)|(1<<DDD6)|(1<<DDD5);
	//set_in[PORTB[5,4,3]]
	DDRB&=~(1<<DDB5)&~(1<<DDB4)&~(1<<DDB3);
	//PULLUP
	PORTB|=(1<<PORTB5)|(1<<PORTB4)|(1<<PORTB3);//LOW_LOGIC


	//main_task
	while(1){
		if(!(PINB & (1<<PINB5)))PORTD|=(1<<PORTD7);
		if(!(PINB & (1<<PINB4)))PORTD|=(1<<PORTD6);
		if(!(PINB & (1<<PINB3)))PORTD|=(1<<PORTD5);
		else PORTD=0x0;//OFF

	}

	return 0;
}
