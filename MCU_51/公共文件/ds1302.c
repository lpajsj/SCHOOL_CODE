#include <reg51.h>
#include <intrins.h>
#include "ange.h"
#include "ds1302.h"
uchar dstime[7]={20,7,12,20,21,47,10};
void write_ds13(uchar x)
{
	uchar i;
	for(i=1;i<=8;i++)
	{
		scl_ds1302=0;
		if(x&0x01)
		io_ds1302=1;
		else
		io_ds1302=0;
		scl_ds1302=1;
		x>>=1;
	}
	scl_ds1302=0;
}
uchar read_ds13()
{

	uchar i,x;
	io_ds1302=1;
	for(i=1;i<=8;i++)
	{
		x>>=1;
		scl_ds1302=0;
		if(io_ds1302)
		x|=0x80;
		scl_ds1302=1;
	}
	scl_ds1302=0;
	return x;
}
uchar read_ds1302(uchar a)
{
	uchar x;
  ce_ds1302=0;
  scl_ds1302=0;
  ce_ds1302=1;
	write_ds13(a);
	x=read_ds13();
//	delay(10);  /////////////!!!!!!!!!!!!要么Io口拉低
	io_ds1302=0;  /////////////!!!!!!!!!!!!要么延时
  ce_ds1302=0;
	return x;
}
void write_ds1302(uchar a,uchar x)
{
	ce_ds1302=0;
	scl_ds1302=0;
	ce_ds1302=1;
	write_ds13(a);
	write_ds13(x);
	ce_ds1302=0;
	return;
}
void write_dstime()
{
	uchar a=0x8c,i,x;
	write_ds1302(0x8e,0);
	for (i=0;i<7;i++)
	{
		x=dstime[i];
		dstime[i]=x/10;
	  dstime[i]<<=4;
	  dstime[i]|=x%10;
		write_ds1302(a,dstime[i]);
		a-=2;
	}
	write_ds1302(0x8e,0x80);
	ce_ds1302=0;
}
void read_dstime()
{
	uchar a=0x8d,x,i;
	ce_ds1302=0;
	scl_ds1302=0;
	ce_ds1302=1;
	write_ds1302(0x8e,0);
	for (i=0;i<7;i++)
	{
		x=read_ds1302(a);
		dstime[i]=x/16*10;
	  dstime[i]+=x%16;
		a-=2;
	}
	write_ds1302(0x8e,0x80);
}