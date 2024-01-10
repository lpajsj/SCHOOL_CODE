#include "led.h"

//LED IO��ʼ��
/*
PA8  485OE
PC4  PD6  PD5  PD4   LEDָʾ��
PD7   ������
*/
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8 485OE
//	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.0,1
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.4,5	
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.0
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 �����
	GPIO_SetBits(GPIOC,GPIO_Pin_4);						 //PC.4 �����
	GPIO_SetBits(GPIOD,GPIO_Pin_4);						 //PD.4 �����
	GPIO_SetBits(GPIOD,GPIO_Pin_5);						 //PD.5 �����
	GPIO_SetBits(GPIOD,GPIO_Pin_6);						 //PD.6 �����
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);					 //PD.7  �����

}

void Max485()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.0
		
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
}
 
