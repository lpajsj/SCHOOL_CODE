

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
#include "ange_SysTick.h"
#include "ange_USART.h"
#include "timer.h"
//��Բ�ͬ�ı��������ò�ͬ��stdint.h�ļ�
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

//����
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)

/***************************************************************************************************************/
/*                                        FreeRTOS������������ѡ��                                              */
/***************************************************************************************************************/
#define configUSE_PREEMPTION					1                       //1ʹ����ռʽ�ںˣ�0ʹ��Э��
#define configUSE_TIME_SLICING					1						//1ʹ��ʱ��Ƭ����(Ĭ��ʽʹ�ܵ�)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                       //1�������ⷽ����ѡ����һ��Ҫ���е�����
                                                                        //һ����Ӳ������ǰ����ָ�,����Ӳ��������ȼ���Ŀֻ��32�������ʹ�õ�
                                                                        //MCUû����ЩӲ��ָ��Ļ��˺�Ӧ������Ϊ0��
#define configUSE_TICKLESS_IDLE					0                       //1���õ͹���ticklessģʽ
#define configUSE_QUEUE_SETS					1                       //Ϊ1ʱ���ö���
#define configCPU_CLOCK_HZ						(SystemCoreClock)       //CPUƵ��
#define configTICK_RATE_HZ						(1000)                  //ʱ�ӽ���Ƶ�ʣ���������Ϊ1000�����ھ���1ms
#define configMAX_PRIORITIES					(32)                    //��ʹ�õ�������ȼ�
#define configMINIMAL_STACK_SIZE				((unsigned short)130)   //��������ʹ�õĶ�ջ��С
#define configMAX_TASK_NAME_LEN					(16)                    //���������ַ�������

#define configUSE_16_BIT_TICKS					0                       //ϵͳ���ļ����������������ͣ�
                                                                        //1��ʾΪ16λ�޷������Σ�0��ʾΪ32λ�޷�������
#define configIDLE_SHOULD_YIELD					1                       //Ϊ1ʱ�����������CPUʹ��Ȩ������ͬ���ȼ����û�����
#define configUSE_TASK_NOTIFICATIONS            1                       //Ϊ1ʱ��������֪ͨ���ܣ�Ĭ�Ͽ���
#define configUSE_MUTEXES						1                       //Ϊ1ʱʹ�û����ź���
 #define configQUEUE_REGISTRY_SIZE				8                       //��Ϊ0ʱ��ʾ���ö��м�¼�������ֵ�ǿ���
                                                                        //��¼�Ķ��к��ź��������Ŀ��
#define configCHECK_FOR_STACK_OVERFLOW			0                       //����0ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹���
                                                                        //�û������ṩһ��ջ������Ӻ��������ʹ�õĻ�
                                                                        //��ֵ����Ϊ1����2����Ϊ������ջ�����ⷽ����
#define configUSE_RECURSIVE_MUTEXES				1                       //Ϊ1ʱʹ�õݹ黥���ź���
#define configUSE_MALLOC_FAILED_HOOK			0                       //1ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configUSE_APPLICATION_TASK_TAG			0                       
#define configUSE_COUNTING_SEMAPHORES			1                       //Ϊ1ʱʹ�ü����ź���

/***************************************************************************************************************/
/*                                FreeRTOS���ڴ������й�����ѡ��                                                */
/***************************************************************************************************************/
#define configSUPPORT_DYNAMIC_ALLOCATION        1                       //֧�ֶ�̬�ڴ�����
#define configSUPPORT_STATIC_ALLOCATION			0						 //ֻ�Ǿ�̬�ڴ�
#define configTOTAL_HEAP_SIZE					((size_t)(20*1024))     //ϵͳ�����ܵĶѴ�С

/***************************************************************************************************************/
/*                                FreeRTOS�빳�Ӻ����йص�����ѡ��                                              */
/***************************************************************************************************************/
#define configUSE_IDLE_HOOK						1                       //1��ʹ�ÿ��й��ӣ�0����ʹ��
#define configUSE_TICK_HOOK						0                       //1��ʹ��ʱ��Ƭ���ӣ�0����ʹ��vApplicationTickHook

/***************************************************************************************************************/
/*                                FreeRTOS������ʱ�������״̬�ռ��йص�����ѡ��                                 */
/***************************************************************************************************************/
#define configGENERATE_RUN_TIME_STATS	        1                       //Ϊ1ʱ��������ʱ��ͳ�ƹ���,Ϊһʱ����Ҫ����������
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()  ConfigureTimeForRunTimeStats()//��ʱ��3�ṩʱ��ͳ�Ƶ�ʱ����Ƶ��Ϊ10K��������Ϊ100us
#define portGET_RUN_TIME_COUNTER_VALUE()		FreeRTOSRunTimeTicks	//��ȡʱ��ͳ��ʱ��ֵ

#define configUSE_TRACE_FACILITY				1                       //Ϊ1���ÿ��ӻ����ٵ���
#define configUSE_STATS_FORMATTING_FUNCTIONS	1                       //���configUSE_TRACE_FACILITYͬʱΪ1ʱ���������3������
                                                                        //prvWriteNameToBuffer(),vTaskList(),
                                                                        //vTaskGetRunTimeStats()
                                                                        
/***************************************************************************************************************/
/*                                FreeRTOS��Э���йص�����ѡ��                                                  */
/***************************************************************************************************************/
#define configUSE_CO_ROUTINES 			        0                       //Ϊ1ʱ����Э�̣�����Э���Ժ��������ļ�croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )                   //Э�̵���Ч���ȼ���Ŀ

/***************************************************************************************************************/
/*                                FreeRTOS�������ʱ���йص�����ѡ��                                            */
/***************************************************************************************************************/
#define configUSE_TIMERS				          1                               //Ϊ1ʱ���������ʱ��
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        //�����ʱ�����ȼ�
#define configTIMER_QUEUE_LENGTH		        5                               //�����ʱ�����г���
#define configTIMER_TASK_STACK_DEPTH	        (configMINIMAL_STACK_SIZE*2)    //�����ʱ�������ջ��С

/***************************************************************************************************************/
/*                                FreeRTOS��ѡ��������ѡ��                                                      */
/***************************************************************************************************************/
#define INCLUDE_xTaskGetSchedulerState          1                       
#define INCLUDE_vTaskPrioritySet		        1
#define INCLUDE_uxTaskPriorityGet		        1            //��ȡ�������ȼ�
#define INCLUDE_vTaskDelete				        1
#define INCLUDE_vTaskCleanUpResources	        1
#define INCLUDE_vTaskSuspend			        1
#define INCLUDE_vTaskDelayUntil			        1
#define INCLUDE_vTaskDelay				        1               //�����ʱ����
#define INCLUDE_eTaskGetState			        1
#define INCLUDE_xTimerPendFunctionCall	        1

/***************************************************************************************************************/
/*                                FreeRTOS���ж��йص�����ѡ��              xPortStartScheduler                                    */
/***************************************************************************************************************/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15                      //�ж�������ȼ�
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5                       //ϵͳ�ɹ��������ж����ȼ�
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/***************************************************************************************************************/
/*                                FreeRTOS���жϷ������йص�����ѡ��                                          */
/***************************************************************************************************************/
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler

#endif /* FREERTOS_CONFIG_H */

#if 0
//��غ���
xTaskCreate() ʹ�ö�̬�ķ�������һ������
xTaskCreateStatic() ʹ�þ�̬�ķ�������һ������
xTaskCreateRestricted() ����һ��ʹ�� MPU �������Ƶ���������ڴ�ʹ�ö�̬�ڴ���䡣
vTaskDelete()    ɾ��һ������
vTaskStartScheduler �����������
vTaskEndScheduler() �ر������������
vTaskSuspendAll()   ����������� �����˼��� vTaskSuspendAll()�����������ͬ����Ҳ�õ��ü��� xTaskResumeAll()�Ż����ջָ����������
xTaskResumeAll()    �ָ��������
vTaskSuspend() ����һ������
vTaskResume()  �ָ�һ����������С�
xTaskResumeFromISR() �жϷ������лָ�һ����������С�
taskYIELD()      �����л�
portYIELD_FROM_ISR  �ж������л�
       ����
vListInitialise   ��ʼ������
vListInitialiseItem  ��ʼ��������
vListInsert          ���������
uxListRemove         ������ɾ�� ֻ�Ƕ�������
vListInsertEnd       ��indexǰ����������


taskENTER_CRITICAL()   �����ٽ���
taskEXIT_CRITICAL()    �˳��ٽ���
taskENTER_CRITICAL_FROM_ISR()  �жϼ��ٽ�
 taskEXIT_CRITICAL_FROM_ISR()  �˳��ж��ٽ�
 taskDISABLE_INTERRUPTS()       ���ж�
 taskENABLE_INTERRUPTS()        ���ж�
 
 �ڴ�
 vPortFree  �ͷ��ڴ�
 
 vTaskStepTick �� �� �� �� ʹ �� FreeRTOS �� �� �� �� tickless ģ ʽ �� ʱ �� �� �� �� �� �� ��configUSE_TICKLESS_IDLE Ϊ 1��
 
 �������API����
 uxTaskPriorityGet();           �˺���������ȡָ����������ȼ�
 vTaskPrioritySet()             �ı��������ȼ�
 uxTaskGetSystemState()         �˺������ڻ�ȡϵͳ���������������׳̬
 vTaskGetInfo()                 �˺���Ҳ��������ȡ����׳̬�ģ������ǻ�ȡָ���ĵ��������׳̬�� Ҫʹ�ô˺����Ļ���configUSE_TRACE_FACILITY Ҫ����Ϊ 1
 xTaskGetApplicationTaskTag()   �˺������ڻ�ȡ����� Tag(��ǩ)ֵ
 xTaskGetCurrentTaskHandle()    �˺������ڻ�ȡ��ǰ�����������
 xTaskGetHandle()               �����������ֻ�ȡ����������������
 xTaskGetIdleTaskHandle()       �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��
 uxTaskGetStackHighWaterMark()  �˺������ڼ������Ӵ����õ����ڵ���ʷʣ����Сֵ INCLUDE_uxTaskGetStackHighWaterMark
 eTaskState eTaskGetState       �˺������ڲ�ѯĳ�����������׳̬
 pcTaskGetName                  ����ĳ�����������������ѯ��������Ӧ��������
  xTaskGetTickCount()           �˺������ڲ�ѯ���������������������ʱ������� xTickCount ��ֵ
	xTaskGetTickCountFromISR()    �˺����� xTaskGetTickCount()���жϼ��汾���������жϷ������л�ȡʱ�������xTickCount ��ֵ
	xTaskGetSchedulerState()      �˺������ڻ�ȡ FreeRTOS ������������������
	uxTaskGetNumberOfTasks()      �˺������ڲ�ѯϵͳ��ǰ���ڵ���������     ֱ�ӵ���
	vTaskList()                   �˺����ᴴ��һ�����������ÿ���������ϸ��Ϣ   
vTaskGetRunTimeStats()          	 FreeRTOS ����ͨ����ص�������ͳ�����������ʱ����ϢconfigGENERATE_RUN_TIME_STATS �� configUSE_STATS_FORMATTING_FUNCTIONS
portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()���˺�������ʼ��һ��������
����Ҫʵ��һ�¼����궨���ṩʱ��ͳ�ƹ��������ʱ���� һ���Ƕ�ʱ��/�����������ʱ���ķֱ���һ��Ҫ�� FreeRTOS
��ϵͳʱ�Ӹߣ�һ�����ʱ����ʱ�Ӿ��ȱ�ϵͳʱ�ӵĸ� 10~20 ���Ϳ����ˡ�
�� portGET_RUN_TIME_COUNTER_VALUE()����
portALT_GET_RUN_TIME_COUNTER_VALUE(Time)�� ��������ʵ������һ������
�ˣ��������������ṩ��ǰ��ʱ����ʱ��ֵ��
vTaskSetApplicationTaskTag()       �˺�����������ĳ������ı�ǩֵ 
SetThreadLocalStoragePointer()     �˺������������̱߳��ش洢ָ���ֵ
 GetThreadLocalStoragePointer()    �� �� �� �� �� �� ȡ �� �� �� �� �� �� ָ �� �� ֵconfigNUM_THREAD_LOCAL_STORAGE_POINTERS ����Ϊ 0
 
 ����
 xQueueCreate();
 xQueueCreateStatic();
 xQueueGenericCreate();
 xQueueGenericCreateStatic()
 ���� xQueueSend()�� xQueueSendToBack()�� xQueueSendToFront()  xQueueOverwrite
 ���� xQueueSendFromISR()��xQueueSendToBackFromISR()��xQueueSendToFrontFromISR()  xQueueOverwriteFromISR
 prvLockQueue()�� prvUnlockQueue()��
 ���񼶳��Ӻ���
xQueueReceive()
�Ӷ����ж�ȡ������(��Ϣ)�����Ҷ�ȡ��
�Ժ�ɾ����������(��Ϣ)
xQueuePeek()
�Ӷ����ж�ȡ������(��Ϣ)�����Ҷ�ȡ��
�Ժ�ɾ��������(��Ϣ)
�жϼ����Ӻ���
xQueueReceiveFromISR()
�Ӷ����ж�ȡ������(��Ϣ)�����Ҷ�ȡ��
�Ժ�ɾ����������(��Ϣ)�������жϷ���
������
xQueuePeekFromISR ()
�Ӷ����ж�ȡ������(��Ϣ)�����Ҷ�ȡ��
�Ժ�ɾ��������(��Ϣ)�������жϷ���
������
            �ź�����ֵ  
��ֵ�ź��������ɹ��Ժ�Ҫ���ͷ�һ��
vSemaphoreCreateBinary ()
�� ̬ �� �� �� ֵ �� �� �� �� �� �� �� �� �� ��
FreeRTOS ��ʹ�õĴ�����ֵ�ź����� API ��
����
xSemaphoreCreateBinary()
��̬������ֵ�ź����� �°� FreeRTOS ʹ�ô�
����������ֵ�ź�����
xSemaphoreCreateBinaryStatic() ��̬������ֵ�ź�����
xSemaphoreGive() �����ź����ͷź���
xSemaphoreGiveFromISR() �жϼ��ź����ͷź���
xSemaphoreTake() ���񼶻�ȡ�ź�������
xSemaphoreTakeFromISR() �жϼ���ȡ�ź�������
            �������ź���
xSemaphoreCreateCounting() ʹ�ö�̬���������������ź�����
xSemaphoreCreateCountingStatic() ʹ�þ�̬���������������ź���
            �������ź���
xSemaphoreCreateMutex() ʹ�ö�̬�������������ź�����
xSemaphoreCreateMutexStatic() ʹ�þ�̬�������������ź�����
//           �ݹ��ź���
Ҫʹ�õݹ黥���ź����Ļ��� configUSE_RECURSIVE_MUTEXES ����Ϊ 1��
xSemaphoreCreateRecursiveMutex() ʹ�ö�̬���������ݹ黥���ź�����
xSemaphoreCreateRecursiveMutexStatic() ʹ�þ�̬���������ݹ黥���ź�����
//          �����ʱ��
xTimerReset() ��λ�����ʱ�������������С�
xTimerResetFromISR() ��λ�����ʱ���������жϷ������С�
xTimerCreate() ʹ�ö�̬�������������ʱ����
xTimerCreateStatic() ʹ�þ�̬�������������ʱ��
xTimerStart() ���������ʱ�������������С�
xTimerStartFromISR() ���������ʱ���������ж��С�
xTimerStop() ֹͣ�����ʱ�������������С�
xTimerStopFromISR() ֹͣ�����ʱ���������жϷ������С�
//        �¼���־��
xEventGroupCreate() ʹ�ö�̬���������¼���־�顣``1234567890QWERPASDFGHJKLLZXCVBNMZXCVBNMNM122345969787597PASDFGHJKLLZXCVBDDDDssss
xEventGroupCreateStatic() ʹ�þ�̬���������¼���־��123456789qwertyuiopasdfghjklzxcvbnmkkkll	lL
xEventGroupClearBits() ��ָ�����¼�λ���㣬���������С�
xEventGroupClearBitsFromISR() ��ָ�����¼�λ���㣬�����жϷ�������
xEventGroupSetBits() ��ָ�����¼�λ�� 1�����������С�
xEventGroupSetBitsFromISR() ��ָ�����¼�λ�� 1�������жϷ������С�
xEventGroupGetBits() ��ȡ��ǰ�¼���־���ֵ(�����¼�λ��ֵ)�����������С�
xEventGroupGetBitsFromISR() ��ȡ��ǰ�¼���־���ֵ�������жϷ������С�
xEventGroupWaitBits()       �ȴ�ָ�����¼�λ
//        ����֪ͨ
xTaskNotify()����֪ͨ������ֵ֪ͨ���Ҳ�������������ԭֵ֪ͨ�����������С�
xTaskNotifyFromISR() ����֪ͨ������ xTaskNotify()���жϰ汾��
xTaskNotifyGive()����֪ͨ������ֵ֪ͨ���Ҳ��������������ֵ֪ͨ���˺����Ὣ���������ֵ֪ͨ��һ�����������С�
vTaskNotifyGiveFromISR() ����֪ͨ������ xTaskNotifyGive()���жϰ汾��
xTaskNotifyAndQuery()����֪ͨ������ֵ֪ͨ���ұ������������ԭֵ֪ͨ�����������С�
xTaskNotiryAndQueryFromISR()����֪ͨ������ xTaskNotifyAndQuery()���жϰ汾�������жϷ������С�
ulTaskNotifyTake()��ȡ����֪ͨ�������������˳��˺�����ʱ������ֵ֪ͨ����
���߼�һ��������֪ͨ������ֵ�ź������߼����ź�����ʱ��ʹ
�ô˺�������ȡ�ź�����
xTaskNotifyWait()�ȴ�����֪ͨ���� ulTaskNotifyTak()��Ϊǿ��ȫ���ܰ�����ͨ
֪��ȡ������
#endif

