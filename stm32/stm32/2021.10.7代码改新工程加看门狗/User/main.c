#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
#include "AD9910.h"
#include "ange_ad.h"
#include "ange_SysTick.h"
#include "ange_timg.h"
#include "ange_timj.h"
#include "bsp_led.h"  
#include "ange_da.h"
#include "ange_rtc_bkp.h"
#include "key.h"
#include "ange_wdg.h"
#define key2 PCin(13)
#define ange_wwdg 1
#define ange_iwdg 0
int32_t main(void)
{
	u8 wr,tr;
	ange_USART_init(460800);
	LED_GPIO_Config();
	SysTick_delayms(500);
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST)==SET)
	{
		LED_RED;
	}
	else
	{
		LED_BLUE;
	}
	SysTick_delayms(500);
	LED_RGBOFF;
	SysTick_delayms(500);
	RCC_ClearFlag();
#if ange_iwdg
	ange_iwdg_init(IWDG_Prescaler_64,625);
	GPIOC_init(GPIO_Pin_13,GPIO_Mode_IN_FLOATING);
    while (1)
		{
			if(key2==1)
			{
				SysTick_delayms(10);
				if(key2==1)
				{
					LED_GREEN;
					ange_iwdg_feed();
				}
			}
		}		
#endif
#if ange_wwdg
	ange_wwdg_init(WWDG_Prescaler_8,0x7f,0x5f);
	wr=WWDG->CFR&0x7f;
    while (1)
		{
//			tr=WWDG->CR&0x7f;
//			if(tr<wr)
//			{
//					LED_GREEN;
			SysTick_delayms(40);
					WWDG_SetCounter(0x7f);
//			}
		}	
#endif
}



