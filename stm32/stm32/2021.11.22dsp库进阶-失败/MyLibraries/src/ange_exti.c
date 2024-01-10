#include "ange_exti.h"
#include "bsp_led.h"
/*
//外部中断配置
ange_extinvicinit();
ange_extiinit();
*/
void ange_extiinit()
{
	GPIO_InitTypeDef gpioinit;
	EXTI_InitTypeDef extiinit;
	ange_extinvicinit();
	RCC_APB2PeriphClockCmd(ange_EXTI_CLK,ENABLE);
	gpioinit.GPIO_Pin=ange_EXTI_GPIO_Pin;
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(ange_EXTI_GPIO_PORT,&gpioinit);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  //配置AFIO->EXTICR寄存器选择EXTIx外部中断的输入源
	extiinit.EXTI_Line=ange_EXTI_Line;
	extiinit.EXTI_Mode=EXTI_Mode_Interrupt;
	extiinit.EXTI_Trigger=EXTI_Trigger_Rising;
	extiinit.EXTI_LineCmd=ENABLE;   //配置中断屏蔽，事件屏蔽寄存器
	EXTI_Init(&extiinit);

}
void ange_extinvicinit()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_EXTI_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
////////////////////////////////////
void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(ange_EXTI_Line)!=RESET)
	{
		LED1_TOGGLE;
		EXTI_ClearITPendingBit(ange_EXTI_Line); //EXTI_Line0
	}
}
/*
● EXTI线16连接到PVD输出
● EXTI线17连接到RTC闹钟事件
● EXTI线18连接到USB唤醒事件
● EXTI线19连接到以太网唤醒事件(只适用于互联型产品)
*/
