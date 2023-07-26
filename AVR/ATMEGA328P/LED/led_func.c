#include <avr/io.h>
#include <util/delay.h>
#define dog 1000
#define ddr (volatile uint8_t*) 0x24
#define port (volatile uint8_t*) 0x25



//func
volatile void blink(volatile uint8_t* DIRECT,volatile uint8_t* PORT,volatile uint8_t val){
*DIRECT=val;
while(1){
*PORT=val;
_delay_ms(dog);
*PORT=0x0;
_delay_ms(dog);
}

}

int main(void){


volatile uint8_t* DIRECT=ddr;
volatile uint8_t* PORT=port;
blink(ddr,port,0x10);
return 0;
}
