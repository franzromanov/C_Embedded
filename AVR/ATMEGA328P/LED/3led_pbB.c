#include <avr/io.h>
#include <util/delay.h>

//declare
uint8_t count=0,port[]={7,6,5};


int main(){
	//SET_OUT
	for(int i=0;i<3;i++){

		DDRD|=(1<<port[i]);
	}
	//SET_IN
	DDRB&=~(1<<DDB0);
	//PULLUP
	PORTB|=(1<<PORTB0);



	//main_task
	while(1){

		if(!(PINB & (1<<PINB0))){
			if(count==0){
				PORTD=0x0;
				count++;
			}
			if(count>0){
				PORTD=(1<<port[count-1]);
				count++;
			}
			if(count>4)count=0;
			_delay_ms(500);
		}

	}

	return 0;
}
