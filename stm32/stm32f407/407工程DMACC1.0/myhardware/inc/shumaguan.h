#ifndef __SHUMAGUAN_H
#define __SHUMAGUAN_H
#include "ange_systick.h"


//需要根据需要修改IO口
#define SHUMAGUANPORT GPIOB  	//定义IO接口
#define DATA_595 GPIO_Pin_12	//定义LED1的IO接口
#define STCP_595 GPIO_Pin_10	//定义LED2的IO接口
#define SHCP_595 GPIO_Pin_11	//定义LED2的IO接口

void ShuMaGuan_Init(void);	//数码管初始化
void display(u8 a,u8 b,u8 c,u8 d,u8 e,u8 f);


#endif


//595管脚--->数码管管脚
//a->c
//b->h
//c->f
//d->a
//e->b
//f->d
//g->e
//h->g


//电路从上到下管脚 VCC GND DS GND（可不连） STCP SHCP
