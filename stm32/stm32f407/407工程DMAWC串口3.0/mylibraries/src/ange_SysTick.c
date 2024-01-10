#include "stm32f4xx.h"
#include "ange_SysTick.h"
__IO u32 SysTickdelayj;
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
	SysTick_Config(1680);
}
void SysTickInitms()  ///��ʼ������1ms
{
	SysTick_Config(168000);
}
void sdelay(u32 n)  //Ҫ���õĺ�����ʱʱ��Ϊ n*SysTickInit()��ʱ��
{
	SysTickdelayj=n;
	while(SysTickdelayj!=0);
}
