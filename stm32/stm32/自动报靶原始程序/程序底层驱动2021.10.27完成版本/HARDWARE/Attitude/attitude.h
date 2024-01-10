#ifndef _attitude_H
#define _attitude_H
#include "Algorithm_quaternion.h"
#include "Algorithm_math.h"

/*   传感器校准  */
//#define ACC_GYRO_CAL_EN
//#define First_Calibrating
/*   原始数据滤波  */
//#define USE_IIR_Filter        // 使用IIR+一阶低通滤波
//#define USE_Steepest_Filter   // 使用梯度下降拟合滤波
//#define USE_HD_Filter         // 使用滑动+一阶低通滤波
/*   姿态解算  */
#define USE_DCM

extern EulerAngle IMU;           // 三个方向姿态角传出


void DCM_CF(float gx,float gy,float gz,float ax,float ay,float az,float dt);


#endif
