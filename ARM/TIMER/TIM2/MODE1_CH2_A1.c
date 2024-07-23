//new_pwm:TIM2_CH2_PA1

#define GPIOA_BASE 0x40010800
#define RCC_BASE 0x40021000
#define TIM2_BASE 0x40000000

//DEFINE_PERIPHERALS
#define RCC_APB1EN (*(volatile uint32_t)(RCC_BASE+0x1C))
#define RCC_APB2EN (*(volatile uint32_t)(RCC_BASE+0x18))
#define GPIOA_CRL (*(volatile uint32_t)(GPIOA_BASE+0x00))
#define TIM2_PSC (*(volatile uint32_t)(TIM2_BASE+0x28))
#define	TIM2_ARR (*(volatile uint32_t)(TIM2_BASE+0x2C))
#define TIM2_CCR2 (*(volatile uint32_t)(TIM2_BASE+0x38))
#define TIM2_CCMR1 (*(volatile uint32_t)(TIM2_BASE+0x18))
#define TIM2_EGR (*(volatile uint32_t)(TIM2_BASE+0x14))
#define TIM2_CCER (*(volatile uint32_t)(TIM2_BASE+0x20))
#define TIM2_CR1 (*(volatile uint32_t)(TIM2_BASE+0x00))





int main(){
	//ENABLE_CLOCK
	RCC_APB1EN|=1;//CLCK_FOR_GPIOA_CONFIG_REG
	RCC_APB2EN|=1<<2;//CLCK_FOR_TIM2_CONFIG_REG
	//serup_AFIO_for TIMER _OUTPUT
	GPIOA_CRL&=~(0xf<<1);
	GPIOA_CRL|=(0b1010<<1);
	//set_timer
	TIM2_PSC|=7;//PRESCALER
	TIM2_ARR|=1000;//FREQUENCY
	TIM2_CCR2|=250;//DUTY_CYCLE
	TIM2_CCMR1|=(0b110<<12);//config_mode
	TIM2_EGR|=1;//enable_update_event generation
	TIM2_CCER|=(1<<4);//allow/enable_signal output on corresponding pin/port
	TIM2_CR1|=1;//enable_counter



	while(1);




	return 0;
}
