/******************* (C) COPYRIGHT 2016 509 Team ***************************/
#ifndef _I2C_H
#define _I2C_H

#include <stm32f10x.h>

/*   IIC�ܽ�����   */
//#define GPIO_I2C	     GPIOB                         // IIC�˿ںź궨��
#define SCL_PIN        GPIO_Pin_6                    	 // IIC_SCL�ܽź궨��
#define SDA_PIN        GPIO_Pin_7                      // IIC_SDA�ܽź궨��
//#define RCC_GPIO_I2C	 RCC_APB2Periph_GPIOB          // IIC�˿ں�ʱ�Ӻ궨��

#define SCL_H         GPIO_SetBits(GPIOB , SCL_PIN)     // IIC_SCL�����
#define SCL_L         GPIO_ResetBits(GPIOB , SCL_PIN)   // IIC_SCL�����
#define SDA_H         GPIO_SetBits(GPIOB , SDA_PIN)     // IIC_SDA�����
#define SDA_L         GPIO_ResetBits(GPIOB , SDA_PIN)   // IIC_SDA�����
#define SCL_read      GPIO_ReadInputDataBit(GPIOB , SCL_PIN) // IIC_SCL��
#define SDA_read      GPIO_ReadInputDataBit(GPIOB , SDA_PIN) // IIC_SDA�� 


#define TRUE 1
#define FALSE 0

/* �������� */
void I2C_Configura(void);                         // IIC��ʼ��
void I2C_delay(void);                             // IIC��ʱ����
u8 I2C_Start(void);                               // IIC��ʼ�ź�                      
void I2C_Stop(void);                              // IIC�����ź�
void I2C_Ack(void);                               // IIC����Ӧ���ź�
void I2C_NoAck(void);                             // IIC���Ͳ�Ӧ���ź�
u8 I2C_WaitAck(void);                             // IIC�ȴ�Ӧ���ź�
void I2C_SendByte(u8 SendByte);                   // IIC����һ���ֽ�   
u8 I2C_RadeByte(void);                            // IIC����һ���ֽ�
u8 Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);   // IICдһ���ֽ�
u8 Single_Read(u8 SlaveAddress,u8 REG_Address);                // IIC��һ���ֽ�
u8 I2C_Read(u8 addr_, u8 reg_, u8 len, u8 *buf);             // IIC����

#endif /* _I2C_H */









