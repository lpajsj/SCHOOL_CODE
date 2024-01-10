#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
#include "AD9910.h"
#include "ange_ad.h"
#include "ange_SysTick.h"
#include "ange_timg.h"
#include "ange_timj.h"
#include "bsp_led.h"  
#include "ange_da.h"
#include "ange_rtc_bkp.h"
int32_t main(void)
{
	u16 x;
	ange_USART_init(460800);
//	ange_TIMg_PWM_init();
//	ange_DA_init();
//	ange_DA_DMA_Config(da_shuju1);
//	dapinlv(100);
//	ange_TIMj_init();
//	TIM_SelectOutputTrigger(ange_TIMjx,TIM_TRGOSource_Update);
//	ange_ADC12_init();
		//开启PWR时钟和后备区域时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);
	//开启后备区域电源
	PWR_BackupAccessCmd(ENABLE);
	BKP_ClearFlag();
	BKP_WriteBackupRegister(BKP_DR1,1234);
	x=BKP_ReadBackupRegister(BKP_DR1);
	printf("备份寄存器数据%d",x);
	BKP_TamperPinLevelConfig(BKP_TamperPinLevel_High);
	BKP_TamperPinCmd(ENABLE);
    while (1)
		{
//sprintf()
		}			
}



