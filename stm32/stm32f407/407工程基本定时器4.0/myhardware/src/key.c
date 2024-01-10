#include "ange_systick.h"
#include "key.h"
void GPIOA_init(u32 Pin,GPIOMode_TypeDef mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=mode;
	gpioinit.GPIO_Pin=Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void GPIOB_init(u32 Pin,GPIOMode_TypeDef mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=mode;
	gpioinit.GPIO_Pin=Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void GPIOC_init(u32 Pin,GPIOMode_TypeDef mode)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=mode;
	gpioinit.GPIO_Pin=Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void GPIOD_init(u32 Pin,GPIOMode_TypeDef mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=mode;
	gpioinit.GPIO_Pin=Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void GPIOE_init(u32 Pin,GPIOMode_TypeDef mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=mode;
	gpioinit.GPIO_Pin=Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
}

