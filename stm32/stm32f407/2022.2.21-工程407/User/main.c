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
#include "MS5611.h"
#include "ange_iic_24c02.h"
#include "bsp_led.h" 
#include "MPU6050.h"
#include "ange_iic.h"
#include "mpu6050_2.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "QMC5883.h"
uint32_t Task_Delay[NumOfTask]={0};
/*
注意两种延时函数的使用,
*/
extern u32 time;
u8 shuju[256];
u8 shuju1[256];
u8 dizhi=0;
	short Acel[3];
	short Gyro[3];
	float Temp;
float pitch,roll,yaw; 		//欧拉角
float raw_hx,raw_hy,raw_hz,raw_t;
int main(void)
{
	u16 x=0;
	u32 i;
	HSE_SetSysClock(8,336,2,7);
	ange_USART_init(115200);
//	SysTickInitms();
	ange_TIMj_init();
//	MPU6050_Init();
	qmc5883_init();
	__nop();
	if(x&0x02)
{
	x&=(~0x02);
}
else
{
	x|=0x02;
}
  while (1)
  {
		while(1)
		{
			///
			if(Task_Delay[0]==TASK_ENABLE)
			{
				Task_Delay[0]=5000;
				x=!x;
				if(x)
				{

				}
				else
				{

					}
			}
			if(Task_Delay[1]==0)
			{
				Task_Delay[1]=500;

			printf("%0.f  %0.f  %0.f  %0.f\n",raw_hx,raw_hy,raw_hz,raw_t);
			}
			if(Task_Delay[2]==0)
			{
				Task_Delay[2]=0;
				qmc5883_get_raw_data(&raw_hx,&raw_hy,&raw_hz,&raw_t);
			}
		}

  }
}






























