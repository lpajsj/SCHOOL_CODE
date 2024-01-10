#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "chuankouping.h"
#include "stm32f10x.h"
extern PWMqh_TIMt_ICValue_TypeDef PWMqh_TIMt_IC_Value;  //定义捕获值结构体
int main()
{
	LED_GPIO_Config();
	PWMqh_TIMt_IC_init();
	ange_USART_init(115200);
	while(1)
	{
		if(PWMqh_TIMt_IC_Value.Capture_finish)
		{
			LED1_TOGGLE;
			printf("value1:%d",PWMqh_TIMt_IC_Value.Capture_value1);
			printf("value2:%d\r\n",PWMqh_TIMt_IC_Value.Capture_value2);
			SysTick_delayms(100);
			PWMqh_TIMt_IC_Value.Capture_finish=0;	
		}
		
  }
}

