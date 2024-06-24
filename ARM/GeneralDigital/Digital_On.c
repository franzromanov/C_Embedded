#include <stdint.h>
#define GPIOB_BASE 0x40010C00
#define RCC_BASE   0x40021000

//mapping
#define RCC_APB2 (*(volatile uint32_t*)(RCC_BASE+0x18))
#define GPIO_CRL (*(volatile uint32_t*)(GPIOB_BASE+0x00))
#define GPIO_ODR (*(volatile uint32_t*)(GPIOB_BASE+0x0C))

void delay(volatile uint32_t count){
	while(count--);

}

int main(){
	RCC_APB2=(1<<3);
	GPIO_CRL=(0xF<<20);
	GPIO_CRL=(0b10<<20);
	while(1){
		GPIO_ODR^=(1<<5);
		delay(1000);
	}


	return 0;
}

