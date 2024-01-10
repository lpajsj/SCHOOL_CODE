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
	//互补通道电平
	timinit1.TIM_OCNPolarity=TIM_OCNPolarity_High;
	//空闲电平
	timinit1.TIM_OCIdleState=TIM_OCIdleState_Set;
	timinit1.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	//pwm占空比调节
	timinit1.TIM_Pulse=ange_TIMg_PWM1_Pulse;
	//比较输出初始化
	TIM_OC1Init(ange_TIMgx,&timinit1);
	//预装载使能
	TIM_OC1PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//通道二初始化
	timinit1.TIM_Pulse=ange_TIMg_PWM2_Pulse;
	TIM_OC2Init(ange_TIMgx,&timinit1);
	TIM_OC2PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//使能计数器
	TIM_Cmd(ange_TIMgx,ENABLE);
	//主输出使能，高级定时器需要
	TIM_CtrlPWMOutputs(ange_TIMgx,ENABLE);
}
void ange_TIMg_PWM_BDTR_GPIO_Config() //刹车gpio初始化
{
	RCC_APB2PeriphClockCmd(ange_TIMg_PWM_BDTR_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	//pwm输出复用，
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;//
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_TIMg_PWM_BDTR_Pin;
	GPIO_Init(ange_TIMg_PWM_BDTR_PORT,&gpioinit);
	GPIO_ResetBits(ange_TIMg_PWM_BDTR_PORT,ange_TIMg_PWM_BDTR_Pin);
}
void ange_TIMg_PWM_BDTR_Config()
{
	TIM_BDTRInitTypeDef timinit;
	//运行模式下的关闭状态
	timinit.TIM_OSSRState=TIM_OSSIState_Enable;
	//空闲模式下的关闭状态
	timinit.TIM_OSSIState=TIM_OSSIState_Enable;
	//锁定级别选择，具体看BDTR的LOCK【1-0】
	timinit.TIM_LOCKLevel=TIM_LOCKLevel_1;
	//配置死区时间具体看 BDTR的DTG[7-0]
	timinit.TIM_DeadTime=11;
	//断路输入功能选择
	timinit.TIM_Break=TIM_Break_Enable;
	//刹车输入极性
	timinit.TIM_BreakPolarity=TIM_BreakPolarity_High;
	//自动输出使能
	timinit.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(ange_TIMgx,&timinit);
}
void ange_TIMg_PWM_init() //带死区时间的pwm互补输出
{
	ange_TIMg_PWM_GPIO_Config();
	ange_TIMg_PWM_Config();
	ange_TIMg_PWM_BDTR_GPIO_Config();
	ange_TIMg_PWM_BDTR_Config();
}
////捕获******************************************************************
void ange_TIMg_ICPWM_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(ange_TIMg_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	//输入捕获需要把管脚设置为浮空输入
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_TIMg_CH1_Pin;
	GPIO_Init(ange_TIMg_CH1_PORT,&gpioinit);
}
void ange_TIMg_ICPWM_Config()
{
	ange_TIMg_APBxClock(ange_TIMg_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	//// 时钟分频因子 ，配置死区时间时需要用到
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数器计数模式
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//驱动CNT计数器的时钟 = Fck_int/(psc+1)
	timinit.TIM_Prescaler=ange_TIMg_Prescaler;
	//自动重装载寄存器的值
	timinit.TIM_Period=ange_TIMg_Period;
	//重复计数器的值
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMgx,&timinit);
	///
	TIM_ICInitTypeDef timinit2;
	//pwm输入只能是通道1和2
	timinit2.TIM_Channel=ange_TIMg_Channelx1;
	///滤波器系数在0-f之间
	timinit2.TIM_ICFilter=0;
	//输入捕获通道预分频器
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//边沿触发选择
	timinit2.TIM_ICPolarity=TIM_ICPolarity_Rising;
	//输入通道选择TIM_ICSelection_DirectTI;TIM_ICSelection_IndirectTI，可以看课本405
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//pwm输入初始化，
	TIM_PWMIConfig(ange_TIMgx,&timinit2);
	//// 选择输入捕获的触发信号
	TIM_SelectInputTrigger(ange_TIMgx,TIM_TS_TI1FP1);
	// PWM输入模式时,从模式必须工作在复位模式，当捕获开始时,计数器CNT会被复位
	TIM_SelectSlaveMode(ange_TIMgx,TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(ange_TIMgx,TIM_MasterSlaveMode_Enable);
	//// 清除中断标志位
	TIM_ClearITPendingBit(ange_TIMgx,ange_TIMg_IT_CCx);
	TIM_ITConfig(ange_TIMgx,ange_TIMg_IT_CCx,ENABLE);
	TIM_Cmd(ange_TIMgx,ENABLE);
}
void ange_TIMg_ICPWM_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//捕获中断源
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
		//获取周期值
		ic1value=TIM_GetCapture1(ange_TIMgx);
		//正脉宽值
		ic2value=TIM_GetCapture2(ange_TIMgx);
		//不能关中断，关中断会出现错误
//		TIM_ITConfig(ange_TIMgx,ange_TIMg_IT_CCx,DISABLE);
		icfinish=1;
	}
	
}
