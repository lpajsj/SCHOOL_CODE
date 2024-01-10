#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define MAX485_OE PAout(8) // PA8
#define LED0      PCout(4)// PC4
#define LED1      PAout(4)// PD6	
#define LED2      PDout(5)// PD5
#define LED3      PDout(4)// PD4	
#define BELL      PDout(7) // PD7

void LED_Init(void);//初始化
void Max485(void);//MAX485,控制脚输出高电平
		 				    
#endif
