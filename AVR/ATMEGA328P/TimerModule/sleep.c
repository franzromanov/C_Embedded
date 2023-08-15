#include <avr/io.h>
#define CLCK 16000000
void ms_sleep(uint32_t period){
 
 //get_frequency
 uint32_t fout=1000/period;

 uint32_t count=(CLCK/(2*fout))-1;

 //setUp_timer
 OCR0A=count;//loadCompVal--->register
 TCCR0A=(0<<COM0A0)|(1<<WGM01);//wave_mode&&compareMode
 TCCR0B=(1<<CS00);//set_prescaler

 //flag_check
 while((TIFR0 & (1<<OCF0A))==0);//check_ifFlagExist
 TIFR0=(1<<OCF0A);
 TCCR0B=0x0;

}

//main
int main(){
 //set_DDR
 DDRD=(1<<DDD4);

while(1){
 
 //HIGH: 1 SECOND
 PORTD=(1<<PORTD4);
 ms_sleep(1000);

 //LOW: 1 SECOND
 PORTD=0x0;
 ms_sleep(1000);

}

//esc
 return 0;
}
