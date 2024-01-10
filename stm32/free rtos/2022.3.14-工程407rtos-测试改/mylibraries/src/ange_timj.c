#include "ange_timj.h"
#include "main.h"
#include "ange_USART.h"
uint32_t time1=0;
static void ange_TIMj_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
//	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);
	nvicinit.NVIC_IRQChannel=ange_TIMj_IRQ;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	nvicinit.NVIC_IRQChannelPreemptionPriority=6;
	nvicinit.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvicinit);
}
static void ange_TIMj_Config()
{
	TIM_TimeBaseInitTypeDef timinit;    
	ange_TIMj_APBxClock(ange_TIMj_CLK,ENABLE);     //timʱ����apb1
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;   //ckint,�������������Լ������˲�������ʱ��Ƶ�ʷ�Ƶ�� ������ʱ����
	timinit.TIM_Prescaler=8400-1;  //ck_psc��Ƶ
	timinit.TIM_CounterMode=TIM_CounterMode_Up;  //��ʱ��������ʽ��������ʱ��ֻ������ģʽ
	timinit.TIM_Period=10000-1;     //��������װֵ
	timinit.TIM_RepetitionCounter=0;  //�ظ���������ֻ���ڸ߼���ʱ��
	TIM_TimeBaseInit(ange_TIMjx,&timinit);//��ʱ��������ʼ��
//	TIM_ClearFlag(ange_TIMjx,TIM_FLAG_Update); //��������־
	TIM_ITConfig(ange_TIMjx,TIM_IT_Update,ENABLE); //ʹ������ж�
	TIM_Cmd(ange_TIMjx,ENABLE);  //ʹ��TIM

}

void ange_TIMj_init()
{
	ange_TIMj_NVIC_Config();
	ange_TIMj_Config();
}
void ange_TIMj_IRQHandler()
{
	if(TIM_GetITStatus(ange_TIMjx,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(ange_TIMjx,TIM_IT_Update);
		printf("tim�ж�123455\n");
		if(time1>0)time1--;
	}
	
}


//tim5��ʱ��ʼ��
void Initial_System_Timer5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFFFFFF; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;       //��ʱ����Ƶ 1us
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //�����ж�
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��3
}

//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x04; //��ռ���ȼ�4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//ͨ�ö�ʱ��5�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��5!
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	//ʹ��TIM5ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 		//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  		//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);	//��ʼ��TIM5
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); 			//����ʱ��5�����ж�
	TIM_Cmd(TIM5,ENABLE); 								//ʹ�ܶ�ʱ��5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; 		//��ʱ��5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x05; 	//��ռ���ȼ�5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; 		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		printf("TIM3���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}


//��ʱ��5�жϷ�����
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		printf("TIM5���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}

