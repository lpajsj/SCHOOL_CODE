#include "ange_rcc.h"
//VCO 时钟必须在 192~432M之间
//pllclk=hse/M*n/p 
/*
 * 使用HSE时，设置系统时钟的步骤
 * 1、开启HSE ，并等待 HSE 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源
 *    设置VCO输入时钟 分频因子        m
 *    设置VCO输出时钟 倍频因子        n
 *    设置PLLCLK时钟分频因子          p
 *    设置OTG FS,SDIO,RNG时钟分频因子 q
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/*
 * m: VCO输入时钟 分频因子，取值2~63
 * n: VCO输出时钟 倍频因子，取值192~432
 * p: PLLCLK时钟分频因子  ，取值2，4，6，8
 * q: OTG FS,SDIO,RNG时钟分频因子，取值4~15
 * 函数调用举例，使用HSE设置时钟
 * SYSCLK=HCLK=168M,PCLK2=HCLK/2=84M,PCLK1=HCLK/4=42M
 * HSE_SetSysClock(25, 336, 2, 7);
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 
 * 系统时钟超频到216M爽一下
 * HSE_SetSysClock(25, 432, 2, 9);
 */
void HSE_SetSysClock(u32 m,u32 n,u32 p,u32 q)
{
	__IO uint32_t HSEStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus==SUCCESS)
	{
    // 调压器电压输出级别配置为1，以便在器件为最大频率
		// 工作时使性能和功耗实现平衡
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
		
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PLLConfig(RCC_PLLSource_HSE,m,n,p,q);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{
			
		}
//配置flash预取指，指令缓存，数据缓存，等待周期，超频后等待周期要加加长
	FLASH_PrefetchBufferCmd(ENABLE);
	FLASH_SetLatency(FLASH_Latency_5);
	FLASH_InstructionCacheCmd(ENABLE);
	FLASH_DataCacheCmd(ENABLE);
//    FLASH->ACR = FLASH_ACR_PRFTEN 
//		            | FLASH_ACR_ICEN 
//		            | FLASH_ACR_DCEN 
//		            | FLASH_ACR_LATENCY_5WS;	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource()!=0x08);
	}
	else
	{
		while(1);
	}
}
/*
 * 使用HSI时，设置系统时钟的步骤
 * 1、开启HSI ，并等待 HSI 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源
 *    设置VCO输入时钟 分频因子        m
 *    设置VCO输出时钟 倍频因子        n
 *    设置SYSCLK时钟分频因子          p
 *    设置OTG FS,SDIO,RNG时钟分频因子 q
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/*
 * m: VCO输入时钟 分频因子，取值2~63
 * n: VCO输出时钟 倍频因子，取值192~432
 * p: PLLCLK时钟分频因子  ，取值2，4，6，8
 * q: OTG FS,SDIO,RNG时钟分频因子，取值4~15
 * 函数调用举例，使用HSI设置时钟
 * SYSCLK=HCLK=168M,PCLK2=HCLK/2=84M,PCLK1=HCLK/4=42M
 * HSI_SetSysClock(16, 336, 2, 7);
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 
 * 系统时钟超频到216M爽一下
 * HSI_SetSysClock(16, 432, 2, 9);
 */
void HSI_SetSysClock(u32 m,u32 n,u32 p,u32 q)
{
	__IO uint32_t HSIStartUpStatus;
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	HSIStartUpStatus=RCC->CR&RCC_CR_HSIRDY;
	if(HSIStartUpStatus==RCC_CR_HSIRDY)
	{
    // 调压器电压输出级别配置为1，以便在器件为最大频率
		// 工作时使性能和功耗实现平衡
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
		
	RCC_HCLKConfig(RCC_SYSCLK_Div1);   //设置hclk预分频
	RCC_PCLK2Config(RCC_HCLK_Div2);    //APB2预分频
	RCC_PCLK1Config(RCC_HCLK_Div4);    //APB1预分频
	RCC_PLLConfig(RCC_PLLSource_HSI,m,n,p,q); //设置PLL时钟来源，和倍频因子
	RCC_PLLCmd(ENABLE); //开启PLL
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET) //等待PLL时钟稳定
		{
			
		}
//配置flash预取指，指令缓存，数据缓存，等待周期，超频后等待周期要加加长
	FLASH_PrefetchBufferCmd(ENABLE);  //
	FLASH_SetLatency(FLASH_Latency_5);
	FLASH_InstructionCacheCmd(ENABLE);
	FLASH_DataCacheCmd(ENABLE);
		// 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //选择PLL为系统时钟
	while(RCC_GetSYSCLKSource()!=0x08); //读取时钟切换状态位，确保PLLCLK为系统时钟
	}
	else
	{
		while(1);
	}
}

