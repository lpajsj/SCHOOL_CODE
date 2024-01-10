#ifndef __ange_rcc_h
#define __ange_rcc_h
#include <stm32f4xx.h>
void HSE_SetSysClock(u32 m,u32 n,u32 p,u32 q);
void HSI_SetSysClock(u32 m,u32 n,u32 p,u32 q);
#endif
