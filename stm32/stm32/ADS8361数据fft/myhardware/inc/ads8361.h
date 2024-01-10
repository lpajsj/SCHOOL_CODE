#ifndef __ads8361_H
#define __ads8361_H	
#include "stm32f10x.h"
#include "ange_systick.h"
//#define ads8361_OUTA_GPIO_CLK     RCC_APB2Periph_GPIOA //a�����������
//#define ads8361_OUTA_GPIO_PORT     GPIOA
//#define ads8361_OUTA_GPIO_Pin   GPIO_Pin_6
//#define ADATA PAin(6)//
//#define ads8361_OUTB_GPIO_CLK     RCC_APB2Periph_GPIOB //b�����������
//#define ads8361_OUTB_GPIO_PORT    GPIOB
//#define ads8361_OUTB_GPIO_Pin     GPIO_Pin_8
//#define BDATA    PBin(9)
//#define ads8361_CLOCK_GPIO_CLK    RCC_APB2Periph_GPIOA  //ads8361ʱ������
//#define ads8361_CLOCK_GPIO_PORT     GPIOA
//#define ads8361_CLOCK_GPIO_Pin  GPIO_Pin_5
//#define CLOCK PAout(5)//
//#define ads8361_CS_GPIO_CLK       RCC_APB2Periph_GPIOA //Ƭѡ
//#define ads8361_CS_GPIO_PORT      GPIOA  
//#define ads8361_CS_GPIO_Pin      GPIO_Pin_4
//#define CS    PAout(4)
//#define ads8361_RD_GPIO_CLK       RCC_APB2Periph_GPIOA  //ת������
//#define ads8361_RD_GPIO_PORT     GPIOA
//#define ads8361_RD_GPIO_Pin     GPIO_Pin_7
//#define RD    PAout(7)//
//#define ads8361_A0_GPIO_CLK       RCC_APB2Periph_GPIOA //A0 ��������
//#define ads8361_A0_GPIO_PORT     GPIOB
//#define ads8361_A0_GPIO_Pin     GPIO_Pin_12
//#define A0    PBout(12)//
//#define ads8361_M0_GPIO_CLK       RCC_APB2Periph_GPIOA  //ת������
//#define ads8361_M0_GPIO_PORT     GPIOB
//#define ads8361_M0_GPIO_Pin     GPIO_Pin_13
//#define M0    PBout(13)//
//#define ads8361_M1_GPIO_CLK       RCC_APB2Periph_GPIOA  //ת������
//#define ads8361_M1_GPIO_PORT     GPIOB
//#define ads8361_M1_GPIO_Pin     GPIO_Pin_14
//#define M1    PBout(14)//
//////////////////////////////////////////////////////////
#define ads8361_OUTA_GPIO_CLK     RCC_APB2Periph_GPIOC //a�����������
#define ads8361_OUTA_GPIO_PORT    GPIOC
#define ads8361_OUTA_GPIO_Pin   	GPIO_Pin_0
#define ADATA PCin(0)//
#define ads8361_OUTB_GPIO_CLK     RCC_APB2Periph_GPIOC //b�����������
#define ads8361_OUTB_GPIO_PORT    GPIOC
#define ads8361_OUTB_GPIO_Pin     GPIO_Pin_1
#define BDATA    PCin(1)
#define ads8361_CLOCK_GPIO_CLK    RCC_APB2Periph_GPIOC  //ads8361ʱ������
#define ads8361_CLOCK_GPIO_PORT   GPIOC
#define ads8361_CLOCK_GPIO_Pin  	GPIO_Pin_3
#define CLOCK PCout(3)//
#define ads8361_CS_GPIO_CLK       RCC_APB2Periph_GPIOA //Ƭѡ
#define ads8361_CS_GPIO_PORT      GPIOA  
#define ads8361_CS_GPIO_Pin     	GPIO_Pin_0
#define CS    PAout(0)
#define ads8361_RD_GPIO_CLK       RCC_APB2Periph_GPIOA  //ת������
#define ads8361_RD_GPIO_PORT     	GPIOA
#define ads8361_RD_GPIO_Pin    	 	GPIO_Pin_1
#define RD    PAout(1)//
#define ads8361_A0_GPIO_CLK       RCC_APB2Periph_GPIOA //A0 ��������
#define ads8361_A0_GPIO_PORT    	GPIOA
#define ads8361_A0_GPIO_Pin     	GPIO_Pin_4
#define A0    PAout(4)//
#define ads8361_M0_GPIO_CLK       RCC_APB2Periph_GPIOA  //ת������
#define ads8361_M0_GPIO_PORT     	GPIOA
#define ads8361_M0_GPIO_Pin     	GPIO_Pin_5
#define M0    PAout(5)//
#define ads8361_M1_GPIO_CLK       RCC_APB2Periph_GPIOA  //ת������
#define ads8361_M1_GPIO_PORT     	GPIOA
#define ads8361_M1_GPIO_Pin     	GPIO_Pin_7
#define M1    PAout(7)//
void ads8361_init(void);
void ads8361_read00(u8 a);  //˫ͨ����ȡCA1 CB1 ͨ��0δ�������� ab����ͬʱ���  180Hz���Զ�256��
	void ads8361_read01(u8 a); //˫ͨ����ȡCA1 CB1 ͨ��0�������ݳ��� ֻ��a�������  130Hz���Զ�256��
		void ads8361_read10(void); //��ͨ�� abͬʱ���  100Hz���Զ�256��
			void ads8361_read11(void); //��ͨ�� a���   70Hz���Զ�256��
void ads8361_read00a1(void);  //˫ͨ����ʽ ����ֻ��ȡa1   250hz���Զ�256��
	void ads8361_read00b1(void); //˫ͨ����ʽ ��ֻ��b1  250hz���Զ�256��
	void ads8361_read00a0(void); //�������Ϊ A0״̬
		void ads8361_read00b0(void); //�������Ϊ A0״̬
/////
void ADS8361_Read_01_OUTA(uint32_t CH,uint32_t *data_a_01,uint32_t *data_b_01);//��M0M1=01�£���ȡAͨ��������

#endif
