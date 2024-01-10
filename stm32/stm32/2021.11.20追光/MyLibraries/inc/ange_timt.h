#ifndef _ange_TIMt_h
#define _ange_TIMt_h
#include "stm32f10x.h"
#define ange_TIMt_OCx TIM4
#define ange_TIMt_OC_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMt_OC_CLK       RCC_APB1Periph_TIM4
#define ange_TIMt_OC_IRQn       TIM4_IRQn
#define ange_TIMt_OC_IRQHandler  TIM4_IRQHandler
#define ange_TIMt_OC_Prescaler   72-1
#define ange_TIMt_OC_Period      20000-1
//////
#define ange_TIMt_OC_PWM1_Pulse  1000+500-1
#define ange_TIMt_OC_PWM2_Pulse  1000+500-1
#define ange_TIMt_OC_PWM3_Pulse  4
#define ange_TIMt_OC_PWM4_Pulse  2
//////
///tim2 ch1
#define ange_TIMt_OC_CH1_CLK RCC_APB2Periph_GPIOB
#define ange_TIMt_OC_CH1_PORT GPIOB
#define ange_TIMt_OC_CH1_Pin  GPIO_Pin_6

///tim2 ch2
#define ange_TIMt_OC_CH2_CLK RCC_APB2Periph_GPIOB
#define ange_TIMt_OC_CH2_PORT GPIOB
#define ange_TIMt_OC_CH2_Pin  GPIO_Pin_7
///tim2 ch3
#define ange_TIMt_OC_CH3_CLK RCC_APB2Periph_GPIOB
#define ange_TIMt_OC_CH3_PORT GPIOB
#define ange_TIMt_OC_CH3_Pin  GPIO_Pin_8
///tim2 ch4
#define ange_TIMt_OC_CH4_CLK RCC_APB2Periph_GPIOB
#define ange_TIMt_OC_CH4_PORT GPIOB
#define ange_TIMt_OC_CH4_Pin  GPIO_Pin_9
void ange_TIMt_OC_PWM_init(void);


/////*/////////////////*/捕获开始
#define ange_TIMt_CCx TIM2
#define ange_TIMt_CC_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMt_CC_CLK       RCC_APB1Periph_TIM2
#define ange_TIMt_CC_IRQn       TIM2_IRQn
#define ange_TIMt_CC_IRQHandler  TIM2_IRQHandler
#define ange_TIMt_CC_Prescaler   7200-1
#define ange_TIMt_CC_Period      0xffff
//////
#define ange_TIMt_CC_PWM1_Pulse  5
#define ange_TIMt_CC_PWM2_Pulse  4
#define ange_TIMt_CC_PWM3_Pulse  4
#define ange_TIMt_CC_PWM4_Pulse  2
//////
///tim2 ch1
#define ange_TIMt_CC_CH1_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CC_CH1_PORT GPIOA
#define ange_TIMt_CC_CH1_Pin  GPIO_Pin_0

///tim2 ch2
#define ange_TIMt_CC_CH2_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CC_CH2_PORT GPIOA
#define ange_TIMt_CC_CH2_Pin  GPIO_Pin_1
///tim2 ch3
#define ange_TIMt_CC_CH3_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CC_CH3_PORT GPIOA
#define ange_TIMt_CC_CH3_Pin  GPIO_Pin_2
///tim2 ch4
#define ange_TIMt_CC_CH4_CLK RCC_APB2Periph_GPIOA
#define ange_TIMt_CC_CH4_PORT GPIOA
#define ange_TIMt_CC_CH4_Pin  GPIO_Pin_3
void ange_TIMt_CC_PWM_init(void);
//是捕获啊***************************/
#define ange_TIMt_CC_Channelx TIM_Channel_1;
#define ange_TIMt_CC_Channel_Polarity1 TIM_ICPolarity_Rising
#define ange_TIMt_CC_Channel_Polarity2 TIM_ICPolarity_Falling
#define ange_TIMt_CC_IT_CCx        TIM_IT_CC1
void ange_TIMt_CC_IC_init(void);
//***********************************/
typedef struct
{
	u8 Capture_finish;
	u8 Capture_ci;
	u16 Capture_Period;
	u16 Capture_value;
}ange_TIMt_CC_ICValue_TypeDef;
#endif

