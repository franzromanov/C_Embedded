//welcome_CodeName::IGNIS
#include <avr/io.h>
#define CLCK 16000000UL

//func
void _TIMER1_OC1B_WAVE_CTC(uint16_t prescaler,uint32_t fout){
 //start
 
 //GenerateCompare_Value
 uint32_t comp_val=((CLCK)/(2*prescaler*fout))-1;
 
 //load_compareValue
 OCR1A=comp_val;//TOP_valueISatOCR1A

 //set_Timer1_registers
 TCCR1A=(1<<COM1B0);
 TCCR1B=(1<<WGM12);

 //set_Prescaler
 switch(prescaler){
 
  case 1:
   TCCR1B|=(1<<CS10);
   break;

  case 8:
   TCCR1B|=(1<<CS11);
   break;

  case 64:
   TCCR1B|=(1<<CS11)|(1<<CS10);
   break;

  case 256:
   TCCR1B|=(1<<CS12);
   break;

  case 1024:
   TCCR1B|=(1<<CS12)|(CS10);
   break;

}


 //clear_flag
 while(TIFR1!=(1<<OCF1A));
 TIFR1|=(1<<OCF1A);

 //end
}


//main
int main(){
 //set_DataDirectionalRegister
 DDRB=(1<<DDB5);


//loop
 while(1)_TIMER1_OC1B_WAVE_CTC(1,62500);


//esc
 return 0;
}
