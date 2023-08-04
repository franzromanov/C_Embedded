//BOOT_ALIVE:::code_name>>>IGNIS
#include <avr/io.h>
#define CLCK 16000000UL

//func_Timer_1:::[ TOP = OCR1A  ]:::
void _TIMER1_OC1A_WAVE_CTC( uint16_t prescaler, uint32_t fout ){

//calculate_compVal
  uint32_t compVal= (CLCK/(2*prescaler*fout))-1;

//LOAD_OCR1A
  OCR1A=compVal;

//set_Timer_1A_&_1B_regs
 TCCR1A|=(1<<COM1A0);//SET_WAVE_MODE_&_COMPARE_OUTPUT_MODE
 TCCR1B|=(1<<WGM12);//SET_WAVE_MODE_&_COMPARE_OUTPUT_MODE

//SET_PRESCALER_Timer_1B_regs
 switch(prescaler){
  case 1:
   TCCR1B|=(1<<CS10);
   break;

  case 8:
   TCCR1B|=(1<<CS11);
   break;

  case 64:
   TCCR1B|=(1<<CS10)|(1<<CS11);
   break;

  case 256:
   TCCR1B|=(1<<CS12);
   break;

  case 1024:
   TCCR1B|=(1<<CS10)|(1<<CS12);
   break;

}

//clear_flag
 while(TIFR1==(1<<OCF1A)) TIFR1|=(1<<OCF1A) ;

}

//main
int main(){

//ENABLE_PORT:::[ OUT ]:::
 DDRB=(1<<DDB1);

//inifnite_loop
 while(1){
  //start_Timer_1
   _TIMER1_OC1A_WAVE_CTC(1,62500);
}

//esc
 return 0;
}
