#ifndef _guoshi15_h
#define _guoshi15_h
#define uchar unsigned char
#define uint unsigned int
#define ucode unsigned char code
void hc138(uchar d,uchar x);
void shumaxianshi();
void delay(uint n);
uint retem();
uchar at24r(uchar d);
void at24w(uchar d,uchar x);
void dapcf(uchar x);
sbit chaofa=P1^0;
sbit chaoshou=P1^1;
sbit key0=P3^0;
sbit key1=P3^1;
sbit key2=P3^2;
sbit key3=P3^3;
sbit key4=P3^4;
sbit key5=P3^5;
sbit key6=P4^2;
sbit key7=P4^4;
uchar anjian();
uchar anjiangai();
uchar anjiangai2();
#endif
///////////////////////////////////
