//BOOT_ALIVE:::code_name>>>IGNIS
#include <avr/io.h>
#define CLCK 16000000UL


//func_Timer_1:::[ TOP =  ]:::
void _TIMER1_OC1A_WAVE_CTC( uint16_t prescaler, uint32_t fout, uint2_t filter, uint2_t edge_select ){


//calculate_compVal
  uint32_t compVal= (CLCK/(2*prescaler*fout))-1;


//LOAD_OCR1A
  OCR1A=compVal;


//set_Timer_1A_regs
 TCCR1A=(1<<WGM12)|(1<<COM1A0);//SET_WAVE_MODE_&_COMPARE_OUTPUT_MODE


//SET_PRESCALER_Timer_1B_regs
 switch(prescaler){
  case 1:
   TCCR1B=(1<<CS10);
   break;

  case 8:
   TCCR1B=(1<<CS11);
   break;

  case 64:
   TCCR1B=(1<<CS10)|(1<<CS11);
   break;

  case 256:
   TCCR1B=(1<<CS12);
   break;

  case 1024:
   TCCR1B=(1<<CS10)|(1<<CS12);
   break;

}
   

//FILTER_ACTIVATION [0:DEACTIVATE; 1:ACTIVATE]
 switch(filter){ 

  case 0:
   TCCR1B=(0<<ICNC1)
   break;

  case 1:
   TCCR1B=(1<<ICNC1)
   break;

}


//EDGE_SELECTION [0:FALLING_EDGE; 1:RISING_EDGE]
 switch(edge_select){

  case 0:
   TCCR1B=(0<<ICES1)
   break;

  case 1:
   TCCR1B=(1<<ICES1)
   break;

}


//clear_flag
 if(TIFR1==(1<<OCF1A)) TIFR1=(1<<OCF1A) ;

}


//main
int main(){


//ENABLE_PORT:::[ OUT ]:::
 DDRB=(1<<DDB1);


//infinite_loop
 while(1){

  //start_Timer_1
  _TIMER1_OC1A_WAVE_CTC(1,62500,0,0);

}


//esc
 return 0;
}
