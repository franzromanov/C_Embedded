#include <avr/io.h>
#include <util/delay.h>


int main(){
//set_ddr&port
DDRB=0x32; //DDRB | (1<<DDB5);
DDRD=0x32;

while(1)
{
//setportB_ state::ON
PORTB=0x32; //PORTB | (1<<PORTB5);

//delay
_delay_ms(100);

//setportB_state::OFF
PORTB=0x0; //PORTB^(1<<PORTB5);

//delay
_delay_ms(100);


//setportD_state: ON
PORTD=0x32;

//delay
_delay_ms(100);

//setportD_state: OFF
PORTD=0x0;

//delay
_delay_ms(100);

}



return 0;
}
