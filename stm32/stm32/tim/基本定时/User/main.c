#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "ange_timj.h"
extern uint32_t time;
int main()
{
	ange_TIMj_init();
	LED_GPIO_Config();
	while(1)
	{
		if(time==1000)
		{
			time=0;
			LED2_TOGGLE;
		}
	}
}

