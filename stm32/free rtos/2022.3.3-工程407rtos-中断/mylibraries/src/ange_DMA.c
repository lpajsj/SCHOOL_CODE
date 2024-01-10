#include "ange_dma.h"
//DMA1 控制器 AHB 外设端口与 DMA2 控制器的情况不同，不连接到总线矩阵，因此，仅 DMA2 数据流能够执行存储器到
//存储器的传输。
#if ange_DMA_CC
void ange_DMA_CC_Config( u32* y,u32 *m,u32 n)//存储器到到存储器 源地址、目标地址、数据量
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_CC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_CC_Channel;  //通道
	
	dmainit.DMA_DIR=DMA_DIR_MemoryToMemory;  //存储器到存储器
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
	DMA_Init(ange_DMA_CC_Stream,&dmainit);
	DMA_Cmd(ange_DMA_CC_Stream,ENABLE);
}
#endif
#if ange_DMA_CW
void ange_DMA_CW_USARTConfig(u8* y)//存储器到外设
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_CW_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_CW_Channel;  //通道
	
	dmainit.DMA_DIR=DMA_DIR_MemoryToPeripheral;  //存储器到外设
	dmainit.DMA_PeripheralBaseAddr=(u32)ange_DMA_CW_mudi;  //地址
	dmainit.DMA_Memory0BaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DMA_CW_BufferSize;  //数据量
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址递增使能
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //内存地址使能
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //数据大小
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;        
	dmainit.DMA_Mode=DMA_Mode_Normal;  //内存到内存不能用循环
	dmainit.DMA_Priority=DMA_Priority_Medium; //仲裁优先级
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifo模式，存储器到存储器自动打开
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo大小设置  full为4字
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //单次触发
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_CW_Stream,&dmainit);
	DMA_Cmd(ange_DMA_CW_Stream,ENABLE);
}
#endif
#if ange_DMA_WC
void ange_DMA_WC_USARTConfig(u8 *m)//外设到存储器，8位数据
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_WC_Channel;  //通道
	
	dmainit.DMA_DIR=DMA_DIR_PeripheralToMemory;  //外设到存储器
	dmainit.DMA_PeripheralBaseAddr=(u32)ange_DMA_WC_yuan;  //地址
	dmainit.DMA_Memory0BaseAddr=(u32)m;
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //数据量
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址递增不使能
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //内存地址使能
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //数据大小
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;        
	dmainit.DMA_Mode=DMA_Mode_Circular;  //内存到内存不能用循环
	dmainit.DMA_Priority=DMA_Priority_Medium; //仲裁优先级
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifo模式，存储器到存储器自动打开
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo大小设置  full为4字
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //单次触发
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_WC_Stream,&dmainit);
	DMA_Cmd(ange_DMA_WC_Stream,ENABLE);
}
void ange_DMA_WC_ADCConfig(u16 *m)//外设到存储器，16位数据
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_WC_Channel;  //通道
	
	dmainit.DMA_DIR=DMA_DIR_PeripheralToMemory;  //外设到存储器
	dmainit.DMA_PeripheralBaseAddr=(u32)ange_DMA_WC_yuan;  //地址
	dmainit.DMA_Memory0BaseAddr=(u32)m;
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //数据量
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //外设地址递增不使能
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //内存地址使能
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;  //数据大小
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;        
	dmainit.DMA_Mode=DMA_Mode_Circular;  //内存到内存不能用循环
	dmainit.DMA_Priority=DMA_Priority_Medium; //仲裁优先级
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifo模式，存储器到存储器自动打开
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo大小设置  full为4字
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //单次触发
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_WC_Stream,&dmainit);
	DMA_Cmd(ange_DMA_WC_Stream,ENABLE);
}
#endif
