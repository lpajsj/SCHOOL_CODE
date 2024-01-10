//#include "stm32f10x.h"
//#include "bsp_led.h"
//#include "ange_dma.h"
//#include "ange_usart.h"
//#include "stdio.h"
//#include "ange_iic.h"
//#include "ange_systick.h"
//#include "ange_ad.h"
//extern u16 adc1zhi11;
//int main()
//{
//	float x;
//	ange_USART_init();
//	LED_GPIO_Config();
//	ange_ADC_init();
//	while(1)
//	{
//		x=(float)adc1zhi11/4096*3.3; //中断读取
//		printf("16进制形式%04x\r\n",adc1zhi11);
//		printf("电压值%f\r\n",x);
//		printf("\r\n");
//		SysTick_delayms(1000);
//		LED1_TOGGLE;
//	}
//}
////////////////////////
//#include "stm32f10x.h"
//#include "bsp_led.h"
//#include "ange_dma.h"
//#include "ange_usart.h"
//#include "stdio.h"
//#include "ange_iic.h"
//#include "ange_systick.h"
//#include "ange_ad.h"
//extern u16 adc1zhi11;
//u16 addmazhi;
//int main()
//{
//	float x;
//	ange_USART_init();
//	LED_GPIO_Config();
//	ange_ADC_init();
//	ange_DMA_WC_ADCConfig(ange_DMA_yuan,(u32)&addmazhi);
//	ADC_DMACmd(ange_ADCx,ENABLE);
//	while(1)
//	{
//		x=(float)(addmazhi)/4096*3.3;
//		printf("16进制形式%04x\r\n",addmazhi);
//		printf("电压值%f\r\n",x);
//		printf("\r\n");
//		SysTick_delayms(1000);
//		LED1_TOGGLE;
//	}
//}
#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_dma.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_iic.h"
#include "ange_systick.h"
#include "ange_ad.h"
extern u16 adc1zhi11;
u16 addmazhi[5];
int main()
{
	float x;
	u8 i;
	ange_USART_init();
	LED_GPIO_Config();
	ange_ADC_init();
	ange_DMA_WC_ADCConfig(ange_DMA_yuan,(u32)&addmazhi);
	SysTick_delayms(10);
	ADC_DMACmd(ange_ADCx,ENABLE);////不要忘了应该放到软件触发之前，全部配置完后再使能
	while(1)
	{
		for(i=0;i<5;i++)
		{
		x=(float)(addmazhi[i])/4096*3.3;
		printf("第%d路16进制形式%04x\r\n",i,addmazhi[i]);
		printf("电压值%f\r\n",x);
		}
		printf("\r\n");
		SysTick_delayms(1000);
		LED1_TOGGLE;
	}
}

