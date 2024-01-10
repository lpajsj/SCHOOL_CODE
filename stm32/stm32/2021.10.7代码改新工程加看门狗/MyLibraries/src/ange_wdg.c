#include "ange_wdg.h"
#include "bsp_led.h"  
/*独立看门狗*/
/*
简述：独立看门狗初始化，
变量：  
presalder:独立看门狗预分频 LSI 40khz/presaler
  *     @arg IWDG_Prescaler_4: IWDG prescaler set to 4
  *     @arg IWDG_Prescaler_8: IWDG prescaler set to 8
  *     @arg IWDG_Prescaler_16: IWDG prescaler set to 16
  *     @arg IWDG_Prescaler_32: IWDG prescaler set to 32
  *     @arg IWDG_Prescaler_64: IWDG prescaler set to 64
  *     @arg IWDG_Prescaler_128: IWDG prescaler set to 128
  *     @arg IWDG_Prescaler_256: IWDG prescaler set to 256
	counter: 预装载值
返回值：无
*/
//可以利用RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET判断是否是IWDG复位
//复位后iWDG看门狗就失效了重新配置后生效，iwdg不用开时钟 
void ange_iwdg_init(u8 presaler,u16 counter)
{
	//独立看门狗在改变预分频以及计数器值时一定要先在键寄存器中写入0x55
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//设置LSI到独立看门狗的时钟分频因子，LSI时钟为40KHZ
	IWDG_SetPrescaler(presaler);
	//设置计数器预装载值
	IWDG_SetReload(counter);
	//要把值加载到计数器
	IWDG_ReloadCounter();
	//使能IWDG
	IWDG_Enable();
}
void ange_iwdg_feed()
{
	IWDG_ReloadCounter();
}
/*窗口看门狗*/
//窗口看门狗在计数器到达0x40时会产生中断，然后复位，如果计数器值在大于窗口值时被重新赋值则也会发生复位
//窗口值在CFR寄存器的低七位，计数器值在CR寄存器的低七位//没有计数预装载
void ange_wwdg_nvic_init()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=WWDG_IRQn;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvicinit);
}
//窗口看门狗复位程序,只清除标志还是会复位，且此中断是只是40H中断
//复位即将发生，不可以在这里设置计数器的值，若设置反而会更快复位
// WWDG 中断复服务程序，如果发生了此中断，表示程序已经出现了故障，
// 这是一个死前中断。在此中断服务程序中应该干最重要的事，
// 比如保存重要的数据等，这个时间具体有多长，要
// 由WDGTB的值决定：
// WDGTB:0   113us
// WDGTB:1   227us
// WDGTB:2   455us
// WDGTB:3   910us
void WWDG_IRQHandler()
{
//	WWDG_SetCounter(0x7f);
	WWDG_ClearFlag();

//	LED_GREEN;
//  WWDG_SetCounter(0x7f);
}
/*
简述：窗口看门狗初始化，包括NVIC，中断开启
变量：
prescaler：wwdg的时钟为APB1clk/4096/prescaler
  *     @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1  113us
  *     @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2  227us
  *     @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4  455us
  *     @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8  910us
counter:计数器的值
window：窗口值，计数器的值若大于窗口值时被重新装载将会发生复位
返回值： 无
wr=WWDG->CFR&0x7f; //取窗口看门口的值
*/
void ange_wwdg_init(u32 prescaler,u8 counter,u8 window)
{
	//开启窗口看门狗时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	//设置预分频
	WWDG_SetPrescaler(prescaler);
	//计数器
	WWDG_SetCounter(counter);
	//窗口值
	WWDG_SetWindowValue(window);
	ange_wwdg_nvic_init();
	//使能,在这里赋值时由于此时赋值计数器值大于窗口值会造成直接将中断标志位置一
	WWDG_Enable(counter);
	WWDG_ClearFlag();
		//开启0x40中断
	WWDG_EnableIT();
}



