/******************* (C) COPYRIGHT 2016 509 Team ***************************/
#ifndef __Algorithm_filter_H
#define	__Algorithm_filter_H

#include "stm32f10x.h" 
#include "Algorithm_math.h"
#include "math.h"//arm_math.h  F4自带数学库

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

typedef struct  // 梯度下降 滤波
{
	u8 cnt;

	s32 lst_pow_sum;
	
	s32 now_out;
	s32 lst_out;
	s32 now_velocity_xdt;
} _steepest_st;

typedef struct   // 一阶滤波
{
	float filter_cf;
	float filter_gyro;
}LPF1ndData_t;

typedef struct  // 二阶滤波
{
	float b0;
	float a1;
	float a2;
	float preout;
	float lastout;
}LPF2ndData_t;
	
/*----------------------一阶低通滤波器系数计算-------------------------*/
//deltaT:系统周期
//Fcut  :截止频率
float LPF_1st_Factor_Cal(float deltaT, float Fcut);
/*----------------------二阶低通滤波器系数计算-------------------------*/
//deltaT:系统周期
//Fcut  :截止频率
//lpf_data:计算结果参数
void LPF_2nd_Factor_Cal(float deltaT, float Fcut, LPF2ndData_t* lpf_data);
/*----------------------二阶低通滤波器------------------------*/
float LPF_2nd(LPF2ndData_t* lpf_2nd, float newData);
/*----------------------互补滤波器系数计算-------------------------*/
//deltaT:系统周期
float CF_Factor_Cal(float deltaT, float tau);


void LPF_1(float hz, //截止频率
					float time,//周期
					float in,  //输入
					float *out //输出
					);
void limit_filter(float T,float hz,_lf_t *data,float in);
void steepest_descend(s32 arr[],u8 len,_steepest_st *steepest,u8 step_num,s32 in);
void fir_arrange_filter(float *arr,u16 len,u8 *fil_cnt,float in,float *arr_out);
void Moving_Average(float moavarray[],//滤波数组 数组长度：len+1
										u16 len ,//滤波数据长度
										u16 *fil_cnt,//滤波元素号数标记（静态，用作存储）
										float in,//输入
										float *out //输出
										);
void Moving_Average1(float in,float moavarray[],u16 len ,u16 fil_cnt[2],float *out);
void LPF_1_db(float hz,float time,double in,double *out); //低通滤波，2hz代表0.5秒上升至目标值0.7倍，大约1秒上升到90%
void step_filter(float step,float in,float *out);
float my_hpf_limited(float T,float hz,float x,float zoom,float *zoom_adj);

void simple_3d_trans(float ref_x,float ref_y,float ref_z,\
										 float in_x,float in_y,float in_z,\
										 float *out_x,float *out_y,float *out_z); //小范围内正确。
											 
void vec_3d_transition(float ref_x,float ref_y,float ref_z,\
										   float in_x,float in_y,float in_z,\
											 float *out_x,float *out_y,float *out_z);




double IIR_I_Filter(double InData, double *x, double *y, double *b, short nb, double *a, short na);
float LPF_1st(float oldData, float newData, float lpf_factor);
float Moving_Median(u8 item,u8 width_num,float in);
float kalmanUpdate(const float gyro_m,const float incAngle);

#endif /* __FILTER_H */









