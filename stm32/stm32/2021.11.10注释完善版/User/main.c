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
#include "ange_rtc_bkp.h"
#include "ange_iic.h"
#include "ange_timt.h"
#include "ange_dma.h"
/*******************************************************************************
DDS子程序程序：250mv，10KHZ-输出：264mv，10KHZ
250mv，20KHZ-输出：264mv，20KHZ
250mv，30KHZ-输出：272mv，29.76-30.12KHZ
250mv，40KHZ-输出：272mv，39.68-40.32KHZ
250mv，50KHZ-输出：264mv，50KHZ
*********************************************************************************/
u8 jieshouzu[ange_DMA_WC_BufferSize];
extern ange_TIMt_CC_ICValue_TypeDef TIMt_IC_Value;
int32_t main(void)
{
		u32 x;
 ange_USART_init(115200);
 ange_usartnvicinit();
 USART_ITConfig(ange_USARTx,USART_IT_IDLE,ENABLE);
ange_DMA_WC_USARTConfig(ange_DMA_WC_yuan,jieshouzu);
 USART_DMACmd(ange_USARTx,USART_DMAReq_Rx,ENABLE);
	while(1)
	{
	}
}



