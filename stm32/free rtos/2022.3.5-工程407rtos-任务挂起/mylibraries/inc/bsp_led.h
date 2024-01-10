#ifndef __LED_H
#define	__LED_H

#include "stm32f4xx.h"

//引脚定义
/*******************************************************/

#define LED1_PIN                  GPIO_Pin_9                 
#define LED1_GPIO_PORT            GPIOF                      
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOF


#define LED2_PIN                  GPIO_Pin_10                 
#define LED2_GPIO_PORT            GPIOF                      
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOF


#define BEEP_PIN                  GPIO_Pin_8                 
#define BEEP_GPIO_PORT            GPIOF                       
#define BEEP_GPIO_CLK             RCC_AHB1Periph_GPIOF
/************************************************************/


/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	
#define BEEP PFout(8)
//#define LED1(a)	if (a)	\
//					GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);\
//					else		\
//					GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

//#define LED2(a)	if (a)	\
//					GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);\
//					else		\
//					GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

//#define BEEP(a)	if (a)	\
//					GPIO_SetBits(BEEP_GPIO_PORT,BEEP_PIN);\
//					else		\
//					GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_PIN)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define LED0_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED0_OFF			digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED0_ON				digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED1_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED1_OFF			digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED1_ON				digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define BEEP_TOGGLE		digitalToggle(BEEP_GPIO_PORT,BEEP_PIN)
#define BEEP_OFF			digitalLo(BEEP_GPIO_PORT,BEEP_PIN)
#define BEEP_ON				digitalHi(BEEP_GPIO_PORT,BEEP_PIN)
void LED_GPIO_Config(void);

//key
#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
#define WK_UP 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0


/*下面方式是通过位带操作方式读取IO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/


#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define WKUP_PRES   4

void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);  		//按键扫描函数	


#endif /* __LED_H */
