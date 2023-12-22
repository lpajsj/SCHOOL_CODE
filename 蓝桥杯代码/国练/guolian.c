#include <STC15F2K60S2.H>
#include "guolian15.h"
extern uchar shuma[];
extern uchar time[];
void xianshi();
bit adb;
uchar adzhi;
extern uint cajs;
void Timer0Init(void)		//2����@12.000MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x30;		//���ö�ʱ��ֵ
	TH0 = 0xF8;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void main()
{
	uchar x;
	Timer0Init();
	EA=1;
	ET0=1;
	writetime();
	adinit(1);
	while(1)
	{
		x=anjian();
		if(x==120)
		{
			adb=1;
		}
		if(x==12)
		{
			adb=0;
		}
		adzhi=adpcf();
		readtime();
	}
}
void t0() interrupt 1
{
	TL0 = 0x30;		//���ö�ʱ��ֵ
	TH0 = 0xF8;		//���ö�ʱ��ֵ
	xianshi();
	if(cajs!=0)
	{
		cajs--;
	}
}
void xianshi()
{
	if(adb==0)
	{
			shuma[0]=time[2]/10;
			shuma[1]=time[2]%10;
			shuma[2]=10;
			shuma[3]=time[1]/10;
			shuma[4]=time[1]%10;
			shuma[5]=10;
			shuma[6]=time[0]/10;
			shuma[7]=time[0]%10;
	}
	else if(adb==1)
	{
			shuma[0]=adzhi/100;
			shuma[1]=adzhi/10%10;
			shuma[2]=adzhi%10;
			shuma[3]=10;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=10;
			shuma[7]=10;
	}
	shumaxianshi();
}