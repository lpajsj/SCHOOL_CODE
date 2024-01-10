#include "stm32f10x_conf.h"
#include "ange_usart.h"
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	printf("%s第%d行输入参数错误\n",file,line);
}
#endif


	#if 0
/*基础数学库*/
	//绝对值
	x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		x++;
	}
	arm_abs_f32(finput,foutput,100);
	//求和
	x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_add_f32(finput,finput2,foutput,100);
	//位与
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_and_u32(u32input,u32input2,u32output,100);
	//点乘sum = pSrcA[0]*pSrcB[0] + pSrcA[1]*pSrcB[1] + ... + pSrcA[blockSize-1]*pSrcB[blockSize-1]
		x=-9;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_dot_prod_f32(finput,finput2,20,&fo);
	//乘法 pDst[n] = pSrcA[n] * pSrcB[n], 0 <= n < blockSize.
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_mult_f32(finput,finput2,foutput,100);
	//相反数pDst[n] = -pSrc[n], 0 <= n < blockSize.//特别注意，这部分函数支持目标指针和源指针指向相同的缓冲区
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_negate_f32(finput,finput,100);
	//位非
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_not_u32(u32input,u32output,100);
	//偏移 pDst[n] = pSrc[n] + offset, 0 <= n < blockSize. 注意，这部分函数支持目标指针和源指针指向相同的缓冲区。
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_offset_f32(finput,10,foutput,100);
	//位或 
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_or_u32(u32input,u32input2,u32output,100);
	//比例因子这部分函数主要用于实现数据的比例放大和缩小， 浮点数据公式描述如下：
//pDst[n] = pSrc[n] * scale, 0 <= n < blockSize.
//如果是 Q31， Q15， Q7 格式的数据， 公式描述如下：
//pDst[n] = (pSrc[n] * scaleFract) << shift, 0 <= n < blockSize.
//这种情况下，比例因子就是：
//scale = scaleFract * 2^shift.
//注意，这部分函数支持目标指针和源指针指向相同的缓冲区。
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
	//位移
//这部分函数主要用于实现位移，公式描述如下：
//pDst[n] = pSrc[n] << shift, 0 <= n < blockSize.
//注意，这部分函数支持目标指针和源指针指向相同的缓冲区。
		x=-50;
	for(i=0;i<100;i++)
	{
		s32input[i]=x;
		s32input2[i]=x;
		x++;
	}
	arm_shift_q31(s32input,3,s32output,100);
	//减法
//	这部分函数主要用于实现减法，公式描述如下：
//pDst[n] = pSrcA[n] - pSrcB[n], 0 <= n < blockSize
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_sub_f32(finput,finput2,foutput,100);
	//异或
		x=0;
	for(i=0;i<100;i++)
	{
		u32input[i]=x;
		u32input2[i]=x*2;
		x++;
	}
	arm_xor_u32(u32input,u32input2,u32output,100);
//	/*快速数学函数*/
  arm_sqrt_f32(0.09,&fo);
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_vsqrt_f32(finput,foutput,100);
	fo=arm_cos_f32(1.0*60/180*3.14);
	fo=arm_sin_f32(1.0*60/180*3.14);
	/*复数数学函数*/
	// 复数共轭运算
//公式描述：
//for(n=0; n<numSamples; n++)
//{
//pDst[(2*n)+0)] = pSrc[(2*n)+0]; // 实部
//pDst[(2*n)+1)] = -pSrc[(2*n)+1]; // 虚部
//}
		x=-50;
	for(i=0;i<100;i++)
	{
		finput[i]=x;
		finput2[i]=x;
		x++;
	}
	arm_cmplx_conj_f32(finput,foutput,50);
	//复数点乘
//公式描述：
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
	//复数求模
//公式描述：
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
	//复数模平方
//公式描述：
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
	//复数乘法
//公式描述：
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
	//复数乘实数
//公式描述：
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
#endif