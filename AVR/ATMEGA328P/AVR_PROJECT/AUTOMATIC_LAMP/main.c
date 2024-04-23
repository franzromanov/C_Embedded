#include <sound_sensing.h>
#include <pir_sensing.h>

int main(){
  DDRB|=(1<<4);//RELAY_ENABLE
  PORTB|=(0<<4);//INIT
  while(1){
    uint8_t sound_logic=db_react(0);
    uint8_t motion_logic=pir_react(5);//pb_5
    if(sound_logic&motion_logic==1)PORTB|=(1<<4);
    else PORTB|=(0<<4);
  }
  return 0;  
 }
