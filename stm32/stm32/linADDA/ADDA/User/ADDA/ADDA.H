#ifndef _ADDA_H
#define _ADDA_H
#include "stm32f10x.h"
/***************************************************************************
ADC的宏定义
*************************************************************************/
//引脚的宏定义
#define ADC6_GPIO_RCC			RCC_APB2Periph_GPIOA
#define ADC6_GPIO_PORT		GPIOA
#define ADC6_GPIO_Pin			GPIO_Pin_6

#define ADC7_GPIO_RCC			RCC_APB2Periph_GPIOA
#define ADC7_GPIO_PORT		GPIOA
#define ADC7_GPIO_Pin			GPIO_Pin_7

#define ADC8_GPIO_RCC			RCC_APB2Periph_GPIOB
#define ADC8_GPIO_PORT		GPIOB
#define ADC8_GPIO_Pin			GPIO_Pin_0
//ADC通道的宏定义
#define ADC6_Channel			ADC_Channel_6
#define ADC7_Channel			ADC_Channel_7
#define ADC8_Channel			ADC_Channel_8

/***************************************************************************
DAC的宏定义
*************************************************************************/
#define DAC1_GPIO_RCC			RCC_APB2Periph_GPIOA
#define DAC1_GPIO_PORT		GPIOA
#define DAC1_GPIO_Pin			GPIO_Pin_4



extern __IO uint16_t ADC_ConvertedValue[3];
extern float ADC_ConvertedValueLocal[3];  
      
void ADCX_Config(void);
void DAC_Config(void);

#endif
