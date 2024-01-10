#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
extern u16 ic1value,ic2value;
extern u8 icfinish;
extern uint32_t time;
int main()
{
	float x,y;
	ange_TIMj_init();
	LED_GPIO_Config();
	ange_TIMt_PWM_init();
	ange_USART_init();
	ange_TIMg_ICPWM_init();
	while(1)
	{
		if(time==1000)
		{
			time=0;
			LED2_TOGGLE;
		if(icfinish==1)
		{
			x=(float)72000000/(ange_TIMg_Prescaler+1)/(ic1value+1);
			y=(float)(ic2value+1)*100/(ic1value+1);
			printf("频率是%0.2fhz  占空比是%0.2f%%\r\n",x,y);
//			ange_TIMg_ICPWM_init();
//			TIM_ITConfig(ange_TIMgx,ange_TIMg_IT_CCx,ENABLE);
			icfinish=0;
		}
		}
	}
}

