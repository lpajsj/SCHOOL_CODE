#ifndef _anjian_h
#define _anjian_h
void ajpd();
void anjianok();
void anjianexit();
void anjianup();
void anjiandown();
sbit down=P3^3;sbit up=P3^4;sbit exit=P3^2;sbit ok=P3^5;sbit feng=P3^3;
//sbit bo1led=P0^0;sbit bo2led=P0^1;sbit bo3led=P0^2;sbit lv1led=P0^3;sbit lv2led=P0^4;sbit lv3led=P0^5;sbit feng=P2^6;//
//sfr led=0x80;
#endif