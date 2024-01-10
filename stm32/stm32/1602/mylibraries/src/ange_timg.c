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
	//����ͨ����ƽ
	timinit1.TIM_OCNPolarity=TIM_OCNPolarity_High;
	//���е�ƽ
	timinit1.TIM_OCIdleState=TIM_OCIdleState_Set;
	timinit1.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	//pwmռ�ձȵ���
	timinit1.TIM_Pulse=ange_TIMg_PWM1_Pulse;
	//�Ƚ������ʼ��
	TIM_OC1Init(ange_TIMgx,&timinit1);
	//Ԥװ��ʹ��
	TIM_OC1PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//ͨ������ʼ��
	timinit1.TIM_Pulse=ange_TIMg_PWM2_Pulse;
	TIM_OC2Init(ange_TIMgx,&timinit1);
	TIM_OC2PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//ʹ�ܼ�����
	TIM_Cmd(ange_TIMgx,ENABLE);
	//�����ʹ�ܣ��߼���ʱ����Ҫ
	TIM_CtrlPWMOutputs(ange_TIMgx,ENABLE);
}
void ange_TIMg_PWM_BDTR_GPIO_Config() //ɲ��gpio��ʼ��
{
	RCC_APB2PeriphClockCmd(ange_TIMg_PWM_BDTR_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	//pwm������ã�
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;//
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_TIMg_PWM_BDTR_Pin;
	GPIO_Init(ange_TIMg_PWM_BDTR_PORT,&gpioinit);
	GPIO_ResetBits(ange_TIMg_PWM_BDTR_PORT,ange_TIMg_PWM_BDTR_Pin);
}
void ange_TIMg_PWM_BDTR_Config()
{
	TIM_BDTRInitTypeDef timinit;
	//����ģʽ�µĹر�״̬
	timinit.TIM_OSSRState=TIM_OSSIState_Enable;
	//����ģʽ�µĹر�״̬
	timinit.TIM_OSSIState=TIM_OSSIState_Enable;
	//��������ѡ�񣬾��忴BDTR��LOCK��1-0��
	timinit.TIM_LOCKLevel=TIM_LOCKLevel_1;
	//��������ʱ����忴 BDTR��DTG[7-0]
	timinit.TIM_DeadTime=11;
	//��·���빦��ѡ��
	timinit.TIM_Break=TIM_Break_Enable;
	//ɲ�����뼫��
	timinit.TIM_BreakPolarity=TIM_BreakPolarity_High;
	//�Զ����ʹ��
	timinit.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(ange_TIMgx,&timinit);
}
void ange_TIMg_PWM_init() //������ʱ���pwm�������
{
	ange_TIMg_PWM_GPIO_Config();
	ange_TIMg_PWM_Config();
	ange_TIMg_PWM_BDTR_GPIO_Config();
	ange_TIMg_PWM_BDTR_Config();
}
////����******************************************************************
void ange_TIMg_ICPWM_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(ange_TIMg_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	//���벶����Ҫ�ѹܽ�����Ϊ��������
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_TIMg_CH1_Pin;
	GPIO_Init(ange_TIMg_CH1_PORT,&gpioinit);
}
void ange_TIMg_ICPWM_Config()
{
	ange_TIMg_APBxClock(ange_TIMg_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	//// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	// ����������ģʽ
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//����CNT��������ʱ�� = Fck_int/(psc+1)
	timinit.TIM_Prescaler=ange_TIMg_Prescaler;
	//�Զ���װ�ؼĴ�����ֵ
	timinit.TIM_Period=ange_TIMg_Period;
	//�ظ���������ֵ
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMgx,&timinit);
	///
	TIM_ICInitTypeDef timinit2;
	//pwm����ֻ����ͨ��1��2
	timinit2.TIM_Channel=ange_TIMg_Channelx1;
	///�˲���ϵ����0-f֮��
	timinit2.TIM_ICFilter=0;
	//���벶��ͨ��Ԥ��Ƶ��
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//���ش���ѡ��
	timinit2.TIM_ICPolarity=TIM_ICPolarity_Rising;
	//����ͨ��ѡ��TIM_ICSelection_DirectTI;TIM_ICSelection_IndirectTI�����Կ��α�405
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//pwm�����ʼ����
	TIM_PWMIConfig(ange_TIMgx,&timinit2);
	//// ѡ�����벶��Ĵ����ź�
	TIM_SelectInputTrigger(ange_TIMgx,TIM_TS_TI1FP1);
	// PWM����ģʽʱ,��ģʽ���빤���ڸ�λģʽ��������ʼʱ,������CNT�ᱻ��λ
	TIM_SelectSlaveMode(ange_TIMgx,TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(ange_TIMgx,TIM_MasterSlaveMode_Enable);
	//// ����жϱ�־λ
	TIM_ClearITPendingBit(ange_TIMgx,ange_TIMg_IT_CCx);
	TIM_ITConfig(ange_TIMgx,ange_TIMg_IT_CCx,ENABLE);
	TIM_Cmd(ange_TIMgx,ENABLE);
}
void ange_TIMg_ICPWM_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//�����ж�Դ
	nvicinit.NVIC_IRQChannel=ange_TIMg_CC_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=0;
	nvicinit.NVIC_IRQChannelSubPriority=3;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
void ange_TIMg_ICPWM_init()
{
	ange_TIMg_ICPWM_GPIO_Config();
	ange_TIMg_ICPWM_NVIC_Config();
	ange_TIMg_ICPWM_Config();
}
u16 ic1value,ic2value;
u8 icfinish;
void ange_TIMg_CC_IRQHandler()
{
	if(TIM_GetITStatus(ange_TIMgx,TIM_IT_CC1)==SET)
	{
		TIM_ClearITPendingBit(ange_TIMgx,TIM_IT_CC1);
		//��ȡ����ֵ
		ic1value=TIM_GetCapture1(ange_TIMgx);
		//������ֵ
		ic2value=TIM_GetCapture2(ange_TIMgx);
		//���ܹ��жϣ����жϻ���ִ���
//		TIM_ITConfig(ange_TIMgx,ange_TIMg_IT_CCx,DISABLE);
		icfinish=1;
	}
	
}
