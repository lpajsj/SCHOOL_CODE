#ifndef __15_H__
#define __15_H__
sfr shuju=0x80;
sbit a38=P2^5;sbit b38=P2^6;sbit c38=P2^7;
sbit fengming=P0^6;sbit jidian=P0^4;
sbit key0=P3^0;sbit key1=P3^1;sbit key2=P3^2;sbit key3=P3^3;
sbit key4=P3^4;sbit key5=P3^5;sbit key6=P3^6;sbit key7=P3^7;
sfr anjian=0xB0;
void hc138(uchar x);
void initial15();
void shumaxianshi(uchar a[8]);
uchar dulianjian();
uchar anjian4x4();
#endif