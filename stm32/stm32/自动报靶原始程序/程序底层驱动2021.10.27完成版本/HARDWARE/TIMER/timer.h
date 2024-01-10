#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

//extern u16 fq,test;
//void TIM3_Int_Init(u16 arr,u16 psc);
//void TIM3_PWM_Init(u16 arr,u16 psc);



void TIM1_Cap_Init(u16 arr,u16 psc);
void TIM3_Cap_Init(u16 arr,u16 psc);
void TIM4_Cap_Init(u16 arr,u16 psc);
void time(void);
//void time3(void);
//void time4(void);
#endif
