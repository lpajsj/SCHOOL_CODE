#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
extern ange_TIMt_CC_ICValue_TypeDef TIMt_IC_Value;
extern uint32_t time;
int main()
{
	u32 x;
	ange_TIMj_init();
	LED_GPIO_Config();
	ange_TIMt_CC_IC_init();
	ange_USART_init();
	while(1)
	{
		if(time==1000)
		{
			time=0;
			LED2_TOGGLE;
		}
		if(TIMt_IC_Value.Capture_finish==1)
		{
			x=TIMt_IC_Value.Capture_Period*(ange_TIMt_CC_Period+1) \
			+TIMt_IC_Value.Capture_value+1;
//		printf("按键按下时间%d.%ds\r\n",x/1000000,x%1000000);
			printf("按键按下时间%d.%ds\r\n",x/10000,x%10000);
			TIMt_IC_Value.Capture_finish=0;
		}
	}
}

