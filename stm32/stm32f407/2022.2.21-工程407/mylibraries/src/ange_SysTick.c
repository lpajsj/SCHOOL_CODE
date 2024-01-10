#include "stm32f4xx.h"
#include "ange_SysTick.h"
__IO u32 SysTickdelayj;
__IO u32 SysTickdelayj2;
void SysTick_delayms(uint32_t n)  //1ms
{
	u32 i;
	SysTick_Config(168000);
	for(i=0;i<n;i++)
	{
		while(((SysTick->CTRL)&(1<<16))==0);
	}
	SysTick->CTRL&=~0x01;
}
void SysTick_delayus(uint32_t n)  //1us
{
	u32 i;
	SysTick_Config(168);
	for(i=0;i<n;i++)
	{
		while(((SysTick->CTRL)&(1<<16))==0);
	}
	SysTick->CTRL&=~0x01;
}
///////////////另一种方法
//SysTickInitus() -> sdelay()
void SysTickInitus()  ///初始化配置10us
{
	SysTick_Config(1680);
}
void SysTickInitms()  ///初始化配置1ms
{
	SysTick_Config(168000);
}

void SysTickreduce()  ///放到中断中
{
	if(SysTickdelayj!=0)
	{
		SysTickdelayj--;
	}
}
void sdelay(u32 n)  //要调用的函数延时时间为 n*SysTickInit()的时间
{
	SysTickdelayj=n;
	while(SysTickdelayj!=0);
}

void SysTickreduce2()  ///放到中断中
{
	if(SysTickdelayj2!=0)
	{
		SysTickdelayj2--;
	}
}
void sdelay2(u32 n)  //要调用的函数延时时间为 n*SysTickInit()的时间
{
	SysTickdelayj2=n;
	while(SysTickdelayj2!=0);
}
