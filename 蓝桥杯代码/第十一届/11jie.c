#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include "ange.h"
#include "15ab.h"
#include "IIC.h"
#include "shiyan.h"
uchar moshi=1,jishu=0; //moshi��ǰϵͳ��ģʽ,������ֵ
uint adain3,adain3a,canshu;//pcf�˿�3��adֵ,����
uchar shuma[]={0,10,10,10,10,0,0,0};  //Ҫ��ʾ������
void xianshi();   //�������ʾ����
void at24w(uchar d,uchar x);  //at24c02д�룬x����,dͨ���ţ�
uchar at24r(uchar d);
uchar  adpcfr(); //��ȡadֵ��
void adpcf(uchar x);//ad��ʼ��
void dapcf(uchar x);//da
bit jishua=0; //adֵ�����������һ
uint dingshijishu=3333;
uint adjishu=100;
bit  xpb=0;
uchar wucao=0;
void ledzhishi();
void main()
{
	uchar x;
	uchar a;
	EA=1;
	ET0=1;
	TMOD=0x01;
	TH0=0xfa;  // 1.5ms
	TL0=0x24;
	initial15();
	TR0=1;
	canshu=at24r(1)*10;   //�����ǳ���10������EEPROM��
	if(canshu%50!=0)   /// ���ڲ���һ����50�ı�����������ʱ�����ǵ�һ�Σ�EEPROM����������ǰ����ص�
	{
		at24w(1,0);
		canshu=0;
	}
//	init_pcf8591();
adpcf(3); /////11
	while(1)
	{
//		a=adc_pcf8591();//11
		if(adjishu==0)
		{
			adjishu=50;
		a=adpcfr();	
		adain3=a*1.96;  //����ο���ѹΪ5v������λС����500/255=1.96 ���յ�ѹ1.96*adain3
		}
//		adpcf(0x40);  //22
//		a=adpcfr();   //22
//		dapcf(canshu/2);  ///22

		x=anjianpanduan(); //�����ж� ע���ް�������ʱ���ص�ֵ��0xff
		switch(x)   //��Ӧ��������
		{
			case 12:     //����S12�л�ģʽ
				moshi+=1;
			if(moshi==4)  //��������ģʽ��1����ʾ��2�ǲ�����3�Ǽ���
				moshi=1;
			break;
			case 13:
				if(moshi==3)  //S12������������
				{
					jishu=0;
				}
				break;
			case 16:    //����+
				if(moshi==2)
				{
					if(canshu<500)   //��ӽ���
					canshu+=50;
					else
					canshu=0;
				}
				at24w(1,canshu/10);  //����������10��д��EEPROM
				break;
			case 17:
				if(moshi==2)   ///����-
				{
					if(canshu>0)
					canshu-=50;
					else
					canshu=500;
				}
				at24w(1,canshu/10);
				break;
		}
		if(moshi==1||moshi==3)   //����ʱ���Ͻ�������ģʽ1��
		{
			if(jishua)   //jishua��ʼֵΪ�㣬�ڶ��ο�ʼ�жϣ�����ֵ�Ƿ��һ
			{
			if((adain3a>canshu)&&(adain3<canshu))  //ǰһ���뱾�ε�ֵһ����������Ա�
				jishu++;			
			adain3a=adain3;   //���汾��adת����ֵ
			if(jishu==100)
				jishu=0;
			}
			else
				adain3a=adain3;  //�����һ�ε�ֵ
			jishua=1;
		}
		if(adain3<canshu)   //led1
		{
			xpb=1;   //xpb��һ��ʱ���� dingshijishu��ʼ��һ
		}
		else
		{
			xpb=0;  //һ�����ֲ���adain3��С�ڲ����������xpbΪ0��dingshijishu���¼���
			dingshijishu=3333;
		}
		//
		if(x!=0xff)  //�ڰ������µ������
		{
		if(moshi==1)  //led3
		{
			if((x==13||x==16||x==17)) //��Ӧģʽ�������������������������һ
				wucao++;
			else
				wucao=0;
		}
		if(moshi==2)
		{
			if(x==13)
				wucao++;
			else
				wucao=0;
		}
		if(moshi==3)
		{
			if(x==16||x==17)
				wucao++;
			else
				wucao=0;
		}
	}
		if(wucao==255)
			wucao--;
		ledzhishi();
		//
	}
}
void ledzhishi()
{
	uchar x=0xff;  //����һ������Ϊ0xff����һλ��Ҫ������Ӧλ����
	if(dingshijishu==0)
	{
		x&=0xfe;
	}
	if(jishu%2!=0)
	{
		x&=0xfd;
	}
	if(wucao>=3)
	{
		x&=0xfb;
	}
	hc138(4,x);  //
}
void xianshi()
{
	switch(moshi)
	{
		case 1:
		shuma[0]=11;
		shuma[5]=adain3/100;
		shuma[6]=adain3/10%10;
		shuma[7]=adain3%10;
		break;
		case 2:
		shuma[0]=12;
		shuma[5]=canshu/100;
		shuma[6]=canshu/10%10;
		shuma[7]=canshu%10;
		break;
		case 3:
		shuma[0]=13;
		shuma[5]=10;
		shuma[6]=jishu/10;
		shuma[7]=jishu%10;
		break;
	}
	shumaxianshi(shuma);
}
void adpcf(uchar x)
{
	IIC_Start(); //ע��start����Ҫ��Ӧ
	IIC_SendByte(0x90);//1001 A2A1A0 R/w  pcf8591����λ�̶���
	IIC_WaitAck();
	IIC_SendByte(x);//0 daλ xx���뷽ʽ 0 xx�˿ں�
	IIC_WaitAck();
	IIC_Stop();
}
uchar  adpcfr() //��ȡadֵ��x��ʾͨ����
{
	uchar y;
	IIC_Start();
	IIC_SendByte(0x91);//��ȡ����
	IIC_WaitAck();
	y=IIC_RecByte();   ///����������ֱ��stop
	IIC_Stop();
	return y;
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
	return;
}
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
}
uchar at24r(uchar d)
{
	uchar x;
	IIC_Start();
	IIC_SendByte(0xa0);
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
void t0() interrupt 1
{
	TH0=0xfa;
	TL0=0x24;  ///1.5ms
	xianshi();
	if(dingshijishu!=0)
	{
		if(xpb==1)
		dingshijishu--;
	}
	{
		if(adjishu!=0)
		{
			adjishu--;
		}
	}
}