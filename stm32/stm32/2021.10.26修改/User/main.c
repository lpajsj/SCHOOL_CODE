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
#include "ange_flash.h"
#include "DDS_API.h"
#include "main.h"
/*******************************************************************************
DDS子程序程序：250mv，10KHZ-输出：264mv，10KHZ
250mv，20KHZ-输出：264mv，20KHZ
250mv，30KHZ-输出：272mv，29.76-30.12KHZ
250mv，40KHZ-输出：272mv，39.68-40.32KHZ
250mv，50KHZ-输出：264mv，50KHZ
*********************************************************************************/
int32_t main(void)
{
	SysTick_delayms(1000);
	ange_USART_init(115200);
  ange_TIMg_ICPWM_init();
	while(1)
	{
		
	}
}



