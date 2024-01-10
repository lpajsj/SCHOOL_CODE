#ifndef _ange_timj_h
#define _ange_timj_h
#include "stm32f10x.h"
#define ange_tim6 0
#define ange_tim7 0
#define ange_tim4 1
void ange_TIMj_init(void);

#if  ange_tim6
#define ange_TIMjx TIM6
#define ange_TIMj_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMj_CLK       RCC_APB1Periph_TIM6
#define ange_TIMj_IRQ       TIM6_IRQn
#define ange_TIMj_IRQHandler  TIM6_IRQHandler
#endif

#if  ange_tim7
#define ange_TIMjx TIM7
#define ange_TIMj_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMj_CLK       RCC_APB1Periph_TIM7
#define ange_TIMj_IRQ       TIM7_IRQn
#define ange_TIMj_IRQHandler  TIM7_IRQHandler
#endif

#if  ange_tim4
#define ange_TIMjx TIM4
#define ange_TIMj_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMj_CLK       RCC_APB1Periph_TIM4
#define ange_TIMj_IRQ       TIM4_IRQn
#define ange_TIMj_IRQHandler  TIM4_IRQHandler
#endif

#endif



