#include <avr/io.h>
#include <util/delay.h>

//pwm_section
void fpwm_init(){
	//set_DDR
	DDRD|=(1<<DDD6);
	//set_timer
	TCCR0A|=(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
	TCCR0B|=(1<<CS02)|(1<<CS00);
  	OCR0A=0;
}


int main(){

	fpwm_init();
  	while(1){
      for(int i=8;i<=38;i++){
        OCR0A=i;
        _delay_ms(40);

      }
      for(int i=38;i>=8;i--){
        OCR0A=i;
        _delay_ms(40);

      }

    }
	//esc
	return 0;
}