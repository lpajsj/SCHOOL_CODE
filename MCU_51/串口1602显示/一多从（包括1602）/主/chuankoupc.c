//P0口是灯，外部中断开关
#include <reg51.h>
#include <stdio.h>
#include <intrins.h>
#include <absacc.h>
#include "ange.h"
#include "duofa.h"
#include "anjian.h"
#include "lcd1602.h"
//uchar code b[]={0xfd,0x60,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7,0xef,0x00};
//uchar shuju[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b};
uchar fasong[17]={"3311224455"};
uchar dingshijishu=255;
extern bit zhixing,yunxing;//发送或接收是否重新开始执行
extern uchar jieshoujishu;
extern bit dizhifuhe,yindaof;
extern bit duofas,yifa,duoshou,yishou;
extern uchar duofadizhi;
extern uchar moshi;
extern ucode caidan[4][17],tishi[17];
extern uchar crcshuzu[17];
extern uchar crcjia;
extern uchar yindaojishu;
uchar fasonggeshu;
uchar crcshengcheng(uchar x);
void main()
{
	uchar i;
	TMOD=0x01;
	IE=0x82;
	TH0=0xdb;//中断重新装如初值
  TL0=0xf0;
	PS=1;
	TR0=1;
	duofachushihua();
	chushihua();
	lcdbei=1;
	delay(10);
	moshi=1;diyihang(caidan[moshi-1],0,16);dierhang(tishi,0,16);
				xiemingling(0xcd);
				xieshuju(duofadizhi/128+0x30);
				xieshuju(duofadizhi%128+0x30);
				xieshuju('H');
		while(1)
	{
ajpd();
		if(yunxing)
		{
		if(duofas==1)
		{
			if(zhixing)
			{
				duofachushihua();
				xuanzedizhi(duofadizhi);
				xiemingling(0x80);
				xieshuju(duofadizhi+0x30);
				zhixing=0;
				yindaojishu=0;
				i=0;
			}
			if(yindaof)
			{
			if(dingshijishu==0)
			{
				crcjia=fasong[i]-0x30;///////////////
				crcjia=crcshengcheng(crcjia);///////////////
				crcshuzu[i]=crcjia%8+0x30;////////////
				SBUF=crcjia;////////
				xieshuju(fasong[i]);
				if(i==0)
				{
					fasonggeshu=fasong[i]-0x30;
				}
				if(i==16||i==fasonggeshu)
				{
					dierhang(crcshuzu,0,i+1);
					duofas=0;
					yunxing=0;
					yindaof=0;
				}
				i++;
				while(TI==0);
		     TI=0;
				dingshijishu=255;
				TR0=1;
			}
		}
			else 
			{
				yindao();
			}
		}
		else if(yifa==1)
		{
			if(zhixing)
			{
				yifachushihua();
				xiemingling(0x80);
				zhixing=0;
				i=0;
				yindaojishu=0;
			}
			if(yindaof)
			{
			if(dingshijishu==0)
			{
				SBUF=fasong[i];
				xieshuju(fasong[i]);
				if(i==0)
				{
					fasonggeshu=fasong[i]-0x30;
				}
				if(i==16||i==fasonggeshu)
				{
					yifa=0;
					yunxing=0;
					yindaof=0;
				}
				i++;
				while(TI==0);
		     TI=0;
				dingshijishu=255;
				TR0=1;
			}
		}
			else
			{
				yindao();
			}
		}
		else if(duoshou==1)
		{
			if(zhixing)
			{
				duofachushihua();
				zhixing=0;
				yindaojishu=0;
				i=0;
			}
		}
		else if(yishou==1)
		{
			if(zhixing)
			{
				yifachushihua();
				zhixing=0;
				yindaojishu=0;
				i=0;
				jieshoujishu=0;
			}
		}
	}
	}
}
void T0ms() interrupt 1 using 2
{
		 TH0=0xdb;//中断重新装如初值
     TL0=0xf0;
	   if(dingshijishu>0)
			 dingshijishu--;
		 else
			 TR0=0;
}
uchar crcshengcheng(uchar x)
{
	uchar i,a,b=0x0b,y;
	y=x;
	x<<=4;
	a=x/32;
	x<<=3;
	for (i=0;i<4;i++)
	{
		if(a&0x04)
		{
		a<<=1;
		if(x&0x80)
		a|=0x01;
		a=a^b;
		a%=8;
		}
		else
		{
			a<<=1;
			if(x&0x80)
		a|=0x01;
			a%=8;
		}
		x<<=1;
	}
		y<<=3;
		y|=a;
	return y;
}