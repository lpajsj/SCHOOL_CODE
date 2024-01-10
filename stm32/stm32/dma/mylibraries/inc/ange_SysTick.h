#ifndef __ange_SysTick_
#define __ange_SysTick_
#include <stm32f10x.h>
void SysTickdelay(void);
void SysTick_delayms(uint32_t n);
void SysTick_delayus(uint32_t n);
void SysTickInit(void);
void delayus(u32 n);
#endif
#if 0
typedef struct
{
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Type;
优先级是 SHPRx
#endif
