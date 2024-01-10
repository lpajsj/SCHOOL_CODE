#include "ange_dma.h"
#if ange_DMA_CC
//DMA存储器到存储器，
//ange_DMA_CC_Config() //函数第一个参数为存储器原始数据地址，第二个为目标地址
void ange_DMA_CC_Config( u32* y,u32 *m)//存储器到到存储器
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_CC_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=(u32)y;
	dmainit.DMA_MemoryBaseAddr=(u32)m;
	dmainit.DMA_BufferSize=ange_DMA_CC_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;
	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Priority=DMA_Priority_High;
	dmainit.DMA_M2M=DMA_M2M_Enable;
	DMA_Init(ange_DMA_CC_Channel,&dmainit);
	DMA_Cmd(ange_DMA_CC_Channel,ENABLE);
}
#endif
#if ange_DMA_CW
//DMA存储器到外设，将内存数据利用DMA通过串口传输出去
//在使用时要先初始化出串口数据，ange_DMA_CW_USARTConfig的第一个参数是内存地址，第二个参数为串口数据寄存器地址
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
//将串口接收数据，传输到内存中，
/* ange_DMA_WC_USARTConfig((u32)&USART1->DR,u8 *m) //串口到内存
使用时先初始化串口并开启串口空闲中断，可以实现外部一帧一帧数据的接收
DMA_SetCurrDataCounter函数可以实现DMA重新从首地址开始传输
函数使用顺序
1.ange_USART_init();
2.NVIC中断初始化
2.USART_ITConfig(串口号,USART_IT_IDLE,ENABLE);
3.USART_DMACmd()
*/
//extern u8 jieshouzu[ange_DMA_BufferSize];
//void ange_USART_IRQHandler() //dma空闲  //此函数目前在串口C文件中
//{
//	u8 x;
//	if(USART_GetITStatus(ange_USARTx,USART_IT_IDLE)!=RESET)
//	{
//		DMA_Cmd(ange_DMA_Channel,DISABLE);
//		x=DMA_GetCurrDataCounter(ange_DMA_Channel);
//		DMA_SetCurrDataCounter(ange_DMA_Channel,ange_DMA_BufferSize);
//		ange_usart_sendnumstr(ange_USARTx,jieshouzu,ange_DMA_BufferSize-x);
//		DMA_Cmd(ange_DMA_Channel,ENABLE);
//		USART_ReceiveData(ange_USARTx);
//		USART_ClearFlag(ange_USARTx,USART_FLAG_IDLE);
//	}
//}
void ange_DMA_WC_USARTConfig(u32 y,u8 *m)//外设到存储器，8位数据 //
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
/*
AD,DMA接收,独立模式半字节数据，已经移植到AD的C文件
*/
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
