#include "ange.h"
#include <reg51.h>
#include "duofa.h"
#include "lcd1602.h"
extern uchar huiying=0,yingda=0;
uchar jieshoushuzu[17]="                 ",jieshoujishu=0,jieshougeshu;
extern bit zhixing,yunxing;
bit dizhifuhe=0;bit yindaof=0,yindaos=0;
uchar yindaojishu=0;
ucode yindaoshuzu[6]={5,0,9,3,2,7};
bit duofas=0,yifa=0,duoshou=0,yishou=0;
uchar crcjia;
uchar crcjianyan(uchar x);
uchar crcshuzu[17];
void yindao()
{
	SBUF=yindaoshuzu[yindaojishu];
	while(TI==0);
	TI=0;
	if(yindaojishu==5)
	{
		yindaof=1;
		return;
	}
	yindaojishu++;
	return;
}
void yindaoyanzheng()
{
	if(yindaoshuzu[yindaojishu]==SBUF)
	{
		if(yindaojishu==5)
		{
			yindaos=1;
			return;
		}
		yindaojishu++;
	}
	else
	{
		yindaojishu=0;
	}
}
void duofachushihua()
{
	PCON=0x00;  //smod=0 th1=fd 9600kbit
	TMOD=0x20; //
	TH1=0xfd;   //
	TL1=0xfd;//
	TR1=1;
	SCON=0xf0; //方式三  sm0 sm1 sm2接收方式 ren(是否接收)//c0不接收 f0条件接收;
	return;
}
void yifachushihua()
{
	PCON=0x00;  //smod=0 th1=fd 9600kbit
	TMOD=0x20; //
	TH1=0xfd;   //
	TL1=0xfd;//
	TR1=1;
	SCON=0x50; //方式yi  sm0 sm1 sm2接收方式 ren(是否接收)//40不接收，50接收
	return;
}
void xuanzedizhi(uchar a)
{
		TB8=1;
		SBUF=a+0x30;
		while(TI==0);
		TI=0;
	  TB8=0;
	  return;
}
void chuankou() interrupt 4
{
	if (RI)
	{
		RI=0;
		if(duoshou)
		{
			if(dizhifuhe)
			{
				if(yindaos)
				{
					crcjia=SBUF;//////////
				jieshoushuzu[jieshoujishu]=crcjia/8+0x30;//////////////
					xieshuju(jieshoushuzu[jieshoujishu]);/////////////
					crcjia=crcjianyan(crcjia);/////////////////
					crcshuzu[jieshoujishu]=crcjia+0x30;///////////////
				if(jieshoujishu==1)
				jieshougeshu=jieshoushuzu[jieshoujishu]+2-0x30;
				jieshoujishu++;
				if((jieshougeshu)==jieshoujishu)
				{
					dierhangxin(crcshuzu,0,jieshoujishu);
					yunxing=0;
					ES=0;
					SM2=1;
					dizhifuhe=0;
					yindaos=0;
				}
	    }
				else
				{
					yindaoyanzheng();
				}
		}
			else
			{
				if(SBUF==benjidizhi+0x30)
				{
					jieshoujishu=0;
					dizhifuhe=1;
					SM2=0;
					xiemingling(0x80);
					jieshoushuzu[jieshoujishu]=benjidizhi+0x30;
					xieshuju(jieshoushuzu[jieshoujishu]);
					jieshoujishu++;
				}
			}
	  }
		else if(yishou)
		{
			if(yindaos)
			{
				jieshoushuzu[jieshoujishu]=SBUF;
				if(jieshoujishu==0)
				jieshougeshu=jieshoushuzu[jieshoujishu]+1-0x30;
				xieshuju(jieshoushuzu[jieshoujishu]);
				jieshoujishu++;
				if(jieshougeshu==jieshoujishu)
				{
					yunxing=0;
					ES=0;
					jieshoujishu=0;
				}
		}
			else
			{
				yindaoyanzheng();
				xiemingling(0x80);
				jieshoujishu=0;
			}
	  }
		}
	return;
}
uchar crcjianyan(uchar x)
{
	uchar i,a,b=0x0b;
	x<<=1;
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
return a;
}