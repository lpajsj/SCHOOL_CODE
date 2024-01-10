#include "led.h"

//LED IO初始化
/*
PA8  485OE
PC4  PD6  PD5  PD4   LED指示灯
PD7   蜂鸣器
*/
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8 485OE
//	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.0,1
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.4,5	
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD.0
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出高
	GPIO_SetBits(GPIOC,GPIO_Pin_4);						 //PC.4 输出高
	GPIO_SetBits(GPIOD,GPIO_Pin_4);						 //PD.4 输出高
	GPIO_SetBits(GPIOD,GPIO_Pin_5);						 //PD.5 输出高
	GPIO_SetBits(GPIOD,GPIO_Pin_6);						 //PD.6 输出高
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);					 //PD.7  输出高

}

void Max485()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//开GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD.0
		
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
}
 
