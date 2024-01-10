#include "ange_da.h"
u16 da_shuju1[64]={496,544,592,639,685,729,771,810,846,879,908,933,954,970,982,989,991,989,982,970,
	954,933,908,879,846,810,771,729,685,639,592,544,496,447,399,352,306,262,220,181,145,112,83,58,37,
21,9,2,0,2,9,21,37,58,83,112,145,181,220,262,306,352,399,447};
void ange_DA_GPIO_Config()  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	ange_DA_GPIO_APBxClock(ange_DA_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_DA1_GPIO_Pin  ;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_DA_GPIO_PORT,&gpioinit);
	return;
}
u16 ange_DA_TIM_Period=1130;   //
u16 ange_DA_TIM_Prescaler=0;  //��Ƶ���Ե���0
void ange_DA_Config()
{
	DAC_InitTypeDef dacinit;
	ange_DA_APBxClock(ange_DA_CLK,ENABLE);
	//DAC_LFSRUnmask_Bit�൱����ѡ�м�λ�����ڲ�����DA�Ĵ�������Ϊ��Сֵ��0bit��һλ����DAC_TriangleAmplitude���ǲ��ķ�����DA����Ϊ��Сֵ��ÿ�δ�����һ
	dacinit.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	dacinit.DAC_OutputBuffer=DAC_OutputBuffer_Disable;            //������壬��С����迹
	dacinit.DAC_Trigger=DAC_Trigger_T4_TRGO;                      //�ⲿ����ʹ�ܺ����޸Ĵ�����ʽ�����������������
	dacinit.DAC_WaveGeneration=DAC_WaveGeneration_None;            //�� ���� ���ǲ�//
	DAC_Init(ange_DA_Channel1,&dacinit);
	DAC_Cmd(ange_DA_Channel1,ENABLE);
}
void ange_DA_DMA_Config(u16* y)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DA_DMA_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralDST;  //SRC ���赽�洢�� DST �浽��
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
	ange_DA_GPIO_Config();  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
	ange_DA_Config();
	ange_DA_TIM_Config();
}
//��ʼ��,ʱ����	ange_DA_init();//DA��ʼ��
	              //ange_DA_DMA_Config(da_shuju1);//DMA��ʼ��	
void dapinlv(u32 i)//�������Ҳ�,�������ΪƵ��
{
	  double  x;
		uint32_t t;
		x=1125000/i;  //���HZ
		t=(u32)x-1;
		ange_DA_TIM_Period=t+5;
	 TIM_SetAutoreload(ange_DA_TIMx,ange_DA_TIM_Period);
//		ange_DA_TIM_Config();
}
