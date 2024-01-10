#include "ange_dma.h"
#if ange_DMA_CC
void ange_DMA_CC_Config( u32* y,u32 *m,u32 n)//存储器到到存储器 源地址、目标地址、数据量
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_CC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_CC_Channel;  //通道
	
	dmainit.DMA_DIR=DMA_DIR_MemoryToMemory;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=(u32)y;  //地址
	dmainit.DMA_Memory0BaseAddr=(u32)m;
	dmainit.DMA_BufferSize=n;  //数据量
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Enable; //外设地址递增使能
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //内存地址使能
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;  //数据大小
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;        
	dmainit.DMA_Mode=DMA_Mode_Normal;  //内存到内存不能用循环
	dmainit.DMA_Priority=DMA_Priority_High; //仲裁优先级
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifo模式，存储器到存储器自动打开
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo大小设置  full为4字
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //单次触发
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_CC_STREAM,&dmainit);
	DMA_Cmd(ange_DMA_CC_STREAM,ENABLE);
}
#endif
#if ange_DMA_CW
void ange_DMA_CW_USARTConfig(u8* y,u32 m)//存储器到外设
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_CW_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralDST;  
	dmainit.DMA_PeripheralBaseAddr=(u32)m;
	dmainit.DMA_MemoryBaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DMA_CW_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;
	dmainit.DMA_Priority=DMA_Priority_Medium;
	dmainit.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(ange_DMA_CW_Channel,&dmainit);
	DMA_Cmd(ange_DMA_CW_Channel,ENABLE);
}
#endif
#if ange_DMA_WC
void ange_DMA_WC_USARTConfig(u32 y,u8 *m)//外设到存储器，8位数据
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=(u32)y;   //外设地址
	dmainit.DMA_MemoryBaseAddr=(u32)m;   //内存地址
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //dma数据传输量
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址不递增
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;  //内存地址是否递增
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;   //外设数据宽度
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //内存数据宽度
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;  //循环还是正常
	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma优先级 包括low medium high veryhigh
	dmainit.DMA_M2M=DMA_M2M_Disable;   //存储器到存储器时选择
	DMA_Init(ange_DMA_WC_Channel,&dmainit);  //初始化是要选择通道
	DMA_Cmd(ange_DMA_WC_Channel,ENABLE);
}
void ange_DMA_WC_ADCConfig(u32 y,u16 *m)//外设到存储器，16位数据
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	DMA_DeInit(ange_DMA_WC_Channel);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=(u32)y;   //外设地址
	dmainit.DMA_MemoryBaseAddr=(u32)m;   //内存地址
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //dma数据传输量
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址不递增
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;  //内存地址是否递增
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;   //外设数据宽度
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;  //内存数据宽度
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;  //循环还是正常
	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma优先级 包括low medium high veryhigh
	dmainit.DMA_M2M=DMA_M2M_Disable;   //存储器到存储器时选择
	DMA_Init(ange_DMA_WC_Channel,&dmainit);  //初始化时要选择通道
	DMA_Cmd(ange_DMA_WC_Channel,ENABLE);
}
#endif
