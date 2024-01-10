#include "stm32f10x.h"                  // Device header
#define uint32_t unsigned int
int main()
{
	uint32_t a=3;
	RCC_APB2ENR|=(a<<3);
	GPIOB_CRL &=~(0X0F<<4*5);
	GPIOB_CRL|=(1<<4*5);
	GPIOB_ODR&=~(0X01<<5);
	GPIOB_CRL &=~(0X0F<<4*1);
	GPIOB_CRL|=(1<<4*1);
	GPIOB_ODR&=~(0X01<<1);
//	GPIOB_CRL &=~(0X0F<<4*0);
//	GPIOB_CRL|=(1<<4*0);
//	GPIOB_ODR&=~(0X01<<0);
	while(1);
}
