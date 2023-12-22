#include <reg51.h>
#include "ange.h"
#include "15a.h"
uint hongwaiyindao=0x6666,hongwaima=0x6666;  ///分别代表红外的引导码和真正码值
extern uchar shuma[];
uchar dingshijishu=500;    
uchar hongjieb=0xff,shujujishu=0;  ///hongjieb代表接收进度，shujujishu代表接收的数据进行到哪一位
void main()
{
	uchar a,x;
	IE=0x82;//开T0和外部中断0
	TMOD=0x11;//T0T1模式1，T0显示，T1计时用
	IT0=1;//
	TH0=0xfa;
	TL0=0x24;//T0每次中断1500US
	PX0=1; ///////外部中断高优先级
	initial15();  //蓝桥杯板子初始化，关各种器件
	TR0=1;   //启动T0
	while(1)
	{
		x=dulianjian(); //按键判断
		if(x==0)
		{
			EX0=1;
			hongjieb=0;    //按键0，开外部，从第一步接收红外
			hc138(4,0);  //灯亮
		}
		else if(x==1)
		{
			EX0=0;   ///关中断灯灭
			hc138(4,0xff);
		}
		if(hongjieb==3)  //接收完毕刷新显示
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
			hc138(4,0xff);//刷新之后关中断，灭灯
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
	shumaxianshi(shuma);  //数码管显示
}
void x0() interrupt 0
{
	uint a;
	if(hongjieb==0)
	{
	  TH0=0xfa;
	  TL0=0x24;
		TF0=0;
		dingshijishu=8; //等待略过引导码9+4.5ms，大于8*1.5ms
		shujujishu=0;
		hongjieb++;   //下次第二步操作
	}
	else  if(hongjieb==1)
	{
		if(dingshijishu==0)
		{
			hongjieb++;//下次第三步操作
			TH1=0x00;  //T1从0开始计数
			TL1=0x00;
			TR1=1;///
		}
		else
			hongjieb=0;
	}
	else if(hongjieb==2) //第三步接收数据
	{	
		a=TH1*256+TL1;
		if(a>1680&&a<2800)//判断是0还是1
		{
			if(shujujishu<16)//前16位
			{
				hongwaiyindao<<=1;
				hongwaiyindao|=0x01;
				shujujishu++;  //每次读数据后，计数变量加一
			}
			else if(shujujishu>=16&&shujujishu<32)//后16位
			{
				hongwaima<<=1;
				hongwaima|=0x01;
				shujujishu++;
			}
			TH1=0x00;
			TL1=0x00;//T1重新计时
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
		 shujujishu=0;  //时间不对重新接收
		 TR1=0;
	 }
	}
	if(shujujishu==32)
	{
		hongjieb=3;//数据接收完毕，
		shujujishu=0;
		TR1=0;
	}
}