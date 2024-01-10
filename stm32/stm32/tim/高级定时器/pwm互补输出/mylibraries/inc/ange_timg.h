#ifndef _ange_timg_h
#define _ange_timg_h
#include "stm32f10x.h"
/////////
#define ange_TIMgx TIM1
#define ange_TIMg_APBxClock RCC_APB2PeriphClockCmd
#define ange_TIMg_CLK       RCC_APB2Periph_TIM1
#define ange_TIMg_UP_IRQ       TIM1_UP_IRQn
#define ange_TIMg_UP_IRQHandler  TIM1_UP_IRQHandler
#define ange_TIMg_Prescaler   9-1
#define ange_TIMg_Period      8-1
//////
#define ange_TIMg_PWM1_Pulse  5
#define ange_TIMg_PWM2_Pulse  5
#define ange_TIMg_PWM3_Pulse  4
#define ange_TIMg_PWM4_Pulse  2

//////
///tim1 ch1
#define ange_TIMg_CH1_CLK  RCC_APB2Periph_GPIOA
#define ange_TIMg_CH1_PORT GPIOA
#define ange_TIMg_CH1_Pin  GPIO_Pin_8
//ª•≤π ch1
#define ange_TIMg_CH1N_CLK RCC_APB2Periph_GPIOB
#define ange_TIMg_CH1N_PORT GPIOB
#define ange_TIMg_CH1N_Pin  GPIO_Pin_13
///tim1 ch2
#define ange_TIMg_CH2_CLK RCC_APB2Periph_GPIOA
#define ange_TIMg_CH2_PORT GPIOA
#define ange_TIMg_CH2_Pin  GPIO_Pin_9
//ª•≤πch2
#define ange_TIMg_CH2N_CLK RCC_APB2Periph_GPIOB
#define ange_TIMg_CH2N_PORT GPIOB
#define ange_TIMg_CH2N_Pin  GPIO_Pin_14
//pwm…≤≥µ ‰»Î
#define ange_TIMg_PWM_BDTR_CLK RCC_APB2Periph_GPIOB
#define ange_TIMg_PWM_BDTR_PORT GPIOB
#define ange_TIMg_PWM_BDTR_Pin GPIO_Pin_12
void ange_TIMg_PWM_init(void);
#endif
