#include "stm32f10x.h"
#include "bsp_led.h"
#include "ange_usart.h"
#include "stdio.h"
#include "ange_systick.h"
#include "chuankouping.h"
#include "stm32f10x.h"
#include "pwm.H"
extern PWMqh_TIMt_ICValue_TypeDef PWMqh_TIMt_IC_Value;  //定义捕获值结构体
int main()
{
	double  pinlv,xiangwei,t1,t2;
	LED_GPIO_Config();
	PWMqh_TIMt_IC_init();
	ange_USART_init(115200);
	while(1)
	{
		if(PWMqh_TIMt_IC_Value.Capture_finish)
		{
			t1=(double)((PWMqh_TIMt_IC_Value.Capture_value1+1)+PWMqh_TIMt_IC_Value.Capture_Period1*(0x10000))/72.0;
			t2=(double)((PWMqh_TIMt_IC_Value.Capture_value2+1)+PWMqh_TIMt_IC_Value.Capture_Period2*(0x10000))/72.0;
			while(t2>t1)
				t2-=t1;
			xiangwei=t2/t1*360;
			if(xiangwei>180)
				xiangwei-=360;
			pinlv=1000000/t1;
			LED1_TOGGLE;
			printf("t1:%lf  ",t1);
			printf("t2:%lf  ",t2);
			printf("xiangwei:%lf  ",xiangwei);
			printf("频率：%lf    ",pinlv);
			printf("\r\n");
			SysTick_delayms(100);
			PWMqh_TIMt_IC_Value.Capture_finish=0;	
		}
		
  }
}

