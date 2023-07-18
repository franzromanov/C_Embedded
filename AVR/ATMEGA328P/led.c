#include <avr/io.h>
#include <util/delay.h>

volatile int noob(){return 0;}

int main(){
//DDRB-->PORTB5
DDRB=0x10;


for(;;){
PORTB=0x10;
_delay_ms(1000);
PORTB=0x0;
_delay_ms(1000);
}
PORTB=0;
noob();
//return 0;
}
