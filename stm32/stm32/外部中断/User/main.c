#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_exti.h"
#include "ange_SysTick.h"
#include "ange_USART.H"
int main()
{
	u8 ch;
	LED_GPIO_Config();
//	ange_extiinit();
//	SysTickInit();
	ange_usartinit();
	USART_ITConfig(ange_USARTx,USART_IT_RXNE,DISABLE);
	printf("安哥np");
	while(1)
	{
		ch=getchar();
		printf("接收到字符%c",ch);
    switch(ch)
    {
      case '1':
        LED_RED;
      break;
      case '2':
        LED_GREEN;
      break;
      case '3':
        LED_BLUE;
      break;
      case '4':
        LED_YELLOW;
      break;
      case '5':
        LED_PURPLE;
      break;
      case '6':
        LED_CYAN;
      break;
      case '7':
        LED_WHITE;
      break;
      case '8':
        LED_RGBOFF;
      break;
      default:
        break;      
    } 
//			LED1( ON ); 
//	    delayus(100000);    	// 100000 * 10us = 1000ms
//		//Delay_ms(100);
//		LED1( OFF );
//	  
//		LED2( ON );
//	    delayus(100000);		// 100000 * 10us = 1000ms
//		//Delay_ms(100);
//		LED2( OFF );
//	
//		LED3( ON );
//	    delayus(100000);		// 100000 * 10us = 1000ms
//		//Delay_ms(100);
//		LED3( OFF );
	}
}
