#ifndef  _ange_spi_h
#define  _ange_spi_h
#include "stm32f4xx.h"
////spi
#define ange_SPIx SPI1
#define ange_SPI_APBxClock RCC_APB2PeriphClockCmd
#define ange_SPI_CLK       RCC_APB2Periph_SPI1
//GPIO
///CS
#define ange_SPI_CS_APBxClock   RCC_AHB1PeriphClockCmd
#define ange_SPI_CS_CLK         RCC_AHB1Periph_GPIOA
#define ange_SPI_CS_PORT        GPIOA
#define ange_SPI_CS_Pin         GPIO_Pin_4
#define ange_SPI_CS1            GPIO_SetBits(ange_SPI_CS_PORT,ange_SPI_CS_Pin);
#define ange_SPI_CS0            GPIO_ResetBits(ange_SPI_CS_PORT,ange_SPI_CS_Pin);
#define ange_SPI_CS_PinSource   GPIO_PinSource4
///CLK
#define ange_SPI_SCK_APBxClock  RCC_AHB1PeriphClockCmd
#define ange_SPI_SCK_CLK        RCC_AHB1Periph_GPIOA
#define ange_SPI_SCK_PORT       GPIOA
#define ange_SPI_SCK_Pin        GPIO_Pin_5
#define ange_SPI_SCK_PinSource   GPIO_PinSource5
//MISO 主机输入，从机输出
#define ange_SPI_MISO_APBxClock  RCC_AHB1PeriphClockCmd
#define ange_SPI_MISO_CLK        RCC_AHB1Periph_GPIOA
#define ange_SPI_MISO_PORT       GPIOA
#define ange_SPI_MISO_Pin       GPIO_Pin_6
#define ange_SPI_MISO_PinSource   GPIO_PinSource6
//MISI 主机输出，从机输入
#define ange_SPI_MOSI_APBxClock  RCC_AHB1PeriphClockCmd
#define ange_SPI_MOSI_CLK        RCC_AHB1Periph_GPIOA
#define ange_SPI_MOSI_PORT       GPIOA
#define ange_SPI_MOSI_Pin        GPIO_Pin_7
#define ange_SPI_MOSI_PinSource   GPIO_PinSource7
u8 ange_SPI_sendbyte(u8 x);
void ange_SPI_GPIO_Congfig(void);
void ange_SPI_Config(void);
//spi2
#define ange_SPI2x SPI2
#define ange_SPI2_APBxClock     RCC_APB1PeriphClockCmd
#define ange_SPI2_CLK           RCC_APB1Periph_SPI2
//GPIO
///CS
#define ange_SPI2_CS_APBxClock   RCC_AHB1PeriphClockCmd
#define ange_SPI2_CS_CLK         RCC_AHB1Periph_GPIOB
#define ange_SPI2_CS_PORT        GPIOB
#define ange_SPI2_CS_Pin         GPIO_Pin_12
#define ange_SPI2_CS1            GPIO_SetBits(ange_SPI2_CS_PORT,ange_SPI2_CS_Pin);
#define ange_SPI2_CS0            GPIO_ResetBits(ange_SPI2_CS_PORT,ange_SPI2_CS_Pin);
#define ange_SPI2_CS_PinSource   GPIO_PinSource12
///CLK
#define ange_SPI2_SCK_APBxClock  RCC_AHB1PeriphClockCmd
#define ange_SPI2_SCK_CLK        RCC_AHB1Periph_GPIOB
#define ange_SPI2_SCK_PORT       GPIOB
#define ange_SPI2_SCK_Pin       GPIO_Pin_13
#define ange_SPI2_SCK_PinSource   GPIO_PinSource13
//MISO 主机输入，从机输出
#define ange_SPI2_MISO_APBxClock  RCC_AHB1PeriphClockCmd
#define ange_SPI2_MISO_CLK        RCC_AHB1Periph_GPIOB
#define ange_SPI2_MISO_PORT       GPIOB
#define ange_SPI2_MISO_Pin       GPIO_Pin_14
#define ange_SPI2_MISO_PinSource   GPIO_PinSource14
//MISI 主机输出，从机输入
#define ange_SPI2_MOSI_APBxClock  RCC_AHB1PeriphClockCmd
#define ange_SPI2_MOSI_CLK        RCC_AHB1Periph_GPIOB
#define ange_SPI2_MOSI_PORT       GPIOB
#define ange_SPI2_MOSI_Pin        GPIO_Pin_15
#define ange_SPI2_MOSI_PinSource   GPIO_PinSource15

u8 ange_SPI2_sendbyte(u8 x);
void ange_SPI2_GPIO_Congfig(void);
void ange_SPI2_Config(void);
#endif


