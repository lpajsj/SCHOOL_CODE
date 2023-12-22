#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include "ange.h"
#include "15ab.h"
#include "IIC.h"
#include "shiyan.h"
uchar moshi=1,jishu=0; //moshi当前系统的模式,，计数值
uint adain3,adain3a,canshu;//pcf端口3的ad值,参数
uchar shuma[]={0,10,10,10,10,0,0,0};  //要显示的数组
void xianshi();   //数码管显示函数
void at24w(uchar d,uchar x);  //at24c02写入，x数据,d通道号，
uchar at24r(uchar d);
uchar  adpcfr(); //读取ad值、
void adpcf(uchar x);//ad初始化
void dapcf(uchar x);//da
bit jishua=0; //ad值若与参数则置一
uint dingshijishu=3333;
uint adjishu=100;
bit  xpb=0;
uchar wucao=0;
void ledzhishi();
void main()
{
	uchar x;
	uchar a;
	EA=1;
	ET0=1;
	TMOD=0x01;
	TH0=0xfa;  // 1.5ms
	TL0=0x24;
	initial15();
	TR0=1;
	canshu=at24r(1)*10;   //参数是除以10保存在EEPROM中
	if(canshu%50!=0)   /// 由于参数一定是50的倍数，不满足时可能是第一次，EEPROM的数据是以前不相关的
	{
		at24w(1,0);
		canshu=0;
	}
//	init_pcf8591();
adpcf(3); /////11
	while(1)
	{
//		a=adc_pcf8591();//11
		if(adjishu==0)
		{
			adjishu=50;
		a=adpcfr();	
		adain3=a*1.96;  //假设参考电压为5v保留两位小数，500/255=1.96 最终电压1.96*adain3
		}
//		adpcf(0x40);  //22
//		a=adpcfr();   //22
//		dapcf(canshu/2);  ///22

		x=anjianpanduan(); //按键判断 注意无按键按下时返回的值是0xff
		switch(x)   //对应按键操作
		{
			case 12:     //按键S12切换模式
				moshi+=1;
			if(moshi==4)  //共有三种模式，1是显示，2是参数，3是计数
				moshi=1;
			break;
			case 13:
				if(moshi==3)  //S12，给计数清零
				{
					jishu=0;
				}
				break;
			case 16:    //参数+
				if(moshi==2)
				{
					if(canshu<500)   //添加界限
					canshu+=50;
					else
					canshu=0;
				}
				at24w(1,canshu/10);  //将参数除以10，写到EEPROM
				break;
			case 17:
				if(moshi==2)   ///参数-
				{
					if(canshu>0)
					canshu-=50;
					else
					canshu=500;
				}
				at24w(1,canshu/10);
				break;
		}
		if(moshi==1||moshi==3)   //计数时加上界限是在模式1下
		{
			if(jishua)   //jishua初始值为零，第二次开始判断，计数值是否加一
			{
			if((adain3a>canshu)&&(adain3<canshu))  //前一次与本次的值一起与参数做对比
				jishu++;			
			adain3a=adain3;   //保存本次ad转换的值
			if(jishu==100)
				jishu=0;
			}
			else
				adain3a=adain3;  //保存第一次的值
			jishua=1;
		}
		if(adain3<canshu)   //led1
		{
			xpb=1;   //xpb置一后定时器中 dingshijishu开始减一
		}
		else
		{
			xpb=0;  //一旦出现不满adain3不小于参数的情况，xpb为0，dingshijishu重新计数
			dingshijishu=3333;
		}
		//
		if(x!=0xff)  //在按键安下的情况下
		{
		if(moshi==1)  //led3
		{
			if((x==13||x==16||x==17)) //对应模式若按其他案件，则误操作数加一
				wucao++;
			else
				wucao=0;
		}
		if(moshi==2)
		{
			if(x==13)
				wucao++;
			else
				wucao=0;
		}
		if(moshi==3)
		{
			if(x==16||x==17)
				wucao++;
			else
				wucao=0;
		}
	}
		if(wucao==255)
			wucao--;
		ledzhishi();
		//
	}
}
void ledzhishi()
{
	uchar x=0xff;  //定义一个变量为0xff，哪一位需要亮给对应位清零
	if(dingshijishu==0)
	{
		x&=0xfe;
	}
	if(jishu%2!=0)
	{
		x&=0xfd;
	}
	if(wucao>=3)
	{
		x&=0xfb;
	}
	hc138(4,x);  //
}
void xianshi()
{
	switch(moshi)
	{
		case 1:
		shuma[0]=11;
		shuma[5]=adain3/100;
		shuma[6]=adain3/10%10;
		shuma[7]=adain3%10;
		break;
		case 2:
		shuma[0]=12;
		shuma[5]=canshu/100;
		shuma[6]=canshu/10%10;
		shuma[7]=canshu%10;
		break;
		case 3:
		shuma[0]=13;
		shuma[5]=10;
		shuma[6]=jishu/10;
		shuma[7]=jishu%10;
		break;
	}
	shumaxianshi(shuma);
}
void adpcf(uchar x)
{
	IIC_Start(); //注意start后不需要回应
	IIC_SendByte(0x90);//1001 A2A1A0 R/w  pcf8591高四位固定，
	IIC_WaitAck();
	IIC_SendByte(x);//0 da位 xx输入方式 0 xx端口号
	IIC_WaitAck();
	IIC_Stop();
}
uchar  adpcfr() //读取ad值、x表示通道号
{
	uchar y;
	IIC_Start();
	IIC_SendByte(0x91);//读取命令
	IIC_WaitAck();
	y=IIC_RecByte();   ///接收完数据直接stop
	IIC_Stop();
	return y;
}
void dapcf(uchar x)
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(0x40);
	IIC_WaitAck();
	IIC_SendByte(x);
	IIC_WaitAck();
	IIC_Stop();
	return;
}
void at24w(uchar d,uchar x)
{
	IIC_Start();
	IIC_SendByte(0xa0);  
	IIC_WaitAck();
	IIC_SendByte(d);
	IIC_WaitAck();
	IIC_SendByte(x);
	IIC_WaitAck();
	IIC_Stop();
}
uchar at24r(uchar d)
{
	uchar x;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(d);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	x=IIC_RecByte();
	IIC_Stop();
	return x;
}
void t0() interrupt 1
{
	TH0=0xfa;
	TL0=0x24;  ///1.5ms
	xianshi();
	if(dingshijishu!=0)
	{
		if(xpb==1)
		dingshijishu--;
	}
	{
		if(adjishu!=0)
		{
			adjishu--;
		}
	}
}