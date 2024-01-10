#ifndef _ange_da_h
#define _ange_da_h
#include "stm32f10x.h"
//DA引脚初始化
#define ange_DA_GPIO_APBxClock RCC_APB2PeriphClockCmd
#define ange_DA_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ange_DA_GPIO_PORT      GPIOA
#define ange_DA1_GPIO_Pin      GPIO_Pin_4
#define ange_DA2_GPIO_Pin      GPIO_Pin_4
//da时钟
#define ange_DA_APBxClock     RCC_APB1PeriphClockCmd
#define ange_DA_CLK           RCC_APB1Periph_DAC
#define ange_DA_Channel1      DAC_Channel_1
//DA的dma定义
#define ange_DA_DMA_APBxClock     RCC_AHBPeriphClockCmd
#define ange_DA_DMA_CLK           RCC_AHBPeriph_DMA2
#define ange_DA_DMA_mudi    (u32)&DAC->DHR12R1
#define ange_DA_DMA_Channel  DMA2_Channel3
//#define ange_DA_DMA_Channel  DMA2_Channel4
#define ange_DA_DMA_BufferSize 128
#define ange_DA_DMA_Clock      RCC_AHBPeriph_DMA2
void ange_DA_DMA_Config(u16* y);
///////da 对应tim触发
#define ange_DA_TIMx TIM4
#define ange_DA_TIM_APBxClock  RCC_APB1PeriphClockCmd
#define ange_DA_TIM_CLK        RCC_APB1Periph_TIM4
#define ange_DA_TIM_IRQn       TIM4_IRQn
#define ange_DA_TIM_IRQHandler  TIM4_IRQHandler
#define ange_DA_TIM_Prescaler   0
extern u16 ange_DA_TIM_Period;
void ange_DA_init(void);
void ange_DA_DMA_Config(u16* y);
void ange_DA_TIM_Config(void);
#endif




