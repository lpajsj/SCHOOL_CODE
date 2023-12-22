#include "stm32f4xx.h"
#include "main.h"
#include "ange_SysTick.h"
#include "ange_USART.h"
#include "ange_rcc.h"
#include "ange_exti.h"
#include "ange_dma.h"
#include "ange_ad.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
#include "ange_da.h"
#include "ange_spi.h"
#include "MS5611.h"
#include "ange_iic_24c02.h"
#include "bsp_led.h" 
#include "MPU6050.h"
#include "ange_iic.h"
#include "mpu6050_2.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "QMC5883.h"
#include "icm20689.h"
#include "oled2.h"
#include "time.h"
/*
注意两种延时函数的使用,
*/
int main(void)
{

	ange_USART_init(115200);
//	USART_SendData(USART1,10);
	while(1)
	{
		ange_usart_sendbyte(USART1,10);
		ange_usart_sendbyte(USART1,11);
		ange_usart_sendbyte(USART1,12);
		ange_usart_sendbyte(USART1,13);
		SysTick_delayus(150);
		ange_usart_sendbyte(USART1,10);
		ange_usart_sendbyte(USART1,11);
		ange_usart_sendbyte(USART1,12);
		ange_usart_sendbyte(USART1,13);
		SysTick_delayus(10);
	}
}













