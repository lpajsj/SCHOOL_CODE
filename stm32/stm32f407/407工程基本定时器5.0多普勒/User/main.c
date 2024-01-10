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
//		RCC_TIMCLKPresConfig(RCC_TIMPrescActivated);  f407 ������
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

		/*������������Ϊ2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/*���赽�洢��ʵ��*/
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






























