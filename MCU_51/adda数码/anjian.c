//#include <reg51.h>
//#include "ange.h"
//#include "anjian.h"
//extern uchar bohao,lvhao;
//extern bit zhixing;
//void fengming();
//void ajpd()
//{
//	if(up==0)
//	{
//		delay(10);
//		if(up==0)
//		{
//			while(up==0);
//			fengming();
//			switch(bohao)
//			{
//				case 1:
//					bohao=2;led|=0x0e;bo2led=0;
//				break;
//				case 2:
//					bohao=3;led|=0x0e;bo3led=0;
//				break;
//				case 3:
//					bohao=0;led|=0x0e;
//				break;
//					case 0:
//					bohao=1;led|=0x0e;bo1led=0;
//				break;
//			}
//		}
//		return;
//	}
//else	if(down==0)
//	{
//		delay(10);
//		if(down==0)
//		{
//			while(down==0);
//			fengming();
//			switch(lvhao)
//			{
//				case 0: 
//					lvhao=1;led|=0x70;lv1led=0;
//				break;
//				case 1:
//					lvhao=2;led|=0x70;lv2led=0;
//				break;
//				case 2:
//					lvhao=3;led|=0x70;lv3led=0;
//				break;
//				case 3:
//				lvhao=0;led|=0x70;
//				break;
//		}
//	}
//		return;
//}
//else	if(exit==0)
//	{
//		delay(10);
//		if(exit==0)
//		{
//			while(exit==0);
//			fengming();
//			
//		}
//		return;
//	}
//else if(ok==0)
//	{
//		delay(10);
//		if(ok==0)
//		{
//			while(ok==0);
//			fengming();
//			zhixing=!zhixing;
//			TR1=zhixing;
//			switch(bohao)
//			{
//				case 2:
//					bo2led=0;
//				break;
//				case 3:
//					bo3led=0;
//				break;
//				case 1:
//				bo1led=0;
//				break;
//			}
//			switch(lvhao)
//			{
//				case 2:
//					lv2led=0;
//				break;
//				case 3:
//					lv3led=0;
//				break;
//				case 1:
//					lv1led=0;
//				break;
//	    }
//	}
//	return;
//}
//	}
//void fengming()
//{
//	feng=0;
//	delay(10);
//	feng=1;
//	return;
//}


//¸¶Ö¾½Ý°å×Ó
#include <reg51.h>
#include "ange.h"
#include "anjian.h"
extern uchar bohao,lvhao;
extern bit zhixing;
void fengming();
void ajpd()
{
	if(up==0)
	{
		delay(5);
		if(up==0)
		{
			while(up==0);
			fengming();
			switch(bohao)
			{
				case 1:
					bohao=2;led|=0x07;bo2led=0;
				break;
				case 2:
					bohao=3;led|=0x07;bo3led=0;
				break;
				case 3:
					bohao=1;led|=0x07;bo1led=0;
				break;
			}
		}
		return;
	}
else	if(down==0)
	{
		delay(5);
		if(down==0)
		{
			while(down==0);
			fengming();
			switch(lvhao)
			{
				case 0: 
					lvhao=1;led|=0x38;lv1led=0;
				break;
				case 1:
					lvhao=2;led|=0x38;lv2led=0;
				break;
				case 2:
					lvhao=3;led|=0x38;lv3led=0;
				break;
				case 3:
				lvhao=0;led|=0x38;
				break;
		}
	}
		return;
}
else	if(exit==0)
	{
		delay(5);
		if(exit==0)
		{
			while(exit==0);
			fengming();
			
		}
		return;
	}
else if(ok==0)
	{
		delay(5);
		if(ok==0)
		{
			while(ok==0);
			fengming();
			zhixing=!zhixing;
			TR1=zhixing;
			switch(bohao)
			{
				case 2:
					bo2led=0;
				break;
				case 3:
					bo3led=0;
				break;
				case 1:
				bo1led=0;
				break;
			}
			switch(lvhao)
			{
				case 2:
					lv2led=0;
				break;
				case 3:
					lv3led=0;
				break;
				case 1:
					lv1led=0;
				break;
	    }
	}
	return;
}
	}
void fengming()
{
	feng=0;
	delay(100);
	feng=1;
	return;
}