#ifndef __ange_ad_h
#define __ange_ad_h
#include "stm32f10x.h"
#define ange_ADC_Mode_Independent 0
#define ange_ADC_Mode_RegSimult 1
#define ange_ADC_Mode_InjecSimult 0
#if ange_ADC_Mode_Independent
/*独立模式ADC_Mode_Independent*/
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
////////////////////////////////
#if ange_ADC_Mode_RegSimult
/*同步规则模式ADC_Mode_RegSimult*/
//adc1配置//////////
#define ange_ADC1_GPIO_APBxClock  RCC_APB2PeriphClockCmd
#define ange_ADC1_GPIO_CLK        RCC_APB2Periph_GPIOA
#define ange_ADC1_Channel1_GPIO_Pin       GPIO_Pin_2
#define ange_ADC1_Channel2_GPIO_Pin       GPIO_Pin_1
#define ange_ADC1_Channel3_GPIO_Pin       GPIO_Pin_2
#define ange_ADC1_Channel4_GPIO_Pin       GPIO_Pin_3
#define ange_ADC1_Channel5_GPIO_Pin       GPIO_Pin_4
#define ange_ADC1_Channel1_GPIO_PORT      GPIOA
#define ange_ADC1_Channel2_GPIO_PORT      GPIOC
#define ange_ADC1_Channel3_GPIO_PORT      GPIOC
#define ange_ADC1_Channel4_GPIO_PORT      GPIOC
#define ange_ADC1_Channel5_GPIO_PORT      GPIOC
//ADC
#define ange_ADC1           ADC1
#define ange_ADC1_APBxClock RCC_APB2PeriphClockCmd
#define ange_ADC1_CLK       RCC_APB2Periph_ADC1
//通道选取
#define ange_ADC1_Channel1   ADC_Channel_2
#define ange_ADC1_Channel2   ADC_Channel_11
#define ange_ADC1_Channel3   ADC_Channel_12
#define ange_ADC1_Channel4   ADC_Channel_13
#define ange_ADC1_Channel5   ADC_Channel_14
//adc2配置///////////////////////////////////////////
#define ange_ADC2_GPIO_APBxClock  RCC_APB2PeriphClockCmd
#define ange_ADC2_GPIO_CLK        RCC_APB2Periph_GPIOA
#define ange_ADC2_Channel1_GPIO_Pin       GPIO_Pin_4
#define ange_ADC2_Channel2_GPIO_Pin       GPIO_Pin_1
#define ange_ADC2_Channel3_GPIO_Pin       GPIO_Pin_2
#define ange_ADC2_Channel4_GPIO_Pin       GPIO_Pin_3
#define ange_ADC2_Channel5_GPIO_Pin       GPIO_Pin_4
#define ange_ADC2_Channel1_GPIO_PORT      GPIOC
#define ange_ADC2_Channel2_GPIO_PORT      GPIOC
#define ange_ADC2_Channel3_GPIO_PORT      GPIOC
#define ange_ADC2_Channel4_GPIO_PORT      GPIOC
#define ange_ADC2_Channel5_GPIO_PORT      GPIOC
//ADC
#define ange_ADC2           ADC2
#define ange_ADC2_APBxClock RCC_APB2PeriphClockCmd
#define ange_ADC2_CLK       RCC_APB2Periph_ADC2
//通道选取
#define ange_ADC2_Channel1   ADC_Channel_4
#define ange_ADC2_Channel2   ADC_Channel_11
#define ange_ADC2_Channel3   ADC_Channel_12
#define ange_ADC2_Channel4   ADC_Channel_13
#define ange_ADC2_Channel5   ADC_Channel_14
//ADC中断
#define ange_ADC12_IRQ       ADC1_2_IRQn
#define ange_ADC12_IRQHandler  ADC1_2_IRQHandler
void ange_ADC12_init(void);
void ange_ADC12_DMA_Config(u32 *x);
//DMA 
#define ange_ADC12_DMA_CLK  RCC_AHBPeriph_DMA1
#define ange_ADC12_DMA_Channel  DMA1_Channel1
#define ange_ADC12_DMA_BufferSize 1024
#define ange_ADC12_DMA_wai  (u32)&(ADC1->DR)
//DMA中断
#define ange_ADC12_DMA_IRQ      DMA1_Channel1_IRQn
#define ange_ADC12_DMA_IRQHandler  DMA1_Channel1_IRQHandler
#define ange_ADC12_DMA_IT_FLAG    DMA1_IT_TC1
void ange_ADC12_DMA_NVIC_Config(void);
#endif
#if ange_ADC_Mode_InjecSimult
/*同步注入模式ADC_Mode_InjecSimult*/
//adc1配置//////////
#define ange_ADC1_GPIO_APBxClock  RCC_APB2PeriphClockCmd
#define ange_ADC1_GPIO_CLK        RCC_APB2Periph_GPIOC
#define ange_ADC1_Channel1_GPIO_Pin       GPIO_Pin_2
#define ange_ADC1_Channel2_GPIO_Pin       GPIO_Pin_1
#define ange_ADC1_Channel3_GPIO_Pin       GPIO_Pin_2
#define ange_ADC1_Channel4_GPIO_Pin       GPIO_Pin_3
#define ange_ADC1_Channel5_GPIO_Pin       GPIO_Pin_4
#define ange_ADC1_Channel1_GPIO_PORT      GPIOC
#define ange_ADC1_Channel2_GPIO_PORT      GPIOC
#define ange_ADC1_Channel3_GPIO_PORT      GPIOC
#define ange_ADC1_Channel4_GPIO_PORT      GPIOC
#define ange_ADC1_Channel5_GPIO_PORT      GPIOC
//ADC
#define ange_ADC1          ADC1
#define ange_ADC1_APBxClock RCC_APB2PeriphClockCmd
#define ange_ADC1_CLK       RCC_APB2Periph_ADC1
//通道选取
#define ange_ADC1_Channel1   ADC_Channel_12
#define ange_ADC1_Channel2   ADC_Channel_11
#define ange_ADC1_Channel3   ADC_Channel_12
#define ange_ADC1_Channel4   ADC_Channel_13
#define ange_ADC1_Channel5   ADC_Channel_14
//adc2配置//////////
#define ange_ADC2_GPIO_APBxClock  RCC_APB2PeriphClockCmd
#define ange_ADC2_GPIO_CLK        RCC_APB2Periph_GPIOC
#define ange_ADC2_Channel1_GPIO_Pin       GPIO_Pin_1
#define ange_ADC2_Channel2_GPIO_Pin       GPIO_Pin_1
#define ange_ADC2_Channel3_GPIO_Pin       GPIO_Pin_2
#define ange_ADC2_Channel4_GPIO_Pin       GPIO_Pin_3
#define ange_ADC2_Channel5_GPIO_Pin       GPIO_Pin_4
#define ange_ADC2_Channel1_GPIO_PORT      GPIOC
#define ange_ADC2_Channel2_GPIO_PORT      GPIOC
#define ange_ADC2_Channel3_GPIO_PORT      GPIOC
#define ange_ADC2_Channel4_GPIO_PORT      GPIOC
#define ange_ADC2_Channel5_GPIO_PORT      GPIOC
//ADC
#define ange_ADC2           ADC2
#define ange_ADC2_APBxClock RCC_APB2PeriphClockCmd
#define ange_ADC2_CLK       RCC_APB2Periph_ADC2
//通道选取
#define ange_ADC2_Channel1   ADC_Channel_11
#define ange_ADC2_Channel2   ADC_Channel_11
#define ange_ADC2_Channel3   ADC_Channel_12
#define ange_ADC2_Channel4   ADC_Channel_13
#define ange_ADC2_Channel5   ADC_Channel_14
//ADC中断
#define ange_ADC12_IRQ       ADC1_2_IRQn
#define ange_ADC12_IRQHandler  ADC1_2_IRQHandler
void ange_ADC12_init(void);
void ange_ADC12_DMA_Config(u32 *x);
//DMA 
#define ange_ADC12_DMA_CLK  RCC_AHBPeriph_DMA1
#define ange_ADC12_DMA_Channel  DMA1_Channel1
#define ange_ADC12_DMA_BufferSize 1
#define ange_ADC12_DMA_wai  (u32)(&ADC1->JDR1)
#endif



#endif




