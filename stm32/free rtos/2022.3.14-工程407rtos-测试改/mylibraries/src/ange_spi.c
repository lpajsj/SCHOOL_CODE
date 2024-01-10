#include "ange_spi.h"
#include "ange_usart.h"
#define ange_SPI_timeout 1000
//注意并未进行验证
void ange_SPI_GPIO_Congfig()
{
	GPIO_InitTypeDef gpioinit;
	//////开启spi的时钟
	ange_SPI_APBxClock(ange_SPI_CLK,ENABLE);
	///开启gpio时钟
	ange_SPI_CS_APBxClock(ange_SPI_CS_CLK|ange_SPI_SCK_CLK|ange_SPI_MISO_CLK|ange_SPI_MOSI_CLK,ENABLE);
	///cs
	gpioinit.GPIO_Mode=GPIO_Mode_AF;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpioinit.GPIO_Pin=ange_SPI_CS_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_SPI_CS_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_CS_PORT,ange_SPI_CS_PinSource,GPIO_AF_SPI1);
	//
	gpioinit.GPIO_Mode=GPIO_Mode_AF;
	gpioinit.GPIO_Pin=ange_SPI_SCK_Pin;
	GPIO_Init(ange_SPI_SCK_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_SCK_PORT,ange_SPI_SCK_PinSource,GPIO_AF_SPI1);
	///
	gpioinit.GPIO_Pin=ange_SPI_MISO_Pin;
	GPIO_Init(ange_SPI_MISO_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_MISO_PORT,ange_SPI_MISO_PinSource,GPIO_AF_SPI1);
	//
	gpioinit.GPIO_Pin=ange_SPI_MOSI_Pin;
	GPIO_Init(ange_SPI_MOSI_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI_MOSI_PORT,ange_SPI_MOSI_PinSource,GPIO_AF_SPI1);
}
void ange_SPI_Config()
{
	SPI_InitTypeDef spiinit;
	spiinit.SPI_Mode=SPI_Mode_Master;  //spi的模式 分为主master 和slave
	spiinit.SPI_Direction=SPI_Direction_2Lines_FullDuplex; //传输方向
	spiinit.SPI_DataSize=SPI_DataSize_8b;  //数据形式 8bits 和16bits
	spiinit.SPI_CPOL=SPI_CPOL_High;    //sck空闲电平
	spiinit.SPI_CPHA=SPI_CPHA_2Edge;   //数据操作是在第一个还是第二个变化电平
	spiinit.SPI_NSS=SPI_NSS_Soft;   //cs操作是软件还是硬件控制
	spiinit.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;  //波特率预分频  spi1是在APB2总线上
	spiinit.SPI_FirstBit=SPI_FirstBit_MSB;  //小端模式还是大端模式
	spiinit.SPI_CRCPolynomial=7;   //crc 
	SPI_Init(ange_SPIx,&spiinit);
	SPI_Cmd(ange_SPIx,ENABLE);
}
void ange_SPI_ERROR(u8 x)
{
	printf("spi出错%d",x);
}
u8 ange_SPI_sendbyte(u8 x)
{
	u16 t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(0);
			return 0xff;
		}
	}
	SPI_I2S_SendData(ange_SPIx,x);
	t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPIx);
	return x;
}
u16 ange_SPI_send2byte(u16 x)
{
	u16 t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(0);
			return 0xffff;
		}
	}
	SPI_I2S_SendData(ange_SPIx,x);
	t=ange_SPI_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPIx,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPIx);
	return x;
}
///
#define ange_SPI2_timeout 1000
//注意并未进行验证
void ange_SPI2_GPIO_Congfig()
{
	GPIO_InitTypeDef gpioinit;
	//////开启spi的时钟
	ange_SPI2_APBxClock(ange_SPI2_CLK,ENABLE);
	///开启gpio时钟
	ange_SPI2_CS_APBxClock(ange_SPI2_CS_CLK|ange_SPI2_SCK_CLK|ange_SPI2_MISO_CLK|ange_SPI2_MOSI_CLK,ENABLE);
	///cs
	gpioinit.GPIO_Mode=GPIO_Mode_OUT;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpioinit.GPIO_Pin=ange_SPI2_CS_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(ange_SPI2_CS_PORT,&gpioinit);
//	GPIO_PinAFConfig(ange_SPI_CS_PORT,ange_SPI2_CS_PinSource,GPIO_AF_SPI2);
	//
	gpioinit.GPIO_Mode=GPIO_Mode_AF;
	gpioinit.GPIO_Pin=ange_SPI2_SCK_Pin;
	GPIO_Init(ange_SPI2_SCK_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI2_SCK_PORT,ange_SPI2_SCK_PinSource,GPIO_AF_SPI2);
	///
	gpioinit.GPIO_Pin=ange_SPI2_MISO_Pin;
	GPIO_Init(ange_SPI2_MISO_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI2_MISO_PORT,ange_SPI2_MISO_PinSource,GPIO_AF_SPI2);
	//
	gpioinit.GPIO_Pin=ange_SPI2_MOSI_Pin;
	GPIO_Init(ange_SPI2_MOSI_PORT,&gpioinit);
	GPIO_PinAFConfig(ange_SPI2_MOSI_PORT,ange_SPI2_MOSI_PinSource,GPIO_AF_SPI2);
}
void ange_SPI2_Config()
{
	SPI_InitTypeDef spiinit;
	spiinit.SPI_Mode=SPI_Mode_Master;  //spi的模式 分为主master 和slave
	spiinit.SPI_Direction=SPI_Direction_2Lines_FullDuplex; //传输方向
	spiinit.SPI_DataSize=SPI_DataSize_8b;  //数据形式 8bits 和16bits
	spiinit.SPI_CPOL=SPI_CPOL_Low;    //MS5611需要
	spiinit.SPI_CPHA=SPI_CPHA_1Edge;   //MS5611需要
//	spiinit.SPI_CPOL=SPI_CPOL_High;    //sck空闲电平
//	spiinit.SPI_CPHA=SPI_CPHA_2Edge;   //数据操作是在第一个还是第二个变化电平
	spiinit.SPI_NSS=SPI_NSS_Soft;   //cs操作是软件还是硬件控制
	spiinit.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;  //波特率预分频  spi1是在APB2总线上
	spiinit.SPI_FirstBit=SPI_FirstBit_MSB;  //小端模式还是大端模式
	spiinit.SPI_CRCPolynomial=7;   //crc 
	SPI_Init(ange_SPI2x,&spiinit);
	SPI_Cmd(ange_SPI2x,ENABLE);
}
void ange_SPI2_ERROR(u8 x)
{
	printf("spi出错%d",x);
}
u8 ange_SPI2_sendbyte(u8 x)
{
	u16 t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(0);
			return 0xff;
		}
	}
	SPI_I2S_SendData(ange_SPI2x,x);
	t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPI2x);
	return x;
}
u16 ange_SPI2_send2byte(u16 x)
{
	u16 t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(0);
			return 0xffff;
		}
	}
	SPI_I2S_SendData(ange_SPI2x,x);
	t=ange_SPI2_timeout;
	while(SPI_I2S_GetFlagStatus(ange_SPI2x,SPI_I2S_FLAG_RXNE)==RESET)
	{
		if((t--)==0)
		{
			ange_SPI2_ERROR(1);
			return 1;
		}
	}
	x=SPI_I2S_ReceiveData(ange_SPI2x);
	return x;
}
///spi3复制其他的

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void SPI3_Init(void)
** 功能描述: SPI3初始化
** 参数描述： 
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void SPI3_Init(void)
{	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);//使能SPI1时钟
 
  //GPIOFB3,4,5初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI3); //PB3复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI3); //PB4复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI3); //PB5复用为 SPI1
 
	//这里只针对SPI口初始化
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);//复位SPI1
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,DISABLE);//停止复位SPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为低电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI3, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI3, ENABLE); //使能SPI外设	
}   
/*::::::::::::::::::::::::::::::::::::
** 函数名称: void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
** 功能描述: 设置SPI3传输速度
** 参数描述： SPI_BaudRatePrescaler时钟分频系数
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI3->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI3->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI3,ENABLE); //使能SPI1
} 
/*::::::::::::::::::::::::::::::::::::
** 函数名称: u8 SPI3_ReadWriteByte(u8 TxData)
** 功能描述: SPI3发送一个字节
** 参数描述：TxData发送字节
** 作  　者: David
** 日　  期: 2018年04月19日
::::::::::::::::::::::::::::::::::::::*/
u8 SPI3_ReadWriteByte(u8 TxData)
{		 			 

  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){;}//等待发送区空  
	
	SPI_I2S_SendData(SPI3, TxData); //通过外设SPIx发送一个byte  数据
		
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){;} //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPI3); //返回通过SPIx最近接收的数据		    
}




