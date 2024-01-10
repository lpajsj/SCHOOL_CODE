#include "ange_ad.h"
u16 adc1zhi11;
#if ange_ADC_IT
void ange_ADC_GPIO_Config()  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC_GPIO_APBxClock(ange_ADC_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC_GPIO_Pin|ange_ADC_GPIO_Pin1|ange_ADC_GPIO_Pin2|ange_ADC_GPIO_Pin3|ange_ADC_GPIO_Pin4;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC_Config()  //adc �������
{
	ADC_InitTypeDef adcinit;
	ange_ADC_APBxClock(ange_ADC_CLK,ENABLE);  ///����adcʱ��
	adcinit.ADC_Mode=ADC_Mode_Independent;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //��ͨ��ɨ��ģʽ���ǵ�ͨ��
	adcinit.ADC_ScanConvMode=ENABLE;        //��ͨ��
	adcinit.ADC_ContinuousConvMode=ENABLE;     //����ת�����ǵ���ת��
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc�ⲿ������ʽ
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //���ݶ��䷽ʽ
	adcinit.ADC_NbrOfChannel=5;                  //adcͨ����Ŀѡ��
	ADC_Init(ange_ADCx,&adcinit);               //adc��ʼ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);           //adc��Ƶ
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel,1,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	///////����ͨ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel1,2,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel2,3,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel3,4,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel4,5,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	/////////
//	ADC_ITConfig(ange_ADCx,ADC_IT_EOC,ENABLE);  //adc�жϿ�
	ADC_Cmd(ange_ADCx,ENABLE);  //��adc
	ADC_StartCalibration(ange_ADCx);  //adc��ʼУ׼
	while(ADC_GetCalibrationStatus(ange_ADCx)); //У׼���
	ADC_SoftwareStartConvCmd(ange_ADCx,ENABLE);  //adc���ʹ��
	
}
void ange_ADC_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //�����ж����ȼ�����
	nvicinit.NVIC_IRQChannel=ange_ADC_IRQ;       //�ж�Դѡ��
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //������ռ���ȼ�
	nvicinit.NVIC_IRQChannelSubPriority=1;       //���������ȼ�
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //�ж�ʹ��
	NVIC_Init(&nvicinit);           //nvic��ʼ������
}
void ange_ADC_init()
{
	ange_ADC_GPIO_Config();
	ange_ADC_NVIC_Config();
	ange_ADC_Config();
}
void ange_ADC_IRQHandler()
{
	if(ADC_GetITStatus(ange_ADCx,ADC_IT_EOC))  ///adcת�������ж�
	{
		adc1zhi11=ADC_GetConversionValue(ange_ADCx);
		ADC_ClearITPendingBit(ange_ADCx,ADC_IT_EOC);
	}
}
#endif
