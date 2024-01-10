#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_dma.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_iic.h"
#include "ange_systick.h"
int main()
{
	u16 x;
	u8 data[256],rdata[256];
	u8 *d=data,*r=rdata;
	ange_usartnvicinit();
	ange_usartinit();
	LED_GPIO_Config();
//	LED_GREEN;
//	SysTick_delayms(3000);
//	LED_BLUE;
	ange_I2C_init();
	while(1)
	{
		LED_RED;
		SysTick_delayms(2000);
		x=256;
		while(x--)
		{
			*d=x;
			d++;
		}
		d-=256;
		ange_I2C_datawrite(1,250,d);
		ange_I2C_dataread(1,250,r);
		x=250;
		while(x--)
		{
			printf("%d ",*r);
			r++;
		}
		LED_GREEN;
		while(1);
//	ange_I2C_bytewrite(3,1);
//	ange_I2C_waitbusy(eeprom_address);
////	SysTick_delayms(3000);
//	LED_RED;
//	x=ange_I2C_byteread(3);
//	printf("¶Á³öÊý¾Ý%d",x);
//	SysTick_delayms(1000);
////	I2C_Cmd(ange_I2Cx,ENABLE);
	}
}
