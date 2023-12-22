#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include "ange.h"
void delay(uchar x)//1ms
{
	unsigned char i,j;
	while(x--)
	{
	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}
}