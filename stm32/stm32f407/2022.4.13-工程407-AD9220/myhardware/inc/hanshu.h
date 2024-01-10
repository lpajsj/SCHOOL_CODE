#ifndef _HANSHU_H
#define _HANSHU_H
#include "stm32f10x.h"
#include <math.h>
extern float xishu,pianzhi;

extern float xishudata[255],pianzhidata[255];
extern uint8_t fengduan[255];


void xianxingnihe(float dataX[],float dataY[],uint8_t number);
void fengduannihe(float dataX[],float dataY[],uint8_t fengduan[],uint8_t number);

#endif
