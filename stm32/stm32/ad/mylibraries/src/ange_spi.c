#include "ange_spi.h"
#include "ange_usart.h"
#define ange_SPI_timeout 1000
void ange_SPI_GPIO_Congfig()
{
	GPIO_InitTypeDef gpioinit;
	//////开启spi的时钟
	ange_SPI_APBxClock(ange_SPI_CLK,ENABLE);
	///开启gpio时钟
	ange_SPI_CS_APBxClock(ange_SPI_CS_CLK|ange_SPI_SCK_CLK|ange_SPI_MISO_CLK|ange_SPI_MISI_CLK,ENABLE);
	///cs
	gpioinit.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioinit.GPIO_Pin=ange_SPI_CS_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_SPI_CS_PORT,&gpioinit);
	//
	gpioinit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioinit.GPIO_Pin=ange_SPI_SCK_Pin;
	GPIO_Init(ange_SPI_SCK_PORT,&gpioinit);
	///
	gpioinit.GPIO_Pin=ange_SPI_MISO_Pin;
	GPIO_Init(ange_SPI_MISO_PORT,&gpioinit);
	//
	gpioinit.GPIO_Pin=ange_SPI_MISI_Pin;
	GPIO_Init(ange_SPI_MISI_PORT,&gpioinit);
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
