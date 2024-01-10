
#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_rcc.h"
#define SOFT_DELAY Delay(0x0FFFFF);
#define RGPIOC13 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
#define RGPIOA0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
void Delay(u32 nCount); 
u8 anjian(void);
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main()
{	
			u8 x=0,y=0,a;
	uint32_t d=0xfffff;
	HSE_SetSysClock(RCC_PLLMul_9);  //改变频率超频
	/* LED 端口初始化 */
//	LED_GPIO_Config();
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE);	
//RRC_APB2PeriohClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		GPIO_InitTypeDef GPIOInit;
		GPIOInit.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5;
		GPIOInit.GPIO_Speed=GPIO_Speed_10MHz;
		GPIOInit.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB,&GPIOInit);
		GPIOInit.GPIO_Pin=GPIO_Pin_13;
		GPIOInit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC,&GPIOInit);
		GPIOInit.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIOInit);
	while (1)
	{
		a=anjian();
		if(a==2)
		{
			x=!x;
		}
		else if(a==1)
		{
			y=!y;
			if(y)
		{
			d=0x5fffff;
		}
		else
		{
			d=0xfffff;
		}
		}
		if(x)
		{
		GPIOB->BSRR=GPIO_Pin_All;
		GPIOB->BRR=GPIO_Pin_0|GPIO_Pin_1;
		}
		else
		{
		GPIOB->BSRR=GPIO_Pin_All;
		GPIOB->BRR=GPIO_Pin_0|GPIO_Pin_5;
		}
		Delay(d);
		GPIOB->BSRR=GPIO_Pin_All;
		Delay(d);
	}
}
u8 anjian(void)
{
	if(RGPIOC13==1)
	{
		SOFT_DELAY;
	if(RGPIOC13==1)
		while(RGPIOC13==1);
			return 0x01;
	}
	else if(RGPIOA0==1)
	 {
		SOFT_DELAY;
	if(RGPIOA0==1)
		while(RGPIOA0==1);
	return 0x02;
   }
	else
	{
		return 0x00;
	}

}

void Delay(uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
