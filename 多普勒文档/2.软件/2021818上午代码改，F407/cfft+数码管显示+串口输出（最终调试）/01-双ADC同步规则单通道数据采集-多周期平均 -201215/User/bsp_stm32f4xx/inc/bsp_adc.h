/*
*********************************************************************************************************
*
*	模块名称 : ADC驱动模块
*	文件名称 : bsp_adc.c
*	版    本 : V1.0
*	说    明 : adc头文件
*	修改记录 :
*		版本号    日期        作者     说明
*		V1.0    2014-01-08   armfly   正式发布
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
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
#define DMA_BUFFER_SIZE          1024 //定义ADC的采样点数，也即DMA缓存大小
#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
