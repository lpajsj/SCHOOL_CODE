//P0口是灯，外部中断开关
#include<reg51.h>
#include<stdio.h>
#include<intrins.h>
#define uchar unsigned char
void send(uchar shuju);
void delay(unsigned int n);
sfr p2=0xa0;
uchar code b[]={0xfd,0x60,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7,0xef,0x00};
uchar code a[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b};
void main()
{
	uchar i;
	PCON=0x00;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SCON=0x40;
	delay(10);
	while(1)
	{
		for(i=0;i<=8;i++)
		{
			p2=b[i];
			send(a[i]);
			delay(100);
		}
	}
}
void send(uchar shuju)
{

	SBUF=shuju;
	while(TI==0)
		;
	TI=0;
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