/*********************************************************************************************
底层驱动：数码管底层驱动
模板制作：
程序名：		STM32通用模板-LJX
编写人：		李佳勋
编写时间：2021年07月07日
硬件支持：STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　
修改日志：无
说明：无
*********************************************************************************************/
#include "shumaguan.h"

u8 numtable[] = {0x82,0xee,0x07,0x46,0x6A,0x52,0x12,0xE6,0x02,0x42,0x22,0x02,0x93,0x82,0x13,0x33,0x2A,0x9b,0x2a,0x23};
/////////////////0000,1111,2222,3333,4444,5555,6666,7777,8888,9999,AAAA,BBBB,CCCC,DDDD,EEEE,FFFF,HHHH,LLLL,UUUU,PPPP//断码对应数字
/////////////////0000,1111,2222,3333,4444,5555,6666,7777,8888,9999,1010,1111,1212,1313,1414,1515,1616,1717,1818,1919//在数组中对应位置

u8 numtable_pot[] = {0x80,0xec,0x05,0x44,0x68,0x50,0x10,0xE4,0x00,0x40};
/////////////////////0.0.,1.1.,2.2.,3.3.,4.4.,5.5.,6.6.,7.7.,8.8.,9.9.//数字加点显示


void ShuMaGuan_Init(void)	//数码管初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);//开启时钟
	GPIO_InitStructure.GPIO_Pin = DATA_595 | STCP_595 | SHCP_595;																			//选择端口号
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;																									//选择IO口工作模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;																									//选择IO口接口速度
	GPIO_Init(SHUMAGUANPORT,&GPIO_InitStructure);																											//将以上设置写入IO口
}


//数码管显示从左到右依次  F E D C B A，写入数据顺序为 A B C D E F
void display(u8 a,u8 b,u8 c,u8 d,u8 e,u8 f)
{
	u8 i,num,n;
	GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
	GPIO_WriteBit(SHUMAGUANPORT,STCP_595,(BitAction)(0));
////////////////////////A位//////////////////////////////////////
	num = numtable[a];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));//SH_CP一个上升沿
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////B位//////////////////////////////////////
	num = numtable[b];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////C位//////////////////////////////////////
	num = numtable[c];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////D位//////////////////////////////////////
	num = numtable[d];
		for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////E位//////////////////////////////////////
	num = numtable[e];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}
////////////////////////F位//////////////////////////////////////
	num = numtable[f];
	for(i = 0; i < 8; i++)
	{
		n=num & 0x80;
		if(n>0)
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(1));
		else
			GPIO_WriteBit(SHUMAGUANPORT,DATA_595,(BitAction)(0));

		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(1));
		SysTick_delayus(1);
		GPIO_WriteBit(SHUMAGUANPORT,SHCP_595,(BitAction)(0));
			num <<= 1;
	}

	GPIO_WriteBit(SHUMAGUANPORT,STCP_595,(BitAction)(1));//数据全部写完，给STCP一个上升沿
  SysTick_delayus(1);
	GPIO_WriteBit(SHUMAGUANPORT,STCP_595,(BitAction)(0));
}
/*安哥添加函数*/
void ange_595_GPIO_init()
{
	GPIO_InitTypeDef gpioinit;
	RCC_APB2PeriphClockCmd(ange_DATA595_GPIO_CLK|ange_STCP595_GPIO_CLK|ange_SHCP595_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_Out_OD;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_DATA595_GPIO_Pin;
	GPIO_Init(ange_DATA595_GPIO_PORT,&gpioinit);
	
	gpioinit.GPIO_Pin=ange_STCP595_GPIO_Pin;
	GPIO_Init(ange_STCP595_GPIO_PORT,&gpioinit);
	
	gpioinit.GPIO_Pin=ange_SHCP595_GPIO_Pin;
	GPIO_Init(ange_SHCP595_GPIO_PORT,&gpioinit);
}
#define shumanum 6
u8 shuma595[shumanum]={1,2,3,4,5,6};

//学长的
//static u8 duanma[]={0x28,0xBD,0x58,0x19,0x8D,0x0B,0x0A,0xB9,0x08,0x09,0xff,0x88,0x0E,0x6A,0x1C,0x4A,0xCA,0xdf};//点为f7

//佳勋板子
//static u8 duanma[]={0x82,0xee,0x07,0x46,0x6A,0x52,0x12,0xE6,0x02,0x42,0x22,0x02,0x93,0x82,0x13,0x33,0x2A,0x9b,0x2a,0x23};

//学弟打板 a-a bb cc dd ee ff gg hh  段码0-9 熄灭 a-f -
static u8 duanma[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xff,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xbf}; //dian为7f  显示左方为第一个

//extern s32   doppler_speed_s32;//多普勒速度用来判断速度是否为零
void ange_595_xianshi()
{
	u8 i,j,x;
	data595=0;
	shcp595=0;
	stcp595=0;
	for(i=0;i<shumanum;i++)
	{
//	x=shuma595[shumanum-i];
//		x=shuma595[5-i];
		x=shuma595[i];
		x=duanma[x];
		for(j=0;j<8;j++)
		{
			if(x&0x80)
			{
				data595=1;
			}
			else
			{
				data595=0;
			}
			shcp595=1;
			SysTick_delayus(1);
			shcp595=0;
			x<<=1;
		}
	}
	stcp595=1;
	SysTick_delayus(1);
	stcp595=0;
}



/* GPIO 库函数			PDF电子版122/368页
**************************************************************************************************************************
GPIO_DeInit  			将外设 GPIOx 寄存器重设为缺省值
GPIO_AFIODeInit  	将复用功能（重映射事件控制和 EXTI 设置）重设为缺省值
GPIO_Init  				根据 GPIO_InitStruct 中指定的参数初始化外设 GPIOx 寄存器
GPIO_StructInit  	把 GPIO_InitStruct 中的每一个参数按缺省值填入
GPIO_ReadInputDataBit  	读取指定端口管脚的输入
GPIO_ReadInputData  		读取指定的 GPIO 端口输入
GPIO_ReadOutputDataBit  读取指定端口管脚的输出
GPIO_ReadOutputData  		读取指定的 GPIO 端口输出
GPIO_SetBits  					设置指定的数据端口位
GPIO_ResetBits  				清除指定的数据端口位
GPIO_WriteBit  					设置或者清除指定的数据端口位
GPIO_Write  						向指定 GPIO 数据端口写入数据
GPIO_PinLockConfig  		锁定 GPIO 管脚设置寄存器
GPIO_EventOutputConfig  选择 GPIO 管脚用作事件输出
GPIO_EventOutputCmd  		使能或者失能事件输出
GPIO_PinRemapConfig  		改变指定管脚的映射
GPIO_EXTILineConfig  		选择 GPIO 管脚用作外部中断线路
**************************************************************************************************************************/

/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/

/*GPIO_Speed可供选择的值
typedef enum
{

  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz,
  GPIO_Speed_50MHz

}GPIOSpeed_TypeDef;
*/
