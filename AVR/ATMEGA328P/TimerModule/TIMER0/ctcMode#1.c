//TCCR0A>>>TIMER 0>>>OCR0A>>>OC0A
#include <avr/io.h>
#define CLCK 16000000UL

//declare
void _TIMER0_OC0A_WAVE1(uint16_t prescaler,uint32_t fout){
 //configure_countValue
 uint32_t count=(CLCK/(2*prescaler*fout))-1;

 //setUp_timer
 OCR0A=count;//loadCompVal--->register
 TCCR0A=(1<<COM0A0)|(1<<WGM01);
 switch(prescaler){
  case 1:
   TCCR0B=(1<<CS00);
   break;
  case 8:
   TCCR0B=(1<<CS01);
   break;
  case 64:
   TCCR0B=(1<<CS00)|(1<<CS01);
   break;
  case 256:
   TCCR0B=(1<<CS02);
   break;
  case 1024:
   TCCR0B=(1<<CS02)|(1<<CS00);
   break;
}
 //flag_check
 while((TIFR0 & (1<<OCF0A))==0);//check_ifFlagExist
 TIFR0=(1<<OCF0A);//CLEAR_FLAG>>>TOGGLE_VALUE>>>START_ANEW
//end
}

//main
int main(){
 DDRD=(1<<DDD6);
 while(1){
  _TIMER0_OC0A_WAVE1(1,100000);

}
//esc
 return 0;
}
