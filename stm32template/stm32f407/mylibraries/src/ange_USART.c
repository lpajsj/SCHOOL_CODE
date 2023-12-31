#include "ange_USART.h"
#include "ange_dma.h"
void ange_usartnvicinit()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_USART_IRQ;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
void ange_USART_init(u32 BaudRate)  //串口初始化
{
	GPIO_InitTypeDef gpioinit;
	USART_InitTypeDef usartinit;
	ange_USART_GPIO_AHBxClkCmd(ange_USART_GPIO_CLK,ENABLE);
	ange_USART_APBxClkCmd(ange_USART_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AF;  //复用
	gpioinit.GPIO_Pin=ange_USART_TX_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(ange_USART_TX_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Mode=GPIO_Mode_AF; //RX复用模式
	gpioinit.GPIO_Pin=ange_USART_RX_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_USART_RX_GPIO_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_USART_TX_GPIO_PORT,ange_USART_TX_AF_Pinsource,ange_USART_TX_AF);  //复用
	GPIO_PinAFConfig(ange_USART_TX_GPIO_PORT,ange_USART_RX_AF_Pinsource,ange_USART_RX_AF);
	usartinit.USART_BaudRate=BaudRate;   //波特率
//	usartinit.USART_BaudRate=ange_USART_BaudRate;   //波特率
	usartinit.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //硬件流控制
	usartinit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //串口模式
	usartinit.USART_Parity=USART_Parity_No;  //校检位
	usartinit.USART_StopBits=USART_StopBits_1; //停止位
	usartinit.USART_WordLength=USART_WordLength_8b; //数据位，如果有校检位选择9位
	USART_Init(ange_USARTx,&usartinit);

	ange_usartnvicinit();  //中断时使用
	USART_ITConfig(ange_USARTx,USART_IT_TC,ENABLE);
//USART_IT_PE 奇偶错误中
//USART_IT_TXE 发送中断
//USART_IT_TC 传输完成中
//USART_IT_RXNE 接收中断
//USART_IT_IDLE 空闲总线中
//USART_IT_LBD LIN 中断检
//USART_IT_CTS CTS 中断
//USART_IT_ERR 错误中断
	USART_Cmd(ange_USARTx,ENABLE);
//	USART_DMACmd(ange_USARTx,USART_DMAReq_Rx,ENABLE);  //应该只是dma与usart的通道最后开
}
void ange_usart_sendbyte(USART_TypeDef *USARTx,u8 x)
{
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
	USART_SendData(USARTx,x);
	
//USART_FLAG_CTS CTS 标志位
//USART_FLAG_LBD LIN 中断检测标志位
//USART_FLAG_TXE 发送数据寄存器空标志位
//USART_FLAG_TC 发送完成标志位
//USART_FLAG_RXNE 接收数据寄存器非空标志位
//USART_FLAG_IDLE 空闲总线标志位
//USART_FLAG_ORE 溢出错误标志位
//USART_FLAG_NE 噪声错误标志位
//USART_FLAG_FE 帧错误标志位
//USART_FLAG_PE 奇偶错误标志位
}
void ange_usart_sendstring(USART_TypeDef *USARTx,u8 *str)
{
	u32 n=0;
	while(str[n]!='\0')
	{
		ange_usart_sendbyte(USARTx,str[n]);
		n++;
	}
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
}
void ange_usart_sendnumstr(USART_TypeDef *usartx,u8 *str,u16 n)
{
	while(n--)
	{
	ange_usart_sendbyte(usartx,*str);
		str++;
	}
}
//u8 jieshouzu[ange_DMA_WC_BufferSize];
//void ange_USART_IRQHandler() //dma空闲
//{
//	u8 x;
//	if(USART_GetITStatus(ange_USARTx,USART_IT_IDLE)!=RESET)
//	{
//		DMA_Cmd(ange_DMA_WC_Stream,DISABLE);  //要关闭dma，USART_DMACmd不可以，
//		x=DMA_GetCurrDataCounter(ange_DMA_WC_Stream);
//		DMA_SetCurrDataCounter(ange_DMA_WC_Stream,ange_DMA_WC_BufferSize);  
//		ange_usart_sendnumstr(ange_USARTx,jieshouzu,ange_DMA_WC_BufferSize-x);
//		DMA_Cmd(ange_DMA_WC_Stream,ENABLE);
//		USART_ReceiveData(ange_USARTx);//需要接收一次数据不然会一直进中断
//		USART_ClearFlag(ange_USARTx,USART_FLAG_IDLE);
//	}
//}

//void ange_USART_IRQHandler()   //回显
//{
//	u8 x;
//	if(USART_GetITStatus(ange_USARTx,USART_IT_RXNE)!=RESET)
//	{
//		x=USART_ReceiveData(ange_USARTx);
//		ange_usart_sendbyte(ange_USARTx,x+1);
//	}
//}
u8 jishu=0;
u8 jishu1=0;
void ange_USART_IRQHandler()   //回显
{
	u8 x;
	if(USART_GetITStatus(ange_USARTx,USART_IT_TC)!=RESET)
	{
		jishu++;
		USART_ClearITPendingBit(ange_USARTx,USART_IT_TC);
//		while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_TXE)==0); //RESET
//		  USART1->DR=jishu1;
//		jishu++;
//		jishu1++;
		if(jishu==255)
		{
//			USART_Cmd(ange_USARTx,DISABLE);
//			USART_ITConfig(ange_USARTx,USART_IT_TXE,DISABLE);
//			USART_Cmd(ange_USARTx,ENABLE);
		}
//		x=USART_ReceiveData(ange_USARTx);
//		ange_usart_sendbyte(ange_USARTx,x+1);
		
	}
}
#if 0
int fputc(int ch,FILE *f)
{
	ange_usart_sendbyte(ange_USARTx,(u8)ch);
	return ch;
}
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_RXNE)==RESET);
	return (int)USART_ReceiveData(ange_USARTx);
}
#endif

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
