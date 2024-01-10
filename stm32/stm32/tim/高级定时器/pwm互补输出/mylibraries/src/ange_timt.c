#include "ange_timt.h"
void ange_TIMt_PWM_GPIO_Config()
{
	//��ͨ����ӦGPIO��ʱ��
	RCC_APB2PeriphClockCmd(ange_TIMt_CH1_CLK|ange_TIMt_CH2_CLK|ange_TIMt_CH3_CLK|ange_TIMt_CH4_CLK,ENABLE);  
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	//ͨ��ch1��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH1_Pin;
	GPIO_Init(ange_TIMt_CH1_PORT,&gpioinit); ////  
	//ͨ��ch2��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH2_Pin;
	GPIO_Init(ange_TIMt_CH2_PORT,&gpioinit); /////////
	//ͨ��ch3��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH3_Pin;
	GPIO_Init(ange_TIMt_CH3_PORT,&gpioinit); /////
	//ͨ��ch4��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH4_Pin;
	GPIO_Init(ange_TIMt_CH4_PORT,&gpioinit); ////
}
void ange_TIMt_PWM_Config()
{
		//��TIMʱ��
	ange_TIMt_APBxClock(ange_TIMt_CLK,ENABLE);
	//��ʱ��������ʼ��
	TIM_TimeBaseInitTypeDef timinit;
	//ʱ�ӷ�Ƶ������ck����int�������������Լ������˲�����Ƶ��
	timinit.TIM_ClockDivision=TIM_CKD_DIV1; 
		//��ʱ��������ʽup down centeraligned
//	timinit.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
		timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//ckpsc��Ƶ��
	timinit.TIM_Prescaler=ange_TIMt_Prescaler;
	//��װֵ
	timinit.TIM_Period=ange_TIMt_Period;
	//�ظ�����ֵ
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMtx,&timinit);
	///////
	TIM_OCInitTypeDef timinit1;
	//�������ģʽ
	timinit1.TIM_OCMode=TIM_OCMode_PWM1;
	//�Ƚ����ʹ��
	timinit1.TIM_OutputState=TIM_OutputState_Enable;
	//�������ʹ�ܣ�ͨ�ö�ʱ��������
	timinit1.TIM_OutputNState=TIM_OutputNState_Enable;
	//�����Ч��ƽ
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

