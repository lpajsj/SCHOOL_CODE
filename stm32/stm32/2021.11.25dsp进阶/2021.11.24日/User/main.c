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
#include "key.h"
#include "ange_wdg.h"
#include "ange_flash.h"
#include "DDS_API.h"
#include "main.h"
#include "ange_rtc_bkp.h"
#include "ange_iic.h"
#include "ange_timt.h"
float finput[512];
float finput2[512];
float foutput[512];
float fo;
float fo2;
u32   u32input[512];
u32   u32input2[512];
u32   u32output[512];
s32   s32input[512];
s32   s32input2[512];
s32   s32output[512];
//u16   u16input[512];
//u16   u16output[512];
//u8   u8input[512];
//u8   u8output[512];
s32 x,i;
arm_biquad_cas_df1_32x64_ins_q31 *fir;
int32_t main(void)
{
		
  ange_USART_init(115200);
arm_biquad_cas_df1_32x64_init_q31(fir,)
/**/
	while(1)
	{
	}
}



