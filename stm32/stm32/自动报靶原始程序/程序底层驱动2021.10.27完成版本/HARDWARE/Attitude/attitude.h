#ifndef _attitude_H
#define _attitude_H
#include "Algorithm_quaternion.h"
#include "Algorithm_math.h"

/*   ������У׼  */
//#define ACC_GYRO_CAL_EN
//#define First_Calibrating
/*   ԭʼ�����˲�  */
//#define USE_IIR_Filter        // ʹ��IIR+һ�׵�ͨ�˲�
//#define USE_Steepest_Filter   // ʹ���ݶ��½�����˲�
//#define USE_HD_Filter         // ʹ�û���+һ�׵�ͨ�˲�
/*   ��̬����  */
#define USE_DCM

extern EulerAngle IMU;           // ����������̬�Ǵ���


void DCM_CF(float gx,float gy,float gz,float ax,float ay,float az,float dt);


#endif
