#ifndef __SHUMAGUAN_H
#define __SHUMAGUAN_H
#include "ange_systick.h"


//��Ҫ������Ҫ�޸�IO��
#define SHUMAGUANPORT GPIOB  	//����IO�ӿ�
#define DATA_595 GPIO_Pin_12	//����LED1��IO�ӿ�
#define STCP_595 GPIO_Pin_10	//����LED2��IO�ӿ�
#define SHCP_595 GPIO_Pin_11	//����LED2��IO�ӿ�

void ShuMaGuan_Init(void);	//����ܳ�ʼ��
void display(u8 a,u8 b,u8 c,u8 d,u8 e,u8 f);


#endif


//595�ܽ�--->����ܹܽ�
//a->c
//b->h
//c->f
//d->a
//e->b
//f->d
//g->e
//h->g


//��·���ϵ��¹ܽ� VCC GND DS GND���ɲ����� STCP SHCP
