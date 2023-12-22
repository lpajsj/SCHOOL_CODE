#include <STC15F2K60S2.H>
#include "guolian15.h"
#include "ds1302.h"
#include "iic.h"
uchar com=1;
uchar shuma[]={0,0,0,0,0,0,0,0};
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};
uchar anjianbu=0,anjianxu;
uchar time[]={55,59,23,1,1,1,21};
uint cajs;
char putchar(char ch)
{
	SBUF=ch;
	while(TI==0);
	TI=0;
	return ch;
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
	P2|=d;
	_nop_();
	_nop_();
	_nop_();
	P2&=0x1f;
	EA=1;
	return;
}
void shumaxianshi()
{
	uchar x=0x01;
	x<<=com-1;
	hc138(7,0xff);
	hc138(6,x);
	x=shuma[com-1];
	x=duanma[x];
	hc138(7,x);
	com++;
	if(com==9)
	{
		com=1;
	}
}
void delay(uint t)		//@12.000MHz
{
	unsigned char i, j;
while(t--)
{
	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}
}
uchar anjian()
{
	uchar x=0xff;
	key5=1;
	key4=1;
	key2=0;
	key3=0;
	if(anjianbu==0)
	{
		cajs=500;
	if(key5==0)
	{
		delay(5);
		if(key5==0)
		{
			key3=1;
			if(key5==1)
			{
				anjianbu++;
				anjianxu=12;
			return x;
			}
			key2=1;
			if(key5==1)
			{
				anjianbu++;
				anjianxu=13;
				return x;
			}
		}
	}
	if(key4==0)
	{
		delay(5);
		if(key4==0)
		{
			key3=1;
			if(key4==1)
			{
				anjianbu++;
				anjianxu=16;
			return x;
			}
			key2=1;
			if(key4==1)
			{
				anjianbu++;
				anjianxu=16;
				return x;
			}
		}
	}
  }
	else if(anjianbu==1)
	{
		if(anjianxu==12||anjianxu==13)
		{
			if(cajs!=0)
			{
				if(key5==1)
				{
					x=anjianxu;
					anjianbu=0;
				}
			}
			else
			{
				x=anjianxu*10;
				anjianbu++;
			}
		}
		else if(anjianxu==16||anjianxu==17)
		{
			if(key4==1)
			{
				x=anjianxu;
				anjianbu=0;
			}
		}
	}
	else if(anjianbu==2)
	{
		if(key4==1&&key5==1)
			anjianbu=0;
	}
	return x;
}
void readtime()
{
	uchar d=0x81,i,x;
	Ds1302_Single_Byte_Write(0x8e,0);
	for(i=0;i<7;i++)
	{
		x=Ds1302_Single_Byte_Read(d);
		SD=0;
		d+=2;
		time[i]=x/16*10+x%16;
	}
Ds1302_Single_Byte_Write(0x8e,0x80);
}
void writetime()
{
	uchar d=0x80,i,x;
	Ds1302_Single_Byte_Write(0x8e,0);
	for(i=0;i<7;i++)
	{
		x=time[i]/10*16+time[i]%10;
		Ds1302_Single_Byte_Write(d,x);
		d+=2;
	}
Ds1302_Single_Byte_Write(0x8e,0x80);
}
void adinit(uchar d)
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
void dapcf(uchar x)
{
  IIC_Start(); 
	IIC_SendByte(0x90);
	IIC_WaitAck(); 
	IIC_SendByte(0x40);
	IIC_WaitAck(); 
	IIC_SendByte(x);
	IIC_WaitAck(); 
  IIC_Stop();  
}
