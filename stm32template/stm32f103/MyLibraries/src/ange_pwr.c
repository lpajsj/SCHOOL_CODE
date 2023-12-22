#include "ange_pwr.h"
/*PVD中断设置*/
/*外部中断16连接PVD*/
void PVD_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  /*使能 PWR 时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* 使能 PVD 中断 */
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    
  /* 配置 EXTI16线(PVD 输出) 来产生上升下降沿中断*/
  EXTI_ClearITPendingBit(EXTI_Line16);
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  /* 配置PVD级别PWR_PVDLevel_2V6 (PVD检测电压的阈值为2.6V，VDD电压低于2.6V时产生PVD中断) */
	/*具体级别根据自己的实际应用要求配置*/
  PWR_PVDLevelConfig(PWR_PVDLevel_2V6);
  /* 使能PVD输出 */
  PWR_PVDCmd(ENABLE);
}
void PVD_IRQHandler(void)
{
		/*检测是否产生了PVD警告信号*/
		if(PWR_GetFlagStatus (PWR_FLAG_PVDO)==SET)			
		{
			/* 亮红灯，实际应用中应进入紧急状态处理 */
		}
    /* 清除中断信号*/
    EXTI_ClearITPendingBit(EXTI_Line16);
}
/*睡眠模式程序停止运行*/
//使用WFI或WFE指令,在SLEEPDEEP=0时使用,事件和中断
//#define __WFI                             __wfi
//#define __WFE                             __wfe
/*停止模式外设停止工作*/
//函数中选择中断或事件唤醒，调压器低功耗更省电但启动时间变长
//void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
/*待机模式*/
//WKUP引脚的上升沿、 RTC闹钟事件的上升沿、 NRST引脚上外部复位、 IWDG复位
//使能电源管理单元的时钟,必须要使能时钟才能进入待机模式 
 //	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR , ENABLE);
//清除WU状态位
//PWR_ClearFlag (PWR_FLAG_WU);
//使能WKUP引脚的唤醒功能 ，使能PA0
//PWR_WakeUpPinCmd (ENABLE);
//进入待机模式 
//PWR_EnterSTANDBYMode();


