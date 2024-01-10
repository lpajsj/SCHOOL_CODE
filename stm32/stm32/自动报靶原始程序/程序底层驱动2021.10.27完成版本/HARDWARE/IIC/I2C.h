/******************* (C) COPYRIGHT 2016 509 Team ***************************/
#ifndef _I2C_H
#define _I2C_H

#include <stm32f10x.h>

/*   IIC管脚配置   */
//#define GPIO_I2C	     GPIOB                         // IIC端口号宏定义
#define SCL_PIN        GPIO_Pin_6                    	 // IIC_SCL管脚宏定义
#define SDA_PIN        GPIO_Pin_7                      // IIC_SDA管脚宏定义
//#define RCC_GPIO_I2C	 RCC_APB2Periph_GPIOB          // IIC端口号时钟宏定义

#define SCL_H         GPIO_SetBits(GPIOB , SCL_PIN)     // IIC_SCL输出高
#define SCL_L         GPIO_ResetBits(GPIOB , SCL_PIN)   // IIC_SCL输出低
#define SDA_H         GPIO_SetBits(GPIOB , SDA_PIN)     // IIC_SDA输出高
#define SDA_L         GPIO_ResetBits(GPIOB , SDA_PIN)   // IIC_SDA输出高
#define SCL_read      GPIO_ReadInputDataBit(GPIOB , SCL_PIN) // IIC_SCL读
#define SDA_read      GPIO_ReadInputDataBit(GPIOB , SDA_PIN) // IIC_SDA读 


#define TRUE 1
#define FALSE 0

/* 函数声明 */
void I2C_Configura(void);                         // IIC初始化
void I2C_delay(void);                             // IIC延时函数
u8 I2C_Start(void);                               // IIC起始信号                      
void I2C_Stop(void);                              // IIC结束信号
void I2C_Ack(void);                               // IIC发送应答信号
void I2C_NoAck(void);                             // IIC发送不应答信号
u8 I2C_WaitAck(void);                             // IIC等待应答信号
void I2C_SendByte(u8 SendByte);                   // IIC发送一个字节   
u8 I2C_RadeByte(void);                            // IIC接收一个字节
u8 Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);   // IIC写一个字节
u8 Single_Read(u8 SlaveAddress,u8 REG_Address);                // IIC读一个字节
u8 I2C_Read(u8 addr_, u8 reg_, u8 len, u8 *buf);             // IIC连读

#endif /* _I2C_H */









