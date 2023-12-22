#include <reg51.h>
#include "ange.h"
#include "15.h"
uint pinlv=0,zqjishu=0,dingshijishu=0,xianshijishu=0;
uchar shuma[]={1,2,3,4,5,10,10,10};
void main()
{
	IE=0x88;
	TMOD=0x15;
	TH1=0xf8;
	TL1=0x30;
	TH0=0x00;
	TL0=0x00;
	TR0=1;
	TR1=1;
	IT0=1;
	initial15();
	while(1)
	{
		
	}
}
void t1() interrupt 3
{
	TH1=0xf8;
	TL1=0x30;
	if(dingshijishu!=0)
	dingshijishu--;
	if(dingshijishu==0)
	{
   zqjishu=TH0*256+TL0;
		TR0=0;
    TH0=0x0;
    TL0=0x0;
		TR0=1;
		dingshijishu=500;
	}
	if(xianshijishu!=0)
		xianshijishu--;
	if(xianshijishu==0)
	{
		pinlv=zqjishu;
	shuma[0]=pinlv/10000;
	shuma[1]=pinlv/1000%10;
	shuma[2]=pinlv%1000/100;
	shuma[3]=pinlv%100/10;
	shuma[4]=pinlv%10;   //前四位显示频率
		xianshijishu=500;
	}
	shumaxianshi(shuma);
}
void t0() interrupt 1
{
	TH0=0x22;
	TL0=0x22;
}