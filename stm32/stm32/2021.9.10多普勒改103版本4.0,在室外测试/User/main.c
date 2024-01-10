#include "arm_math.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
#include "AD9910.h"
#include "ange_ad.h"
#include "ange_SysTick.h"
#include "ange_timt.h"
#include "bsp_led.h"  
#include "ange_timg.h"
#include "shumaguan.h"

/*
双ad PA2 PA4
数码管ser PB11 ,RCK PB13,SCK PB15;
*/
u32 shuju12[ange_ADC12_DMA_BufferSize];
extern u8 adc12_dma_finish;
float ad1_real[ange_ADC12_DMA_BufferSize],ad2_real[ange_ADC12_DMA_BufferSize];
float ad1_mean,ad2_mean;
float ad12_fft[ange_ADC12_DMA_BufferSize*2];
float ad12_fftout[ange_ADC12_DMA_BufferSize];
float ad12_fftout_cfar[ange_ADC12_DMA_BufferSize];
#define ad12_fftout_fazhi 80  //fft结果清零阀值
float ad12_fft_maxresult;
u32   ad12_fft_maxindex;
float doppler_speed;  
#define lvbocishu  2    //两次结果显示一次
u32 doppler_speed_jilu_index=0; //记录速度值数组的下标 
float doppler_speed_jilu[lvbocishu]; //记录速度值
s32   doppler_speed_s32;
//float shuju[10]={1,2,3,4,5,6,7,9,8,10};
arm_cfft_instance_f32 cfft_f32;
void cfar(void);
float cfarsum;
float cfarjilu[ange_ADC12_DMA_BufferSize]={0};
int32_t main(void)
{
	u16 i;
	ange_USART_init(115200);
	ange_ADC12_init();
	ange_ADC12_DMA_NVIC_Config();
	ange_ADC12_DMA_Config(shuju12);
	DMA_ITConfig(ange_ADC12_DMA_Channel,DMA_IT_TC,ENABLE);
//	DMA_ITConfig(ange_ADC12_DMA_Channel,DMA_IT_TC,ENABLE);
	ange_TIMg_PWM_Config();
//	ange_TIMt_PWM_init();
//	TIM_CtrlPWMOutputs(ange_TIMtx,ENABLE);
	ange_595_GPIO_init();
	ange_595_xianshi();
    while (1)
		{	
			if(adc12_dma_finish==1)
			{
				TIM_CtrlPWMOutputs(ange_TIMgx,DISABLE);
//		  TIM_Cmd(ange_TIMgx,DISABLE);
			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
			{
				ad1_real[i]=(float)(shuju12[i]&0xffff)/4095*3.3;
				ad2_real[i]=(float)(shuju12[i]>>16)/4095*3.3;
//				printf("%f,%f\n",ad1_real[i],ad2_real[i]);
			}
//				
				arm_mean_f32(ad1_real,ange_ADC12_DMA_BufferSize,&ad1_mean);
				arm_mean_f32(ad2_real,ange_ADC12_DMA_BufferSize,&ad2_mean);
			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
			{
				ad12_fft[2*i]=ad1_real[i]-ad1_mean;
				ad12_fft[2*i+1]=ad2_real[i]-ad2_mean;
			}
			arm_cfft_init_f32(&cfft_f32,ange_ADC12_DMA_BufferSize);
			arm_cfft_f32(&cfft_f32,ad12_fft,0,1);
			arm_cmplx_mag_f32(ad12_fft,ad12_fftout,ange_ADC12_DMA_BufferSize);
			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
			{
				ad12_fftout_cfar[i]=ad12_fftout[i];
			}
			cfar();
			//打印数据
//			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
//			{
//				//打印原始数据
//			printf("%f,%f,%f\n",ad12_fftout[i],ad12_fftout_cfar[i],cfarjilu[i]);
//			}
//			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
//			{
//				//打印原始数据
//			printf("%f\n",ad12_fftout[i]);
//			}
//			printf("-50\n");
//			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
//			{
//			//打印cfar后的数据
//			printf("%f\n",ad12_fftout_cfar[i]);
//			}
//			printf("-50\n");
//			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
//			{
//			//打印cfar的阀值
//			printf("%f\n",cfarjilu[i]);
//			}
			///////////
			for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
			{
//				printf("%f ",ad12_fftout[i]);
				if(ad12_fftout_cfar[i]<ad12_fftout_fazhi)
				{
					ad12_fftout_cfar[i]=0;
				}
				if(ad12_fftout[i]<ad12_fftout_fazhi)
				{
					ad12_fftout[i]=0;
				}
			}
			//开始fft
			arm_max_f32(ad12_fftout_cfar,ange_ADC12_DMA_BufferSize,&ad12_fft_maxresult,&ad12_fft_maxindex);
			if(ad12_fft_maxindex>(ange_ADC12_DMA_BufferSize/2))
			{
				ad12_fft_maxindex=ange_ADC12_DMA_BufferSize-ad12_fft_maxindex;
				doppler_speed= -1.0*ad12_fft_maxindex*(1.0*ange_TIMg_pinlv/(ange_ADC12_DMA_BufferSize*160));
			}
			else
			{
				doppler_speed= 1.0*ad12_fft_maxindex*(1.0*ange_TIMg_pinlv/(ange_ADC12_DMA_BufferSize*160));
			}
			doppler_speed_jilu[doppler_speed_jilu_index]=doppler_speed;
			doppler_speed_jilu_index++;
			if(doppler_speed_jilu_index==lvbocishu)
			{
			arm_mean_f32(doppler_speed_jilu,doppler_speed_jilu_index,&doppler_speed);
				//防止出现错误速度
				if(doppler_speed>40||doppler_speed<-40)
					doppler_speed=0;
				if(doppler_speed<0.12&&doppler_speed>-0.12)
				doppler_speed=0;
				doppler_speed*=3.6;
			doppler_speed_s32=doppler_speed*100;
				doppler_speed_jilu_index=0;
			if(doppler_speed_s32<0)
			{shuma595[0]=17;}
			else
			{shuma595[0]=10;}
			shuma595[1]=10;
			shuma595[2]=10;
			shuma595[3]=10;
			shuma595[4]=10;
			shuma595[5]=10;
			doppler_speed_s32=abs(doppler_speed_s32);
			if(doppler_speed_s32>10000)
			shuma595[1]=doppler_speed_s32/10000%10;
			if(doppler_speed_s32>1000)
			shuma595[2]=doppler_speed_s32/1000%10;
			shuma595[3]=doppler_speed_s32/100%10;
			shuma595[4]=doppler_speed_s32/10%10;
			shuma595[5]=doppler_speed_s32%10;
			ange_595_xianshi();
		  }
			adc12_dma_finish=0;
			TIM_Cmd(ange_TIMgx,ENABLE);
			TIM_CtrlPWMOutputs(ange_TIMgx,ENABLE);
		 }			
	   }
}
#define cfarshuliang 7
void cfar()
{
	u16 i,j;
	cfarsum=0;
	for(j=0;j<cfarshuliang;j++)
	{
	cfarsum+=ad12_fftout[j];
	}
	for(i=0;i<ange_ADC12_DMA_BufferSize;i++)
	{
		if(i<(cfarshuliang+1)/2)
		{
			cfarjilu[i]=(cfarsum-ad12_fftout[i])/(cfarshuliang-1);
			if(ad12_fftout[i]<cfarjilu[i])
			{
				ad12_fftout_cfar[i]=0;
		  }
			else
			{
				//大于平均值改为不减平均值
//				cfarjilu[i]=(cfarsum-ad12_fftout[i])/6;
//				ad12_fftout_cfar[i]-=(cfarsum-ad12_fftout[i])/6;
			}
	  }
		else if(i>ange_ADC12_DMA_BufferSize-(cfarshuliang+1)/2)
		{
			cfarjilu[i]=(cfarsum-ad12_fftout[i])/(cfarshuliang-1);
			if(ad12_fftout[i]<cfarjilu[i])
			{
				ad12_fftout_cfar[i]=0;
		  }
			else
			{
//				cfarjilu[i]=(cfarsum-ad12_fftout[i])/6;
//				ad12_fftout_cfar[i]-=(cfarsum-ad12_fftout[i])/6;
			}
		}
		else
		{
			cfarsum=cfarsum-ad12_fftout[i-(cfarshuliang+1)/2]+ad12_fftout[i+(cfarshuliang-1)/2];
			cfarjilu[i]=(cfarsum-ad12_fftout[i])/(cfarshuliang-1);
			if(ad12_fftout[i]<cfarjilu[i])
			{
				ad12_fftout_cfar[i]=0;
		  }
			else
			{
//				cfarjilu[i]=(cfarsum-ad12_fftout[i])/6;
//				ad12_fftout_cfar[i]-=(cfarsum-ad12_fftout[i])/6;
			}
		}
//		printf("%d:%f,",i,cfarsum);
//		printf("%f,%f,%f\n",ad12_fftout[i],ad12_fftout_cfar[i],cfarjilu[i]);
}
}

