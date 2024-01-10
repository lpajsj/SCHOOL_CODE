#include "spi.h"
#include "MultiRotor_systime.H"
#include "sys.h"
#include "tlc2543.h"
#include "flash.h"

 
//以下是SPI模块的初始化代码，配置成主机模式，访问SD Card/W25Q64/NRF24L01						  
//SPI口初始化
//这里针是对SPI2的初始化

void SPI2_Init(void)
{
 	//GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	//RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2时钟使能 	
 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15复用推挽输出 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB

// 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15上拉

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI2, ENABLE); //使能SPI外设
	
	SPI2_ReadWriteByte(0xff);//启动传输		 
 
}   
//SPI 速度设置函数
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分频   
//SPI_BaudRatePrescaler_8   8分频   
//SPI_BaudRatePrescaler_16  16分频  
//SPI_BaudRatePrescaler_256 256分频 
  
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	//设置SPI2速度 
	SPI_Cmd(SPI2,ENABLE); 

} 

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
}

/***************************SPI1*************************/

void SPI1_Init(void)
{
		SPI_InitTypeDef  SPI_InitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
      
    /* PA5-SCK PA7-MOSI */  
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5 |GPIO_Pin_7 ;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    /*PA4-CS0*/  
    GPIO_SetBits(GPIOA, GPIO_Pin_4);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);	
  
	 /*PE7-CS1*/  
    GPIO_SetBits(GPIOE, GPIO_Pin_7);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_Init(GPIOE, &GPIO_InitStructure);  
		
    /*PA6-MISO*/  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    /* SPI1 configuration ???SPI??????TLC2543????*/  
    SPI_Cmd(SPI1, DISABLE);                                                 //?????,????MODE  
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      //?????  
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                           //?  
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                      //16?  
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                              //???????????  
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                            //?????????????  
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               //??NSS,?????????  
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;    //128??  
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      //????  
      
    SPI_Init(SPI1, &SPI_InitStructure);  
    SPI_Cmd(SPI1, ENABLE); 
		
		SPI_FLASH_CS_HIGH();        //sst25 CS信号 高
		SPI_TLC2543_CS_HIGH();			//tlc2543 CS信号 高
		
// 	GPIO_InitTypeDef GPIO_InitStructure;
//  SPI_InitTypeDef  SPI_InitStructure;

//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1,  ENABLE );//SPI1时钟使能 	
 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15复用推挽输出 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB

// 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15上拉

//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;		//定义波特率预分频的值:波特率预分频值为128
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
//	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
//	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
// 
//	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
	SPI1_ReadWriteByte(0xff);//启动传输		 
}   
//SPI 速度设置函数
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分频   
//SPI_BaudRatePrescaler_8   8分频   
//SPI_BaudRatePrescaler_16  16分频  
//SPI_BaudRatePrescaler_256 256分频 
  
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI1->CR1&=0XFFC7;
	SPI1->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE); 

} 

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
//	GPIO_ResetBits(GPIOA, GPIO_Pin_4);	                          
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  		
//	GPIO_SetBits(GPIOA, GPIO_Pin_4);  
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据					    
}




/****************************MAX6675********************************/

void Init_MAX6675_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TC1_SCK ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(MAX6675_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = TC1_SO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//下拉输入
	GPIO_Init(MAX6675_PORT, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE, GPIO_Pin_0); //CS=1;
	GPIO_SetBits(GPIOE, GPIO_Pin_1); //CS=1;
	GPIO_SetBits(GPIOE, GPIO_Pin_2); //CS=1;
	GPIO_SetBits(GPIOE, GPIO_Pin_3); //CS=1;
	GPIO_SetBits(GPIOB, GPIO_Pin_12);//CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_8); //CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_9); //CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_10);//CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_11);//CS=1;

	GPIO_ResetBits(MAX6675_PORT, TC1_SCK );//SCK=0;
	GPIO_SetBits(MAX6675_PORT, TC1_SO);

}

unsigned char MAX6675(unsigned char channel)
{
	u16 temp=0;
	u8 i,temp1=0;
	switch(channel)
	{
		case 1:GPIO_ResetBits(GPIOE, GPIO_Pin_0); break;//CS=1;
		case 2:GPIO_ResetBits(GPIOE, GPIO_Pin_1); break;//CS=2;
		case 3:GPIO_ResetBits(GPIOE, GPIO_Pin_2); break;//CS=3;
		case 4:GPIO_ResetBits(GPIOE, GPIO_Pin_3); break;//CS=4;
		case 5:GPIO_ResetBits(GPIOB, GPIO_Pin_12);break;//CS=5;
		case 6:GPIO_ResetBits(GPIOD, GPIO_Pin_8); break;//CS=6;
		case 7:GPIO_ResetBits(GPIOD, GPIO_Pin_9); break;//CS=7;
		case 8:GPIO_ResetBits(GPIOD, GPIO_Pin_10);break;//CS=8;
		case 9:GPIO_ResetBits(GPIOD, GPIO_Pin_11);break;//CS=9;
		default: temp=0;   break;
	}
	if(DIN)	temp|=0x0001;
	Delay_us(10);
	for(i=0;i<=14;i++)
	{
		SCLK_H;									//read data SO
		Delay_us(10);
		temp<<=1;
		if(DIN)
		temp|=0x0001;
		SCLK_L;
		Delay_us(10);
	}
	temp<<=1;
	if(DIN)	temp|=0x0001;
	Delay_us(10);
	if(temp&0x0004) temp=0;
	temp=(temp>>5);
	switch(channel)
	{
		case 1:
			GPIO_SetBits(GPIOE, GPIO_Pin_0);
			temp1=(unsigned char)(temp); 				//冷却液出水温度
		break;//CS=1;
		case 2:
			GPIO_SetBits(GPIOE, GPIO_Pin_1);
			temp1=(unsigned char)(temp>>2); 		//左排气管温度
		break;//CS=2;
		case 3:
			GPIO_SetBits(GPIOE, GPIO_Pin_2);
			temp1=(unsigned char)(temp>>1);			//左缸体温度
		break;//CS=3;
		case 4:
			GPIO_SetBits(GPIOE, GPIO_Pin_3);
			temp1=(unsigned char)(temp>>2); 		//左缸头温度
		break;//CS=4;
		case 5:
			GPIO_SetBits(GPIOB, GPIO_Pin_12);
			temp1=(unsigned char)(temp);				//冷却液进水温度
		break;//CS=5;
		case 6:
			GPIO_SetBits(GPIOD, GPIO_Pin_8); 
			temp1=(unsigned char)(temp);				//滑油温度
		break;//CS=6;
		case 7:
			GPIO_SetBits(GPIOD, GPIO_Pin_9); 
			temp1=(unsigned char)(temp>>2);			//右排气管温度
		break;//CS=7;
		case 8:
			GPIO_SetBits(GPIOD, GPIO_Pin_10);
			temp1=(unsigned char)(temp>>1);			//右缸体温度
		break;//CS=8;
		case 9:
			GPIO_SetBits(GPIOD, GPIO_Pin_11);
			temp1=(unsigned char)(temp>>2);			//右缸头温度
		break;//CS=9;
		default: 
			temp1=0;   
		break;
	}
//	temp1=temp;
//	Delay_ms(2);
	return temp1;
}

