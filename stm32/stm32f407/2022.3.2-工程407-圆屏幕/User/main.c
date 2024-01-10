#include "stm32f4xx.h"
#include "main.h"
#include "ange_SysTick.h"
#include "ange_USART.h"
#include "ange_rcc.h"
#include "ange_exti.h"
#include "ange_dma.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
#include "ange_spi.h"
#include "bsp_led.h" 
#include "ange_iic.h"

#include "GUI_Paint.h"
#include "fonts.h"
#include "image.h"
#include "LCD_Test.h"

void MX_GPIO_init(void);
/*
注意两种延时函数的使用,
*/


int main(void)
{
//	MX_GPIO_init();
//	ange_SPI_GPIO_Congfig();
//	ange_SPI_Config();
	ange_USART_init(115200);
	ange_TIMt_PWM_init();
//	TIM_SetCompare2(TIM5,900);
//	LCD_1in28_test();
//	printf("123455");
	while(1)
	{
		
  }
}
#define DC_Pin GPIO_Pin_8
#define DC_GPIO_Port GPIOA
#define RST_Pin GPIO_Pin_9
#define RST_GPIO_Port GPIOA
#define CS_Pin GPIO_Pin_6
#define CS_GPIO_Port GPIOB
void MX_GPIO_init()
{
	GPIO_InitTypeDef gpioinit;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_OUT;  //
	gpioinit.GPIO_Pin=DC_Pin|RST_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&gpioinit);
	gpioinit.GPIO_Pin=CS_Pin;
	GPIO_Init(CS_GPIO_Port,&gpioinit);
	CS=1;
	RST=1;
	DC=1;
}





























