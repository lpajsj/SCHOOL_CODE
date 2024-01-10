/******************* (C) COPYRIGHT 2016 509 Team ***************************/
#ifndef _MPU6050_H
#define _MPU6050_H

#include <stm32f10x.h>
//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	   // �����ǲ����ʣ�����ֵ��0x07(125Hz)  1K/8
#define	CONFIGL			  0x1A	   // ��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	   // �������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	   // ���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define	PWR_MGMT_1		0x6B	    // ��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		  0x75	    // IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define MPU6050_ADDRESS 0xD0    // IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

#define MPU6050_DLPF_BW_256         0x00
#define MPU6050_DLPF_BW_188         0x01
#define MPU6050_DLPF_BW_98          0x02
#define MPU6050_DLPF_BW_42          0x03
#define MPU6050_DLPF_BW_20          0x04
#define MPU6050_DLPF_BW_10          0x05
#define MPU6050_DLPF_BW_5           0x06
//MPU6050�ڲ���ͨ�˲�����
//#define MPU6050_DLPF  MPU6050_DLPF_BW_256 	// 256Hz��ͨ�˲�
//#define MPU6050_DLPF  MPU6050_DLPF_BW_188 	// 188Hz��ͨ�˲�
//#define MPU6050_DLPF  MPU6050_DLPF_BW_98	  // 98Hz��ͨ�˲�      
//#define MPU6050_DLPF  MPU6050_DLPF_BW_42 		// 42Hz��ͨ�˲�
//#define MPU6050_DLPF  MPU6050_DLPF_BW_20 		// 20Hz��ͨ�˲�
//#define MPU6050_DLPF  MPU6050_DLPF_BW_10    // 10Hz��ͨ�˲� 	     
//#define MPU6050_DLPF  MPU6050_DLPF_BW_5 		// 5Hz��ͨ�˲�


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

/*       ���������ݴ���ṹ��      */
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
	struct _int16 origin;  // ԭʼֵ
	struct _float averag;  // ƽ��ֵ
	struct _float histor;  // ��ʷֵ
	struct _int16 quiet;   // ��ֵ̬
	struct _float radian;  // ����ֵ 
};

struct _sensor{   
	struct _trans acc;
	struct _trans gyro;
};
/*----------------�����ǲɼ��޷�--------------------*/
#define GYRO_GATHER   30 
/*    �˲�ϵ������  */
#define GYRO_LPF_CUT 10.0f	//�����ǵ�ͨ�˲�����ֹƵ��10Hz
#define GYRO_CF_TAU  1.2f   //�����Ǿ������� 

extern struct _sensor sensor;	// ԭʼ���ݴ����ṹ��

u8 MPU6050_Configure(u16 lpf);// MPU6050��ʼ��	
void Calibrating_Init(void);  // У׼������ʼ��
void Filter_Init(void);       // �˲�������ʼ��
void MPU_Type(float x,float y,float z);// MPU6050���μ��
void MPU6050_Read(void);      // ��ȡMPU6050ԭʼ����
void Sensor_Dir(u8 dir,float itx,float ity,float itz,float *it_x,float *it_y,float *it_z);
void MPU6050_Dataanl(void);   // MPU6050ԭʼ����Ԥ����
void Acc_Caloffest(float x,float y,float z,u16 amount); // ���ٶ�У׼����
void Gyro_Caloffest(float x,float y,float z,u16 amount);// ������У׼����
void Acc_Gyro_OFFSET(void);   // ���ٶȡ�������У׼����
extern void mpu6050(void);

#endif /* _MPU6050_H */










