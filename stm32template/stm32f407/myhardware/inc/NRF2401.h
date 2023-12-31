#ifndef _NRF2401_H
#define _NRF2401_H

#include "stm32f10x.h"
#include "ange_SysTick.h"
#define TX_ADR_WIDTH 	5  	//发射地址宽度
#define TX_PLOAD_WIDTH  30   //发射数据通道有效数据宽度0~32Byte 

#define RX_ADR_WIDTH    5
#define RX_PLOAD_WIDTH  30  //发送接收宽度要一致

#define CHANAL 40	//频道选择 

// SPI(nRF24L01) commands ,	NRF的SPI命令宏定义，详见NRF功能使用文档
#define NRF_READ_REG    0x00  // Define read command to register  
#define NRF_WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD 0x61  // Define RX payload register address   FIFO读数据
#define WR_TX_PLOAD 0xA0  // Define TX payload register address   写FIFO寄存器
#define FLUSH_TX    0xE1  // Define flush TX register command     清空TX
#define FLUSH_RX    0xE2  // Define flush RX register command     清空RX
#define REUSE_TX_PL 0xE3  // Define reuse TX payload register command  重新发送上一次的数据
#define NOP         0xFF  // Define No Operation, might be used to read status register

// SPI(nRF24L01) registers(addresses) ，NRF24L01 相关寄存器地址的宏定义
#define CONFIG      0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address 自动应答
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address  使能接收地址
#define SETUP_AW    0x03  // 'Setup address width' register address  地址宽度
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address 设置自动重发
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address  地址
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address 数据宽度
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address    状态

#define MAX_RT      0x10 //达到最大重发次数中断标志位
#define TX_DS		0x20 //发送完成中断标志位	  // 

#define RX_DR		0x40 //接收到数据中断标志位

/* NRF1 管脚 */
#define NRF_software   1
#define NRF_hardware   0

#define NRF_soft_clk_GPIO_CLK  RCC_APB2Periph_GPIOA
#define NRF_soft_clk_GPIO_PORT GPIOA
#define NRF_soft_clk_GPIO_Pin  GPIO_Pin_5
#define NRF_soft_clk  PAout(5)
#define NRF_soft_miso_GPIO_CLK  RCC_APB2Periph_GPIOA
#define NRF_soft_miso_GPIO_PORT GPIOA
#define NRF_soft_miso_GPIO_Pin  GPIO_Pin_6
#define NRF_soft_miso  PAin(6)
#define NRF_soft_mosi_GPIO_CLK  RCC_APB2Periph_GPIOA
#define NRF_soft_mosi_GPIO_PORT  GPIOA
#define NRF_soft_mosi_GPIO_Pin  GPIO_Pin_7
#define NRF_soft_mosi  PAout(7)

#define NRF_CSN_GPIO_PORT    GPIOC
#define NRF_CSN_PIN          GPIO_Pin_6
#define NRF_CSN_GPIO_CLK     RCC_APB2Periph_GPIOC

#define NRF_CE_GPIO_PORT    GPIOC
#define NRF_CE_PIN          GPIO_Pin_5
#define NRF_CE_GPIO_CLK     RCC_APB2Periph_GPIOC

#define NRF_IRQ_GPIO_PORT    GPIOC
#define NRF_IRQ_PIN          GPIO_Pin_4
#define NRF_IRQ_GPIO_CLK     RCC_APB2Periph_GPIOC
#define NRF_EXTI_PortSource  GPIO_PortSourceGPIOC
#define NRF_EXTI_PinSource   GPIO_PinSource4
#define NRF_EXTI_Line        EXTI_Line4
#define NRF_Rx_IRQn          EXTI4_IRQn
#define NRF_Rx_IRQHandler    EXTI4_IRQHandler
void NRF_Rx_extiinit(void);

#define NRF_CSN_HIGH()      GPIO_SetBits(NRF_CSN_GPIO_PORT, NRF_CSN_PIN)
#define NRF_CSN_LOW()       GPIO_ResetBits(NRF_CSN_GPIO_PORT, NRF_CSN_PIN)		        //csn置低
#define NRF_CE_HIGH()	      GPIO_SetBits(NRF_CE_GPIO_PORT,NRF_CE_PIN)
#define NRF_CE_LOW()	      GPIO_ResetBits(NRF_CE_GPIO_PORT,NRF_CE_PIN)			      //CE置低
#define NRF_Read_IRQ()		  GPIO_ReadInputDataBit(NRF_IRQ_GPIO_PORT, NRF_IRQ_PIN)  //中断引脚
#define NRF_IRQn            exti

void SPI_NRF_Init(void);
u8 SPI_NRF_RW(u8 dat);
u8 SPI_NRF_ReadReg(u8 reg );
u8 SPI_NRF_WriteReg(u8 reg,u8 dat);

u8 SPI_NRF_ReadBuf(u8 reg,u8 *pBuf,u8 bytes);
u8 SPI_NRF_WriteBuf(u8 reg ,u8 *pBuf,u8 bytes);	

void NRF_TX_Mode(void);
void NRF_RX_Mode(void);
u8 NRF_Rx_Dat(u8 *rxbuf);
u8 NRF_Tx_Dat(u8 *txbuf);
u8 NRF_Check(void); 
//中断接收

/* NRF2 管脚 */

#define NRF2_CSN_GPIO_PORT    GPIOB
#define NRF2_CSN_PIN          GPIO_Pin_8
#define NRF2_CSN_GPIO_CLK     RCC_APB2Periph_GPIOB

#define NRF2_CE_GPIO_PORT    GPIOC
#define NRF2_CE_PIN          GPIO_Pin_7
#define NRF2_CE_GPIO_CLK     RCC_APB2Periph_GPIOC

#define NRF2_IRQ_GPIO_PORT    GPIOB
#define NRF2_IRQ_PIN          GPIO_Pin_12
#define NRF2_IRQ_GPIO_CLK     RCC_APB2Periph_GPIOB

#define NRF2_CSN_HIGH()     GPIO_SetBits(NRF2_CSN_GPIO_PORT, NRF2_CSN_PIN)
#define NRF2_CSN_LOW()      GPIO_ResetBits(NRF2_CSN_GPIO_PORT, NRF2_CSN_PIN)		        //csn置低
#define NRF2_CE_HIGH()	    GPIO_SetBits(NRF2_CE_GPIO_PORT,NRF2_CE_PIN)
#define NRF2_CE_LOW()	      GPIO_ResetBits(NRF2_CE_GPIO_PORT,NRF2_CE_PIN)			      //CE置低
#define NRF2_Read_IRQ()		  GPIO_ReadInputDataBit ( NRF2_IRQ_GPIO_PORT, NRF2_IRQ_PIN)  //中断引脚

void SPI_NRF2_Init(void);
u8 SPI_NRF2_RW(u8 dat);
u8 SPI_NRF2_ReadReg(u8 reg );
u8 SPI_NRF2_WriteReg(u8 reg,u8 dat);

u8 SPI_NRF2_ReadBuf(u8 reg,u8 *pBuf,u8 bytes);
u8 SPI_NRF2_WriteBuf(u8 reg ,u8 *pBuf,u8 bytes);	

void NRF2_TX_Mode(void);
void NRF2_RX_Mode(void);
u8 NRF2_Rx_Dat(u8 *rxbuf);
u8 NRF2_Tx_Dat(u8 *txbuf);
u8 NRF2_Check(void); 

#endif /* __SPI_NRF_H */
