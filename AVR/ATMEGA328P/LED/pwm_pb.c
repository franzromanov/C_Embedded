#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

uint8_t count=0;
bool state=0;

void activate_pwm1(bool state){

	if(state==true){
		//set_timer
		//SET_OUT_REGISTER
		DDRD|=(1<<DDD6);
		//SET_TIMER_REG
		TCCR0A|=(1<<WGM01)|(1<<WGM00)|(1<<COM0A1);
		TCCR0B|=(1<<CS00);

	}

}

void pb_pwm(bool val, uint8_t* count){

	if(val==1){

   		(*count)++;
	    switch(*count){

	      case 1:
	      	activate_pwm1(1);
	        OCR0A=63;
	        (*count)++;
	        break;

	      case 2:
	        OCR0A=127;
	        (*count)++;
	        break;

	      case 3:
	        OCR0A=191;
	        (*count)++;
	        break;

	      case 4:
	        OCR0A=255;
	        (*count)++;
	        break;

	      case 5:
	        OCR0A=0;
	        DDRD=0x0;
	        (*count)=0;
	        break;

	    }
  }
}

int main (){
  	//SET_DDR
	DDRB&=~(1<<DDB0);
	//PULL_UP
	PORTB|=(1<<PORTB0);
	//activate_timer
	//state=1;
	//activate_pwm1(state);


	//main_task
	while(1){
		pb_pwm(!(PINB&(1<<PINB0)),&count);
    	_delay_ms(100);
	}


	return 0;
}
