/**********************************************************************************************************
*	ģ������ : ADC����ģ��
*	�ļ����� : bsp_adc.c
*	��    �� : V1.0
*	˵    �� : ˫ADCͬ������ͨ��������ADC1����ADC2�ӡ���ģʽ�±Ƚ����⣬ADC1��ADC2��DR�Ĵ���ֵ�ֱ�
			   ��32λ��ADC_CDR_ADDRESS�Ĵ����ĵ�16λ�͸�16λ��
**********************************************************************************************************/
#include "bsp.h"

/* define ---------------------------------------------------------------------*/
#define ADC_CDR_ADDRESS          ((uint32_t)0x40012308)

/* ���� ----------------------------------------------------------------------*/
__IO uint32_t aADCDualConvertedValue[DMA_BUFFER_SIZE];

/**********************************************************************************************************
*	�� �� ��: bsp_InitADC
*	����˵��: ADC��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void bsp_InitADC(void)
{
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;
    NVIC_InitTypeDef      NVIC_InitStructure;
	
	/* ʹ������ʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2, ENABLE);
    
    /* �������� */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* DMA2 Stream0 channel0 ����-------------------------------------------------- */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //ADC1 ��DMA2��Stream0��Channel0��Ӧ���ɲμ��ֲ�
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
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //Ĭ���ж����ȼ�����0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
	/* 
	************************************************************************************************************************
	PCLK2 = HCLK / 2 
	����ѡ�����2��Ƶ 
	ADCCLK = PCLK2 / 8 = HCLK / 16 = 168 / 16 = 10.5M 
	ADC����Ƶ�ʣ� Sampling Time + Conversion Time = 480 + 12 cycles = 492cyc 
	              Conversion Time = 10.5MHz / 492cyc = 21ksps.
	************************************************************************************************************************
	*/
	/* ADC ������������ *************************************************/ 
	// 480+12����ת�� ����Ƶһ��ת��1/42M*492=11.7us  11.7us��Ӧ��������ֵ�� 1968  ���ȡ��Ƶ��168000000/2000=84000
    ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_RegSimult;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_2;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //���β���֮�����ʱʱ�䣬�ܲ���ʱ��12+5+480
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC3;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    
    /* ADC1����ͨ��0���� */ 
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles); //ADC_SampleTime_480Cycles��ʾ��������ʱ��
   
    /* ADC2����ͨ��0���� */ 
    ADC_Init(ADC2, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1, ADC_SampleTime_480Cycles);// ��Ҫ��2��ADC��ת����ͬ��ͨ�����ֲᣩ��channel_10��Ӧ˫ADCģʽ

    /* ʹ��DMA���� (��ADCģʽ) */
    ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
    
    /* ʹ�� ADC1 */
    ADC_Cmd(ADC1, ENABLE);
    /* ʹ�� ADC2 */
    ADC_Cmd(ADC2, ENABLE);
    
    /* ����ת�����ⲿ��ʱ��TIM1���� */
//    ADC_SoftwareStartConv(ADC2);
}

/**********************************************************************************************************
*	�� �� ��: bsp_ADCTrigEnable��bsp_ADCTrigDisable
*	����˵��: ADC��ʱ���ⴥ��ʹ�ܺ͹ر�
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void bsp_ADCTrigEnable(void)
{
	TIM_CtrlPWMOutputs(TIM1, ENABLE);  	//ʹ��TIM1ͨ��OC3��PWM ���
}

void bsp_ADCTrigDisable(void)
{
	TIM_CtrlPWMOutputs(TIM1, DISABLE);  	//�ر�TIM1ͨ��OC3��PWM ���
}
