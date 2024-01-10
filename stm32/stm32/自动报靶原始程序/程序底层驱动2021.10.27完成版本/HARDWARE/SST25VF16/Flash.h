#ifndef __sst25vf016b_h__
#define __sst25vf016b_h__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/
/* 定义操作SST25VF016B所需的数据 */
typedef enum ERTYPE{Sec1,Sec8,Sec16,Chip} ErType;  
typedef enum IDTYPE{Manu_ID,Dev_ID,Jedec_ID} idtype;

/* Private define ------------------------------------------------------------*/
//#define MAX_ADDR		0x1FFFFF	/* 定义芯片内部最大地址 */
#define	SEC_MAX     	511         /* 定义最大扇区号 */
#define SEC_SIZE		0x1000      /* 扇区大小	*/   
// 2M=1024*2048=1024*1024*2=512*(0x1000)字节

#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)

/* Private function prototypes -----------------------------------------------*/
void  sst25_init(void);
uint8_t SSTF016B_RD(uint32_t Dst, uint8_t* RcvBufPt ,uint32_t NByte);
uint8_t SSTF016B_RdID(idtype IDType,uint32_t* RcvbufPt);
uint8_t SSTF016B_WR(uint32_t Dst, uint8_t* SndbufPt,uint32_t NByte);

uint8_t SSTF016B_Erase(uint32_t sec1, uint32_t sec2);
uint8_t SPI_FLASH_Test(void);
/* Private function prototypes -----------------------------------------------*/
void df_read_open(uint32_t addr);
void df_write_open(uint32_t addr);
void df_read(uint8_t *buf,uint16_t size);
void df_write(uint8_t *buf,uint16_t size);
void df_read_seek(uint32_t addr);
void df_write_seek(uint32_t addr);
void df_read_close(void);
void df_write_close(void);
uint8_t Flash_ReadWriteByte(uint8_t data);




//自己填的函数
void sst25_write(uint32_t flash_start_addr,uint8_t* WriteBuffer,uint16_t size);
void sst25_read(uint32_t flash_start_addr,uint8_t* ReadBuffer,uint16_t size);

void Flash_addr_write(u32 s_addr,u16 s_sector);//保存sst25 FLASH 当前写 地址 扇区号
u32 Flash_addr_read(u32 r_addr);							 //读回sst25 FLASH 当前写 地址 扇区号

void Flash_SaveSec0(void);
void Flash_SaveSec1(void);
void Flash_save_PwrOffTransinfo(void);
void Flash_save_Transaction(u32 add,u8 * buf,u8 length);
#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

