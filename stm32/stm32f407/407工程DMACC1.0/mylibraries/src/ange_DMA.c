#include "ange_dma.h"
#if ange_DMA_CC
void ange_DMA_CC_Config( u32* y,u32 *m,u32 n)//�洢�������洢�� Դ��ַ��Ŀ���ַ��������
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_CC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_CC_Channel;  //ͨ��
	
	dmainit.DMA_DIR=DMA_DIR_MemoryToMemory;  //SRC ���赽�洢�� DST �浽��
	dmainit.DMA_PeripheralBaseAddr=(u32)y;  //��ַ
	dmainit.DMA_Memory0BaseAddr=(u32)m;
	dmainit.DMA_BufferSize=n;  //������
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Enable; //�����ַ����ʹ��
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //�ڴ��ַʹ��
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;  //���ݴ�С
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;        
	dmainit.DMA_Mode=DMA_Mode_Normal;  //�ڴ浽�ڴ治����ѭ��
	dmainit.DMA_Priority=DMA_Priority_High; //�ٲ����ȼ�
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifoģʽ���洢�����洢���Զ���
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo��С����  fullΪ4��
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //���δ���
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_CC_STREAM,&dmainit);
	DMA_Cmd(ange_DMA_CC_STREAM,ENABLE);
}
#endif
#if ange_DMA_CW
void ange_DMA_CW_USARTConfig(u8* y,u32 m)//�洢��������
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_CW_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralDST;  
	dmainit.DMA_PeripheralBaseAddr=(u32)m;
	dmainit.DMA_MemoryBaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DMA_CW_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;
	dmainit.DMA_Priority=DMA_Priority_Medium;
	dmainit.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(ange_DMA_CW_Channel,&dmainit);
	DMA_Cmd(ange_DMA_CW_Channel,ENABLE);
}
#endif
#if ange_DMA_WC
void ange_DMA_WC_USARTConfig(u32 y,u8 *m)//���赽�洢����8λ����
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC ���赽�洢�� DST �浽��
	dmainit.DMA_PeripheralBaseAddr=(u32)y;   //�����ַ
	dmainit.DMA_MemoryBaseAddr=(u32)m;   //�ڴ��ַ
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //dma���ݴ�����
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ������
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;  //�ڴ��ַ�Ƿ����
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;   //�������ݿ��
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //�ڴ����ݿ��
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;  //ѭ����������
	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma���ȼ� ����low medium high veryhigh
	dmainit.DMA_M2M=DMA_M2M_Disable;   //�洢�����洢��ʱѡ��
	DMA_Init(ange_DMA_WC_Channel,&dmainit);  //��ʼ����Ҫѡ��ͨ��
	DMA_Cmd(ange_DMA_WC_Channel,ENABLE);
}
void ange_DMA_WC_ADCConfig(u32 y,u16 *m)//���赽�洢����16λ����
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	DMA_DeInit(ange_DMA_WC_Channel);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC ���赽�洢�� DST �浽��
	dmainit.DMA_PeripheralBaseAddr=(u32)y;   //�����ַ
	dmainit.DMA_MemoryBaseAddr=(u32)m;   //�ڴ��ַ
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //dma���ݴ�����
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ������
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;  //�ڴ��ַ�Ƿ����
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;   //�������ݿ��
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;  //�ڴ����ݿ��
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;  //ѭ����������
	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma���ȼ� ����low medium high veryhigh
	dmainit.DMA_M2M=DMA_M2M_Disable;   //�洢�����洢��ʱѡ��
	DMA_Init(ange_DMA_WC_Channel,&dmainit);  //��ʼ��ʱҪѡ��ͨ��
	DMA_Cmd(ange_DMA_WC_Channel,ENABLE);
}
#endif
