/*-----------------------------------------------
  名称：AD9854并口驱动
  编写：Liu
  日期：2014.3
  修改：无
  内容：
------------------------------------------------*/
#ifndef __AD9910_H__
#define __AD9910_H__

#include "stm32f10x.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long int

//新增IO
//#define SDO PAout(4)
//#define PDCLK PCout(6)//PDCLK
//#define PLL_LOCK PCout(7)//悬空
//#define SYNC_CLK PCout(9)//悬空
//#define TXENABLE PCout(11)//TXEN
//#define RSO PCout(12)//RAM-SWP-OVR
#define AD9910_PWR PBout(9) //0
#define AD9910_SDIO PDout(0)
#define DRHOLD PCout(12)
#define DROVER PDout(1)
#define UP_DAT PDout(3)
#define PROFILE1 PBout(3)
#define MAS_REST PBout(8) 
#define SCLK PAout(12)     
#define DRCTL PDout(2)    
#define OSK PDout(4)
#define PROFILE0 PDout(5)
#define PROFILE2 PDout(7)
#define CS PAout(9) 

//void Init_AD9910(void);  //INIT 9910
//void AD9910WriteByte (unsigned char commond, unsigned char *databyte,unsigned char lengh);
void AD9110_IOInit(void);
void Init_ad9910(void);
void Freq_convert(ulong Freq);            //写频率
void Amp_convert(unsigned int Amplitude); //写幅度
void Txcfr(void);
void Txramprofile(void);
void Txramdata(int wave_num);
void Square_wave(uint Sample_interval);                                                   //方波;
void Sawtooth_wave(uint Sample_interval);                                                 //三角波
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime); //扫频

#endif
#if 0
#include "stm32_config.h"
#include "stdio.h"
//#include "led.h"
//#include "lcd.h"
#include "key.h"
#include "AD9910.h"
//#include "task_manage.h"
//#include "timer.h"

char str[30]; //显示缓存
extern u8 _return;

extern uchar cfr2[4]; //cfr2控制字
extern uchar cfr1[4]; //cfr1控制字

int main(void)
{
	//	u16 i=0;

	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //设置中断分组
	delay_init(72);										//初始化延时函数
	delay_ms(300);
	Init_ad9910();

//	while(1)
//	{
//		KeyRead(); //读取按键值 （内部备注不详，不用管）
//				   //		Set_PointFre(Keycode, 0);//按键处理
//				   //		if(_return){_return=0;LCD_Refresh_Gram();}//更新显示

//		if (PBin(11) == 0) //单频正弦
//		{
//			cfr1[0] = 0x00;		 //RAM 失能
//			cfr2[1] = 0x00;		 //DRG 失能
//			Txcfr();			 //发送cfrx控制字
//			Amp_convert(500);	//写幅度(单位mV)，输入范围：1-650 mV
//			Freq_convert(1000); //写频率(单位Hz)，输入范围：1-400 000 000Hz
//		}

//		if (PBin(15) == 0) //扫频
//		{
//			Amp_convert(500);			//写幅度，输入范围：1-650 mV
//			//扫频波下限频率，上限频率，频率步进（单位：Hz），步进时间间隔（单位：us）
//			SweepFre(100, 1000000, 50, 2000000); //步进时间范围·：4*(1~65536)ns
//			delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(200);
//			cfr2[1] = 0x00;
//			Txcfr(); 
//			delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(200);
//			cfr2[1] = 0x0e; //DRG 使能
//			Txcfr();
//		}

//		if (PBin(14) == 0) //RAM方波
//		{
			Square_wave(2621440); //方波，采样时间间隔输入范围：4*(1~65536)ns
//		}

//		if (PBin(13) == 0) //RAM锯齿波
//		{
//			Sawtooth_wave(2621440); //锯齿波，采样时间间隔输入范围：4*(1~65536)ns
//		}

//		KEY_EXIT();
//	}



//	Amp_convert(500);			//写幅度，输入范围：1-650 mV
//	//扫频波下限频率，上限频率，频率步进（单位：Hz），步进时间间隔（单位：us）
//	SweepFre(100, 3000000, 300, 200000); //步进时间范围·：4*(1~65536)ns

	while(1)
	{
		
//		delay_ms(1000);delay_ms(1000);
//		cfr2[1] = 0x00;
//		Txcfr(); 
//		
//		
//		delay_ms(1000);delay_ms(1000);
//		cfr2[1] = 0x0e; //DRG 使能
//		Txcfr();	
	}
}




#endif
