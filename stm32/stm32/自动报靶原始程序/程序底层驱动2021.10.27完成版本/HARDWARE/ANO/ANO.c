#include "ano.h"
#include "usart.h"


/************************************************
//文件名: 串口发送给匿名上位机信息
//描述： PA9 PA10
//创建人：
//时间：2016-12-9
//修改次数：第一次
************************************************/

//串口1发送1个字符 
//c:要发送的字符
void usart1_send_char(u8 c)
{   	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
	USART_SendData(USART1,c);  
}

//版本信息
void  Data_Send_Ver(u8 HardwareType,float HardwareVER,float SoftwareVER,float ProtocolVER,float BootlocaderVER)
{
		u8 SUM=0;
		u16 HVER,SVER,PVER,BootVER;
		HardwareVER*=100;//硬件版本
		SoftwareVER*=100;//软件版本
		ProtocolVER*=100;//协议标准
		BootlocaderVER*=100;
	  HVER=(u16)HardwareVER;
	  SVER=(u16)SoftwareVER;
	  PVER=(u16)ProtocolVER;
	  BootVER=(u16)BootlocaderVER;
	  
		usart1_send_char(0xAA);
		usart1_send_char(0xAA);
		usart1_send_char(0x00);
		usart1_send_char(9);//1001
	  
		usart1_send_char(HardwareType);
//		usart1_send_char(PART1(HVER));
//		usart1_send_char(PART0(HVER));
	  usart1_send_char((u8)(HVER>>8));
		usart1_send_char((u8)HVER);
		usart1_send_char(PART1(SVER));
		usart1_send_char(PART0(SVER));
		usart1_send_char(PART1(PVER));
		usart1_send_char(PART0(PVER));
		usart1_send_char(PART1(BootVER));
		usart1_send_char(PART0(BootVER));
		
		SUM+=0XAA;SUM+=0xAA;SUM+=0x00;SUM+=9;
		SUM+=HardwareType;
		SUM+=HVER>>8;SUM+=HVER;
		SUM+=SVER>>8;SUM+=SVER;
		SUM+=PVER>>8;SUM+=PVER;
	  SUM+=BootVER>>8;SUM+=BootVER;
		usart1_send_char(SUM);	
}
//状态 飞机姿态
void  Data_Send_Status(float ROL,float PIT,float YAW,s32 ALT_USE,u8 FLY_MODEL,u8 ARMED)
{
			//int 类型默认为有符号的，所以为 s16.
	    u8 SUM=0;
			s16 roll,pitch,yaw;//翻滚角、俯仰角、偏航角
			ROL*=100;
			PIT*=100;
			YAW*=100;
			roll=(s16)ROL;
			pitch=(s16)PIT;
			yaw=(s16)YAW;

			usart1_send_char(0xAA);
			usart1_send_char(0xAA);
			usart1_send_char(0x01);
			usart1_send_char(12);//len

			usart1_send_char(PART1(roll));
			usart1_send_char(PART0(roll));
			usart1_send_char(PART1(pitch));
			usart1_send_char(PART0(pitch));
			usart1_send_char(PART1(yaw));
			usart1_send_char(PART0(yaw));

			usart1_send_char(PART3(ALT_USE));
			usart1_send_char(PART2(ALT_USE));
			usart1_send_char(PART1(ALT_USE));
			usart1_send_char(PART0(ALT_USE));

			usart1_send_char(FLY_MODEL);
			usart1_send_char(ARMED);
			
			SUM+=0XAA;SUM+=0xAA;SUM+=0x00;SUM+=12;
			SUM+=roll>>8;SUM+=roll;
			SUM+=pitch>>8;SUM+=pitch;
			SUM+=yaw>>8;SUM+=yaw;
			SUM+=ALT_USE>>24;SUM+=ALT_USE>>16;SUM+=ALT_USE>>8;SUM+=ALT_USE;
	    SUM+=FLY_MODEL;
	    SUM+=ARMED;
			usart1_send_char(SUM);
}
//传感器数据  ACC 加速度计 GYRO 陀螺仪 MAG 电磁传感器 BARO 气压传感器
void  Data_Send_Senser(s16 ACC_X,s16 ACC_Y,s16 ACC_Z,s16 GYRO_X,s16 GYRO_Y,s16 GYRO_Z,s16 MAG_X,s16 MAG_Y,s16 MAG_Z)
{
			u8 SUM=0;

			usart1_send_char(0xAA);
			usart1_send_char(0xAA);
			usart1_send_char(0x02);
			usart1_send_char(18);//len
	 
	    usart1_send_char(PART1(ACC_X));
			usart1_send_char(PART0(ACC_X));
			usart1_send_char(PART1(ACC_Y));
			usart1_send_char(PART0(ACC_Y));
			usart1_send_char(PART1(ACC_Z));
			usart1_send_char(PART0(ACC_Z));
	
	    usart1_send_char(PART1(GYRO_X));
			usart1_send_char(PART0(GYRO_X));
			usart1_send_char(PART1(GYRO_Y));
			usart1_send_char(PART0(GYRO_Y));
			usart1_send_char(PART1(GYRO_Z));
			usart1_send_char(PART0(GYRO_Z));
	
	    usart1_send_char(PART1(MAG_X));
			usart1_send_char(PART0(MAG_X));
			usart1_send_char(PART1(MAG_Y));
			usart1_send_char(PART0(MAG_Y));
			usart1_send_char(PART1(MAG_Z));
			usart1_send_char(PART0(MAG_Z));
			
			SUM+=0XAA;SUM+=0xAA;SUM+=0x02;SUM+=18;
			SUM+=ACC_X>>8;SUM+=ACC_X;
			SUM+=ACC_Y>>8;SUM+=ACC_Y;
	    SUM+=ACC_Z>>8;SUM+=ACC_Z;
			
			SUM+=GYRO_X>>8;SUM+=GYRO_X;
			SUM+=GYRO_Y>>8;SUM+=GYRO_Y;
	    SUM+=GYRO_Z>>8;SUM+=GYRO_Z;
			
			SUM+=MAG_X>>8;SUM+=MAG_X;
			SUM+=MAG_Y>>8;SUM+=MAG_Y;
	    SUM+=MAG_Z>>8;SUM+=MAG_Z;
			usart1_send_char(SUM);
			 
}
//飞机收到的控制数据
//THR 推力   AUX 额外传感器控制数据
void  Data_Send_RCDATA(s16 THR,s16 YAW,s16 ROL,s16 PIT,s16 AUX1,s16 AUX2,s16 AUX3,s16 AUX4,s16 AUX5,s16 AUX6)
{
	    u8 SUM=0;
	    usart1_send_char(0xAA);
			usart1_send_char(0xAA);
			usart1_send_char(0x03);
			usart1_send_char(20);//len
	    
	    usart1_send_char(PART1(THR));
			usart1_send_char(PART0(THR));
			usart1_send_char(PART1(YAW));
			usart1_send_char(PART0(YAW));
			usart1_send_char(PART1(ROL));
			usart1_send_char(PART0(ROL));
	
	    usart1_send_char(PART1(PIT));
			usart1_send_char(PART0(PIT));
			usart1_send_char(PART1(AUX1));
			usart1_send_char(PART0(AUX1));
			usart1_send_char(PART1(AUX2));
			usart1_send_char(PART0(AUX2));
	
	    usart1_send_char(PART1(AUX3));
			usart1_send_char(PART0(AUX3));
			usart1_send_char(PART1(AUX4));
			usart1_send_char(PART0(AUX4));
			usart1_send_char(PART1(AUX5));
			usart1_send_char(PART0(AUX5));
			usart1_send_char(PART1(AUX6));
			usart1_send_char(PART0(AUX6));
	
	    SUM+=0XAA;SUM+=0xAA;SUM+=0x03;SUM+=20;
			SUM+=THR>>8;SUM+=THR;
			SUM+=YAW>>8;SUM+=YAW;
	    SUM+=ROL>>8;SUM+=ROL;
			
			SUM+=PIT>>8;SUM+=PIT;
			SUM+=AUX1>>8;SUM+=AUX1;
	    SUM+=AUX2>>8;SUM+=AUX2;
			
			SUM+=AUX3>>8;SUM+=AUX3;
			SUM+=AUX4>>8;SUM+=AUX4;
	    SUM+=AUX5>>8;SUM+=AUX5;
			SUM+=AUX6>>8;SUM+=AUX6;
			usart1_send_char(SUM);
}
//机载GPS信息
//定位状态、卫星数量、经度、纬度、回航角
//unsigned  signed    float 4个字节
//回航角需要*100，*10得不到正确的数据，我认为是协议误写
void  Data_Send_GPSDATA(u8 GPSlocation,u8 GPSNum,float LNG,float LAT,float Rangle)
{
			u8  SUM=0;
			s32  lng,lat;
			s16  rangle;
			LNG*=10000000;
			LAT*=10000000;
			Rangle*=100;//Rangle int16
	
	    lng=(s32)LNG;
	    lat=(s32)LAT;
	    rangle=(s16)Rangle;
	    
	    usart1_send_char(0xAA);
			usart1_send_char(0xAA);
			usart1_send_char(0x04);
			usart1_send_char(12);//len
	
	    usart1_send_char(GPSlocation);
			usart1_send_char(GPSNum);
	
			usart1_send_char(PART3(lng));
			usart1_send_char(PART2(lng));
			usart1_send_char(PART1(lng));
			usart1_send_char(PART0(lng));
			
			usart1_send_char(PART3(lat));
			usart1_send_char(PART2(lat));
			usart1_send_char(PART1(lat));
			usart1_send_char(PART0(lat));
			
	    usart1_send_char(PART1(rangle));
			usart1_send_char(PART0(rangle));
			
			SUM+=0XAA;SUM+=0xAA;SUM+=0x04;SUM+=12;
			
			SUM+=GPSlocation;SUM+=GPSNum;
			SUM+=lng>>24;SUM+=lng>>16;SUM+=lng>>8;SUM+=lng;
	    SUM+=lat>>24;SUM+=lat>>16;SUM+=lat>>8;SUM+=lat;
			SUM+=rangle>>8;SUM+=rangle;
			usart1_send_char(SUM);
			
}
//电源状态   voltage电压  current 电流
void  Data_Send_Power(float Votage,float Current)
{
			u8 SUM=0;
			u16 VOGE,CURT;

			Votage*=100;
			Current*=100;
			VOGE=(u16)Votage;
			CURT=(u16)Current;
	
	    usart1_send_char(0xAA);
			usart1_send_char(0xAA);
			usart1_send_char(0x05);
			usart1_send_char(4);//len    
	
	    usart1_send_char(PART1(VOGE));
			usart1_send_char(PART0(VOGE));
			usart1_send_char(PART1(CURT));
			usart1_send_char(PART0(CURT));
	
	    SUM+=0XAA;SUM+=0xAA;SUM+=0x05;SUM+=4;
	    SUM+=VOGE>>8;SUM+=VOGE;
	    SUM+=CURT>>8;SUM+=CURT;
			usart1_send_char(SUM);
	 
}
//马达PWM 0-1000
void  Data_Send_MOTO(u16 PWM_MOTO1,u16 PWM_MOTO2,u16 PWM_MOTO3,u16 PWM_MOTO4,u16 PWM_MOTO5,u16 PWM_MOTO6,u16 PWM_MOTO7,u16 PWM_MOTO8)
{
			u8 SUM=0;
	
			usart1_send_char(0xAA);
			usart1_send_char(0xAA);
			usart1_send_char(0x06);
			usart1_send_char(16);//len  
	    
	    usart1_send_char(PART1(PWM_MOTO1));
			usart1_send_char(PART0(PWM_MOTO1));
			usart1_send_char(PART1(PWM_MOTO2));
			usart1_send_char(PART0(PWM_MOTO2));
	
	    usart1_send_char(PART1(PWM_MOTO3));
			usart1_send_char(PART0(PWM_MOTO3));
			usart1_send_char(PART1(PWM_MOTO4));
			usart1_send_char(PART0(PWM_MOTO4));
	
	    usart1_send_char(PART1(PWM_MOTO5));
			usart1_send_char(PART0(PWM_MOTO5));
			usart1_send_char(PART1(PWM_MOTO6));
			usart1_send_char(PART0(PWM_MOTO6));
			
			usart1_send_char(PART1(PWM_MOTO7));
			usart1_send_char(PART0(PWM_MOTO7));
			usart1_send_char(PART1(PWM_MOTO8));
			usart1_send_char(PART0(PWM_MOTO8));
			
			
	    SUM+=0XAA;SUM+=0xAA;SUM+=0x06;SUM+=16;
	    SUM+=PWM_MOTO1>>8;SUM+=PWM_MOTO1;
	    SUM+=PWM_MOTO2>>8;SUM+=PWM_MOTO2;
			SUM+=PWM_MOTO3>>8;SUM+=PWM_MOTO3;
	    SUM+=PWM_MOTO4>>8;SUM+=PWM_MOTO4;
			SUM+=PWM_MOTO5>>8;SUM+=PWM_MOTO5;
	    SUM+=PWM_MOTO6>>8;SUM+=PWM_MOTO6;
			SUM+=PWM_MOTO7>>8;SUM+=PWM_MOTO7;
	    SUM+=PWM_MOTO8>>8;SUM+=PWM_MOTO8;
			usart1_send_char(SUM);
	 
}
