#include "stm32f4xx.h"
#include "main.h"
#include "ange_SysTick.h"
#include "ange_USART.h"
#include "ange_rcc.h"
#include "ange_exti.h"
#include "ange_dma.h"
#include "ange_ad.h"
#include "ange_timj.h"
#include "ange_timt.h"
#include "ange_timg.h"
#include "ange_da.h"
#include "ange_spi.h"
#include "MS5611.h"
#include "ange_iic_24c02.h"
#include "bsp_led.h" 
#include "MPU6050.h"
#include "ange_iic.h"
#include "mpu6050_2.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "QMC5883.h"
#include "icm20689.h"
#include "oled2.h"
#include "time.h"
#define DAC902_CLK PAout(4)

#define AD9220_D12 PCin(11)	//OTR 溢出位
#define AD9220_D11 PCin(10)
#define AD9220_D10 PCin(9)
#define AD9220_D9  PCin(8)
#define AD9220_D8  PCin(7)
#define AD9220_D7  PCin(6)
#define AD9220_D6  PCin(5)
#define AD9220_D5  PCin(4)
#define AD9220_D4  PCin(3)
#define AD9220_D3  PCin(2)
#define AD9220_D2  PCin(1)
#define AD9220_D1  PCin(0)
#define AD9220_D0  PCin(12)
uint32_t Task_Delay[NumOfTask]={0};
/*
注意两种延时函数的使用,
*/
#define FIFOLEN 1024
volatile uint16_t AD_Data[FIFOLEN] = {0};

volatile uint16_t AD_DataFIFO[FIFOLEN],fifoPtr = 0;
int32_t int_sampleVol[FIFOLEN];
float adf[FIFOLEN];
void AD9220_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure ; 

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	GPIO_Init(GPIOC ,&GPIO_InitStructure) ;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
}

//uint16_t AD9220ReadData(void)
//{
//  uint16_t data;
//	DAC902_CLK = 0;
//	data = GPIO_ReadInputData(GPIOC)&0X1FFF;
////	data = GPIO_ReadInputData(GPIOC)&0X1FFF;
////	data = GPIO_ReadInputData(GPIOC)&0X1FFF;
////	data = GPIO_ReadInputData(GPIOC)&0X1FFF;//增加延时
//	data = ((data<<1)&0X1FFF)|(data>>12);//对管脚数据重新排序，详细对应关系查看AD9220.H中定义
//	DAC902_CLK = 1;
//	return (data&0X0FFF);
//}

uint16_t AD9220ReadData(void)
{
  uint16_t data;
	DAC902_CLK = 0;
	data = GPIO_ReadInputData(GPIOC)&0X1FFF;
//	data = GPIO_ReadInputData(GPIOC)&0X1FFF;
//	data = GPIO_ReadInputData(GPIOC)&0X1FFF;
//	data = GPIO_ReadInputData(GPIOC)&0X1FFF;//增加延时
//	data = ((data<<1)&0X1FFF)|(data>>12);//对管脚数据重新排序，详细对应关系查看AD9220.H中定义
	DAC902_CLK = 1;
	return (data);
}
int main(void)
{
	int i;
//	char showLcd[30];
	AD9220_IO_Init();//AD9220初始化
	ange_USART_init(115200);
	DAC902_CLK=0;
	SysTick_delayms(1000);
//	initial_lcd();
//	LCD_Show_CEStr(0,0,"AD9220");//黑色
//	LCD_Show_CEStr(0,2,"Read Test");//黑色
//	LCD_Refresh_Gram();
	
	while(1)
	{
		for(i=0;i<FIFOLEN;i++)
		{
		AD_Data[i] = AD9220ReadData();	//AD数据读取800K
		}
		for(i=0;i<FIFOLEN;i++)
		{
		AD_Data[i] = ((AD_Data[i]<<1)&0X1FFF)|(AD_Data[i]>>12);//对管脚数据重新排序，详细对应关系查看AD9220.H中定义
			AD_Data[i]&=0x0fff;
		adf[i]=5000.0f*((float)AD_Data[i]/4096);
		printf("%f\r\n",adf[i]);
		}
//		int_sampleVol[fifoPtr++] = ((int32_t)5000)*((float)((short)AD_Data)/4096);	//数据转换到电压
//		fifoPtr %= FIFOLEN;
//		sprintf(showLcd, "%04d", int_sampleVol[0]);	
//		LCD_ShowString(0,24 , 32, (const u8*)showLcd);	//显示电压数据
//		LCD_Refresh_Gram();
	}
}













