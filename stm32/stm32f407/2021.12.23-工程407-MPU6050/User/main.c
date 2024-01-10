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
uint32_t Task_Delay[NumOfTask]={0};
/*
ע��������ʱ������ʹ��,
*/
extern u32 time;
u8 shuju[256];
u8 shuju1[256];
u8 dizhi=0;
	short Acel[3];
	short Gyro[3];
	float Temp;
float pitch,roll,yaw; 		//ŷ����
int main(void)
{
	u32 i;
	HSE_SetSysClock(8,336,2,7);
	ange_USART_init(115200);
//	SysTickInitms();
	ange_TIMj_init();
	LED_GPIO_Config();
	I2cMaster_Init();
	MPU6050_Init();
//	MPU_Init();
	__nop();
	for(i=0;i<256;i++)
	{
		shuju[i]=i;
	}
	ange_I2C_datawrite(dizhi,256,shuju);
	ange_I2C_dataread(0,256,shuju1);
	for(i=0;i<256;i++)
	{
		printf("%d ",shuju1[i]);
	}
	while(mpu_dmp_init())
	{
		printf("MPU6050��ʼ��ʧ��");
	}
  while (1)
  {
	if (MPU6050ReadID() == 1)
	{	
		while(1)
		{
			///
			if(Task_Delay[0]==TASK_ENABLE)
			{
				Task_Delay[0]=1000;
		LED1_ON;
		LED2_ON;
			}
			if(Task_Delay[1]==0)
			{
		   LED1_OFF;
		   LED2_OFF;
				MPU6050ReadAcc(Acel);
				printf("���ٶȣ�%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
				MPU6050ReadGyro(Gyro);
				printf("    ������%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
				MPU6050_ReturnTemp(&Temp);
				printf("    �¶�%8.2f",Temp);				
				while(mpu_dmp_get_data(&pitch,&roll,&yaw)==0);
				
				Temp=pitch;
					printf("pitch:%.1f  ",Temp);				
				Temp=roll;
					printf("roll:%.1f  ",Temp);
				Temp=yaw;
					printf("yaw:%.1f\r\n",Temp);
				
				Task_Delay[1]=0; //����һ�����ݣ��ɸ����Լ���������߲���Ƶ�ʣ���100ms����һ��
			}
		}

	}
	else
	{
			printf("\r\nû�м�⵽MPU6050��������\r\n");
		while(1);	
	}

  }
}






























