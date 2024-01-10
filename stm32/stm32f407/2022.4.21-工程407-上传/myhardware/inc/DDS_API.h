#ifndef _DDS_API_H
#define _DDS_API_H
#include "stm32f10x.h"
#include "stdio.h"
#include "AD9910.h"
#include "ange_SysTick.h"

/*
	单频正弦0~650mV，0~400,000,000Hz
	void sine(u32 volt,u32 frequence);
	
	扫频方式1：控制步进速率
				峰峰值mV,	下限频率Hz，上限频率Hz,	  频率步进Hz,  步进时间间隔us
	void sweep1(u32 volt,u32 startFreq,u32 endFreq,u32 buJinFreq, u32 buJinTime);
	
	扫频方式2：控制扫频点数和总时间
				峰峰值mV,	下限频率Hz，上限频率Hz,		   扫频点数，扫频总时间mS
	void sweep2(u32 volt,u32 startFreq,u32 endFreq,u32 sweepDianShu, u32 totalTime);
*/
void sine(u32 volt,u32 frequence);
void sweep1(u32 volt,u32 startFreq,u32 endFreq,u32 buJinFreq,u32 buJinTime);
void sweep2(u32 volt,u32 startFreq,u32 endFreq,u32 sweepDianShu,u32 totalTime);

#endif





