#include "hanshu.h"
//int32_t main(void)
//{
//  ange_USART_init(115200);
//	ange_TIMt_OC_PWM_init();
//	while(1)
//	{

//	}
//}

//u16 panduan()
//{
//	u32 i;
//	u16 x=0;
//	adbilichazhi[0]=adbili[6-1]-adbili[7-1];
//	adbilichazhi[1]=adbili[5-1]-adbili[8-1];
//	adbilichazhi[2]=adbili[4-1]-adbili[1-1];
//	adbilichazhi[3]=adbili[3-1]-adbili[2-1];
//	adbilichazhi[4]=adbili[5-1]-adbili[4-1];
//	adbilichazhi[5]=adbili[6-1]-adbili[3-1];
//	adbilichazhi[6]=adbili[7-1]-adbili[2-1];
//	adbilichazhi[7]=adbili[8-1]-adbili[1-1];
//	for(i=0;i<8;i++)
//	{
//	if(fabs(adbilichazhi[i])>0.2)
//	{
//		if(i<4) //左右
//		{
//			if(adbilichazhi[i]>0)
//			{
//				x|=0x01; //左边值大
//			}
//			else
//			{
//				x|=0x10;
//			}
//		}
//		else //上下
//		{
//			if(adbilichazhi[i]>0)
//			{
//				x|=0x100; //左边值大
//			}
//			else
//			{
//				x|=0x1000; //右边值大
//			}
//		}
//	}
//	}
//	return x;
//}
//
