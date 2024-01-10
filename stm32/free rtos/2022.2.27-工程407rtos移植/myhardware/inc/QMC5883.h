#ifndef _QMC5883_h
#define _QMC5883_h
#include "stm32f4xx.h"
#include "ange_SysTick.h"
#define qmc_delayms SysTick_delayms
#define QMC5883_ADDR (0x1a>>1)
#define QMC_SCL_GPIO_CLK RCC_AHB1Periph_GPIOD
#define QMC_SCL_GPIO_PORT   GPIOD
#define QMC_SCL_GPIO_Pin    GPIO_Pin_15
#define QMC_IIC_SCL    PDout(15) //SCL

#define QMC_SDA_GPIO_CLK RCC_AHB1Periph_GPIOD
#define QMC_SDA_GPIO_PORT   GPIOD
#define QMC_SDA_GPIO_Pin    GPIO_Pin_14
#define QMC_IIC_SDA    PDout(14) //SDA	 
#define QMC_READ_SDA   PDin(14)  //输入SDA 
#define QMC_SDA_IN()  {GPIOD->MODER&=~(3<<(14*2));GPIOD->MODER|=0<<14*2;}	//PB9输入模式
#define QMC_SDA_OUT() {GPIOD->MODER&=~(3<<(14*2));GPIOD->MODER|=1<<14*2;} //PB9输出模式
void qmc5883_init(void);
void qmc5883_get_raw_data(float *x,float *y,float *z,float *t);
#endif

