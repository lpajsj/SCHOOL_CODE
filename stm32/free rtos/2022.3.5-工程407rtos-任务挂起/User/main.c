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
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128
////�����ջ
//StackType_t StartTaskStack[START_STK_SIZE];
////������ƿ�
//StaticTask_t StartTaskTCB;
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define KEY_TASK_PRIO		2
//�����ջ��С	
#define KEY_STK_SIZE 		128  
////�����ջ
//StackType_t KEYTaskStack[KEY_STK_SIZE];
////������ƿ�
//StaticTask_t KEYTaskTCB;
//������
TaskHandle_t KeyTask_Handler;
//������
void key_task(void *pvParameters);

//�������ȼ�
#define TASK1_TASK_PRIO		3
//�����ջ��С	
#define TASK1_STK_SIZE 		128  
////�����ջ
//StackType_t Task1TaskStack[TASK1_STK_SIZE];
////������ƿ�
//StaticTask_t Task1TaskTCB;
//������
TaskHandle_t Task1Task_Handler;
//������
void task1_task(void *pvParameters);

//�������ȼ�
#define TASK2_TASK_PRIO		4
//�����ջ��С	
#define TASK2_STK_SIZE 		128  
////�����ջ
//StackType_t Task2TaskStack[TASK2_STK_SIZE];
////������ƿ�
//StaticTask_t Task2TaskTCB;
//������
TaskHandle_t Task2Task_Handler;
//������
void task2_task(void *pvParameters);

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 ���ӵ��ж���4
	
	/* ����EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line =  EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);							//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;		//�ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;//��ռ���ȼ�6
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;	//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);							//����	   
}

//������
//extern TaskHandle_t Task2Task_Handler;

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	BaseType_t YieldRequired;
	
	delay_xms(20);	//����
	if(KEY0==0)	 
	{				 
		YieldRequired=xTaskResumeFromISR(Task2Task_Handler);//�ָ�����2
		printf("�ָ�����2������!\r\n");
		if(YieldRequired==pdTRUE)
		{
			/*�������xTaskResumeFromISR()����ֵΪpdTRUE����ô˵��Ҫ�ָ������
			������������ȼ����ڻ��߸����������е�����(���жϴ�ϵ�����),������
			�˳��жϵ�ʱ��һ��Ҫ�����������л���*/
			portYIELD_FROM_ISR(YieldRequired);
		}
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}
//LCDˢ��ʱʹ�õ���ɫ
int lcd_discolor[14]={	WHITE, BLACK, BLUE,  BRED,      
						GRED,  GBLUE, RED,   MAGENTA,       	 
						GREEN, CYAN,  YELLOW,BROWN, 			
						BRRED, GRAY };
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	ange_USART_init(115200);     	//��ʼ������
	LED_GPIO_Config();		        //��ʼ��LED�˿� portDISABLE_INTERRUPTS
	LCD_Init();							//��ʼ��LCD
	KEY_Init();							//��ʼ������
	EXTIX_Init();						//��ʼ���ⲿ�ж�
	POINT_COLOR = RED;
	LCD_ShowString(30,10,200,16,16,"ATK STM32F103/F407");	
	LCD_ShowString(30,30,200,16,16,"FreeRTOS Examp 6-1");
	LCD_ShowString(30,50,200,16,16,"Task Creat and Del");
	LCD_ShowString(30,70,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,90,200,16,16,"2016/11/25");

	ange_TIMj_init();
	//������ʼ����
                 xTaskCreate
	              ((TaskFunction_t )start_task,          //������
                (const char*    )"start_task",          //��������
                (uint32_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
								(TaskHandle_t*) &StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}
void start_task(void* pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
		             xTaskCreate((TaskFunction_t )key_task,             
                (const char*    )"key_task",           
                (uint16_t       )KEY_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )KEY_TASK_PRIO,        
                (TaskHandle_t*  )&KeyTask_Handler);  
    //����TASK1����
                xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
								(TaskHandle_t*) &Task1Task_Handler);   //������ 
    //����TASK2����
                xTaskCreate((TaskFunction_t )task2_task,     
                (const char*    )"task2_task",   
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_TASK_PRIO,
								(TaskHandle_t*) &Task2Task_Handler);   //������ 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();  
}
//key������
void key_task(void *pvParameters)
{
	u8 key;
	while(1)
	{
		key=KEY_Scan(0);
		switch(key)
		{
			case WKUP_PRES:
				vTaskSuspend(Task1Task_Handler);//��������1
				printf("��������1������!\r\n");
				break;
			case KEY1_PRES:
				vTaskResume(Task1Task_Handler);	//�ָ�����1
				printf("�ָ�����1������!\r\n");
				break;
			case KEY2_PRES:
				vTaskSuspend(Task2Task_Handler);//��������2
				printf("��������2������!\r\n");
				break;
		}
		vTaskDelay(10);			//��ʱ10ms 
	}
}
//task1������
void task1_task(void *pvParameters)
{
	u8 task1_num=0;
	
	POINT_COLOR = BLACK;

	LCD_DrawRectangle(5,110,115,314); 	//��һ������	
	LCD_DrawLine(5,130,115,130);		//����
	POINT_COLOR = BLUE;
	LCD_ShowString(6,111,110,16,16,"Task1 Run:000");
	while(1)
	{
		task1_num++;	//����ִ1�д�����1 ע��task1_num1�ӵ�255��ʱ������㣡��
		LED0=!LED0;
		printf("����1�Ѿ�ִ�У�%d��\r\n",task1_num);

  

		LCD_Fill(6,131,114,313,lcd_discolor[task1_num%14]); //�������
		LCD_ShowxNum(86,111,task1_num,3,16,0x80);	//��ʾ����ִ�д���
        vTaskDelay(1000);                           //��ʱ1s��Ҳ����1000��ʱ�ӽ���	
	}
}

//task2������
void task2_task(void *pvParameters)
{
	u8 task2_num=0;
	
	POINT_COLOR = BLACK;

	LCD_DrawRectangle(125,110,234,314); //��һ������	
	LCD_DrawLine(125,130,234,130);		//����
	POINT_COLOR = BLUE;
	LCD_ShowString(126,111,110,16,16,"Task2 Run:000");
	while(1)
	{
		task2_num++;	//����2ִ�д�����1 ע��task1_num2�ӵ�255��ʱ������㣡��
        LED1=!LED1;
		printf("����2�Ѿ�ִ�У�%d��\r\n",task2_num);
		LCD_ShowxNum(206,111,task2_num,3,16,0x80);  //��ʾ����ִ�д���
		LCD_Fill(126,131,233,313,lcd_discolor[13-task2_num%14]); //�������
        vTaskDelay(1000);                           //��ʱ1s��Ҳ����1000��ʱ�ӽ���	
	}
}



























