//P0���ǵƣ��ⲿ�жϿ���
#include<reg51.h>
#include<stdio.h>
#include<intrins.h>
#define uchar unsigned char
int receive();
void delay(unsigned int n);
sfr p2=0x90;
uchar code b[]={0xfd,0x60,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7,0xef,0x00};
void main()
{
	uchar i;
	PCON=0x00;
	TMOD=0x20;   //��ʱ��T1�÷�ʽ2
	TH1=0xfd;   //11.0992mhz,9600������
	TL1=0xfd;
	TR1=1;
	SCON=0x50;
	while(1)
	{

		for(i=0;i<=8;i++)
		{
			p2=b[receive()];
			delay(100);
		}
	}
}
int receive()
{
	uchar shuju;
	while(RI==0)
		;
	RI=0;
	shuju=SBUF;
	shuju-=48;
	return shuju;

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