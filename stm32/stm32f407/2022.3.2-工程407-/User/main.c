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
uint32_t Task_Delay[NumOfTask]={0};
/*
注意两种延时函数的使用,
*/
//extern u32 time;
//u8 shuju[256];
//u8 shuju1[256];
//u8 dizhi=0;
//	short Acel[3];
//	short Gyro[3];
//	float Temp;
//float pitch,roll,yaw; 		//欧拉角
//float raw_hx,raw_hy,raw_hz,raw_t;
int16_t icm20689_buffer_raw[6];
float gx,gy,gz,ax,ay,az;
char oled_buffer[80];
int main(void)
{
	u16 x=0;
	u32 i;
	HSE_SetSysClock(8,336,2,7);
	ange_USART_init(115200);
	ange_TIMj_init();
//	MPU6050_Init();
//	qmc5883_init();
	ICM20689_Init();
	MS561101BA_Init();  ///加上这个的原因是将5611的CS管脚至高
	  SPI3_Init();
	  OLED_Init();
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
				Task_Delay[1]=0;

			Get_ICM20689_Raw(icm20689_buffer_raw);
			gx=(float)icm20689_buffer_raw[3]/16.4f;
			gy=(float)icm20689_buffer_raw[4]/16.4f;
			gz=(float)icm20689_buffer_raw[5]/16.4f;
			
			ax=(float)icm20689_buffer_raw[0]/16.384f;
			ay=(float)icm20689_buffer_raw[1]/16.384f;
			az=(float)icm20689_buffer_raw[2]/16.384f;
			sprintf(oled_buffer,"陀螺仪:%5.1f ",gx);
			OLED_Display_GB2312_string(0,0,(u8*)oled_buffer);//
			sprintf(oled_buffer,"%5.1f ",gy);
			OLED_Display_GB2312_string(0,2,(u8*)oled_buffer);//
			sprintf(oled_buffer,"%5.1f ",gz);
			OLED_Display_GB2312_string(60,2,(u8*)oled_buffer);//
			sprintf(oled_buffer,"加速度:%5.1f ",ax);
			OLED_Display_GB2312_string(0,4,(u8*)oled_buffer);//
			sprintf(oled_buffer,"%5.1f ",ay);
			OLED_Display_GB2312_string(0,6,(u8*)oled_buffer);//
			sprintf(oled_buffer,"%5.1f ",az);
			OLED_Display_GB2312_string(60,6,(u8*)oled_buffer);//
			SysTick_delayms(2);
			}
			if(Task_Delay[2]==0)
			{
				Task_Delay[2]=0;
			}
		}

  }
}






























