#include "ange_timg.h"
void ange_TIMg_PWM_GPIO_Config()
{
	//��ͨ����ӦGPIO��ʱ��
	RCC_APB2PeriphClockCmd(ange_TIMg_CH1_CLK|ange_TIMg_CH2_CLK|ange_TIMg_CH1N_CLK|ange_TIMg_CH2N_CLK,ENABLE);  
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	//ͨ��ch1��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH1_Pin;
	GPIO_Init(ange_TIMg_CH1_PORT,&gpioinit); ////  
	//ͨ��ch1N��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH1N_Pin;
	GPIO_Init(ange_TIMg_CH1N_PORT,&gpioinit); /////////
	//ͨ��ch2��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH2_Pin;
	GPIO_Init(ange_TIMg_CH2_PORT,&gpioinit); /////
	//ͨ��ch2N��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH2N_Pin;
	GPIO_Init(ange_TIMg_CH2N_PORT,&gpioinit); ////
}

void ange_TIMg_PWM_Config()
{
		//��TIMʱ��
	ange_TIMg_APBxClock(ange_TIMg_CLK,ENABLE);
	//��ʱ��������ʼ��
	TIM_TimeBaseInitTypeDef timinit;
	//ʱ�ӷ�Ƶ������ck����int�������������Լ������˲�����Ƶ��
	timinit.TIM_ClockDivision=TIM_CKD_DIV1; 
		//��ʱ��������ʽup down centeraligned
//	timinit.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
		timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//ckpsc��Ƶ��
	timinit.TIM_Prescaler=ange_TIMg_Prescaler;
	//��װֵ
	timinit.TIM_Period=ange_TIMg_Period;
	//�ظ�����ֵ
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMgx,&timinit);
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
	timinit1.TIM_Pulse=ange_TIMg_PWM1_Pulse;
	//�Ƚ������ʼ��
	TIM_OC1Init(ange_TIMgx,&timinit1);
	//Ԥװ��ʹ��
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
