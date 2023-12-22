/**********************************************************************************************************
*	模块名称 : ADC驱动模块
*	文件名称 : bsp_adc.c
*	版    本 : V1.0
*	说    明 : 双ADC同步规则通道采样，ADC1主，ADC2从。该模式下比较特殊，ADC1和ADC2的DR寄存器值分别
			   存32位的ADC_CDR_ADDRESS寄存器的低16位和高16位。
**********************************************************************************************************/
#include "bsp.h"

/* define ---------------------------------------------------------------------*/
#define ADC_CDR_ADDRESS          ((uint32_t)0x40012308)

/* 变量 ----------------------------------------------------------------------*/
__IO uint32_t aADCDualConvertedValue[DMA_BUFFER_SIZE];

/**********************************************************************************************************
*	函 数 名: bsp_InitADC
*	功能说明: ADC初始化
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void bsp_InitADC(void)
{
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;
    NVIC_InitTypeDef      NVIC_InitStructure;
	
	/* 使能外设时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2, ENABLE);
    
    /* 配置引脚 */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* DMA2 Stream0 channel0 配置-------------------------------------------------- */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //ADC1 与DMA2的Stream0的Channel0对应，可参见手册
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&aADCDualConvertedValue;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC_CDR_ADDRESS;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = DMA_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);

    /* Enable DMA Stream Transfer Complete interrupt */
    DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);

    /* DMA2_Stream0 enable */
    DMA_Cmd(DMA2_Stream0, ENABLE);
    
    /* Enable the DMA Stream IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //默认中断优先级分组0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
	/* 
	************************************************************************************************************************
	PCLK2 = HCLK / 2 
	下面选择的是2分频 
	ADCCLK = PCLK2 / 8 = HCLK / 16 = 168 / 16 = 10.5M 
	ADC采样频率： Sampling Time + Conversion Time = 480 + 12 cycles = 492cyc 
	              Conversion Time = 10.5MHz / 492cyc = 21ksps.
	************************************************************************************************************************
	*/
	/* ADC 公共部分配置 *************************************************/ 
	// 480+12周期转换 二分频一次转换1/42M*492=11.7us  11.7us对应计数器初值在 1968  最高取样频率168000000/2000=84000
    ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_RegSimult;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_2;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //两次采样之间的延时时间，总采样时间12+5+480
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC3;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    
    /* ADC1规则通道0配置 */ 
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles); //ADC_SampleTime_480Cycles表示采样消耗时间
   
    /* ADC2规则通道0配置 */ 
    ADC_Init(ADC2, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1, ADC_SampleTime_480Cycles);// 不要在2个ADC上转换相同的通道（手册），channel_10对应双ADC模式

    /* 使能DMA请求 (多ADC模式) */
    ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
    
    /* 使能 ADC1 */
    ADC_Cmd(ADC1, ENABLE);
    /* 使能 ADC2 */
    ADC_Cmd(ADC2, ENABLE);
    
    /* 启动转换由外部定时器TIM1触发 */
//    ADC_SoftwareStartConv(ADC2);
}

/**********************************************************************************************************
*	函 数 名: bsp_ADCTrigEnable，bsp_ADCTrigDisable
*	功能说明: ADC定时器外触发使能和关闭
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void bsp_ADCTrigEnable(void)
{
	TIM_CtrlPWMOutputs(TIM1, ENABLE);  	//使能TIM1通道OC3的PWM 输出
}

void bsp_ADCTrigDisable(void)
{
	TIM_CtrlPWMOutputs(TIM1, DISABLE);  	//关闭TIM1通道OC3的PWM 输出
}
