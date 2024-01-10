/******************* (C) COPYRIGHT 2016 509 Team ***************************
 * 文件名   ：Algorithm_filter.c
 * 描述     ：Algorithm_filter配置   
 * 实验平台 ：STM32F407
 * 库版本   ：ST3.5.0
 * 作者     ：San_it
***************************************************************************/
#include "Algorithm_filter.h"

/*----------------------一阶低通滤波器系数计算-------------------------*/
float LPF_1st_Factor_Cal(float deltaT, float Fcut)
{
	return deltaT / (deltaT + 1 / (2 * M_PI * Fcut));//0.002/(0.002+1/(2*3.1415*10))=0.11
}
/*----------------------二阶低通滤波器系数计算-------------------------*/
void LPF_2nd_Factor_Cal(float deltaT, float Fcut, LPF2ndData_t* lpf_data)
{
	float a = 1 / (2 * M_PI * Fcut * deltaT);
	lpf_data->b0 = 1 / (a*a + 3*a + 1);
	lpf_data->a1 = (2*a*a + 3*a) / (a*a + 3*a + 1);
	lpf_data->a2 = (a*a) / (a*a + 3*a + 1);
}
/*----------------------二阶低通滤波器------------------------*/
float LPF_2nd(LPF2ndData_t* lpf_2nd, float newData)
{
	float lpf_2nd_data;
	
	lpf_2nd_data = newData * lpf_2nd->b0 + lpf_2nd->lastout * lpf_2nd->a1 - lpf_2nd->preout * lpf_2nd->a2;
	lpf_2nd->preout = lpf_2nd->lastout;
	lpf_2nd->lastout = lpf_2nd_data;
	
	return lpf_2nd_data;
}
/*----------------------互补滤波器系数计算-------------------------*/
float CF_Factor_Cal(float deltaT, float tau)
{
	return tau / (deltaT + tau);
}

void limit_filter(float T,float hz,_lf_t *data,float in)
{
	float abs_t;
	LPF_1(hz,T,	 in,&(data->lpf_1)); // 一阶低通滤波
	abs_t = ABS(data->lpf_1);        // 绝对值
	data->out = LIMIT(in,-abs_t,abs_t);// 输出限幅
}
void LPF_1(float hz,float time,float in,float *out)  
{
	*out += ( 1 / ( 1 + 1 / ( hz *6.28f *time ) ) ) *( in - *out );
}

// 梯度下降
// #define STEEPEST_ARR_NUM 10
// #define STEEPEST_STEP 10  //次
void steepest_descend(s32 arr[],u8 len,_steepest_st *steepest,u8 step_num,s32 in)
{	
	u8 updw = 1;//0 dw,1up
	s16 i;
	u8 step_cnt=0;
	u8 step_slope_factor=1;
	u8 on = 1;
	s8 pn = 1;
	//float last = 0;
	float step = 0;
	s32 start_point = 0;
	s32 pow_sum = 0;
	
	steepest->lst_out = steepest->now_out;
	if( ++(steepest->cnt) >= len )	
	{
		(steepest->cnt) = 0; //now
	}
	//last = arr[ (steepest->cnt) ];
	arr[ (steepest->cnt) ] = in;
	
	step = (float)(in - steepest->lst_out)/step_num ;//梯度
	if(ABS(step)<1)//整形数据<1的有效判定
	{
		if(ABS(step)*step_num<2)
		{
			step = 0;
		}
		else
		{
		  step = (step > 0) ? 1 : -1;
		}
	}
	start_point = steepest->lst_out;
	do
	{
		//start_point = steepest->lst_out;
		for(i=0;i<len;i++)
		{
// 			j = steepest->cnt + i + 1;
// 			if( j >= len )	
// 			{
// 				j = j - len; //顺序排列
// 			}
			pow_sum += my_pow(arr[i] - start_point );// /step_num;//除法减小比例**
			//start_point += pn *(step_slope_factor *step/len);
		}	
		if(pow_sum - steepest->lst_pow_sum > 0)
		{		
			if(updw==0)
			{
				on = 0;
			}
			updw = 1;//上升了
			pn = (pn == 1 )? -1:1;
		}
		else
		{
			updw = 0; //正在下降
 			if(step_slope_factor<step_num)
 			{
 				step_slope_factor++;
 			}
		}
		steepest->lst_pow_sum = pow_sum;		
		pow_sum = 0;
		start_point += pn *step;//调整
		
		if(++step_cnt > step_num)//限制计算次数
		{
			on = 0;
		}
			//////
			if(step_slope_factor>=2)//限制下降次数1次，节省时间，但会增大滞后，若cpu时间充裕可不用。
			{
				on = 0;

			}
			//////
	}
	while(on==1);
	steepest->now_out = start_point ;//0.5f *(start_point + steepest->lst_out);//
	steepest->now_velocity_xdt = steepest->now_out - steepest->lst_out;
}
// FIR 滤波     arr：入口    arr_out:出口
void fir_arrange_filter(float *arr,u16 len,u8 *fil_cnt,float in,float *arr_out) //len<=255 len >= 3
{
	//float arrange[len];
	float tmp;
	u8 i,j;
/*
窗口数据处理
*/		
	if( ++*fil_cnt >= len )	
	{
		*fil_cnt = 0; //now
	}
	
	arr[ *fil_cnt ] = in;
/*
窗口数据处理
*/	
	
/*
赋值、排列
*/	
	for(i=0;i<len;i++)
	{
		arr_out[i] = arr[i];
	}
	
	for(i=0;i<len-1;i++)
	{
		for(j=0;j<len-1-i;j++)
		{
			if(arr_out[j]>arr_out[j+1])
			{
				tmp = arr_out[j+1];
				arr_out[j+1] = arr_out[j];
				arr_out[j] = tmp;
			}
		}
	}
/*
赋值、排列
*/		
}

// #define WIDTH_NUM 101
// #define FIL_ITEM  10
void Moving_Average(float moavarray[],u16 len ,u16 *fil_cnt,float in,float *out)
{
	u16 width_num;
	float last;

	width_num = len ;
	
	if( ++*fil_cnt >= width_num )	
	{
		*fil_cnt = 0; //now
	}
	
	last = moavarray[ *fil_cnt ];
	
	moavarray[ *fil_cnt ] = in;
	
	*out += (in - (last))/(float)( width_num ) ;
	//*out += 0.00001f *(in - *out);
	*out += 0.00001f *LIMIT((in - *out),-1,1);  //数据精度误差修正
}

void Moving_Average1(float in,float moavarray[],u16 len ,u16 fil_cnt[2],float *out)
{
	u16 width_num;
	
	width_num = len ;
	
	if( ++fil_cnt[0] > width_num )	
	{
		fil_cnt[0] = 0; //now
		fil_cnt[1] = 1; //old
	}
	else
	{
		fil_cnt[1] = (fil_cnt[0] == width_num)? 0 : (fil_cnt[0] + 1);
	}
	
	moavarray[ fil_cnt[0] ] = in;
	*out += ( in - ( moavarray[ fil_cnt[1] ]  ) )/(float)( width_num ) ;
	
}
// double型数据 一阶低通滤波
// 低通滤波，2hz代表0.5秒上升至目标值0.7倍，大约1秒上升到90%
void LPF_1_db(float hz,float time,double in,double *out)
{
	*out += ( 1 / ( 1 + 1 / ( hz *6.28f *time ) ) ) *( in - *out );
}

void step_filter(float step,float in,float *out) 
{
	if(in - *out > step)
	{
		*out += step;
	}
	else if(in - *out < -step)
	{
		*out -= step;
	}
	else
	{
		*out = in;
	}
}

float my_hpf_limited(float T,float hz,float x,float zoom,float *zoom_adj)
{
	*zoom_adj += ( 1 / ( 1 + 1 / ( hz *6.28f *T ) ) ) *(x - *zoom_adj);
	*zoom_adj = LIMIT(*zoom_adj,-zoom,zoom);
	return (x - *zoom_adj);
}

void simple_3d_trans(float ref_x,float ref_y,float ref_z,\
										 float in_x,float in_y,float in_z,\
										 float *out_x,float *out_y,float *out_z) //小范围内正确。
{
	static s8 pn;
	static float h_tmp_x,h_tmp_y;
	
#ifdef ARM_MATH_CM4
	arm_sqrt_f32((my_pow(ref_z) + my_pow(ref_y)),&h_tmp_x);
	arm_sqrt_f32((my_pow(ref_z) + my_pow(ref_x)),&h_tmp_y);
#else
	h_tmp_x = my_sqrt(my_pow(ref_z) + my_pow(ref_y));
	h_tmp_y = my_sqrt(my_pow(ref_z) + my_pow(ref_x));
#endif
	
	pn = ref_z < 0? -1 : 1;
	
	*out_x = ( h_tmp_x * in_x - pn * ref_x * in_z );
	*out_y = ( h_tmp_y * in_y * pn - ref_y * in_z );
	
// 	 out->x = h_tmp_x *in->x - ref->x *in->z;
// 	 out->y = ref->z *in->y - ref->y *in->z;
	
	*out_z = ref_x * in_x + ref_y * in_y + ref_z * in_z;

}

void vec_3d_transition(float ref_x,float ref_y,float ref_z,\
										   float in_x,float in_y,float in_z,\
											 float *out_x,float *out_y,float *out_z)
{
	float vec_3d_ref_z_x,vec_3d_ref_z_y,vec_3d_ref_z_z;
	float vec_3d_ref_x_x,vec_3d_ref_x_y,vec_3d_ref_x_z;
	float vec_3d_ref_y_x,vec_3d_ref_y_y,vec_3d_ref_y_z;
	
	vec_3d_ref_z_x = ref_x;
	vec_3d_ref_z_y = ref_y;
	vec_3d_ref_z_z = ref_z;
	
#ifdef ARM_MATH_CM4
	arm_sqrt_f32((my_pow(vec_3d_ref_z_z) + my_pow(vec_3d_ref_z_y)),&vec_3d_ref_x_x);
#else
	vec_3d_ref_x_x =  my_sqrt(my_pow(vec_3d_ref_z_z) + my_pow(vec_3d_ref_z_y));
#endif
	
	vec_3d_ref_x_y = -vec_3d_ref_z_x *vec_3d_ref_z_y/vec_3d_ref_x_x;
	vec_3d_ref_x_z = -vec_3d_ref_z_x *vec_3d_ref_z_z/vec_3d_ref_x_x;
	
	vec_3d_ref_y_x = 0;
	vec_3d_ref_y_y =  vec_3d_ref_z_z/vec_3d_ref_x_x;
	vec_3d_ref_y_z = -vec_3d_ref_z_y/vec_3d_ref_x_x;
	
	*out_x = in_x *vec_3d_ref_x_x + in_y *vec_3d_ref_x_y + in_z *vec_3d_ref_x_z;
	*out_y = in_x *vec_3d_ref_y_x + in_y *vec_3d_ref_y_y + in_z *vec_3d_ref_y_z;
	*out_z = in_x *vec_3d_ref_z_x + in_y *vec_3d_ref_z_y + in_z *vec_3d_ref_z_z;
}

/*====================================================================================================*/
/*====================================================================================================*
** 函数名称: IIR_I_Filter
** 功能描述: IIR直接I型滤波器
** 输    入: InData 为当前数据
**           *x     储存未滤波的数据
**           *y     储存滤波后的数据
**           *b     储存系数b
**           *a     储存系数a
**           nb     数组*b的长度
**           na     数组*a的长度
**           LpfFactor
** 输    出: OutData         
** 说    明: 无
** 函数原型: y(n) = b0*x(n) + b1*x(n-1) + b2*x(n-2) -
                    a1*y(n-1) - a2*y(n-2)
**====================================================================================================*/
/*====================================================================================================*/
double IIR_I_Filter(double InData, double *x, double *y, double *b, short nb, double *a, short na)
{
  double z1,z2;
  short i;
  double OutData;
  
  for(i=nb-1; i>0; i--)
  {
    x[i]=x[i-1];
  }
  
  x[0] = InData;
  
  for(z1=0,i=0; i<nb; i++)
  {
    z1 += x[i]*b[i];
  }
  
  for(i=na-1; i>0; i--)
  {
    y[i]=y[i-1];
  }
  
  for(z2=0,i=1; i<na; i++)
  {
    z2 += y[i]*a[i];
  }
  
  y[0] = z1 - z2; 
  OutData = y[0];
    
  return OutData;
}
/*====================================================================================================*/
/*====================================================================================================*
** 函数名称: IIR_I_Filter
** 功能描述: IIR直接II型滤波器
** 输    入: InData 为当前数据
**           *x     储存未滤波的数据
**           *y     储存滤波后的数据
**           *b     储存系数b
**           *a     储存系数a
**           nb     数组*b的长度
**           na     数组*a的长度
**           LpfFactor
** 输    出: OutData         
** 说    明: 无
** 函数原型: y(n) = b0*x(n) + b1*x(n-1) + b2*x(n-2) -
                    a1*y(n-1) - a2*y(n-2)
**====================================================================================================*/
/*====================================================================================================*/
//相当于两个直接I型滤波器的串联






/*====================================================================================================*/
/*====================================================================================================*
**函数 : LPF_1st
**功能 : 一阶低通滤波
**输入 :  
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
float LPF_1st(float oldData, float newData, float lpf_factor)
{
	return oldData * (1 - lpf_factor) + newData * lpf_factor;
}
/*====================================================================================================*/
/*====================================================================================================*
**函数 : KalmanFilter
**功能 : 卡尔曼滤波
**输入 :  
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
double KalmanFilter(const double ResrcData,double ProcessNiose_Q,double MeasureNoise_R)
{
   double R = MeasureNoise_R;
   double Q = ProcessNiose_Q;
   static double x_mid ;//= x_last
   static double x_now;
   static double p_mid ;
   static double p_now;
   static double kg;        
   static double x_last,p_last;//原来是在形式参数里的
   x_mid=x_last;          //x_last=x(k-1|k-1),x_mid=x(k|k-1)
   p_mid=p_last+Q;        //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
   kg=p_mid/(p_mid+R);    //kg为kalman filter，R为噪声
   x_now=x_mid+kg*(ResrcData-x_mid);//估计出的最优值
                
   p_now=(1-kg)*p_mid;   //最优值对应的covariance       
   p_last = p_now;       //更新covariance值
   x_last = x_now;       //更新系统状态值
   return x_now;                
}



#define MED_WIDTH_NUM 11
#define MED_FIL_ITEM  4

float med_filter_tmp[MED_FIL_ITEM][MED_WIDTH_NUM ];
float med_filter_out[MED_FIL_ITEM];

u8 med_fil_cnt[MED_FIL_ITEM];

float Moving_Median(u8 item,u8 width_num,float in)
{
	u8 i,j;
	float t;
	float tmp[MED_WIDTH_NUM];
	
	if(item >= MED_FIL_ITEM || width_num >= MED_WIDTH_NUM )
	{
		return 0;
	}
	else
	{
		if( ++med_fil_cnt[item] >= width_num )	
		{
			med_fil_cnt[item] = 0;
		}
		
		med_filter_tmp[item][ med_fil_cnt[item] ] = in;
		
		for(i=0;i<width_num;i++)
		{
			tmp[i] = med_filter_tmp[item][i];
		}
		
		for(i=0;i<width_num-1;i++)
		{
			for(j=0;j<(width_num-1-i);j++)
			{
				if(tmp[j] > tmp[j+1])
				{
					t = tmp[j];
					tmp[j] = tmp[j+1];
					tmp[j+1] = t;
				}
			}
		}		
		return ( tmp[(u16)width_num/2] );
	}
}

//float gyro_m：陀螺仪测得的量（角速度）  
//float incAngle:加计测得的角度值  
#define dt                  0.0025f //卡尔曼滤波采样频率   
#define R_angle             0.69f   //测量噪声的协方差（即是测量偏差） 
#define Q_angle             0.005f  //过程噪声的协方差   
#define Q_gyro              0.001f  //过程噪声的协方差  过程噪声协方差为一个一行两列矩阵 
float kalmanUpdate(const float gyro_m,const float incAngle)    
{  
	  float K_0;//含有卡尔曼增益的另外一个函数，用于计算最优估计值         
		float K_1;//含有卡尔曼增益的函数，用于计算最优估计值的偏差         
		float Y_0;         
		float Y_1;            
		float Rate;//去除偏差后的角速度           
		float Pdot[4];//过程协方差矩阵的微分矩阵          
		float angle_err;//角度偏量         
		float E;//计算的过程量          
		static float angle = 0;            //下时刻最优估计值角度          
		static float q_bias = 0;        //陀螺仪的偏差                          
		static float P[2][2] = {{ 1, 0 }, { 0, 1 }};//过程协方差矩阵         
		Rate = gyro_m - q_bias;          //计算过程协方差矩阵的微分矩阵               
		Pdot[0] = Q_angle - P[0][1] - P[1][0];//？？？？？？                  
		Pdot[1] = - P[1][1];                                   
		Pdot[2] = - P[1][1];                                           
		Pdot[3] = Q_gyro;//？？？？？？                                  
		angle += Rate * dt; //角速度积分得出角度         
		P[0][0] += Pdot[0] * dt; //计算协方差矩阵         
		P[0][1] += Pdot[1] * dt;          
		P[1][0] += Pdot[2] * dt;          
		P[1][1] += Pdot[3] * dt;            
		angle_err = incAngle - angle; //计算角度偏差          
		E = R_angle + P[0][0];          
		K_0 = P[0][0] / E; //计算卡尔曼增益         
		K_1 = P[1][0] / E;           
		Y_0 = P[0][0];            
		Y_1 = P[0][1];             
		P[0][0] -= K_0 * Y_0; //跟新协方差矩阵         
		P[0][1] -= K_0 * Y_1;          
		P[1][0] -= K_1 * Y_0;           
		P[1][1] -= K_1 * Y_1;          
		angle += K_0 * angle_err; //给出最优估计值         
		q_bias += K_1 * angle_err;//跟新最优估计值偏差          
		return angle;
}









