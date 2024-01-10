#include "stm32f10x.h"
#include "USART_Init.H"
#include "USART_HIM.H"

int main()
{
	USARTX_Config();
	Key_GPIO_Init();
	printf("´®¿ÚÆÁ²âÊÔ");
	while(1)
	{
		switch(KeyScan())
		{
			case 1:ToSendOrder("page y2");break;
			case 2:Send_Text("t0t","µçÑ¹");break;
			case 3:Send_Decimal("t0",3.3);break;
			case 4:ToSendOrder("page y1");break;
			default:break;
		}
	}
	
}
