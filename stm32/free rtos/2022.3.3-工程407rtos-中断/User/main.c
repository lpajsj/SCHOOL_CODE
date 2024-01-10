#include "stm32f4xx.h"
#include "ange_SysTick.h"
#include "main.h"
#include "ange_USART.h"
#include "ange_rcc.h"
#include "ange_exti.h"
#include "ange_dma.h"
#include "ange_ad.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
#include "ange_da.h"
#include "ange_spi.h"
#include "MS5611.h"
#include "ange_iic_24c02.h"
#include "bsp_led.h" 
#include "MPU6050.h"
#include "ange_iic.h"
#include "mpu6050_2.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "QMC5883.h"
#include "icm20689.h"
#include "lcd.h"

//#define LED0 PFout(9)	// DS0
//#define LED1 PFout(10)	// DS1	

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		256
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

#define INTERRUPT_TASK_PRIO 2
#define INTERRUPT_STK_SIZE  256
TaskHandle_t INTERRUPTTask_Handler;
void interrupt_task(void *pvParameters);


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	ange_USART_init(115200);     	//��ʼ������
	LED_GPIO_Config();		        //��ʼ��LED�˿�
//	ange_TIMj_init();  //��������ᱻ�ж�ʱ�ᱻ��ռ
	TIM3_Int_Init(8400,10000);
	TIM5_Int_Init(8400,10000);
	ange_TIMj_init();
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}
void start_task(void* pvParameters)
{
	taskENTER_CRITICAL();
	xTaskCreate((TaskFunction_t)interrupt_task,
	             (const char*)  "interrupt_task",
							 (uint16_t   )  INTERRUPT_STK_SIZE,
							 (void *     )  NULL,
								(UBaseType_t) INTERRUPT_TASK_PRIO,
							 (TaskHandle_t) &INTERRUPTTask_Handler);
	vTaskDelete(StartTask_Handler);
	taskEXIT_CRITICAL();
}
void interrupt_task(void* pvParameters)
{
	static u32 total_num=0;
	while(1)
	{
		total_num++;
		if(total_num==5)
		{
			printf("�ر��жϡ���������\n");
			portDISABLE_INTERRUPTS();
			delay_xms(5000);
			printf("���жϡ�������\n");
			portENABLE_INTERRUPTS();
		}
		LED0=!LED0;
		vTaskDelay(1000);
	}
}



























