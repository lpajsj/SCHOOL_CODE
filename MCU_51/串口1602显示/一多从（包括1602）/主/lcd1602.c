#include "lcd1602.h"
#include <reg51.h>
#include <intrins.h>
void delay10us(void)  //��� 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=2;a>0;a--);
}
void xiemingling(uchar a)    //д������
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
void xieshuju(uchar a)   //д������
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
void chamang()   //��æ
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
void chushihua()   //��ʼ������
{
	xiemingling(0x38);  //1602�������ã�16x2��ʾ��5x7����8λ���ݽӿ�
	delay(1);     //��ʱ
	xiemingling(0x0c);  //����ʾ������ʾ���
	delay(1);
	xiemingling(0x06);  //д�����ָ���һ
	delay(1);
	xiemingling(0x01);  //����
	delay(1);
	return;
}
void diyihang(uchar *a,uchar x,uchar n)  //
{
	x=x+0x80;
	xiemingling(x);  //��궨λ��1602�ڶ��е�һ��λ��
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
	xiemingling(x);  //��궨λ��1602�ڶ��е�һ��λ��
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
	xiemingling(x);  //��궨λ��1602�ڶ��е�һ��λ��
	while(*a&&n--) //
	{
		xieshuju(*a);  //
		a++;
		x++;//���д����ʮ����
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
