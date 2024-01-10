#ifndef _ange_da_h
#define _ange_da_h
#include "stm32f10x.h"
#define ange_DA_OUT1 1
#define ange_DA_OUT2 0
//DA引脚初始化
#if ange_DA_OUT1
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
#define ange_DA_DMA_BufferSize 64
#define ange_DA_DMA_Clock      RCC_AHBPeriph_DMA2
#endif
#if ange_DA_OUT2
#define ange_DA_GPIO_APBxClock RCC_APB2PeriphClockCmd
#define ange_DA_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ange_DA_GPIO_PORT      GPIOA
#define ange_DA1_GPIO_Pin      GPIO_Pin_5
#define ange_DA2_GPIO_Pin      GPIO_Pin_5
//da时钟
#define ange_DA_APBxClock     RCC_APB1PeriphClockCmd
#define ange_DA_CLK           RCC_APB1Periph_DAC
#define ange_DA_Channel1      DAC_Channel_2
//DA的dma定义
#define ange_DA_DMA_APBxClock     RCC_AHBPeriphClockCmd
#define ange_DA_DMA_CLK           RCC_AHBPeriph_DMA2
#define ange_DA_DMA_mudi    (u32)&DAC->DHR12R2
//#define ange_DA_DMA_Channel  DMA2_Channel3
#define ange_DA_DMA_Channel  DMA2_Channel4
#define ange_DA_DMA_BufferSize 64
#define ange_DA_DMA_Clock      RCC_AHBPeriph_DMA2
#endif
///////da 对应tim触发
#define ange_DA_TIMx TIM4
#define ange_DA_TIM_APBxClock  RCC_APB1PeriphClockCmd
#define ange_DA_TIM_CLK        RCC_APB1Periph_TIM4
#define ange_DA_TIM_IRQn       TIM4_IRQn
#define ange_DA_TIM_IRQHandler  TIM4_IRQHandler
extern u16 ange_DA_TIM_Prescaler;
extern u16 ange_DA_TIM_Period;
extern u16 da_shuju1[64];
//extern u16 da_shuju2[64];
void ange_DA_init(void);
void ange_DA_DMA_Config(u16* y);
void ange_DA_TIM_Config(void);
void dapinlv(u32 i);//产生正弦波
void dafudu(u16 *x,u32 d,float max);
/*简单软件触发*/
#define ange_DA_EASY_OUT1 0
#define ange_DA_EASY_OUT2 1
#if ange_DA_EASY_OUT1
#define ange_DA_EASY_GPIO_APBxClock RCC_APB2PeriphClockCmd
#define ange_DA_EASY_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ange_DA_EASY_GPIO_PORT      GPIOA
#define ange_DA1_EASY_GPIO_Pin      GPIO_Pin_4
//da时钟
#define ange_DA_EASY_APBxClock     RCC_APB1PeriphClockCmd
#define ange_DA_EASY_CLK           RCC_APB1Periph_DAC
#define ange_DA_EASY_Channel1      DAC_Channel_1
#endif
#if ange_DA_EASY_OUT2
#define ange_DA_EASY_GPIO_APBxClock RCC_APB2PeriphClockCmd
#define ange_DA_EASY_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ange_DA_EASY_GPIO_PORT      GPIOA
#define ange_DA1_EASY_GPIO_Pin      GPIO_Pin_5
//da时钟
#define ange_DA_EASY_APBxClock     RCC_APB1PeriphClockCmd
#define ange_DA_EASY_CLK           RCC_APB1Periph_DAC
#define ange_DA_EASY_Channel1      DAC_Channel_2
#endif
void ange_DA_easy_init(void);
void ange_DA_easy_GPIO_Config(void);  //adc通道11 pc1的端口初始化;
void ange_DA_easy_Config(void);
void ange_DA_easy_trigger(float x);
#endif




