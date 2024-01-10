#ifndef _ange_wdg_h
#define _ange_wdg_h
#include "stm32f10x.h"
void ange_iwdg_init(u8 presaler,u16 counter);
void ange_iwdg_feed(void);
void ange_wwdg_init(u32 prescaler,u8 counter,u8 window);
#endif



