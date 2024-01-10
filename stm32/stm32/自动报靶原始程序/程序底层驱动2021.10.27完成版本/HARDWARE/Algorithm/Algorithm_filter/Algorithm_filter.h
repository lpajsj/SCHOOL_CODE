/******************* (C) COPYRIGHT 2016 509 Team ***************************/
#ifndef __Algorithm_filter_H
#define	__Algorithm_filter_H

#include "stm32f10x.h" 
#include "Algorithm_math.h"
#include "math.h"//arm_math.h  F4�Դ���ѧ��

//typedef struct
//{
//	float integration_1;
//	float integration_2;
//	float out_tmp;
//	float out;

//}_com_fil_t;

typedef struct
{
	float lpf_1;
	float out;
}_lf_t;

//typedef struct
//{
//	float lpf_1;
//	float lpf_2;
//	float in_old;
//	float out;
//}_jldf_t;

typedef struct  // �ݶ��½� �˲�
{
	u8 cnt;

	s32 lst_pow_sum;
	
	s32 now_out;
	s32 lst_out;
	s32 now_velocity_xdt;
} _steepest_st;

typedef struct   // һ���˲�
{
	float filter_cf;
	float filter_gyro;
}LPF1ndData_t;

typedef struct  // �����˲�
{
	float b0;
	float a1;
	float a2;
	float preout;
	float lastout;
}LPF2ndData_t;
	
/*----------------------һ�׵�ͨ�˲���ϵ������-------------------------*/
//deltaT:ϵͳ����
//Fcut  :��ֹƵ��
float LPF_1st_Factor_Cal(float deltaT, float Fcut);
/*----------------------���׵�ͨ�˲���ϵ������-------------------------*/
//deltaT:ϵͳ����
//Fcut  :��ֹƵ��
//lpf_data:����������
void LPF_2nd_Factor_Cal(float deltaT, float Fcut, LPF2ndData_t* lpf_data);
/*----------------------���׵�ͨ�˲���------------------------*/
float LPF_2nd(LPF2ndData_t* lpf_2nd, float newData);
/*----------------------�����˲���ϵ������-------------------------*/
//deltaT:ϵͳ����
float CF_Factor_Cal(float deltaT, float tau);


void LPF_1(float hz, //��ֹƵ��
					float time,//����
					float in,  //����
					float *out //���
					);
void limit_filter(float T,float hz,_lf_t *data,float in);
void steepest_descend(s32 arr[],u8 len,_steepest_st *steepest,u8 step_num,s32 in);
void fir_arrange_filter(float *arr,u16 len,u8 *fil_cnt,float in,float *arr_out);
void Moving_Average(float moavarray[],//�˲����� ���鳤�ȣ�len+1
										u16 len ,//�˲����ݳ���
										u16 *fil_cnt,//�˲�Ԫ�غ�����ǣ���̬�������洢��
										float in,//����
										float *out //���
										);
void Moving_Average1(float in,float moavarray[],u16 len ,u16 fil_cnt[2],float *out);
void LPF_1_db(float hz,float time,double in,double *out); //��ͨ�˲���2hz����0.5��������Ŀ��ֵ0.7������Լ1��������90%
void step_filter(float step,float in,float *out);
float my_hpf_limited(float T,float hz,float x,float zoom,float *zoom_adj);

void simple_3d_trans(float ref_x,float ref_y,float ref_z,\
										 float in_x,float in_y,float in_z,\
										 float *out_x,float *out_y,float *out_z); //С��Χ����ȷ��
											 
void vec_3d_transition(float ref_x,float ref_y,float ref_z,\
										   float in_x,float in_y,float in_z,\
											 float *out_x,float *out_y,float *out_z);




double IIR_I_Filter(double InData, double *x, double *y, double *b, short nb, double *a, short na);
float LPF_1st(float oldData, float newData, float lpf_factor);
float Moving_Median(u8 item,u8 width_num,float in);
float kalmanUpdate(const float gyro_m,const float incAngle);

#endif /* __FILTER_H */









