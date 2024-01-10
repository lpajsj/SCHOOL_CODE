#include "stm32f10x.h"
#include "AD5410.H"
#include "usart.h"
void Delay_ms(uint32_t ms) //毫秒级延时函数
{
	uint32_t i;
	SysTick_Config(72000);
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//关闭系统定时器
}
int main()
{
	uint32_t dat=0;
	USART_Config();//串口初始化
	AD5410_GPIO_Init();//5410的引脚初始化
	AD5410_Init();//5410初始化
	dat=AD5410_ReadDate(0x020002);//回读控制寄存器
	printf("%x",dat);
	while(1)
	{
//		AD5410_SendDate(0x01fff0);//输出20mV电流	
//		AD5410_SendDate(0x010000);//输出0mV电流
	}
}
