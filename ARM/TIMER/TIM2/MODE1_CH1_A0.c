
/*
 * x is channel
 * NOTE
 * Timer Freq=CLCK/(prescaler*(ARR+1))
 * set bits on OC1PE will use the shdow register for CCR1
 * OCxREF:signal of output compare result of CCRx on channel x
 * CCxIF: is a capture/compare flag, its a flag that occurs when an compare value is triggering SREG (on pwm mode 1 its when CNT==CCRx)
 *****on MOde_1:CNT reset to 0 when CNT==ARR;
 enable clock to peripherals
 configure output control in GPIOx&AFIO control register (configure AFIO for timer function)
 configure the timer:
 *based on the clock source:
	 determine the prescaler
	 determine frequency by setting value on ARR
	 determine duty cycle by giving value TIMx_CCRy
 *set pwm mode
 *set upcounting/downcounting
 *set enable update event generation to generate an update event when CNT==ARR
 *set shadow register (optional)
 *enable counter

 ----shadow register is a register to hold a copy of a value of the primary register
shadow register act like a buffer

if using shadow register:

before value loaded to the ARR its loaded to shadow register first
then it transfered to ARR 
if in your project doesnt require a signal change by changing the arr value then shadow register is not necessary
if your project require the change in arr value to create such signal with new frequency thus shadow register is a must to create smooth transistion:

first frequency value>>shadow register>>ARR>>TIMER-PROCESS
next frequency value>>shadow register>>waiting for TIMER finish it process(update event)>>(if its done/update event occurs)>>value from shadow register transfered to ARR>> Timer process with new frequency

this also applied on CCx if your project require the change of PWM duty cycle at some point, its up to your system models

 */

#include <stdint.h>
#define RCC_BASE	0x40021000
#define TIM2_BASE	0x40000000
#define GPIOA_BASE	0x40010800
#define AFIO_BASE	0x40010000

//memory-mapping
#define RCC_APB1EN	(*(volatile uint32_t*)(RCC_BASE+0x1C))
#define RCC_APB2EN	(*(volatile uint32_t*)(RCC_BASE+0x18))
#define GPIOA_CRL	(*(volatile uint32_t*)(GPIOA_BASE+0x00))
#define TIM2_ARR	(*(volatile uint32_t*)(TIM2_BASE+0x2C))
#define TIM2_CCR1	(*(volatile uint32_t*)(TIM2_BASE+0x34))
#define TIM2_CCMR1	(*(volatile uint32_t*)(TIM2_BASE+0x18))
#define TIM2_CR1	(*(volatile uint32_t*)(TIM2_BASE+0x00))
#define TIM2_EGR	(*(volatile uint32_t*)(TIM2_BASE+0x14))
#define TIM2_CCER	(*(volatile uint32_t*)(TIM2_BASE+0x20))
#define TIM2_ARR	(*(volatile uint32_t*)(TIM2_BASE+0x2C))
#define TIM2_PSC	(*(volatile uint32_t*)(TIM2_BASE+0x28))

void pwm_init(){
//enable clock to peripherals
	RCC_APB1EN|=(1<<0);
	RCC_APB2EN|=(1<<2);

//setting-afio

	GPIOA_CRL&=~(0xF<<0);
	GPIOA_CRL|=(0b1010<<0);
//question: why its not required to config the AFIO CTRL registers?

//TIM2_CONFIG
	TIM2_CR1=0;
	TIM2_PSC = 7;
	TIM2_CCMR1|=(0x06<<4)|(1<<3);
	TIM2_CCER|=(1<<0);//enable channel as an output of the signal on corresponding pin
	TIM2_ARR=1000;
	TIM2_CCR1=250;
	TIM2_EGR|=(1<<0);
	TIM2_CR1|=(1<<0);

}

int main(){
	pwm_init();
	while(1){

	}
	return 0;
}
