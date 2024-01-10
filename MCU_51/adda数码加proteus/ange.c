#include "ange.h"
#include <reg51.h>
void delay(unsigned int n)  //ÑÓÊ±º¯Êý
{
    unsigned char a,b,c;
	for(;n>0;n--)
	{
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
	}
}