#include <reg51.h>
#include "ange.h"
#include "intrins.h"
sbit chaofa=P2^7;sbit chaoshou=P1^1;

extern uchar shuma[];
uint dingshijishu=500;
void chaofasong(uint i);
uchar fangshi=0;
sbit key0=P2^0;sbit key1=P2^1;sbit key2=P3^2;sbit key3=P3^3;
uchar dulianjian()
{
	if(key0==0)
	{
		delay(10);
		if(key0==0)
		{
			while(key0==0);
			return 0;
		}
	}

else	if(key1==0)
	{
		delay(10);
		if(key1==0)
		{
			while(key1==0);
			return 1;
		}

	 }
//else	if(key2==0)
//	{
//		delay(10);
//		if(key2==0)
//		{
//			while(key2==0);
//			return 2;
//		}
//	}
//else if(key3==0)
//	{
//		delay(10);
//		if(key3==0)
//		{
//			while(key3==0);
//			return 3;
//	}
//}
	return 0xff;
}
void main()
{
	uchar x;
	IE=0x82;//开T0和外部中断0
	TMOD=0x11;//T0T1模式1，T0显示，T1计时用
	TH0=0xf8;
	TL0=0x30;//T0每次中断1500US
	TR0=1;   //启动T0
	while(1)
	{
		x=dulianjian();
		if(x!=0xff)
		{
			if(x==0)
				fangshi=1;
			else if(x==1)
				fangshi=2;
		}
		if(fangshi==1)
		{
			chaofasong(2000);
			fangshi=0;
		}
		if(fangshi==2)
		{
		if(dingshijishu==0)
		{
			dingshijishu=250;
			chaofasong(2000);
		}
		}
		P2=0x03;
}
}
void t0() interrupt 1
{
	TH0=0xf8;
	TL0=0x30;
	if(dingshijishu!=0)
	{
		dingshijishu--;
	}
//	shumaxianshi(shuma);  //数码管显示
}
void Delay12us()		//@11.0592MHz
{
	unsigned char i;
	i = 29;
	while (--i);
}

void chaofasong(uint i)
{
	while(i--)
	{
		P2=0x0f;
//		chaofa=0;
		Delay12us();
//		chaofa=1;
		P2=0xf3;
		Delay12us();
	}
}