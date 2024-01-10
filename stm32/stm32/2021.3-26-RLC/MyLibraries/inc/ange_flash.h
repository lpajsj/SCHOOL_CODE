#ifndef _ange_flash_h
#define _ange_flash_h
#include "stm32f10x.h"
#define ange_flash_size 2048
void ange_flash_write32(u32 adress,u32 *x,u32 number);
void ange_flash_read32(u32 adress,u32 *x,u32 number);
void ange_flash_write16(u32 adress,__IO u16 *x,u32 number);
void ange_flash_read16(u32 adress,u16 *x,u32 number);
//
void ange_flash_writeprotect(uint32_t FLASH_Pages);
void ange_flash_readprotect(FunctionalState NewState);
void ange_flash_examine(void);
#endif


