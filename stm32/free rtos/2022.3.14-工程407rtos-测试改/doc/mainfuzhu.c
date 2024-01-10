// GPIO初始化
//		GPIO_InitTypeDef GPIO_InitStructure;
//		/*开启LED相关的GPIO外设时钟*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
//		/*选择要控制的GPIO引脚*/
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
//		/*设置引脚模式为通用推挽输出*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//		/*设置引脚速率为50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		/*调用库函数，初始化GPIO*/
//		GPIO_Init(GPIOA, &GPIO_InitStructure);	

/*
EXTI
相关寄存器

*/
#if 0
STM32F407 只有 FSMC 功能，但是使用的固件库里面有 FMC 和 FSMC 的功能，如果这两个文件
都同时编译的话，那么就会出错，所以我们选择把 FMC 在工程里面屏蔽掉，就不编译。同时，固
件库里面还有 DMA2D 和 LTDC 的库，但是 F407 都没有这两个功能，所以我们也选择把这两个
文件从工程里面屏蔽掉
#endif
#if 0
//结构体学习
https://blog.csdn.net/as480133937/article/details/83473208?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~aggregatepage~first_rank_ecpm_v1~rank_v31_ecpm-1-83473208.pc_agg_new_rank&utm_term=%E7%BB%93%E6%9E%84%E4%BD%93%E6%88%90%E5%91%98%E4%B8%8D%E6%8C%89%E9%A1%BA%E5%BA%8F%E5%88%9D%E5%A7%8B%E5%8C%96&spm=1000.2123.3001.4430
#endif
#if 0
//任务优先级
#define TASK2_TASK_PRIO		3
//任务堆栈大小	
#define TASK2_STK_SIZE 		128  
//任务堆栈
StackType_t Task2TaskStack[TASK2_STK_SIZE];
//任务控制块
StaticTask_t Task2TaskTCB;
//任务句柄
TaskHandle_t Task2Task_Handler;
//任务函数
void task2_task(void *pvParameters);
/////xTaskCreateStatic 静态任务需要添加的代码-自行分配内存 空闲任务与定时器任务
//空闲任务任务堆栈
static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
//空闲任务控制块
static StaticTask_t IdleTaskTCB;

//定时器服务任务堆栈
static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
//定时器服务任务控制块
static StaticTask_t TimerTaskTCB;
//获取空闲任务地任务堆栈和任务控制块内存，因为本例程使用的
//静态内存，因此空闲任务的任务堆栈和任务控制块的内存就应该
//有用户来提供，FreeRTOS提供了接口函数vApplicationGetIdleTaskMemory()
//实现此函数即可。
//ppxIdleTaskTCBBuffer:任务控制块内存
//ppxIdleTaskStackBuffer:任务堆栈内存
//pulIdleTaskStackSize:任务堆栈大小
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, 
								   StackType_t **ppxIdleTaskStackBuffer, 
								   uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
	*ppxIdleTaskStackBuffer=IdleTaskStack;
	*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

//获取定时器服务任务的任务堆栈和任务控制块内存
//ppxTimerTaskTCBBuffer:  任务控制块内存
//ppxTimerTaskStackBuffer:任务堆栈内存
//pulTimerTaskStackSize:  任务堆栈大小
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, 
									StackType_t **ppxTimerTaskStackBuffer, 
									uint32_t *pulTimerTaskStackSize)
{
	*ppxTimerTaskTCBBuffer=&TimerTaskTCB;
	*ppxTimerTaskStackBuffer=TimerTaskStack;
	*pulTimerTaskStackSize=configTIMER_TASK_STACK_DEPTH;
}
//进入低功耗模式前需要处理的事情
//ulExpectedIdleTime：低功耗模式运行时间  configPOST_SLEEP_PROCESSING()
void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
	//关闭某些低功耗模式下不使用的外设时钟，
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, DISABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, DISABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, DISABLE);	  
}

//退出低功耗模式以后需要处理的事情
//ulExpectedIdleTime：低功耗模式运行时间
void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
	//退出低功耗模式以后打开那些被关闭的外设时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);	              
}
#endif


