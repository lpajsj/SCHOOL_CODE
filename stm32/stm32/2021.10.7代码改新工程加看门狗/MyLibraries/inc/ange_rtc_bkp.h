#ifndef _ange_rtc_bkp_h
#define _ange_rtc_bkp_h
#include "stm32f10x.h"
//BKP
void ange_BKP_init(void);
void ange_BKP_Tamper_init(void);
void ange_BKP_Tamper_NVIC_init(void);
//RTC
void ange_RTC_init(void);
void ange_RTC_NVIC_init(void);
#endif


