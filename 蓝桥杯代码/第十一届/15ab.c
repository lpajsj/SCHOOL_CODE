#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include "ange.h"
#include "15ab.h"
uchar com=1;
extern uchar moshi;
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xc1,0x8c,0xad,0xfd};//0-9 熄灭 U P N -
void hc138(uchar x,uchar a)//x为通道，a为数据
{
	x<<=5;        //P2口的5.6.7选择不同部件
	EA=0;
	shuju=a;  //数据写入
	P2=P2&0x1f|x;  //与上1f让原来低五位的参数不变，
P2&=0x1f;   //数据写入后高三位清零
	EA=1;
	return;
}
void initial15()
{
	hc138(5,0);       //关闭蜂鸣器，继电器
	hc138(4,0xff);
	hc138(7,0xff);
	return;
}
void shumaxianshi(uchar b[8])
{
	uchar x=0x01,a,z;
	a=shuju;   //保存P0口原来的数据
	x<<=com-1;  //com表示要显示的位1-8
	hc138(6,x);     
	z=b[com-1];   //本位要显示的数
	x=duanma[z];  //显示的数对应的段码
	if(moshi==1||moshi==2)  //加点，如果是模式1/2第六个数码管加点
	{
		if(com==6)
		{
			x&=0x7f; //段码最高位g为零
		}
	}
	hc138(7,x); //段码写入
	com++;
	if(com==9)  //有1-8数码管
		com=1;
	shuju=a;  //恢复数据
	return;
}
uchar anjianpanduan()
{
	anjian=0x0f;  //P3口高四位写入0，低四位写入1、矩阵键盘
	if(key2==0)
	{
		delay(10);   //消抖
		key4=1;     
		if(key2==1)
		{
		key4=0;
		while(key2==0);	
		return 17;
		}
		key5=1;
		if(key2==1)
		{
		key5=0;
		while(key2==0);	
		return 13;
		}
	}
	if(key3==0)
	{
		delay(5);
				if(key3==0)
				{
		key4=1;
		if(key3==1)
		{
		key4=0;
		while(key3==0);	
		return 16;
		}
		key5=1;
		if(key3==1)
		{
		key5=0;
		while(key3==0);	
		return 12;
		}
	}
	}
return 0xff;  //无操作返回0xff
}
