#ifndef _dijiu15_h_
#define _dijiu15_h_
#define uchar unsigned char
#define uint unsigned int
void delay(uint x);
void hc138(uchar d,uchar x);
void shumaxianshi();
sbit key0=P3^0;sbit key1=P3^1;sbit key2=P3^2;sbit key3=P3^3;sbit key4=P3^4;
uchar anjian();
uchar adpcf();
void adinit(uchar d);
	uchar at24r(uchar d);
void at24w(uchar d,uchar x);
#endif