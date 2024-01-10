/*-----------------------------------------------
  名称：AD9854并口驱动
  编写：Liu
  日期：2014.3
  修改：无
  内容：
	有560mV左右的偏置，偏置纹波1mV左右
------------------------------------------------*/
#ifndef __AD9910_H__
#define __AD9910_H__

#include "stm32f10x.h"
#include "ange_systick.h"

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
#define MAS_REST PBout(8) //
#define SCLK PAout(12)     //
#define DRCTL PDout(2)    //
#define OSK PDout(4)
#define PROFILE0 PDout(5)
#define PROFILE2 PDout(7)
#define CS PAout(9) //

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


extern uchar cfr1[5];						  //cfr1控制字
extern uchar cfr2[5];						  //cfr2控制字
extern uchar cfr3[5];						  //cfr3控制字  40M输入  25倍频  VC0=101   ICP=001;
extern uchar profile11[9]; //profile1控制字 0x25,0x09,0x7b,0x42
																	  //01振幅控制 23相位控制 4567频率调谐字
extern uchar ramprofile0[8];                                     //ramprofile0控制字
extern uchar drgparameter[20];

#endif
