#include "ange_rtc_bkp.h"
#include "ange_usart.h"
/*复位后，对备份寄存器和RTC的访问被禁止，并且备份域被保护以防止可能存在的意外的写操
作。执行以下操作可以使能对备份寄存器和RTC的访问。
● 通过设置寄存器RCC_APB1ENR的PWREN和BKPEN位来打开电源和后备接口的时钟
● 电源控制寄存器(PWR_CR)的DBP位来使能对后备寄存器和RTC的访问。*/
/*备份寄存器是42个16位的寄存器，可用来存储84个字节的用户应用程序数据。他们处在备份域
里，当VDD电源被切断，他们仍然由VBAT维持供电*/
/*RTC的PRL，CNT,ALR,与RCC的BDTR都位于备份域*/
/*BKP初始化*/
void ange_BKP_init()
{
	//开启PWR时钟和后备区域时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);
	//开启后备区域电源
	PWR_BackupAccessCmd(ENABLE);
	
}
//void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);  //写备份寄存器
//uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);             //读备份寄存器
void ange_BKP_Tamper_init()
{
	BKP_TamperPinLevelConfig(BKP_TamperPinLevel_High);
	BKP_TamperPinCmd(ENABLE);
	BKP_ClearFlag();
}
void ange_BKP_Tamper_NVIC_init()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=TAMPER_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
	BKP_ITConfig(ENABLE);
	
}
//void BKP_ITConfig(FunctionalState NewState) 侵入中断配置
void TAMPER_IRQHandler()
{
	if(BKP_GetITStatus()==SET)
	{
		//侵入事件标志位不清除在BAT供电情况下会一直存在
		BKP_ClearFlag();
		BKP_ClearITPendingBit();
		printf("Tamper is high level");
	}
}

/*RTC*/
/*配置PRL，CNT,ALR寄存器要先配置CNF，并等待其他操作完成。一开始的时候还要同步时钟*/
#define ange_RTCCLK_LSE
//#define ange_RTCCLK_LSI
void ange_RTC_init()
{
	//开启PWR时钟和后备区域时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);
	//开启后备区域电源
	PWR_BackupAccessCmd(ENABLE);
	//复位备份域，这里控制的是RCC的BDCR寄存器
	BKP_DeInit();
#ifdef ange_RTCCLK_LSI
	RCC_LSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);
	//RCC中RTC与LSE开关位于备份域，意味着如果BAT供电则重新复位后可以不用配置,而LSI需要配置
	//RTC时钟来源选择与使能
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);
	//等待同步
	RTC_WaitForSynchro();
	//等待操作完成
	RTC_WaitForLastTask();
	//设置RTC时钟预分频
	RTC_SetPrescaler(40000-1);
	RTC_WaitForLastTask();
	RTC_SetCounter(1000);
	RTC_WaitForLastTask();
#endif
#ifdef ange_RTCCLK_LSE
  RCC_LSEConfig(RCC_LSE_ON);
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY));
	//RCC中RTC与LSE开关位于备份域，意味着如果BAT供电则重新复位后可以不用配置,而LSI需要配置
	//RTC时钟来源选择与使能
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
		//等待同步
	RTC_WaitForSynchro();
	//等待操作完成
	RTC_WaitForLastTask();
  //设置RTC时钟预分频
	RTC_SetPrescaler(32768-1);
	RTC_WaitForLastTask();
	RTC_SetCounter(1000);
	RTC_WaitForLastTask();
#endif
//开启秒中断
RTC_ITConfig(RTC_IT_SEC,ENABLE);
}
void ange_RTC_NVIC_init()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=RTC_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
void RTC_IRQHandler()
{
	if(RTC_GetITStatus(RTC_IT_SEC)==SET)
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);
		printf("RTC计数器的值：%d",RTC_GetCounter());
	}
}





