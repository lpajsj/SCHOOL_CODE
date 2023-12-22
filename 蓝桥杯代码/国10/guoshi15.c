#include <STC15F2K60S2.H>
#include <absacc.h>
#include <intrins.h>
#include "guoshi15.h"
#include "iic.h"
#include "onewire.h"
uchar com=1;   //数码管显示位
uchar shuma[8]={9,10,10,10,10,10,10,10};  //数码管显示数值
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xc6,0xc7,0xc8,0x8c};//c l n p 段码
uint cajs;// 按键长按计数
extern uchar sc;  //数据参数界面指示
extern uchar shujuj;  //数据界面指示
uchar anjianbu=0,anjianxu;
void hc138(uchar d,uchar x) 
{
	d<<=5;  //通道值左移五位写入138
	EA=0;   //关中断
	P2&=0x1f;  //关通道
	P0=x;  //写入数据
	_nop_();
	_nop_();
	_nop_();
	P2=P2&0x1f|d; //开通道
	_nop_();
	_nop_();
	_nop_();
	P2&=0x1f; //关通道
	EA=1;   //开通道
	return;
}
void shumaxianshi()
{
	uchar x=0x01;  
	x<<=com-1; //选择通道的变量
	hc138(7,0xff);  //消隐
	hc138(6,x);   //选择将要亮的数码管
	x=shuma[com-1]; //该位数码管将要显示的数据
	x=duanma[x]; //取段码
	if(sc==1&&shujuj==1&&com==6)  ////
		x=x&0x7f;///////////显示点与上0x7f
	hc138(7,x); //写入段码
	com++;    //数码显示位加一
	if(com==9) //有八个数码管
	{
		com=1;  //
	}
}
/*
pcf859使用IIC，
da：初始化 0x90 等待 写命令位6为da标志位 等待 写数据 等待 结束
ad：初始化 0x90 等待 写通道低两位为通道 等待 结束 初始化 0x91 等待 读数据 结束 
*/
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
/*
写：初始化 0xa0 等待 写地址 等待 写数据 等待 结束
读：初始化 0xa0 等待 写地址 等待 结束 初始化  0xa1 等待 读数据 结束
*/
void at24w(uchar d,uchar x)
{
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(d);
	IIC_WaitAck();
	IIC_SendByte(x);
	IIC_WaitAck();
	IIC_Stop();
	return;
}
uchar at24r(uchar d)
{
	uchar x;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(d);
	IIC_WaitAck();
//	IIC_Stop();
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	x=IIC_RecByte();
	IIC_Stop();
	return x;
}
/*
分辨率 初始化 写cc 写4e 写随意 写随意 写控制寄存器（1f 3f 5f 7f 默认7f 12位）
温度： 初始化 cc 44启动转化 延时（100 200 400 750） 初始化 cc 4e读取命令 先低八位后高八位
*/
uint retem()
{
	uchar teml,temh;
	uint x;
	Init_DS18B20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);
//	delay(150);
  Init_DS18B20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);
	teml=Read_DS18B20();
	temh=Read_DS18B20();
	x=temh;
	x<<=8;
	x|=teml;
	x=x*6.25;
	return x;
}
void delay(uint n)
{
	unsigned char i, j;
	while(n--)
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
	P32=0;
	P33=0;
	P34=1;
	P35=1;
	if(P35==0)
	{
		delay(10);
			if(P35==0)  //第二个判断后给按键长按计数赋值
			{ 
				cajs=490;
				P33=1;
				if(P35==1)
				{
					P33=0;
					while(P35==0);
					if(cajs!=0)
					{
						return 12;   //计数为0则为长按
					}
					else
					{
						return 120;  //不为0位短按
					}
				}
				P32=1;
				if(P35==1)
				{
					P32=0;
					while(P35==0);
					if(cajs!=0)
					return 13;
					else
					return 130;
				}
			}
	}
	else if(key4==0)
	{
		delay(10);
		if(key4==0)
		{
			key3=1;
			if(key4==1)
			{
				key3=0;
				while(key4==0);
				return 16;
			}
			key2=1;
			if(key4==1)
			{
				key2=0;
				while(key4==0);
				return 17;
			}
		}
	}
	return 0xff;
}
uchar anjiangai()
{
	uchar x=0xff;
	key2=0;
	key3=0;
	key4=1;
	key5=1;   //
	if(anjianbu==0||anjianbu==1)  //等于零是未按下若按下加一，等于一是第二次判断延时消抖
	{
		if(anjianbu==0)  //按键长按判断
		{
			cajs=500;
		}
		if(anjianbu==1) //按键消抖
		{
			delay(5);
		}
		if(key5==0)
		{
			key3=1;
			if(key5==1)
			{
				anjianbu++;
				anjianxu=12;  //不同按键按下变量赋不同的值
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
			if(key2==1)
			{
				anjianbu++;
				anjianxu=17;
				return x;
			}
		}
		anjianbu=0;  //加上步骤等于0
		return x;
	}
	else if(anjianbu==2)
	{
		if(anjianxu==12||anjianxu==13)
		{
			if(cajs>0)
			{
				if(key5==1)
				{
					x=anjianxu;
					anjianbu=0; //短按抬起后给返回值，步骤清零
					return x;
				}
			}
			else
			{
				anjianbu++;
				x=anjianxu*10; //长按到时间给返回值，步骤加一 
				return x;
			}
		}
		if(anjianxu==16||anjianxu==17)
		{
				if(key4==1)
				{
					x=anjianxu;
					anjianbu=0;
					return x;
				}
		}
	}
	else if(anjianbu==3)  //长按等待抬起后给返回值
	{
		if(key5==1&&key4==1)
		{
			anjianbu=0;
		}
	}
	return x;
}
uchar anjiangai2()
{
	uchar x=0xff;
	P32=0;
	P33=0;
	P34=1;
	P35=1;
	if(anjianbu==0)
	{
	cajs=500;
	if(key5==0)
	{
		delay(10);
			if(key5==0)  //第二个判断后给按键长按计数赋值
			{ 
				key3=1;
				if(key5==1)
				{
					key3=0;
					anjianxu=12;
					anjianbu++;
					return x;
				}
				key2=1;
				if(key5==1)
				{
					key2=0;
					anjianxu=13;
					anjianbu++;
					return x;
				}
			}
	}
	else if(key4==0)
	{
		delay(10);
		if(key4==0)
		{
			key3=1;
			if(key4==1)
			{
				key3=0;
				anjianbu++;
				anjianxu=16;
				return x;
			}
			key2=1;
			if(key4==1)
			{
				key2=0;
				anjianbu++;
				anjianxu=17;
				return x;
			}
		}
	}
}
else  if(anjianbu==1)
{
	if(anjianxu==12||anjianxu==13)
	{
		if(cajs>0)
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
		if(anjianxu==16||anjianxu==17)
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
	if(key5==1&&key4==1)
		anjianbu=0;
}
	return x;
}
//void writetime()
//{
//	uchar i,d=0x80,x;
//	Ds1302_Single_Byte_Write(0x8e,0);
//	for(i=0;i<=6;i++)
//	{
//		x=time[6-i];
//		x=x/10*16+x%10;
//		Ds1302_Single_Byte_Write(d,x);
//		d+=2;
//	}
//	Ds1302_Single_Byte_Write(0x8e,0x80);
//}
//void readtime()
//{
//	uchar i,d=0x81,x;
//	Ds1302_Single_Byte_Write(0x8e,0);
//	for(i=0;i<=6;i++)
//	{
//		x=Ds1302_Single_Byte_Read(d);
//		SDA_R=0;
//		time[6-i]=x/16*10+x%16;
//		d+=2;
//	}
//	Ds1302_Single_Byte_Write(0x8e,0x80);
//}