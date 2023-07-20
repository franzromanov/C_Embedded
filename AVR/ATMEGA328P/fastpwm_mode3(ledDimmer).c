//::mode->3
#include <avr/io.h>
#include <util/delay.h>
//main
int main(){
//set_out::D6(ARDUINO_PIN)
 DDRB|=(1<<DDB3);//DataDirectionRegister(Register_D)

//PWM_frequency::62,5KHz
 //set_T/C
 TCCR2A|=(1<<WGM21)|(1<<WGM20)|(1<<COM2A1);
 TCCR2B|=(1<<CS20);

//loop
while(1){

 //load_OCR2A::DutyCycle(100%)
 OCR2A=255;
 _delay_ms(200);
 //load_OCR2A::DutyCycle(75%)
 OCR2A=191;
 _delay_ms(200);
 //load_OCR2A::DutyCycle(50%)
 OCR2A=127;
 _delay_ms(200);
 //load_OCR2A::DutyCycle(25%)
 OCR2A=63;
 _delay_ms(150);
 //load_OCRA::DutyCycle(15%)
 OCR2A=37.4;
 _delay_ms(100);
 //load_OCR2A::DutyCycle(5%)
 OCR2A=11.8;
 _delay_ms(100);
 //load_OCR2A::DutyCycle(0%)
 OCR0A=0;
 _delay_ms(100);
 DDRB=0x0;//forced_off
 _delay_ms(200);
 //regulate
 DDRB|=(1<<DDB3);
 //load_OCR2A::DutyCycle(0%)
 OCR0A=0;
 _delay_ms(100);
 //load_OCR2A::DutyCycle(5%)
 OCR2A=11.8;
 _delay_ms(100);
 //load_OCRA::DutyCycle(15%)
 OCR2A=37.4;
 _delay_ms(100);
 //load_OCR2A::DutyCycle(25%)
 OCR2A=63;
 _delay_ms(150);
 //load_OCR2A::DutyCycle(50%)
 OCR2A=127;
 _delay_ms(200);
 //load_OCR2A::DutyCycle(75%)
 OCR2A=191;
 _delay_ms(200);
};

return 0;
}
