#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
#include "AD9910.h"
extern u8 _return;
extern uchar cfr2[4]; //cfr2控制字
extern uchar cfr1[4]; //cfr1控制字
int32_t main(void)
{
//	GPIO_PinRemapConfig()
	Init_ad9910();
//			cfr1[0] = 0x00;		 //RAM 失能
//			cfr2[1] = 0x00;		 //DRG 失能
//			Txcfr();			 //发送cfrx控制字
//			Amp_convert(500);	//写幅度(单位mV)，输入范围：1-650 mV
//			Freq_convert(1000); //写频率(单位Hz)，输入范围：1-400 000 000Hz
//			Amp_convert(500);			//写幅度，输入范围：1-650 mV
	Square_wave(272888); //方波，采样时间间隔输入范围：4*(1~65536)ns
			//扫频波下限频率，上限频率，频率步进（单位：Hz），步进时间间隔（单位：us）
//			SweepFre(100, 1000000, 50, 20000); //步进时间范围·：4*(1~65536)ns
//	Sawtooth_wave(30214); //锯齿波，采样时间间隔输入范围：4*(1~65536)ns
    while (1);                           
	
}
