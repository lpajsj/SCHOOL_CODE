#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
extern uint32_t time;
int main()
{
	ange_TIMj_init();
	LED_GPIO_Config();
	ange_TIMg_PWM_init();
	while(1)
	{
//		if(time==1000)
//		{
//			time=0;
//			LED2_TOGGLE;
//		}
	}
}

