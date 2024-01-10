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
	 /*当采样频率为44800时频率4900,8400,18725幅值分别为1500 2700 4000的正弦信号的叠加，直流分量为100*/
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
	/* cfft 函数结构体初始化，num对应取的点数，也可以不用初始化，直接有相应的定义
	arm_cfft_sR_f32_len256，arm_cfft_sR_f32_len512等*/
  arm_cfft_init_f32(&varInstCfftF32,num);
	/*模拟产生几个频率正弦波在fs采样率下的数据  
	当前复数 FFT 函数支持浮点类型， Q31 和 Q15类型。 有待分析的数据存放在一个输入数组中，
	为了节省空间，这些 FFT 函数将FFT的变换结果覆盖在输入数组中，数组的顺序均为：实部、虚部、
	实部、虚部，所以输入数组长度为取样点的2倍*/
	InitBufInArray();
	/*fft变换*/
  arm_cfft_f32(&varInstCfftF32, input, ifftFlag, doBitReverse);
	/*复数求模运算，根据out数组就可以分析频率幅值，除去第一个点得出的数据前一半与后一半数据是对称的，也就是说
	可以测的频率最大为采样频率的一半，
	若采样频率为 Fs，信号频率 F，采样点数为 N，那么某点 n 所表示的频率为：
Fn=(n-1)*Fs/N; （假设n从1开始计数）
		FFT得到的第一点频率为0，即为直流分量，其幅值为实际直流分量的N倍
	而X后面的为复数，其幅值为实际的N/2倍
若FFT变换后第n点的幅度值为An，则对应的实际物理幅度数值：
A=An/(N/2);
运用上述公式即可将FFT结果和实际物理量对应起来*/
  arm_cmplx_mag_f32(input,out,num);
/*找出数组最大值以及下标*/
  arm_max_f32(out, num, &maxValue, &testIndex);
    while (1);                             /* main function does not return */
}