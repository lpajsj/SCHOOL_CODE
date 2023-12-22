#include <reg51.h>
#include <intrins.h>
#include "dijiu15.h"
#include "iic.h"
uchar bianhao=1,moshi=1,lx=1,dengji;//bainhao�Ǹ������Ĳ�ͬ��ʽ��moshi��ʾ�������ʾ��ʽ��lx��ʾLED�����ڼ��Σ��ȼ���LED���ȵȼ�
uint shanshuojishu,liujianjishu,liujian=400;//������������������LED��ת���ʱ��
bit smmab=0,lxb=1;  //����������־����LED��ת��־λ
void led();  //LED��ˮ�ƺ���
bit ledb=0;  //��ˮ�Ʊ�־λ
void anjianchuli(); //����������
void xianshi();  //�������ʾ����
extern uchar shuma[]; //���������
uint adzhi=1;  //adֵ��LED�������������pwm��
void liangdu(); //�������ȵȼ�����pwm�ߵ�ƽʱ��
bit dengjib;  //�ȼ���־λ�����Ƿ���ʾ���ȵȼ�
uint qianzhou,houzhou,zongzhou=2000; //����pwm�ĸ������
bit zhoub;  //pwm�ߵͲ���
void zhankong();  //���pwm
void main()
{
	uchar x;
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x24;		//���ö�ʱ��ֵ
	TH0 = 0xFA;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	EA=1;
	ET0=1;
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0xA4;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1=1;
	hc138(4,0xff); ////�ر�LED
	hc138(5,0);  ///�رշ�����
	hc138(7,0xff); ///����ܹر�
	liujian=at24r(0)*10;  //�����ʱ���ȡ
	if(liujian%100!=0||liujian<400||liujian>1200)
	{
		liujian=400;
	at24w(0,40);
	}
	adinit(1);  ///ADC��ʼ��
	while(1)
	{
//			adinit(1);  ///ADC��ʼ��
		adzhi=adpcf(); //��ȡadֵ ||||||||||����һֱ��
		if(adzhi<=125/2)  ///����adֵ�ж����ȵȼ�
		{
			dengji=1;
		}
		else if(adzhi>125/2&&adzhi<=250/2)
			dengji=2;
		else if(adzhi>250/2&&adzhi<=475/2)
			dengji=3;
		else if(adzhi>475/2)
			dengji=4;	
		x=anjian();  //�����ж�
		anjianchuli(); //�����������
		if(ledb)
		{
			liangdu();  /////�����ж�ʱ�䣬����LED����
			if(lxb)    //
			{
				lxb=0; //�����ת��־λ
				liujianjishu=liujian*10/15;  //led��ת�����ֵ
				lx++;
			 if(bianhao==1||bianhao==2)  ///���ݱ�ţ�ѡ��LED�����ڼ���
		     if(lx==9)
			     lx=1;
			 if(bianhao==3||bianhao==4) //��ʽ3��4ֻ�� 4��
				 if(lx==5)
					lx=1;
			}
		}
		else
			hc138(4,0xff); // ���LED��־λδ����Ϩ��LED
	}
}
void t1() interrupt 3
{
	zhankong();  //��ʱ��1����pwm
}
//////liangdu
void liangdu()
{
	switch(dengji)   //����pwm�ĸߵ�ƽʱ��
	{
		case 1:
			qianzhou=10;
		break;
		case 2:
			qianzhou=100;
		break;
		case 3:
			qianzhou=1000;
		break;
		case 4:
			qianzhou=1500;
		break;
	}
}
///////
void zhankong()  //���pwm
{
	uint x;
	zhoub=!zhoub;  //�ߵ͵�ƽ��־λ
	houzhou=zongzhou-qianzhou;  //�͵�ƽ����
	if(zhoub)
	{
		x=65535-qianzhou;  //��־λΪһ������Ӧ�ߵ�ƽʱ��д��
	}
	else
	{
		x=65535-houzhou; //�͵�ƽ
	}
	if(ledb)
	{
			if(zhoub)  //��־λΪһ��LED��
			led();
			else   //����LEDϨ��
			hc138(4,0xff); //
		}
		TH1=x/256;
		TL1=x%256;
}
//��ʾ
void xianshi()   ///�������ʾ
{
	if(moshi==1)
	{
		shuma[0]=10;
		shuma[1]=10;
		shuma[2]=10;
		shuma[3]=10;
		shuma[4]=10;
		shuma[5]=10;
		shuma[6]=10;
		shuma[7]=10;
		if(dengjib)
		{
		shuma[6]=11;
		shuma[7]=dengji;  //��ʾ�ȼ�
		}
	}
//			shuma[0]=
//		shuma[1]=
//		shuma[2]=
//		shuma[3]=
//		shuma[4]=
//		shuma[5]=
//		shuma[6]=
//		shuma[7]=
	if(moshi==2||moshi==3)  //����ʱ��
	{
		shuma[0]=11;
		shuma[1]=bianhao;
		shuma[2]=11;
		shuma[3]=10;
		shuma[4]=liujian/1000;
		if(shuma[4]==0)
			shuma[4]=10;
		shuma[5]=liujian/100%10;
		shuma[6]=liujian/10%10;
		shuma[7]=liujian%10;
		if(shanshuojishu==0)
		{
			smmab=!smmab;
			shanshuojishu=533;
		}
	}
	if(moshi==2)  //ģʽ2����LED��ţ�����ܸ���smmab��������
	{
		if(smmab==0)
		{
		shuma[0]=10;
		shuma[1]=10;
		shuma[2]=10;
		}
	}
	if(moshi==3)  //�������ʱ��
	{
		if(smmab==0)
		{
			shuma[4]=10;
		shuma[5]=10;
		shuma[6]=10;
		shuma[7]=10;
		}
	}
//	shuma[0]=adzhi/100;
//	shuma[1]=adzhi/10%10;
//	shuma[2]=adzhi%10;
	shumaxianshi();
}
/////////��������
void anjianchuli(uchar x)
{
		if(x==7)  //led����
		{
		ledb=!ledb;
		lx=1;
		lxb=0;
		liujianjishu=liujian*10/15;  //led��ת�����ֵ
		}
		if(x==6) //�����л���ģʽ2������ţ�3�������
		{
			switch(moshi)
			{
				case 3:moshi=1;
				break;
				case 1:moshi=2;
				break;
				case 2:moshi=3;
				break;
			}
		}
		if(x==5)  
		{
			if(moshi==2)
			{
				lx=1;
				bianhao++;
				if(bianhao==5)
					bianhao=1;
			}
			if(moshi==3)
			{
				if(liujian==1200)
					liujian=400;
				else
					liujian+=100;
				at24w(0,liujian/10);
			}
		}
		if(x==4)
		{
			if(moshi==2)
			{
				lx=1;
				if(bianhao==1)
					bianhao=4;
				else
					bianhao--;
			}
			if(moshi==3)
			{
				if(liujian==400)
					liujian=1200;
				else
					liujian-=100;
				at24w(0,liujian/10);
			}
		}
		return;
}
///////////////�ж�
void t0() interrupt 1
{
	TL0 = 0x24;		//���ö�ʱ��ֵ
	TH0 = 0xFA;		//���ö�ʱ��ֵ
	if(shanshuojishu!=0)
	shanshuojishu--;
	if(liujianjishu!=0) //��ת�������
	{
		liujianjishu--;
	}
	else
		lxb=1;  //��ʾ��ʼ����һ��LED
	xianshi();  //�������ʾ
}
///////////led
void led()  //led��ʾ����
{
	uchar x;
	if(bianhao==1)  //��һ����ʾ��ʽ
	{
		x=0xfe;
		x=_crol_(x,lx-1);
		hc138(4,x);

	}
	if(bianhao==2)  //
	{
		x=0x7f;
		x=_cror_(x,lx-1);
		hc138(4,x);

	}
	if(bianhao==3)
	{
		if(lx==1)
			x=0x7e;
		if(lx==2)
			x=0xbd;
		if(lx==3)
		{
			x=0xdb;
		}
		if(lx==4)
		{
			x=0xe7;
		}
		hc138(4,x);
	}
	if(bianhao==4)
	{
		if(lx==4)
		{
			x=0x7e;
		}
		if(lx==3)
			x=0xbd;
		if(lx==2)
		{
			x=0xdb;
		}
		if(lx==1)
			x=0xe7;
		hc138(4,x);
	}
}