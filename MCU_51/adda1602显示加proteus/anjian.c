#include <reg51.h>
#include "ange.h"
#include "anjian.h"
#include "lcd1602.h"
extern void zhengxian();
extern void sanjiao();
extern void fangbo();
uchar ye=0,hao=0;
uchar code ye1[4][17] = {"Sine Wave       ",//显示当前波形类型
                            "Triangle Wave   ",
                            "Square Wave     ",
                            "Sine Wave       "};
ucode ye5_13[2][17]={"    running     ","     ->exit      "};
ucode ye234[4][17]={"    average     ","      fir       ","      iir       ","    average     "};
extern uchar bohao,lvhao;
void ajpd()
{
	if(up==0)
	{
		delay(10);
		if(up==0)
		{
			while(up==0);
			anjianup();
		}
	}
else	if(down==0)
	{
		delay(10);
		if(down==0)
		{
			while(down==0);
			anjiandown();
		}
	}
else	if(exit==0)
	{
		delay(10);
		if(exit==0)
		{
			while(exit==0);
			anjianexit();
		}
	}
else if(ok==0)
	{
		delay(10);
		if(ok==0)
		{
			while(ok==0);
			anjianok();
		}
	}
	return;
}
void anjianok()
{
	if (ye==0)
	{
		ye=1;
		hao=1;
		diyihang(ye1[0],0);
		dierhang(ye1[1],0);
		return;
	}
else if (ye==1)
{
	if(hao==1)
	{
		ye=2;
		hao=1;
		diyihang(ye234[0],0);
		dierhang(ye234[1],0);
		bohao=1;
		return;
	}
else if(hao==2)
	{
		ye=3;
		hao=1;
		diyihang(ye234[0],0);
		dierhang(ye234[1],0);
		bohao=2;
		return;
	}
else if(hao==3)
	{
		ye=4;
		hao=1;
		diyihang(ye234[0],0);
		dierhang(ye234[1],0);
		bohao=3;
		return;
	}
}
else if(ye==2)
{
if(hao==1)
	{
		ye=5;
		hao=1;
		lvhao=1;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}
	else if(hao==2)
	{
		ye=6;
		hao=1;
		lvhao=2;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}
	else if(hao==3)
	{
		ye=7;
		hao=1;
		lvhao=3;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}
	zhengxian();
	return;
}
else if(ye==3)
{
if(hao==1)
	{
		ye=8;
		lvhao=hao;
		hao=1;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}
	else if(hao==2)
	{
		ye=9;
		lvhao=hao;
		hao=1;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}
	else if(hao==3)
	{
		ye=10;
		lvhao=hao;
		hao=1;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}
	sanjiao();
	return;
}
else if(ye==4)
{
if(hao==1)
	{
		ye=11;
		lvhao=hao;
		hao=1;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
		
	}
	else if(hao==2)
	{
		ye=12;
		lvhao=hao;
		hao=1;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}
	else if(hao==3)
	{
		ye=13;
		lvhao=hao;
		hao=1;
		diyihang(ye5_13[0],0);
		dierhang(ye5_13[1],0);
	}	
	fangbo();
	return;
}
}
void anjianexit()
{
	if (ye==0)
	{
		ye=1;
		hao=1;
		diyihang(ye1[0],0);
		dierhang(ye1[1],0);
		return;
	}
	else if(ye==2)
	{
		ye=1;
		hao=1;
		diyihang(ye1[0],0);
		dierhang(ye1[1],0);
		return;
	}
	else if(ye==3)
	{
		ye=1;
		hao=2;
		diyihang(ye1[1],0);
		dierhang(ye1[2],0);
		return;
	}
	else if(ye==4)
	{
		ye=1;
		hao=3;
		diyihang(ye1[2],0);
		dierhang(ye1[3],0);
		return;
	}
	else if(ye==5||ye==6||ye==7)
	{
		ye=2;
		if (ye==5)
		 hao=1;
		else if(ye==6)
			hao=2;
		else if(ye==7)
			hao=3;
		diyihang(ye234[hao-1],0);
		dierhang(ye234[hao],0);
		return;
	}
	else if(ye==8||ye==9||ye==10)
	{
		ye=3;
		if (ye==8)
		 hao=1;
		else if(ye==9)
			hao=2;
		else if(ye==10)
			hao=3;
		diyihang(ye234[hao-1],0);
		dierhang(ye234[hao],0);
		return;
	}
	else if(ye==11||ye==12||ye==13)
	{
		ye=4;
		if (ye==11)
		 hao=1;
		else if(ye==12)
			hao=2;
		else if(ye==13)
			hao=3;
		diyihang(ye234[hao-1],0);
		dierhang(ye234[hao],0);
		return;
	}
}
void anjiandown()
{
	if (ye==0)
	{
		ye=1;
		hao=1;
		diyihang(ye1[0],0);
		dierhang(ye1[1],0);
		return;
	}
else
{
	hao+=2;
	anjianup();
}
}
void anjianup()
{
	if (ye==0)
	{
		ye=1;
		hao=1;
		diyihang(ye1[0],0);
		dierhang(ye1[1],0);
		return;
	}
else
{
	hao--;
	if(ye==1)
	{
	if(hao==1||hao==4)
	{
		hao=1;
		diyihang(ye1[0],0);
		dierhang(ye1[1],0);
	}
	else if(hao==2)
	{
		diyihang(ye1[1],0);
		dierhang(ye1[2],0);
	}
	else if(hao==0||hao==3)
	{
		hao=3;
		diyihang(ye1[2],0);
		dierhang(ye1[3],0);
	}	
  }
else if(ye==2||ye==3||4==ye)
{
	if(hao==1||hao==4)
	{
		hao=1;
		diyihang(ye234[hao-1],0);
		dierhang(ye234[hao],0);
	}
	else if(hao==2)
	{
		diyihang(ye234[hao-1],0);
		dierhang(ye234[hao],0);
	}
	else if(hao==0||hao==3)
	{
		hao=3;
		diyihang(ye234[hao-1],0);
		dierhang(ye234[hao],0);
	}
}
}
return;
}