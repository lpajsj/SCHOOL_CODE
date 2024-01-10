#ifndef __tlc2543_h__
#define __tlc2543_h__
#include "stm32f10x.h"

#define SPI_TLC2543_CS_LOW()       GPIO_ResetBits(GPIOE, GPIO_Pin_7)
#define SPI_TLC2543_CS_HIGH()      GPIO_SetBits(GPIOE, GPIO_Pin_7)

void TLC2543_INIT(void);
u8 Read_TLC2543(u16 chan);


#endif
