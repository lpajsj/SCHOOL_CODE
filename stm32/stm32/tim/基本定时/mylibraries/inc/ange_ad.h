#ifndef __ange_ad_h
#define __ange_ad_h
#include "stm32f10x.h"
#define ange_ADC_IT 1
#define ange_ADC_DMA 0
#if ange_ADC_IT
//GPIO
#define ange_ADC_GPIO_APBxClock  RCC_APB2PeriphClockCmd
#define ange_ADC_GPIO_CLK        RCC_APB2Periph_GPIOC
#define ange_ADC_GPIO_Pin       GPIO_Pin_1
#define ange_ADC_GPIO_Pin2       GPIO_Pin_2
#define ange_ADC_GPIO_Pin3       GPIO_Pin_3
#define ange_ADC_GPIO_Pin4       GPIO_Pin_4
#define ange_ADC_GPIO_Pin1       GPIO_Pin_0

#define ange_ADC_GPIO_PORT      GPIOC
//ADC
#define ange_ADCx          ADC1
#define ange_ADC_APBxClock RCC_APB2PeriphClockCmd
#define ange_ADC_CLK       RCC_APB2Periph_ADC1
//通道选取
#define ange_ADC_Channel   ADC_Channel_11
#define ange_ADC_Channel1   ADC_Channel_10
#define ange_ADC_Channel2   ADC_Channel_12
#define ange_ADC_Channel3   ADC_Channel_13
#define ange_ADC_Channel4  ADC_Channel_14

//ADC中断
#define ange_ADC_IRQ       ADC1_2_IRQn
#define ange_ADC_IRQHandler  ADC1_2_IRQHandler
void ange_ADC_init(void);
#endif
#if ange_ADC_DMA

#endif
#endif




