#ifndef __check_h_
#define __check_h_
/***********************************************/
#include "stm32f10x.h"

uint16_t Get_Crc16(uint8_t *puchMsg,uint16_t usDataLen);
uint8_t Get_Crc8(uint8_t *ptr,uint16_t len);

/***********************************************/
#endif
