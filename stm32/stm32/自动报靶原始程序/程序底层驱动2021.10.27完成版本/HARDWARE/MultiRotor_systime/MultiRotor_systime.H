#ifndef _MultiRotor_systime_H
#define _MultiRotor_systime_H

/*   系统头文件   */
#include <stm32f10x.h>        // 包含F103固件库 

#define TICK_PER_SECOND 500  // 每秒钟中断次数
#define TICK_US	(1000000/TICK_PER_SECOND)

#define GET_TIME_NUM  (5)   //获取时间数量
typedef struct
{
	u8 check_flag;
	u8 err_flag;
	s16 cnt_1ms;
	s16 cnt_2ms;
	s16 cnt_4ms;
	s16 cnt_10ms;
	s16 cnt_20ms;
	s16 cnt_50ms;
	u16 time;
}loop_t;

enum
{
	NOW = 0,
	OLD,
	NEW,
};

void  SysTick_Configuration(void);
uint32_t GetSysTime_us(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void sys_time(void);
float Get_Cycle_T(u8 item);
void Cycle_Time_Init(void);

extern volatile uint32_t sysTickUptime;
extern int time_1h,time_1m,time_1s,time_1ms;

#endif
