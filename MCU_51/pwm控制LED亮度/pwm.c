#include <reg52.h>
#include "ange.h"
#include "15.h"
uint thtl0=0,ledtime=1;
uchar th0,tl0;
bit ledbright=1;
uchar shuma[]={1,2,3,4,5,6,7,8};
void main()
{
	uchar xl;
	TMOD=0x01;
	TH0=0xf8;
	TL0=0x30;
	IE=0x82;
	tl0=0x30;
	th0=0xf8;
	initial15();
	TR0=1;
	while(1)
	{
		shuma[0]=ledtime/1000;
		shuma[1]=ledtime/100%10;
		shuma[2]=ledtime%100/10;
		shuma[3]=ledtime%10;
		xl=dulianjian();
		if(xl==0&&ledtime<2000)
		{
			ledtime+=100;

		}
		else if(xl==1&&ledtime>100)
		{
			ledtime-=100;
		}
		xl=0xff;
	}
}
void t0() interrupt 1
{
	uint ab;
	if(ledbright)
	{
	shuju=0x0;
	hc138(4);
	thtl0=65536-ledtime;
	shumaxianshi(shuma);
	}
	else
	{
	shuju=0xff;
	hc138(4);
	ab=2002-ledtime;
	thtl0=65536-ab;
	}
	ledbright=!ledbright;
	th0=thtl0/256;
	tl0=thtl0%256;
	TH0=th0;
	TL0=tl0;
	return;
}