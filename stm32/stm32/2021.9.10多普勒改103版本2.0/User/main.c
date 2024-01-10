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
Ë«ad PA2 PA4
ÊýÂë¹Üser PB11 ,RCK PB13,SCK PB15;
*/
u32 shuju12[ange_ADC12_DMA_BufferSize];
extern u8 adc12_dma_finish;
float ad1_real[ange_ADC12_DMA_BufferSize],ad2_real[ange_ADC12_DMA_BufferSize];
float ad1_mean,ad2_mean;
float ad12_fft[ange_ADC12_DMA_BufferSize*2];
float ad12_fftout[ange_ADC12_DMA_BufferSize];
float ad12_fft_maxresult;
u32   ad12_fft_maxindex;
float doppler_speed;
#define lvbocishu  2
u32 doppler_speed_jilu_index=0;
float doppler_speed_jilu[lvbocishu];
s32   doppler_speed_s32;
//float shuju[10]={1,2,3,4,5,6,7,9,8,10};
arm_cfft_instance_f32 cfft_f32;
int32_t main(void)
{
	u16 i;
	ange_USART_init(115200);
	ange_ADC12_init();
	ange_ADC12_DMA_NVIC_Config();
	ange_ADC12_DMA_Config(shuju12);
	DMA_ITConfig(ange_ADC12_DMA_Channel,DMA_IT_TC,ENABLE);
	DMA_ITConfig(ange_ADC12_DMA_Channel,DMA_IT_TC,ENABLE);
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
//				printf("%f ",ad12_fftout[i]);
				if(ad12_fftout[i]<30)
				{
					ad12_fftout[i]=0;
				}
			}
			arm_max_f32(ad12_fftout,ange_ADC12_DMA_BufferSize,&ad12_fft_maxresult,&ad12_fft_maxindex);
			if(ad12_fft_maxindex>(ange_ADC12_DMA_BufferSize/2))
			{
				ad12_fft_maxindex=ange_ADC12_DMA_BufferSize-ad12_fft_maxindex;
				doppler_speed= -1.0*ad12_fft_maxindex*ange_TIMg_pinlv/(ange_ADC12_DMA_BufferSize*160);
			}
			else
			{
				doppler_speed= 1.0*ad12_fft_maxindex*ange_TIMg_pinlv/(ange_ADC12_DMA_BufferSize*160);
			}
			doppler_speed_jilu[doppler_speed_jilu_index]=doppler_speed;
			doppler_speed_jilu_index++;
			if(doppler_speed_jilu_index==lvbocishu)
			{
			arm_mean_f32(doppler_speed_jilu,doppler_speed_jilu_index,&doppler_speed);
				if(doppler_speed>10||doppler_speed<-10)
					doppler_speed=0;
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



