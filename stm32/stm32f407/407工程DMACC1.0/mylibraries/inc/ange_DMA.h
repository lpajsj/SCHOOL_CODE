#ifndef __ange_DMA_H_
#define __ange_DMA_H_
#include "stm32f4xx.h"
#define ange_DMA_CC 1
#define ange_DMA_CW 0
#define ange_DMA_WC 0
#if ange_DMA_CC
#define ange_DMA_CC_STREAM     DMA2_Stream0  //选择数据流
#define ange_DMA_CC_Channel    DMA_Channel_6  //通道
#define ange_DMA_CC_Clock      RCC_AHB1Periph_DMA2  //DMA时钟

#define ange_DMA_CC_TCIF    DMA_FLAG_TCIF0 //数据传输流

#define ange_DMA_CC_BufferSize 32
void ange_DMA_CC_Config( u32* y,u32 *m,u32 n);//存储器到到存储器
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
#define ange_DMA_WC_yuan   (u32)&(ADC1->DR)
//#define ange_DMA_WC_yuan (u32)&USART1->DR  //串口
//#define ange_DMA_WC_Channel  DMA1_Channel5
#define ange_DMA_WC_Channel  DMA1_Channel1
#define ange_DMA_WC_BufferSize 5
#define ange_DMA_WC_Clock      RCC_AHBPeriph_DMA1
void ange_DMA_WC_USARTConfig(u32 y,u8* m);
void ange_DMA_WC_ADCConfig(u32 y,u16 *m);
#endif


#if 0
#endif
#endif


