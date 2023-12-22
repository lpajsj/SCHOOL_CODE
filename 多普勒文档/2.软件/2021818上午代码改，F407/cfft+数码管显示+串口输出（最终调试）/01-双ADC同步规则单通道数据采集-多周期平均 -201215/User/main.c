/**********************************************************************************************************
*	ģ������ : ������ģ�顣
*	�ļ����� : main.c
*	��    �� : V1.1
*	˵    �� : 1. ����ADC1��ͨ��0,10����ת����ADC2��ͨ��0,10����ת��,ʹ������PAC0��PA0
*              2. ����һ��500msΪ���ڵ������ʱ����ÿ500ms��ӡһ�βɼ�����
*              ע�����
*                1. ��ʵ���Ƽ�ʹ�ô������SecureCRT��Ҫ�����ڴ�ӡЧ�������롣
*                2. ��ؽ��༭��������������TAB����Ϊ4���Ķ����ļ���Ҫ��������ʾ�����롣
*                3. ����ADC��DAC�ο���ѹ����ñ�ӵ�3.3V�ϣ�������2.5V�ϡ�
*********************************************************************************************************/
/* �ײ�Ӳ������ */
#include "bsp.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "led.h"
#include "sysTick.h"
#include "clkconfig.h"

/* �������ļ��ڵ��õĺ������� */
static void PrintfLogo(void);
static void arm_cfft_f32_app(void);
    
extern __IO uint32_t aADCDualConvertedValue[DMA_BUFFER_SIZE];
extern __IO uint8_t  FLAG_DMA_TC;

/* ������������ */
static float32_t testOutput[DMA_BUFFER_SIZE]; 
static float32_t testInput[DMA_BUFFER_SIZE*2];
//static float32_t testOutput_half[DMA_BUFFER_SIZE/2];
/* ��ʱ���� */
static float32_t testInput_Real[DMA_BUFFER_SIZE];
static float32_t testInput_Imag[DMA_BUFFER_SIZE];
/* ���� */
uint32_t fftSize = DMA_BUFFER_SIZE; 
uint32_t ifftFlag1 = 0; 
uint32_t doBitReverse = 1; 
float Doppler_velocity = 0;
float Doppler_velocity1 = 0;

unsigned int Doppler_velocity_output;
unsigned char Doppler_velocity_output1;
unsigned char Doppler_velocity_output2;

//#define M_LEVEL  5   //����ȡƽ��������
/**********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************/
int main(void)
{   
	HSI_SetSysClock(16,336,2,7);
//    uint16_t i;
    /* ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f4xx.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ�ӣ��ڲ�Flash����ʱ������FSMC�����ⲿSRAM��*/
	bsp_Init();		/* Ӳ����ʼ�� */
    LED_GPIO_Config();//����ܳ�ʼ��
//	PrintfLogo();	/* ��ӡ������Ϣ������1 */
	SysTick_Init(168);
//    delay_ms(5000);
//	bsp_StartAutoTimer(0, 500);	/* ����1��500ms���Զ���װ�Ķ�ʱ�� */
	bsp_ADCTrigEnable();  /* ����I,Q ˫ͨ��ADC������������ȡ����ADC_FREQUENCY��������bsp_timer.h */
  FLAG_DMA_TC = 0;
	/* ����������ѭ���� */
	//��ʾ����
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
		bsp_Idle();		/* ���������bsp.c�ļ����û������޸��������ʵ��CPU���ߺ�ι�� */ 
		/*  DMA��������ж���ı�FLAG_DMA_TC��־*/
		

		if (FLAG_DMA_TC == 1)
		{
				bsp_ADCTrigDisable(); //�ú������Է����ж�����
				arm_cfft_f32_app(); //����FFT����ģ������ȡ���ֵ���±�
				bsp_ADCTrigEnable(); 
				FLAG_DMA_TC = 0;
//			 delay_ms(100);
		}

		if (bsp_CheckTimer(0))	/* �ж������ʱ����ʱʱ�� */
		{           
			printf("uwADC1_2ConvertedVoltage = %0.5f\r\n", Doppler_velocity);
		}

	}
}
/*
*********************************************************************************************************
*	�� �� ��: arm_cfft_f32_app
*	����˵��: ���ú���arm_cfft_f32_app�����Ƶ��
*	��    �Σ���
*	�� �� ֵ: ��
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


	
	/* ����ʵ�����鲿��ʵ�����鲿..... ��˳��洢���� */
	for(i=0; i<fftSize; i++)
	{
		testInput_Real[i] = (float32_t)((aADCDualConvertedValue[i] & 0xffff) * 3.3f) / 0Xfff;
        testInput_Imag[i] = (float32_t)((aADCDualConvertedValue[i] >> 16)* 3.3f) / 0Xfff;
	}
	
    /* ��ƽ��������ֱ��ƫ�� */
    arm_mean_f32(testInput_Real,fftSize,&pMean_Real);
    arm_mean_f32(testInput_Imag,fftSize,&pMean_Imag);
    /* ȥֱ�� */
	for(i=0; i<fftSize; i++)
	{
		testInput[i*2] = testInput_Real[i]-pMean_Real;
        testInput[i*2+1] = testInput_Imag[i]-pMean_Imag;
	}
	//���ԭʼ�ź�
//	for(i=0; i<fftSize; i++)
//	{
//		printf("%f,", testInput[i*2]);
//		printf("%f\r\n", testInput[i*2+1]);
////		printf("%f,", testInput_Real[i]);
////		printf("%f\r\n", testInput_Imag[i]);
//	}
	/* CFFT�任 */ 
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, testInput, ifftFlag1, doBitReverse);

//	/* ���ģֵ  */ 
	arm_cmplx_mag_f32(testInput, testOutput, fftSize);
//    /* ȡ����������鲻����Ҫ ���ݲ����ǶԳƵ�  */

		for(i=0; i<fftSize; i++)
	{
//		printf("%f\r\n", testOutput[i]);
//		if(testOutput[i]<=20)
//		{
//			testOutput[i]=0;
//		}
	}
////    /* �˳���Ƶ���ţ���ֵ��Ϊ60Hz  */
////    n = 60*DMA_BUFFER_SIZE/ADC_FREQUENCY;
//	//���÷�ֵ����ģֵ�����е��ڷ�ֵ��������Ϊ0
////	for(i=0; i<n; i++)
////	{
////      testOutput_half[i] = 0;
////	}
    /* �����Ƶ�㼰��λ���±�  */
  arm_max_f32(testOutput, fftSize, &pResult, &pIndex);
	pIndex1=pIndex;
	if(pIndex1>512)
	{
		pIndex1=fftSize-pIndex1;
		Doppler_velocity = -3.6*pIndex1*ADC_FREQUENCY/(fftSize*160);
	}
	else
	{
    /* ��ȡ�������ٶ�  */
    Doppler_velocity = 3.6*pIndex1*ADC_FREQUENCY/(fftSize*160);
	}
    
//  printf("arm_max_f32 : pResult = %f pIndex = %d Doppler_velocity = %f\r\n", pResult, pIndex, Doppler_velocity);

	Doppler_velocity1= fabs(Doppler_velocity);
	//�������ʾ����
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
*	�� �� ��: PrintfLogo
*	����˵��: ��ӡ�������ƺ����̷�������, ���ϴ����ߺ󣬴�PC���ĳ����ն�������Թ۲���
*	��    �Σ���
*	�� �� ֵ: ��
**********************************************************************************************************/
static void PrintfLogo(void)
{
	printf("\r\n ----˫ADCͬ������ͨ�����ݲɼ�ʵ��----\r\n");
}
