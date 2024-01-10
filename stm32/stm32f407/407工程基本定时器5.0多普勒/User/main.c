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
#define led PAout(4)		
extern u32 time;
int main(void)
{
	HSE_SetSysClock(8, 336, 2, 7);
//	  HSI_SetSysClock(16,336,2,7);
//		RCC_TIMCLKPresConfig(RCC_TIMPrescActivated);  f407 不存在
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

		/*设置引脚速率为2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/*外设到存储器实验*/
		ange_USART_init(115200);
		printf("618");
		led=0;
		ange_TIMj_init();
		ange_TIMt_PWM_init();
  while (1)
  {
		if(time>=5000)
		{
			led=!led;
			time=0;
		}
  }
}






























