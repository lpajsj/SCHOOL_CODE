/*
*********************************************************************************************************
*
*	ģ������ : RTC
*	�ļ����� : bsp_rtc.c
*	��    �� : V1.0
*	˵    �� : RTC�ײ�����
*	�޸ļ�¼ :
*		�汾��   ����        ����     ˵��
*		V1.0    2013-12-11  armfly   ��ʽ����
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"


/* ���� */
RTC_InitTypeDef  RTC_InitStructure;
RTC_TimeTypeDef  RTC_TimeStruct;

/* �������ļ��ڵ��õĺ������� */
static void RTC_Config(void);
static void RTC_AlarmConfig(void);

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitRTC
*	����˵��: ��ʼ��RTC
*	��    �Σ���
*	�� �� ֵ: ��		        
*********************************************************************************************************
*/
void bsp_InitRTC(void)
{
	RTC_Config();
	RTC_AlarmConfig();
}

/*
*********************************************************************************************************
*	�� �� ��: RTC_Config
*	����˵��: RTC����
*	��    �Σ���
*	�� �� ֵ: ��		        
*********************************************************************************************************
*/
static void RTC_Config(void)
{
	/* ʹ��PWRʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* �������RTC */
	PWR_BackupAccessCmd(ENABLE);

	/* ��λRTC�� */
	RCC_BackupResetCmd(ENABLE);
	RCC_BackupResetCmd(DISABLE);

	/* ʹ�� LSE OSC */
	RCC_LSEConfig(RCC_LSE_ON);

	/* �ȴ����� */  
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}

	/* ѡ��ʱ��Դ */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* ����RTC���Ĵ����ͷ�Ƶ */
	/* ck_spre(1Hz) = RTCCLK(LSI) /(AsynchPrediv + 1)*(SynchPrediv + 1)*/
	RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
	RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
	RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
	RTC_Init(&RTC_InitStructure);

	/* ����ʱ�� 00h 00mn 00s AM */
	RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
	RTC_TimeStruct.RTC_Hours   = 0;
	RTC_TimeStruct.RTC_Minutes = 0;
	RTC_TimeStruct.RTC_Seconds = 0;  
	RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);
}

/*
*********************************************************************************************************
*	�� �� ��: RTC_AlarmConfig
*	����˵��: ��������
*	��    �Σ���
*	�� �� ֵ: ��		        
*********************************************************************************************************
*/
static void RTC_AlarmConfig(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	RTC_AlarmTypeDef RTC_AlarmStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* EXTI ���� */
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* ʹ�� RTC Alarm �ж� */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* ���� alarm A ���� */
	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_All;
	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_Weekday_Monday;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = 0x0;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes =0x0;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds =0x0;
	RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);

	/* ���� alarm A ���� �� ʹ���������� : ÿ��8���ж� */
	RTC_AlarmSubSecondConfig(RTC_Alarm_A, 0xFF, RTC_AlarmSubSecondMask_SS14_5);

	/* ʹ�� alarm A �ж� */
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
}

