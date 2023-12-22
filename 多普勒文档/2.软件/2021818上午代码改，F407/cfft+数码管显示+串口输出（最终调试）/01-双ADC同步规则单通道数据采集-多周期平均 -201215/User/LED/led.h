#ifndef _BSP_LED_H2
#define _BSP_LED_H2

#include "stm32f4xx.h"

#define SH1 {	GPIO_SetBits(GPIOA,GPIO_Pin_11);	}
#define SH0 {	GPIO_ResetBits(GPIOA,GPIO_Pin_11);	}

#define ST1 {	GPIO_SetBits(GPIOA,GPIO_Pin_8);		}
#define ST0 {	GPIO_ResetBits(GPIOA,GPIO_Pin_8);	}

#define DS1 {	GPIO_SetBits(GPIOA,GPIO_Pin_15);	}
#define DS0 {	GPIO_ResetBits(GPIOA,GPIO_Pin_15);	}


void LED_GPIO_Config(void);
void output(unsigned char x);
void output_point(u8 x);


#endif /*_BSP_LED_H*/
