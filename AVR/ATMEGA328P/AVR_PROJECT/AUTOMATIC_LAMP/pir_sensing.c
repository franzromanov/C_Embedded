#include <pir_sensing.h>
uint8_t pir_react(uint8_t gpio){
	DDRB&=~(1<<gpio);
	return (uint8_t)(PINB&(1<<gpio)); 
}