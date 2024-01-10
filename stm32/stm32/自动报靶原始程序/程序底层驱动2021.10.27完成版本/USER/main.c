#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "I2C.h"
#include "mpu6050.h"
#include "tlc2543.h"   
#include "attitude.h"
#include "SPI.h"
#include "flash.h"
#include "MultiRotor_systime.H"
#include "wdg.h"
#include "timer.h"
#include "check.h"
#include "stm32_flash.h"
#include "rtc.h"

extern u8 data1[58];            //姿态数据包 包括 舵机电压、转速、PWM、陀螺仪、发电机参数  200ms发一次
extern u8 data2[22];            //电压温度数据包 包括油量位置、供电电压、发动机温度参数    1s发一次
extern u8 data3[48];            //GPS数据包  包括经纬度、地速、时间、磁力计等GPS获取的参数 1s发一次

extern struct rtc RTC_time;			//时间结构体
extern u8 curtime[8];						//64位时间戳数组 8字节 串口
extern u8 curtime1[8];					//64位时间戳数组 8字节 RTC
extern u8 curtime2[8];					//64位时间戳数组 8字节 FLASH

u8 data[58];										//FLASH存储缓存

u8 com5_data[10];

u8 number_4G;               		//数据发送计数器  每发一帧自动加1

extern u8 sys_ID;   						//0x08030000   ID号地址内部FLASH
extern u8 par_ID;
extern u8 Write_ID;

extern u32 flash_addr;					//flash存储地址
extern u16 sector;     					//扇区地址 0--511 共512个扇区，每个扇区0x1000=4096字节

extern u16 recoad_min; 			//回读FLASH 时间 秒
u32 flash_read_addr;						//回读FLASH 地址

extern u16 high;								//高度

u8 tempreture1,tempreture2,tempreture3,tempreture4,tempreture5;
u8 tempreture6,tempreture7,tempreture8,tempreture9;                //温度

u8 DJ_voli1,DJ_voli2,DJ_voli3,DJ_voli4,DJ_voli5;         //舵机电压
u8 voli1,voli2,voli3,voli4,voli5,voli6;               	 //其他电压

u16 dx,dy,dz,ax,ay,az,duty;

extern u32 latitude;        		//纬度
extern u32 longitude;       		//经度

extern u8 fq_ABC;    						//发电机交流信号频率

extern u8 TIM3_IRQ_count;

u8 fh;
extern u16 ms50cnt;

extern u16 duty1,duty2,duty3,duty4,duty5;	//duty1-4副翼、螺距、升降、油门PWM duty5 尾波PWM占空比
extern u16 fq1,fq2,fq3,fq4;				  			//fq1油箱流量计 fq2 发动机转速 fq3主轴转速 fq4尾波转速频率

extern u8 comminflag,duty_OK;
extern u8 ms200flg,ms500flg,s1flg;
extern u16 s1cnt;
extern u16 ms50cnt;
void mpu6050(void);

void USR_4G_780_200ms(void);
void USR_4G_780_1000ms(void);
void USR_4G_780_GPS(void);

void FloatToByte(float floatNum,unsigned char* byteArry);////浮点数转十六进制
u16 JS_a_b(u16 BBdata1,u16 BBdata2);

int main(void)
{		 
	u32 i=0;
	u16 temp=0; 
	s1cnt=0;
	ms50cnt=0;
	TIM3_IRQ_count=0;
	
	DBGMCU_Config(DBGMCU_TIM3_STOP,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
  SysTick_Configuration();													//嘀嗒定时器 1ms中断一次
	LED_Init();
//	TIM1_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数  
	TIM3_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 
//	TIM4_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数

	Usart1_Init(115200);
//	Usart2_Init(115200);
//	Usart3_Init(115200);
//	Usart4_Init(115200);
//	Usart5_Init(115200);
	
	Max485(); //MAX485,控制脚输出高
	
	LED0=1;
	LED1=1;
	LED2=1;
	LED3=1;					
	BELL=0;					//蜂鸣器
	
	s1cnt=0;ms200flg=0;ms500flg=0;s1flg=0;
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4); //清除中断标志位		
	for(i=0;i<16777216;i++)
	{
			__nop();
	}

	TIM_ITConfig(TIM3,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断	
	while(1)
	{		
		
		if((duty_OK&0x0f)==0x0f)
			{
				TIM_ITConfig(TIM3,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);
//				TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4); //清除中断标志位		
//				for(i=0;i<16777216;i++)
//				{
//						__nop();
//				}					
				printf("0  ");	
								
				duty2=JS_a_b(duty1,duty2);
				if((fh==1)&&(duty2!=0))
				{
					printf("-");
				}
				printf("%d  ",duty2);
				
				
				duty3=JS_a_b(duty1,duty3);
				if((fh==1)&&(duty3!=0))
				{
					printf("-");
				}
				printf("%d  ",duty3);
				
				
				duty4=JS_a_b(duty1,duty4);
				if((fh==1)&&(duty4!=0))
				{
					printf("-");
				}
				printf("%d\r\n",duty4);
				duty_OK=0;
				ms50cnt=0;
				
				LED0=~LED0;				//LED灯		
				TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4); //清除中断标志位		
				for(i=0;i<16777216;i++)
				{
						__nop();
				}				
				TIM_ITConfig(TIM3,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断	
				__nop();
			}	
			if(ms50cnt>=5)
				{
					duty_OK=0;
					ms50cnt=0;
					LED1=~LED1;
				}
		else;;
	}
}

u16 JS_a_b(u16 BBdata1,u16 BBdata2)
{
	u16 Duty11;
	fh=0;
	if(BBdata2>BBdata1)
	{
		Duty11=BBdata2-BBdata1;
	}
	else
	{
		fh=1;
		Duty11=BBdata1-BBdata2;
	}
	if(Duty11>=30000)
	{
		fh=0;
		Duty11=65536-Duty11;
	}
	else;;
	return(Duty11);

}
void mpu6050(void)														//陀螺仪三轴信号
{
//	s16 ACCx,ACCy,ACCz,GYROx,GYROy,GYROz;
//	u8 i=0;
	
	MPU6050_Dataanl();//350us	
//	printf("角速度：%.3f %.3f %.3f\r\n",sensor.gyro.averag.x,sensor.gyro.averag.y,sensor.gyro.averag.z);
//	printf("加速度：%.3f %.3f %.3f\r\n",sensor.acc.averag.x,sensor.acc.averag.y,sensor.acc.averag.z);
	DCM_CF(sensor.gyro.averag.x * AtR,sensor.gyro.averag.y * AtR,sensor.gyro.averag.z * AtR,\
	sensor.acc.averag.x,sensor.acc.averag.y,sensor.acc.averag.z,0.004);//517us
//	printf("姿态角：%.1f %.1f %.2f\r\n",IMU.Roll,IMU.Pitch,sensor.acc.averag.z*Acc_G);
	Delay_ms(4);
//	printf("\r\n");	
			
//	Data_Send_Senser(ACCx, ACCy, ACCz, GYROx, GYROy, GYROz,1,1,1);
//	Data_Send_Status(IMU.Roll,IMU.Pitch,IMU.Yaw,200,1,1);//1.359ms

//	printf("MPU6050原始数据：%d %d %d %d %d %d\r\n",ACCx, ACCy, ACCz, GYROx, GYROy, GYROz);
//	LED3=1;
}

void USR_4G_780_200ms(void)
{
	u16 CRC_buff=0;
	u8 data0[4];
	data1[0]=0xfe;
	data1[1]=56;
	data1[2]=(number_4G++);
	data1[3]=sys_ID;
	data1[4]=par_ID;
	data1[5]=0xf1;
	data1[6]=DJ_voli1;         						
	data1[7]=DJ_voli2;
	data1[8]=DJ_voli3;
	data1[9]=DJ_voli4;
	data1[10]=DJ_voli5;
			
	data1[12]=(duty1&0xff00)>>8;            
	data1[11]=(duty1&0x00ff);
	data1[14]=(duty2&0xff00)>>8;
	data1[13]=(duty2&0x00ff);
	data1[16]=(duty3&0xff00)>>8;
	data1[15]=(duty3&0x00ff);
	data1[18]=(duty4&0xff00)>>8;
	data1[17]=(duty4&0x00ff);
	data1[20]=(duty5&0xff00)>>8;
	data1[19]=(duty5&0x00ff);
			
	data1[22]=(fq1&0xff00)>>8;
	data1[21]=fq1&0x00ff;    
	data1[24]=(fq2&0xff00)>>8;
	data1[23]=fq2&0x00ff;    
	data1[26]=(fq3&0xff00)>>8;
	data1[25]=fq3&0x00ff;    
	data1[28]=(fq4&0xff00)>>8;
	data1[27]=fq4&0x00ff;  
				
  data1[30]=(high&0xff00)>>8;         //高度
	data1[29]=high&0x00ff;
	
	FloatToByte(IMU.Roll,data0);        //三轴角度 角速度IMU.Roll,IMU.Pitch,IMU.Yaw
	data1[31]=data0[0];
	data1[32]=data0[1];
	data1[33]=data0[2];
	data1[34]=data0[3];
	FloatToByte(sensor.gyro.averag.x,data0);
	data1[35]=data0[0];
	data1[36]=data0[1];
	data1[37]=data0[2];
	data1[38]=data0[3];
	FloatToByte(IMU.Pitch,data0);
	data1[39]=data0[0];
	data1[40]=data0[1];
	data1[41]=data0[2];
	data1[42]=data0[3];
	FloatToByte(sensor.gyro.averag.y,data0);
	data1[43]=data0[0];
	data1[44]=data0[1];
	data1[45]=data0[2];
	data1[46]=data0[3];
	FloatToByte((sensor.acc.averag.z*Acc_G),data0);//
	data1[47]=data0[0];
	data1[48]=data0[1];
	data1[49]=data0[2];
	data1[50]=data0[3];
	FloatToByte(sensor.gyro.averag.z,data0);
	data1[51]=data0[0];
	data1[52]=data0[1];
	data1[53]=data0[2];
	data1[54]=data0[3];
	
	data1[55]=fq_ABC;                    //三相交流电
	
	CRC_buff=Get_Crc16(&data1[0],56);
																			//等待CRC校验	
	data1[57]=(CRC_buff&0xff00)>>8;
	data1[56]=CRC_buff&0x00ff;
	MAX485_OE=1;
	Usart2_Send(data1,58);
	Delay_ms(10);
	MAX485_OE=0;	
	Usart1_Send(data1,58);
	Delay_ms(10);
}

void USR_4G_780_1000ms(void)
{
	u16 CRC_buff=0;
	data2[0]=0xfe;
	data2[1]=20;
	data2[2]=(number_4G++);
	data2[3]=sys_ID;
	data2[4]=par_ID;
	data2[5]=0xf2;
	
	data2[6]=tempreture5;         
	data2[7]=tempreture1;
	data2[8]=tempreture6;
	data2[9]=tempreture2;
	data2[10]=tempreture7+3;
	data2[11]=tempreture3;
	data2[12]=tempreture8;
	data2[13]=tempreture4;
	data2[14]=tempreture9;
	
	data2[15]=voli1;
	data2[16]=voli2;
	data2[17]=voli5;
	data2[18]=voli4;
	data2[19]=voli3;
			
	CRC_buff=Get_Crc16(&data2[0],20);//等待CRC校验	
																			
	data2[21]=(CRC_buff&0xff00)>>8;
	data2[20]=CRC_buff&0x00ff;
	MAX485_OE=1;
	Usart2_Send(data2,22);
	Delay_ms(5);
	MAX485_OE=0;	
	Usart1_Send(data2,22);
	Delay_ms(5);
	
}	
	
void USR_4G_780_GPS(void)
{
	u16 CRC_buff=0;
	data3[0]=0xfe;
	data3[1]=46;
	data3[2]=(number_4G++);
	data3[3]=sys_ID;
	data3[4]=par_ID;
	data3[5]=0xf3;
	
	CRC_buff=Get_Crc16(&data3[0],46);//等待CRC校验	
																			
	data3[47]=(CRC_buff&0xff00)>>8;
	data3[46]=CRC_buff&0x00ff;
	
	MAX485_OE=1;
	Usart2_Send(data3,48);
	Delay_ms(6);
	MAX485_OE=0;
	Usart1_Send(data3,48);
	Delay_ms(6);
		
}

void FloatToByte(float floatNum,unsigned char* byteArry)////浮点数转十六进制
{
  u8 i;  
	char* pchar=(char*)&floatNum;
	for(i=0;i<sizeof(float);i++)
	{
		*byteArry=*pchar;
		pchar++;
		byteArry++;
	}
}


