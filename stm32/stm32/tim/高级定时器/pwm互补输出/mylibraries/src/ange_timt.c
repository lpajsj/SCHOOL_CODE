#include "ange_timt.h"
void ange_TIMt_PWM_GPIO_Config()
{
	//打开通道对应GPIO的时钟
	RCC_APB2PeriphClockCmd(ange_TIMt_CH1_CLK|ange_TIMt_CH2_CLK|ange_TIMt_CH3_CLK|ange_TIMt_CH4_CLK,ENABLE);  
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	//通道ch1初始化
	gpioinit.GPIO_Pin=ange_TIMt_CH1_Pin;
	GPIO_Init(ange_TIMt_CH1_PORT,&gpioinit); ////  
	//通道ch2初始化
	gpioinit.GPIO_Pin=ange_TIMt_CH2_Pin;
	GPIO_Init(ange_TIMt_CH2_PORT,&gpioinit); /////////
	//通道ch3初始化
	gpioinit.GPIO_Pin=ange_TIMt_CH3_Pin;
	GPIO_Init(ange_TIMt_CH3_PORT,&gpioinit); /////
	//通道ch4初始化
	gpioinit.GPIO_Pin=ange_TIMt_CH4_Pin;
	GPIO_Init(ange_TIMt_CH4_PORT,&gpioinit); ////
}
void ange_TIMt_PWM_Config()
{
		//开TIM时钟
	ange_TIMt_APBxClock(ange_TIMt_CLK,ENABLE);
	//定时器基本初始化
	TIM_TimeBaseInitTypeDef timinit;
	//时钟分频，设置ck——int与死区发生器以及数字滤波器分频比
	timinit.TIM_ClockDivision=TIM_CKD_DIV1; 
		//定时器计数方式up down centeraligned
//	timinit.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
		timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//ckpsc分频比
	timinit.TIM_Prescaler=ange_TIMt_Prescaler;
	//重装值
	timinit.TIM_Period=ange_TIMt_Period;
	//重复计数值
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMtx,&timinit);
	///////
	TIM_OCInitTypeDef timinit1;
	//设置输出模式
	timinit1.TIM_OCMode=TIM_OCMode_PWM1;
	//比较输出使能
	timinit1.TIM_OutputState=TIM_OutputState_Enable;
	//互补输出使能，通用定时器不存在
	timinit1.TIM_OutputNState=TIM_OutputNState_Enable;
	//输出有效电平
	timinit1.TIM_OCPolarity=TIM_OCPolarity_High;
	timinit1.TIM_OCNPolarity=TIM_OCNPolarity_High;
	timinit1.TIM_OCIdleState=TIM_OCIdleState_Set;
	timinit1.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	timinit1.TIM_Pulse=ange_TIMt_PWM1_Pulse;
	TIM_OC1Init(ange_TIMtx,&timinit1);
	TIM_OC1PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//
	timinit1.TIM_Pulse=ange_TIMt_PWM2_Pulse;
	TIM_OC2Init(ange_TIMtx,&timinit1);
	TIM_OC2PolarityConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//
	timinit1.TIM_Pulse=ange_TIMt_PWM3_Pulse;
	TIM_OC3Init(ange_TIMtx,&timinit1);
	TIM_OC3PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	///
	timinit1.TIM_Pulse=ange_TIMt_PWM4_Pulse;
	timinit1.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC4Init(ange_TIMtx,&timinit1);
	TIM_OC4PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//
	TIM_Cmd(ange_TIMtx,ENABLE);
}
void ange_TIMt_PWM_init()
{
	ange_TIMt_PWM_GPIO_Config();
	ange_TIMt_PWM_Config();
}

