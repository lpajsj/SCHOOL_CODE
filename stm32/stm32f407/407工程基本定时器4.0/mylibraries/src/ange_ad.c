#include "ange_ad.h"
u16 adc1zhi11;
#if ange_ADC_Mode_Independent
/*独立模式ADC_Mode_Independent*/
#if ange_ADC_IT
void ange_ADC_GPIO_Config()  //adc通道11 pc1的端口初始化
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC_GPIO_AHBxClock(ange_ADC_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC_GPIO_Pin|ange_ADC_GPIO_Pin1|ange_ADC_GPIO_Pin2|ange_ADC_GPIO_Pin3|ange_ADC_GPIO_Pin4;
//	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
//	gpioinit.GPIO_OType=GPIO_OType_OD;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(ange_ADC_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC_Config()  //adc 相关配置
{
	ADC_InitTypeDef adcinit;
	ADC_CommonInitTypeDef adccominit;
	ange_ADC_APBxClock(ange_ADC_CLK,ENABLE);  ///开启adc时钟
	adccominit.ADC_Mode=ADC_Mode_Independent;
	adccominit.ADC_Prescaler=ADC_Prescaler_Div2;  //最大36M
	adccominit.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_16Cycles;  //采样间隔时间
	adccominit.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;  //多重adc的DMA传输模式
	ADC_CommonInit(&adccominit);
	adcinit.ADC_ScanConvMode=ENABLE;        //多通道
	adcinit.ADC_ContinuousConvMode=ENABLE;     //连续转换还是单次转换
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T2_TRGO;  //adc外部触发方式
	adcinit.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;   //外部触发电平
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //数据对其方式
	adcinit.ADC_NbrOfConversion=5;              //转换通道数目
	adcinit.ADC_Resolution=ADC_Resolution_12b;  //数据分辨率
	ADC_Init(ange_ADCx,&adcinit);               //adc初始化


	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel,1,ADC_SampleTime_3Cycles);//规则通道使能
	///////开多通道
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel1,2,ADC_SampleTime_3Cycles);//规则通道使能
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel2,3,ADC_SampleTime_3Cycles);//规则通道使能
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel3,4,ADC_SampleTime_3Cycles);//规则通道使能
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel4,5,ADC_SampleTime_3Cycles);//规则通道使能
	//开中断
//	ADC_ITConfig(ange_ADCx,ADC_IT_EOC,ENABLE);  //adc中断开
	//DMA使能
  ADC_DMARequestAfterLastTransferCmd(ange_ADCx,ENABLE);  //独立模式dma使能
	//不要忘了应该放到软件触发之前，全部配置完后再使能
  ADC_DMACmd(ange_ADCx,ENABLE);     //一旦使能dma配置将无法修改，且此使能不要放在软件触发之后，多通道放在软件触发之后会造成dma通道数据错位
 
	ADC_Cmd(ange_ADCx,ENABLE);  //开adc
	ADC_SoftwareStartConv(ange_ADCx);  //adc软件使能,软件启动转换 
}
void ange_ADC_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //设置中断优先级分组
	nvicinit.NVIC_IRQChannel=ange_ADC_IRQ;       //中断源选择
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //设置抢占优先级
	nvicinit.NVIC_IRQChannelSubPriority=1;       //设置子优先级
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //中断使能
	NVIC_Init(&nvicinit);           //nvic初始化函数
}
/*ADC_DMACmd(ange_ADCx,ENABLE);     //一旦使能dma配置将无法修改，且此使能不要放在软件触发之后，多通道放在软件触发之后会造成dma通道数据错位*/
void ange_ADC_init()  //要先开DMA再初始化
{ 
	ange_ADC_GPIO_Config();
//	ange_ADC_NVIC_Config();
	ange_ADC_Config();
}
void ange_ADC_IRQHandler()
{
	if(ADC_GetITStatus(ange_ADCx,ADC_IT_EOC))  ///adc转换结束中断
	{
		adc1zhi11=ADC_GetConversionValue(ange_ADCx);
		ADC_ClearITPendingBit(ange_ADCx,ADC_IT_EOC);
	}
}
#endif
#endif
////////////////////////////////////////////////////////////////////
#if ange_ADC_Mode_RegSimult
/*同步规则模式ADC_Mode_RegSimult*/
void ange_ADC12_GPIO_Config()  //adc通道11 pc1的端口初始化
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC1_GPIO_APBxClock(ange_ADC1_GPIO_CLK|ange_ADC2_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC1_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC1_Channel1_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=ange_ADC2_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC2_Channel1_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC12_Config()  //adc 相关配置
{
	ADC_InitTypeDef adcinit;
	ange_ADC1_APBxClock(ange_ADC1_CLK,ENABLE);  ///开启adc时钟
	adcinit.ADC_Mode=ADC_Mode_RegSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //多通道扫描模式还是单通道
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=ENABLE;     //连续转换还是单次转换
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc外部触发方式
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //数据对其方式
	adcinit.ADC_NbrOfChannel=1;                  //adc通道数目选择
	ADC_Init(ange_ADC1,&adcinit);               //adc初始化
	//adc时钟不能超过14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc分频
	ADC_RegularChannelConfig(ange_ADC1,ange_ADC1_Channel1,1,ADC_SampleTime_55Cycles5);//规则通道使能
	/////////
//	ADC_ITConfig(ange_ADC1,ADC_IT_EOC,ENABLE);  //adc中断开
	ADC_Cmd(ange_ADC1,ENABLE);  //开adc
	ADC_ResetCalibration(ange_ADC1);
	while(ADC_GetResetCalibrationStatus(ange_ADC1));
	ADC_StartCalibration(ange_ADC1);  //adc开始校准
	while(ADC_GetCalibrationStatus(ange_ADC1)); //校准完成
//	ADC_SoftwareStartConvCmd(ange_ADC1,ENABLE);  //adc软件使能,软件启动转换
//adc2配置、、、、、、、、、
	ange_ADC2_APBxClock(ange_ADC2_CLK,ENABLE);  ///开启adc时钟
	adcinit.ADC_Mode=ADC_Mode_RegSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //多通道扫描模式还是单通道
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=ENABLE;     //连续转换还是单次转换
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc外部触发方式
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //数据对其方式
	adcinit.ADC_NbrOfChannel=1;                  //adc通道数目选择
	ADC_Init(ange_ADC2,&adcinit);               //adc初始化
	//adc时钟不能超过14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc分频
	ADC_RegularChannelConfig(ange_ADC2,ange_ADC2_Channel1,1,ADC_SampleTime_55Cycles5);//规则通道使能
	/////////
//	ADC_ITConfig(ange_ADC2,ADC_IT_EOC,ENABLE);  //adc中断开
	ADC_Cmd(ange_ADC2,ENABLE);  //开adc
	ADC_ResetCalibration(ange_ADC2);
	while(ADC_GetResetCalibrationStatus(ange_ADC2));
	ADC_StartCalibration(ange_ADC2);  //adc开始校准
	while(ADC_GetCalibrationStatus(ange_ADC2)); //校准完成
	ADC_ExternalTrigConvCmd(ange_ADC2,ENABLE);
//	ADC_SoftwareStartConvCmd(ange_ADC2,ENABLE);  //adc软件使能,软件启动转换
}
void ange_ADC12_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //设置中断优先级分组
	nvicinit.NVIC_IRQChannel=ange_ADC12_IRQ;       //中断源选择
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //设置抢占优先级
	nvicinit.NVIC_IRQChannelSubPriority=1;       //设置子优先级
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //中断使能
	NVIC_Init(&nvicinit);           //nvic初始化函数
}
void ange_ADC12_DMA_Config(u32 *x)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_ADC12_DMA_CLK,ENABLE);
	DMA_DeInit(ange_ADC12_DMA_Channel);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=ange_ADC12_DMA_wai;   //外设地址
	dmainit.DMA_MemoryBaseAddr=(u32)(x);   //内存地址
	dmainit.DMA_BufferSize=ange_ADC12_DMA_BufferSize;  //dma数据传输量
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址不递增
	dmainit.DMA_MemoryInc=DMA_PeripheralInc_Disable;  //内存地址是否递增
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;   //外设数据宽度
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;  //内存数据宽度
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;  //循环还是正常
	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma优先级 包括low medium high veryhigh
	dmainit.DMA_M2M=DMA_M2M_Disable;   //存储器到存储器时选择
	DMA_Init(ange_ADC12_DMA_Channel,&dmainit);  //初始化时要选择通道
	DMA_Cmd(ange_ADC12_DMA_Channel,ENABLE);
	ADC_DMACmd(ange_ADC1,ENABLE);
}
void ange_ADC12_init()
{
	ange_ADC12_GPIO_Config();
//	ange_ADC12_NVIC_Config();
	ange_ADC12_Config();
}
void ange_ADC12_IRQHandler()
{
	if(ADC_GetITStatus(ange_ADC1,ADC_IT_EOC))  ///adc转换结束中断
	{
		adc1zhi11=ADC_GetConversionValue(ange_ADC1);
		ADC_ClearITPendingBit(ange_ADC1,ADC_IT_EOC);
	}
}
#endif
/////////////////////////////////
#if ange_ADC_Mode_InjecSimult
/*同步注入模式ADC_Mode_InjecSimult*/
void ange_ADC12_GPIO_Config()  //adc通道11 pc1的端口初始化
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC1_GPIO_APBxClock(ange_ADC1_GPIO_CLK|ange_ADC2_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC1_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC1_Channel1_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=ange_ADC2_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC2_Channel1_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=ange_ADC2_Channel4_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC2_Channel4_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC12_Config()  //adc 相关配置
{
	ADC_InitTypeDef adcinit;
	ange_ADC1_APBxClock(ange_ADC1_CLK,ENABLE);  ///开启adc时钟
	adcinit.ADC_Mode=ADC_Mode_InjecSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //多通道扫描模式还是单通道
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=DISABLE;     //连续转换还是单次转换
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc外部触发方式
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //数据对其方式
	adcinit.ADC_NbrOfChannel=1;                  //规则组adc通道数目选择
	ADC_Init(ange_ADC1,&adcinit);               //adc初始化
	//adc时钟不能超过14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc分频
	ADC_InjectedSequencerLengthConfig(ange_ADC1,3);
	ADC_InjectedChannelConfig(ange_ADC1,ange_ADC1_Channel1,1,ADC_SampleTime_55Cycles5);//规则通道使能
	ADC_InjectedChannelConfig(ange_ADC1,ange_ADC2_Channel1,2,ADC_SampleTime_55Cycles5);//规则通道使能
		ADC_InjectedChannelConfig(ange_ADC1,ange_ADC1_Channel4,3,ADC_SampleTime_55Cycles5);//规则通道使能
	ADC_Cmd(ange_ADC1,ENABLE);  //开adc
	ADC_ResetCalibration(ange_ADC1);
	while(ADC_GetResetCalibrationStatus(ange_ADC1));
	ADC_StartCalibration(ange_ADC1);  //adc开始校准
	while(ADC_GetCalibrationStatus(ange_ADC1)); //校准完成
//adc2配置、、、、、、、、、就初始化就可以了
	ange_ADC2_APBxClock(ange_ADC2_CLK,ENABLE);  ///开启adc时钟
	adcinit.ADC_Mode=ADC_Mode_InjecSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //多通道扫描模式还是单通道
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=DISABLE;     //连续转换还是单次转换
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc外部触发方式
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //数据对其方式
	adcinit.ADC_NbrOfChannel=1;                  //adc通道数目选择
	ADC_Init(ange_ADC2,&adcinit);               //adc初始化
	//adc时钟不能超过14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc分频
	ADC_Cmd(ange_ADC2,ENABLE);  //开adc
	ADC_ResetCalibration(ange_ADC2);
	while(ADC_GetResetCalibrationStatus(ange_ADC2));
	ADC_StartCalibration(ange_ADC2);  //adc开始校准
	while(ADC_GetCalibrationStatus(ange_ADC2)); //校准完成

	ADC_ExternalTrigInjectedConvConfig(ange_ADC1,ADC_ExternalTrigInjecConv_T4_TRGO);
	ADC_ExternalTrigInjectedConvCmd(ange_ADC1,ENABLE);
}
void ange_ADC12_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //设置中断优先级分组
	nvicinit.NVIC_IRQChannel=ange_ADC12_IRQ;       //中断源选择
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //设置抢占优先级
	nvicinit.NVIC_IRQChannelSubPriority=1;       //设置子优先级
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //中断使能
	NVIC_Init(&nvicinit);           //nvic初始化函数
}
//void ange_ADC12_DMA_Config(u32 *x)
//{
//	DMA_InitTypeDef dmainit;
//	RCC_AHBPeriphClockCmd(ange_ADC12_DMA_CLK,ENABLE);
//	DMA_DeInit(ange_ADC12_DMA_Channel);
//	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC 外设到存储器 DST 存到外
//	dmainit.DMA_PeripheralBaseAddr=ange_ADC12_DMA_wai;   //外设地址
//	dmainit.DMA_MemoryBaseAddr=(u32)(x);   //内存地址
//	dmainit.DMA_BufferSize=ange_ADC12_DMA_BufferSize;  //dma数据传输量
//	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址不递增
//	dmainit.DMA_MemoryInc=DMA_PeripheralInc_Disable;  //内存地址是否递增
//	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;   //外设数据宽度
//	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;  //内存数据宽度
////	dmainit.DMA_Mode=DMA_Mode_Normal;
//	dmainit.DMA_Mode=DMA_Mode_Circular;  //循环还是正常
//	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma优先级 包括low medium high veryhigh
//	dmainit.DMA_M2M=DMA_M2M_Disable;   //存储器到存储器时选择
//	DMA_Init(ange_ADC12_DMA_Channel,&dmainit);  //初始化时要选择通道
//	DMA_Cmd(ange_ADC12_DMA_Channel,ENABLE);
//	ADC_DMACmd(ange_ADC1,ENABLE);
//}
void ange_ADC12_init()
{
	ange_ADC12_GPIO_Config();
//	ange_ADC12_NVIC_Config();
	ange_ADC12_Config();
}
//void ange_ADC12_IRQHandler()
//{
//	if(ADC_GetITStatus(ange_ADC1,ADC_IT_EOC))  ///adc转换结束中断
//	{
//		adc1zhi11=ADC_GetConversionValue(ange_ADC1);
//		ADC_ClearITPendingBit(ange_ADC1,ADC_IT_EOC);
//	}
//}
#endif

