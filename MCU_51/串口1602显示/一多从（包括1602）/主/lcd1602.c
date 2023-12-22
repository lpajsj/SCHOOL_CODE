#include "lcd1602.h"
#include <reg51.h>
#include <intrins.h>
void delay10us(void)  //误差 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=2;a>0;a--);
}
void xiemingling(uchar a)    //写入命令
{
	//chamang();
	RS=0;
	RW=0;
	E=0;
	shuju=a;
	E=1;
	_nop_();
	delay10us();
	E=0;
}
void xieshuju(uchar a)   //写入数据
{
//	chamang();
	RS=1;
	RW=0;
	E=0;
	shuju=a;
	E=1;
	_nop_();
	delay10us();
	E=0;
}
/*
void chamang()   //查忙
{
	uchar b;
	do
		{
	b=0xff;
	E=0;
	RS=0;
	RW=1;
	E=1;
	_nop_();
	b=shuju;
	 }while(b&0x80);
	E=0;
}
*/
void chushihua()   //初始化函数
{
	xiemingling(0x38);  //1602功能设置，16x2显示，5x7点阵，8位数据接口
	delay(1);     //延时
	xiemingling(0x0c);  //开显示，不显示光标
	delay(1);
	xiemingling(0x06);  //写入后光标指针加一
	delay(1);
	xiemingling(0x01);  //清屏
	delay(1);
	return;
}
void diyihang(uchar *a,uchar x,uchar n)  //
{
	x=x+0x80;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	while(*a&&n--) //
	{
		xieshuju(*a);  //
		a++;
	}
	return;
}
void diyihangb(uchar *a,uchar x,uchar n)  //
{
	x=x+0x80;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	while(*a&&n--) //
	{
		xieshuju(*a);  //
		a++;
	}
	xiemingling(0x80);
	xieshuju(0x20);
	xieshuju(0x7e);
	return;
}
void dierhang(uchar *a,uchar x,uchar n)  //
{
	x=x+0xc0;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	while(*a&&n--) //
	{
		xieshuju(*a);  //
		a++;
		x++;//最多写到第十六个
	}
	return;
}
void dierhangxin(uchar *a,uchar x,uchar n)  //
{
	xiemingling(0xc0+x);
	while(n--) //
	{
		xieshuju(*a);  //
		a++;
	}
	return;
}
