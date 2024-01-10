#include "ange_timg.h"
void ange_TIMg_PWM_GPIO_Config()
{
	//打开通道对应GPIO的时钟
	RCC_APB2PeriphClockCmd(ange_TIMg_CH1_CLK|ange_TIMg_CH2_CLK|ange_TIMg_CH1N_CLK|ange_TIMg_CH2N_CLK,ENABLE);  
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	//通道ch1初始化
	gpioinit.GPIO_Pin=ange_TIMg_CH1_Pin;
	GPIO_Init(ange_TIMg_CH1_PORT,&gpioinit); ////  
	//通道ch1N初始化
	gpioinit.GPIO_Pin=ange_TIMg_CH1N_Pin;
	GPIO_Init(ange_TIMg_CH1N_PORT,&gpioinit); /////////
	//通道ch2初始化
	gpioinit.GPIO_Pin=ange_TIMg_CH2_Pin;
	GPIO_Init(ange_TIMg_CH2_PORT,&gpioinit); /////
	//通道ch2N初始化
	gpioinit.GPIO_Pin=ange_TIMg_CH2N_Pin;
	GPIO_Init(ange_TIMg_CH2N_PORT,&gpioinit); ////
}

void ange_TIMg_PWM_Config()
{
		//开TIM时钟
	ange_TIMg_APBxClock(ange_TIMg_CLK,ENABLE);
	//定时器基本初始化
	TIM_TimeBaseInitTypeDef timinit;
	//时钟分频，设置ck——int与死区发生器以及数字滤波器分频比
	timinit.TIM_ClockDivision=TIM_CKD_DIV1; 
		//定时器计数方式up down centeraligned
//	timinit.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
		timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//ckpsc分频比
	timinit.TIM_Prescaler=ange_TIMg_Prescaler;
	//重装值
	timinit.TIM_Period=ange_TIMg_Period;
	//重复计数值
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMgx,&timinit);
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
	timinit1.TIM_Pulse=ange_TIMg_PWM1_Pulse;
	//比较输出初始化
	TIM_OC1Init(ange_TIMgx,&timinit1);
	//预装载使能
	TIM_OC1PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//
	timinit1.TIM_Pulse=ange_TIMg_PWM2_Pulse;
	TIM_OC2Init(ange_TIMgx,&timinit1);
	TIM_OC2PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//
	TIM_Cmd(ange_TIMgx,ENABLE);
	TIM_CtrlPWMOutputs(ange_TIMgx,ENABLE);
}
void ange_TIMg_PWM_BDTR_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(ange_TIMg_PWM_BDTR_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_TIMg_PWM_BDTR_Pin;
	GPIO_Init(ange_TIMg_PWM_BDTR_PORT,&gpioinit);
	GPIO_ResetBits(ange_TIMg_PWM_BDTR_PORT,ange_TIMg_PWM_BDTR_Pin);
}
void ange_TIMg_PWM_BDTR_Config()
{
	TIM_BDTRInitTypeDef timinit;
	timinit.TIM_OSSRState=TIM_OSSIState_Enable;
	timinit.TIM_OSSIState=TIM_OSSIState_Enable;
	timinit.TIM_LOCKLevel=TIM_LOCKLevel_1;
	timinit.TIM_DeadTime=11;
	timinit.TIM_Break=TIM_Break_Enable;
	timinit.TIM_BreakPolarity=TIM_BreakPolarity_High;
	timinit.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(ange_TIMgx,&timinit);
}
void ange_TIMg_PWM_init()
{
	ange_TIMg_PWM_GPIO_Config();
	ange_TIMg_PWM_Config();
	ange_TIMg_PWM_BDTR_GPIO_Config();
	ange_TIMg_PWM_BDTR_Config();
}
