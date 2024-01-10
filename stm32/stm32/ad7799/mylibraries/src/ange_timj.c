#include "ange_timj.h"
uint32_t time=0;
//static void ange_TIMj_Config()
//{
//	TIM_TimeBaseInitTypeDef timinit;    
//	ange_TIMj_APBxClock(ange_TIMj_CLK,ENABLE);     //tim时钟在apb1
//	timinit.TIM_ClockDivision=TIM_CKD_DIV1;   //ckint,和死区发生器以及数字滤波器采样时钟频率分频比 基本定时器无
//	timinit.TIM_Prescaler=71;  //ck_psc分频
//	timinit.TIM_CounterMode=TIM_CounterMode_Up;  //定时器计数方式，基本定时器只有上升模式
//	timinit.TIM_Period=1000-1;     //计数器重装值
//	timinit.TIM_RepetitionCounter=0;  //重复计数器，只存在高级定时器
//	TIM_TimeBaseInit(ange_TIMjx,&timinit);//定时器基本初始化
//	TIM_ClearFlag(ange_TIMjx,TIM_FLAG_Update); //清除溢出标志
//	TIM_ITConfig(ange_TIMjx,TIM_IT_Update,ENABLE); //使能溢出中断
//	TIM_Cmd(ange_TIMjx,ENABLE);  //使能TIM
//}
//static void ange_TIMj_NVIC_Config()
//{
//	NVIC_InitTypeDef nvicinit;
//	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_1);
//	nvicinit.NVIC_IRQChannel=ange_TIMj_IRQ;
//	nvicinit.NVIC_IRQChannelCmd=ENABLE;
//	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
//	nvicinit.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&nvicinit);
//}
//void ange_TIMj_init()
//{
//	ange_TIMj_NVIC_Config();
//	ange_TIMj_Config();
//}
//void ange_TIMj_IRQHandler()
//{
//	if(TIM_GetITStatus(ange_TIMjx,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(ange_TIMjx,TIM_IT_Update);
//		time++;
//	}
//}

