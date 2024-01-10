#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
#include "AD9910.h"
#include "ange_ad.h"
#include "ange_SysTick.h"
#include "ange_timg.h"
#include "ange_timj.h"
#include "bsp_led.h"  
#include "ange_da.h"
#include "ange_rtc_bkp.h"
#include "key.h"
#include "ange_wdg.h"
#include "ange_flash.h"
#include "DDS_API.h"
#include "main.h"
#include "ange_rtc_bkp.h"
#include "ange_iic.h"
#include "ange_timt.h"
float finput[512];
float finput2[512];
float foutput[512];
float fo;
float fo2;
u32   u32input[512];
u32   u32input2[512];
u32   u32output[512];
s32   s32input[512];
s32   s32input2[512];
s32   s32output[512];
//u16   u16input[512];
//u16   u16output[512];
//u8   u8input[512];
//u8   u8output[512];
s32 x,i;
int32_t main(void)
{
		
  ange_USART_init(115200);
/*������ѧ��*/
	//����ֵ
	x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		x++;
	}
	arm_abs_f32(finput,foutput,100);
	//���
	x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_add_f32(finput,finput2,foutput,100);
	//λ��
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_and_u32(u32input,u32input2,u32output,100);
	//���sum = pSrcA[0]*pSrcB[0] + pSrcA[1]*pSrcB[1] + ... + pSrcA[blockSize-1]*pSrcB[blockSize-1]
		x=-9;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_dot_prod_f32(finput,finput2,20,&fo);
	//�˷� pDst[n] = pSrcA[n] * pSrcB[n], 0 <= n < blockSize.
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_mult_f32(finput,finput2,foutput,100);
	//�෴��pDst[n] = -pSrc[n], 0 <= n < blockSize.//�ر�ע�⣬�ⲿ�ֺ���֧��Ŀ��ָ���Դָ��ָ����ͬ�Ļ�����
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_negate_f32(finput,finput,100);
	//λ��
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_not_u32(u32input,u32output,100);
	//ƫ�� pDst[n] = pSrc[n] + offset, 0 <= n < blockSize. ע�⣬�ⲿ�ֺ���֧��Ŀ��ָ���Դָ��ָ����ͬ�Ļ�������
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_offset_f32(finput,10,foutput,100);
	//λ�� 
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_or_u32(u32input,u32input2,u32output,100);
	//���������ⲿ�ֺ�����Ҫ����ʵ�����ݵı����Ŵ����С�� �������ݹ�ʽ�������£�
//pDst[n] = pSrc[n] * scale, 0 <= n < blockSize.
//����� Q31�� Q15�� Q7 ��ʽ�����ݣ� ��ʽ�������£�
//pDst[n] = (pSrc[n] * scaleFract) << shift, 0 <= n < blockSize.
//��������£��������Ӿ��ǣ�
//scale = scaleFract * 2^shift.
//ע�⣬�ⲿ�ֺ���֧��Ŀ��ָ���Դָ��ָ����ͬ�Ļ�������
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_scale_f32(finput,10,foutput,100);
		x=-50;
	for(i=0;i<100;i++)
	{
		s32input[i]=x;
		s32input2[i]=x;
		x++;
	}
	arm_scale_q31(s32input,10,2,s32output,100);
	//λ��
//�ⲿ�ֺ�����Ҫ����ʵ��λ�ƣ���ʽ�������£�
//pDst[n] = pSrc[n] << shift, 0 <= n < blockSize.
//ע�⣬�ⲿ�ֺ���֧��Ŀ��ָ���Դָ��ָ����ͬ�Ļ�������
		x=-50;
	for(i=0;i<100;i++)
	{
		s32input[i]=x;
		s32input2[i]=x;
		x++;
	}
	arm_shift_q31(s32input,3,s32output,100);
	//����
//	�ⲿ�ֺ�����Ҫ����ʵ�ּ�������ʽ�������£�
//pDst[n] = pSrcA[n] - pSrcB[n], 0 <= n < blockSize
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_sub_f32(finput,finput2,foutput,100);
	//���
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_xor_u32(u32input,u32input2,u32output,100);
//	/*������ѧ����*/������
//  arm_sqrt_f32(0.09,&fo);
//		x=-50;
//	for(i=0;i<100;i++)
//	{
//		finput[i]=x;
//		finput2[i]=x;
//		x++;
//	}
//	arm_vsqrt_f32(finput,foutput,100);
//	fo=arm_cos_f32(1.0*60/180*3.14);
//	fo=arm_sin_f32(1.0*60/180*3.14);
	/*������ѧ����*/
	// ������������
//��ʽ������
//for(n=0; n<numSamples; n++)
//{
//pDst[(2*n)+0)] = pSrc[(2*n)+0]; // ʵ��
//pDst[(2*n)+1)] = -pSrc[(2*n)+1]; // �鲿
//}
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_cmplx_conj_f32(finput,foutput,50);
	//�������
//��ʽ������
//realResult=0;
//imagResult=0;
//for(n=0; n<numSamples; n++) {
//realResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+0] - pSrcA[(2*n)+1]*pSrcB[(2*n)+1];
//imagResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+1] + pSrcA[(2*n)+1]*pSrcB[(2*n)+0];
//}
		x=-10;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_cmplx_dot_prod_f32(finput,finput2,20,&fo,&fo2);
	//������ģ
//��ʽ������
//for(n=0; n<numSamples; n++) {
//pDst[n] = sqrt(pSrc[(2*n)+0]^2 + pSrc[(2*n)+1]^2);
//}
	x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
arm_cmplx_mag_f32(finput,foutput,50);
	//����ģƽ��
//��ʽ������
//for(n=0; n<numSamples; n++) {
//pDst[n] = pSrc[(2*n)+0]^2 + pSrc[(2*n)+1]^2;
//}
	x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
arm_cmplx_mag_squared_f32(finput,foutput,50);
	//�����˷�
//��ʽ������
//for(n=0; n<numSamples; n++) {
//pDst[(2*n)+0] = pSrcA[(2*n)+0] * pSrcB[(2*n)+0] - pSrcA[(2*n)+1] * pSrcB[(2*n)+1];
//pDst[(2*n)+1] = pSrcA[(2*n)+0] * pSrcB[(2*n)+1] + pSrcA[(2*n)+1] * pSrcB[(2*n)+0];
//}
	x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
arm_cmplx_mult_cmplx_f32(finput,finput2,foutput,50);
	//������ʵ��
//��ʽ������
//for(n=0; n<numSamples; n++) {
//pCmplxDst[(2*n)+0] = pSrcCmplx[(2*n)+0] * pSrcReal[n];
//pCmplxDst[(2*n)+1] = pSrcCmplx[(2*n)+1] * pSrcReal[n];
//}
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
arm_cmplx_mult_real_f32 (finput,finput2,foutput,50);
/**/
	while(1)
	{
	}
}



