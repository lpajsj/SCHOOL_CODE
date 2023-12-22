#include <reg51.h>
#include "ange.h"
#include "15a.h"
#include "intrins.h"
sbit chaofa=P1^0;sbit chaoshou=P1^1;
sfr xx=0x90;
uint chaoju,chaojum;
extern uchar shuma[];
uint dingshijishu=500;
void chaofasong(uchar i);
void main()
{
	IE=0x82;//开T0和外部中断0
	TMOD=0x11;//T0T1模式1，T0显示，T1计时用
	TH0=0xfa;
	TL0=0x24;//T0每次中断1500US
	initial15();  //蓝桥杯板子初始化，关各种器件
	TR0=1;   //启动T0
	while(1)
	{
		if(dingshijishu==0)
		{
			dingshijishu=1;

						chaofasong(8);
		TF1=0;
		TH1=0;
		TL1=0;
		TR1=1;
//		while(chaoshou==1&&TF1==0)
//		{

//		}
//		TR1=0;
//		if(TF1==0)
//		{
//		chaojum=TH1*256+TL1;
//		chaoju=chaojum*0.017;
//		}
//		else
//		{
//			chaoju=9999;
//		}
//		shuma[0]=0;
//		shuma[1]=chaoju/1000%10;
//		shuma[2]=chaoju/100%10;
//		shuma[3]=chaoju/10%10;
//		shuma[4]=chaoju%10;
//		shuma[5]=10;
//		shuma[6]=10;
//		shuma[7]=10;
	}

}
}
void t0() interrupt 1
{
	TH0=0xfa;
	TL0=0x24;
	if(dingshijishu!=0)
	{
		dingshijishu--;
	}
	shumaxianshi(shuma);  //数码管显示
}
void Delay12us()		//@11.0592MHz
{
	unsigned char i;


	i = 30;
	while (--i);
}

void chaofasong(uchar i)
{
	while(i--)
	{
		xx|=~0xfa;
//		chaofa=1;
		Delay12us();
		xx&=0xfa;
//		chaofa=0;
		Delay12us();
	}
}