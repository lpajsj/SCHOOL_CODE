#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
#include "ange.h"
#include "15a.h"
#include "ds1302.h"
bit shuaxinbiao,yeardayb;
extern uchar dstime[7];
extern uchar shuma[];
uint dingshijishu=500,shuaxinjishu=500;
void main()
{
	TMOD=0x01;
	EA=1;
	ET0=1;
	TH0=0xec;
	TL0=0x78;
	TR0=1;
	initial15();
	write_dstime();
	while(1)
	{
		read_dstime();
		delay(10);
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
	else
	{
		yeardayb=!yeardayb;
		dingshijishu=10000;
	}
	if(shuaxinjishu!=0)
	{
		shuaxinjishu--;
	}
	else
	{
		shuaxinbiao=1;
		shuaxinjishu=500;
	}
	if(shuaxinbiao)
	{
		if(yeardayb)
		{
		shuma[0]=dstime[4]/10;
		shuma[1]=dstime[4]%10;
		shuma[2]=11;
		shuma[3]=dstime[5]/10;
		shuma[4]=dstime[5]%10;
		shuma[5]=11;
		shuma[6]=dstime[6]/10;
		shuma[7]=dstime[6]%10;
		}
		else
		{
		shuma[0]=dstime[0]/10;
		shuma[1]=dstime[0]%10;
		shuma[2]=11;
		shuma[3]=dstime[2]/10;
		shuma[4]=dstime[2]%10;
		shuma[5]=11;
		shuma[6]=dstime[3]/10;
		shuma[7]=dstime[3]%10;
		}
		shuaxinbiao=0;
	}
	shumaxianshi(shuma);
}