#include "clkconfig.h"


void User_SetSysClock(void)
{
	//��λRCC���мĴ���
	RCC_DeInit();
	
/******************************************************************************/
/*            PLL (clocked by HSE) used as System clock source                */
/******************************************************************************/
	
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	
  /* Enable HSE */
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
	do
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
	{
		HSEStatus = (uint32_t)0x01;
	}
	else
	{
		HSEStatus = (uint32_t)0x00;
	}

	if (HSEStatus == (uint32_t)0x01)
	{
		/* Select regulator voltage output Scale 1 mode */
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;

		/* HCLK = SYSCLK / 1*/
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

		/* PCLK2 = HCLK / 2*/
		RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
    
		/* PCLK1 = HCLK / 4*/
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

//----------------------------------------------------------
//��    ��         : pllm��VCO ����ʱ�� ��Ƶ���ӣ���Χ0-63
//					 plln��VCO ���ʱ�� ��Ƶ���ӣ���Χ192-432
//					 pllp��PLLCLK ʱ�ӷ�Ƶ���ӣ���Χ2, 4, 6, or 8
//					 pllq��OTG FS,SDIO,RNG ʱ�ӷ�Ƶ���ӣ���Χ4-15
//����8��HSE�ⲿʱ��8MHz��336�Ǳ�Ƶ��2�Ƿ�Ƶ�����մﵽ168MHz��
		/* Configure the main PLL */
		RCC->PLLCFGR = 8 | (336 << 6) | (((2 >> 1) -1) << 16) |
					   (RCC_PLLCFGR_PLLSRC_HSE) | (7 << 24);
		
		/* Enable the main PLL */
		RCC->CR |= RCC_CR_PLLON;

		/* Wait till the main PLL is ready */
		while((RCC->CR & RCC_CR_PLLRDY) == 0);

		/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

		/* Select the main PLL as system clock source */
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= RCC_CFGR_SW_PLL;

		/* Wait till the main PLL is used as system clock source */
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    
	  }
	  else
	  { /* If HSE fails to start-up, the application will have wrong clock
			 configuration. User can add here some code to deal with this error */
	  }

}

void HSE_SetSysClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{
	
	
	/* ��λRCC���мĴ��� */
	RCC_DeInit();
	
	ErrorStatus HSE_ErrorStatus = ERROR;
	
	/* Enable HSE */
	/* ʹ�� HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSE_ErrorStatus = RCC_WaitForHSEStartUp();
	
	if(HSE_ErrorStatus == SUCCESS)
	{
		/* Select regulator voltage output Scale 1 mode */
		/* ѡ���ѹ����ģʽΪģʽ1 */
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;
		
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div4);
		RCC_PCLK2Config(RCC_HCLK_Div2);

		/* Configure the main PLL */
		RCC_PLLConfig(RCC_PLLSource_HSE,PLLM,PLLN,PLLP,PLLQ);
	
		/* Enable the main PLL */
		RCC_PLLCmd(ENABLE);
		
		/* Wait till the main PLL is ready */
		while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
		
		/* Select the main PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		/* Wait till the main PLL is used as system clock source */
	/*	����ֵ The clock source used as system clock. The returned value can be one
	 *         of the following:
	 *              - 0x00: HSI used as system clock
	 *              - 0x04: HSE used as system clock
	 *              - 0x08: PLL used as system clock (PLL P for STM32F446xx devices)
	 *              - 0x0C: PLL R used as system clock (only for STM32F446xx devices)
	 */
		while( RCC_GetSYSCLKSource() != 0x08);
		
	}
	else
	{
		/* HSE����ʧ�ܣ��ڴ���Ӵ�������� */
	}

}

void HSI_SetSysClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{
	
	
	/* ��λRCC���мĴ��� */
	RCC_DeInit();
	
	volatile uint32_t HSI_ErrorStatus = 0;
	
	/* Enable HSI */
	/* ʹ�� HSI */
	RCC_HSICmd(ENABLE);


	/* Wait till HSI is ready */
	HSI_ErrorStatus = RCC->CR & RCC_CR_HSIRDY;
	
	if(HSI_ErrorStatus == RCC_CR_HSIRDY)
	{
		/* Select regulator voltage output Scale 1 mode */
		/* ѡ���ѹ����ģʽΪģʽ1 */
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;
		
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div4);
		RCC_PCLK2Config(RCC_HCLK_Div2);

		/* Configure the main PLL */
		RCC_PLLConfig(RCC_PLLSource_HSI,PLLM,PLLN,PLLP,PLLQ);
	
		/* Enable the main PLL */
		RCC_PLLCmd(ENABLE);
		
		/* Wait till the main PLL is ready */
		while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
		
		/* Select the main PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		/* Wait till the main PLL is used as system clock source */
	/*	����ֵ The clock source used as system clock. The returned value can be one
	 *         of the following:
	 *              - 0x00: HSI used as system clock
	 *              - 0x04: HSE used as system clock
	 *              - 0x08: PLL used as system clock (PLL P for STM32F446xx devices)
	 *              - 0x0C: PLL R used as system clock (only for STM32F446xx devices)
	 */
		while( RCC_GetSYSCLKSource() != 0x08);
		
	}
	else
	{
		/* HSI����ʧ�ܣ��ڴ���Ӵ�������� */
	}

}



