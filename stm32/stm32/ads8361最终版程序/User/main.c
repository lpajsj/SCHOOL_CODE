/**************************************************************************
2021.8.3.20:13 �޸���AD7799�ĳ���������SPIģʽ��������ģʽ
2021.8.5.17:22 �޸���ADS8361�ĳ���������SPIģʽ����ֻ�ܶ�Bͨ��������
2021.8.6 9:09  �޸���AD7799�ĳ���������DMA���䣬����AD7799Ҫ��æ����Ȼ����ȫΪF
2021.8.10 ȷ��ads8361���ճ�������spi��ȡ����
ע�������ads8361�иı�궨��ı�spi��ȡģʽ���������ȡģʽ
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
���ݵĶ�������ʾ����
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
			AD=ads8361_readb();  //ֻ�����ݶ�ȡ��ģʽ�����ڳ�ʼ���ǿ��ƣ������ʽ��ȡ
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
		for(i=0;i<1024;i++)  //����ȡ1024�����ݣ�Ŀǰ��6.83us�Ķ�ȡ����
		{
			AD=ADS8361_SPI_Read(); //ֻ�����ݶ�ȡ��ģʽ�����ڳ�ʼ���ǿ��ƣ������ʽ��ȡ

			shuju[i]=AD;  //��ǰ��ʽֻ��ȡ��ǰ16λ������
		}
		for(i=0;i<1024;i++)  
		{
			shuju[i]&=0x1fff;
			if(shuju[i]>0xfff) //�����ݱ�Ϊ�������ŵ�
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

