#ifndef _AD5410_H
#define _AD5410_H
#include "stm32f10x.h"

//软件SPI的AD7799宏定义
#define  AD5410_RCC							RCC_APB2Periph_GPIOA//AD5410的GPIO时钟
#define  AD5410_LATCH_PIN				GPIO_Pin_1 	//AD5410的数据锁存脚
#define  AD5410_LATCH_GPIO			GPIOA
#define  AD5410_LATCH_1					GPIO_SetBits(AD5410_LATCH_GPIO,AD5410_LATCH_PIN)
#define  AD5410_LATCH_0					GPIO_ResetBits(AD5410_LATCH_GPIO,AD5410_LATCH_PIN)


#define  AD5410_SCLK_PIN				GPIO_Pin_2  	//AD5410的时钟引脚
#define  AD5410_SCLK_GPIO				GPIOA
#define  AD5410_SCLK_1					GPIO_SetBits(AD5410_SCLK_GPIO,AD5410_SCLK_PIN)
#define  AD5410_SCLK_0					GPIO_ResetBits(AD5410_SCLK_GPIO,AD5410_SCLK_PIN)

#define  AD5410_SDI_PIN					GPIO_Pin_3	//AD5410的输入引脚
#define  AD5410_SDI_GPIO				GPIOA
#define  AD5410_SDI_1						GPIO_SetBits(AD5410_SDI_GPIO,AD5410_SDI_PIN)
#define  AD5410_SDI_0						GPIO_ResetBits(AD5410_SDI_GPIO,AD5410_SDI_PIN)

#define  AD5410_SDO_PIN					GPIO_Pin_4 	//AD5410的输出引脚
#define  AD5410_SDO_GPIO				GPIOA
#define  READ_AD5410						GPIO_ReadInputDataBit(AD5410_SDO_GPIO,AD5410_SDO_PIN)


void AD5410_GPIO_Init(void);//AD5410的引脚初始化
void AD5410_SendDate(uint32_t date);//写操作
uint32_t AD5410_ReadDate(uint32_t addr);//回读操作
void AD5410_Init(void);//AD5410初始化




#endif
