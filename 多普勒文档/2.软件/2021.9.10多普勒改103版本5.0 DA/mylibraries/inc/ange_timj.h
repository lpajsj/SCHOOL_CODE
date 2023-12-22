#ifndef _ange_timj_h
#define _ange_timj_h
#include "stm32f10x.h"
#define ange_tim6 1
#define ange_tim7 0
void ange_TIMj_init(void);

#define ange_TIMjx TIM4
#define ange_TIMj_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMj_CLK       RCC_APB1Periph_TIM4
#define ange_TIMj_IRQ       TIM4_IRQn
#define ange_TIMj_IRQHandler  TIM4_IRQHandler
#endif



