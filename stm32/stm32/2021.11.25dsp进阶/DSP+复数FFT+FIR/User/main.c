#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_USART.h"
#include "ange_dma.h"
#define FIR_hanshu 1
#define IIR_hanshu 0
#if FIR_hanshu
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
arm_cfft_instance_f32 varInstCfftF32;
uint32_t refIndex = 213, testIndex = 0;
#define fs 44800
#define pi 3.1415926
#define num 256
float input[num];
float input_fft[num*2];
float out[num];
#define fir_sample num
#define fir_size   256  //调用一次处理的数量
#define fir_num   29   //fir滤波器系数个数
float fir_input[fir_sample];
float fir_output[fir_sample];
float fir_state[fir_size+fir_num-1];
arm_fir_instance_f32 F;
float fir_output_fft[fir_sample*2];
// fdatool工具
const float LT[29] = {
   0.001286207204908,-0.001296973284681,-0.003000711108496, 0.001444865258538,
   0.008009016825171,0.0006750908856413, -0.01697711454583,-0.009397219364226,
    0.02885578843708,  0.03137495697012,  -0.0410238678079, -0.08354714549036,
    0.05017255845178,   0.3102031395362,   0.4464428160641,   0.3102031395362,
    0.05017255845178, -0.08354714549036,  -0.0410238678079,  0.03137495697012,
    0.02885578843708,-0.009397219364226, -0.01697711454583,0.0006750908856413,
   0.008009016825171, 0.001444865258538,-0.003000711108496,-0.001296973284681,
   0.001286207204908
};
const float HT[29] = {
  -4.227972219877e-18,-0.002017207671221,-0.002601173329327, 0.001160160727948,
   0.007849334209498, 0.007498930271009,-0.007547558453377, -0.02453021987026,
   -0.01477087027243,  0.02932608290627,  0.06407985062841,  0.02121901869738,
    -0.1186424471891,  -0.2831898022368,   0.6421996544612,  -0.2831898022368,
    -0.1186424471891,  0.02121901869738,  0.06407985062841,  0.02932608290627,
   -0.01477087027243, -0.02453021987026,-0.007547558453377, 0.007498930271009,
   0.007849334209498, 0.001160160727948,-0.002601173329327,-0.002017207671221,
  -4.227972219877e-18
};
const float DT[29] = {
                   0,5.749825664855e-05,-0.0001731008644038,0.0001798674056106,
  0.0005131838651001,-0.005944259044567, -0.01608635281502,1.001274485315e-17,
    0.05289333919869,  0.06986244662383, -0.02762360840254,  -0.1550187527169,
    -0.1178399860039,  0.09082681020185,   0.2165349051121,  0.09082681020185,
    -0.1178399860039,  -0.1550187527169, -0.02762360840254,  0.06986244662383,
    0.05289333919869,1.001274485315e-17, -0.01608635281502,-0.005944259044567,
  0.0005131838651001,0.0001798674056106,-0.0001731008644038,5.749825664855e-05,
                   0
};
 void InitBufInArray()
 {
     unsigned short i;
	 /*当采样频率为44800时频率4900,8400,18725幅值分别为1500 2700 4000的正弦信号的叠加，直流分量为100*/
    for(i=0; i<num; i++)
     {
         input[i] = 1500 * sin(2*pi * i * 4900.0 / fs) +
              2700 * sin(2*pi * i * 8400.0 / fs) +
              4000 * sin(2*pi * i * 100000.0 / fs)+100;
    }
    for(i=0; i<num; i++)
     {
			 fir_input[i]=input[i];
    }
 }
 
int32_t main(void)
{
	u32 i;
	ange_USART_init(115200);
  float32_t maxValue;

	InitBufInArray();
	printf("原始信号\n");
	for(i=0;i<fir_sample;i++)
	{
		printf("%.3f\n",input[i]);  //原始信号
	}
	arm_fir_init_f32(&F,fir_num,LT,fir_state,fir_size); //FIR初始化
	for(i=0;i<fir_sample/fir_size;i++)
	{
		arm_fir_f32(&F,fir_input+(i*fir_size),fir_output+(i*fir_size),fir_size); //进行FIR
	}
	printf("fir输出数据\n");
	for(i=0;i<fir_sample;i++)
	{
		printf("%.3f\n",fir_output[i]);
	}
    for(i=0; i<num*2; i+=2)
     {
         input_fft[i] = input[i/2];
         input_fft[i+1]=0;
    }
    for(i=0; i<num*2; i+=2)
     {
         input_fft[i] = input[i/2];
         input_fft[i+1]=0;
    }
	/*fft变换*/
	  arm_cfft_init_f32(&varInstCfftF32,num);
  arm_cfft_f32(&varInstCfftF32, input, ifftFlag, doBitReverse);

  arm_cmplx_mag_f32(input,out,num);
		printf("fft结果");
    for(i=0; i<num*2; i+=1)
     {
			 printf("%.3f\n",out[i]);
    }
/*找出数组最大值以及下标*/
  arm_max_f32(out, num, &maxValue, &testIndex);
    while (1);                             /* main function does not return */
}
#endif
#if IIR_hanshu

#endif


