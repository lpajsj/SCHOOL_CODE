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
//			/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
//		GPIO_InitTypeDef GPIO_InitStructure;
//		/*����LED��ص�GPIO����ʱ��*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
//		/*ѡ��Ҫ���Ƶ�GPIO����*/
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
//		/*��������ģʽΪͨ���������*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//		/*������������Ϊ50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		/*���ÿ⺯������ʼ��GPIO*/
//		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
DBGMCU_Config(DBGMCU_TIM1_STOP,ENABLE);
ange_TIMt_CC_IC_init();
	while(1) 
	{	

		Delay_10us(100000);
		Delay_10us(100);
	}
}



