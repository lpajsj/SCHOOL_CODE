/**************************************************************************
2021.8.3.20:13 修改了AD7799的程序，增加了SPI模式和连续读模式
2021.8.5.17:22 修改了ADS8361的程序，增加了SPI模式但是只能读B通道的数据
2021.8.6 9:09  修改了AD7799的程序，增加了DMA传输，但是AD7799要读忙，不然数据全为F
2021.8.10 确定ads8361最终程序，利用spi读取数据
注意可以在ads8361中改变宏定义改变spi读取模式或是软件读取模式
**************************************************************************/
#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "ange_ad.h"
#include "stm32f10x.h"
#include "ange_dma.h"
#include "ange_da.h"
#include "USART_HIM.H"
#include "AD5410.H"
#include "ADDA.H"
#include "key.h"
#include "shumaguan.h"
#include "ad7799.h"
#include "pwm.h"
#include "flash.h"
#include "AD9910.h"
#include "ads8361.h"
#include "hanshu.h"
float shuju1[1024]={0},shuju2[1024]={0},shuju3[1024]={0},shuju4[1024]={0};
s32 shuju[1024];
uint32_t ad1=0,ad2=0,ad3=0;
uint8_t cad[3]={0};
uint32_t AD;
/***********************************************************************************************************
数据的二进制显示程序
************************************************************************************************************/
static void shiToer(uint32_t AD1)
{
	uint32_t i,m=0x800000;
	for(i=0;i<24;i++)
	{
		if((AD1&m)==m)
			printf("1");
		else
			printf("0");
		m>>=1;		
		if((i+1)%4==0)
			printf(" ");
	}
	printf("\n");
}

int main()
{
	uint32_t i;
	ange_USART_init(115200);
	ads8361_init();
	while(1)                                                                                                   
	{
#if ADS8361_Sofeware_SPI		
		for(i=0;i<1000;i++)
		{
			AD=ads8361_readb();  //只是数据读取，模式控制在初始化是控制，软件方式读取
//			shiToer(AD);
//			SysTick_delayms(1);
				shuju1[i]=AD;
//			shuju[i]=AD;
		}
		for(i=0;i<1000;i++)
		{
			printf("%f,%f,%f,%f\r\n",shuju1[i]/32768*2.5,shuju2[i]/32768*2.5,shuju3[i]/32768*2.5,shuju4[i]/32768*2.5);
//			printf("%f,%f,%f,%f\r\n",shuju1[i],shuju2[i],shuju3[i],shuju4[i]);
//			printf("%x  ",shuju[i]);
//			for(i==)
		}
#endif
		
#if ADS8361_Hardware_SPI	
		for(i=0;i<1024;i++)  //连续取1024个数据，目前是6.83us的读取速率
		{
			AD=ADS8361_SPI_Read(); //只是数据读取，模式控制在初始化是控制，软件方式读取

			shuju[i]=AD;  //当前方式只读取了前16位的数据
		}
		for(i=0;i<1024;i++)  
		{
			shuju[i]&=0x1fff;
			if(shuju[i]>0xfff) //将数据变为带正负号的
			{
				shuju[i]&=0xfff;
				shuju[i]=0x1000-shuju[i];
				shuju[i]=-shuju[i];
			}
//			shuju1[i]=shuju[i];
			printf("%d\n",shuju[i]);
//printf("%f,%f,%f,%f\r\n",shuju1[i]/4095*2.5,shuju2[i]/4095*2.5,shuju3[i]/4095*2.5,shuju4[i]/4095*2.5);
//			shuju[i]&=0xffff;
//			if(shuju[i]>0x7fff)
//			{
//				shuju[i]&=0x7fff;
//				shuju[i]=0x8000-shuju[i];
//				shuju[i]=-shuju[i];
//			}
//				shuju1[i]=shuju[i];
//			printf("%f,%f,%f,%f\r\n",shuju1[i]/32768*2.5,
//			shuju2[i]/32768*2.5,shuju3[i]/32768*2.5,shuju4[i]/32768*2.5);
////			shiToer(shuju[i]);
		}		
#endif
  }
}

