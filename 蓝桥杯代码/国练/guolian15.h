#ifndef _guolian15_h
#define _guolian15_h

#include "intrins.h"
#include "absacc.h"
#include "stdio.h"
#define uchar unsigned char
#define uint unsigned char
#define ucode unsigned char code
sbit key0=P3^0;sbit key1=P3^1;sbit key2=P3^2;sbit key3=P3^3;sbit key4=P3^4;sbit key5=P3^5;sbit key6=P4^2;sbit key7=P4^4;
char putchar(char ch);
void shumaxianshi();
void hc138(uchar d,uchar x);
void writetime();
void readtime();
void adinit(uchar d);
	uchar adpcf();
void dapcf(uchar x);
uchar anjian();
#endif