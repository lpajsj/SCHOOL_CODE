#ifndef _Algorithm_math_H
#define	_Algorithm_math_H

#include <stm32f10x.h>
#include <math.h>

#define M_PI  (float)3.1415926535
#define squa( Sq )        (((float)Sq)*((float)Sq))
#define toRad( Math_D )	  ((float)(Math_D)*0.0174532925f)
#define toDeg( Math_R )	  ((float)(Math_R)*57.2957795f)
#define absu16( Math_X )  (Math_X<0? -(Math_X):Math_X)
#define absFloat( Math_X )(Math_X<0? -(Math_X):Math_X)

#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define my_pow(x) ((x)*(x))
#define ABS(x) ( (x)>0?(x):-(x) )
#define TAN_MAP_RES     0.003921569f     /* (smallest non-zero value in table) */
#define TAN_MAP_SIZE    256
#define ONE_PI   (3.14159265)

float my_abs(float f);
float fast_atan2(float y, float x);
float my_atan2(float x, float y);//ÐÞ¸Ä
float my_sqrt(float number);
double mx_sin(double rad);
double my_sin(double rad);
float my_cos(double rad);
float my_deadzone(float x,float ref,float zoom);
float my_deadzone_2(float x,float ref,float zoom);
float my_HLP(float T,float hz,float x,float zoom,float range,float *zoom_adj);
double To_180_degrees_db(double x);
float To_180_degrees(float x);
float my_pow_2_curve(float in,float a,float max);
float safe_div(float numerator ,float denominator);
double my_norm_2(double x,double y);
double my_norm_3(double x,double y,double z);
float second_degree(float in ,float max,float first_p);

float my_deathzoom(float x,float zoom);
float my_deathzoom_2(float x,float zoom);

float Q_rsqrt(float number);
float VariableParameter(float error);
void array_assign(u16 *array,s16 value,u16 length);
void array_astrict(s16 *array,s16 lower,s16 upper);
float data_limit(float data,float toplimit,float lowerlimit);
double Degree(double rad);
double Rad(double angle);
double constrain(double inputvalue, double limitmin, double limitmax);
void applyDeadband(double value,double deadband);
#endif /* __Algorithm_math_H */









