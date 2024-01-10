#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
#include "ange_ad.h"
#include "ange_SysTick.h"
#include "ange_timg.h"
#include "ange_timj.h"
#include "bsp_led.h"  
#include "ange_da.h"
#include "ange_rtc_bkp.h"
#include "key.h"
#include "ange_wdg.h"
#include "ange_flash.h"
#include "main.h"
#include "ange_rtc_bkp.h"
#include "ange_iic.h"
#include "ange_timt.h"
#include "ange_rcc.h"
#include "ange_exti.h"
int32_t main(void)
{
	
//	LED_GPIO_Config();
//   ange_extiinit();
//			/*定义一个GPIO_InitTypeDef类型的结构体*/
//		GPIO_InitTypeDef GPIO_InitStructure;
//		/*开启LED相关的GPIO外设时钟*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
//		/*选择要控制的GPIO引脚*/
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
//		/*设置引脚模式为通用推挽输出*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//		/*设置引脚速率为50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		/*调用库函数，初始化GPIO*/
//		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
DBGMCU_Config(DBGMCU_TIM1_STOP,ENABLE);
ange_TIMt_CC_IC_init();
	while(1) 
	{	

		Delay_10us(100000);
		Delay_10us(100);
	}
}



