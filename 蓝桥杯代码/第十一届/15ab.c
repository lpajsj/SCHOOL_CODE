#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include "ange.h"
#include "15ab.h"
uchar com=1;
extern uchar moshi;
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xc1,0x8c,0xad,0xfd};//0-9 Ϩ�� U P N -
void hc138(uchar x,uchar a)//xΪͨ����aΪ����
{
	x<<=5;        //P2�ڵ�5.6.7ѡ��ͬ����
	EA=0;
	shuju=a;  //����д��
	P2=P2&0x1f|x;  //����1f��ԭ������λ�Ĳ������䣬
P2&=0x1f;   //����д������λ����
	EA=1;
	return;
}
void initial15()
{
	hc138(5,0);       //�رշ��������̵���
	hc138(4,0xff);
	hc138(7,0xff);
	return;
}
void shumaxianshi(uchar b[8])
{
	uchar x=0x01,a,z;
	a=shuju;   //����P0��ԭ��������
	x<<=com-1;  //com��ʾҪ��ʾ��λ1-8
	hc138(6,x);     
	z=b[com-1];   //��λҪ��ʾ����
	x=duanma[z];  //��ʾ������Ӧ�Ķ���
	if(moshi==1||moshi==2)  //�ӵ㣬�����ģʽ1/2����������ܼӵ�
	{
		if(com==6)
		{
			x&=0x7f; //�������λgΪ��
		}
	}
	hc138(7,x); //����д��
	com++;
	if(com==9)  //��1-8�����
		com=1;
	shuju=a;  //�ָ�����
	return;
}
uchar anjianpanduan()
{
	anjian=0x0f;  //P3�ڸ���λд��0������λд��1���������
	if(key2==0)
	{
		delay(10);   //����
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
return 0xff;  //�޲�������0xff
}
