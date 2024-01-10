#ifndef __ange_iic_h
#define  __ange_iic_h
#include "stm32f10x.h"
//iic
#define ange_I2Cx I2C1
#define ange_I2C_APBxClock RCC_APB1PeriphClockCmd
#define ange_I2C_CLK RCC_APB1Periph_I2C1
#define ange_I2C_Speed  400000
#define ange_I2C_OwnAddress 0X0A
//GPIO
#define ange_I2C_GPIO_APBxClock RCC_APB2PeriphClockCmd
#define ange_I2C_GPIO_CLK  RCC_APB2Periph_GPIOB
#define ange_I2C_SCL_PORT GPIOB
#define ange_I2C_SCL_Pin  GPIO_Pin_6
#define ange_I2C_SDA_PORT GPIOB
#define ange_I2C_SDA_Pin  GPIO_Pin_7
//
#define eeprom_address 0xa0
#define eeprom_pagesize  8
///
void ange_I2C_GPIO_Config(void);
void ange_I2C_Config(void);
void ange_I2C_init(void);
void ange_I2C_EE_ERROR(u8 x);
void ange_I2C_bytewrite(u8 d,u8 s);
void ange_I2C_pagewrite(u8 d,u16 n,u8 *data);
void ange_I2C_datawrite(u8 d,u16 n,u8 *data);
void ange_I2C_dataread(u8 d,u16 n,u8 *data);
void ange_I2C_waitbusy(u8 d);
#endif
