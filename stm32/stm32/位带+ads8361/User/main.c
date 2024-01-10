#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "ads8361.h"
//#include "arm_math.h"
extern float ads8361a0,ads8361a1,ads8361b0,ads8361b1;
float shuju1[1000],shuju2[1000],shuju3[1000],shuju4[1000];
float shuju11[10],shuju21[10],shuju31[10],shuju41[10];
int main()
{
	u16 i=0;
	u32 x,y;
//	u8 b=0;
//	LED_GPIO_Config();
//	LED_GREEN;

	ange_USART_init();
	ads8361_init();
	SysTick_delayms(100);
	while(1)
	{
//		printf("3.52454,6.222,7.3555\r\n");
		for(i=0;i<1000;i++)
		{
//			ADS8361_Read_01_OUTA(0,&x,&y);//在M0M1=01下，读取A通道的数据
//						shuju1[i]=x&0x7fff;
//			shuju2[i]=ads8361a1;
//			shuju3[i]=y&0x7fff;
//			shuju4[i]=ads8361b1;
			

		  ads8361_read10();
			shuju1[i]=ads8361a0;
			shuju2[i]=ads8361a1;
			shuju3[i]=ads8361b0;
			shuju4[i]=ads8361b1;

			////////////
//			shuju1[i]=0;
//			shuju2[i]=0;
//			shuju3[i]=0;
//			shuju4[i]=0;
//			for(x=0;x<10;x++)
//			{
//		  ads8361_read00a1();
//			shuju1[i]+=ads8361a0;
//			shuju2[i]+=ads8361a1;
//			shuju3[i]+=ads8361b0;
//			shuju4[i]+=ads8361b1;
//			}
//			shuju1[i]/=10;
//			shuju2[i]/=10;
//			shuju3[i]/=10;
//			shuju4[i]/=10;
		}
		/////
		for(i=0;i<1000;i++)
		{
			printf("%f,%f,%f,%f\r\n",shuju1[i]/32768*2.5,shuju2[i]/32768*2.5,shuju3[i]/32768*2.5,shuju4[i]/32768*2.5);
//printf("%x ",shuju1[i]);
//		  printf("a0:%f  ",shuju1[i]/32768*2.5);
//			printf("a1:%f  ",shuju2[i]/32768*2.5);
//			printf("b0:%f  ",shuju3[i]/32768*2.5);
//			printf("b1:%f  ",shuju4[i]/32768*2.5);
		}
	}
}

