#include "ADDA.H"
/**************************************************************************************
AD使用到的引脚：PA6,PA7,PB0
理论转换时间：
ADC时钟：72/8=9M
转换时间：7.5+12.5=20 20*1/9=2.2us 但是未测试

DA使用到的引脚：PA4
理论输出时间： 2*1/72=27ns
测试输出128点正弦波：35KHZ  每点输出223ns
最小8.5HZ
外部变量的使用：
			ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
**************************************************************************************/
__IO uint16_t ADC_ConvertedValue[3]={0};//存器ADC转换的值
float ADC_ConvertedValueLocal[3]={0}; //存储转换后电压的值       

void ADCX_Config(void)
{
	RCC_APB2PeriphClockCmd(ADC6_GPIO_RCC,ENABLE);//开启ADC1-6,7通道引脚的时钟
	RCC_APB2PeriphClockCmd(ADC8_GPIO_RCC,ENABLE);//开启ADC1-8通道的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//开启DMA1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//开启ADC1的时钟
/*-------------------GPIO初始化-----------------------------------------------*/	
	GPIO_InitTypeDef GPIO_InitStruction;
	GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AIN;//设置为模拟输入
	GPIO_InitStruction.GPIO_Pin=ADC6_GPIO_Pin|ADC7_GPIO_Pin;
	GPIO_Init(ADC6_GPIO_PORT,&GPIO_InitStruction);
	
	GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruction.GPIO_Pin=ADC8_GPIO_Pin;
	GPIO_Init(ADC8_GPIO_PORT,&GPIO_InitStruction);	
	
/*-------------------DMA初始化-----------------------------------------------*/
	DMA_InitTypeDef ADC_DMA_InitStruction;
	ADC_DMA_InitStruction.DMA_BufferSize=3;//一次传输3个
	ADC_DMA_InitStruction.DMA_DIR=DMA_DIR_PeripheralSRC;//外设为源
	ADC_DMA_InitStruction.DMA_M2M=DMA_M2M_Disable;//关闭存储到存储
	ADC_DMA_InitStruction.DMA_MemoryBaseAddr=(uint32_t)ADC_ConvertedValue;//存储器的地址
	ADC_DMA_InitStruction.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//16位，半个字节
	ADC_DMA_InitStruction.DMA_MemoryInc=DMA_MemoryInc_Enable;//地址自增
	ADC_DMA_InitStruction.DMA_Mode=DMA_Mode_Circular;//开启循环发数
	ADC_DMA_InitStruction.DMA_PeripheralBaseAddr=(uint32_t)(&(ADC1->DR));//ADC数据地址
	ADC_DMA_InitStruction.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//16位，半个字节
	ADC_DMA_InitStruction.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址自增
	ADC_DMA_InitStruction.DMA_Priority=DMA_Priority_High;//高优先级
	DMA_Init(DMA1_Channel1,&ADC_DMA_InitStruction);
	DMA_Cmd(DMA1_Channel1,ENABLE);
/*----------------------ADC初始化------------------------------------------------*/	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_InitTypeDef ADC_InitStruction;
	ADC_InitStruction.ADC_ContinuousConvMode=ENABLE;//连续转换
	ADC_InitStruction.ADC_DataAlign=ADC_DataAlign_Right;//数据右对齐
	ADC_InitStruction.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//关闭外部触发
	ADC_InitStruction.ADC_Mode=ADC_Mode_Independent;//独立模式
	ADC_InitStruction.ADC_NbrOfChannel=3;//转换三个通道
	ADC_InitStruction.ADC_ScanConvMode=ENABLE;//开启扫描模式
	ADC_Init(ADC1,&ADC_InitStruction);

	ADC_RegularChannelConfig(ADC1,ADC6_Channel,1,ADC_SampleTime_7Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC7_Channel,2,ADC_SampleTime_7Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC8_Channel,3,ADC_SampleTime_7Cycles5);
	
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//先关闭软件触发
}
#ifdef STM32F10X_HD
uint16_t DA1_Data[128]={2047,2147,2247,2347,2446,2544,2641,2736,2830,2922,3011,3099,3184,3266,3345,
												3421,3494,3563,3629,3691,3749,3802,3852,3897,3938,3974,4005,4032,4054,4071,
												4084,4091,4093,4091,4084,4071,4054,4032,4005,3974,3938,3897,3852,3802,3749,
												3691,3629,3563,3494,3421,3345,3266,3184,3099,3011,2922,2830,2736,2641,2544,
												2446,2347,2247,2147,2047,1946,1846,1746,1647,1549,1452,1357,1263,1171,1082,
												994,909,827,748,672,599,530,464,402,344,291,241,196,155,119,88,61,39,22,9,
												2,0,2,9,22,39,61,88,119,155,196,241,291,344,402,464,530,599,672,748,827,909,
												994,1082,1171,1263,1357,1452,1549,1647,1746,1846,1946};
void DAC_Config(void)
{

	RCC_APB2PeriphClockCmd(DAC1_GPIO_RCC,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
/*-------------------GPIO初始化-----------------------------------------------*/	
	
	GPIO_InitTypeDef DAC_GPIO_InitStruction;
	DAC_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AIN;
	DAC_GPIO_InitStruction.GPIO_Pin=DAC1_GPIO_Pin;
	GPIO_Init(DAC1_GPIO_PORT,&DAC_GPIO_InitStruction);	
/*-------------------DMA初始化-----------------------------------------------*/
	
	DMA_InitTypeDef  DAC_DMA_InitStruction;
	DAC_DMA_InitStruction.DMA_BufferSize=128;
	DAC_DMA_InitStruction.DMA_DIR=DMA_DIR_PeripheralDST;
	DAC_DMA_InitStruction.DMA_M2M=DMA_M2M_Disable;
	DAC_DMA_InitStruction.DMA_MemoryBaseAddr=(uint32_t)DA1_Data;
	DAC_DMA_InitStruction.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DAC_DMA_InitStruction.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DAC_DMA_InitStruction.DMA_Mode=DMA_Mode_Circular;
	DAC_DMA_InitStruction.DMA_PeripheralBaseAddr=(uint32_t)(&(DAC->DHR12R1));
	DAC_DMA_InitStruction.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DAC_DMA_InitStruction.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DAC_DMA_InitStruction.DMA_Priority=DMA_Priority_High;
	DMA_Init(DMA2_Channel3,&DAC_DMA_InitStruction);
	DMA_Cmd(DMA2_Channel3,ENABLE);
/*----------------------DAC初始化------------------------------------------------*/	
	
	DAC_InitTypeDef DAC_InitStruction;
	DAC_InitStruction.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//DAC产生波形的幅度，这里用不到
	DAC_InitStruction.DAC_OutputBuffer=DAC_OutputBuffer_Disable;//输出缓存，用来减少输出阻抗
	DAC_InitStruction.DAC_Trigger=DAC_Trigger_T6_TRGO;//选择定时器6触发
	DAC_InitStruction.DAC_WaveGeneration=DAC_WaveGeneration_None;//关闭DAC产生波形功能
	DAC_Init(DAC_Channel_1,&DAC_InitStruction);
	DAC_Cmd(DAC_Channel_1,ENABLE);
	DAC_DMACmd(DAC_Channel_1,ENABLE);
	
/*----------------------TIM6初始化------------------------------------------------*/	
	TIM_TimeBaseInitTypeDef TIM6_TimeBaseInitStruction;
	TIM6_TimeBaseInitStruction.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM6_TimeBaseInitStruction.TIM_CounterMode=TIM_CounterMode_Up;
	TIM6_TimeBaseInitStruction.TIM_Period=0xFFFF;
	TIM6_TimeBaseInitStruction.TIM_Prescaler=0;
	TIM6_TimeBaseInitStruction.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM6,&TIM6_TimeBaseInitStruction);
	TIM_SelectOutputTrigger(TIM6,TIM_TRGOSource_Update);
	TIM_Cmd(TIM6,DISABLE);//先关闭定时器
}

#endif
