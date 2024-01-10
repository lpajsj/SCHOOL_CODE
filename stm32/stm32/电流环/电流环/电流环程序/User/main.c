#include "stm32f10x.h"
#include "AD5410.H"
#include "usart.h"
void Delay_ms(uint32_t ms) //���뼶��ʱ����
{
	uint32_t i;
	SysTick_Config(72000);
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//�ر�ϵͳ��ʱ��
}
int main()
{
	uint32_t dat=0;
	USART_Config();//���ڳ�ʼ��
	AD5410_GPIO_Init();//5410�����ų�ʼ��
	AD5410_Init();//5410��ʼ��
	dat=AD5410_ReadDate(0x020002);//�ض����ƼĴ���
	printf("%x",dat);
	while(1)
	{
//		AD5410_SendDate(0x01fff0);//���20mV����	
//		AD5410_SendDate(0x010000);//���0mV����
	}
}
