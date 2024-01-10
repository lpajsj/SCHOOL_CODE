#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"

#if defined(SEMIHOSTING)
#include <stdio.h>
#endif
#define TEST_LENGTH_SAMPLES 2048
/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
//extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
static float32_t testOutput[TEST_LENGTH_SAMPLES/2];
/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
arm_cfft_instance_f32 varInstCfftF32;
/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, testIndex = 0;
/* ----------------------------------------------------------------------
* Max magnitude FFT Bin test
* ------------------------------------------------------------------- */
//int32_t main(void)
//{
//  arm_status status;
//  float32_t maxValue;
//  status = ARM_MATH_SUCCESS;
//  status=arm_cfft_init_f32(&varInstCfftF32,fftSize);
//  /* Process the data through the CFFT/CIFFT module */
//  arm_cfft_f32(&varInstCfftF32, testInput_f32_10khz, ifftFlag, doBitReverse);
//  /* Process the data through the Complex Magnitude Module for
//  calculating the magnitude at each bin */
//  arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);
//  /* Calculates maxValue and returns corresponding BIN value */
//  arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);
//  status = (testIndex != refIndex) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;
//  
//  if (status != ARM_MATH_SUCCESS)
//  {
//#if defined (SEMIHOSTING)
//    printf("FAILURE\n");
//#else
//    while (1);                             /* main function does not return */
//#endif
//  }
//  else
//  {
//#if defined (SEMIHOSTING)
//    printf("SUCCESS\n");
//#else
//    while (1);                             /* main function does not return */
//#endif
//  }
//}
#define fs 44800
#define pi 3.1415926
#define num 256
float input[2*num];
float out[num];
 void InitBufInArray()
 {
     unsigned short i;
	 /*������Ƶ��Ϊ44800ʱƵ��4900,8400,18725��ֵ�ֱ�Ϊ1500 2700 4000�������źŵĵ��ӣ�ֱ������Ϊ100*/
    for(i=0; i<num*2; i+=2)
     {
         input[i] = 1500 * sin(pi * i * 4900.0 / fs) +\
              2700 * sin(pi * i * 8400.0 / fs) +\
              4000 * sin(pi * i * 18725.0 / fs)+100;
         input[i+1]=0;
    }
 }
int32_t main(void)
{
  arm_status status;
  float32_t maxValue;
	/* cfft �����ṹ���ʼ����num��Ӧȡ�ĵ�����Ҳ���Բ��ó�ʼ����ֱ������Ӧ�Ķ���
	arm_cfft_sR_f32_len256��arm_cfft_sR_f32_len512��*/
  arm_cfft_init_f32(&varInstCfftF32,num);
	/*ģ���������Ƶ�����Ҳ���fs�������µ�����  
	��ǰ���� FFT ����֧�ָ������ͣ� Q31 �� Q15���͡� �д����������ݴ����һ�����������У�
	Ϊ�˽�ʡ�ռ䣬��Щ FFT ������FFT�ı任������������������У������˳���Ϊ��ʵ�����鲿��
	ʵ�����鲿�������������鳤��Ϊȡ�����2��*/
	InitBufInArray();
	/*fft�任*/
  arm_cfft_f32(&varInstCfftF32, input, ifftFlag, doBitReverse);
	/*������ģ���㣬����out����Ϳ��Է���Ƶ�ʷ�ֵ����ȥ��һ����ó�������ǰһ�����һ�������ǶԳƵģ�Ҳ����˵
	���Բ��Ƶ�����Ϊ����Ƶ�ʵ�һ�룬
	������Ƶ��Ϊ Fs���ź�Ƶ�� F����������Ϊ N����ôĳ�� n ����ʾ��Ƶ��Ϊ��
Fn=(n-1)*Fs/N; ������n��1��ʼ������
		FFT�õ��ĵ�һ��Ƶ��Ϊ0����Ϊֱ�����������ֵΪʵ��ֱ��������N��
	��X�����Ϊ���������ֵΪʵ�ʵ�N/2��
��FFT�任���n��ķ���ֵΪAn�����Ӧ��ʵ�����������ֵ��
A=An/(N/2);
����������ʽ���ɽ�FFT�����ʵ����������Ӧ����*/
  arm_cmplx_mag_f32(input,out,num);
/*�ҳ��������ֵ�Լ��±�*/
  arm_max_f32(out, num, &maxValue, &testIndex);
    while (1);                             /* main function does not return */
}