#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#include <stm32f10x.h>        // ����F103�̼��� 


#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define SPI_FLASH_SCK_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define SPI_FLASH_SCK_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_5)

#define SPI_FLASH_DIN       GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
//#define SPI_FLASH_DIN_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_6)

#define SPI_FLASH_DOUT_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define SPI_FLASH_DOUT_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define MAX6675_PORT  GPIOB
#define TC1_SCK       GPIO_Pin_13
#define TC1_SO        GPIO_Pin_14
//CS  PE7
#define SCLK_H GPIO_SetBits(MAX6675_PORT, TC1_SCK)
#define SCLK_L GPIO_ResetBits(MAX6675_PORT, TC1_SCK)
#define DIN    GPIO_ReadInputDataBit(MAX6675_PORT, TC1_SO)
 				  	    													  
void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
void SPI1_Init(void);			 //��ʼ��SPI��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�	



void Init_MAX6675_GPIO(void);
unsigned char MAX6675(unsigned char channel);
#endif

