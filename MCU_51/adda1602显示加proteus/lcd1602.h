#ifndef _lcd1602_h
#define _lcd1602_h
#include <reg51.h>
#include "ange.h"
sbit E=P2^7;sbit RW=P2^6;sbit RS=P2^5;  //定义1602端口
sfr shuju=0x80;  //P0口数据传送对应1602的D0-D7
void xiemingling(uchar a);  //1602写入命令
void xieshuju(uchar a);  //1602写入数据
void dierhang(uchar *a,uchar x);
void diyihang(uchar *a,uchar x);
void diyihangb(uchar *a,uchar x);
void delay10us(void);
void chamang();     //查忙
void chushihua();  //初始化
#endif