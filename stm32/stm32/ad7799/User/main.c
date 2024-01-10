#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "chuankouping.h"
#include "stm32f10x.h"
#include "AD7799.H"
extern FunctionalState FIRFilter_Flag;
extern uint8_t FIR_times;
extern double IIR_ADD_AD;
extern uint8_t IIR_times;
extern void shiToer(uint32_t AD);


int main()
{
	u32 ad;
	double x,ya,yf,yi,yaf;
	LED_GPIO_Config();
	ange_USART_init(115200);

	AD7799_GPIO_Init();
	
	spi_ad7799_init();//ad7799��ʼ�����ܽ�����,����Ҫ��û�в���
//	while(!AD7799_Init())
//	{
//	}         //��ȡAD7799��ID��

	AD7799_REG_Init();
	printf("AD7799����\n");
	while(1)
	{

		AD7799_Calibrate(1);
		AD7799_SetMode(AD7799_MODE_CONT);
		while(!AD7799_Ready());
				ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
		     x=ad;
//		printf("%x  ",ad);
//		shiToer((u32)ad);
//		printf("���˲�%.10f ",x*5/16777215);
//		printf("\r\n");
//		//ƽ���˲�
		  average_lvbo(x);
			if(average_b)
			{
				average_b=0;
				ya=average_zhi;
					shiToer((u32)ya);
				printf("ƽ���˲�%.10f ",ya*5/16777215);
				printf("\r\n");
			}
//			//fir�˲�
//			yf=fir_lvbo(x);
//			printf("fir�˲�%.10f ",yf*5/16777215);
//			//iir�˲�
//			yi=iir_lvbo(x);
//			printf("iir�˲�%.10f ",yi*5/16777215);
//			//ƽ����fir�˲�
//			average_fir_lvbo(x);
//				if(average_fir_fb)
//				{
//					shiToer((u32)x);
//				average_fir_fb=0;
//				//ȡֵ
//				yaf=average_fir_zhi;
//				printf("yyds��%.10f ",yaf*5/16777215);
//									printf("\r\n");
//				}
//				printf("\r\n");
				SysTick_delayms(10);
			//

			}
}

