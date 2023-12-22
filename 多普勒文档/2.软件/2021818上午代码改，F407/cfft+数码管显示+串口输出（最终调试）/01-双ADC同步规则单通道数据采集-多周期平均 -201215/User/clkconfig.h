#ifndef __BSP_CLKCONFIG_H
#define __BSP_CLKCONFIG_H

#include "stm32f4xx.h"

void User_SetSysClock(void);
void HSE_SetSysClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ);
void HSI_SetSysClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ);


#endif /* __BSP_CLKCONFIG_H */


