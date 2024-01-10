#include "pwm.h"
#include "ange_usart.h"
#include "ange_systick.h"
#if PWM_xiangwei
//是捕获啊，为相位而生************************************************************/ 
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
	TIM_ClearFlag(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1);  //只开通道1中断
	TIM_ITConfig(PWMqh_TIMtx,PWMqh_TIMt_IT_CCx1,ENABLE);
	TIM_Cmd(PWMqh_TIMtx,ENABLE);
}
/**************************************************************************************
***************************************************************************************/
PWMqh_TIMt_ICValue_TypeDef PWMqh_TIMt_IC_Value;  //定义捕获值结构体
void PWMqh_TIMt_IRQHandler() //修改于2021-8-1，测试nice
{
	if(TIM_GetFlagStatus(PWMqh_TIMtx,TIM_FLAG_CC1)==SET)  //只开通道1中断
	{
		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_FLAG_CC1); //清除中断标志位
		if(PWMqh_TIMt_IC_Value.Capture_finish==0)  //判断是否读取完数据
		{
		if((PWMqh_TIMt_IC_Value.Capture_ci==0)&&(PWMqh_TIMt_IC_Value.Capture_finish==0))
		{
			TIM_SetCounter(PWMqh_TIMtx,0);    //读取通道1上升沿后将数据清零，
			PWMqh_TIMt_IC_Value.Capture_ci=1;		//1.48us +0.15	
			
		}
		else if((PWMqh_TIMt_IC_Value.Capture_ci==1)&&(PWMqh_TIMt_IC_Value.Capture_finish==0)) //第二次直接将通道一和通道二的捕获数值一起读出
		{
			PWMqh_TIMt_IC_Value.Capture_value2=TIM_GetCapture2(PWMqh_TIMtx);
			PWMqh_TIMt_IC_Value.Capture_value1=TIM_GetCapture1(PWMqh_TIMtx);
			PWMqh_TIMt_IC_Value.Capture_finish=1;
			PWMqh_TIMt_IC_Value.Capture_ci=0;
		}
	  }
		
	}
//	if(TIM_GetFlagStatus(PWMqh_TIMtx,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_IT_Update);
//	}

}
void PWMqh_TIMt_IC_init()
{
	PWMqh_TIMt_IC_GPIO_Config();
	PWMqh_TIMt_NVIC_Config();
	PWMqh_TIMt_IC_Config();
}
//*********************************************/
void PWMqh_TIMt_panduan()
{
		if(PWMqh_TIMt_IC_Value.Capture_finish)
		{
			PWMqh_TIMt_IC_Value.t1=(double)((PWMqh_TIMt_IC_Value.Capture_value1+1))/72; //得出以微妙为单位
			PWMqh_TIMt_IC_Value.t2=(double)((PWMqh_TIMt_IC_Value.Capture_value2+1))/72;
			PWMqh_TIMt_IC_Value.t1+=1.48+0.15;       //加上补偿值
			PWMqh_TIMt_IC_Value.t2+=1.48+0.15;       //第一次上升沿到中断中把计时器置零的时间
			if(PWMqh_TIMt_IC_Value.t2>PWMqh_TIMt_IC_Value.t1) //如果通道2的上升沿距离通道一的上升沿的时间太短，很可能通道二的捕获值会多记一个周期
				PWMqh_TIMt_IC_Value.t2-=PWMqh_TIMt_IC_Value.t1;
			PWMqh_TIMt_IC_Value.xiangwei=PWMqh_TIMt_IC_Value.t2/PWMqh_TIMt_IC_Value.t1*360; //计算出相位
			if(PWMqh_TIMt_IC_Value.xiangwei>180)
				PWMqh_TIMt_IC_Value.xiangwei-=360;  //加上正负号
			PWMqh_TIMt_IC_Value.pinlv=1000000/PWMqh_TIMt_IC_Value.t1;  //求出频率
			delayms_PWM(100);  //延时
			PWMqh_TIMt_IC_Value.Capture_finish=0;	 //清除转换完成标志位
		}
}
#endif
