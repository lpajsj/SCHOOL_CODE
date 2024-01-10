#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ucode  unsigned char code
sbit E=P2^2;sbit RW=P2^1;sbit RS=P2^0;  //定义1602端口
sfr shuju=0x80;  //P0口数据传送对应1602的D0-D7
sfr p2=0xa0;
sbit key1=P3^0;sbit key2=P3^1;sbit key3=P3^2;sbit key4=P3^3;sbit key5=P3^4;sbit key6=P3^5;sbit key7=P3^6;sbit duoj=P3^7;
void delay(unsigned int n);
void xiemingling(uchar a);  //1602写入命令
void xieshuju(uchar a);  //1602写入数据
void chamang();     //查忙
void chushihua();  //初始化
uchar dier[16];
void dierhang(uchar *a,uchar x);
void diyihang(uchar a[]);
void delay10us(void);
void ajpd();
void xianshi();
uchar djb=0,djbb=0,jz1,i=0,thh,tll,bujinsu=30,bujindang=1;
uchar bujin[]={0x02,0x06,0x04,0x0c,0x08,0x09,0x01,0x03};
uint thl=0;uchar thljs=0,thlbh=0;
bit xs=0,zfb=1,duojjb=1;
uint duojpt=5000,duojph=500,duojptdang=100,duojjd=0;
uchar duojjddang=1,dingshijishu=0;
uchar ndiv=1;
ucode xiangmu[5][17] = {" stepping motor ",//显示当前波形类型
                       "steering engine ",
	                     "steering engine+",
                       "     trumpet    ",
                       "     switch     "};
void main()
{
	PT0=1;
	TMOD=0x11;
	IE=0x8a;
	thljs=150/bujinsu;
	thlbh=thljs;
	TH0=0xdb;//中断重新装如初值
   TL0=0xf0;
	thl=(unsigned long)7500000/bujinsu%50000;
	if(thljs)
	{
	 TH1=0x3c;//中断重新装如初值
   TL1=0xb0;
	}
	else
	{
	 thh=thl/256;//中断重新装如初值
   tll=thl%256;
	}
	TR1=1;
	chushihua();
	while(1)
	{
	ajpd();
		if(xs)
			xianshi();
	}
}
void xianshi()
{
	uchar dier[17];
	xiemingling(0x01);
	diyihang(&xiangmu[djb-1]);
	if(djb==1)
	{
	if(zfb)
  	dier[0]='+';
	else
		dier[0]='-';
					dier[1]='V';
					dier[2]=':';
					dier[3]=bujinsu/100+0x30;
					dier[4]=bujinsu%100/10+0x30;
					dier[5]=bujinsu%10+0x30;
					dier[6]='/';
					dier[7]='m';
					dier[8]='i';
					dier[9]='n';
					dier[10]=' ';
	dier[11]='+';
	dier[12]='-';
	dier[13]=0;
					dierhang(dier,0);
	switch(bujindang)
        {
        	case 1:	dierhang("1/m",13);
				break;
        	case 5:dierhang("5/m",13);
				break;
       	 	case 10:dierhang("10/m",12);
				break;
				}
			}
	else if(djb==2)
	{
		dier[0]='T';
		dier[1]=':';
					dier[2]=duojpt/10000+0x30;
					dier[3]=duojpt/1000%10+0x30;
					dier[4]=duojpt%1000/100+0x30;
					dier[5]=duojpt%100/10+0x30;
					dier[6]=duojpt%10+0x30;
					dier[7]=' ';
					dier[8]=ndiv+0x30;
					dier[9]='d';
					dier[10]='+';
	dier[11]='-';
	dier[12]=duojptdang/1000+0x30;
	dier[13]=duojptdang/100%10+0x30;
		dier[14]=duojptdang/10%10+0x30;
		dier[15]=duojptdang%10+0x30;
		dier[16]=0;
		dierhang(dier,0);
	}
	else if(djb==3)
	{
		dier[0]='d';
		dier[1]=':';
					dier[2]=duojjd/100+0x30;
					dier[3]=duojjd/10%10+0x30;
					dier[4]=duojjd%10+0x30;
					dier[5]=' ';
					dier[6]=' ';
					dier[7]=' ';
					dier[8]='+';
					dier[9]='-';
		dier[10]=':';
	dier[11]=duojjddang/10+0x30;
	dier[12]=duojjddang%10+0x30;
	dier[13]=0;
		dier[14]=0;
		dier[15]=0;
		dier[16]=0;
		dierhang(dier,0);
	}
				xs=0;
}
void dianji() interrupt  3 using 2
{
	uchar a;
	if(djb==1)
	{
	if(thlbh)
		thlbh--;
	if(thlbh)
	{
		TH1=0x3c;//中断重新装如初值
    TL1=0xb0;
		return;
	}
	else
	{
		if(thljs)
			thlbh=thljs;
		 TH1=thh;//中断重新装如初值
    TL1=tll;
		if(zfb)
		i=i<7 ?i+1:0;
		else
			i=i>0?i-1:7;
		a=bujin[i];
		a<<=4;
		p2=p2&0x0f;
		p2=p2|a;
	}
	return;
}
	else if(djb==2)
	{
		TR1=0;
	duojjb=!duojjb;
	duoj=duojjb;
		if(!duojjb)
		{
			thl=65536-duojpt+duojph;
			TH1=thl/256;
			TL1=thl%256;
			if(zfb)
			{
				duojph=duojph+ndiv*8;
				if(duojph>2400)
				zfb=0;
			}
			else
			{
				duojph=duojph-ndiv*8;
				if(duojph<600)
					zfb=1;
			}
		}
		else
		{
			thl=65536-duojph;
		  TH1=thl/256;
			TL1=thl%256;
		}
		TR1=1;
		return;
	}
else if(djb==3)
{
duojph=500+duojjd*11;
	duojjb=!duojjb;
	duoj=duojjb;
		if(!duojjb)
		{
			thl=45536+duojph;
			TH1=thl/256;
			TL1=thl%256;
		}
		else
		{
			thl=65536-duojph;
		  TH1=thl/256;
			TL1=thl%256;
		}	
		return;
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
void ajpd()
{
	if(key1==0)
	{
		while(key1==0);
		if(TR1==0)
			TR1=1;
				switch(djb)
		   {
					case 0:djb=1;
				 break;
        	case 1:	djb=2;
				 duoj=0;
				 thl=65536-duojpt+duojph;
				 TH1=thl/256;
				 TL1=thl%256;
				 thljs=0;
				 thlbh=0;
				break;
        	case 2:djb=3;
				break;
       	 	case 3:djb=1;
				break;
				}
xs=1;			 
	}
else if(key2==0)
	{
		dingshijishu=100;
		TR0=1;
		delay(10);
		while(key2==0);
		jz1=2;
		xs=1;
		if(dingshijishu)
		{
		if(djb==1)
		{
				switch(bujindang)
		   {
        	case 1:	bujindang=5;
				break;
        	case 5:bujindang=10;
				break;
       	 	case 10:bujindang=1;
				break;
				}	
		}
		else if(djb==2)
		{
				switch(duojptdang)
		   {
        	case 1:	duojptdang=10;
				break;
        	case 10: duojptdang=100;
				break;
       	 	case 100: duojptdang=1000;
				break;
					case 1000: duojptdang=1;
				 break;
				}	
		}
			else if(djb==3)
		{
				switch(duojjddang)
		   {
        	case 1:	duojjddang=10;
				break;
        	case 10: duojjddang=20;
				break;
       	 	case 20: duojjddang=1;
				 break;
				}	
		}
	}
		else
		{
		if(djb==1)
		zfb=~zfb;
		else if(djb==2)
		{
			switch(ndiv)
			{
				case 1:ndiv=2;
					break;
				case 2:ndiv=3;
			break;
				case 3:ndiv=4;
			break;
				case 4:ndiv=5;
			break;
				case 5:ndiv=1;
			break;
			}
		}
		}
}
	
else if(key3==0)
	{
		while(key3==0);
		jz1=3;
if(djb==1&&bujinsu+bujindang<=150)
		{
			bujinsu=bujinsu+bujindang;
	thljs=150/bujinsu;
			thlbh=thljs;
	thl=(unsigned long)7500000/bujinsu%50000;
	if(thljs)
	{
	 TH1=0x3c;//中断重新装如初值
   TL1=0xb0;
	}
	else
	{
	 thh=thl/256;//中断重新装如初值
   tll=thl%256;
	}
		}
else if(djb==2&&duojptdang+duojpt<=50000)
		{
			duojpt=duojptdang+duojpt;
		}
else if(djb==3&&duojjddang+duojjd<=180)
		{
			duojjd=duojjddang+duojjd;
		}
		xs=1;
	}
else if(key4==0)
	{
		dingshijishu=100;
		TR0=1;
		delay(10);
		while(key4==0);
		jz1=4;
		if(dingshijishu)
		{
		if(djb==1&&bujinsu-bujindang>=10)
		{
			bujinsu=bujinsu-bujindang;
	thljs=150/bujinsu;
			thlbh=thljs;
	thl=(unsigned long)7500000/bujinsu%50000;
	if(thljs)
	{
	 TH1=0x3c;//中断重新装如初值
   TL1=0xb0;
	}
	else
	{
	 thh=thl/256;//中断重新装如初值
   tll=thl%256;
	}
		}
else if(djb==2&&duojpt-duojptdang>=3000)
		{
			duojpt=-duojptdang+duojpt;
		}
else if(djb==3&&duojjd-duojjddang>=0)
		{
			duojjd=duojjd-duojjddang;
		}
	xs=1;
	}
			else
	{
		TR1=0;
		xiemingling(0x01);
	}
	}
else if(key5==0)
	{
		while(key5==0);
		jz1=5;

		xs=1;
	}
else if(key6==0)
	{
		while(key6==0);
		jz1=6;
	}
else if(key7==0)
	{
		while(key7==0);
		jz1=7;
		TR1=0;
		xiemingling(0x01);
	}
	return;
}
void delay(unsigned int n)  //延时函数
{
    unsigned char a,b,c;
	for(;n>0;n--)
	{
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
	}
}
void delay10us(void)  //误差 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=2;a>0;a--);
}
void xiemingling(uchar a)    //写入命令
{
	//chamang();
	RS=0;
	RW=0;
	E=0;
	shuju=a;
	E=1;
	_nop_();
	delay10us();
	E=0;
}
void xieshuju(uchar a)   //写入数据
{
//	chamang();
	RS=1;
	RW=0;
	E=0;
	shuju=a;
	E=1;
	_nop_();
	delay10us();
	E=0;
}
void chamang()   //查忙
{
	uchar b;
	do
		{
	b=0xff;
	E=0;
	RS=0;
	RW=1;
	E=1;
	_nop_();
	b=shuju;
	 }while(b&0x80);
	E=0;
}
void chushihua()   //初始化函数
{
	xiemingling(0x38);  //1602功能设置，16x2显示，5x7点阵，8位数据接口
	delay(1);     //延时
	xiemingling(0x0c);  //开显示，不显示光标
	delay(1);
	xiemingling(0x06);  //写入后光标指针加一
	delay(1);
	xiemingling(0x01);  //清屏
	delay(1);
	return;
}
void diyihang(uchar *a)  //
{
	xiemingling(0x80);  //光标定位到1602第一行第一个位置
	while(*a)
	{
		xieshuju(*a);  //写入字符
		a++;
	}
	return;
}
void dierhang(uchar *a,uchar x)  //
{
	x=x+0xc0;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	while(*a)  //
	{
		xieshuju(*a);  //
		a++;
	}
	return;
}