#include "stm32f10x.h"
#include "ADDA.H"
#include "usart.h"

int main()
{
	ADCX_Config();
	USART_Config();
	DAC_Config();
	printf("ADC≤‚ ‘");
	
	TIM_Cmd(TIM6,DISABLE);
	TIM_SetAutoreload(TIM6,0x1);
	TIM_Cmd(TIM6,ENABLE);
	while(1)
	{
		
			ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			printf("\r\n CH6 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
			printf("\r\n CH7 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
			printf("\r\n CH8 value = %f V \r\n",ADC_ConvertedValueLocal[2]);		
	
	}
	
}
