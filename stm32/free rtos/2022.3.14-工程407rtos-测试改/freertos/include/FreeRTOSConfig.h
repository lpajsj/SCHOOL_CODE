

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
#include "ange_SysTick.h"
#include "ange_USART.h"
#include "timer.h"
//针对不同的编译器调用不同的stdint.h文件
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

//断言
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)

/***************************************************************************************************************/
/*                                        FreeRTOS基础配置配置选项                                              */
/***************************************************************************************************************/
#define configUSE_PREEMPTION					1                       //1使用抢占式内核，0使用协程
#define configUSE_TIME_SLICING					1						//1使能时间片调度(默认式使能的)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                       //1启用特殊方法来选择下一个要运行的任务
                                                                        //一般是硬件计算前导零指令，,并且硬件最大优先级数目只有32，如果所使用的
                                                                        //MCU没有这些硬件指令的话此宏应该设置为0！
#define configUSE_TICKLESS_IDLE					0                       //1启用低功耗tickless模式
#define configUSE_QUEUE_SETS					1                       //为1时启用队列
#define configCPU_CLOCK_HZ						(SystemCoreClock)       //CPU频率
#define configTICK_RATE_HZ						(1000)                  //时钟节拍频率，这里设置为1000，周期就是1ms
#define configMAX_PRIORITIES					(32)                    //可使用的最大优先级
#define configMINIMAL_STACK_SIZE				((unsigned short)130)   //空闲任务使用的堆栈大小
#define configMAX_TASK_NAME_LEN					(16)                    //任务名字字符串长度

#define configUSE_16_BIT_TICKS					0                       //系统节拍计数器变量数据类型，
                                                                        //1表示为16位无符号整形，0表示为32位无符号整形
#define configIDLE_SHOULD_YIELD					1                       //为1时空闲任务放弃CPU使用权给其他同优先级的用户任务
#define configUSE_TASK_NOTIFICATIONS            1                       //为1时开启任务通知功能，默认开启
#define configUSE_MUTEXES						1                       //为1时使用互斥信号量
 #define configQUEUE_REGISTRY_SIZE				8                       //不为0时表示启用队列记录，具体的值是可以
                                                                        //记录的队列和信号量最大数目。
#define configCHECK_FOR_STACK_OVERFLOW			0                       //大于0时启用堆栈溢出检测功能，如果使用此功能
                                                                        //用户必须提供一个栈溢出钩子函数，如果使用的话
                                                                        //此值可以为1或者2，因为有两种栈溢出检测方法。
#define configUSE_RECURSIVE_MUTEXES				1                       //为1时使用递归互斥信号量
#define configUSE_MALLOC_FAILED_HOOK			0                       //1使用内存申请失败钩子函数
#define configUSE_APPLICATION_TASK_TAG			0                       
#define configUSE_COUNTING_SEMAPHORES			1                       //为1时使用计数信号量

/***************************************************************************************************************/
/*                                FreeRTOS与内存申请有关配置选项                                                */
/***************************************************************************************************************/
#define configSUPPORT_DYNAMIC_ALLOCATION        1                       //支持动态内存申请
#define configSUPPORT_STATIC_ALLOCATION			0						 //只是静态内存
#define configTOTAL_HEAP_SIZE					((size_t)(20*1024))     //系统所有总的堆大小

/***************************************************************************************************************/
/*                                FreeRTOS与钩子函数有关的配置选项                                              */
/***************************************************************************************************************/
#define configUSE_IDLE_HOOK						1                       //1，使用空闲钩子；0，不使用
#define configUSE_TICK_HOOK						0                       //1，使用时间片钩子；0，不使用vApplicationTickHook

/***************************************************************************************************************/
/*                                FreeRTOS与运行时间和任务状态收集有关的配置选项                                 */
/***************************************************************************************************************/
#define configGENERATE_RUN_TIME_STATS	        1                       //为1时启用运行时间统计功能,为一时还需要定义其他的
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()  ConfigureTimeForRunTimeStats()//定时器3提供时间统计的时基，频率为10K，即周期为100us
#define portGET_RUN_TIME_COUNTER_VALUE()		FreeRTOSRunTimeTicks	//获取时间统计时间值

#define configUSE_TRACE_FACILITY				1                       //为1启用可视化跟踪调试
#define configUSE_STATS_FORMATTING_FUNCTIONS	1                       //与宏configUSE_TRACE_FACILITY同时为1时会编译下面3个函数
                                                                        //prvWriteNameToBuffer(),vTaskList(),
                                                                        //vTaskGetRunTimeStats()
                                                                        
/***************************************************************************************************************/
/*                                FreeRTOS与协程有关的配置选项                                                  */
/***************************************************************************************************************/
#define configUSE_CO_ROUTINES 			        0                       //为1时启用协程，启用协程以后必须添加文件croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )                   //协程的有效优先级数目

/***************************************************************************************************************/
/*                                FreeRTOS与软件定时器有关的配置选项                                            */
/***************************************************************************************************************/
#define configUSE_TIMERS				          1                               //为1时启用软件定时器
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        //软件定时器优先级
#define configTIMER_QUEUE_LENGTH		        5                               //软件定时器队列长度
#define configTIMER_TASK_STACK_DEPTH	        (configMINIMAL_STACK_SIZE*2)    //软件定时器任务堆栈大小

/***************************************************************************************************************/
/*                                FreeRTOS可选函数配置选项                                                      */
/***************************************************************************************************************/
#define INCLUDE_xTaskGetSchedulerState          1                       
#define INCLUDE_vTaskPrioritySet		        1
#define INCLUDE_uxTaskPriorityGet		        1            //获取任务优先级
#define INCLUDE_vTaskDelete				        1
#define INCLUDE_vTaskCleanUpResources	        1
#define INCLUDE_vTaskSuspend			        1
#define INCLUDE_vTaskDelayUntil			        1
#define INCLUDE_vTaskDelay				        1               //相对延时函数
#define INCLUDE_eTaskGetState			        1
#define INCLUDE_xTimerPendFunctionCall	        1

/***************************************************************************************************************/
/*                                FreeRTOS与中断有关的配置选项              xPortStartScheduler                                    */
/***************************************************************************************************************/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15                      //中断最低优先级
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5                       //系统可管理的最高中断优先级
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/***************************************************************************************************************/
/*                                FreeRTOS与中断服务函数有关的配置选项                                          */
/***************************************************************************************************************/
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler

#endif /* FREERTOS_CONFIG_H */

#if 0
//相关函数
xTaskCreate() 使用动态的方法创建一个任务。
xTaskCreateStatic() 使用静态的方法创建一个任务。
xTaskCreateRestricted() 创建一个使用 MPU 进行限制的任务，相关内存使用动态内存分配。
vTaskDelete()    删除一个任务。
vTaskStartScheduler 开启任务调度
vTaskEndScheduler() 关闭任务任务调度
vTaskSuspendAll()   挂起任务调度 调用了几次 vTaskSuspendAll()挂起调度器，同样的也得调用几次 xTaskResumeAll()才会最终恢复任务调度器
xTaskResumeAll()    恢复任务调度
vTaskSuspend() 挂起一个任务。
vTaskResume()  恢复一个任务的运行。
xTaskResumeFromISR() 中断服务函数中恢复一个任务的运行。
taskYIELD()      任务切换
portYIELD_FROM_ISR  中断任务切换
       链表
vListInitialise   初始化链表
vListInitialiseItem  初始化链表项
vListInsert          链表项插入
uxListRemove         链表项删除 只是断了连接
vListInsertEnd       在index前插入链表项


taskENTER_CRITICAL()   进入临界区
taskEXIT_CRITICAL()    退出临界区
taskENTER_CRITICAL_FROM_ISR()  中断级临界
 taskEXIT_CRITICAL_FROM_ISR()  退出中断临界
 taskDISABLE_INTERRUPTS()       关中断
 taskENABLE_INTERRUPTS()        开中断
 
 内存
 vPortFree  释放内存
 
 vTaskStepTick 此 函 数 在 使 用 FreeRTOS 的 低 功 耗 tickless 模 式 的 时 候 会 用 到 ， 即 宏configUSE_TICKLESS_IDLE 为 1。
 
 任务相关API函数
 uxTaskPriorityGet();           此函数用来获取指定任务的优先级
 vTaskPrioritySet()             改变任务优先级
 uxTaskGetSystemState()         此函数用于获取系统中所有任务的任务壮态
 vTaskGetInfo()                 此函数也是用来获取任务壮态的，但是是获取指定的单个任务的壮态的 要使用此函数的话宏configUSE_TRACE_FACILITY 要定义为 1
 xTaskGetApplicationTaskTag()   此函数用于获取任务的 Tag(标签)值
 xTaskGetCurrentTaskHandle()    此函数用于获取当前任务的任务句柄
 xTaskGetHandle()               根据任务名字获取任务句柄。。。。。
 xTaskGetIdleTaskHandle()       此 函 数 用 于 返 回 空 闲 任 务 的 任 务 句 柄
 uxTaskGetStackHighWaterMark()  此函数用于检查任务从创建好到现在的历史剩余最小值 INCLUDE_uxTaskGetStackHighWaterMark
 eTaskState eTaskGetState       此函数用于查询某个任务的运行壮态
 pcTaskGetName                  根据某个任务的任务句柄来查询这个任务对应的任务名
  xTaskGetTickCount()           此函数用于查询任务调度器从启动到现在时间计数器 xTickCount 的值
	xTaskGetTickCountFromISR()    此函数是 xTaskGetTickCount()的中断级版本，用于在中断服务函数中获取时间计数器xTickCount 的值
	xTaskGetSchedulerState()      此函数用于获取 FreeRTOS 的任务调度器运行情况
	uxTaskGetNumberOfTasks()      此函数用于查询系统当前存在的任务数量     直接调用
	vTaskList()                   此函数会创建一个表格来描述每个任务的详细信息   
vTaskGetRunTimeStats()          	 FreeRTOS 可以通过相关的配置来统计任务的运行时间信息configGENERATE_RUN_TIME_STATS 和 configUSE_STATS_FORMATTING_FUNCTIONS
portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()，此宏用来初始化一个外设来
还需要实现一下几个宏定义提供时间统计功能所需的时基， 一般是定时器/计数器。这个时基的分辨率一定要比 FreeRTOS
的系统时钟高，一般这个时基的时钟精度比系统时钟的高 10~20 倍就可以了。
● portGET_RUN_TIME_COUNTER_VALUE()或者
portALT_GET_RUN_TIME_COUNTER_VALUE(Time)， 这两个宏实现其中一个就行
了，这两个宏用于提供当前的时基的时间值。
vTaskSetApplicationTaskTag()       此函数用于设置某个任务的标签值 
SetThreadLocalStoragePointer()     此函数用于设置线程本地存储指针的值
 GetThreadLocalStoragePointer()    此 函 数 用 于 获 取 线 程 本 地 存 储 指 针 的 值configNUM_THREAD_LOCAL_STORAGE_POINTERS 不能为 0
 
 队列
 xQueueCreate();
 xQueueCreateStatic();
 xQueueGenericCreate();
 xQueueGenericCreateStatic()
 函数 xQueueSend()、 xQueueSendToBack()和 xQueueSendToFront()  xQueueOverwrite
 函数 xQueueSendFromISR()、xQueueSendToBackFromISR()、xQueueSendToFrontFromISR()  xQueueOverwriteFromISR
 prvLockQueue()和 prvUnlockQueue()。
 任务级出队函数
xQueueReceive()
从队列中读取队列项(消息)，并且读取完
以后删除掉队列项(消息)
xQueuePeek()
从队列中读取队列项(消息)，并且读取完
以后不删除队列项(消息)
中断级出队函数
xQueueReceiveFromISR()
从队列中读取队列项(消息)，并且读取完
以后删除掉队列项(消息)，用于中断服务
函数中
xQueuePeekFromISR ()
从队列中读取队列项(消息)，并且读取完
以后不删除队列项(消息)，用于中断服务
函数中
            信号量二值  
二值信号量创建成功以后要先释放一下
vSemaphoreCreateBinary ()
动 态 创 建 二 值 信 号 量 ， 这 个 是 老 版 本
FreeRTOS 中使用的创建二值信号量的 API 函
数。
xSemaphoreCreateBinary()
动态创建二值信号量， 新版 FreeRTOS 使用此
函数创建二值信号量。
xSemaphoreCreateBinaryStatic() 静态创建二值信号量。
xSemaphoreGive() 任务级信号量释放函数
xSemaphoreGiveFromISR() 中断级信号量释放函数
xSemaphoreTake() 任务级获取信号量函数
xSemaphoreTakeFromISR() 中断级获取信号量函数
            计数型信号量
xSemaphoreCreateCounting() 使用动态方法创建计数型信号量。
xSemaphoreCreateCountingStatic() 使用静态方法创建计数型信号量
            互斥型信号量
xSemaphoreCreateMutex() 使用动态方法创建互斥信号量。
xSemaphoreCreateMutexStatic() 使用静态方法创建互斥信号量。
//           递归信号量
要使用递归互斥信号量的话宏 configUSE_RECURSIVE_MUTEXES 必须为 1！
xSemaphoreCreateRecursiveMutex() 使用动态方法创建递归互斥信号量。
xSemaphoreCreateRecursiveMutexStatic() 使用静态方法创建递归互斥信号量。
//          软件定时器
xTimerReset() 复位软件定时器，用在任务中。
xTimerResetFromISR() 复位软件定时器，用在中断服务函数中。
xTimerCreate() 使用动态方法创建软件定时器。
xTimerCreateStatic() 使用静态方法创建软件定时器
xTimerStart() 开启软件定时器，用于任务中。
xTimerStartFromISR() 开启软件定时器，用于中断中。
xTimerStop() 停止软件定时器，用于任务中。
xTimerStopFromISR() 停止软件定时器，用于中断服务函数中。
//        事件标志组
xEventGroupCreate() 使用动态方法创建事件标志组。``1234567890QWERPASDFGHJKLLZXCVBNMZXCVBNMNM122345969787597PASDFGHJKLLZXCVBDDDDssss
xEventGroupCreateStatic() 使用静态方法创建事件标志组123456789qwertyuiopasdfghjklzxcvbnmkkkll	lL
xEventGroupClearBits() 将指定的事件位清零，用在任务中。
xEventGroupClearBitsFromISR() 将指定的事件位清零，用在中断服务函数中
xEventGroupSetBits() 将指定的事件位置 1，用在任务中。
xEventGroupSetBitsFromISR() 将指定的事件位置 1，用在中断服务函数中。
xEventGroupGetBits() 获取当前事件标志组的值(各个事件位的值)，用在任务中。
xEventGroupGetBitsFromISR() 获取当前事件标志组的值，用在中断服务函数中。
xEventGroupWaitBits()       等待指定的事件位
//        任务通知
xTaskNotify()发送通知，带有通知值并且不保留接收任务原通知值，用在任务中。
xTaskNotifyFromISR() 发送通知，函数 xTaskNotify()的中断版本。
xTaskNotifyGive()发送通知，不带通知值并且不保留接收任务的通知值，此函数会将接收任务的通知值加一，用于任务中。
vTaskNotifyGiveFromISR() 发送通知，函数 xTaskNotifyGive()的中断版本。
xTaskNotifyAndQuery()发送通知，带有通知值并且保留接收任务的原通知值，用在任务中。
xTaskNotiryAndQueryFromISR()发送通知，函数 xTaskNotifyAndQuery()的中断版本，用在中断服务函数中。
ulTaskNotifyTake()获取任务通知，可以设置在退出此函数的时候将任务通知值清零
或者减一。当任务通知用作二值信号量或者计数信号量的时候使
用此函数来获取信号量。
xTaskNotifyWait()等待任务通知，比 ulTaskNotifyTak()更为强大，全功能版任务通
知获取函数。
#endif

