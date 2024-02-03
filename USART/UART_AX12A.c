#include <avr/io.h>
#include <util/delay.h>

//INSTRUCTION_PACKET
#define HEADER 0xFF
#define INSTRUCTION 0x03

//ID_
uint8_t ID_[]={1,2,3,4,5,6,7,8,9,10,11,12};

//uart_session
void UART_SET(){
  UCSR0A|=(1<<U2X0);
  //Baud_rate
  UBRR0H=(uint8_t)(1>>8);
  UBRR0L=(uint8_t)1;
  //frame_set
  UCSR0C|=(3<<UCSZ00);
  //ENABLE
  UCSR0B|=(1<<TXEN0)|(1<<RXEN0);

}

//uart_send
void uart_t(uint8_t *pack,uint8_t len){

 
  for(uint8_t i=0;i<len;i++){
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0=pack[i];
  }

}

void set_velo(uint16_t velocity,uint8_t ID_){
  uint16_t checksum=ID_+5+INSTRUCTION+32+velocity;
  if(checksum>255)checksum=(checksum&0xFF);
  uint8_t packet_velo[9]={HEADER, HEADER, ID_,5,INSTRUCTION,0x20,(uint8_t)(velocity & 0xFF),(uint8_t)(velocity>>8),~((uint8_t)checksum)};
  uart_t(packet_velo,9);

}

//ax12a_protocol
void pos_goal(uint16_t pos_val,uint8_t ID_ ){
  //pos_set
  uint16_t checksum=ID_+5+3+30+(uint8_t)(pos_val&0xFF)+(uint8_t)(pos_val>>8);
  if(checksum>255)checksum=(checksum&0xFF);
  uint8_t packet[9]={HEADER, HEADER, ID_,5,INSTRUCTION,0x1E,uint8_t(pos_val&0xFF),(uint8_t)(pos_val>>8),~((uint8_t)checksum)};
  uart_t(packet,9);
  _delay_ms(100);
}



//main-section
int main(){
  
  UART_SET();//init
    //set_velocity
    for(int i=0;i<12;i++)set_velo(100,ID_[i]);



    
    while(1){
   
        //set_position
  for(int i=0;i<12;i++){
    pos_goal(750,ID_[i]);
   //_delay_ms(500);
   //pos_goal(750,ID_[i]);
   
  }_delay_ms(1000);
    //set_position
  for(int i=0;i<12;i++){
    pos_goal(512,ID_[i]);
    
   //pos_goal(750,ID_[i]);
   
  }_delay_ms(1000);


    }
    

  return 0;
}