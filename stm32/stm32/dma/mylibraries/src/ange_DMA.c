#include "ange_dma.h"
#if DMA_CC
void ange_DMA_CC_Config(const u32* y,u32 *m)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=(u32)y;
	dmainit.DMA_MemoryBaseAddr=(u32)m;
	dmainit.DMA_BufferSize=ange_DMA_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;
	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Priority=DMA_Priority_High;
	dmainit.DMA_M2M=DMA_M2M_Enable;
	DMA_Init(ange_DMA_Channel,&dmainit);
	DMA_Cmd(ange_DMA_Channel,ENABLE);
}
#endif
#if DMA_CW
void ange_DMA_CW_USARTConfig(u8* y,u32 m)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralDST;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=(u32)m;
	dmainit.DMA_MemoryBaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DMA_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	dmainit.DMA_Mode=DMA_Mode_Normal;
//	dmainit.DMA_Mode=DMA_Mode_Circular;
	dmainit.DMA_Priority=DMA_Priority_Medium;
	dmainit.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(ange_DMA_Channel,&dmainit);
	DMA_Cmd(ange_DMA_Channel,ENABLE);
}
#endif
#if DMA_WC
void ange_DMA_WC_USARTConfig(u32 y,u8 *m)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=(u32)y;
	dmainit.DMA_MemoryBaseAddr=(u32)m;
	dmainit.DMA_BufferSize=ange_DMA_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	dmainit.DMA_Mode=DMA_Mode_Normal;
//	dmainit.DMA_Mode=DMA_Mode_Circular;
	dmainit.DMA_Priority=DMA_Priority_Medium;
	dmainit.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(ange_DMA_Channel,&dmainit);
	DMA_Cmd(ange_DMA_Channel,ENABLE);
}
#endif
