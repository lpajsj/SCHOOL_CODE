#include "ange_USART.h"
void ange_usartnvicinit()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	nvicinit.NVIC_IRQChannel=ange_USART_IRQ;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
void ange_usartinit()
{
	GPIO_InitTypeDef gpioinit;
	USART_InitTypeDef usartinit;
	ange_USART_GPIO_APBxClkCmd(ange_USART_GPIO_CLK,ENABLE);
	ange_USART_APBxClkCmd(ange_USART_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioinit.GPIO_Pin=ange_USART_TX_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_USART_TX_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioinit.GPIO_Pin=ange_USART_RX_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_USART_RX_GPIO_PORT,&gpioinit);
	usartinit.USART_BaudRate=ange_USART_BaudRate;
	usartinit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usartinit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	usartinit.USART_Parity=USART_Parity_No;
	usartinit.USART_StopBits=USART_StopBits_1;
	usartinit.USART_WordLength=USART_WordLength_8b;
	USART_Init(ange_USARTx,&usartinit);
	ange_usartnvicinit();
	USART_ITConfig(ange_USARTx,USART_IT_RXNE,ENABLE);
//USART_IT_PE 奇偶错误中
//USART_IT_TXE 发送中断
//USART_IT_TC 传输完成中
//USART_IT_RXNE 接收中断
//USART_IT_IDLE 空闲总线中
//USART_IT_LBD LIN 中断检
//USART_IT_CTS CTS 中断
//USART_IT_ERR 错误中断
	USART_Cmd(ange_USARTx,ENABLE);
}
void ange_usart_sendbyte(USART_TypeDef *USARTx,u8 x)
{
	USART_SendData(USARTx,x);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
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
void ange_usart_sendstring(USART_TypeDef *USARTx,char *str)
{
	u32 n=0;
	while(str[n]!='\0')
	{
		ange_usart_sendbyte(USARTx,str[n]);
		n++;
	}
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
}
void ange_USART_IRQHandler()
{
	u8 x;
	if(USART_GetITStatus(ange_USARTx,USART_IT_RXNE)!=RESET)
	{
		x=USART_ReceiveData(ange_USARTx);
		ange_usart_sendbyte(ange_USARTx,x+1);
	}
}
int fputc(int ch,FILE *f)
{
	ange_usart_sendbyte(ange_USARTx,(u8)ch);
	while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_TXE)==RESET);
	return ch;
}
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_RXNE)==RESET);
	return (int)USART_ReceiveData(ange_USARTx);
}
