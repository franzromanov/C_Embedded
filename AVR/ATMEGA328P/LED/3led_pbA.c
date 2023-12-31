#include <avr/io.h>
#include <util/delay.h>
//declare
uint8_t count=0,port[]={7,6,5};

int main(){

	//set_out
	DDRD|=(1<<DDD7)|(1<<DDD6)|(1<<DDD5);
	//set_in
	DDRB&=~(1<<DDB0);
	//pullup:LOW_LOGIC
	PORTB|=(1<<PORTB0);


	//loop
	while(1){

		if(!(PINB & (1<<PINB0))){
			count++;
			PORTD=(1<<port[count-1]);
			_delay_ms(1000);
			}else PORTD=0x0;

		if(count==3)count=0;

	}

	return 0;
}
