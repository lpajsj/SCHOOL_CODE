#include "reg51.h"
#include "dijiu15.h"
#include "intrins.h"
#include "iic.h"

uchar shuma[8]={0,0,0,0,0,0,0,0};
uchar duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf};
uchar com=1;
extern bit dengjib;
extern uchar moshi;
void adinit(uchar d)  ///注意·改驱动里的延时
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(d);
	IIC_WaitAck();
	IIC_Stop();
}
uchar adpcf()
{
	uchar x;
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	x=IIC_RecByte();
	IIC_Stop();
	return x;
}
uchar at24r(uchar d)
{
	uchar x;
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
  IIC_SendByte(d);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	x=IIC_RecByte();
	IIC_Stop();
	return x;
}
void at24w(uchar d,uchar x)
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
  IIC_SendByte(d);
	IIC_WaitAck();
  IIC_SendByte(x);
	IIC_WaitAck();
	IIC_Stop();
}
void shumaxianshi()
{
	uchar x=0x01;
	x<<=com-1;
	hc138(7,0xff);
	hc138(6,x);
	x=shuma[com-1];
	hc138(7,duanma[x]);
	com++;
	if(com==9)
		com=1;
	return;
}
void hc138(uchar d,uchar x)
{
	d<<=5;
	EA=0;
	P2&=0x1f;
	P0=x;
	_nop_();
	_nop_();
	_nop_();
	P2=P2&0x1f|d;
	_nop_();
	_nop_();
	_nop_();
	P2&=0x1f;
	EA=1;
	return;
}
void delay(uint x)
{
	unsigned char i, j;
while(x--)
{
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}
}
uchar anjian()
{
	if(key0==0)
	{
		delay(10);
		if(key0==0)
		{
			while(key0==0);
			return 7;
		}
	}
	if(key1==0)
	{
		delay(10);
		if(key1==0)
		{
			while(key1==0);
			return 6;
		}
	}
	if(key2==0)
	{
		delay(10);
		if(key2==0)
		{
			while(key2==0);
			return 5;
		}
	}
	if(key3==0)
	{
		delay(10);
		if(moshi==1)
			dengjib=1;
		else
		{
		if(key3==0)
		{
			while(key3==0);
			return 4;
		}
	}
	}
	else
	{
			dengjib=0;
	}
	return 0xff;
}