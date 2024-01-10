#ifndef __ange_USART_H
#define __ange_USART_H
#include "stm32f10x.h"
#include <stdio.h>
//串口
#define ange_USARTx     						USART1
#define ange_USART_CLK  						RCC_APB2Periph_USART1
#define ange_USART_APBxClkCmd				RCC_APB2PeriphClockCmd
//#define ange_USART_BaudRate  9600

#define ange_USART_IRQ 							USART1_IRQn
#define ange_USART_IRQHandler 			USART1_IRQHandler
//GPIO
#define ange_USART_GPIO_CLK 				RCC_APB2Periph_GPIOA
#define ange_USART_GPIO_APBxClkCmd 	RCC_APB2PeriphClockCmd
#define ange_USART_TX_GPIO_PORT 		GPIOA
#define ange_USART_TX_GPIO_Pin  		GPIO_Pin_9
#define ange_USART_RX_GPIO_PORT 		GPIOA
#define ange_USART_RX_GPIO_Pin  		GPIO_Pin_10
void ange_usartnvicinit(void);
void ange_USART_init(u32 BaudRate);  //串口初始化
//void ange_USART_init(void);
void ange_usart_sendbyte(USART_TypeDef *USARTx,u8 x);
void ange_usart_sendstring(USART_TypeDef *USARTx,u8 *str);
//////
int fputc(int ch,FILE *f);
int fgetc(FILE *f);
#endif
#if 0
typedef struct
{
vu16 SR;
u16 RESERVED1;
vu16 DR;
u16 RESERVED2;
vu16 BRR;
u16 RESERVED3;
vu16 CR1;
u16 RESERVED4;
vu16 CR2;
u16 RESERVED5;
vu16 CR3;
u16 RESERVED6;
vu16 GTPR;
u16 RESERVED7;
} USART_TypeDef;

SR USART 状态寄存器
DR USART 数据寄存器
BRR USART 波特率寄存器
CR1 USART 控制寄存器 1
CR2 USART 控制寄存器 2
CR3 USART 控制寄存器 3
GTPR USART 保护时间和预分频寄存器

typedef struct
{
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

  uint16_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  uint16_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint16_t USART_Parity;                                                                 /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  uint16_t USART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;
#endif
