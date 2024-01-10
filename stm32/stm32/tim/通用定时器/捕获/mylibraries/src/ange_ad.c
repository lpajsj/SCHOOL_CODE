#include "ange_ad.h"
u16 adc1zhi11;
#if ange_ADC_IT
void ange_ADC_GPIO_Config()  //adc通道11 pc1的端口初始化
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC_GPIO_APBxClock(ange_ADC_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC_GPIO_Pin|ange_ADC_GPIO_Pin1|ange_ADC_GPIO_Pin2|ange_ADC_GPIO_Pin3|ange_ADC_GPIO_Pin4;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC_Config()  //adc 相关配置
{
	ADC_InitTypeDef adcinit;
	ange_ADC_APBxClock(ange_ADC_CLK,ENABLE);  ///开启adc时钟
	adcinit.ADC_Mode=ADC_Mode_Independent;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //多通道扫描模式还是单通道
	adcinit.ADC_ScanConvMode=ENABLE;        //多通道
	adcinit.ADC_ContinuousConvMode=ENABLE;     //连续转换还是单次转换
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc外部触发方式
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //数据对其方式
	adcinit.ADC_NbrOfChannel=5;                  //adc通道数目选择
	ADC_Init(ange_ADCx,&adcinit);               //adc初始化
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);           //adc分频
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel,1,ADC_SampleTime_55Cycles5);//规则通道使能
	///////开多通道
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel1,2,ADC_SampleTime_55Cycles5);//规则通道使能
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel2,3,ADC_SampleTime_55Cycles5);//规则通道使能
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel3,4,ADC_SampleTime_55Cycles5);//规则通道使能
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel4,5,ADC_SampleTime_55Cycles5);//规则通道使能
	/////////
//	ADC_ITConfig(ange_ADCx,ADC_IT_EOC,ENABLE);  //adc中断开
	ADC_Cmd(ange_ADCx,ENABLE);  //开adc
	ADC_StartCalibration(ange_ADCx);  //adc开始校准
	while(ADC_GetCalibrationStatus(ange_ADCx)); //校准完成
	ADC_SoftwareStartConvCmd(ange_ADCx,ENABLE);  //adc软件使能
	
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
void ange_ADC_init()
{
	ange_ADC_GPIO_Config();
	ange_ADC_NVIC_Config();
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
