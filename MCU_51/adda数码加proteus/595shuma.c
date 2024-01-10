#include <reg51.h>
#include "ange.h"
#include "595shuma.h"
#include <intrins.h>
//ucode shumazifu[18]={0x7B,0x41,0x7C,0x75,0x47,0x37,0x3F,0x61,0x7F,0x77,0,0x2E,0x6e};//xin
ucode shumazifu[18]={0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xE7,00,0xce,0x8e};//abcd
void shumaxianshi(uchar *shuma,uchar n)
{
	uchar i=0,x=0;
	while(n--)
	{
	x=shumazifu[*shuma];
		if(n!=2)
			x&=0xfe;
		for(i=0;i<8;i++)
		{
			x=_cror_(x,1);
			hclk595=0;
			date595=!(bit)(x&0x80);
			hclk595=1;
			_nop_();
			hclk595=0;
		}
		shuma++;
	}
	lclk595=0;
	_nop_();
	lclk595=1;
	lclk595=0;
	return;
}