#include <avr/io.h>
#define CLK 16000000UL

void _TIMER0_OC0B_WAVE_CTC(uint32_t fout,uint16_t scaler){
 //get_compare_val
 uint32_t comp_val=(CLK/(2*scaler*fout))-1;
 //load_OCR0A:: in ctc mode for time 0 the TOP value will always on the OCR0A no matter where the intended output compare port you wanna use
 OCR0A=comp_val;

 //setup_timer
 TCCR0A=(1<<COM0B0)|(1<<WGM01);//mode::ctc
 asm volatile("sei");
 //set_up_prescalerMode
 switch(scaler){
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
   TCCR0B=(1<<CS00)|(1<<CS02);
   break;
}

//Match_Occurs[ClearFlag]
  while((TIFR0 & (1<<OCF0A))==0);
  TIFR0=(1<<OCF0A); //clearFlag 
}




//main
int main(){
 //set_asOUT
 DDRD=(1<<DDD5);
 
//call_inLoop
 while(1){_TIMER0_OC0B_WAVE_CTC(10000,8);}


//esc
 return 0;
}

