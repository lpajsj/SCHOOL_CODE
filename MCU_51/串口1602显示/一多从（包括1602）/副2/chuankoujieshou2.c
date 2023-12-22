//P0口是灯，外部中断开关
#include<reg51.h>
#include<stdio.h>
#include<intrins.h>
#define uchar unsigned char
void delay(unsigned int n);
int anjian();
sfr p2=0xa0;
sbit fj=P1^0;sbit jian1=P1^2;sbit zhishi=P1^1;
uchar jianzhi=0,xuan=0;
uchar code b[]={0xfd,0x60,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7,0xef,0x00};
uchar shuju[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b};
void main()
{
	uchar i,a;
	PCON=0x00;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SCON=0xd0;
	zhishi=0;
	SM2=1;
	EA=1;
	ES=1;
	fj=0;
		while(1)
	{
		while(xuan==0);
		jianzhi=anjian();
		if(jianzhi==1)
		{
		TB8=0;
		fj=1;	
		SBUF=0x6f;
		while(TI==0);
		;
		TI=0;
		SBUF=0x6b;
		while(TI==0);
		;
		TI=0;
		}
		fj=0;
		SM2=0;
		for(i=0;i<=9;i++)
	{
		while(RI==0);
		;
		RI=0;
		a=SBUF;
		a-=0x30;
		p2=b[a];
		delay(100);
	}
	}
}
int anjian()
{
	while(1)
	{
	if(jian1==0)
	{
		delay(10);
		if(jian1==0)
			return 1;
	}
}
}
void delay(unsigned int n)  
{
    unsigned char a,b,c;
	for(;n>0;n--)
	{
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
	}
}
void chuankou() interrupt 4
{
				zhishi=1;
	if (RI)
	{
		RI=0;
		if(RB8==1)
		{
		if(SBUF==0x32)
			xuan=1;
		else
			xuan=0;
		return;
	}
	}
}
