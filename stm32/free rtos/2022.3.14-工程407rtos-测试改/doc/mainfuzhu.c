// GPIO��ʼ��
//		GPIO_InitTypeDef GPIO_InitStructure;
//		/*����LED��ص�GPIO����ʱ��*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
//		/*ѡ��Ҫ���Ƶ�GPIO����*/
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
//		/*��������ģʽΪͨ���������*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//		/*������������Ϊ50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		/*���ÿ⺯������ʼ��GPIO*/
//		GPIO_Init(GPIOA, &GPIO_InitStructure);	

/*
EXTI
��ؼĴ���

*/
#if 0
STM32F407 ֻ�� FSMC ���ܣ�����ʹ�õĹ̼��������� FMC �� FSMC �Ĺ��ܣ�����������ļ�
��ͬʱ����Ļ�����ô�ͻ������������ѡ��� FMC �ڹ����������ε����Ͳ����롣ͬʱ����
�������滹�� DMA2D �� LTDC �Ŀ⣬���� F407 ��û�����������ܣ���������Ҳѡ���������
�ļ��ӹ����������ε�
#endif
#if 0
//�ṹ��ѧϰ
https://blog.csdn.net/as480133937/article/details/83473208?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~aggregatepage~first_rank_ecpm_v1~rank_v31_ecpm-1-83473208.pc_agg_new_rank&utm_term=%E7%BB%93%E6%9E%84%E4%BD%93%E6%88%90%E5%91%98%E4%B8%8D%E6%8C%89%E9%A1%BA%E5%BA%8F%E5%88%9D%E5%A7%8B%E5%8C%96&spm=1000.2123.3001.4430
#endif
#if 0
//�������ȼ�
#define TASK2_TASK_PRIO		3
//�����ջ��С	
#define TASK2_STK_SIZE 		128  
//�����ջ
StackType_t Task2TaskStack[TASK2_STK_SIZE];
//������ƿ�
StaticTask_t Task2TaskTCB;
//������
TaskHandle_t Task2Task_Handler;
//������
void task2_task(void *pvParameters);
/////xTaskCreateStatic ��̬������Ҫ��ӵĴ���-���з����ڴ� ���������붨ʱ������
//�������������ջ
static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
//����������ƿ�
static StaticTask_t IdleTaskTCB;

//��ʱ�����������ջ
static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
//��ʱ������������ƿ�
static StaticTask_t TimerTaskTCB;
//��ȡ��������������ջ��������ƿ��ڴ棬��Ϊ������ʹ�õ�
//��̬�ڴ棬��˿�������������ջ��������ƿ���ڴ��Ӧ��
//���û����ṩ��FreeRTOS�ṩ�˽ӿں���vApplicationGetIdleTaskMemory()
//ʵ�ִ˺������ɡ�
//ppxIdleTaskTCBBuffer:������ƿ��ڴ�
//ppxIdleTaskStackBuffer:�����ջ�ڴ�
//pulIdleTaskStackSize:�����ջ��С
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, 
								   StackType_t **ppxIdleTaskStackBuffer, 
								   uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
	*ppxIdleTaskStackBuffer=IdleTaskStack;
	*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

//��ȡ��ʱ����������������ջ��������ƿ��ڴ�
//ppxTimerTaskTCBBuffer:  ������ƿ��ڴ�
//ppxTimerTaskStackBuffer:�����ջ�ڴ�
//pulTimerTaskStackSize:  �����ջ��С
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, 
									StackType_t **ppxTimerTaskStackBuffer, 
									uint32_t *pulTimerTaskStackSize)
{
	*ppxTimerTaskTCBBuffer=&TimerTaskTCB;
	*ppxTimerTaskStackBuffer=TimerTaskStack;
	*pulTimerTaskStackSize=configTIMER_TASK_STACK_DEPTH;
}
//����͹���ģʽǰ��Ҫ���������
//ulExpectedIdleTime���͹���ģʽ����ʱ��  configPOST_SLEEP_PROCESSING()
void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
	//�ر�ĳЩ�͹���ģʽ�²�ʹ�õ�����ʱ�ӣ�
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, DISABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, DISABLE);	  
}

//�˳��͹���ģʽ�Ժ���Ҫ���������
//ulExpectedIdleTime���͹���ģʽ����ʱ��
void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
	//�˳��͹���ģʽ�Ժ����Щ���رյ�����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);	              
}
#endif


