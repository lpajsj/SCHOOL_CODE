#ifndef _lcd1602_h
#define _lcd1602_h
#include <reg51.h>
#include "ange.h"
//sbit E=P2^7;sbit RW=P2^6;sbit RS=P2^5;sbit lcdbei=P2^3;  //����1602�˿�ѧ��
sbit E=P2^5;sbit RW=P2^6;sbit RS=P2^7;sbit lcdbei=P2^3;  //����1602�˿ڼ�ѫ
sfr shuju=0x80;  //P0�����ݴ��Ͷ�Ӧ1602��D0-D7
void xiemingling(uchar a);  //1602д������
void xieshuju(uchar a);  //1602д������
void dierhang(uchar *a,uchar x,uchar n);
void diyihang(uchar *a,uchar x,uchar n);
void diyihangb(uchar *a,uchar x,uchar n);
void delay10us(void);
void chamang();     //��æ
void chushihua();  //��ʼ��
void dierhangxin(uchar *a,uchar x,uchar n);  ////////////////
#endif