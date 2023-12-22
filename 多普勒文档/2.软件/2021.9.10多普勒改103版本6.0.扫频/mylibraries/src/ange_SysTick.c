#include <stm32f10x.h>
#include "ange_SysTick.h"
void SysTick_Handler(void)  //ÿ�ν����ж�SysTickdelayj--
{
//	SysTickdelay();
}
__IO u32 SysTickdelayj;
void SysTick_delayms(uint32_t n)  //1ms
{
	u32 i;
	SysTick_Config(72000);
	for(i=0;i<n;i++)
	{
		while(((SysTick->CTRL)&(1<<16))==0);
	}
	SysTick->CTRL&=~0x01;
}
void SysTick_delayus(uint32_t n)  //1us
{
	u32 i;
	SysTick_Config(72);
	for(i=0;i<n;i++)
	{
		while(((SysTick->CTRL)&(1<<16))==0);
	}
	SysTick->CTRL&=~0x01;
}
///////////////��һ�ַ���
//SysTickInitus() -> sdelay()
void SysTickdelay()  ///�ŵ��ж���
{
	if(SysTickdelayj!=0)
	{
		SysTickdelayj--;
	}
}
void SysTickInitus()  ///��ʼ������10us
{
	SysTick_Config(720);
}
void SysTickInitms()  ///��ʼ������1ms
{
	SysTick_Config(72000);
}
void sdelay(u32 n)  //Ҫ���õĺ�����ʱʱ��Ϊ n*SysTickInit()��ʱ��
{
	SysTickdelayj=n;
	while(SysTickdelayj!=0);
}
