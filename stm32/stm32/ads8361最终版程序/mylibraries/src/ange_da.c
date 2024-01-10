#include "ange_da.h"
u16 da_shuju1[64]={620,680,740,799,857,912,964,1013,1058,1099,1135,1166,1192
	,1213,1228,1237,1239,1237,1228,1213,1192,1166,1135,1099,1058,1013,964,912,
	857,799,740,680,620,559,499,440,382,327,275,226,181,140,104,73,47,26,11,2,
	0,2,11,26,47,73,104,140,181,226,275,327,382,440,499,559};
void ange_DA_GPIO_Config()  //adc通道11 pc1的端口初始化
{
	GPIO_InitTypeDef gpioinit;
	ange_DA_GPIO_APBxClock(ange_DA_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_DA1_GPIO_Pin  ;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_DA_GPIO_PORT,&gpioinit);
	return;
}
void ange_DA_Config()
{
	DAC_InitTypeDef dacinit;
	ange_DA_APBxClock(ange_DA_CLK,ENABLE);
	dacinit.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0  ;
	dacinit.DAC_OutputBuffer=DAC_OutputBuffer_Disable;
	dacinit.DAC_Trigger=DAC_Trigger_T4_TRGO;
	dacinit.DAC_WaveGeneration=DAC_WaveGeneration_None;
	DAC_Init(ange_DA_Channel1,&dacinit);
	DAC_Cmd(ange_DA_Channel1,ENABLE);
}
void ange_DA_DMA_Config(u16* y)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DA_DMA_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralDST;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=ange_DA_DMA_mudi;
	dmainit.DMA_MemoryBaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DA_DMA_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;
	dmainit.DMA_Priority=DMA_Priority_Medium;
	dmainit.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(ange_DA_DMA_Channel,&dmainit);
	DMA_Cmd(ange_DA_DMA_Channel,ENABLE);
	DAC_DMACmd(ange_DA_Channel1,ENABLE);
}
u16 ange_DA_TIM_Period=1;
u16 ange_DA_TIM_Prescaler=0;
void ange_DA_TIM_Config()
{
	ange_DA_TIM_APBxClock(ange_DA_TIM_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=0;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Period=ange_DA_TIM_Period;
	timinit.TIM_Prescaler=ange_DA_TIM_Prescaler;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_DA_TIMx,&timinit);
	TIM_SelectOutputTrigger(ange_DA_TIMx,TIM_TRGOSource_Update);
	TIM_Cmd(ange_DA_TIMx,ENABLE);
}
void ange_DA_init()
{
	ange_DA_GPIO_Config();  //adc通道11 pc1的端口初始化
	ange_DA_Config();
	ange_DA_TIM_Config();
}
