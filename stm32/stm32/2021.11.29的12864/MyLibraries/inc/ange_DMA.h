#ifndef __ange_DMA_H_
#define __ange_DMA_H_
#include "stm32f10x.h"
#define ange_DMA_CC 1
#define ange_DMA_CW 1
#define ange_DMA_WC 1
#if ange_DMA_CC
#define ange_DMA_CC_Channel    DMA1_Channel6
#define ange_DMA_CC_Clock      RCC_AHBPeriph_DMA1

#define ange_DMA_CC_FLAG_TC    DMA1_FLAG_TC6

#define ange_DMA_CC_BufferSize 32
void ange_DMA_CC_Config( u32 *y,u32 *m);
#endif


#if ange_DMA_CW
//内存到串口
#define ange_DMA_CW_mudi (u32)&USART1->DR
#define ange_DMA_CW_Channel  DMA1_Channel4
#define ange_DMA_CW_BufferSize 32
#define ange_DMA_CW_Clock      RCC_AHBPeriph_DMA1
void ange_DMA_CW_USARTConfig(u8* y,u32 m);
#endif


#if ange_DMA_WC
//#define ange_DMA_WC_yuan   (u32)&(ADC1->DR)
//#define ange_DMA_WC_Channel  DMA1_Channel1
#define ange_DMA_WC_yuan (u32)&USART1->DR  //串口
#define ange_DMA_WC_Channel  DMA1_Channel5
#define ange_DMA_WC_BufferSize 32
#define ange_DMA_WC_Clock      RCC_AHBPeriph_DMA1
void ange_DMA_WC_USARTConfig(u32 y,u8* m);
void ange_DMA_WC_ADCConfig(u32 y,u16 *m);
#endif


#if 0
#endif
#endif


