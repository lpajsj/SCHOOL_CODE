#include "stm32f4xx.h"
#include "main.h"
#include "ange_SysTick.h"
#include "ange_USART.h"
#include "ange_rcc.h"
#include "ange_exti.h"
#include "ange_dma.h"
#include "ange_ad.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
#include "ange_da.h"
#include "MS5611.h"
#define led PAout(4)		
extern u32 time;
char oled_buffer[80];
int main(void)
{
//	HSE_SetSysClock(8, 336, 2, 7);
//	  HSI_SetSysClock(16,336,2,7);

//		Initial_System_Timer5();
		ange_USART_init(115200);
//		MS561101BA_Init();	
		printf("618");
		printf("618");
//		led=0;
  while (1)
  {
//			 MS5611BA_Routing();
//				sprintf(oled_buffer,"气压高%0.2f 米  ",MS5611_Altitude*0.01f);

//				sprintf(oled_buffer,"气压%0.1f mbar  ",MS5611_Pressure);

//				sprintf(oled_buffer,"温度%0.1f °C  ",MS5611_Temperature);

//			 SysTick_delayms(100);
  }
}






























