#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include "ange.h"
#include "15.h"
#include "onewire.h"
#include "iic.h"
uchar shuma[]={1,2,3,0,0,10,7,8};
uint dingshijishu=0;
void main()
{
	uchar x,i=0,tem=10,at24=77,at25;
	TMOD=0x01;
	EA=1;
	ET0=1;
	TH0=0xec;
	TL0=0x78;
	TR0=1;
	fengming=0;
	hc138(5);
	initial15();
	
			at25=read_at24c02(255);
			at25++;
			write_at24c02(255,at25);
		
		 i++;
	while(1)
	{
		x=anjian4x4();
		if(dingshijishu==0)
		{
			tem=temget();
			shuma[6]=tem/10%10;
			shuma[7]=tem%10;
			
//			write_at24c02(i,1);
//		 at25=read_at24c02(i);
//		 i++;
  shuma[0]=at25/100;
	shuma[1]=at25/10%10;
	shuma[2]=at25%10;
			dingshijishu=100;
		}
		if(x==0)
		{
			write_at24c02(255,0);
			at25=read_at24c02(255);
		}
		if(x!=0xff)
		{
			shuma[4]=x%10;
			shuma[3]=x/10;
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
	shumaxianshi(shuma);
}