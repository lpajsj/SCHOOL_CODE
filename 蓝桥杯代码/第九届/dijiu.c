#include <reg51.h>
#include <intrins.h>
#include "dijiu15.h"
#include "iic.h"
uchar bianhao=1,moshi=1,lx=1,dengji;//bainhao是各种亮的不同方式，moshi表示数码管显示方式，lx表示LED亮到第几次，等级是LED亮度等级
uint shanshuojishu,liujianjishu,liujian=400;//数码管亮暗间隔计数，LED流转间隔时间
bit smmab=0,lxb=1;  //数码亮暗标志，和LED流转标志位
void led();  //LED流水灯函数
bit ledb=0;  //流水灯标志位
void anjianchuli(); //按键处理函数
void xianshi();  //数码管显示函数
extern uchar shuma[]; //数码管数组
uint adzhi=1;  //ad值，LED明暗间隔计数（pwm）
void liangdu(); //根据亮度等级调整pwm高电平时间
bit dengjib;  //等级标志位，看是否显示亮度等级
uint qianzhou,houzhou,zongzhou=2000; //产生pwm的各项参数
bit zhoub;  //pwm高低参数
void zhankong();  //输出pwm
void main()
{
	uchar x;
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x24;		//设置定时初值
	TH0 = 0xFA;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	EA=1;
	ET0=1;
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0xA4;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1=1;
	hc138(4,0xff); ////关闭LED
	hc138(5,0);  ///关闭蜂鸣器
	hc138(7,0xff); ///数码管关闭
	liujian=at24r(0)*10;  //将间隔时间读取
	if(liujian%100!=0||liujian<400||liujian>1200)
	{
		liujian=400;
	at24w(0,40);
	}
	adinit(1);  ///ADC初始化
	while(1)
	{
//			adinit(1);  ///ADC初始化
		adzhi=adpcf(); //读取ad值 ||||||||||不能一直读
		if(adzhi<=125/2)  ///根据ad值判断亮度等级
		{
			dengji=1;
		}
		else if(adzhi>125/2&&adzhi<=250/2)
			dengji=2;
		else if(adzhi>250/2&&adzhi<=475/2)
			dengji=3;
		else if(adzhi>475/2)
			dengji=4;	
		x=anjian();  //按键判断
		anjianchuli(); //按键处理程序
		if(ledb)
		{
			liangdu();  /////调整中断时间，调整LED亮度
			if(lxb)    //
			{
				lxb=0; //清除流转标志位
				liujianjishu=liujian*10/15;  //led流转间隔赋值
				lx++;
			 if(bianhao==1||bianhao==2)  ///根据编号，选择LED亮到第几次
		     if(lx==9)
			     lx=1;
			 if(bianhao==3||bianhao==4) //形式3和4只有 4次
				 if(lx==5)
					lx=1;
			}
		}
		else
			hc138(4,0xff); // 如果LED标志位未开则熄灭LED
	}
}
void t1() interrupt 3
{
	zhankong();  //定时器1产生pwm
}
//////liangdu
void liangdu()
{
	switch(dengji)   //调整pwm的高电平时间
	{
		case 1:
			qianzhou=10;
		break;
		case 2:
			qianzhou=100;
		break;
		case 3:
			qianzhou=1000;
		break;
		case 4:
			qianzhou=1500;
		break;
	}
}
///////
void zhankong()  //输出pwm
{
	uint x;
	zhoub=!zhoub;  //高低电平标志位
	houzhou=zongzhou-qianzhou;  //低电平变量
	if(zhoub)
	{
		x=65535-qianzhou;  //标志位为一，将对应高电平时间写入
	}
	else
	{
		x=65535-houzhou; //低电平
	}
	if(ledb)
	{
			if(zhoub)  //标志位为一则LED亮
			led();
			else   //否则LED熄灭
			hc138(4,0xff); //
		}
		TH1=x/256;
		TL1=x%256;
}
//显示
void xianshi()   ///数码管显示
{
	if(moshi==1)
	{
		shuma[0]=10;
		shuma[1]=10;
		shuma[2]=10;
		shuma[3]=10;
		shuma[4]=10;
		shuma[5]=10;
		shuma[6]=10;
		shuma[7]=10;
		if(dengjib)
		{
		shuma[6]=11;
		shuma[7]=dengji;  //显示等级
		}
	}
//			shuma[0]=
//		shuma[1]=
//		shuma[2]=
//		shuma[3]=
//		shuma[4]=
//		shuma[5]=
//		shuma[6]=
//		shuma[7]=
	if(moshi==2||moshi==3)  //调整时间
	{
		shuma[0]=11;
		shuma[1]=bianhao;
		shuma[2]=11;
		shuma[3]=10;
		shuma[4]=liujian/1000;
		if(shuma[4]==0)
			shuma[4]=10;
		shuma[5]=liujian/100%10;
		shuma[6]=liujian/10%10;
		shuma[7]=liujian%10;
		if(shanshuojishu==0)
		{
			smmab=!smmab;
			shanshuojishu=533;
		}
	}
	if(moshi==2)  //模式2调整LED编号，数码管根据smmab决定亮灭
	{
		if(smmab==0)
		{
		shuma[0]=10;
		shuma[1]=10;
		shuma[2]=10;
		}
	}
	if(moshi==3)  //调整间隔时间
	{
		if(smmab==0)
		{
			shuma[4]=10;
		shuma[5]=10;
		shuma[6]=10;
		shuma[7]=10;
		}
	}
//	shuma[0]=adzhi/100;
//	shuma[1]=adzhi/10%10;
//	shuma[2]=adzhi%10;
	shumaxianshi();
}
/////////按键处理
void anjianchuli(uchar x)
{
		if(x==7)  //led开关
		{
		ledb=!ledb;
		lx=1;
		lxb=0;
		liujianjishu=liujian*10/15;  //led流转间隔赋值
		}
		if(x==6) //设置切换，模式2调整编号，3调整间隔
		{
			switch(moshi)
			{
				case 3:moshi=1;
				break;
				case 1:moshi=2;
				break;
				case 2:moshi=3;
				break;
			}
		}
		if(x==5)  
		{
			if(moshi==2)
			{
				lx=1;
				bianhao++;
				if(bianhao==5)
					bianhao=1;
			}
			if(moshi==3)
			{
				if(liujian==1200)
					liujian=400;
				else
					liujian+=100;
				at24w(0,liujian/10);
			}
		}
		if(x==4)
		{
			if(moshi==2)
			{
				lx=1;
				if(bianhao==1)
					bianhao=4;
				else
					bianhao--;
			}
			if(moshi==3)
			{
				if(liujian==400)
					liujian=1200;
				else
					liujian-=100;
				at24w(0,liujian/10);
			}
		}
		return;
}
///////////////中断
void t0() interrupt 1
{
	TL0 = 0x24;		//设置定时初值
	TH0 = 0xFA;		//设置定时初值
	if(shanshuojishu!=0)
	shanshuojishu--;
	if(liujianjishu!=0) //流转间隔计数
	{
		liujianjishu--;
	}
	else
		lxb=1;  //表示开始亮下一个LED
	xianshi();  //数码管显示
}
///////////led
void led()  //led显示函数
{
	uchar x;
	if(bianhao==1)  //第一种显示方式
	{
		x=0xfe;
		x=_crol_(x,lx-1);
		hc138(4,x);

	}
	if(bianhao==2)  //
	{
		x=0x7f;
		x=_cror_(x,lx-1);
		hc138(4,x);

	}
	if(bianhao==3)
	{
		if(lx==1)
			x=0x7e;
		if(lx==2)
			x=0xbd;
		if(lx==3)
		{
			x=0xdb;
		}
		if(lx==4)
		{
			x=0xe7;
		}
		hc138(4,x);
	}
	if(bianhao==4)
	{
		if(lx==4)
		{
			x=0x7e;
		}
		if(lx==3)
			x=0xbd;
		if(lx==2)
		{
			x=0xdb;
		}
		if(lx==1)
			x=0xe7;
		hc138(4,x);
	}
}