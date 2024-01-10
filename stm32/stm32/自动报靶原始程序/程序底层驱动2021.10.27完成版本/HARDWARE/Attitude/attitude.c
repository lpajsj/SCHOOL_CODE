#include "attitude.h"

EulerAngle IMU={0};

#ifdef USE_DCM

float ix,iy,iz,\
			jx,jy,jz,\
			kx,ky,kz;
int32_t accRatio;
extern LPF1ndData_t lpf1;     // 滤波参数带出
void DCM_CF(float gx,float gy,float gz,float ax,float ay,float az,float dt) // 180us
{
	static float deltaGyroAnglex,deltaGyroAngley,deltaGyroAnglez;
	static float LastGyrox,LastGyroy,LastGyroz;
	static float Vector_Gx=0,Vector_Gy=0,Vector_Gz=4096;// 此处4096跟加速度量程一致
	static float Vector_Mx=1000,Vector_My=0,Vector_Mz=0;
	float sinx,cosx,siny,cosy,sinz,cosz;
	
	gx=-gx;gy=-gy;gz=-gz;
	accRatio =(squa(ax)+ squa(ay) +squa(az))*100/(4096*4096);// 此处4096跟加速度量程一致
	
	deltaGyroAnglex = (gx+LastGyrox)*0.5*dt;
	deltaGyroAngley = (gy+LastGyroy)*0.5*dt;
	deltaGyroAnglez = (gz+LastGyroz)*0.5*dt;
	
	LastGyrox = gx;
	LastGyroy = gy;
	LastGyroz = gz;
	
	sinx = sinf(deltaGyroAnglex);
	cosx = cosf(deltaGyroAnglex);
	siny = sinf(deltaGyroAngley);
	cosy = cosf(deltaGyroAngley);
	sinz = sinf(deltaGyroAnglez);
	cosz = cosf(deltaGyroAnglez);
	
	ix = cosy * cosz;
	iy = (sinx * siny * cosz) + (cosx * sinz);
	iz = -(cosx * siny * cosz) + (sinx * sinz);
	
	jx = -cosy * sinz;
	jy = -(sinx * siny * sinz) + (cosx * cosz);
	jz = (cosx * siny * sinz) + (sinx * cosz);
	
	kx = siny;
	ky =  -sinx * cosy;	
	kz = cosx * cosy;
	
	Vector_Gx = Vector_Gx * ix + Vector_Gy * jx + Vector_Gz * kx;
	Vector_Gy = Vector_Gx * iy + Vector_Gy * jy + Vector_Gz * ky;
	Vector_Gz = Vector_Gx * iz + Vector_Gy * jz + Vector_Gz * kz;
	
	Vector_Mx = Vector_Mx * ix + Vector_My * jx + Vector_Mz * kx;
	Vector_My = Vector_Mx * iy + Vector_My * jy + Vector_Mz * ky;
	Vector_Mz = Vector_Mx * iz + Vector_My * jz + Vector_Mz * kz;
	
	if (50 < (uint16_t)accRatio && (uint16_t)accRatio < 150) 
	{
		Vector_Gx = (Vector_Gx*lpf1.filter_cf) + (ax*(1-lpf1.filter_cf));//互补滤波器系数
		Vector_Gy = (Vector_Gy*lpf1.filter_cf) + (ay*(1-lpf1.filter_cf));
		Vector_Gz = (Vector_Gz*lpf1.filter_cf) + (az*(1-lpf1.filter_cf));
	}
		
	IMU.Roll =  Degree(atan2f(Vector_Gy, sqrtf(Vector_Gx * Vector_Gx + Vector_Gz* Vector_Gz)));
	IMU.Pitch = Degree(atan2f(-Vector_Gx, sqrtf(Vector_Gy * Vector_Gy + Vector_Gz* Vector_Gz)));
#ifndef USE_HMC5883
	IMU.Yaw =   Degree(atan2f(Vector_My,Vector_Mx));
#endif
}
#endif
