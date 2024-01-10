#include "MultiRotor_systime.H"
#include "timer.h"
#include "led.h"

volatile uint32_t sysTickUptime = 0;

void  SysTick_Configuration(void)
{
	RCC_ClocksTypeDef  rcc_clocks;
	u32  cnts;

	RCC_GetClocksFreq(&rcc_clocks);

	cnts = (uint32_t)rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;
	cnts = cnts / 8;

	SysTick_Config(cnts);
	//滴答定时器1us 计数9   这里装载9000 也就是1MS中断一次
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

uint32_t GetSysTime_us(void) 
{
	u32 ms;
	u32 value;
	ms = sysTickUptime;
	value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
	return value;
}

void Delay_us(uint32_t us)
{
	u32 now = GetSysTime_us();
	while (GetSysTime_us() - now < us);
}

void Delay_ms(uint32_t ms)
{
	while (ms--)
		Delay_us(1000);
}

int time_1h,time_1m,time_1s,time_1ms;
void sys_time()
{ 
	if(time_1ms < 999)
	{
		time_1ms++;
//		LED1=0;
//		time1();
//		LED1=1;
		//Loop_check();
	}
	else
	{
		//IWDG_ReloadCounter();//reload
		time_1ms =0;
		//Loop_check();//////注意这个地方也是需要执行这个函数的！！！
		if(time_1s<59)
		{
			time_1s++;
		}
		else
		{
			time_1s = 0;
			if(time_1m<59)
			{
				time_1m++;
			}
			else
			{
				time_1m = 0;
				if(time_1h<23)
				{
					time_1h++;
				}
				else
				{
					time_1h = 0;
				}
			}
		}
	}
}

volatile float Cycle_T[GET_TIME_NUM][3];

float Get_Cycle_T(u8 item)	
{
	Cycle_T[item][OLD] = Cycle_T[item][NOW];	//上一次的时间
	Cycle_T[item][NOW] = GetSysTime_us()/1000000.0f; //本次的时间
	Cycle_T[item][NEW] = ( ( Cycle_T[item][NOW] - Cycle_T[item][OLD] ) );//间隔的时间（周期）
	return Cycle_T[item][NEW];
}

void Cycle_Time_Init()
{
	u8 i;
	for(i=0;i<GET_TIME_NUM;i++)
	{
		Get_Cycle_T(i);
	}
}

