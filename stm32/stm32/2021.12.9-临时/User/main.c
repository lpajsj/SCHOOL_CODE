#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
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
#include "main.h"
#include "ange_rtc_bkp.h"
#include "ange_iic.h"
#include "ange_timt.h"
#include "ange_rcc.h"
#include "OLED12864.h"
#include "NRF2401.h"
u8 shuju[32];
u8 shuju1[32];
u8 shuju2[32];
 u8 RX_ADDRESS3[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};
extern u8 SPI_NRF_ReadReg(u8 reg);
int32_t main(void)
{
	u32 i,j;
	for(i=0;i<32;i++)
	{
		shuju[i]=i;
	}
  SPI_NRF_Init();
	SPI_NRF2_Init();
	ange_USART_init(115200);
	NRF2_TX_Mode();
	NRF_RX_Mode();
	NRF_Rx_extiinit();
		for(i=0;i<0x18;i++)
	{
		SPI_NRF_ReadBuf(i,shuju1,5);
		printf("1NRF%x:",i);
		for(j=0;j<5;j++)
		{
			printf("%x,",shuju1[j]);
		}
		printf("  ");
		SPI_NRF2_ReadBuf(i,shuju2,5);
		printf("2NRF%x:",i);
		for(j=0;j<5;j++)
		{
			printf("%x,",shuju2[j]);
		}
		printf("\n");
//		SysTick_delayms(100);
	}
		NRF2_TX_Mode();
	NRF_RX_Mode();
	while(1) 
	{	
		NRF2_Tx_Dat(shuju);
//	NRF2_Rx_Dat(shuju1);
//	for(i=0;i<32;i++)
//	{
//		printf("%d,",shuju1[i]);
//	}
//		SPI_NRF_WriteReg(NRF_WRITE_REG+RX_ADDR_P2,1);
//		SPI_NRF_ReadBuf(RX_ADDR_P2,shuju1,5);
//		for(i=0;i<5;i++)
//		printf("%x;;;;;;",shuju1[i]);
//	NRF2_TX_Mode();
//	NRF_RX_Mode();

		SysTick_delayms(1000);
	}
}



