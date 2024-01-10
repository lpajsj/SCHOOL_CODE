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
	u8 data[256],rdata[256],b;
	u8 *d=data,*r=rdata;
	ange_usartnvicinit();
	ange_usartinit();
	LED_GPIO_Config();
//	LED_GREEN;
//	SysTick_delayms(3000);
//	LED_BLUE;
	SysTick_delayms(2000);
	ange_I2C_init();

	while(1)
	{
		LED_RED;
		
		////////////////////
		
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
		/////////////////
//	ange_I2C_bytewrite(3,10);
//	ange_I2C_waitbusy(eeprom_address);
////	SysTick_delayms(3000);
//	ange_I2C_dataread(3,1,&b);
//	LED_YELLOW;
//	printf("¶Á³öÊý¾Ý%d",b);
//	while(1);
	/////////////////
	}
}
