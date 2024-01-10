#include "oled2.h"
#include "stdlib.h"
#include "ange_systick.h"
#include "ange_spi.h"

//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PA0（SCL） PB3
//              D1   接PA1（SDA） PB5
//              DC   接PA2        PD5
//              CS1  接PA3        PD7
//              FS0  接PA4        PB4
//              CS2  接PA5        PD6

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_Init(void)
** 功能描述: OLED初始化
** 参数描述：无
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD,ENABLE);//使能A端口时钟
//模拟SPI	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入模式
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	  //初始化GPIOA
	

 	GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

	Delay_ms_OLED2(200);
	
	OLED_WR_Byte(0xAE,OLED_CMD); /*display off*/ 
	OLED_WR_Byte(0x02,OLED_CMD); /*set lower column address*/ 
	OLED_WR_Byte(0x10,OLED_CMD); /*set higher column address*/ 
	OLED_WR_Byte(0x40,OLED_CMD); /*set display start line*/ 
	OLED_WR_Byte(0xB0,OLED_CMD); /*set page address*/
	OLED_WR_Byte(0x81,OLED_CMD); /*contract control*/ 
	OLED_WR_Byte(0xcf,OLED_CMD); /*128*/ 
	OLED_WR_Byte(0xA1,OLED_CMD); /*set segment remap*/ 
	OLED_WR_Byte(0xA6,OLED_CMD); /*normal / reverse*/ 
	OLED_WR_Byte(0xA8,OLED_CMD); /*multiplex ratio*/ 
	OLED_WR_Byte(0x3F,OLED_CMD); /*duty = 1/64*/ 
	OLED_WR_Byte(0xad,OLED_CMD); /*set charge pump enable*/ 
	OLED_WR_Byte(0x8b,OLED_CMD); /* 0x8B 内供 VCC */ 
	OLED_WR_Byte(0x33,OLED_CMD); /*0X30---0X33 set VPP 9V */ 
	OLED_WR_Byte(0xC8,OLED_CMD); /*Com scan direction*/ 
	OLED_WR_Byte(0xD3,OLED_CMD); /*set display offset*/ 
	OLED_WR_Byte(0x00,OLED_CMD); /* 0x20 */ 
	OLED_WR_Byte(0xD5,OLED_CMD); /*set osc division*/ 
	OLED_WR_Byte(0x80,OLED_CMD); 
	OLED_WR_Byte(0xD9,OLED_CMD); /*set pre-charge period*/ 
	OLED_WR_Byte(0x1f,OLED_CMD); /*0x22*/ 
	OLED_WR_Byte(0xDA,OLED_CMD); /*set COM pins*/ 
	OLED_WR_Byte(0x12,OLED_CMD); 
	OLED_WR_Byte(0xdb,OLED_CMD); /*set vcomh*/ 
	OLED_WR_Byte(0x40,OLED_CMD);
	OLED_Clear();
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/
	
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	//z	qdelay_xms(200);
}

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_ColorTurn(u8 i)
** 功能描述: 反显函数
** 参数描述：i
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_ColorTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xA6,OLED_CMD);//正常显示
	}
	if(i==1)
	{
		OLED_WR_Byte(0xA7,OLED_CMD);//反色显示
	}
}

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_DisplayTurn(u8 i)
** 功能描述: 显示旋转180度
** 参数描述：i
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_DisplayTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xC8,OLED_CMD);//正常显示
		OLED_WR_Byte(0xA1,OLED_CMD);
	}
	if(i==1)
	{
		OLED_WR_Byte(0xC0,OLED_CMD);//反转显示
		OLED_WR_Byte(0xA0,OLED_CMD);
	}
}

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_DisPlay_On(void)
** 功能描述: 开始显示
** 参数描述：i
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x14,OLED_CMD);//开启电荷泵
	OLED_WR_Byte(0xAF,OLED_CMD);//点亮屏幕
}
/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_DisPlay_Off(void)
** 功能描述: 关闭显示
** 参数描述：i
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x10,OLED_CMD);//关闭电荷泵
	OLED_WR_Byte(0xAE,OLED_CMD);//关闭屏幕
}


/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_WR_Byte(u8 dat,u8 cmd)
** 功能描述: OLED写入一个字节
** 参数描述：dat--数据，cmd-入命令还是数据
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_WR_Byte(u8 dat,u8 cmd)
{			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	Delay_us_OLED2(1);
 
	SPI3_ReadWriteByte(dat);
  Delay_us_OLED2(1);	
	OLED_CS_Set();
	OLED_DC_Set();   	  
}

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_Clear(void)
** 功能描述: 屏幕清空
** 参数描述： 
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	 	 OLED_WR_Byte(0xb0+i,OLED_CMD);//设置页地址
	   OLED_WR_Byte(0x10,OLED_CMD);  //设置列地址的高4位
	   OLED_WR_Byte(0x02,OLED_CMD);  //设置列地址的低4位
	   for(n=0;n<128;n++)
		 {
			 OLED_WR_Byte(0x00,OLED_DATA);//清除所有数据
		 }
  }
}

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_address(u8 x,u8 y)
** 功能描述: 设置起始地址
** 参数描述： xy-起始坐标
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_address(u8 x,u8 y)
{
	x+=2;
	OLED_WR_Byte(0xb0+y,OLED_CMD);              //设置页地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);  //设置列地址的高4位
	OLED_WR_Byte((x&0x0f),OLED_CMD);            //设置列地址的低4位
}

//显示128x64点阵图像
void OLED_Display_128x64(u8 *dp)
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_address(0,i);
		for(j=0;j<128;j++)
		{
			OLED_WR_Byte(*dp,OLED_DATA); //写数据到OLED,每写完一个8位的数据后列地址自动加1
		
			dp++;
    }
  }
}
/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_Display_16x16(u8 x,u8 y,u8 *dp)
** 功能描述: 显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标
** 参数描述： xy-起始坐标，*dp--
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/

void OLED_Display_16x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<16;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);  //写数据到OLED,每写完一个8位的数据后列地址自动加1
		  //UART4_Put_Char('A');
			dp++;

    }
		y++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_Display_8x16(u8 x,u8 y,u8 *dp)
** 功能描述: //显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标
** 参数描述： xy-起始坐标，*dp--
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/

void OLED_Display_8x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);   //写数据到LCD,每写完一个8位的数据后列地址自动加1
			//UART4_Put_Char(*dp);
			dp++;
    }
		y++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_Display_5x7(u8 x,u8 y,u8 *dp)
** 功能描述: //显示5*7点阵图像、ASCII, 或5x7点阵的自造字符、其他图标
** 参数描述： xy-起始坐标，*dp--
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/

void OLED_Display_5x7(u8 x,u8 y,u8 *dp)
{
	u8 i;
  OLED_address(x,y);
	for(i=0;i<6;i++)
	{
		OLED_WR_Byte(*dp,OLED_DATA);
		dp++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** 函数名称: void Send_Command_to_ROM(u8 dat)
** 功能描述: //送指令到晶联讯字库IC
** 参数描述： dat--写入命令
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/

void Send_Command_to_ROM(u8 dat)
{
	   SPI3_ReadWriteByte(dat);
}
/*::::::::::::::::::::::::::::::::::::
** 函数名称: u8 Get_data_from_ROM(void)
** 功能描述: //从晶联讯字库IC中取汉字或字符数据（1个字节）
** 参数描述： dat--写入命令
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/

u8 Get_data_from_ROM(void)
{
	return SPI3_ReadWriteByte(0xFF);
}



/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen)
** 功能描述: //从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pbuff的地址
//连续读取
** 参数描述： 
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen)
{
	u8 i;
	OLED_ROM_CS_Clr();
	Delay_us_OLED2(5);
	Send_Command_to_ROM(0x03);
	Send_Command_to_ROM(addrHigh);
	Send_Command_to_ROM(addrMid);
	Send_Command_to_ROM(addrLow);
	for(i=0;i<DataLen;i++)
	{
		*(pbuff+i)=Get_data_from_ROM();
	//	printf("%d ",*(pbuff+i));
  }
	OLED_ROM_CS_Set();
}


/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_Display_GB2312_string(u8 x,u8 y,u8 *text)
** 功能描述: 显示GB2312汉字
** 参数描述：  
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_Display_GB2312_string(u8 x,u8 y,u8 *text)
{
	u32 fontaddr=0;
	u8 i=0;
	u8 addrHigh,addrMid,addrLow;
	u8 fontbuf[32];
	while(text[i]>0x00)
	{
		if((text[i]>=0xb0)&&(text[i]<=0xf7)&&(text[i+1]>=0xa1))
		{
			//国标简体（GB2312）汉字在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr=(text[i]-0xb0)*94;
			fontaddr+=(text[i+1]-0xa1)+846;
			fontaddr=fontaddr*32;
			
			addrHigh=(fontaddr&0xff0000)>>16;   //地址的高8位,共24位
			addrMid=(fontaddr&0xff00)>>8;       //地址的中8位,共24位
			addrLow=(fontaddr&0xff);            //地址的低8位,共24位
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32);
			//取32个字节的数据，存到"fontbuf[32]"
			
			OLED_Display_16x16(x,y,fontbuf);
			//显示汉字到LCD上，y为页地址，x为列地址，fontbuf[]为数据
			x+=16;
			i+=2;
    }
		else if((text[i]>=0xa1)&&(text[i]<=0xa3)&&(text[i+1]>=0xa1))
		{
			
			fontaddr=(text[i]-0xa1)*94;
			fontaddr+=(text[i+1]-0xa1);
			fontaddr=fontaddr*32;
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=(fontaddr&0xff);
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32);
			OLED_Display_16x16(x,y,fontbuf);
			x+=16;
			i+=2;
    }
		else if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			unsigned char fontbuf[16];
			fontaddr=(text[i]-0x20);
			fontaddr=(unsigned long)(fontaddr*16);
			fontaddr=(unsigned long)(fontaddr+0x3cf80);
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=fontaddr&0xff;
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16);
			OLED_Display_8x16(x,y,fontbuf);
			x+=8;
			i+=1;
    }
		else 
			i++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_Display_string_5x7(u8 x,u8 y,u8 *text)
** 功能描述: 显示GB2312汉字
** 参数描述：  
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_Display_string_5x7(u8 x,u8 y,u8 *text)
{
	u32 fontaddr=0;
	u8 i=0;
	u8 addrHigh,addrMid,addrLow;
	while(text[i]>0x00)
	{
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			u8 fontbuf[8];
			fontaddr=(text[i]-0x20);
			fontaddr=(unsigned long)(fontaddr*8);
			fontaddr=(unsigned long)(fontaddr+0x3bfc0);
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=fontaddr&0xff;
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,8);
			OLED_Display_5x7(x,y,fontbuf);
			x+=6;
			i+=1;
    }
		else 
			i++;
  }
}

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void OLED_ShowNum(u8 x,u8 y,float num1,u8 len)
** 功能描述: 显示2个小数点float
** 参数描述：  
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void OLED_ShowNum(u8 x,u8 y,float num1,u8 len)
{
	u8 i;
	u32 t,num;
	x=x+len*8+8;//要显示的小数最低位的横坐标
	num=num1*100;//将小数左移两位并转化为整数
	OLED_Display_GB2312_string(x-24,y,".");//显示小数点
	for(i=0;i<len;i++)
	{
		t=num%10;//取个位数的数值
		num=num/10;//将整数右移一位
		x-=8;
		if(i==2){x-=8;}//当显示出来两个小数之后，空出小数点的位置
		switch(t)
		{
			case 0 :OLED_Display_GB2312_string(x,y,"0");break;
			case 1 :OLED_Display_GB2312_string(x,y,"1");break;
			case 2 :OLED_Display_GB2312_string(x,y,"2");break;
			case 3 :OLED_Display_GB2312_string(x,y,"3");break;
			case 4 :OLED_Display_GB2312_string(x,y,"4");break;
			case 5 :OLED_Display_GB2312_string(x,y,"5");break;
			case 6 :OLED_Display_GB2312_string(x,y,"6");break;
			case 7 :OLED_Display_GB2312_string(x,y,"7");break;
			case 8 :OLED_Display_GB2312_string(x,y,"8");break;
			case 9 :OLED_Display_GB2312_string(x,y,"9");break;
		}
	}
}



