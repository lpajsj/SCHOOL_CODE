#include <STC15F2K60S2.H>
#include <absacc.h>
#include <intrins.h>
#include "guoshi15.h"
#include "iic.h"
#include "onewire.h"
uchar com=1;   //�������ʾλ
uchar shuma[8]={9,10,10,10,10,10,10,10};  //�������ʾ��ֵ
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xc6,0xc7,0xc8,0x8c};//c l n p ����
uint cajs;// ������������
extern uchar sc;  //���ݲ�������ָʾ
extern uchar shujuj;  //���ݽ���ָʾ
uchar anjianbu=0,anjianxu;
void hc138(uchar d,uchar x) 
{
	d<<=5;  //ͨ��ֵ������λд��138
	EA=0;   //���ж�
	P2&=0x1f;  //��ͨ��
	P0=x;  //д������
	_nop_();
	_nop_();
	_nop_();
	P2=P2&0x1f|d; //��ͨ��
	_nop_();
	_nop_();
	_nop_();
	P2&=0x1f; //��ͨ��
	EA=1;   //��ͨ��
	return;
}
void shumaxianshi()
{
	uchar x=0x01;  
	x<<=com-1; //ѡ��ͨ���ı���
	hc138(7,0xff);  //����
	hc138(6,x);   //ѡ��Ҫ���������
	x=shuma[com-1]; //��λ����ܽ�Ҫ��ʾ������
	x=duanma[x]; //ȡ����
	if(sc==1&&shujuj==1&&com==6)  ////
		x=x&0x7f;///////////��ʾ������0x7f
	hc138(7,x); //д�����
	com++;    //������ʾλ��һ
	if(com==9) //�а˸������
	{
		com=1;  //
	}
}
/*
pcf859ʹ��IIC��
da����ʼ�� 0x90 �ȴ� д����λ6Ϊda��־λ �ȴ� д���� �ȴ� ����
ad����ʼ�� 0x90 �ȴ� дͨ������λΪͨ�� �ȴ� ���� ��ʼ�� 0x91 �ȴ� ������ ���� 
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
д����ʼ�� 0xa0 �ȴ� д��ַ �ȴ� д���� �ȴ� ����
������ʼ�� 0xa0 �ȴ� д��ַ �ȴ� ���� ��ʼ��  0xa1 �ȴ� ������ ����
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
�ֱ��� ��ʼ�� дcc д4e д���� д���� д���ƼĴ�����1f 3f 5f 7f Ĭ��7f 12λ��
�¶ȣ� ��ʼ�� cc 44����ת�� ��ʱ��100 200 400 750�� ��ʼ�� cc 4e��ȡ���� �ȵͰ�λ��߰�λ
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
			if(P35==0)  //�ڶ����жϺ����������������ֵ
			{ 
				cajs=490;
				P33=1;
				if(P35==1)
				{
					P33=0;
					while(P35==0);
					if(cajs!=0)
					{
						return 12;   //����Ϊ0��Ϊ����
					}
					else
					{
						return 120;  //��Ϊ0λ�̰�
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
	if(anjianbu==0||anjianbu==1)  //��������δ���������¼�һ������һ�ǵڶ����ж���ʱ����
	{
		if(anjianbu==0)  //���������ж�
		{
			cajs=500;
		}
		if(anjianbu==1) //��������
		{
			delay(5);
		}
		if(key5==0)
		{
			key3=1;
			if(key5==1)
			{
				anjianbu++;
				anjianxu=12;  //��ͬ�������±�������ͬ��ֵ
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
		anjianbu=0;  //���ϲ������0
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
					anjianbu=0; //�̰�̧��������ֵ����������
					return x;
				}
			}
			else
			{
				anjianbu++;
				x=anjianxu*10; //������ʱ�������ֵ�������һ 
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
	else if(anjianbu==3)  //�����ȴ�̧��������ֵ
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
			if(key5==0)  //�ڶ����жϺ����������������ֵ
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