#ifndef _USART_HIM_H
#define _USART_HIM_H
#include "stm32f10x.h"
#include "ange_USART.h"

#define		Key1_GPIO_PORT					GPIOB
#define		Key1_GPIO_RCC						RCC_APB2Periph_GPIOB
#define		Key1_GPIO_Pin						GPIO_Pin_12
#define		READ_KEY1								GPIO_ReadInputDataBit(Key1_GPIO_PORT,Key1_GPIO_Pin)


#define		Key2_GPIO_PORT					GPIOB
#define		Key2_GPIO_RCC						RCC_APB2Periph_GPIOB
#define		Key2_GPIO_Pin						GPIO_Pin_13
#define		READ_KEY2								GPIO_ReadInputDataBit(Key2_GPIO_PORT,Key2_GPIO_Pin)

#define		Key3_GPIO_PORT					GPIOB
#define		Key3_GPIO_RCC						RCC_APB2Periph_GPIOB
#define		Key3_GPIO_Pin						GPIO_Pin_14
#define		READ_KEY3								GPIO_ReadInputDataBit(Key3_GPIO_PORT,Key3_GPIO_Pin)

#define		Key4_GPIO_PORT					GPIOB
#define		Key4_GPIO_RCC						RCC_APB2Periph_GPIOB
#define		Key4_GPIO_Pin						GPIO_Pin_15
#define		READ_KEY4								GPIO_ReadInputDataBit(Key4_GPIO_PORT,Key4_GPIO_Pin)

#define ToSendOrder(fmg,ag...) {printf(fmg,##ag);\
																USART_SendData(ange_USARTx,0xff);\
																while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_TXE)==0);	\
																USART_SendData(ange_USARTx,0xff);\
																while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_TXE)==0);	\
																USART_SendData(ange_USARTx,0xff);\
																while(USART_GetFlagStatus(ange_USARTx,USART_FLAG_TXE)==0);}

																
																
extern uint8_t Curve_Data[255];
																

void Key_GPIO_Init(void);
uint8_t KeyScan(void);//键盘扫描

void Draw_Curve(uint8_t id,uint8_t CH,uint8_t *buf,uint8_t Times);//绘制曲线	
void Send_Text(char t[],char test[]);//发送文本
void Send_Number(char t[],uint32_t number);//发送整数
void Send_Decimal(char t[],double number);//发送小数
void Send_Colour(char t[],uint16_t Colour);//改变颜色
															
#endif
