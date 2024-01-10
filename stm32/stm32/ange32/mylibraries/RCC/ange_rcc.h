#ifndef __ange_rcc_h
#define __ange_rcc_h
#include <stm32f10x.h>
void HSE_SetSysClock(u32 RCC_PLLMul_x);
void HSI_SetSysClock(u32 RCC_PLLMul_x);
#endif
