#include "ange_exti.h"
void ange_extiinit()
{
	GPIO_InitTypeDef gpioinit;
	EXTI_InitTypeDef extiinit;
	ange_extinvicinit();
		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd (ange_EXTI_GPIO_CLK, ENABLE); 
		RCC_APB2PeriphClockCmd(ange_EXTI_SYSCFG_CLK,ENABLE);  //必须先开时钟再进行操作
		/*选择要控制的GPIO引脚*/															   
		gpioinit.GPIO_Pin = ange_EXTI_GPIO_Pin;	
		/*设置引脚模式为输出模式*/
		gpioinit.GPIO_Mode = GPIO_Mode_IN;   
    /*设置引脚的输出类型为推挽输出*/
    gpioinit.GPIO_OType = GPIO_OType_OD; 
    /*设置引脚为上拉模式*/
    gpioinit.GPIO_PuPd = GPIO_PuPd_DOWN;
		/*设置引脚速率为2MHz */   
		gpioinit.GPIO_Speed = GPIO_Speed_2MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(ange_EXTI_GPIO_PORT, &gpioinit);
	SYSCFG_EXTILineConfig(ange_EXTI_PortSource,ange_EXTI_PinSource);  //配置AFIO->EXTICR寄存器选择EXTIx外部中断的输入源
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

/*

*/
