#include "ads8361.h"
#include "ange_systick.h"
#include "ange_usart.h"
float ads8361a0,ads8361a1,ads8361b0,ads8361b1;
void ads8361_init()   //焊接测试
{
	GPIO_InitTypeDef gpioinit;
	
	RCC_APB2PeriphClockCmd(ads8361_RD_GPIO_CLK|ads8361_CS_GPIO_CLK|ads8361_OUTB_GPIO_CLK|ads8361_A0_GPIO_CLK,ENABLE);//使能PORTA,PORTE时钟
	//RD
	gpioinit.GPIO_Pin  = ads8361_RD_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
 	GPIO_Init(ads8361_RD_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
	//CS
		gpioinit.GPIO_Pin  = ads8361_CS_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
 	GPIO_Init(ads8361_CS_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
	//clk
	gpioinit.GPIO_Pin  = ads8361_CLOCK_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
 	GPIO_Init(ads8361_CLOCK_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
  //A0
	gpioinit.GPIO_Pin  = ads8361_A0_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
 	GPIO_Init(ads8361_A0_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
	//outa、
	gpioinit.GPIO_Pin  = ads8361_OUTA_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空输入
 	GPIO_Init(ads8361_OUTA_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
	//////outb
	gpioinit.GPIO_Pin  = ads8361_OUTB_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空输入
 	GPIO_Init(ads8361_OUTB_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
	////MO 
		gpioinit.GPIO_Pin  = ads8361_M0_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //设置成浮空输入
 	GPIO_Init(ads8361_M0_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
	//M1
  gpioinit.GPIO_Pin  = ads8361_M1_GPIO_Pin;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP; //设置成浮空输入
 	GPIO_Init(ads8361_M1_GPIO_PORT, &gpioinit);//初始化GPIOE2,3,4
//	M0=0;M1=0;A0=0; //模式一  A0,B0双通道  A和B输出  未成功
//	MO=0;M1=0;A0=1; //模式一  A1,B1双通道  A和B输出
//	MO=0;M1=1;A0=0; //模式二  A0,B0双通道  A输出
//	MO=0;M1=1;A0=1; //模式二  A1,B1双通道  A输出
//	MO=1;M1=0;A0=0; //模式三  A0,A1,B0,B1四通道  A和B输出
//	M0=1;M1=1;A0=1; //模式四  A0,A1,B0,B1四通道  A输出(顺序为A0,B0,A1,B1)
	A0=1;
}


//int flag=0;
u32 ads8361_reada(void)
{
	unsigned char i;
	u32 A_Data = 0;
	
	CS=0;
	RD = 1;
	CLOCK = 1;

	CLOCK = 0;
	RD = 0;
	
	for(i = 0;i < 18;i ++) //读取16位AD转换后的值，高位在前，所以每读一位是左移
	{
			A_Data <<= 1;
			CLOCK = 1;
			if(ADATA)
			{A_Data |= 0x01;}
			CLOCK = 0;
	}
	
	CLOCK = 1;

	CLOCK = 0;
	return A_Data;
}
u32 ads8361_readb(void)
{
	unsigned char i;
	u32 bdata = 0;
	
	CS=0;
	RD = 1;
	CLOCK = 1;

	CLOCK = 0;
	RD = 0;
	
	for(i = 0;i < 18;i ++) //读取16位AD转换后的值，高位在前，所以每读一位是左移
	{
			bdata <<= 1;
			CLOCK = 1;
			if(BDATA)
			{bdata |= 0x01;}
			CLOCK = 0;
	}
	
	CLOCK = 1;
	CLOCK = 0;
	
	return bdata;
}
uint64_t ads8361_readab(void)
{
	unsigned char i;
	u32 b = 0,a=0;
	uint64_t x=0;
	CS=0;
	RD = 1;
	CLOCK = 1;
	CLOCK = 0;
	RD = 0;
	for(i = 0;i < 18;i ++) //读取16位AD转换后的值，高位在前，所以每读一位是左移
	{
			b <<= 1;
		  a<<=1;
			CLOCK = 1;
			if(BDATA)
			{b |= 0x01;}
			if(ADATA)
			{
				a|=0x01;
			}
			CLOCK = 0;
	}
	
	CLOCK = 1;
	CLOCK = 0;
	x=a; //adata<<32不可以
	x<<=32;
	x+=b; //
	return x;
}
void ads8361_read00a0() //带入参数为 A0状态
{
	 s32 ch1;
	M0=0;
	M1=0;
	A0=0;
		ch1=ads8361_reada();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361a0=ch1;
//			printf("%x ",ch1);
}
void ads8361_read00b0() //带入参数为 A0状态
{
	M0=0;
	M1=0;
	 s32 ch1;
	A0=0;
		ch1=ads8361_readb();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361b0=ch1;
	
}
void ads8361_read00a1() //带入参数为 A0状态
{
	 s32 ch1;
	A0=1;
	M0=0;
	M1=0;
		ch1=ads8361_reada();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361a1=ch1;
//					printf("%x ",ch1);
}
void ads8361_read00b1() //带入参数为 A0状态
{

	 s32 ch1;
	A0=1;
	M0=0;
	M1=0;
		ch1=ads8361_readb();
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
				ads8361b1=ch1;
}
//	M0=0;M1=0;A0=0; //模式一  A0,B0双通道  A和B输出  无法读出数据
//	MO=0;M1=0;A0=1; //模式一  A1,B1双通道  A和B输出
void ads8361_read00(u8 a) //带入参数为 A0状态
{
	M0=0;
	M1=0;
	uint64_t ch;
	 s32 ch1,ch2;
	if(a==0)
	{
	A0=0;
	}
	else
	{
	A0=1;
	}
		ch=ads8361_readab();
			ch1=ch>>32;
			ch2=ch&0xfffff;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			if(a==0)
			{
				ads8361a0=ch1;  
		  }
			else
			{
				ads8361a1=ch1;
			}
			ch2&=0xffff;
			if(ch2&0x8000)
			{
				ch2&=0x7fff;
				ch2=0x7fff-ch2;
				ch2=-ch2;
			}
			if(a==0)
			{
				ads8361b0=ch2;  
		  }
			else
			{
				ads8361b1=ch2;
			}
}
//	MO=0;M1=1;A0=0; //模式二  A0,B0双通道  A输出 数据会间歇出错
//	MO=0;M1=1;A0=1; //模式二  A1,B1双通道  A输出
void ads8361_read01(u8 a) //输入参数为A0状态
{
	u8 i,x;
	s32 ch1;
	M0=0;
	M1=1;
	if(a==0)
	{
		A0=0;
	}
	else
	{
		A0=1;
	}
		for(i=0;i<2;i++)
		{

			ch1=ads8361_reada();

//			if(i==1)
//			{
//				A0=0;
//			}
			x=ch1>>16;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			if(a==0)
			{

				if(x==0)
				ads8361a0=ch1; 
				else
				ads8361b0=ch1;

			}				
			else
			{
				if(x==0)
				ads8361a1=ch1;
				else if(x==1)
				ads8361b1=ch1;
			}
		}
}
//	MO=1;M1=0;A0=0; //模式三  A0,A1,B0,B1四通道  A和B输出
void ads8361_read10() //4通道· ab输出 nice
{
	u8 i,x;
	uint64_t ch;
	s32 ch1,ch2;
	M0=1;
	M1=0;
A0=1;
		for(i=0;i<2;i++)
		{
			ch=ads8361_readab();
			ch1=ch>>32;
			ch2=ch&0xfffff;
			x=ch1>>16;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			if(x==0)
				ads8361a0=ch1;
			else
				ads8361a1=ch1;
			x=ch2>>16;
			ch2&=0xffff;
			if(ch2&0x8000)
			{
				ch2&=0x7fff;
				ch2=0x7fff-ch2;
				ch2=-ch2;
			}
			if(x==0)
				ads8361b0=ch2;
			else
				ads8361b1=ch2;
			
		}
}
//	M0=1;M1=1;A0=1; //模式四  A0,A1,B0,B1四通道  A输出(顺序为A0,B0,A1,B1)
void ads8361_read11() //四通道 a输出 nice
{
	u8 i;
	s32 ch1,x;
	M0=1;M1=1;
	A0=1;
		for(i=0;i<4;i++)
		{
			ch1=ads8361_reada();
//			if(i==3)
//			{
//				CS=1;
//			}
			x=ch1>>16;
			ch1&=0xffff;
			if(ch1&0x8000)
			{
				ch1&=0x7fff;
				ch1=0x7fff-ch1;
				ch1=-ch1;
			}
			switch(x)
			{
				
				case 0:
					ads8361a0=ch1;  
				break;
				case 1:
					ads8361b0=ch1;  
				break;
				case 2:
					ads8361a1=ch1;  
				break;
				case 3:
					ads8361b1=ch1; 
				break;
				default: break;					
			}
		}
}
/////////////俊霖的改版
void ADS8361_Read_01_OUTA(uint32_t CH,uint32_t *data_a_01,uint32_t *data_b_01)//在M0M1=01下，读取A通道的数据
{
	M0=0;
	M1=1;
	uint32_t dat=0,temp=0;
	uint32_t i;
	CLOCK=0;//
  CS=0;
	RD=1;
	CLOCK = 1;
	if(CH==0)
		A0=0;
	else
		A0=1;	
	CLOCK=0;//
	CLOCK = 1;
	RD=0;//RD要放在循环前，放在循环后CH1读不出来
	for(i=0;i<18;i++)
	{
		dat<<=1;
	CLOCK=0;//
		temp=ADATA;
		if(temp==1)
			dat|=1;
CLOCK = 1;
	}
	CLOCK=0;//
	CLOCK = 1;
	CLOCK=0;//
	dat=0;//第一次读出的是没用的数据,直接不要
	
	RD=1;
	CLOCK = 1;
	CLOCK=0;//
	CLOCK = 1;
	RD=0;
	for(i=0;i<18;i++)
	{
		dat<<=1;
	CLOCK=0;//
		temp=ADATA;
		if(temp==1)
			dat|=1;
	CLOCK = 1;
	}
	CLOCK=0;//
	CLOCK = 1;
	CLOCK=0;//
	if((dat&0x30000)==0x00000)//如果标志位是A通道的，则将数据给A
	{*data_a_01=dat;dat=0;}
	else if((dat&0x30000)==0x10000)//如果标志位是B通道的，则将数据给B
	{*data_b_01=dat;dat=0;}
	else
		dat=0;
		
	RD=1;
	CLOCK = 1;
	CLOCK=0;//
	CLOCK = 1;
	RD=0;
	for(i=0;i<18;i++)
	{
		dat<<=1;
	CLOCK=0;//
		temp=ADATA;
		if(temp==1)
			dat|=1;
	CLOCK = 1;
	}
	CLOCK=0;//
	CLOCK = 1;
	CLOCK=0;//
	if((dat&0x30000)==0x00000)//如果标志位是A通道的，则将数据给A
	{*data_a_01=dat;dat=0;}
	else if((dat&0x30000)==0x10000)//如果标志位是B通道的，则将数据给B
	{*data_b_01=dat;dat=0;}
	else
		dat=0;				
	CS=1;
}

