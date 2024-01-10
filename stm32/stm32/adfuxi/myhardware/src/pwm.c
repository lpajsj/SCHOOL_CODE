#include "pwm.h"
//是捕获啊************************************************************/
void PWMqh_TIMt_IC_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(PWMqh_TIMt_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=PWMqh_TIMt_CH1_Pin;
	GPIO_Init(PWMqh_TIMt_CH1_PORT,&gpioinit);
	//通道2gpio初始化
	RCC_APB2PeriphClockCmd(PWMqh_TIMt_CH2_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=PWMqh_TIMt_CH2_Pin;
	GPIO_Init(PWMqh_TIMt_CH2_PORT,&gpioinit);
}
void PWMqh_TIMt_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=PWMqh_TIMt_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=0;
	nvicinit.NVIC_IRQChannelSubPriority=2;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}

void PWMqh_TIMt_IC_Config()
{
	PWMqh_TIMt_APBxClock(PWMqh_TIMt_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Prescaler=PWMqh_TIMt_Prescaler;
	timinit.TIM_Period=PWMqh_TIMt_Period;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(PWMqh_TIMtx,&timinit);
	///捕获结构体
	TIM_ICInitTypeDef timinit2;
	//第一个通道设置****************
	timinit2.TIM_Channel=PWMqh_TIMt_Channelx1;
	///滤波器系数在0-f之间
	timinit2.TIM_ICFilter=0;
	//预分频
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//边沿
	timinit2.TIM_ICPolarity=PWMqh_TIMt_Channel_Polarity1;
	//通道选择
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(PWMqh_TIMtx,&timinit2);
	//第二个通道设置**********
	timinit2.TIM_Channel=PWMqh_TIMt_Channelx2;
	///滤波器系数在0-f之间
	timinit2.TIM_ICFilter=0;
	//预分频
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//边沿
	timinit2.TIM_ICPolarity=PWMqh_TIMt_Channel_Polarity1;
	//通道选择
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(PWMqh_TIMtx,&timinit2);
	//***************
	TIM_ClearFlag(PWMqh_TIMtx,TIM_IT_Update|PWMqh_TIMt_IT_CCx1|PWMqh_TIMt_IT_CCx2);
	TIM_ITConfig(PWMqh_TIMtx,TIM_IT_Update|PWMqh_TIMt_IT_CCx1|PWMqh_TIMt_IT_CCx2,ENABLE);
	TIM_Cmd(PWMqh_TIMtx,ENABLE);
}
PWMqh_TIMt_ICValue_TypeDef PWMqh_TIMt_IC_Value;  //定义捕获值结构体
void PWMqh_TIMt_IRQHandler() //12K以下可以检测超前滞后，比较Capture_value1与Capture_value2的大小
{
	//检测溢出
	if(TIM_GetITStatus(PWMqh_TIMtx,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_IT_Update);
		//溢出次数加一
		PWMqh_TIMt_IC_Value.Capture_Period1++;
	}
	if(PWMqh_TIMt_IC_Value.Capture_finish==0)
	{
	if(PWMqh_TIMt_IC_Value.Capture_ci==0)
	{
	if(TIM_GetITStatus(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1)==SET)
	{
		TIM_ClearITPendingBit(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1);
		//第一次捕获
		
			PWMqh_TIMt_IC_Value.Capture_ci=1;
			//捕获到第一个上升沿后开始真正计时,一定要给计数器清零，
			TIM_SetCounter(PWMqh_TIMtx,0);
			PWMqh_TIMt_IC_Value.Capture_Period1=0;
			PWMqh_TIMt_IC_Value.Capture_value1=0;
			TIM_OC1PolarityConfig(PWMqh_TIMtx,TIM_ICPolarity_Rising);
		//关中断后不可以读出正确时间
//		  TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1,DISABLE);
//		  TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx2,ENABLE);
	}
  }
	//第二次捕获
	if(PWMqh_TIMt_IC_Value.Capture_ci==1)
	{
		if(TIM_GetITStatus(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx2)==SET)
		{
			TIM_ClearITPendingBit(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx2);
			PWMqh_TIMt_IC_Value.Capture_ci++;
			//捕获第二路上升沿信号距离第一路上升沿的时间
			PWMqh_TIMt_IC_Value.Capture_value1=TIM_GetCapture2(PWMqh_TIMtx)+1+PWMqh_TIMt_IC_Value.Capture_Period1*0x10000;
			TIM_SetCounter(PWMqh_TIMtx,0);
			PWMqh_TIMt_IC_Value.Capture_Period1=0;
			TIM_OC2PolarityConfig(PWMqh_TIMtx,TIM_ICPolarity_Rising);
//			TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1,ENABLE);
//		  TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx2,DISABLE);
		}
	}
	if(PWMqh_TIMt_IC_Value.Capture_ci==2)
	{
		if(TIM_GetITStatus(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1)==SET)
		{
			TIM_ClearITPendingBit(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1);
			PWMqh_TIMt_IC_Value.Capture_ci=0;
			PWMqh_TIMt_IC_Value.Capture_finish=1;
			//捕获第一路第二次上升沿信号距离前一次第二路上升沿的时间
			PWMqh_TIMt_IC_Value.Capture_value2=TIM_GetCapture1(PWMqh_TIMtx)+1+PWMqh_TIMt_IC_Value.Capture_Period1*0x10000;
			TIM_OC2PolarityConfig(PWMqh_TIMtx,TIM_ICPolarity_Rising);
//			TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1,ENABLE);
//		  TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx2,DISABLE);
		}
	}
  }
	TIM_ClearITPendingBit(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1|PWMqh_TIMt_IT_CCx2);
}
void PWMqh_TIMt_IC_init()
{
	PWMqh_TIMt_IC_GPIO_Config();
	PWMqh_TIMt_NVIC_Config();
	PWMqh_TIMt_IC_Config();
}
//*********************************************/

