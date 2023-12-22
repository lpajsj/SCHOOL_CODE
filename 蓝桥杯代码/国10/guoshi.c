#include <STC15F2K60S2.H>
#include <absacc.h>
#include <intrins.h>
#include "guoshi15.h"
#include "onewire.h"
#include <stdio.h>
extern uchar shuma[];   
void Delay12us();  //超声波延时
void xianshi(); //显示函数
uint chaosheng();  //超声波
uint juli,julic=35,julicc,chaoshengjishu,biangeng; //距离 距离参数 距离参数暂存 超声计数 变更次数
uchar sc=1,shujuj=1;canshuj=1;  //数据参数界面判断 数据界面 参数界面
uint wendu,wenduc=30,wenducc,wendujishu=100; //温度 温度参数 温度参数暂存 温度计数
void anjianchuli(uchar x); //按键处理函数
extern uint cajs; //按键长按计数
bit dab=0;  //da标志位
void led(); //LED指示
ucode chashu[]={"ST\r\n"};  // 查询数据
ucode chacan[]={"PARA\r\n"};  // 查询参数
ucode cuowu[]={"ERROR\r\n"};  // 发送错误
uchar fashu[]={"$20,20.24\r\n"};//1 2  45 78数据
uchar facan[]={"#35,30\r\n"}; //12 45参数
uchar cjjishu=0,cjmoshi=0;  //串口接收计数 判断发送何种数据
bit cfb1=0,cfb2=0,cfb3=0;
void UartInit(void);
void ckchuli();
char putchar(char ch)
{
	SBUF=ch;
	while(TI==0);
	TI=0;
	return ch;
}
void UartInit(void)		//4800bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR &= 0xFB;		//定时器2时钟为Fosc/12,即12T
	T2L = 0xCC;		//设定定时初值
	T2H = 0xFF;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
}
void ckchuli()
{
	float h=3.21;
	uchar *x=cuowu;
	uchar i=0;
	sprintf(fashu,"$%d,%d.%d\r\n",juli,wendu/100,wendu%100);
//	fashu[1]=juli/10+0x30;
//	fashu[2]=juli%10+0x30;
//	fashu[4]=wendu/1000%10+0x30;
//	fashu[5]=wendu/100%10+0x30;
//	fashu[7]=wendu/10%10+0x30;
//	fashu[8]=wendu%10+0x30;
	sprintf(facan,"#%d,%d\r\n",julic,wenduc);
//	facan[1]=julic/10+0x30;
//	facan[2]=julic%10+0x30;
//	facan[4]=wenduc/10+0x30;
//	facan[5]=wenduc%10+0x30;  //发送串口数组赋值
	if(cfb1==1)      ///串口发送标志
	{
		cfb1=0;  //接收标志赋值0
			for(i=0;i<=10;i++)
		{
			SBUF=fashu[i]; //第一种发送数据
			while(TI==0);
				TI=0;
		}
	}
	
		else if(cfb2==1)
		{
			cfb2=0;
//			printf("%06.1f\r\n",h);
//			printf("#%06d,%d%s\r\n",julic,wenduc,cuowu);
			for(i=0;i<=7;i++)
		{
			SBUF=facan[i];  //第二种发送参数
			while(TI==0);
				TI=0;
		}
	  }
	else if(cfb3==1)
		{
			cfb3=0;
			for(i=0;i<=6;i++)
		{
			SBUF=*x;
			while(TI==0);  //第三种发送错误
				TI=0;
			x++;
		}
	  }
}
void chuan() interrupt 4 
{
	if(RI==1)
	{
		RI=0;   //清除中断标志位
		if(SBUF!='\r'&&SBUF!='\n') //忽略\r\n
		{
		if(cjjishu==0)
		{
				if(SBUF==chashu[cjjishu])
				{
					cjmoshi=1;
					cjjishu++;
				}
			else	if(SBUF==chacan[cjjishu]) //
				{
					cjmoshi=2;
					cjjishu++;
				}
				else
				{
					cjmoshi=3;
					cfb3=1;
					cjjishu=0;
				}
			}
		else if(cjmoshi==1)
		{
				if(SBUF==chashu[cjjishu])
				{
					cjjishu++;
					if(cjjishu==2)   //\r\n是4没有是2
					{
						cfb1=1;
						cjjishu=0;
					}
				}
				else
				{
					cjmoshi=3;
					cfb3=1;
					cjjishu=0;
				}
		}
		else if(cjmoshi==2)
		{
				if(SBUF==chacan[cjjishu])
				{
					cjjishu++;
					if(cjjishu==4) //\r\n是6没有是4
					{
						cfb2=1;
						cjjishu=0;
					}
				}
				else
				{
					cjmoshi=3;
					cfb3=1;
					cjjishu=0;
				}
		}
	}
    }
}
void main()
{
	uchar x;
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x30;		//设置定时初值
	TH0 = 0xF8;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	TMOD |= 0x10;		//设置定时器模式
	Init_DS18B20();
	Write_DS18B20(0xcc);  //跳过ROM
	Write_DS18B20(0x4e);   //写寄存器
	Write_DS18B20(0x00);   //TH
	Write_DS18B20(0x00);    //TL
	Write_DS18B20(0x5f);  //调整分辨率 1f 3f 5f 7f
	wendu=retem();  //温度读取
	delay(300);
	wendu=retem();  //温度读取
	hc138(4,0xff); //关闭数码管
	hc138(5,0); //关闭蜂鸣器
	EA=1;
	PS=1;
	ES=1;
//	x=at24r(0);
//  y=at24r(1);
//	biangeng=256*x+y;
	biangeng=at24r(0)*256+at24r(1); //读取EEPROM 参数变更值
	UartInit();
	while(1)
	{
		x=anjiangai2();  //读取按键值
		anjianchuli(x);  //按键处理
		if(wendujishu==0)
		{
			wendujishu=220;  //温度计数隔一段时间读取
	    wendu=retem();  //读取温度
		}
		if(chaoshengjishu==0)
		{
			chaoshengjishu=450;  //超声波计数
		  juli=chaosheng();  //读取距离
		}
		if(dab)   //da标志位
		{
			if(juli<=julic)  //根据参数值输出不同电压
			dapcf(100);
			else
			dapcf(200);
		}
		else
		{
			dapcf(20); //关闭da时输出0.4
		}
		led();  //LED指示函数
		ckchuli();  //串口发送
	}
}
void t0() interrupt 1
{
	TL0 = 0x30;		//设置定时初值
	TH0 = 0xF8;		//设置定时初值
xianshi();  //数码管显示
	if(chaoshengjishu!=0) 
	{
		chaoshengjishu--;  //
	}
	if(cajs!=0)
	{
		cajs--;
	}
	if(wendujishu!=0)
	{
		wendujishu--;
	}
}
void anjianchuli(uchar x)
{
	if(x==13)
	{
		switch(sc)  //切换参数和数据页面
		{
			case 1:sc=2;
			julicc=julic; //保存距离和温度参数
			wenducc=wenduc;
			break;
			case 2:sc=1;
			if(wenduc!=wenducc||julicc!=julic)  //如果参数改变则变更加一
			{
				biangeng++;
				at24w(0,biangeng/256); ///写后需要等待
				delay(10);
				at24w(1,biangeng%256);
			}
			break;
		}
		shujuj=1;
		canshuj=1;  //显示第一个页面
	}
	if(x==12)     //调整当前界面的页面
	{
		switch(sc)
		{
			case 1:
				switch(shujuj)
				{
					case 1:shujuj=2;break;
					case 2:shujuj=3;break;
					case 3:shujuj=1;break;
				}
				break;
			case 2:
				canshuj++;
				if(canshuj==3)
					canshuj=1;
				break;
		}
	}
	if(x==16)  
	{
	if(sc==2)
	{
		if(canshuj==1)
		{
			if(wenduc>=2)
				wenduc-=2;
		}
		if(canshuj==2)
		{
			if(julic>=5)
				julic-=5;
		}
	}
  }
	if(x==17)
	{
	if(sc==2)
	{
		if(canshuj==1)
		{
			if(wenduc<=97)
				wenduc+=2;
		}
		if(canshuj==2)
		{
			if(julic<=94)
				julic+=5;
		}
	}
  }
	if(x==120) //按键12长按，清变更
	{
		biangeng=0;
		at24w(0,0);
		delay(10);
		at24w(1,0);
	}
	if(x==130)
	{
		dab=!dab;
	}
}
void led()
{
	uchar x=0xff;  //x为即将写入的数据
	if(wendu/100>wenduc)
		x&=~0x01;
	if(juli<julic) //满足条件改变x的值
		x&=~0x02;
	if(dab)
		x&=~0x04;
	hc138(4,x);
}
void xianshi()
{
	if(sc==1)
	{
		if(shujuj==1)
		{
			shuma[0]=11;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=10;
			shuma[4]=wendu/1000;
			shuma[5]=wendu/100%10;
			shuma[6]=wendu/10%10;
			shuma[7]=wendu%10;
		}
		if(shujuj==2)
		{
			shuma[0]=12;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=10;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=juli/10%10;
			shuma[7]=juli%10;
		}
		if(shujuj==3)
		{
			shuma[0]=13;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=10;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=10;
			shuma[7]=10;
			if(biangeng>10000)
			shuma[3]=biangeng/10000; //加上判断条件 数值前边熄灭
			if(biangeng>1000)
			shuma[4]=biangeng/1000%10;
			if(biangeng>100)
			shuma[5]=biangeng/100%10;
			if(biangeng>10)
			shuma[6]=biangeng/10%10;
			shuma[7]=biangeng%10;
		}
	}
	else if(sc==2)
	{
		if(canshuj==1)
		{
			shuma[0]=14;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=1;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=wenduc/10%10;
			shuma[7]=wenduc%10;
		}
		if(canshuj==2)
		{
			shuma[0]=14;
			shuma[1]=10;
			shuma[2]=10;
			shuma[3]=2;
			shuma[4]=10;
			shuma[5]=10;
			shuma[6]=julic/10%10;
			shuma[7]=julic%10;
		}
	}
	shumaxianshi();
}
uint chaosheng()
{
	uchar x=8     ;  //八个周期方波
	uint t=0,s;
	TR1=0;
	TH1=0;
	TL1=0;
//	EA=0;  //不关闭中断感觉没有太大影响
	while(x--)
	{
		chaofa=1;
		Delay12us();  //一定是12us
		chaofa=0;
		Delay12us();
	}
	TR1=1;      //启动定时器
	while(chaoshou==1&&t<6000)  //6000是因为1ms传播34cm 100cm的话就是大约3ms来回就是6ms 等待时接收端为1
	{
		t=TH1*256+TL1;  
	}
	TR1=0;
	EA=1;    //开中断
	s=t*0.017;  //1ms大概34cm 一微妙就是0.034cm  t/2*0.034

	if(s>99)  //要加上判断值大于99显示99
		s=99;
	return s;
}
void Delay12us()		
{
	unsigned char i;
	_nop_();
	_nop_();
	_nop_();
	i = 30;
	while (--i);
}
//void Delay12us()		//@12.000MHz
//{
//	unsigned char i;

//	_nop_();
//	_nop_();
//	i = 33;
//	while (--i);
//}
//void Delay12us()		//@12.000MHz
//{
//	unsigned char i;

//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	i = 33;
//	while (--i);
//}
