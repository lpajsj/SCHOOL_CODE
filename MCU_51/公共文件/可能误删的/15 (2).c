#include <reg51.h> 
#include <intrins.h>
#include "ange.h"
#include "15.h"
uchar com=1;
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar led=0x01;
uchar fj=0x00;bit jidianb=1,fengmingb=1;
extern uchar shuma[];
void hc138(uchar x)
{
	x<<=5;
  P2=P2&0x1f|x;
	_nop_();
	_nop_();
	_nop_();
	P2&=0x1f;
	return;
}
void initial15()
{
	fengming=0;
	jidian=0;
	hc138(5);
	P0=0xff;
	hc138(7);
	P0=0xff;
	hc138(4);
	return;
}
void shumaxianshi(uchar a[8])
{
	uchar x=0x01,z;
	z=shuju;
	x<<=com-1;
	P0=x;
	hc138(6);
	P0=duanma[a[com-1]];
	hc138(7);
	com++;
	if(com==9)
		com=1;
	shuju=z;
	return;
}
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
else	if(key2==0)
	{
		delay(10);
		if(key2==0)
		{
			while(key2==0);
			return 2;
		}
	}
else if(key3==0)
	{
		delay(10);
		if(key3==0)
		{
			while(key3==0);
			return 3;
	}
}
	return 0xff;
}
uchar anjian4x4()
{
	uchar x;
	anjian=0x0f;
	if(key0==0)
	{
		delay(10);
		if(key0==0)
		{
			key7=1;
			if(key0==1)
				x=0;
			key7=0;
			key6=1;
			if(key0==1)
				x=1;
			key6=0;
			key5=1;
			if(key0==1)
				x=2;
			key5=0;
			key4=1;
			if(key0==1)
				x=3;
			key4=0;
			while(key0==0);
     return x;			
		}
	}
	///////////////
	if(key1==0)
	{
		delay(10);
		if(key1==0)
		{
			key7=1;
			if(key1==1)
				x=4;
			key7=0;
			key6=1;
			if(key1==1)
				x=5;
			key6=0;
			key5=1;
			if(key1==1)
				x=6;
			key5=0;
			key4=1;
			if(key1==1)
				x=7;
			key4=0;
			while(key1==0);
     return x;			
		}
	}
	///////////////
	if(key2==0)
	{
		delay(10);
		if(key2==0)
		{
			key7=1;
			if(key2==1)
				x=8;
			key7=0;
			key6=1;
			if(key2==1)
				x=9;
			key6=0;
			key5=1;
			if(key2==1)
				x=10;
			key5=0;
			key4=1;
			if(key2==1)
				x=11;
			key4=0;
			while(key2==0);
     return x;			
		}
	}
	////////////////
	if(key3==0)
	{
		delay(10);
		if(key3==0)
		{
			key7=1;
			if(key3==1)
				x=12;
			key7=0;
			key6=1;
			if(key3==1)
				x=13;
			key6=0;
			key5=1;
			if(key3==1)
				x=14;
			key5=0;
			key4=1;
			if(key3==1)
				x=15;
			key4=0;
			while(key3==0);
     return x;			
		}
	}
	return 0xff;
	///////////////
}