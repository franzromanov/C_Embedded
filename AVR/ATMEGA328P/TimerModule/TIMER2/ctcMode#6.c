//WELCOME_codename:IGNIS
#include <avr/io.h>
#define CLCK 16000000UL

//func
void _TIMER2_0C2B_WAVE2(uint16_t prescaler,uint32_t fout){
//start

 //get_CompVal
 uint32_t comp_val=(CLCK/(2*prescaler*fout))-1;
 
 //load_OutputCompareRegister
 OCR2A=comp_val;

 //setUp_TimerRegister
 TCCR2A=(1<<WGM21)|(1<<COM2B0);

 //prescaler_set
 switch(prescaler){

  case 1:
   TCCR2B=(1<<CS20);
   break;

  case 8:
   TCCR2B=(1<<CS21);
   break;

  case 32:
   TCCR2B=(1<<CS20)|(1<<CS21);
   break;

  case 64:
   TCCR2B=(1<<CS22);
   break;

  case 128:
   TCCR2B=(1<<CS20)|(1<<CS22);
   break;

  case 256:
   TCCR2B=(1<<CS21)|(1<<CS22);
   break;

  case 1024:
   TCCR2B=(1<<CS21)|(1<<CS22)|(1<<CS20);
   break;

}

 //clear_flag
 while(TIFR2!=(1<<OCF2A));
 TIFR2|=(1<<OCF2A);

//end
}

//main
int main(){
//data_DirectionalRegister
 DDRD=(1<<DDD3);

//loop
 while(1)_TIMER2_0C2B_WAVE2(1,62500);

//esc
 return 0;
}
