#ifndef _anjian_h
#define _anjian_h
void ajpd();
void anjianok();
void anjianexit();
void anjianup();
void anjiandown();
sbit up=P3^4;sbit down=P3^5;sbit exit=P3^6;sbit ok=P3^7;
#endif