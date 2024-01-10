#ifndef  _ANO_H
#define  _ANO_H
#include "sys.h"

//&有两种用法 引用声明和取地址
//*            指针声明和取值
//Data  u8
//*&   *优先级> &  两个运算符从右向左结合运算
//*&a   先运算* 得到指针，然后运算&得到指针的引用
#define  PART0(Data) (*(char*)(&Data))
#define  PART1(Data) (*((char*)(&Data)+1))//地址
#define  PART2(Data) (*((char*)(&Data)+2))
#define  PART3(Data) (*((char*)(&Data)+3))
	
void  usart1_send_char(u8 c);
void  Data_Send_Ver(u8 HardwareType,float HardwareVER,float SoftwareVER,float ProtocolVER,float BootlocaderVER);
void  Data_Send_Status(float ROL,float PIT,float YAW,s32 ALT_USE,u8 FLY_MODEL,u8 ARMED);
void  Data_Send_Senser(s16 ACC_X,s16 ACC_Y,s16 ACC_Z,s16 GYRO_X,s16 GYRO_Y,s16 GYRO_Z,s16 MAG_X,s16 MAG_Y,s16 MAG_Z);
void  Data_Send_RCDATA(s16 THR,s16 YAW,s16 ROL,s16 PIT,s16 AUX1,s16 AUX2,s16 AUX3,s16 AUX4,s16 AUX5,s16 AUX6);
void  Data_Send_GPSDATA(u8 GPSlocation,u8 GPSNum,float LNG,float LAT,float Rangle);
void  Data_Send_Power(float Votage,float Current);
void  Data_Send_MOTO(u16 PWM_MOTO1,u16 PWM_MOTO2,u16 PWM_MOTO3,u16 PWM_MOTO4,u16 PWM_MOTO5,u16 PWM_MOTO6,u16 PWM_MOTO7,u16 PWM_MOTO8);
#endif
