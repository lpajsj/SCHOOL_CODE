#include "ange.h"
#include <reg51.h>
#include "lvbo.h"
uchar pingjunshuzu[10];
uchar firshuzu[4];
uchar iirshu=0;
uchar firjishu=0;
bit firkaishi=0;
bit iirkaishi=0;
//
uchar pingjunshuzu1[10];
uchar firshuzu1[4];
uchar iirshu1=0;
uchar firjishu1=0;
bit firkaishi1=0;
bit iirkaishi1=0;
uchar pingjun()
{
	uint a=0,n=10;
	while(n--)
	{
		a+=pingjunshuzu[n];
	}
	a/=10;
	return a;
}
uchar iir(uchar x)
{
	if(iirkaishi==0)
	{
		iirkaishi=1;
		iirshu=x;
	}
	iirshu=iirshu/2+x/2;
	return iirshu;
}
uchar fir(uchar x)
{
	if(!firkaishi)
	{
		firshuzu[firjishu]=x/4;
		firjishu++;
		if(firjishu==4)
		{
			firkaishi=1;
			firjishu=0;
   	}
			return x;
	}
	else
	{
		firshuzu[firjishu]=x/4;
		firjishu++;
		if(firjishu==4)
			firjishu=0;
		x=firshuzu[0]+firshuzu[1]+firshuzu[2]+firshuzu[3];
			return x;
	}
}
//
uchar pingjun1()
{
	uint a=0,n=10;
	while(n--)
	{
		a+=pingjunshuzu1[n];
	}
	a/=10;
	return a;
}
uchar iir1(uchar x)
{
		if(iirkaishi1==0)
		{
			iirkaishi1=1;
		iirshu1=x;
		}
	iirshu1=iirshu1/2+x/2;
	return iirshu1;
}
uchar fir1(uchar x)
{
	if(!firkaishi1)
	{
		firshuzu[firjishu1]=x/4;
		firjishu1++;
		if(firjishu1==4)
		{
			firkaishi1=1;
			firjishu1=0;
   	}
			return x;
	}
	else
	{
		firshuzu1[firjishu1]=x/4;
		firjishu1++;
		if(firjishu1==4)
			firjishu1=0;
		x=firshuzu1[0]+firshuzu1[1]+firshuzu1[2]+firshuzu1[3];
			return x;
	}
}