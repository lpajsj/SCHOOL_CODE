//P0口是灯，外部中断开关
#include<reg51.h>
#include<stdio.h>
#include<intrins.h>
#define uchar unsigned char
#define ucode unsigned char code
void send(uchar shuju);
void delay(unsigned int n);
void diyierhang16(uchar a[]);
void diyierhang16y(uchar a[]);
void diyierhang16b(uchar a[]);
void diyihang(uchar *a,uchar x);  //
void dierhang(uchar *a,uchar x) ; //
void diyihangb(uchar *a,uchar x);  //
void dierhangb(uchar *a,uchar x);  //
void delay10us(void);
void anjianup()
void anjianup()
void anjianup()
void anjianup()
sbit RS=P2^5;sbit RW=P2^6; sbit E=P2^7;
sbit ok=P2^0;sbit exit=P2^1;sbit up=P2^2;sbit down=P2^3;
sfr p2=0x90;sfr shuju=0x80;
ucode ye0[2][17]={"   serial port  ","  communication "};
ucode ye1[3][17]={"first","three","first"};
ucode ye23[3][17]={"send","receive","send"};
/*ucde ye46[][]={
48,49,50,51,52,53,54,55,56,57,66,67,68,69,70,71,
72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,
88,89,90,91,92,93,94,95,}
ucode yewu*/
uchar code b[]={0xfd,0x60,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7,0xef,0x00};
uchar code a[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b};
uchar lcdye=0,lcdhao=0,jz=0;
void main()
{
	uchar i;
	PCON=0x00;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	delay(10);
	diyihang(ye0[0],0);
	dierhang(ye0[0],0);
	while(1)
	{
		jz=ajpd();
		switch(jz)
		{
			case 1:
				anjianup();break;
			case 2:
				anjiandown();break;
			case 3:
				anjianok();break;
			case 4:
				anjianexit();break;
		}
		jz=0;
		}
	}
void anjianup()
{
	uchar n;
	if (lcdye==0)
	{
		lcdye=1;
		lcdhao=1;
		diyierhang16b(&ye1[0]);
	}
	else
	{
		if(lcdye==1)
		{
			lcdhao--;
			if (lcdhao==0)
				lcdhao=3;
			n=(lcdhao-1)*16;
			diyierhang16b(&ye1[n]);
		}
		else if(lcdye==2)
		{
			lcdhao--;
			if (lcdhao==3)
				lcdhao=5;
			n=(lcdhao-4)*16;
			diyierhang16b(&ye2[n]);
		}
	}
}
void anjiandown()
{
	uchar n;
	if(lcdye==0)
	{
		lcdye=1;
		lcdhao=1;
		diyierhang16b(&ye1[0]);
	}
	else
	{
		if(lcdye==1)
		{
			lcdhao++;
			if (lcdhao==4)
				lcdhao=1;
			n=(lcdhao-1)*16;
			diyierhang16b(&ye1[n]);
		}
		else if(lcdye==2)
		{
			lcdhao++;
			if (lcdhao==6)
				lcdhao=4;
			n=(lcdhao-4)*16;
			diyierhang16b(&ye2[n]);
		}
	}
}
void anjianok()
{
	if (lcdye==0)
	{
		lcdye=1;
		lcdhao=1;
		diyierhang16b(&ye1[0]);
	}
	else
	{
		if(lcdye==1)
		{
			if (lcdhao==1)
			{
				diyierhang16b(ye2);
				lcdye=2;
				lcdhao=5;
				anjianup();
				return;
			}
			else if (lcdhao==2)
			{
				
			diyierhang16(ye234);
				lcdye=3;
				time();
				return;
			}
			else if (lcdhao==3)
			{
				
			 diyierhang16(ye234);
				lcdye=4;
				daojishi();
				return;
			}
		}
		else if(lcdye==2)
		{
			
			if (lcdhao==4)
			{
				diyierhang16(ye234);
				lcdye=5;
				led1();
				return;
			}
			else if (lcdhao==5)
			{
				diyierhang16(ye234);
				lcdye=5;
				led2();
				return;
			}
		}
	}
}
void anjianexit()
{
	if (lcdye==0)
	{
		lcdye=1;
		lcdhao=1;
		diyierhang16b(&ye1[0]);
	}
	else 
	{
		if (lcdye==3||lcdye==4||lcdye==2)
		{
			lcdye=1;
			lcdhao=2;
			anjianup();
		}
		else if(lcdye==5)
		{
			lcdye=2;
			lcdhao=5;
			anjianup();
		}
	}
}
int ajpd()
{
	while(1)
	{
		if (up==0)
		{
			delay(5);
			if (up==0)
			{
				while(up==0);
				return 1;	
			}
		}
		if (down==0)
		{
			delay(5);
			if (down==0)
			{
				while(down==0);
				return 2;	
			}
		}
		if (ok==0)
		{
			delay(5);
			if (ok==0)
			{
				while(ok==0);
				return 3;	
			}
		}
	}
}
void send(uchar shu)
{

	SBUF=shu;
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
void diyihang(uchar *a,uchar x)  //
{
xiemingling(0x80);
xieshuju(0x20);
xieshuju(0x7e);  
	x=x+0x80;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	{
		xieshuju(*a);  //
		a++;
		x++;       //最多写到第十六个
	}
	return;
}
void dierhangb(uchar *a,uchar x)  //
{
xiemingling(0x80);
xieshuju(0x20);
xieshuju(0x7e);  
	x=x+0xc0;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	{
		xieshuju(*a);  //
		a++;
		x++;//最多写到第十六个
	}
	return;
}
void diyihangb(uchar *a,uchar x)  //
{
	x=x+0x80;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	{
		xieshuju(*a);  //
		a++;
		x++;//最多写到第十六个
	}
	return;
}
void dierhang(uchar *a,uchar x)  //
{
	x=x+0xc0;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	while(*a&&x!=16) //
	{
		xieshuju(*a);  //
		a++;
		x++;//最多写到第十六个
	}
	return;
}
void diyierhang16y(uchar a[])  //
{
	uchar i=0;
	xiemingling(0x80);  
	while(i!=16)
	{
		xieshuju(a[i]); 
		delay(10);
		i++;
	}
	xiemingling(0xc0);  //
	while(i!=32)  //
	{
		xieshuju(a[i]);  //
		delay(10);
		i++;
	}
}
void diyierhang16(uchar a[])  //
{
	uchar i=0;
	xiemingling(0x80);  
	while(i!=16)
	{
		xieshuju(a[i]); 
		i++;
	}
	xiemingling(0xc0);  //
	while(i!=32)  //
	{
		xieshuju(a[i]);  //
		i++;
	}
}
void diyierhang16b(uchar a[])  //
{
	uchar i=2;
xiemingling(0x80);
xieshuju(0x20);
xieshuju(0x7e);  
	while(i!=16)
	{
		xieshuju(a[i]); 
		i++;
	}
	xiemingling(0xc0);  //
	while(i!=32)  //
	{
		xieshuju(a[i]);  //
		i++;
	}
}