#include "ange_rcc.h"
void HSE_SetSysClock(u32 RCC_PLLMul_x)
{
	__IO uint32_t HSEStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus==SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{
			
		}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource()!=0x08);
	}
	else
	{
		while(1);
	}
}
void HSI_SetSysClock(u32 RCC_PLLMul_x)
{
	__IO uint32_t HSIStartUpStatus;
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
//	HSIStartUpStatus=GetFlagStatus(RCC_FLAG_HSIRDY);
	HSIStartUpStatus=RCC->CR&RCC_CR_HSIRDY;
	if(HSIStartUpStatus==RCC_CR_HSIRDY)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //使能flash预存取缓冲区
		FLASH_SetLatency(FLASH_Latency_2); //设置sysclk周期与flash访问时间的比例，频率高的同时，不能设置的太小
	RCC_HCLKConfig(RCC_SYSCLK_Div1);   //设置hclk预分频
	RCC_PCLK2Config(RCC_HCLK_Div1);    //APB2预分频
	RCC_PCLK1Config(RCC_HCLK_Div2);    //APB1预分频
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_x); //设置PLL时钟来源，和倍频因子
	RCC_PLLCmd(ENABLE); //开启PLL
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET) //等待PLL时钟稳定
		{
			
		}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //选择PLL为系统时钟
	while(RCC_GetSYSCLKSource()!=0x08); //读取时钟切换状态位，确保PLLCLK为系统时钟
	}
	else
	{
		while(1);
	}
}

