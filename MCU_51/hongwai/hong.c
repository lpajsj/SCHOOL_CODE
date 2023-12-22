#include <reg51.h>
#include "ange.h"
#include "15a.h"
uint hongwaiyindao=0x6666,hongwaima=0x6666;  ///�ֱ���������������������ֵ
extern uchar shuma[];
uchar dingshijishu=500;    
uchar hongjieb=0xff,shujujishu=0;  ///hongjieb������ս��ȣ�shujujishu������յ����ݽ��е���һλ
void main()
{
	uchar a,x;
	IE=0x82;//��T0���ⲿ�ж�0
	TMOD=0x11;//T0T1ģʽ1��T0��ʾ��T1��ʱ��
	IT0=1;//
	TH0=0xfa;
	TL0=0x24;//T0ÿ���ж�1500US
	PX0=1; ///////�ⲿ�жϸ����ȼ�
	initial15();  //���ű����ӳ�ʼ�����ظ�������
	TR0=1;   //����T0
	while(1)
	{
		x=dulianjian(); //�����ж�
		if(x==0)
		{
			EX0=1;
			hongjieb=0;    //����0�����ⲿ���ӵ�һ�����պ���
			hc138(4,0);  //����
		}
		else if(x==1)
		{
			EX0=0;   ///���жϵ���
			hc138(4,0xff);
		}
		if(hongjieb==3)  //�������ˢ����ʾ
		{
			a=hongwaiyindao/256;
			shuma[0]=a/16;
			shuma[1]=a%16;
			a=hongwaiyindao%256;
			shuma[2]=a/16;
			shuma[3]=a%16;
			a=hongwaima/256;
			shuma[4]=a/16;
			shuma[5]=a%16;
			a=hongwaima%256;
			shuma[6]=a/16;
			shuma[7]=a%16;
			hongjieb=0xff;
			hc138(4,0xff);//ˢ��֮����жϣ����
			EX0=0;
		}
	}
}
void t0() interrupt 1
{
	TH0=0xfa;
	TL0=0x24;
	if(dingshijishu!=0)
	{
		dingshijishu--;
	}
	shumaxianshi(shuma);  //�������ʾ
}
void x0() interrupt 0
{
	uint a;
	if(hongjieb==0)
	{
	  TH0=0xfa;
	  TL0=0x24;
		TF0=0;
		dingshijishu=8; //�ȴ��Թ�������9+4.5ms������8*1.5ms
		shujujishu=0;
		hongjieb++;   //�´εڶ�������
	}
	else  if(hongjieb==1)
	{
		if(dingshijishu==0)
		{
			hongjieb++;//�´ε���������
			TH1=0x00;  //T1��0��ʼ����
			TL1=0x00;
			TR1=1;///
		}
		else
			hongjieb=0;
	}
	else if(hongjieb==2) //��������������
	{	
		a=TH1*256+TL1;
		if(a>1680&&a<2800)//�ж���0����1
		{
			if(shujujishu<16)//ǰ16λ
			{
				hongwaiyindao<<=1;
				hongwaiyindao|=0x01;
				shujujishu++;  //ÿ�ζ����ݺ󣬼���������һ
			}
			else if(shujujishu>=16&&shujujishu<32)//��16λ
			{
				hongwaima<<=1;
				hongwaima|=0x01;
				shujujishu++;
			}
			TH1=0x00;
			TL1=0x00;//T1���¼�ʱ
		}
    else if(a<=1680&&a>280)	
   {
			if(shujujishu<16)
			{
				hongwaiyindao<<=1;
				shujujishu++;
			}
			else if(shujujishu>=16&&shujujishu<32)
			{
				hongwaima<<=1;
				shujujishu++;
			}
			TH1=0x00;
			TL1=0x00;
   }	
	 else
	 {
		 hongjieb=0;
		 shujujishu=0;  //ʱ�䲻�����½���
		 TR1=0;
	 }
	}
	if(shujujishu==32)
	{
		hongjieb=3;//���ݽ�����ϣ�
		shujujishu=0;
		TR1=0;
	}
}