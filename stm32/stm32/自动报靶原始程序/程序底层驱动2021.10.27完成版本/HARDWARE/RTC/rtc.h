#ifndef __rtc_h_
#define __rtc_h_
//***************************************************
#include "stm32f10x.h"

uint8_t RTC_Init(void);
uint8_t Is_Leap_Year(uint16_t year);
uint8_t RTC_Set(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec);
void RTC_Set_64(unsigned char *timebuff);
uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day);
uint8_t RTC_Get(void);
uint8_t str_cmpx(uint8_t*s1,uint8_t*s2,uint8_t len);
//void Auto_Time_Set(void);

//时间结构体初始化
struct rtc
{
uint16_t w_year;
uint8_t w_month;
uint8_t w_date;
uint8_t hour;
uint8_t min;
uint8_t sec;
uint8_t week;
};
//***************************************************
#endif
