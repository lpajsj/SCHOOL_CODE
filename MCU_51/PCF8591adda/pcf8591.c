#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include <ange.h>
#include <15.h>
#include "iic.h"    //I2C×ÜÏßÇý¶¯¿â 
uchar shuma[]={1,2,3,4,5,6,7,10};
uchar dingshijishu,ada,dashuju,adbiao,dabiao;
#define DELAY_TIME 5

void main()
{
	uchar x=4;
	TMOD=0x01;
	IE=0x82;
	TH0=0xfa;
	TL0=0x24;
	initial15();
	x<<=5;
  P2=P2&0x1f|x;
	P0=0;
	P2=0;
	TR0=1;
	while (1)
	{
		x=dulianjian();
		if(x==2)
		{
			adbiao=1;
			dabiao=0;
		}
		else if(x==3)
		{
			dabiao=1;
			adbiao=0;
		}
		else if(x==0)
		{
			if(dashuju<=240)
				dashuju+=10;

		}
		else if(x==1)
		{
			if(dashuju>=10)
				dashuju-=10;
		}	
		if(adbiao)
		{
			ad_pcfinitial(1);
			ada=ad_pcfrec();
			delay(10);
		}
		if(dabiao)
		{
			da_pcf(dashuju);
			delay(10);
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
		if(dingshijishu==0)
		 {
	shuma[0]=ada/100;
	shuma[1]=ada%100/10;
	shuma[2]=ada%10;
	shuma[3]=dashuju/100;
			 shuma[4]=dashuju%100/10;
			 shuma[5]=dashuju%10;
			 if(adbiao)
				 shuma[6]=1;
			 else
				 shuma[6]=2;
			dingshijishu=500;
		}
	shumaxianshi(shuma);
}
