//付志捷板子
#include <reg51.h>
#include "ange.h"
#include "anjian.h"
#include "duofa.h"
#include "lcd1602.h"
bit zhixing=0;//提示完成初始化等各种操作
bit yunxing=0;//发送接收正在运行标志
void fengming();
uchar moshi=1;
ucode caidan[4][17]={" duojifasong    ","   danjifasong  ","  duojijieshou  ","  danjijieshou  "};
ucode tishi[17]={"     run->ok    "};
extern bit duofas,yifa,duoshou,yishou;
extern bit yindaof,yindaos;
extern uchar yindaojishu;
extern jieshoujishu;
uchar duofadizhi=0;
void xianshi();
void ajpd()
{
	if(up==0)
	{
		delay(5);
		if(up==0)
		{
			while(up==0);
			fengming();
			if(!yunxing)
			{
			switch(moshi)
			{
				case 1:moshi=2;break;
				case 2:moshi=3;break;
				case 3:moshi=4;break;
				case 4:moshi=1;break;
			}
			xianshi();
		}
	}
		return;
	}
else	if(down==0)
	{
		delay(5);
		if(down==0)
		{
			while(down==0);
			fengming();
			if(!yunxing)
			{
			if(moshi==1)
			{
			switch(duofadizhi)
			{
				case 0:duofadizhi=1;break;
				case 1:duofadizhi=2;break;
				case 2:duofadizhi=3;break;
				case 3:duofadizhi=0;break;
			}
xianshi();
		}
	 }
		return;
 }
}
else	if(exit==0)
	{
		delay(5);
		if(exit==0)
		{
			while(exit==0);
			fengming();
			ES=0;
			duofas=0,yifa=0,duoshou=0,yishou=0;
			zhixing=0;
			yunxing=0;
			yindaof=0;
			yindaos=0;
			xianshi();
		}
		return;
	}
else if(ok==0)
	{
		delay(5);
		if(ok==0)
		{
			while(ok==0);
			fengming();
			yunxing=1;
			zhixing=1;
			xiemingling(0x01);
			delay(1);
			switch(moshi)
			{
				case 1:
			ES=0;
			duofas=1,yifa=0,duoshou=0,yishou=0;
			break;
				case 2:
			ES=0;
			duofas=0,yifa=1,duoshou=0,yishou=0;
			break;
				case 3:
			ES=1;
			duofas=0,yifa=0,duoshou=1,yishou=0;
			break;
				case 4:
			ES=1;
			duofas=0,yifa=0,duoshou=0,yishou=1;
			xiemingling(0x80);
				jieshoujishu=0;
			break;
			}
	}
			yindaof=0;
			yindaos=0;
	yindaojishu=0;
	return;
}
}
void fengming()
{
//	feng=0;
//	delay(100);
//	feng=1;
	return;
}
void xianshi()
{
				switch(moshi)
			{
				case 2:diyihang(caidan[moshi-1],0,16);dierhang(tishi,0,16);break;
				case 3:diyihang(caidan[moshi-1],0,16);dierhang(tishi,0,16);
				xiemingling(0xcd);
				xieshuju(benjidizhi/128+0x30);
				xieshuju(benjidizhi%128+0x30);
				xieshuju('H');
				break;
				case 4:diyihang(caidan[moshi-1],0,16);dierhang(tishi,0,16);break;
				case 1:diyihang(caidan[moshi-1],0,16);dierhang(tishi,0,16);
				xiemingling(0xcd);
				xieshuju(duofadizhi/128+0x30);
				xieshuju(duofadizhi%128+0x30);
				xieshuju('H');
				break;
				return;
			}
}