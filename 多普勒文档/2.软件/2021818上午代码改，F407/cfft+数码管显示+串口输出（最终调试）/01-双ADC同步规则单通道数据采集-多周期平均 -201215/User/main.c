/**********************************************************************************************************
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	版    本 : V1.1
*	说    明 : 1. 配置ADC1的通道0,10进行转换和ADC2的通道0,10进行转换,使用引脚PAC0和PA0
*              2. 创建一个500ms为周期的软件定时器，每500ms打印一次采集数据
*              注意事项：
*                1. 本实验推荐使用串口软件SecureCRT，要不串口打印效果不整齐。
*                2. 务必将编辑器的缩进参数和TAB设置为4来阅读本文件，要不代码显示不整齐。
*                3. 板载ADC，DAC参考电压跳线帽接到3.3V上，而不是2.5V上。
*********************************************************************************************************/
/* 底层硬件驱动 */
#include "bsp.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "led.h"
#include "sysTick.h"
#include "clkconfig.h"

/* 仅允许本文件内调用的函数声明 */
static void PrintfLogo(void);
static void arm_cfft_f32_app(void);
    
extern __IO uint32_t aADCDualConvertedValue[DMA_BUFFER_SIZE];
extern __IO uint8_t  FLAG_DMA_TC;

/* 输入和输出缓冲 */
static float32_t testOutput[DMA_BUFFER_SIZE]; 
static float32_t testInput[DMA_BUFFER_SIZE*2];
//static float32_t testOutput_half[DMA_BUFFER_SIZE/2];
/* 临时缓冲 */
static float32_t testInput_Real[DMA_BUFFER_SIZE];
static float32_t testInput_Imag[DMA_BUFFER_SIZE];
/* 变量 */
uint32_t fftSize = DMA_BUFFER_SIZE; 
uint32_t ifftFlag1 = 0; 
uint32_t doBitReverse = 1; 
float Doppler_velocity = 0;
float Doppler_velocity1 = 0;

unsigned int Doppler_velocity_output;
unsigned char Doppler_velocity_output1;
unsigned char Doppler_velocity_output2;

//#define M_LEVEL  5   //定义取平均周期数
/**********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************/
int main(void)
{   
	HSI_SetSysClock(16,336,2,7);
//    uint16_t i;
    /* ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f4xx.c 文件，主要功能是
	配置CPU系统的时钟，内部Flash访问时序，配置FSMC用于外部SRAM。*/
	bsp_Init();		/* 硬件初始化 */
    LED_GPIO_Config();//数码管初始化
//	PrintfLogo();	/* 打印例程信息到串口1 */
	SysTick_Init(168);
//    delay_ms(5000);
//	bsp_StartAutoTimer(0, 500);	/* 启动1个500ms的自动重装的定时器 */
	bsp_ADCTrigEnable();  /* 启动I,Q 双通道ADC采样，采样率取决于ADC_FREQUENCY，定义于bsp_timer.h */
  FLAG_DMA_TC = 0;
	/* 进入主程序循环体 */
	//显示测试
	ST0;
	output(0x34);
	delay_us(2);
	output(0x12);
	delay_us(2);
	output(0x56);
	ST1;
	delay_us(1);
	ST0;
	
	
	
	while (1)
	{
//		while(1)
//		{
//			GPIO_ToggleBits(GPIOA,GPIO_Pin_15);
//			delay_us(10);
//		}
		bsp_Idle();		/* 这个函数在bsp.c文件。用户可以修改这个函数实现CPU休眠和喂狗 */ 
		/*  DMA传输完成中断里改变FLAG_DMA_TC标志*/
		

		if (FLAG_DMA_TC == 1)
		{
				bsp_ADCTrigDisable(); //该函数可以放在中断里面
				arm_cfft_f32_app(); //计算FFT和求模，并求取最大值和下标
				bsp_ADCTrigEnable(); 
				FLAG_DMA_TC = 0;
//			 delay_ms(100);
		}

		if (bsp_CheckTimer(0))	/* 判断软件定时器超时时间 */
		{           
			printf("uwADC1_2ConvertedVoltage = %0.5f\r\n", Doppler_velocity);
		}

	}
}
/*
*********************************************************************************************************
*	函 数 名: arm_cfft_f32_app
*	功能说明: 调用函数arm_cfft_f32_app计算幅频。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
    float32_t   pResult; 
    uint32_t    pIndex;
    uint32_t    pIndex1;
    float32_t   pMean_Real;
    float32_t   pMean_Imag;
static void arm_cfft_f32_app(void)
{
	uint16_t    i, n;


	
	/* 按照实部，虚部，实部，虚部..... 的顺序存储数据 */
	for(i=0; i<fftSize; i++)
	{
		testInput_Real[i] = (float32_t)((aADCDualConvertedValue[i] & 0xffff) * 3.3f) / 0Xfff;
        testInput_Imag[i] = (float32_t)((aADCDualConvertedValue[i] >> 16)* 3.3f) / 0Xfff;
	}
	
    /* 求平均，计算直流偏量 */
    arm_mean_f32(testInput_Real,fftSize,&pMean_Real);
    arm_mean_f32(testInput_Imag,fftSize,&pMean_Imag);
    /* 去直流 */
	for(i=0; i<fftSize; i++)
	{
		testInput[i*2] = testInput_Real[i]-pMean_Real;
        testInput[i*2+1] = testInput_Imag[i]-pMean_Imag;
	}
	//输出原始信号
//	for(i=0; i<fftSize; i++)
//	{
//		printf("%f,", testInput[i*2]);
//		printf("%f\r\n", testInput[i*2+1]);
////		printf("%f,", testInput_Real[i]);
////		printf("%f\r\n", testInput_Imag[i]);
//	}
	/* CFFT变换 */ 
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, testInput, ifftFlag1, doBitReverse);

//	/* 求解模值  */ 
	arm_cmplx_mag_f32(testInput, testOutput, fftSize);
//    /* 取半个长度数组不可以要 数据并不是对称的  */

		for(i=0; i<fftSize; i++)
	{
//		printf("%f\r\n", testOutput[i]);
//		if(testOutput[i]<=20)
//		{
//			testOutput[i]=0;
//		}
	}
////    /* 滤除工频干扰，阀值设为60Hz  */
////    n = 60*DMA_BUFFER_SIZE/ADC_FREQUENCY;
//	//设置阀值，将模值数据中低于阀值的数据置为0
////	for(i=0; i<n; i++)
////	{
////      testOutput_half[i] = 0;
////	}
    /* 求最大频点及其位置下标  */
  arm_max_f32(testOutput, fftSize, &pResult, &pIndex);
	pIndex1=pIndex;
	if(pIndex1>512)
	{
		pIndex1=fftSize-pIndex1;
		Doppler_velocity = -3.6*pIndex1*ADC_FREQUENCY/(fftSize*160);
	}
	else
	{
    /* 求取多普勒速度  */
    Doppler_velocity = 3.6*pIndex1*ADC_FREQUENCY/(fftSize*160);
	}
    
//  printf("arm_max_f32 : pResult = %f pIndex = %d Doppler_velocity = %f\r\n", pResult, pIndex, Doppler_velocity);

	Doppler_velocity1= fabs(Doppler_velocity);
	//数码管显示数据
	Doppler_velocity_output = Doppler_velocity1*100;
	Doppler_velocity_output1 = Doppler_velocity_output % 10;
	Doppler_velocity_output2 = (Doppler_velocity_output % 100)/10;
	ST0;	
	output((Doppler_velocity_output2 << 4)|Doppler_velocity_output1);
//	printf("%d",(Doppler_velocity_output2 << 4)|Doppler_velocity_output1);
	Doppler_velocity_output1 = (Doppler_velocity_output / 100)%10;
	Doppler_velocity_output2 = (Doppler_velocity_output / 1000)%10;	
	output((Doppler_velocity_output2 << 4)|Doppler_velocity_output1);
	if(Doppler_velocity<0)
  output(0xAb);
	else
	{
		output(0xAa);
	}
	ST1;
	delay_us(1);
	ST0;
	
}
/**********************************************************************************************************
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开PC机的超级终端软件可以观察结果
*	形    参：无
*	返 回 值: 无
**********************************************************************************************************/
static void PrintfLogo(void)
{
	printf("\r\n ----双ADC同步规则单通道数据采集实验----\r\n");
}
