#include "ange_exti.h"
#include "bsp_led.h"
void ange_extiinit()
{
	GPIO_InitTypeDef gpioinit;
	EXTI_InitTypeDef extiinit;
	ange_extinvicinit();
//	RCC_APB2PeriphClockCmd(ange_EXTI_CLK,ENABLE);
	gpioinit.GPIO_Pin=ange_EXTI_GPIO_Pin;
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(ange_EXTI_GPIO_PORT,&gpioinit);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	extiinit.EXTI_Line=ange_EXTI_Line;
	extiinit.EXTI_Mode=EXTI_Mode_Interrupt;
	extiinit.EXTI_Trigger=EXTI_Trigger_Rising;
	extiinit.EXTI_LineCmd=ENABLE;
	EXTI_Init(&extiinit);
	RCC_APB2PeriphClockCmd(ange_EXTI_CLK,ENABLE);
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

*/
