#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_dma.h"
#include "ange_usart.h"
#include "stdio.h"
const uint32_t yuanzu[ange_DMA_BufferSize]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
uint32_t muzu[ange_DMA_BufferSize];
u8 bufferpp(const u32 *yuan,u32 *mu,u32 size)
{
	while(size--)
	{
		if(*yuan!=*mu)
		{
			return 0;
		}
		yuan++;
		mu++;
	}
	return 1;
}
	void delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
#if DMA_CC
int main()
	
{
	u8 ch;
	LED_GPIO_Config();
	LED_GREEN;
delay(0xffffff);
	ange_DMA_CC_Config(yuanzu,muzu);
	while(DMA_GetFlagStatus(ange_DMA_FLAG_TC)==RESET);
	ch=bufferpp(yuanzu,muzu,ange_DMA_BufferSize);
	if(ch==1)
	{
		LED_BLUE;
	}
	else
	{
		LED_RED;
	}
	while(1)
	{
	
	}
}
#endif
#if DMA_CW
u8 yuanzu2[ange_DMA_BufferSize];
int main()
{
	u8 ch;
	LED_GPIO_Config();
	LED_GREEN;
	ange_usartinit();
	for(ch=0;ch<ange_DMA_BufferSize;ch++)
	{
		yuanzu2[ch]=ch;
	}
delay(0xffffff);
	USART_Cmd(ange_USARTx,ENABLE);
	USART_DMACmd(ange_USARTx,USART_DMAReq_Tx,ENABLE);
	ange_DMA_CW_USARTConfig(yuanzu2,ange_DMA_mudi);
	if(ch==1)
	{
		LED_BLUE;
	}
	else
	{
		LED_RED;
	}
	while(1)
	{
			delay(0xfffff);
		for(ch=0;ch<ange_DMA_BufferSize;ch++)
	{
		yuanzu2[ch]=ch+10;
	}
		DMA_Cmd(ange_DMA_Channel,DISABLE);
		DMA_SetCurrDataCounter(ange_DMA_Channel,ange_DMA_BufferSize);
		DMA_Cmd(ange_DMA_Channel,ENABLE);
	}
}
#endif
#if DMA_WC
u8 jieshouzu[ange_DMA_BufferSize];
int main()
{
	u8 ch;
//	LED_GPIO_Config();
//	LED_GREEN;
//  delay(0xffffff);
	ange_usartinit();
	USART_Cmd(ange_USARTx,ENABLE);  
  USART_ITConfig(ange_USARTx,USART_IT_IDLE,ENABLE);
	USART_DMACmd(ange_USARTx,USART_DMAReq_Rx,ENABLE);
	ange_DMA_WC_USARTConfig(ange_DMA_yuan,jieshouzu);
	if(ch==1)
	{
		LED_BLUE;
	}
	else
	{
		LED_RED;
	}
	while(1)
	{
	}
}
#endif
