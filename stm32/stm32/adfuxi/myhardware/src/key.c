#include "ange_systick.h"
#include "key.h"
void keya_init(u32 Pin)
{
	u32 x=0x1;
	x<<=Pin;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=key_mode;
	gpioinit.GPIO_Pin=x;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void keyb_init(u32 Pin)
{
	u32 x=0x1;
	x<<=Pin;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=key_mode;
	gpioinit.GPIO_Pin=x;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void keyc_init(u32 Pin)
{
	u32 x=0x1;
	x<<=Pin;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=key_mode;
	gpioinit.GPIO_Pin=x;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void keyd_init(u32 Pin)
{
	u32 x=0x1;
	x<<=Pin;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=key_mode;
	gpioinit.GPIO_Pin=x;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}
void keye_init(u32 Pin)
{
	u32 x=0x1;
	x<<=Pin;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=key_mode;
	gpioinit.GPIO_Pin=x;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioinit);
	
}

