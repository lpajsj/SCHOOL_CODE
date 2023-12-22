#include <STC15F2K60S2.H>
#include <absacc.h>
#include <intrins.h>
#include "guoshi15.h"
#include "onewire.h"
#include <stdio.h>
extern uchar shuma[];   
void Delay12us();  //��������ʱ
void xianshi(); //��ʾ����
uint chaosheng();  //������
uint juli,julic=35,julicc,chaoshengjishu,biangeng; //���� ������� ��������ݴ� �������� �������
uchar sc=1,shujuj=1;canshuj=1;  //���ݲ��������ж� ���ݽ��� ��������
uint wendu,wenduc=30,wenducc,wendujishu=100; //�¶� �¶Ȳ��� �¶Ȳ����ݴ� �¶ȼ���
void anjianchuli(uchar x); //����������
extern uint cajs; //������������
bit dab=0;  //da��־λ
void led(); //LEDָʾ
ucode chashu[]={"ST\r\n"};  // ��ѯ����
ucode chacan[]={"PARA\r\n"};  // ��ѯ����
ucode cuowu[]={"ERROR\r\n"};  // ���ʹ���
uchar fashu[]={"$20,20.24\r\n"};//1 2  45 78����
uchar facan[]={"#35,30\r\n"}; //12 45����
uchar cjjishu=0,cjmoshi=0;  //���ڽ��ռ��� �жϷ��ͺ�������
bit cfb1=0,cfb2=0,cfb3=0;
void UartInit(void);
void ckchuli();
char putchar(char ch)
{
	SBUF=ch;
	while(TI==0);
	TI=0;
	return ch;
}
void UartInit(void)		//4800bps@12.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR &= 0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
	T2L = 0xCC;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
}
void ckchuli()
{
	float h=3.21;
	uchar *x=cuowu;
	uchar i=0;
	sprintf(fashu,"$%d,%d.%d\r\n",juli,wendu/100,wendu%100);
//	fashu[1]=juli/10+0x30;
//	fashu[2]=juli%10+0x30;
//	fashu[4]=wendu/1000%10+0x30;
//	fashu[5]=wendu/100%10+0x30;
//	fashu[7]=wendu/10%10+0x30;
//	fashu[8]=wendu%10+0x30;
	sprintf(facan,"#%d,%d\r\n",julic,wenduc);
//	facan[1]=julic/10+0x30;
//	facan[2]=julic%10+0x30;
//	facan[4]=wenduc/10+0x30;
//	facan[5]=wenduc%10+0x30;  //���ʹ������鸳ֵ
	if(cfb1==1)      ///���ڷ��ͱ�־
	{
		cfb1=0;  //���ձ�־��ֵ0
			for(i=0;i<=10;i++)
		{
			SBUF=fashu[i]; //��һ�ַ�������
			while(TI==0);
				TI=0;
		}
	}
	
		else if(cfb2==1)
		{
			cfb2=0;
//			printf("%06.1f\r\n",h);
//			printf("#%06d,%d%s\r\n",julic,wenduc,cuowu);
			for(i=0;i<=7;i++)
		{
			SBUF=facan[i];  //�ڶ��ַ��Ͳ���
			while(TI==0);
				TI=0;
		}
	  }
	else if(cfb3==1)
		{
			cfb3=0;
			for(i=0;i<=6;i++)
		{
			SBUF=*x;
			while(TI==0);  //�����ַ��ʹ���
				TI=0;
			x++;
		}
	  }
}
void chuan() interrupt 4 
{
	if(RI==1)
	{
		RI=0;   //����жϱ�־λ
		if(SBUF!='\r'&&SBUF!='\n') //����\r\n
		{
		if(cjjishu==0)
		{
				if(SBUF==chashu[cjjishu])
				{
					cjmoshi=1;
					cjjishu++;
				}
			else	if(SBUF==chacan[cjjishu]) //
				{
					cjmoshi=2;
					cjjishu++;
				}
				else
				{
					cjmoshi=3;
					cfb3=1;
					cjjishu=0;
				}
			}
		else if(cjmoshi==1)
		{
				if(SBUF==chashu[cjjishu])
				{
					cjjishu++;
					if(cjjishu==2)   //\r\n��4û����2
					{
						cfb1=1;
						cjjishu=0;
					}
				}
				else
				{
					cjmoshi=3;
					cfb3=1;
					cjjishu=0;
				}
		}
		else if(cjmoshi==2)
		{
				if(SBUF==chacan[cjjishu])
				{
					cjjishu++;
					if(cjjishu==4) //\r\n��6û����4
					{
						cfb2=1;
						cjjishu=0;
					}
				}
				else
				{
					cjmoshi=3;
					cfb3=1;
					cjjishu=0;
				}
		}
	}
    }
}
void main()
{
	uchar x;
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x30;		//���ö�ʱ��ֵ
	TH0 = 0xF8;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0=1;
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	Init_DS18B20();
	Write_DS18B20(0xcc);  //����ROM
	Write_DS18B20(0x4e);   //д�Ĵ���
	Write_DS18B20(0x00);   //TH
	Write_DS18B20(0x00);    //TL
	Write_DS18B20(0x5f);  //�����ֱ��� 1f 3f 5f 7f
	wendu=retem();  //�¶ȶ�ȡ
	delay(300);
	wendu=retem();  //�¶ȶ�ȡ
	hc138(4,0xff); //�ر������
	hc138(5,0); //�رշ�����
	EA=1;
	PS=1;
	ES=1;
//	x=at24r(0);
//  y=at24r(1);
//	biangeng=256*x+y;
	biangeng=at24r(0)*256+at24r(1); //��ȡEEPROM �������ֵ
	UartInit();
	while(1)
	{
		x=anjiangai2();  //��ȡ����ֵ
		anjianchuli(x);  //��������
		if(wendujishu==0)
		{
			wendujishu=220;  //�¶ȼ�����һ��ʱ���ȡ
	    wendu=retem();  //��ȡ�¶�
		}
		if(chaoshengjishu==0)
		{
			chaoshengjishu=450;  //����������
		  juli=chaosheng();  //��ȡ����
		}
		if(dab)   //da��־λ
		{
			if(juli<=julic)  //���ݲ���ֵ�����ͬ��ѹ
			dapcf(100);
			else
			dapcf(200);
		}
		else
		{
			dapcf(20); //�ر�daʱ���0.4
		}
		led();  //LEDָʾ����
		ckchuli();  //���ڷ���
	}
}
void t0() interrupt 1
{
	TL0 = 0x30;		//���ö�ʱ��ֵ
	TH0 = 0xF8;		//���ö�ʱ��ֵ
xianshi();  //�������ʾ
	if(chaoshengjishu!=0) 
	{
		chaoshengjishu--;  //
	}
	if(cajs!=0)
	{
		cajs--;
	}
	if(wendujishu!=0)
	{
		wendujishu--;
	}
}
void anjianchuli(uchar x)
{
	if(x==13)
	{
		switch(sc)  //�л�����������ҳ��
		{
			case 1:sc=2;
			julicc=julic; //���������¶Ȳ���
			wenducc=wenduc;
			break;
			case 2:sc=1;
			if(wenduc!=wenducc||julicc!=julic)  //��������ı�������һ
			{
				biangeng++;
				at24w(0,biangeng/256); ///д����Ҫ�ȴ�
				delay(10);
				at24w(1,biangeng%256);
			}
			break;
		}
		shujuj=1;
		canshuj=1;  //��ʾ��һ��ҳ��
	}
	if(x==12)     //������ǰ�����ҳ��
	{
		switch(sc)
		{
			case 1:
				switch(shujuj)
				{
					case 1:shujuj=2;break;
					case 2:shujuj=3;break;
					case 3:shujuj=1;break;
				}
				break;
			case 2:
				canshuj++;
				if(canshuj==3)
					canshuj=1;
				break;
		}
	}
	if(x==16)  
	{
	if(sc==2)
	{
		if(canshuj==1)
		{
			if(wenduc>=2)
				wenduc-=2;
		}
		if(canshuj==2)
		{
			if(julic>=5)
				julic-=5;
		}
	}
  }
	if(x==17)
	{
	if(sc==2)
	{
		if(canshuj==1)
		{
			if(wenduc<=97)
				wenduc+=2;
		}
		if(canshuj==2)
		{
			if(julic<=94)
				julic+=5;
		}
	}
  }
	if(x==120) //����12����������
	{
		biangeng=0;
		at24w(0,0);
		delay(10);
		at24w(1,0);
	}
	if(x==130)
	{
		dab=!dab;
	}
}
void led()
{
	uchar x=0xff;  //xΪ����д�������
	if(wendu/100>wenduc)
		x&=~0x01;
	if(juli<julic) //���������ı�x��ֵ
		x&=~0x02;
	if(dab)
		x&=~0x04;
	hc138(4,x);
}
void xianshi()
{
	if(sc==1)
	{
		if(shujuj==1)
		{
			shuma[0]=11;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=10;
			shuma[4]=wendu/1000;
			shuma[5]=wendu/100%10;
			shuma[6]=wendu/10%10;
			shuma[7]=wendu%10;
		}
		if(shujuj==2)
		{
			shuma[0]=12;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=10;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=juli/10%10;
			shuma[7]=juli%10;
		}
		if(shujuj==3)
		{
			shuma[0]=13;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=10;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=10;
			shuma[7]=10;
			if(biangeng>10000)
			shuma[3]=biangeng/10000; //�����ж����� ��ֵǰ��Ϩ��
			if(biangeng>1000)
			shuma[4]=biangeng/1000%10;
			if(biangeng>100)
			shuma[5]=biangeng/100%10;
			if(biangeng>10)
			shuma[6]=biangeng/10%10;
			shuma[7]=biangeng%10;
		}
	}
	else if(sc==2)
	{
		if(canshuj==1)
		{
			shuma[0]=14;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=1;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=wenduc/10%10;
			shuma[7]=wenduc%10;
		}
		if(canshuj==2)
		{
			shuma[0]=14;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=2;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=julic/10%10;
			shuma[7]=julic%10;
		}
	}
	shumaxianshi();
}
uint chaosheng()
{
	uchar x=8     ;  //�˸����ڷ���
	uint t=0,s;
	TR1=0;
	TH1=0;
	TL1=0;
//	EA=0;  //���ر��жϸо�û��̫��Ӱ��
	while(x--)
	{
		chaofa=1;
		Delay12us();  //һ����12us
		chaofa=0;
		Delay12us();
	}
	TR1=1;      //������ʱ��
	while(chaoshou==1&&t<6000)  //6000����Ϊ1ms����34cm 100cm�Ļ����Ǵ�Լ3ms���ؾ���6ms �ȴ�ʱ���ն�Ϊ1
	{
		t=TH1*256+TL1;  
	}
	TR1=0;
	EA=1;    //���ж�
	s=t*0.017;  //1ms���34cm һ΢�����0.034cm  t/2*0.034

	if(s>99)  //Ҫ�����ж�ֵ����99��ʾ99
		s=99;
	return s;
}
void Delay12us()		
{
	unsigned char i;
	_nop_();
	_nop_();
	_nop_();
	i = 30;
	while (--i);
}
//void Delay12us()		//@12.000MHz
//{
//	unsigned char i;

//	_nop_();
//	_nop_();
//	i = 33;
//	while (--i);
//}
//void Delay12us()		//@12.000MHz
//{
//	unsigned char i;

//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	i = 33;
//	while (--i);
//}
