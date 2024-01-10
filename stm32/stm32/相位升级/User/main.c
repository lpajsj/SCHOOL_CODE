#include "bsp_led.h"
#include "ange_usart.h"
#include "ange_systick.h"
#include "stm32f10x.h"
#include "pwm.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
/***********************************************************************************************************
主函数的相位检测功能已在pwm.c中改为了函数供调用，主程序已经经过测试，函数基本和主程序一样，可以看函数中的注释
程序目前用到了定时器4，的输入捕获通道1 2 用到了管脚 B6 B7，使用时pwm直接接到这两个管脚即可，100Khz以下有较好的测量效果
为了提高准确性，定时器并没有溢出计数相关操作，目前是1分频 （计数最高只有910us，且信号周期不要接近910us，），太低频率请改变分频，以及程序中时间计算操作的系数
************************************************************************************************************/
double  pinlv,xiangwei,t1,t2;
int main()
{

	ange_USART_init(115200);//串口初始化
	LED_GPIO_Config();  //可以去掉
	PWMqh_TIMt_IC_init(); //捕获初始化
	while(1)
	{
			//函数中有详细注释 PWMqh_TIMt_panduan()
		if(PWMqh_TIMt_IC_Value.Capture_finish)
		{
			t1=(double)((PWMqh_TIMt_IC_Value.Capture_value1+1))/72;//得出以微妙为单位，若要测低频率的值要修改定时器的分频，以及这里的系数，目前是1分频
			t2=(double)((PWMqh_TIMt_IC_Value.Capture_value2+1))/72;
			t1+=1.48+0.15;//加上补偿值
			t2+=1.48+0.15;//第一次上升沿到中断中把计时器置零的时间
			if(t2>t1)  //如果通道2的上升沿距离通道一的上升沿的时间太短，很可能通道二的捕获值会多记一个周期
				t2-=t1;
			xiangwei=t2/t1*360; //计算出相位

			if(xiangwei>180) //加上正负号
				xiangwei-=360;
			pinlv=1000000/t1; //求出频率
			LED1_TOGGLE;  //可以去掉
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


