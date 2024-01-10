#ifndef _ange_timt_h
#define _ange_timt_h
#include "stm32f10x.h"
/////
#define ange_TIMtx TIM2
#define ange_TIMt_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMt_CLK       RCC_APB1Periph_TIM2
#define ange_TIMt_IRQ       TIM2_IRQn
#define ange_TIMt_IRQHandler  TIM2_IRQHandler
#define ange_TIMt_Prescaler   90-1
#define ange_TIMt_Period      8-1
//////
#define ange_TIMt_PWM1_Pulse  5
#define ange_TIMt_PWM2_Pulse  4
#define ange_TIMt_PWM3_Pulse  4
#define ange_TIMt_PWM4_Pulse  2
//////
///tim2 ch1
#define ange_TIMt_CH1_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CH1_PORT GPIOA
#define ange_TIMt_CH1_Pin  GPIO_Pin_0
///tim2 ch2
#define ange_TIMt_CH2_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CH2_PORT GPIOA
#define ange_TIMt_CH2_Pin  GPIO_Pin_1
///tim2 ch3
#define ange_TIMt_CH3_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CH3_PORT GPIOA
#define ange_TIMt_CH3_Pin  GPIO_Pin_2
///tim2 ch4
#define ange_TIMt_CH4_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CH4_PORT GPIOA
#define ange_TIMt_CH4_Pin  GPIO_Pin_3
void ange_TIMt_PWM_init(void);
#endif

