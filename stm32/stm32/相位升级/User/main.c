#include "bsp_led.h"
#include "ange_usart.h"
#include "ange_systick.h"
#include "stm32f10x.h"
#include "pwm.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
/***********************************************************************************************************
����������λ��⹦������pwm.c�и�Ϊ�˺��������ã��������Ѿ��������ԣ�����������������һ�������Կ������е�ע��
����Ŀǰ�õ��˶�ʱ��4�������벶��ͨ��1 2 �õ��˹ܽ� B6 B7��ʹ��ʱpwmֱ�ӽӵ��������ܽż��ɣ�100Khz�����нϺõĲ���Ч��
Ϊ�����׼ȷ�ԣ���ʱ����û�����������ز�����Ŀǰ��1��Ƶ ���������ֻ��910us�����ź����ڲ�Ҫ�ӽ�910us������̫��Ƶ����ı��Ƶ���Լ�������ʱ����������ϵ��
************************************************************************************************************/
double  pinlv,xiangwei,t1,t2;
int main()
{

	ange_USART_init(115200);//���ڳ�ʼ��
	LED_GPIO_Config();  //����ȥ��
	PWMqh_TIMt_IC_init(); //�����ʼ��
	while(1)
	{
			//����������ϸע�� PWMqh_TIMt_panduan()
		if(PWMqh_TIMt_IC_Value.Capture_finish)
		{
			t1=(double)((PWMqh_TIMt_IC_Value.Capture_value1+1))/72;//�ó���΢��Ϊ��λ����Ҫ���Ƶ�ʵ�ֵҪ�޸Ķ�ʱ���ķ�Ƶ���Լ������ϵ����Ŀǰ��1��Ƶ
			t2=(double)((PWMqh_TIMt_IC_Value.Capture_value2+1))/72;
			t1+=1.48+0.15;//���ϲ���ֵ
			t2+=1.48+0.15;//��һ�������ص��ж��аѼ�ʱ�������ʱ��
			if(t2>t1)  //���ͨ��2�������ؾ���ͨ��һ�������ص�ʱ��̫�̣��ܿ���ͨ�����Ĳ���ֵ����һ������
				t2-=t1;
			xiangwei=t2/t1*360; //�������λ

			if(xiangwei>180) //����������
				xiangwei-=360;
			pinlv=1000000/t1; //���Ƶ��
			LED1_TOGGLE;  //����ȥ��
			printf("t1:%lf  ",t1);
			printf("t2:%lf  ",t2);
			printf("xiangwei:%lf  ",xiangwei);
			printf("Ƶ�ʣ�%lf    ",pinlv);
			printf("\r\n");
			SysTick_delayms(100);
			PWMqh_TIMt_IC_Value.Capture_finish=0;	
		}
  }
}


