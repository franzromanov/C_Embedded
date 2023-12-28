#include <avr/io.h>
int main(){
        DDRB|=(1<<DDB0)&~(0<<DDB4);

        //ACTIVATE_PULLUP_RESISTOR
        PORTB|=(1<<PORTB4);

while(1){
        //PB_LED
        if(!(PINB & (1 << PINB4)))PORTB|=(1<<PORTB0);
        else PORTB&=~(1<<PORTB0);

 
}
  return 0;
}


