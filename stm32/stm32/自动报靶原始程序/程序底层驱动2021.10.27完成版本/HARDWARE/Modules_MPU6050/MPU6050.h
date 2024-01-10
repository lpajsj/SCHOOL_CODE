/******************* (C) COPYRIGHT 2016 509 Team ***************************/
#ifndef _MPU6050_H
#define _MPU6050_H

#include <stm32f10x.h>
//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	   // 陀螺仪采样率，典型值：0x07(125Hz)  1K/8
#define	CONFIGL			  0x1A	   // 低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	   // 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	   // 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	    // 电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		  0x75	    // IIC地址寄存器(默认数值0x68，只读)
#define MPU6050_ADDRESS 0xD0    // IIC写入时的地址字节数据，+1为读取

#define MPU6050_DLPF_BW_256         0x00
#define MPU6050_DLPF_BW_188         0x01
#define MPU6050_DLPF_BW_98          0x02
#define MPU6050_DLPF_BW_42          0x03
#define MPU6050_DLPF_BW_20          0x04
#define MPU6050_DLPF_BW_10          0x05
#define MPU6050_DLPF_BW_5           0x06
//MPU6050内部低通滤波设置
//#define MPU6050_DLPF  MPU6050_DLPF_BW_256 	// 256Hz低通滤波
//#define MPU6050_DLPF  MPU6050_DLPF_BW_188 	// 188Hz低通滤波
//#define MPU6050_DLPF  MPU6050_DLPF_BW_98	  // 98Hz低通滤波      
//#define MPU6050_DLPF  MPU6050_DLPF_BW_42 		// 42Hz低通滤波
//#define MPU6050_DLPF  MPU6050_DLPF_BW_20 		// 20Hz低通滤波
//#define MPU6050_DLPF  MPU6050_DLPF_BW_10    // 10Hz低通滤波 	     
//#define MPU6050_DLPF  MPU6050_DLPF_BW_5 		// 5Hz低通滤波


#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x08
#define MPU6050_GYRO_FS_1000        0x10
#define MPU6050_GYRO_FS_2000        0x18
#define MPU6050_ACCEL_FS_2          0x01
#define MPU6050_ACCEL_FS_4          0x09
#define MPU6050_ACCEL_FS_8          0x11
#define MPU6050_ACCEL_FS_16         0x19

#define RtA 		 57.32484		   // 180/PI
#define AtR    	 0.017453			 // PI/180
#define Acc_G 	 0.002392	     // 1*9.8/4096		
#define Gyro_G 	 0.0304878	   // 1/32.8
#define Gyro_Gr	 0.000542      //

enum
{
	MPU_6050_0 = 0,
	MPU_6050_1,
};

/*       传感器数据处理结构体      */
struct _float{
	float x;
	float y;
	float z;
};

struct _int16{
	int16_t x;
	int16_t y;
	int16_t z;
};		

struct _trans{
	struct _int16 origin;  // 原始值
	struct _float averag;  // 平均值
	struct _float histor;  // 历史值
	struct _int16 quiet;   // 静态值
	struct _float radian;  // 弧度值 
};

struct _sensor{   
	struct _trans acc;
	struct _trans gyro;
};
/*----------------陀螺仪采集限幅--------------------*/
#define GYRO_GATHER   30 
/*    滤波系数计算  */
#define GYRO_LPF_CUT 10.0f	//陀螺仪低通滤波器截止频率10Hz
#define GYRO_CF_TAU  1.2f   //陀螺仪纠正参数 

extern struct _sensor sensor;	// 原始数据带出结构体

u8 MPU6050_Configure(u16 lpf);// MPU6050初始化	
void Calibrating_Init(void);  // 校准参数初始化
void Filter_Init(void);       // 滤波参数初始化
void MPU_Type(float x,float y,float z);// MPU6050批次检测
void MPU6050_Read(void);      // 读取MPU6050原始数据
void Sensor_Dir(u8 dir,float itx,float ity,float itz,float *it_x,float *it_y,float *it_z);
void MPU6050_Dataanl(void);   // MPU6050原始数据预处理
void Acc_Caloffest(float x,float y,float z,u16 amount); // 加速度校准函数
void Gyro_Caloffest(float x,float y,float z,u16 amount);// 陀螺仪校准函数
void Acc_Gyro_OFFSET(void);   // 加速度、陀螺仪校准函数
extern void mpu6050(void);

#endif /* _MPU6050_H */










