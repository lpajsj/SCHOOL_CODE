/*
*********************************************************************************************************
*
*	ģ������ : ADC����ģ��
*	�ļ����� : bsp_adc.c
*	��    �� : V1.0
*	˵    �� : adcͷ�ļ�
*	�޸ļ�¼ :
*		�汾��    ����        ����     ˵��
*		V1.0    2014-01-08   armfly   ��ʽ����
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f4xx.h"

void bsp_InitADC(void);
void bsp_ADCTrigEnable(void);
void bsp_ADCTrigDisable(void);
float GetTemp(uint16_t advalue);

#define VBATDIV                  2
#define DMA_BUFFER_SIZE          1024 //����ADC�Ĳ���������Ҳ��DMA�����С
#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
