#ifndef _usart_H
#define _usart_H

#include <stm32f10x.h>        // °üº¬F103¹Ì¼þ¿â 
#include "stdio.h"
#include "sys.h"

//u8 uart4_rx_flag=0;
//u8 uart4_rx_counter=0;

void Usart1_Init(u32 bound);
void Usart2_Init(u32 bound);
void Usart3_Init(u32 bound);
void Usart4_Init(u32 bound);
void Usart5_Init(u32 bound);
void Usart1_Send(unsigned char *DataToSend ,u8 data_num);
void Usart2_Send(unsigned char *DataToSend ,u8 data_num);
void Usart3_Send(unsigned char *DataToSend ,u8 data_num);
void Usart4_Send(unsigned char *DataToSend ,u8 data_num);
void Usart5_Send(unsigned char *DataToSend ,u8 data_num);

//u8 Uart1_4G_init(void);

#endif
