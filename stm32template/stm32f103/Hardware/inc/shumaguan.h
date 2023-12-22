#ifndef __SHUMAGUAN_H
#define __SHUMAGUAN_H
#include "ange_systick.h"

#define delayus_shumaguan SysTick_delayus
//需要根据需要修改IO口
#define SHUMAGUANPORT GPIOB  	//定义IO接口
#define DATA_595 GPIO_Pin_12	//定义LED1的IO接口
#define STCP_595 GPIO_Pin_10	//定义LED2的IO接口
#define SHCP_595 GPIO_Pin_11	//定义LED2的IO接口

void ShuMaGuan_Init(void);	//数码管初始化
void display(u8 a,u8 b,u8 c,u8 d,u8 e,u8 f);
/*安哥添加*/
#define ange_DATA595_GPIO_CLK   RCC_APB2Periph_GPIOB
#define ange_DATA595_GPIO_PORT  GPIOB
#define ange_DATA595_GPIO_Pin   GPIO_Pin_11
#define data595       PBout(11)
#define ange_STCP595_GPIO_CLK   RCC_APB2Periph_GPIOB
#define ange_STCP595_GPIO_PORT  GPIOB
#define ange_STCP595_GPIO_Pin   GPIO_Pin_13
#define stcp595       PBout(13)
#define ange_SHCP595_GPIO_CLK   RCC_APB2Periph_GPIOB
#define ange_SHCP595_GPIO_PORT  GPIOB
#define ange_SHCP595_GPIO_Pin   GPIO_Pin_15
#define shcp595       PBout(15)
void ange_595_GPIO_init(void);
void ange_595_xianshi(void);
extern u8 shuma595[];

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
