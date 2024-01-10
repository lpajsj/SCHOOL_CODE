#include "pwm.h"
#include "ange_usart.h"

//�ǲ���************************************************************/
void PWMqh_TIMt_IC_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(PWMqh_TIMt_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=PWMqh_TIMt_CH1_Pin;
	GPIO_Init(PWMqh_TIMt_CH1_PORT,&gpioinit);
	//ͨ��2gpio��ʼ��
	RCC_APB2PeriphClockCmd(PWMqh_TIMt_CH2_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=PWMqh_TIMt_CH2_Pin;
	GPIO_Init(PWMqh_TIMt_CH2_PORT,&gpioinit);
}
void PWMqh_TIMt_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=PWMqh_TIMt_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=0;
	nvicinit.NVIC_IRQChannelSubPriority=2;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}

void PWMqh_TIMt_IC_Config()
{
	PWMqh_TIMt_APBxClock(PWMqh_TIMt_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Prescaler=PWMqh_TIMt_Prescaler;
	timinit.TIM_Period=PWMqh_TIMt_Period;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(PWMqh_TIMtx,&timinit);
	///����ṹ��
	TIM_ICInitTypeDef timinit2;
	//��һ��ͨ������****************
	timinit2.TIM_Channel=PWMqh_TIMt_Channelx1;
	///�˲���ϵ����0-f֮��
	timinit2.TIM_ICFilter=0;
	//Ԥ��Ƶ
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//����
	timinit2.TIM_ICPolarity=PWMqh_TIMt_Channel_Polarity1;
	//ͨ��ѡ��
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(PWMqh_TIMtx,&timinit2);
	//�ڶ���ͨ������**********
	timinit2.TIM_Channel=PWMqh_TIMt_Channelx2;
	///�˲���ϵ����0-f֮��
	timinit2.TIM_ICFilter=0;
	//Ԥ��Ƶ
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//����
	timinit2.TIM_ICPolarity=PWMqh_TIMt_Channel_Polarity1;
	//ͨ��ѡ��
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(PWMqh_TIMtx,&timinit2);
	//***************
	TIM_ClearFlag(PWMqh_TIMtx,TIM_IT_Update|PWMqh_TIMt_IT_CCx1|PWMqh_TIMt_IT_CCx2);
	TIM_ITConfig(PWMqh_TIMtx,TIM_IT_Update|PWMqh_TIMt_IT_CCx1|PWMqh_TIMt_IT_CCx2,ENABLE);
	TIM_Cmd(PWMqh_TIMtx,ENABLE);
}
/**************************************************************************************
��ʱ��4���жϺ�����
value1�����ڵĲ��������ֵ
value3�����ڵ��������
value2���ڶ�·ͨ���������ؼ���ֵ
value4���ڶ�·ͨ�������ڵ��������
		float cycle=0,xiangwei=0;
		if(PWMqh_TIMt_IC_Value.Capture_finish==1)
		{
			
			cycle=((float)value3*65536+(float)value1)/72000000;//����
			xiangwei=((((float)value2)+((float)value4)*65536)/72000000-cycle)/cycle*360;//�ڶ�·��������-���ھ�Ϊ��λʱ���
			if((xiangwei<0)||(xiangwei>=360))//��λ�������
				xiangwei=0;
			printf("value1:%d  \n",value1);
			printf("value2:%d  \n",value2);
			printf("value3:%d  \n",value3);
			printf("value4:%d  \n",value4);	
			printf("cycle:%f  \n",cycle);
			printf("xiangwei:%f  \n",xiangwei);
			PWMqh_TIMt_IC_Value.Capture_finish=0;
		}


***************************************************************************************/
PWMqh_TIMt_ICValue_TypeDef PWMqh_TIMt_IC_Value;  //���岶��ֵ�ṹ��
uint32_t value1,value2,value3,value4;

void PWMqh_TIMt_IRQHandler() //12K���¿��Լ�ⳬǰ�ͺ󣬱Ƚ�Capture_value1��Capture_value2�Ĵ�С
{
	if(TIM_GetFlagStatus(PWMqh_TIMtx,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_IT_Update);
		PWMqh_TIMt_IC_Value.Capture_Period1++;
	}
	if(TIM_GetFlagStatus(PWMqh_TIMtx,TIM_FLAG_CC1)==SET)
	{
		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_FLAG_CC1);
		
		if((PWMqh_TIMt_IC_Value.Capture_ci==0)&&(PWMqh_TIMt_IC_Value.Capture_finish==0))
		{
			TIM_SetCounter(PWMqh_TIMtx,0);
			PWMqh_TIMt_IC_Value.Capture_Period1=0;
			PWMqh_TIMt_IC_Value.Capture_value1=0;
			PWMqh_TIMt_IC_Value.Capture_value2=0;
			PWMqh_TIMt_IC_Value.Capture_ci=1;			
			
		}
		else if((PWMqh_TIMt_IC_Value.Capture_ci==1)&&(PWMqh_TIMt_IC_Value.Capture_finish==0))
		{
			PWMqh_TIMt_IC_Value.Capture_value1=TIM_GetCapture1(PWMqh_TIMtx);
			PWMqh_TIMt_IC_Value.Capture_ci=2;
			value3=PWMqh_TIMt_IC_Value.Capture_Period1;	

		}
	}

	if(TIM_GetFlagStatus(PWMqh_TIMtx,TIM_FLAG_CC2)==SET)
	{
		TIM_ClearITPendingBit(PWMqh_TIMtx,TIM_FLAG_CC2);
		if((PWMqh_TIMt_IC_Value.Capture_ci==2)&&(PWMqh_TIMt_IC_Value.Capture_finish==0))
		{			
		

			PWMqh_TIMt_IC_Value.Capture_value2=TIM_GetCapture2(PWMqh_TIMtx);
			value4=PWMqh_TIMt_IC_Value.Capture_Period1;
			
			PWMqh_TIMt_IC_Value.Capture_finish=1;
			PWMqh_TIMt_IC_Value.Capture_ci=0;
			
			value1=PWMqh_TIMt_IC_Value.Capture_value1;
			value2=PWMqh_TIMt_IC_Value.Capture_value2;	
		}
	}
}
void PWMqh_TIMt_IC_init()
{
	PWMqh_TIMt_IC_GPIO_Config();
	PWMqh_TIMt_NVIC_Config();
	PWMqh_TIMt_IC_Config();
}
//*********************************************/

