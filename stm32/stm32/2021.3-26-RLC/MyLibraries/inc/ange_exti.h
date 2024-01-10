#ifndef __ange_exti_H
#define __ange_exti_H
#include <stm32f10x.h>
#define ange_EXTI_GPIO_PORT   GPIOA            //
#define ange_EXTI_CLK         RCC_APB2Periph_GPIOA  //使用外部中断是也要打开AFIO时钟
#define ange_EXTI_GPIO_Pin    GPIO_Pin_0
#define ange_EXTI_PortSource  GPIO_PortSourceGPIOA //void GPIO_EXTILineConfig(u8 GPIO_PortSource, u8 GPIO_PinSource)  0123456对应abcdefg
#define ange_EXTI_PinSource  GPIO_PinSource0  //选择 GPIO 管脚用作外部中断线路的参数  0-15
#define ange_EXTI_Line       EXTI_Line0      //中断事件线  1<<n
#define ange_EXTI_IRQn        EXTI0_IRQn      //中断源
#define ange_EXTI             EXTI0_IRQHandler  ///中断函数
void ange_extinvicinit(void);
void ange_extiinit(void);
#endif
/*
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
根据 EXTI_InitStruct 中指定的参数初始化外设 EXTI 寄存器
typedef struct
{
u32 EXTI_Line;
EXTIMode_TypeDef EXTI_Mode;
EXTIrigger_TypeDef EXTI_Trigger;
FunctionalState EXTI_LineCmd;
} EXTI_InitTypeDef;
typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;
typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;
*/
