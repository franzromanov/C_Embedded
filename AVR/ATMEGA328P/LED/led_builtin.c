//led_builtin
#include<avr/io.h>

int main(){

//set_DDR
DDRB|=(1<<DDB5);

//set_logic_onPORT
PORTB|=(0<<PORTB5);

return 0;
}


