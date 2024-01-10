#include "USART_Init.H"
static void NVIC_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitTypeDef USART_NVIC_InitStruction;
	USART_NVIC_InitStruction.NVIC_IRQChannel=DBUG_USARTX_IRQn;
	USART_NVIC_InitStruction.NVIC_IRQChannelCmd=ENABLE;
	USART_NVIC_InitStruction.NVIC_IRQChannelPreemptionPriority=0;
	USART_NVIC_InitStruction.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&USART_NVIC_InitStruction);
}	
void USARTX_Config(void)
{
	DBUG_USARTX_ClockCmd(DBUG_USARTX_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(DBUG_USARTX_GPIO_RCC,ENABLE);
	
	GPIO_InitTypeDef  USART_GPIO_InitSturction;
	USART_GPIO_InitSturction.GPIO_Mode=GPIO_Mode_AF_PP;
	USART_GPIO_InitSturction.GPIO_Pin=DBUG_USARTX_GPIO_TX_Pin;
	USART_GPIO_InitSturction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DBUG_USARTX_GPIO_PORT,&USART_GPIO_InitSturction);
	
	USART_GPIO_InitSturction.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	USART_GPIO_InitSturction.GPIO_Pin=DBUG_USARTX_GPIO_RX_Pin;
	GPIO_Init(DBUG_USARTX_GPIO_PORT,&USART_GPIO_InitSturction);	
	
	
	USART_InitTypeDef USART_InitStruction;
	USART_InitStruction.USART_BaudRate=DBUG_USARTX_BaudRate;
	USART_InitStruction.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruction.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruction.USART_Parity=USART_Parity_No;
	USART_InitStruction.USART_StopBits=USART_StopBits_1;
	USART_InitStruction.USART_WordLength=USART_WordLength_8b;
	USART_Init(DBUG_USARTX,&USART_InitStruction);
	//根据需要开启中断，不然串口屏会返回数据导致程序卡死
//	NVIC_Config();
//	USART_ITConfig(DBUG_USARTX,USART_IT_RXNE,ENABLE);
	USART_Cmd(DBUG_USARTX,ENABLE);
}
//重定向C库函数printf到串口，重定向可使用printf函数
int fputc(int ch,FILE *f)
{
	/*发送一个字节数据到串口*/
	USART_SendData(DBUG_USARTX,(uint8_t)ch);
	/*等待发送完毕*/
	while(USART_GetFlagStatus(DBUG_USARTX,USART_FLAG_TXE)==RESET);	
	return ch;
}
