#ifndef _15ab_h_
#define _15ab_h_
sfr shuju=0x80;
sfr anjian=0xb0;
sbit key0=P3^0;sbit key1=P3^1;sbit key2=P3^2;sbit key3=P3^3;sbit key4=P3^4;sbit key5=P3^5;sbit key6=P3^6;sbit key7=P3^7;
void hc138(uchar x,uchar a);
void initial15();
void shumaxianshi(uchar b[8]);
uchar anjianpanduan();
#endif