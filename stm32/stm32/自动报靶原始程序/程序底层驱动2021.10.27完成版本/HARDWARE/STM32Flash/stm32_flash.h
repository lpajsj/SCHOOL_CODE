#ifndef __stm32_flash_h_
#define __stm32_flash_h_
/***************************************************/
#include <stm32f10x.h>

#define STM32_FLASH_SIZE  256
//解锁密钥：
#define FLASH_KEY1        0X45670123
#define FLASH_KEY2        0XCDEF89AB

//可用函数
void STMFLASH_Unlock(void);
void STMFLASH_Lock(void);
uint8_t STMFLASH_GetStatus(void);
uint8_t STMFLASH_WaitDone(uint16_t time);
uint8_t STMFLASH_ErasePage(uint32_t paddr);
uint8_t STMFLASH_WriteHalfWord(uint32_t faddr,uint16_t dat);
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);
void ID_write(u8 s_ID,u8 p_ID);
u16 ID_read(u32 ID_addr);

//待用函数
void STMFLASH_Write_NoCheck(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead);
/***************************************************/
#endif
