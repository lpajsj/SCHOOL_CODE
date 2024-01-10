#ifndef _ange_timt_h
#define _ange_timt_h
#include "stm32f4xx.h"
/////apb1时钟42 定时器84M  apb2 时钟84m 定时器168m
#define ange_TIMtx TIM5
#define ange_TIMt_APBxClock RCC_APB1PeriphClockCmd
#define ange_TIMt_CLK       RCC_APB1Periph_TIM5
#define ange_TIMt_IRQn       TIM5_IRQn
#define ange_TIMt_IRQHandler  TIM5_IRQHandler
#define ange_TIMt_Prescaler   84-1
#define ange_TIMt_Period      1000-1
//////
#define ange_TIMt_PWM1_Pulse  500
#define ange_TIMt_PWM2_Pulse  500
#define ange_TIMt_PWM3_Pulse  4
#define ange_TIMt_PWM4_Pulse  2
//////
///tim2 ch1
#define ange_TIMt_CH1_CLK RCC_AHB1Periph_GPIOA
#define ange_TIMt_CH1_PORT GPIOA
#define ange_TIMt_CH1_Pin  GPIO_Pin_0
#define ange_TIMt_CH1_Pinsource  GPIO_PinSource0
#define ange_TIMt_CH1_AF  GPIO_AF_TIM5
///tim2 ch2
#define ange_TIMt_CH2_CLK RCC_AHB1Periph_GPIOA
#define ange_TIMt_CH2_PORT GPIOA
#define ange_TIMt_CH2_Pin  GPIO_Pin_1
#define ange_TIMt_CH2_Pinsource  GPIO_PinSource1
#define ange_TIMt_CH2_AF  GPIO_AF_TIM5
///tim2 ch3
#define ange_TIMt_CH3_CLK RCC_AHB1Periph_GPIOA
#define ange_TIMt_CH3_PORT GPIOA
#define ange_TIMt_CH3_Pin  GPIO_Pin_2
#define ange_TIMt_CH3_Pinsource  GPIO_PinSource2
#define ange_TIMt_CH3_AF  GPIO_AF_TIM5
///tim2 ch4
#define ange_TIMt_CH4_CLK RCC_AHB1Periph_GPIOA
#define ange_TIMt_CH4_PORT GPIOA
#define ange_TIMt_CH4_Pin  GPIO_Pin_3
#define ange_TIMt_CH4_Pinsource  GPIO_PinSource3
#define ange_TIMt_CH4_AF  GPIO_AF_TIM5
void ange_TIMt_PWM_init(void);
//是捕获啊***************************/
#define ange_TIMt_Channelx TIM_Channel_1;
#define ange_TIMt_Channel_Polarity1 TIM_ICPolarity_Rising
#define ange_TIMt_Channel_Polarity2 TIM_ICPolarity_Falling
#define ange_TIMt_IT_CCx        TIM_IT_CC1
void ange_TIMt_IC_init(void);
//***********************************/
typedef struct
{
	u8 Capture_finish; //采集完成标志
	u8 Capture_ci;  //第几次采集
	u16 Capture_Period; //溢出几次
	u16 Capture_value; //当前捕获值
}ange_TIMt_ICValue_TypeDef;
#endif

