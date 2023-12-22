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
uchar time[7]={20,1,1,1,23,59,50}; ///�� ����-----��
uchar shuma[8]={10,10,10,10,10,10,10,10};  //�������ʾ����
ucode duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf,0xc6};//0-9 Ϩ�� - c����ʾ�ַ���
uchar com=1;    // ��Ӧ1-8 ��ʾ�������ʾ��λ
uchar moshi=1;  //wendu��ʾ��ȡ�����¶�ֵ ��moshi��ʾ��ʾ״̬ ����1λ������ʾ���ߵ���ʱ�� 2��������
uint wendu;
void delay(uint x); //��ʱ����
uint readtem();    //��ȡ�¶�
void writetime();  //дʱ��
void readtime();  //��ʱ��
void hc138(uchar d,uchar x);  //hc138д��
void shumaxianshi();  ///�������ʾ����
uchar anjian();     //�����ж�
uchar swei=0;  //sweiʱ�����ӵ���ʱ��˸��λ ��
uint shanjishu,naojishu=0,naoyanshi=0;//����ʱ������˸�����ʱ���� ������LEDָʾ��˸���������LED��˸ʱ�����
bit nzhong=0,szhong=0;  //naozhong���ӵ�����־ ʱ�������־ ����ֹ������������ͻ
void anjiancaozuo(uchar x);  ///������Ӧ����
uchar ntime[3]={0,0,0};    //��������
void shanshuo();   ///�������˸����
bit ma=0; //ma����� LED������־ ��������Ӧ��־
#define wtime writetime();
#define hc13(a,b) hc138(a,b)
void main()
{
	uchar x;
	TMOD=0x01;  //��ʱ��
	TH0=0xfa;  //1.5ms��ʱ��
	TL0=0x24;
	IE=0x82;  //���жϺͶ�ʱ��0�жϴ�
	TR0=1;  //������ʱ��0
	hc13(4,0xff); // Ϩ��LED
	hc138(5,0x00);//  �ر�λ6������ λ4�̵���
	hc138(6,0xff);// �ر������
//	writetime();///  д���ʼʱ��
	wtime
	wendu=readtem();
	while(1)
	{
		x=anjian();  //  �����ж�
		if(szhong==0&&nzhong==0)  ///ȷ����ǰ���ڵ���ʱ���������
		readtime();  ///��ȡʱ��
//		delay(1);  //
		if(x==0xfe)
		wendu=readtem(); //��ȡ�¶�
		anjiancaozuo(x);//  ������Ӧ����
		if(naoyanshi!=0)  //�������������Ӧ���а���������ر�LED
		{
			if(x!=0xff)   //
			{
				naoyanshi=0;   ///��Ӧʱ���Ϊ�㣬��ֹ�ٴν������Ӻ���ʹLED��
				hc138(4,0xff);  //��LED
			}
		}
		else
			hc138(4,0xff);  //���������ʱ�ѹ���Ҳ�ر�LED
	}
}
void shanshuo()
{
	if(swei!=0)     ///����ڵ���ʱ��������ӣ�����˸
	{
		if(shanjishu==0)  //
		{
			shanjishu=667;   //667*1.5ms ����ܼ��һ����˸
			ma=!ma;      //�����������־λ
	  }
		if(ma)   //
		{
			switch(swei)  ///�жϸ���һλ��˸
			{
				case 1:
				shuma[0]=10;   ///10����Ϩ���ַ�
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
	if(time[4]==ntime[0]&&time[5]==ntime[1]&&time[6]==ntime[2])  ///ʱ�������ʱ����ͬ���������������������
	{
		naoyanshi=3333;  ///LED��˸5s
	}
		if(naoyanshi!=0)  //�ж���ʱʱ���Ƿ񵽴�
		{
			if(naojishu==0)  //�������ʱ�䵽
			{
				naojishu=133;  //��ֵ���ʱ��
				ma=!ma;        //LED��ת
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
				if(nzhong==0)  //������ӵ���û������
				{
				szhong=1;  //ʱ�ӵ�����־
				swei++;   ///�������˸����λ��һ
			if(swei==4)  ///
			{
				writetime();  //ʱ��ֻ��123λ����0����������
				swei=0;   //
				szhong=0;  //���ʱ�ӵ�����־λ
			}
		   }
			break;
			case 6:
				if(szhong==0)///ʱ�ӵ���δ������
				{
					moshi=3;  //���ӵ���Ϊģʽ��
				nzhong=1;   //
				if(moshi) //
				swei++;   //
			if(swei==4) //
			{
				nzhong=0;   //
				swei=0; //
				moshi=1;   //�������к�ʱ�ӵ���ʱģʽ1
			}
		   }
				break;
			case 5:
				if(swei!=0)   //
				{
					if(szhong)//���ڵ���ʱ��
					{
						time[swei+3]++; //��Ӧλ��һ
						if(swei==1)
						{
							if(time[swei+3]==24) //Сʱ�߽�ֵ
								time[swei+3]=0;
						}
						else
						{
							if(time[swei+3]==60)   //����߽�ֵ
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
		shanjishu--;    //������˸�������
	}
	if(naoyanshi!=0)
		naoyanshi--;    //����LED��˸ʱ�����
	if(naojishu!=0)
		naojishu--;   //LED��˸�������
	if(moshi==1)
	{
		shuma[0]=time[4]/10;   //ģʽһ��ʾ
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
		shuma[0]=10;       //�¶���ʾ��ģʽ��
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
		shuma[0]=ntime[0]/10;    //ģʽ��������������ʾ
		shuma[1]=ntime[0]%10;
		shuma[2]=11;
		shuma[3]=ntime[1]/10;
		shuma[4]=ntime[1]%10;
		shuma[5]=11;
		shuma[6]=ntime[2]/10;
		shuma[7]=ntime[2]%10;
	}
	shanshuo();   //������˸����
	naozhong();    //������Ӧ����
	shumaxianshi();   //�������ʾ����
}
uint readtem()
{
	uchar teh,tel;
	uint a;
	Init_DS18B20();
//	Write_DS18B20(0xcc);   //����ROM
//	Write_DS18b20(0X4E);
//	Write_DS18B20(0x00);   //
//	Write_DS18B20(0x00);
//	Write_DS18B20(0x1f);
	Init_DS18B20();
	Write_DS18B20(0xcc);   //����ROM
	Write_DS18B20(0x44);   //�����¶�ת��
//	delay(750);
	delay(100);//
	Init_DS18B20();
	Write_DS18B20(0xcc);   //
	Write_DS18B20(0xBE);   //��ȡ�Ĵ���
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
//	uchar i,a,d=0x80;    //��ַ��0x80��ʼ
//	Ds1302_Single_Byte_Write(0x8e,0);  // ȥ��д����
//	for (i=0;i<7;i++)
//	{
//		a=time[6-i]/10;   //������תΪBCD��
//		a<<=4;
////		a*=16;
//		a+=time[6-i]%10;    //
//		Ds1302_Single_Byte_Write(d,a);   //д����
//		d+=2;     //��ַ�Ӷ�
//	}
//	Ds1302_Single_Byte_Write(0x8e,0x80); //����д����
//}
//void readtime()   //ʱ���ȡ
//{
//	uchar i,a,d=0x81;
//	Ds1302_Single_Byte_Write(0x8e,0);
//	for (i=0;i<7;i++)
//	{
////		EA=0;//////!!!!!!!!!!!!!!�����ݼ��жϽ�ֹ����������żȻ����
//		a=Ds1302_Single_Byte_Read(d);
//		EA=1;
//		SDA_R=0;	////////!!!!!!!ÿ�ζ�ȡһ���ֽ�Ҫ��IO�����ͻ�����ʱ
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
	EA=0;///���ж�
	P2&=0x1f;    //�ر�ͨ��
		P0=x;     //д������
	_nop_();
	_nop_();
	_nop_();
	P2=P2&0x1f|d;   //ѡ��ͨ��
	_nop_();
	_nop_();
	_nop_();
	P2&=0x1f;    //�ر�ͨ��
	EA=1;
	return;
}
void shumaxianshi()   
{
	uchar a=0x01;
	a<<=com-1;
	hc138(7,0xff);
	hc138(6,a);    //ѡ��Ҫ����λ
	a=shuma[com-1];   //Ҫ��ʾ������
	hc138(7,duanma[a]);   //���ַ�д��
	com++;         //��ʾλ��һ
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
		  if(szhong==0&&nzhong==0)  //�����������ʾ
		{
			moshi=2;    //key3Ϊ�͵�ƽʱΪģʽ��
			return 0xfe;
		}
		else
			while(key3==0);  //������������
			return 4;
		}
	}
	if(moshi==2)
	{
		if(key3==1)   //Ϊ�ߵ�ƽ�ⷵ��ģʽһ
			moshi=1;
	}
	return 0xff;    //
}