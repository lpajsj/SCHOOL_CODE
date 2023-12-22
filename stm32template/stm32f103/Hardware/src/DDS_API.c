#include "DDS_API.h"

extern uchar cfr2[4]; //cfr2控制字
extern uchar cfr1[4]; //cfr1控制字
/*
中心电压：500MV
参数1：峰峰值，单位MV
参数2：频率
*/
void sine(u32 volt,u32 frequence)  //
{
	
	cfr1[0] = 0x00;		 //RAM 失能
	cfr2[1] = 0x00;		 //DRG 失能
	Txcfr();			 //发送cfrx控制字
	Amp_convert(volt);	//写幅度(单位mV)，输入范围：1-650 mV
	Freq_convert(frequence); //写频率(单位Hz)，输入范围：1-400 000 000Hz
	
}

void sweep2(u32 volt,u32 startFreq,u32 endFreq,u32 sweepDianShu,u32 totalTime)
{
	cfr1[0] = 0x00;		 //RAM 失能
	cfr2[1] = 0x00;		 //DRG 失能
	Txcfr();			 //发送cfrx控制字
	Amp_convert(volt);			//写幅度，输入范围：1-650 mV
	
	u32	freq = startFreq;
	u32 DianShu = sweepDianShu;		
	u32 buJinPinLv = (endFreq - startFreq)/(sweepDianShu - 1);
	u32 buJinShiJian = totalTime / sweepDianShu;
	
	Freq_convert(freq);
	delayms_DDS_API(buJinShiJian/2);delayms_DDS_API(buJinShiJian/2);
	DianShu--;
	
	while(DianShu--!=1)
	{
		freq+=buJinPinLv;
		Freq_convert(freq);
		delayms_DDS_API(buJinShiJian/2);delayms_DDS_API(buJinShiJian/2);
	}
	
	Freq_convert(endFreq);
	delayms_DDS_API(buJinShiJian/2);delayms_DDS_API(buJinShiJian/2);

	
}

void sweep1(u32 volt,u32 startFreq,u32 endFreq,u32 buJinFreq,u32 buJinTime)
{
	Amp_convert(volt);			//写幅度，输入范围：1-650 mV
	//扫频波下限频率，上限频率，频率步进（单位：Hz），步进时间间隔（单位：us）
	SweepFre(startFreq, endFreq, buJinFreq, buJinTime); //步进时间范围·：0~262143ns
}

