#include <avr/io.h>
#include <util/delay.h>
#define Direct_B (int*) 0x24
#define PORTB_ (int*) 0x25


int main(){


*Direct_B=0x10;
while(1){
*PORTB_=0x10;
_delay_ms(1000);
*PORTB_=0x0;
_delay_ms(1000);
}

return 0;
}
