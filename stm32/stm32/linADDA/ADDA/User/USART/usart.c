#include "usart.h"
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//嵌套向量中断控制器组选择
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//配置USART为中断源
	NVIC_InitStructure.NVIC_IRQChannel=DEBUG_USART_IRQ;
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	//配置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	//配置从优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	//初始化配置
	NVIC_Init(&NVIC_InitStructure);
}
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	//打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd(DEBUG_USART_GPIO_CLK,ENABLE);
	//打开串口外设的时钟
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK,ENABLE);
	//将USART TX的GPIO配置为推挽复用模式
	GPIO_InitStruct.GPIO_Pin=DEBUG_USART_TX_GP1O_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitStruct);
	//将USART RX的GPIO配置为浮空输入模式
	GPIO_InitStruct.GPIO_Pin=DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitStruct);
	//配置串口的工作模式
	USART_InitStruct.USART_BaudRate=DEBUG_USART_BAUDRATE;//配置波特率
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//配置帧数据字长
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//配置停止位
	USART_InitStruct.USART_Parity=USART_Parity_No;//配置校验位
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//配置硬件流控制
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//配置工作模式，收发一起
	USART_Init(DEBUG_USARTx,&USART_InitStruct);//完成串口的初始化配置
	
	//使能串口中断优先级配置
	NVIC_Configuration();
	//使能串口接收中断
	USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);
	//使能串口 UE
	USART_Cmd(DEBUG_USARTx,ENABLE);
}
//重定向C库函数printf到串口，重定向可使用printf函数
int fputc(int ch,FILE *f)
{
	/*发送一个字节数据到串口*/
	USART_SendData(DEBUG_USARTx,(uint8_t)ch);
	/*等待发送完毕*/
	while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TXE)==RESET);	
	return ch;
}
