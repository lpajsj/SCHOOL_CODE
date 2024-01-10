#include "ange_pwr.h"
/*PVD�ж�����*/
/*�ⲿ�ж�16����PVD*/
void PVD_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  /*ʹ�� PWR ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* ʹ�� PVD �ж� */
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    
  /* ���� EXTI16��(PVD ���) �����������½����ж�*/
  EXTI_ClearITPendingBit(EXTI_Line16);
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  /* ����PVD����PWR_PVDLevel_2V6 (PVD����ѹ����ֵΪ2.6V��VDD��ѹ����2.6Vʱ����PVD�ж�) */
	/*���弶������Լ���ʵ��Ӧ��Ҫ������*/
  PWR_PVDLevelConfig(PWR_PVDLevel_2V6);
  /* ʹ��PVD��� */
  PWR_PVDCmd(ENABLE);
}
void PVD_IRQHandler(void)
{
		/*����Ƿ������PVD�����ź�*/
		if(PWR_GetFlagStatus (PWR_FLAG_PVDO)==SET)			
		{
			/* ����ƣ�ʵ��Ӧ����Ӧ�������״̬���� */
		}
    /* ����ж��ź�*/
    EXTI_ClearITPendingBit(EXTI_Line16);
}
/*˯��ģʽ����ֹͣ����*/
//ʹ��WFI��WFEָ��,��SLEEPDEEP=0ʱʹ��,�¼����ж�
//#define __WFI                             __wfi
//#define __WFE                             __wfe
/*ֹͣģʽ����ֹͣ����*/
//������ѡ���жϻ��¼����ѣ���ѹ���͹��ĸ�ʡ�絫����ʱ��䳤
//void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
/*����ģʽ*/
//WKUP���ŵ������ء� RTC�����¼��������ء� NRST�������ⲿ��λ�� IWDG��λ
//ʹ�ܵ�Դ������Ԫ��ʱ��,����Ҫʹ��ʱ�Ӳ��ܽ������ģʽ 
 //	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR , ENABLE);
//���WU״̬λ
//PWR_ClearFlag (PWR_FLAG_WU);
//ʹ��WKUP���ŵĻ��ѹ��� ��ʹ��PA0
//PWR_WakeUpPinCmd (ENABLE);
//�������ģʽ 
//PWR_EnterSTANDBYMode();

