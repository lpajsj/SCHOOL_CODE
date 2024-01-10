#ifndef _USART_H
#define _USART_H
#include "stm32f10x.h"
#include <stdio.h>
#define DBUG_USARTX_IRQn					USART1_IRQn

#define	DBUG_USARTX_GPIO_PORT					GPIOA
#define	DBUG_USARTX_GPIO_RCC			RCC_APB2Periph_GPIOA
#define	DBUG_USARTX_GPIO_TX_Pin				GPIO_Pin_9
#define	DBUG_USARTX_GPIO_RX_Pin				GPIO_Pin_10

#define	DBUG_USARTX										USART1
#define	DBUG_USARTX_ClockCmd					RCC_APB2PeriphClockCmd
#define	DBUG_USARTX_RCC								RCC_APB2Periph_USART1
#define	DBUG_USARTX_BaudRate					115200

//sadasd
#define DEBUG_USARTx                    USART1
#define DEBUG_USART_CLK               	RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd         	RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE           	115200
//USART GPIOÒý½Åºê¶¨Òå
#define DEBUG_USART_GPIO_CLK            RCC_APB2Periph_GPIOA
#define DEBUG_USART_GPIO_APBxClkCmd     RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT        GPIOA
#define DEBUG_USART_TX_GP1O_PIN         GPIO_Pin_9
#define DEBUG_USART_RX_GPIO_PORT        GPIOA
#define DEBUG_USART_RX_GPIO_PIN         GPIO_Pin_10

#define DEBUG_USART_IRQ                 USART1_IRQn
#define DEBUG_USART_IRQHandler          USART1_IRQHandler

void USARTX_Config(void);
void Send_Text(char t[],char test[]);
void Send_Number(char t[],uint32_t number);
void Send_Decimal(char t[],double number);
void Send_Colour(char t[],uint16_t Colour);

#endif
