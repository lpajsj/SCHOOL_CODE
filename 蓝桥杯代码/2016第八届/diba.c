#include <reg52.h>
#include <intrins.h>
#include <absacc.h>
#include "ds1302.h"
#include "onewire.h"
#define uchar unsigned char
#define uint unsigned int
#define ucode unsigned char code
sfr shuju=0x80;
sbit key0=P3^0;sbit key1=P3^1;sbit key2=P3^2;sbit key3=P3^3; 
uchar time[7]={20,1,1,1,23,59,50}; ///年 星期-----秒
uchar shuma[8]={10,10,10,10,10,10,10,10};  //数码管显示数组
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf,0xc6};//0-9 熄灭 - c（显示字符）
uchar com=1;    // 对应1-8 表示数码管显示的位
uchar moshi=1;  //wendu表示读取到的温度值 ，moshi表示显示状态 等于1位正常显示或者调整时间 2调整闹钟
uint wendu;
void delay(uint x); //延时函数
uint readtem();    //读取温度
void writetime();  //写时间
void readtime();  //读时间
void hc138(uchar d,uchar x);  //hc138写入
void shumaxianshi();  ///数码管显示函数
uchar anjian();     //按键判断
uchar swei=0;  //swei时间闹钟调整时闪烁的位 ，
uint shanjishu,naojishu=0,naoyanshi=0;//调整时间是闪烁间隔延时计数 、闹钟LED指示闪烁间隔计数、LED闪烁时间计数
bit nzhong=0,szhong=0;  //naozhong闹钟调整标志 时间调整标志 、防止与其他按键冲突
void anjiancaozuo(uchar x);  ///按键对应操作
uchar ntime[3]={0,0,0};    //闹钟数组
void shanshuo();   ///数码管闪烁函数
bit ma=0; //ma数码管 LED明暗标志 、闹钟响应标志
#define wtime writetime();
#define hc13(a,b) hc138(a,b)
void main()
{
	uchar x;
	TMOD=0x01;  //定时器
	TH0=0xfa;  //1.5ms定时器
	TL0=0x24;
	IE=0x82;  //总中断和定时器0中断打开
	TR0=1;  //启动定时器0
	hc13(4,0xff); // 熄灭LED
	hc138(5,0x00);//  关闭位6蜂鸣器 位4继电器
	hc138(6,0xff);// 关闭数码管
//	writetime();///  写入初始时间
	wtime
	wendu=readtem();
	while(1)
	{
		x=anjian();  //  按键判断
		if(szhong==0&&nzhong==0)  ///确定当前不在调整时间或者闹钟
		readtime();  ///读取时间
//		delay(1);  //
		if(x==0xfe)
		wendu=readtem(); //读取温度
		anjiancaozuo(x);//  按键对应操作
		if(naoyanshi!=0)  //如果闹钟正在响应，有按键按下则关闭LED
		{
			if(x!=0xff)   //
			{
				naoyanshi=0;   ///响应时间变为零，防止再次进入闹钟函数使LED亮
				hc138(4,0xff);  //关LED
			}
		}
		else
			hc138(4,0xff);  //如果闹钟延时已过则也关闭LED
	}
}
void shanshuo()
{
	if(swei!=0)     ///如果在调整时间或者闹钟，才闪烁
	{
		if(shanjishu==0)  //
		{
			shanjishu=667;   //667*1.5ms 数码管间隔一秒闪烁
			ma=!ma;      //数码管亮暗标志位
	  }
		if(ma)   //
		{
			switch(swei)  ///判断该哪一位闪烁
			{
				case 1:
				shuma[0]=10;   ///10代表熄灭字符
				shuma[1]=10;
				break;
				case 2:
				shuma[3]=10;
				shuma[4]=10;
				break;
				case 3:
				shuma[6]=10;
				shuma[7]=10;
				break;
			}
		}
	}
	return;
}
void naozhong()
{
	if(swei==0)   //
	{
	if(time[4]==ntime[0]&&time[5]==ntime[1]&&time[6]==ntime[2])  ///时间和闹钟时间相同，且是在正常运行情况下
	{
		naoyanshi=3333;  ///LED闪烁5s
	}
		if(naoyanshi!=0)  //判断延时时间是否到达
		{
			if(naojishu==0)  //亮暗间隔时间到
			{
				naojishu=133;  //赋值间隔时间
				ma=!ma;        //LED翻转
				if(ma)
					hc138(4,0xfe);  //
				else
					hc138(4,0xff);  //
			}
		}
	}
	return;
}
void anjiancaozuo(uchar x)
{
			switch(x)
		{
			case 7:
				if(nzhong==0)  //如果闹钟调整没有运行
				{
				szhong=1;  //时钟调整标志
				swei++;   ///数码管闪烁调整位加一
			if(swei==4)  ///
			{
				writetime();  //时钟只有123位，到0是正常运行
				swei=0;   //
				szhong=0;  //清除时钟调整标志位
			}
		   }
			break;
			case 6:
				if(szhong==0)///时钟调整未在运行
				{
					moshi=3;  //闹钟调整为模式三
				nzhong=1;   //
				if(moshi) //
				swei++;   //
			if(swei==4) //
			{
				nzhong=0;   //
				swei=0; //
				moshi=1;   //正常运行和时钟调整时模式1
			}
		   }
				break;
			case 5:
				if(swei!=0)   //
				{
					if(szhong)//若在调整时间
					{
						time[swei+3]++; //对应位加一
						if(swei==1)
						{
							if(time[swei+3]==24) //小时边界值
								time[swei+3]=0;
						}
						else
						{
							if(time[swei+3]==60)   //分秒边界值
								time[swei+3]=0;
						}
						writetime();
					}
					if(nzhong)   //
					{
						ntime[swei-1]++;   //
						if(swei==1)
						{
							if(ntime[swei-1]==24) //
								ntime[swei-1]=0;
						}
						else
						{
							if(ntime[swei-1]==60)   //
								ntime[swei-1]=0;   //
						}
					}
				}
				break;
			case 4:
				if(swei!=0)
				{
					if(szhong)
					{
						if(time[swei+3]==0)   //
						{
							if(swei==1)
							time[swei+3]=23;
							else
							{
								time[swei+3]=59;   //
							}
							writetime();   //
							break;
						}
						time[swei+3]--;   //
						writetime();     //
					}
					if(nzhong)    //
					{
						if(ntime[swei-1]==0)   //
						{
							if(swei==1)    
							ntime[swei-1]=23;   //
							else
							{
								ntime[swei-1]=59;   //
							}
							break;
						}
						ntime[swei-1]--;    //
					}
				}
				break;
		}
}
void t0() interrupt 1
{
	TH0=0xfa;
	TL0=0x24;   //
	if(shanjishu!=0)
	{
		shanjishu--;    //数码闪烁间隔计数
	}
	if(naoyanshi!=0)
		naoyanshi--;    //闹钟LED闪烁时间计数
	if(naojishu!=0)
		naojishu--;   //LED闪烁间隔计数
	if(moshi==1)
	{
		shuma[0]=time[4]/10;   //模式一显示
		shuma[1]=time[4]%10;
		shuma[2]=11;
		shuma[3]=time[5]/10;
		shuma[4]=time[5]%10;
		shuma[5]=11;
		shuma[6]=time[6]/10;
		shuma[7]=time[6]%10;
	}
	else if(moshi==2)
	{
		shuma[0]=10;       //温度显示，模式二
		shuma[1]=10;
		shuma[2]=wendu/10000;
		shuma[3]=wendu/1000%10;
		shuma[4]=wendu/100%10;
		shuma[5]=wendu/10%10;
		shuma[6]=wendu%10;
		shuma[7]=12;
	}
	else if(moshi==3)
	{
		shuma[0]=ntime[0]/10;    //模式三，调整闹钟显示
		shuma[1]=ntime[0]%10;
		shuma[2]=11;
		shuma[3]=ntime[1]/10;
		shuma[4]=ntime[1]%10;
		shuma[5]=11;
		shuma[6]=ntime[2]/10;
		shuma[7]=ntime[2]%10;
	}
	shanshuo();   //数码闪烁函数
	naozhong();    //闹钟响应函数
	shumaxianshi();   //数码管显示函数
}
uint readtem()
{
	uchar teh,tel;
	uint a;
	Init_DS18B20();
//	Write_DS18B20(0xcc);   //跳过ROM
//	Write_DS18b20(0X4E);
//	Write_DS18B20(0x00);   //
//	Write_DS18B20(0x00);
//	Write_DS18B20(0x1f);
	Init_DS18B20();
	Write_DS18B20(0xcc);   //跳过ROM
	Write_DS18B20(0x44);   //启动温度转换
//	delay(750);
	delay(100);//
	Init_DS18B20();
	Write_DS18B20(0xcc);   //
	Write_DS18B20(0xBE);   //读取寄存器
	tel=Read_DS18B20();      //
	teh=Read_DS18B20();      //
	a=teh<<4;
	a<<=4;
//	tel>>=4;
	a|=tel;    //
	a=a*0.0625*100;
	return a;
}

void writetime()
{
	uchar i,d=0x80,x;
	Ds1302_Single_Byte_Write(0x8e,0);
	for(i=0;i<=6;i++)
	{
		x=time[6-i];
		x=x/10*16+x%10;
		Ds1302_Single_Byte_Write(d,x);
		d+=2;
	}
	Ds1302_Single_Byte_Write(0x8e,0x80);
}
void readtime()
{
	uchar i,d=0x81,x;
	Ds1302_Single_Byte_Write(0x8e,0);
	for(i=0;i<=6;i++)
	{
		x=Ds1302_Single_Byte_Read(d);
		SDA_R=0;
		time[6-i]=x/16*10+x%16;
		d+=2;
	}
	Ds1302_Single_Byte_Write(0x8e,0x80);
}
//void writetime()
//{
//	uchar i,a,d=0x80;    //地址从0x80开始
//	Ds1302_Single_Byte_Write(0x8e,0);  // 去除写保护
//	for (i=0;i<7;i++)
//	{
//		a=time[6-i]/10;   //将数据转为BCD码
//		a<<=4;
////		a*=16;
//		a+=time[6-i]%10;    //
//		Ds1302_Single_Byte_Write(d,a);   //写数据
//		d+=2;     //地址加二
//	}
//	Ds1302_Single_Byte_Write(0x8e,0x80); //开启写保护
//}
//void readtime()   //时间读取
//{
//	uchar i,a,d=0x81;
//	Ds1302_Single_Byte_Write(0x8e,0);
//	for (i=0;i<7;i++)
//	{
////		EA=0;//////!!!!!!!!!!!!!!读数据加中断禁止，否则会出现偶然错误
//		a=Ds1302_Single_Byte_Read(d);
//		EA=1;
//		SDA_R=0;	////////!!!!!!!每次读取一个字节要把IO口拉低或者延时
//		
//		time[6-i]=a/16*10+a%16;

//		d+=2;
//	}
//	Ds1302_Single_Byte_Write(0x8e,0x80);
//}
void delay(uint x)		//@11.0592MHz
{
	unsigned char i,j;
	while(x--)
	{
	_nop_();
	_nop_();
	i = 11;
	j = 190;    //
	do
	{
		while (--j);
	} while (--i);
}
}
void hc138(uchar d,uchar x)
{
	d<<=5;
	EA=0;///关中断
	P2&=0x1f;    //关闭通道
		P0=x;     //写入数据
	_nop_();
	_nop_();
	_nop_();
	P2=P2&0x1f|d;   //选择通道
	_nop_();
	_nop_();
	_nop_();
	P2&=0x1f;    //关闭通道
	EA=1;
	return;
}
void shumaxianshi()   
{
	uchar a=0x01;
	a<<=com-1;
	hc138(7,0xff);
	hc138(6,a);    //选择要亮的位
	a=shuma[com-1];   //要显示的数字
	hc138(7,duanma[a]);   //将字符写入
	com++;         //显示位加一
	if(com==9)
		com=1;
	return;
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
			while(key2==0);   //
			return 5;
		}
	}
	/////
	if(key3==0)
	{
		delay(10);
		if(key3==0)
		{
		  if(szhong==0&&nzhong==0)  //如果在正常显示
		{
			moshi=2;    //key3为低电平时为模式二
			return 0xfe;
		}
		else
			while(key3==0);  //按键正常按下
			return 4;
		}
	}
	if(moshi==2)
	{
		if(key3==1)   //为高电平测返回模式一
			moshi=1;
	}
	return 0xff;    //
}