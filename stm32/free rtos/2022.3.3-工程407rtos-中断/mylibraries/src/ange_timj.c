#include "ange_timj.h"
#include "main.h"
#include "ange_USART.h"
uint32_t time1=0;
static void ange_TIMj_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
//	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);
	nvicinit.NVIC_IRQChannel=ange_TIMj_IRQ;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	nvicinit.NVIC_IRQChannelPreemptionPriority=6;
	nvicinit.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvicinit);
}
static void ange_TIMj_Config()
{
	TIM_TimeBaseInitTypeDef timinit;    
	ange_TIMj_APBxClock(ange_TIMj_CLK,ENABLE);     //tim时钟在apb1
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;   //ckint,和死区发生器以及数字滤波器采样时钟频率分频比 基本定时器无
	timinit.TIM_Prescaler=8400-1;  //ck_psc分频
	timinit.TIM_CounterMode=TIM_CounterMode_Up;  //定时器计数方式，基本定时器只有上升模式
	timinit.TIM_Period=10000-1;     //计数器重装值
	timinit.TIM_RepetitionCounter=0;  //重复计数器，只存在高级定时器
	TIM_TimeBaseInit(ange_TIMjx,&timinit);//定时器基本初始化
//	TIM_ClearFlag(ange_TIMjx,TIM_FLAG_Update); //清除溢出标志
	TIM_ITConfig(ange_TIMjx,TIM_IT_Update,ENABLE); //使能溢出中断
	TIM_Cmd(ange_TIMjx,ENABLE);  //使能TIM

}

void ange_TIMj_init()
{
	ange_TIMj_NVIC_Config();
	ange_TIMj_Config();
}
void ange_TIMj_IRQHandler()
{
	if(TIM_GetITStatus(ange_TIMjx,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(ange_TIMjx,TIM_IT_Update);
		printf("tim中断123455\n");
		if(time1>0)time1--;
	}
	
}


//tim5定时初始化
void Initial_System_Timer5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFFFFFF; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;       //定时器分频 1us
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //不开中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器3
}

//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x04; //抢占优先级4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//通用定时器5中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器5!
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	//使能TIM5时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 		//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  		//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);	//初始化TIM5
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); 			//允许定时器5更新中断
	TIM_Cmd(TIM5,ENABLE); 								//使能定时器5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; 		//定时器5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x05; 	//抢占优先级5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; 		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		printf("TIM3输出.......\r\n");
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}


//定时器5中断服务函数
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		printf("TIM5输出.......\r\n");
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}

