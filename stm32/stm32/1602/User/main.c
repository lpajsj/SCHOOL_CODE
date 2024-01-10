#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "ange_ad.h"
#include "stm32f10x.h"
#include "ange_dma.h"
#include "ange_da.h"
#include "key.H"
uint16_t DA1_data[128]={2047,2147,2247,2347,2446,2544,2641,2736,2830,2922,3011,3099,3184,3266,3345,
												3421,3494,3563,3629,3691,3749,3802,3852,3897,3938,3974,4005,4032,4054,4071,
												4084,4091,4093,4091,4084,4071,4054,4032,4005,3974,3938,3897,3852,3802,3749,
												3691,3629,3563,3494,3421,3345,3266,3184,3099,3011,2922,2830,2736,2641,2544,
												2446,2347,2247,2147,2047,1946,1846,1746,1647,1549,1452,1357,1263,1171,1082,
												994,909,827,748,672,599,530,464,402,344,291,241,196,155,119,88,61,39,22,9,
												2,0,2,9,22,39,61,88,119,155,196,241,291,344,402,464,530,599,672,748,827,909,
994,1082,1171,1263,1357,1452,1549,1647,1746,1846,1946};
////
#define RS PBout(12)
#define RW PBout(13)
#define E PBout(14)
#define D0 PAout(2)
#define D1 PAout(3)
#define D2 PAout(4)
#define D3 PAout(5)
#define D4 PAout(6)
#define D5 PAout(7)
#define D6 PBout(5)
#define D7 PBout(6)	
void xiemingling(u8 a)    //写入命令
{
	//chamang();
	RS=0;
	SysTick_delayus(10);
	RW=0;
	SysTick_delayus(10);
	E=0;
	D0=a&0x01;
		a>>=1;
	D1=a&0x01;
	a>>=1;
	D2=a&0x01;
		a>>=1;
	D3=a&0x01;
		a>>=1;
	D4=a&0x01;
		a>>=1;
	D5=a&0x01;
		a>>=1;
	D6=a&0x01;
		a>>=1;
	D7=a&0x01;
	E=1;
	SysTick_delayus(10);
	E=0;
}
void xieshuju(u8 a)   //写入数据
{
//	chamang();
	RS=1;
	RW=0;
	E=0;
	D0=a&0x01;
		a>>=1;
	D1=a&0x01;
	a>>=1;
	D2=a&0x01;
		a>>=1;
	D3=a&0x01;
		a>>=1;
	D4=a&0x01;
		a>>=1;
	D5=a&0x01;
		a>>=1;
	D6=a&0x01;
		a>>=1;
	D7=a&0x01;
	E=1;
	SysTick_delayus(10);
	E=0;
}
/*
void chamang()   //查忙
{
	uchar b;
	do
		{
	b=0xff;
	E=0;
	RS=0;
	RW=1;
	E=1;
	_nop_();
	b=shuju;
	 }while(b&0x80);
	E=0;
}
*/
void chushihua()   //初始化函数
{
	xiemingling(0x38);  //1602功能设置，16x2显示，5x7点阵，8位数据接口
	SysTick_delayms(10);     //延时
	xiemingling(0x0c);  //开显示，不显示光标
	SysTick_delayms(10);
	xiemingling(0x06);  //写入后光标指针加一
	SysTick_delayms(10);
	xiemingling(0x01);  //清屏
	SysTick_delayms(10);
	return;
}
void diyihang(u8 *a,u8 x,u8 n)  //
{
	x=x+0x80;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	SysTick_delayus(100);
	while(*a&&n--) //
	{
		xieshuju(*a);  //
		SysTick_delayus(100);
		a++;
	}
	return;
}
void dierhang(u8 *a,u8 x,u8 n)  //
{
	x=x+0xc0;
	xiemingling(x);  //光标定位到1602第二行第一个位置
	SysTick_delayus(100);
	while(*a&&n--) //
	{
		xieshuju(*a);  //
		SysTick_delayus(100);
		a++;
		x++;//最多写到第十六个
	}
	return;
}
u8 ch[]={"123"};
int main()
{
	float x;
	u32 i,t;
	LED_GPIO_Config();
	GPIOB_init(GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14,GPIO_Mode_Out_PP);
	GPIOA_init(GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,GPIO_Mode_Out_PP);
	ange_USART_init(115200);
	chushihua();
	diyihang(ch,5,3);
	dierhang("5441",8,4);
	while(1)
	{

  }
}

