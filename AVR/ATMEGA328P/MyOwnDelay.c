#include <avr/io.h>
//declare
void delay(unsigned int milis){ 
 int try=0;
 for(unsigned int i=0;i<milis;i++){
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
}


}



//main
int main(){ 
 DDRB=(1<<DDB5);

 while(1){ 
 PORTB|=(1<<PORTB5);
 delay(1000);
 PORTB=0x0;
 delay(1000);

}
//esc
 return 0;
}
