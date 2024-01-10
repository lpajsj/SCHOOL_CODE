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
/*******************************************************************************
DDS子程序程序：250mv，10KHZ-输出：264mv，10KHZ
250mv，20KHZ-输出：264mv，20KHZ
250mv，30KHZ-输出：272mv，29.76-30.12KHZ
250mv，40KHZ-输出：272mv，39.68-40.32KHZ
250mv，50KHZ-输出：264mv，50KHZ
*********************************************************************************/
u16 adxiaozhun[8];
u16 adshuju[8];
float adbili[8];
float adliangbiao[8];
float adbilichazhi[8];  //67,58,41,32,||54,63,72,81
u16 duoji_pwm1=1000+500,duoji_pwm2=1000+500;
u16 duoji1_zheng=1,duoji2_zheng=1;
u16 panduan(void);
void xianshi(u16 x);
void tiaozheng(u16 x);
int32_t main(void)
{
	u32 i;
	u32 x;
  ange_USART_init(115200);
	ange_TIMt_OC_PWM_init();
	TIM_SetCompare1(ange_TIMt_OCx,duoji_pwm1);
	TIM_SetCompare2(ange_TIMt_OCx,duoji_pwm2);
	
 ange_ADC_init();  //
 ange_ADC_DMA_Config(adshuju); //参数为AD数据将要放入的数组
	ADC_DMACmd(ange_ADCx,ENABLE);     //一旦使能dma配置将无法修改，且此使能不要放在软件触发之后，多通道放在软件触发之后会造成dma通道数据错位
	SysTick_delayms(2000);
		ADC_SoftwareStartConvCmd(ange_ADCx,ENABLE);
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
	for(i=0;i<8;i++)
	{
		adxiaozhun[i]=adshuju[i];
	}
//	ADC_SoftwareStartConvCmd(ange_ADCx,ENABLE);  //adc软件使能,软件启动转换
	while(1)
	{
		ADC_SoftwareStartConvCmd(ange_ADCx,ENABLE);
		while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);
		DMA_ClearFlag(DMA1_FLAG_TC1);
//		ADC_SoftwareStartConvCmd(ange_ADCx,DISABLE);
		for(i=0;i<8;i++)
		printf("%d,",adshuju[i]);
		printf("\n");
		for(i=0;i<8;i++)
		{
			adbili[i]=(float)adshuju[i]/adxiaozhun[i];
			printf("%d:%.3f,",i+1,adbili[i]);
		}
		printf("\n");
		x=panduan();
    xianshi(x);
		tiaozheng(x);
		TIM_SetCompare1(ange_TIMt_OCx,duoji_pwm1);
		TIM_SetCompare2(ange_TIMt_OCx,duoji_pwm2);
//		SysTick_delayms(1);
	}
}

u16 pwm_bujin=10;
void tiaozheng(u16 x)
{
	if(x!=0)
	{
		if((x&0x01)>0)
		{
			if(duoji_pwm1-pwm_bujin>=500)
			   duoji_pwm1-=pwm_bujin;
		}
		if((x&0x010)>0)
		{
			if(duoji_pwm1+pwm_bujin<=2500)
			   duoji_pwm1+=pwm_bujin;
		}
		if((x&0x0100)>0)
		{
			if(duoji_pwm2-pwm_bujin>=500)
			   duoji_pwm2-=pwm_bujin;
		}
		if((x&0x1000)>0)
		{
			if(duoji_pwm2+pwm_bujin<=2500)
			   duoji_pwm2+=pwm_bujin;

		}
	}
}
u16 panduan()
{
	u32 i;
	u16 x=0;
	for(i=0;i<8;i++)
	{
		if(adbili[i]>1.4)
		adliangbiao[i]=1;
		else
			adliangbiao[i]=0;
	}
	adbilichazhi[0]=adliangbiao[6-1]-adliangbiao[7-1];
	adbilichazhi[1]=adliangbiao[5-1]-adliangbiao[8-1];
	adbilichazhi[2]=adliangbiao[4-1]-adliangbiao[1-1];
	adbilichazhi[3]=adliangbiao[3-1]-adliangbiao[2-1];
	adbilichazhi[4]=adliangbiao[5-1]-adliangbiao[4-1];
	adbilichazhi[5]=adliangbiao[6-1]-adliangbiao[3-1];
	adbilichazhi[6]=adliangbiao[7-1]-adliangbiao[2-1];
	adbilichazhi[7]=adliangbiao[8-1]-adliangbiao[1-1];
	for(i=0;i<8;i++)
	{
	if(fabs(adbilichazhi[i])>0.2)
	{
		if(i<4) //左右
		{
			if(adbilichazhi[i]>0)
			{
				x|=0x01; //左边值大
			}
			else
			{
				x|=0x10;
			}
		}
		else //上下
		{
			if(adbilichazhi[i]>0)
			{
				x|=0x100; //左边值大
			}
			else
			{
				x|=0x1000; //右边值大
			}
		}
	}
	}
	return x;
}
void xianshi(u16 x)
{
		if((x&0x01)>0)
		{
			printf("左光强 ");
		}
		else if((x&0x10)>0)
		{
			printf("右光强 ");
		}
		else
		{
			printf("左右平 ");
		}
		
		if((x&0x100)>0)
		{
			printf("上光强 ");
		}
		else if((x&0x1000)>0)
		{
			printf("下光强 ");
		}
		else
		{
			printf("上下平 ");
		}
		printf("\n");
}

