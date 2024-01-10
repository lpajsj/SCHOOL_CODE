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

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		256
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

#define INTERRUPT_TASK_PRIO 2
#define INTERRUPT_STK_SIZE  256
TaskHandle_t INTERRUPTTask_Handler;
void interrupt_task(void *pvParameters);


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	ange_USART_init(115200);     	//初始化串口
	LED_GPIO_Config();		        //初始化LED端口
//	ange_TIMj_init();  //放在这里会被中断时会被抢占
	TIM3_Int_Init(8400,10000);
	TIM5_Int_Init(8400,10000);
	ange_TIMj_init();
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
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
			printf("关闭中断。。。。。\n");
			portDISABLE_INTERRUPTS();
			delay_xms(5000);
			printf("打开中断。。。。\n");
			portENABLE_INTERRUPTS();
		}
		LED0=!LED0;
		vTaskDelay(1000);
	}
}



























