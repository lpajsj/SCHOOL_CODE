#include <stm32f10x.h>
#include "ange_SysTick.h"
__IO u32 SysTickdelayj;
void SysTick_delayms(uint32_t n)
{
	u32 i;
	SysTick_Config(72000);
	for(i=0;i<n;i++)
	{
		while(((SysTick->CTRL)&(1<<16))==0);
	}
	SysTick->CTRL&=~0x01;
}
void SysTick_delayus(uint32_t n)
{
	u32 i;
	SysTick_Config(720);
	for(i=0;i<n;i++)
	{
		while(((SysTick->CTRL)&(1<<16))==0);
	}
	SysTick->CTRL&=~0x01;
}
void SysTickdelay()
{
	if(SysTickdelayj!=0)
	{
		SysTickdelayj--;
	}
}
void SysTickInit()
{
	SysTick_Config(720);
}
void delayus(u32 n)
{
	SysTickdelayj=n;
	while(SysTickdelayj!=0);
}
