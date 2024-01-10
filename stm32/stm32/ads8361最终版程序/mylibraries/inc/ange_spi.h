#ifndef  _ange_spi_h
#define  _ange_spi_h
#include "stm32f10x.h"
////spi
#define ange_SPIx SPI1
#define ange_SPI_APBxClock RCC_APB2PeriphClockCmd
#define ange_SPI_CLK       RCC_APB2Periph_SPI1
//GPIO
///CS
#define ange_SPI_CS_APBxClock   RCC_APB2PeriphClockCmd
#define ange_SPI_CS_CLK         RCC_APB2Periph_GPIOA
#define ange_SPI_CS_PORT        GPIOA
#define ange_SPI_CS_Pin         GPIO_Pin_4
#define ange_SPI_CS1            GPIO_SetBits(ange_SPI_CS_PORT,ange_SPI_CS_Pin);
#define ange_SPI_CS0            GPIO_ResetBits(ange_SPI_CS_PORT,ange_SPI_CS_Pin);
///CLK
#define ange_SPI_SCK_APBxClock  RCC_APB2PeriphClockCmd
#define ange_SPI_SCK_CLK        RCC_APB2Periph_GPIOA
#define ange_SPI_SCK_PORT       GPIOA
#define ange_SPI_SCK_Pin       GPIO_Pin_5
//MISO 主机输入，从机输出
#define ange_SPI_MISO_APBxClock  RCC_APB2PeriphClockCmd
#define ange_SPI_MISO_CLK        RCC_APB2Periph_GPIOA
#define ange_SPI_MISO_PORT       GPIOA
#define ange_SPI_MISO_Pin       GPIO_Pin_6
//MISI 主机输出，从机输入
#define ange_SPI_MISI_APBxClock  RCC_APB2PeriphClockCmd
#define ange_SPI_MISI_CLK        RCC_APB2Periph_GPIOA
#define ange_SPI_MISI_PORT       GPIOA
#define ange_SPI_MISI_Pin        GPIO_Pin_7
#endif


