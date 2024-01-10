#ifndef __ange_DMA_H_
#define __ange_DMA_H_
#include "stm32f10x.h"
#define DMA_CC 0
#define DMA_CW 1
#define DMA_WC 0
#if DMA_CC
#define ange_DMA_Channel    DMA1_Channel6
#define ange_DMA_Clock      RCC_AHBPeriph_DMA1

#define ange_DMA_FLAG_TC    DMA1_FLAG_TC6

#define ange_DMA_BufferSize 32
void ange_DMA_CC_Config(const u32 *y,u32 *m);
#endif


#if DMA_CW
//ÄÚ´æµ½´®¿Ú
#define ange_DMA_mudi (u32)&USART1->DR
#define ange_DMA_Channel  DMA1_Channel4
#define ange_DMA_BufferSize 32
#define ange_DMA_Clock      RCC_AHBPeriph_DMA1
void ange_DMA_CW_USARTConfig(u8* y,u32 m);
#endif


#if DMA_WC
#define ange_DMA_yuan (u32)&USART1->DR
#define ange_DMA_Channel  DMA1_Channel5
#define ange_DMA_BufferSize 32
#define ange_DMA_Clock      RCC_AHBPeriph_DMA1
void ange_DMA_WC_USARTConfig(u32 y,u8* m);
#endif


#if 0
#endif
#endif


