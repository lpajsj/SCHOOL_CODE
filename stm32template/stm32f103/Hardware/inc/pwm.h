#ifndef _PWMqh_pwm_h
#define _PWMqh_pwm_h
#include "stm32f10x.h"
#define PWM_xiangwei 0
/////
#if PWM_xiangwei  
#define delayms_PWM SysTick_delayms
#define PWMqh_TIMtx TIM4
#define PWMqh_TIMt_APBxClock  RCC_APB1PeriphClockCmd
#define PWMqh_TIMt_CLK        RCC_APB1Periph_TIM4
#define PWMqh_TIMt_IRQn        TIM4_IRQn
#define PWMqh_TIMt_IRQHandler  TIM4_IRQHandler
#define PWMqh_TIMt_Prescaler   0
#define PWMqh_TIMt_Period      0xffff
//////
#define PWMqh_TIMt_PWM1_Pulse  5
#define PWMqh_TIMt_PWM2_Pulse  4
#define PWMqh_TIMt_PWM3_Pulse  4
#define PWMqh_TIMt_PWM4_Pulse  2
//////
///tim2 ch1
#define PWMqh_TIMt_CH1_CLK RCC_APB2Periph_GPIOB
#define PWMqh_TIMt_CH1_PORT GPIOB
#define PWMqh_TIMt_CH1_Pin  GPIO_Pin_6
///tim2 ch2
#define PWMqh_TIMt_CH2_CLK RCC_APB2Periph_GPIOB
#define PWMqh_TIMt_CH2_PORT GPIOB
#define PWMqh_TIMt_CH2_Pin  GPIO_Pin_7
///tim2 ch3
#define PWMqh_TIMt_CH3_CLK RCC_APB2Periph_GPIOB
#define PWMqh_TIMt_CH3_PORT GPIOB
#define PWMqh_TIMt_CH3_Pin  GPIO_Pin_8
///tim2 ch4
#define PWMqh_TIMt_CH4_CLK RCC_APB2Periph_GPIOB
#define PWMqh_TIMt_CH4_PORT GPIOB
#define PWMqh_TIMt_CH4_Pin  GPIO_Pin_9
void PWMqh_TIMt_PWM_init(void);
//是捕获啊***************************/
#define PWMqh_TIMt_Channelx1 TIM_Channel_1; //输入通道
#define PWMqh_TIMt_Channelx2 TIM_Channel_2;
#define PWMqh_TIMt_Channel_Polarity1 TIM_ICPolarity_Rising
#define PWMqh_TIMt_Channel_Polarity2 TIM_ICPolarity_Falling
#define PWMqh_TIMt_IT_CCx1        TIM_IT_CC1  //捕获通道
#define PWMqh_TIMt_IT_CCx2        TIM_IT_CC2
void PWMqh_TIMt_IC_init(void);
//***********************************/
typedef struct
{
	u8 Capture_finish; //采集完成标志
	u8 Capture_ci;  //第几次采集
//	u16 Capture_Period1; //溢出几次
	u32 Capture_value1; //一路当前捕获值
	u32 Capture_value2; //二路当前捕获值
	double  pinlv,xiangwei,t1,t2;
}PWMqh_TIMt_ICValue_TypeDef;
extern PWMqh_TIMt_ICValue_TypeDef PWMqh_TIMt_IC_Value;  //定义捕获值结构体
#endif
#endif

