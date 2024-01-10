#include "ange_timt.h"
//********************************************************//
void ange_TIMt_PWM_GPIO_Config()
{
	//打开通道对应GPIO的时钟
	RCC_AHB1PeriphClockCmd(ange_TIMt_CH1_CLK|ange_TIMt_CH2_CLK|ange_TIMt_CH3_CLK|ange_TIMt_CH4_CLK,ENABLE);  
	GPIO_InitTypeDef gpioinit;													   
		gpioinit.GPIO_Mode = GPIO_Mode_AF;   
    gpioinit.GPIO_OType = GPIO_OType_PP; 
    gpioinit.GPIO_PuPd = GPIO_PuPd_NOPULL;  
		gpioinit.GPIO_Speed = GPIO_Speed_100MHz; 
	//通道ch1初始化
	gpioinit.GPIO_Pin=ange_TIMt_CH1_Pin;
	GPIO_Init(ange_TIMt_CH1_PORT,&gpioinit); ////  
	//通道ch2初始化
	gpioinit.GPIO_Pin=ange_TIMt_CH2_Pin;
	GPIO_Init(ange_TIMt_CH2_PORT,&gpioinit); /////////
//	//通道ch3初始化
//	gpioinit.GPIO_Pin=ange_TIMt_CH3_Pin;
//	GPIO_Init(ange_TIMt_CH3_PORT,&gpioinit); ////////
//	//通道ch4初始化
//	gpioinit.GPIO_Pin=ange_TIMt_CH4_Pin;
//	GPIO_Init(ange_TIMt_CH4_PORT,&gpioinit); ////
	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH1_Pinsource,ange_TIMt_CH1_AF);
	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH2_Pinsource,ange_TIMt_CH2_AF);
//	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH3_Pinsource,ange_TIMt_CH3_AF);
//	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH4_Pinsource,ange_TIMt_CH4_AF);
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
	//高级定时器存在
	timinit1.TIM_OCNPolarity=TIM_OCNPolarity_High;
	timinit1.TIM_OCIdleState=TIM_OCIdleState_Set;
	timinit1.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	/////通道1输出
	timinit1.TIM_Pulse=ange_TIMt_PWM1_Pulse;
	TIM_OC1Init(ange_TIMtx,&timinit1);
	TIM_OC1PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//通道2输出
	timinit1.TIM_Pulse=ange_TIMt_PWM2_Pulse;
	TIM_OC2Init(ange_TIMtx,&timinit1);
	TIM_OC2PolarityConfig(ange_TIMtx,TIM_OCPreload_Enable);
//	//通道3输出
//	timinit1.TIM_Pulse=ange_TIMt_PWM3_Pulse;
//	TIM_OC3Init(ange_TIMtx,&timinit1);
//	TIM_OC3PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
//	///通道4输出
//	timinit1.TIM_Pulse=ange_TIMt_PWM4_Pulse;
//	timinit1.TIM_OCPolarity=TIM_OCPolarity_Low;
//	TIM_OC4Init(ange_TIMtx,&timinit1);
//	TIM_OC4PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//
	TIM_Cmd(ange_TIMtx,ENABLE);
}
void ange_TIMt_PWM_init()
{
	ange_TIMt_PWM_GPIO_Config();
	ange_TIMt_PWM_Config();
}
//是捕获啊************************************************************/
void ange_TIMt_IC_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(ange_TIMt_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF;  
    gpioinit.GPIO_OType = GPIO_OType_PP; 
    gpioinit.GPIO_PuPd = GPIO_PuPd_NOPULL;  
		gpioinit.GPIO_Speed=GPIO_Speed_50MHz; 
	//通道ch1初始化
	gpioinit.GPIO_Pin=ange_TIMt_CH1_Pin;
	GPIO_Init(ange_TIMt_CH1_PORT,&gpioinit);
}
void ange_TIMt_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_TIMt_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=0;
	nvicinit.NVIC_IRQChannelSubPriority=2;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}

void ange_TIMt_IC_Config()
{
	ange_TIMt_APBxClock(ange_TIMt_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Prescaler=ange_TIMt_Prescaler;
	timinit.TIM_Period=ange_TIMt_Period;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMtx,&timinit);
	///
	TIM_ICInitTypeDef timinit2;
	timinit2.TIM_Channel=ange_TIMt_Channelx;
	///滤波器系数在0-f之间
	timinit2.TIM_ICFilter=0;
	//预分频
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//边沿
	timinit2.TIM_ICPolarity=ange_TIMt_Channel_Polarity1;
	//通道选择
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(ange_TIMtx,&timinit2);
	TIM_ClearFlag(ange_TIMtx,TIM_IT_Update|ange_TIMt_IT_CCx);
	TIM_ITConfig(ange_TIMtx,TIM_IT_Update|ange_TIMt_IT_CCx,ENABLE);
	TIM_Cmd(ange_TIMtx,ENABLE);
}
ange_TIMt_ICValue_TypeDef TIMt_IC_Value;  //定义捕获值结构体
//void ange_TIMt_IRQHandler()
//{
//	//检测溢出
//	if(TIM_GetITStatus(ange_TIMtx,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(ange_TIMtx,TIM_IT_Update);
//		//溢出次数加一
//		TIMt_IC_Value.Capture_Period++;
//	}
//	if(TIM_GetITStatus(ange_TIMtx,ange_TIMt_IT_CCx)==SET)
//	{
//		TIM_ClearITPendingBit(ange_TIMtx,ange_TIMt_IT_CCx);
//		//第一次捕获
//		if(TIMt_IC_Value.Capture_ci==0)
//		{
//			TIMt_IC_Value.Capture_ci=1;
//			//捕获到第一个上升沿后开始真正计时
//			TIMt_IC_Value.Capture_Period=0;
////			TIMt_IC_Value.Capture_value=0;
//			//开始检测下降沿
//			TIM_OC1PolarityConfig(ange_TIMtx,TIM_ICPolarity_Falling);
//		}
//		//第二次捕获
//		else if(TIMt_IC_Value.Capture_ci==1)
//		{
//			TIMt_IC_Value.Capture_ci=0;
//			TIMt_IC_Value.Capture_value=TIM_GetCapture1(ange_TIMtx);
//			TIMt_IC_Value.Capture_finish=1;
//			TIM_OC1PolarityConfig(ange_TIMtx,TIM_ICPolarity_Rising);
//		}
//	}
//}
void ange_TIMt_IC_init()
{
	ange_TIMt_IC_GPIO_Config();
	ange_TIMt_NVIC_Config();
	ange_TIMt_IC_Config();
}
//*********************************************/

