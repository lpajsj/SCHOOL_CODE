/******************* (C) COPYRIGHT 2016 509 Team ***************************
 * �ļ���   ��MPU6050.c
 * ����     ��MPU6050���ú���  
 * ʵ��ƽ̨ ��FK_3.0�ɿ���������@STM32F103CBT6
 * ��汾   ��ST3.5.0
 
***************************************************************************/
#include "MPU6050.h"
#include "I2C.h"
#include "delay.h"
#include "Algorithm_filter.h"
#include "MultiRotor_systime.H"
#include "led.h"
#include "usart.h"

extern u16 acc_g;
extern u16 acc_x;
extern u16 acc_y;

#define USE_HD_Filter
//#define USE_IIR_Filter
//#define USE_Steepest_Filter

u8 mpu6050_buffer[14];		// MPU6050��ȡ������������	
struct _sensor sensor;    // �ṹ�壺ԭʼֵ��ƽ��ֵ����ʷֵ����ֵ̬������ֵ      

/*====================================================================================================*/
/*====================================================================================================*
**���� : InitMPU6050
**���� : ��ʼ��MPU6050
**���� : None
**ݔ�� : None
**��ע : None
**====================================================================================================*/
/*====================================================================================================*/
u8 MPU6050_Configure(u16 lpf)
{
	u8 ack;
	u16 default_filter = 1;

	ack = Single_Read(MPU6050_ADDRESS, WHO_AM_I);// ���MPU6050���߷�
	if(ack!=0x68)
     return 1;
	
	switch(lpf)
	{
	case 5:
			default_filter = MPU6050_DLPF_BW_5;
			break;
	case 10:
			default_filter = MPU6050_DLPF_BW_10;
			break;
	case 20:
			default_filter = MPU6050_DLPF_BW_20;
			break;
	case 42:
			default_filter = MPU6050_DLPF_BW_42;
			break;
	case 98:
			default_filter = MPU6050_DLPF_BW_98;
			break;
	case 188:
			default_filter = MPU6050_DLPF_BW_188;
			break;
	case 256:
			default_filter = MPU6050_DLPF_BW_256;
			break;
	default:
			default_filter = MPU6050_DLPF_BW_42;
			break;
	}
	Single_Write(MPU6050_ADDRESS, PWR_MGMT_1, 0x80);  	             // ��������״̬
	Delay_ms(20);
	Single_Write(MPU6050_ADDRESS, PWR_MGMT_1, 0x00);  	             // �������״̬
	Delay_ms(20);
	//�Ĵ�����ַ0x19    ����Ϊ0x07    1K/8=125HZ
	Single_Write(MPU6050_ADDRESS, SMPLRT_DIV, 0x07);                 // ������ 1K/��7+1��        
	Single_Write(MPU6050_ADDRESS, CONFIGL, default_filter);          // ��ͨ�˲�  Ĭ��42Hz
	Single_Write(MPU6050_ADDRESS, GYRO_CONFIG, MPU6050_GYRO_FS_1000);// ���������� +-1000
	Single_Write(MPU6050_ADDRESS, ACCEL_CONFIG, MPU6050_ACCEL_FS_8); // ���ٶ����� +-8G
	
//	flag.MPU_Type = MPU_6050_0;   // Ĭ��6050���� У׼��������ʶ������
//	Calibrating_Init();           // У׼������ʼ��
  	Filter_Init();                // �˲�������ʼ��
//#ifdef First_Calibrating        // �ϵ���У׼
//	flag.CalibratingACC_GYRO=1;
//#else
//	flag.CalibratingACC_GYRO=0;
//#endif
	
	return 0;
}
void Calibrating_Init(void)//У׼
{
	sensor.acc.quiet.x = 0;
	sensor.acc.quiet.y = 0;
	sensor.acc.quiet.z = 4096;// �˴�4096��6050���ٶ����������й�   32768/8=4096
	
	sensor.gyro.quiet.x = 0;
	sensor.gyro.quiet.y = 0;
	sensor.gyro.quiet.z = 0;
}
LPF1ndData_t lpf1;
void Filter_Init(void)
{
	//�����˲���ϵ������
	lpf1.filter_gyro= LPF_1st_Factor_Cal(2000 * 1e-6, GYRO_LPF_CUT);//�������˲�ʹ��
	//�����˲���ϵ������
	lpf1.filter_cf =  CF_Factor_Cal(4000 * 1e-6,GYRO_CF_TAU);       //DCMʹ��
}
/*====================================================================================================*/
/*====================================================================================================*
**���� : MPU_Type
**���� : 6050����������
**���� : ���ٶ�ԭʼ����
**ݔ�� : None
**��ע : None
**====================================================================================================*/
/*====================================================================================================*/
void MPU_Type(float x,float y,float z)
{
//	float length;
//	length = my_sqrt(my_pow(x)+my_pow(y)+my_pow(z));
//	
//	if(length > 2000 && length < 6200)  // ����жϸ����������й�  �˴���4096
//	{
//		flag.MPU_Type = MPU_6050_0;
//	}
//	else
//	{
//		flag.MPU_Type = MPU_6050_1;
//	}
}
/*====================================================================================================*/
/*====================================================================================================*
**���� : MPU6050_Read
**���� : ��ȡMPU6050ԭʼ����
**���� : None
**ݔ�� : MPU6050ԭʼ����
**��ע : None
**====================================================================================================*/
/*====================================================================================================*/
void MPU6050_Read(void)
{
	// �洢˳�򣺼��ٶ�XYZ��01 23 45 TEMP��67  ������XYZ��89 10 11 12 13
	/* ����
	mpu6050_buffer[0] = Single_Read(MPU6050_ADDRESS, 0x3B);
	mpu6050_buffer[1] = Single_Read(MPU6050_ADDRESS, 0x3C);
	mpu6050_buffer[2] = Single_Read(MPU6050_ADDRESS, 0x3D);
	mpu6050_buffer[3] = Single_Read(MPU6050_ADDRESS, 0x3E);
	mpu6050_buffer[4] = Single_Read(MPU6050_ADDRESS, 0x3F);
	mpu6050_buffer[5] = Single_Read(MPU6050_ADDRESS, 0x40);
	
	mpu6050_buffer[8] = Single_Read(MPU6050_ADDRESS, 0x43);
	mpu6050_buffer[9] = Single_Read(MPU6050_ADDRESS, 0x44);
	mpu6050_buffer[10] =Single_Read(MPU6050_ADDRESS, 0x45);
	mpu6050_buffer[11] =Single_Read(MPU6050_ADDRESS, 0x46);
	mpu6050_buffer[12] =Single_Read(MPU6050_ADDRESS, 0x47);
	mpu6050_buffer[13] =Single_Read(MPU6050_ADDRESS, 0x48);
	*/
	// ����    ִ��ʱ��300us
	I2C_Read(MPU6050_ADDRESS,ACCEL_XOUT_H,14,mpu6050_buffer);//14=6+6+2
}
/*
������Ĭ�Ϸ���
     +x
     |
 +y--|--
   . |       (.��ʾ6050һ�Źܽ�)

0:Ĭ��  
1��������˳ʱ��90 ��
2��������˳ʱ��180��
3��������˳ʱ��270��
*/
void Sensor_Dir(u8 dir,float itx,float ity,float itz,float *it_x,float *it_y,float *it_z)
{
	switch(dir)
	{
		case 1: //������˳ʱ��90��
				*it_x = ity;
				*it_y = -itx;
				*it_z = itz;
		break;
		case 2://������˳ʱ��180��
				*it_x = -itx;
				*it_y = -ity;
				*it_z = itz;
		break;
		case 3://������˳ʱ��270��
				*it_x = -ity;
				*it_y = itx;
				*it_z = itz;
		break;
		default://������Ĭ�Ϸ���
			*it_x = itx;
			*it_y = ity;
			*it_z = itz;			
		break;
	}
}
/*====================================================================================================*/
/*====================================================================================================*
**���� : MPU6050_Dataanl
**���� : MPU6050����Ԥ����
**���� : None
**ݔ�� : Ԥ����������
**��ע : None
**====================================================================================================*/
/*====================================================================================================*/
#ifdef USE_Steepest_Filter                  // �ݶ��½��˲�

#define MPU_WINDOW_NUM 5
#define MPU_STEEPEST_NUM 5

#define MPU_WINDOW_NUM_ACC 25
#define MPU_STEEPEST_NUM_ACC 25

_steepest_st steepest_ax;
_steepest_st steepest_ay;
_steepest_st steepest_az;
_steepest_st steepest_gx;
_steepest_st steepest_gy;
_steepest_st steepest_gz;
s32 steepest_ax_arr[MPU_WINDOW_NUM_ACC ];
s32 steepest_ay_arr[MPU_WINDOW_NUM_ACC ];
s32 steepest_az_arr[MPU_WINDOW_NUM_ACC ];
s32 steepest_gx_arr[MPU_WINDOW_NUM ];
s32 steepest_gy_arr[MPU_WINDOW_NUM ];
s32 steepest_gz_arr[MPU_WINDOW_NUM ];

#endif

#ifdef USE_IIR_Filter              // IIR+һ�׵�ͨ�˲�

#define  IIR_ORDER     4           // ʹ��IIR�˲����Ľ���
double b_IIR[IIR_ORDER+1] ={0.0008f, 0.0032f, 0.0048f, 0.0032f, 0.0008f};  // ϵ��b
double a_IIR[IIR_ORDER+1] ={1.0000f, -3.0176f, 3.5072f, -1.8476f, 0.3708f};// ϵ��a
double InPut_IIR[3][IIR_ORDER+1] = {0};  
double OutPut_IIR[3][IIR_ORDER+1] = {0};

float Gyrolastx,Gyrolasty,Gyrolastz;
#endif

#ifdef USE_HD_Filter              // ����+һ�׵�ͨ�˲�
	
	#define FILTER_NUM_ACC 	20   
	uint8_t filter_cnt_acc=0;
	int16_t	X_BUF[FILTER_NUM_ACC],Y_BUF[FILTER_NUM_ACC],Z_BUF[FILTER_NUM_ACC];//���ٶȻ��������˲�����
	int32_t temp_accx=0,temp_accy=0,temp_accz=0;
	uint8_t i_acc;

float Gyrolastx,Gyrolasty,Gyrolastz;
#endif

//���������������ʱ�䣨�����ɼ�6050���ݣ�
//USE_Steepest_Filter     440us
//USE_IIR_Filter          395us
//USE_HD_Filter           330us  
void MPU6050_Dataanl(void)
{
	MPU6050_Read();     // ��ȡMPU6050ԭʼ���ݲ�������Ưֵ֮����Ϊԭʼ���ݲ����������
	
	if(1)//flag.MPU_Type==MPU_6050_0      ��
	{
		sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]) - acc_x;
		sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]) - acc_y;
		sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]) - acc_g + 4096;
//		printf("%d \r\n",acc_g);
	}
	else if(0)//flag.MPU_Type==MPU_6050_1    ��
	{
		sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]) - sensor.acc.quiet.x;
		sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]) - sensor.acc.quiet.y;
		sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]) - sensor.acc.quiet.z + 2048;
	}
	else
	{
		//flag.CalibratingACC_GYRO = 1;  // ����У׼  ���6050����
	}
//	printf("%d    %d \r\n",mpu6050_buffer[4],mpu6050_buffer[5]);
	sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8)| mpu6050_buffer[9])  - sensor.gyro.quiet.x;
	sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10])<< 8)| mpu6050_buffer[11]) - sensor.gyro.quiet.y;
	sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12])<< 8)| mpu6050_buffer[13]) - sensor.gyro.quiet.z;

#ifdef USE_Steepest_Filter
	
  /*�ݶ��½��������*/	
	steepest_descend(steepest_ax_arr ,MPU_WINDOW_NUM_ACC ,&steepest_ax ,MPU_STEEPEST_NUM_ACC,(s32) sensor.acc.origin.x);
	steepest_descend(steepest_ay_arr ,MPU_WINDOW_NUM_ACC ,&steepest_ay ,MPU_STEEPEST_NUM_ACC,(s32) sensor.acc.origin.y);
	steepest_descend(steepest_az_arr ,MPU_WINDOW_NUM_ACC ,&steepest_az ,MPU_STEEPEST_NUM_ACC,(s32) sensor.acc.origin.z);
	steepest_descend(steepest_gx_arr ,MPU_WINDOW_NUM ,&steepest_gx ,MPU_STEEPEST_NUM,(s32) sensor.gyro.origin.x * Gyro_G);
	steepest_descend(steepest_gy_arr ,MPU_WINDOW_NUM ,&steepest_gy ,MPU_STEEPEST_NUM,(s32) sensor.gyro.origin.y * Gyro_G);
	steepest_descend(steepest_gz_arr ,MPU_WINDOW_NUM ,&steepest_gz ,MPU_STEEPEST_NUM,(s32) sensor.gyro.origin.z * Gyro_G);	

	/*�������������*/
	Sensor_Dir( 0,													//���ٶȼƷ���
				(float)steepest_ax.now_out,
				(float)steepest_ay.now_out,
				(float)steepest_az.now_out,
				&sensor.acc.averag.x ,
				&sensor.acc.averag.y ,
				&sensor.acc.averag.z );
						
	Sensor_Dir( 0,													//�����Ƿ���
				(float)steepest_gx.now_out,
				(float)steepest_gy.now_out,
				(float)steepest_gz.now_out,
				&sensor.gyro.averag.x ,
				&sensor.gyro.averag.y ,
				&sensor.gyro.averag.z);
#endif
				
#ifdef USE_IIR_Filter
	/* ���ٶȼ�IIR�˲� */
	sensor.acc.averag.x = IIR_I_Filter(sensor.acc.origin.x, InPut_IIR[0], OutPut_IIR[0], b_IIR, IIR_ORDER+1, a_IIR, IIR_ORDER+1);
	sensor.acc.averag.y = IIR_I_Filter(sensor.acc.origin.y, InPut_IIR[1], OutPut_IIR[1], b_IIR, IIR_ORDER+1, a_IIR, IIR_ORDER+1);
	sensor.acc.averag.z = IIR_I_Filter(sensor.acc.origin.z, InPut_IIR[2], OutPut_IIR[2], b_IIR, IIR_ORDER+1, a_IIR, IIR_ORDER+1);
	
	/* ������һ�׵�ͨ�˲� */
 	sensor.gyro.averag.x = LPF_1st(Gyrolastx,sensor.gyro.origin.x * Gyro_G,lpf1.filter_gyro);	Gyrolastx = sensor.gyro.averag.x;
 	sensor.gyro.averag.y = LPF_1st(Gyrolasty,sensor.gyro.origin.y * Gyro_G,lpf1.filter_gyro);	Gyrolasty = sensor.gyro.averag.y;
 	sensor.gyro.averag.z = LPF_1st(Gyrolastz,sensor.gyro.origin.z * Gyro_G,lpf1.filter_gyro);	Gyrolastz = sensor.gyro.averag.z;
#endif
				
#ifdef USE_HD_Filter //һ�׵�ͨ�˲�
	
	X_BUF[filter_cnt_acc] = sensor.acc.origin.x;// ���»�����������
	Y_BUF[filter_cnt_acc] = sensor.acc.origin.y;
	Z_BUF[filter_cnt_acc] = sensor.acc.origin.z;
	temp_accx=temp_accy=temp_accz=0;
	for(i_acc=0;i_acc<FILTER_NUM_ACC;i_acc++)
	{
		temp_accx += X_BUF[i_acc];
		temp_accy += Y_BUF[i_acc];
		temp_accz += Z_BUF[i_acc];
	}
	sensor.acc.averag.x = temp_accx / FILTER_NUM_ACC;
	sensor.acc.averag.y = temp_accy / FILTER_NUM_ACC;
	sensor.acc.averag.z = temp_accz / FILTER_NUM_ACC;
	filter_cnt_acc++;
	if(filter_cnt_acc==FILTER_NUM_ACC)	filter_cnt_acc=0;
	
	/* ������һ�׵�ͨ�˲� */    //�ṹ�嶨λ�� LPF1ndData_t;
 	sensor.gyro.averag.x = LPF_1st(Gyrolastx,sensor.gyro.origin.x * Gyro_G,lpf1.filter_gyro);	Gyrolastx = sensor.gyro.averag.x;
 	sensor.gyro.averag.y = LPF_1st(Gyrolasty,sensor.gyro.origin.y * Gyro_G,lpf1.filter_gyro);	Gyrolasty = sensor.gyro.averag.y;
 	sensor.gyro.averag.z = LPF_1st(Gyrolastz,sensor.gyro.origin.z * Gyro_G,lpf1.filter_gyro);	Gyrolastz = sensor.gyro.averag.z;
#endif
}
/*====================================================================================================*/
/*====================================================================================================*
**���� : Acc_Calculateoffest
**���� : ������ٶ���ƫ
**���� : None
**��� : None
**ʹ�� : None
**====================================================================================================*/
/*====================================================================================================*/

void Acc_Caloffest(float x,float y,float z,u16 amount)
{
   acc_x = x/amount;
	 acc_y = y/amount;
	 acc_g = z/amount;
}
/*====================================================================================================*/
/*====================================================================================================*
**���� : Gyro_Calculateoffest
**���� : ������������ƫ
**���� : None
**��� : None
**ʹ�� : None
**====================================================================================================*/
/*====================================================================================================*/
void Gyro_Caloffest(float x,float y,float z,u16 amount)
{
   sensor.gyro.quiet.x = x/amount;
	 sensor.gyro.quiet.y = y/amount;
	 sensor.gyro.quiet.z = z/amount;
}

/*====================================================================================================*/
/*====================================================================================================*
**���� : Acc_Gyro_OFFSET
**���� : ���ٶ������Ǿ�̬�ɼ�
**���� : None
**ݔ�� : None
**��ע : None
**====================================================================================================*/
/*====================================================================================================*/
u16 acc_g = 0;
u16 acc_x = 0;
u16 acc_y = 0;
void Acc_Gyro_OFFSET(void)
{
		static u8 over_flag=0;
		u8 i,cnt_g = 0;                        // ѭ������

		int16_t gx_last=0,gy_last=0,gz_last=0; // ��ʱ�洢�������ϴ���ֵ
		int16_t Integral[3] ={0,0,0};          // �����ǻ����޷�
		int32_t tempg[6]={0,0,0,0,0,0};        // ���ٶ��������ۼӺ�
		over_flag=0;                           // У׼��־
		
		while(!over_flag)	    // �ж�У׼��־
		{
			if(cnt_g < 200)
			{
				MPU6050_Read();   // �����ɼ�200��ԭʼ���ݣ������ƽ����ֵ
				
				sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]);
				sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]);
				sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]);
				
				sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
				sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
				sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);

				tempg[0] += sensor.acc.origin.x;   // ���ٶ��ۼӺ�
				tempg[1] += sensor.acc.origin.y;
				tempg[2] += sensor.acc.origin.z;
				
				tempg[3] += sensor.gyro.origin.x;  // �������ۼӺ�
				tempg[4] += sensor.gyro.origin.y;
				tempg[5] += sensor.gyro.origin.z;

				Integral[0] += absu16(gx_last - sensor.gyro.origin.x);  // X Y Z��
				Integral[1] += absu16(gy_last - sensor.gyro.origin.y);  // �����ǻ����޷�
				Integral[2] += absu16(gz_last - sensor.gyro.origin.z);  // ̫��ָʾУ׼ʧ��

				gx_last = sensor.gyro.origin.x;  // �洢�ϴ���ֵ
				gy_last = sensor.gyro.origin.y;  // �����´μ���
				gz_last = sensor.gyro.origin.z;
			}
			else
			{
				// δУ׼�ɹ��������ǻ��ִ����������ֵ��
				if(Integral[0]>=GYRO_GATHER || Integral[1]>=GYRO_GATHER || Integral[2]>= GYRO_GATHER)
				{
					cnt_g = 0;                  // �Զ�����У׼
					for(i=0;i<3;i++)            // �����ǻ����޷�����
						Integral[i]=0;
					for(i=0;i<6;i++)            // ���ٶ��������ۼӺ�����
						tempg[i]=0;
					
					Acc_Caloffest(0,0,0,1); // ���ٶ�ƫ������д��0
					Gyro_Caloffest(0,0,0,1);// ������ƫ������д��0
				}
				else// У׼�ɹ�
				{
					Acc_Caloffest(tempg[0],tempg[1],tempg[2],200);  // ������ٶ�ƽ��ֵ
					Gyro_Caloffest(tempg[3],tempg[4],tempg[5],200); // ����������ƽ��ֵ
					over_flag = 1;                                  // У׼�ɹ���־ ��1
					//MPU_Type(sensor.acc.quiet.x,sensor.acc.quiet.y,sensor.acc.quiet.z);
				}
			}
			cnt_g++;                                            // �ɼ�������һ
		}
}

