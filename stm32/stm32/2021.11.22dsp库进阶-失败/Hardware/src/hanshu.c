#include "hanshu.h"
/*******************************************************************************
作用：线性拟合函数
参数： dataX[]-X轴数据，dataY[]-Y轴数据，number-要处理的点数
全局变量：xishu-系数，pianzhi-偏置
说明：正，负相关的直线都能处理，输入无顺序要求
*******************************************************************************/
float xishu,pianzhi;
void xianxingnihe(float dataX[],float dataY[],uint8_t number)
{
	float xiao_sum=0,pian_sum=0,xishu0=0,pianzhi0=0,cha=0;
	uint8_t i;
	
	for(i=0;i<number-1;i++)
	{

		cha=dataY[i+1]-dataY[i];//Y轴的点相减
		xishu0=cha/(dataX[i+1]-dataX[i]);//Y的差值除X的差值，得到系数
		xiao_sum=xiao_sum+xishu0;//系数相加
		
		pianzhi0=dataY[i+1]-(dataX[i+1]*xishu0);//偏置=Y-系数*X
		pian_sum=pian_sum+pianzhi0;
	}
	xishu=xiao_sum/(number-1);
	pianzhi=pian_sum/(number-1);
}
/*******************************************************************************
作用：分段线性拟合函数
参数： dataX[]-X轴数据，dataY[]-Y轴数据，number-要分的段数,fengduan[255]要分段的点的位置
例如：fengduan[3]={1,2,3};  说明1到2一段，2到3一段。
全局变量： xishudata[255]-系数，pianzhidata[255]-偏置，
说明：正，负相关的直线都能处理，X,Y的数据必须按分段的顺序输入
*******************************************************************************/
float xishudata[255]={0},pianzhidata[255]={0};
void fengduannihe(float dataX[],float dataY[],uint8_t fengduan[],uint8_t number)
{
	float xiao_sum=0,pian_sum=0,xishu0=0,pianzhi0=0,cha=0;
	uint8_t i,j;
	for(j=0;j<number;j++)
	{
		xiao_sum=0;pian_sum=0;
		for(i=fengduan[j];i<fengduan[j+1];i++)
		{
			cha=dataY[i]-dataY[i-1];//Y轴的点相减
			xishu0=cha/(dataX[i]-dataX[i-1]);//Y的差值除X的差值，得到系数
			xiao_sum=xiao_sum+xishu0;//系数相加
			
			pianzhi0=dataY[i]-(dataX[i]*xishu0);//偏置=Y-系数*X
			pian_sum=pian_sum+pianzhi0;
		}
		xishudata[j]=xiao_sum/(fengduan[j+1]-fengduan[j]);
		pianzhidata[j]=pian_sum/(fengduan[j+1]-fengduan[j]);		
	}
}
