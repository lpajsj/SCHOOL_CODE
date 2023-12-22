#ifndef _595shuma_h
#define _595shuma_h
//sbit date595=P1^0;sbit lclk595=P1^1;sbit hclk595=P1^2;//·ÂÕæ
sbit date595=P2^5;sbit lclk595=P2^4;sbit hclk595=P2^3;//°å×Ó
void shumaxianshi(uchar *shuma,uchar n);
#endif