#ifndef _ange_timg_h
#define _ange_timg_h
#include "stm32f10x.h"
#define ange_TIM1_CC3  1
#define ange_TIMx_PWM_IC  0  
#if ange_TIMx_PWM_IC
/////////******************************
#define ange_TIMgx TIM1
#define ange_TIMg_APBxClock RCC_APB2PeriphClockCmd
#define ange_TIMg_CLK       RCC_APB2Periph_TIM1
#define ange_TIMg_UP_IRQ       TIM1_UP_IRQn
#define ange_TIMg_UP_IRQHandler  TIM1_UP_IRQHandler
#define ange_TIMg_Prescaler   1-1  //在pwm捕获时一定要小于pwm频率
#define ange_TIMg_Period      72000000/20000-1//在pwm捕获时周期要大于pwm周期
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
//互补 ch1
#define ange_TIMg_CH1N_CLK RCC_APB2Periph_GPIOB
#define ange_TIMg_CH1N_PORT GPIOB
#define ange_TIMg_CH1N_Pin  GPIO_Pin_13
///tim1 ch2
#define ange_TIMg_CH2_CLK RCC_APB2Periph_GPIOA
#define ange_TIMg_CH2_PORT GPIOA
#define ange_TIMg_CH2_Pin  GPIO_Pin_9
//互补ch2
#define ange_TIMg_CH2N_CLK RCC_APB2Periph_GPIOB
#define ange_TIMg_CH2N_PORT GPIOB
#define ange_TIMg_CH2N_Pin  GPIO_Pin_14
//pwm刹车输入
#define ange_TIMg_PWM_BDTR_CLK RCC_APB2Periph_GPIOB
#define ange_TIMg_PWM_BDTR_PORT GPIOB
#define ange_TIMg_PWM_BDTR_Pin GPIO_Pin_12
void ange_TIMg_PWM_init(void);
void ange_TIMg_PWM_Config(void);
///*********************************************pwm 捕获
#define  ange_TIMg_CC_IRQn   TIM1_CC_IRQn
#define  ange_TIMg_CC_IRQHandler  TIM1_CC_IRQHandler
#define ange_TIMg_IT_CCx       TIM_IT_CC1
#define ange_TIMg_Channelx1 TIM_Channel_1;
#define ange_TIMg_Channelx2 TIM_Channel_2;
void ange_TIMg_ICPWM_init(void);
//////////***********************************
#endif
#if ange_TIM1_CC3
#define ange_TIMgx TIM1
#define ange_TIMg_APBxClock RCC_APB2PeriphClockCmd
#define ange_TIMg_CLK       RCC_APB2Periph_TIM1
#define ange_TIMg_UP_IRQ       TIM1_UP_IRQn
#define ange_TIMg_UP_IRQHandler  TIM1_UP_IRQHandler
#define ange_TIMg_Prescaler   1-1  //在pwm捕获时一定要小于pwm频率
#define ange_TIMg_pinlv       20000
#define ange_TIMg_Period      72000000/ange_TIMg_pinlv-1//宏定义在计算时要加括号 
void ange_TIMg_PWM_Config(void);
#endif
#endif

