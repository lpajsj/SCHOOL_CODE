#include "arm_math.h"
#include "stm32f10x.h"
#include "arm_const_structs.h"
#include "ange_usart.h"
#include "AD9910.h"
extern u8 _return;
extern uchar cfr2[4]; //cfr2������
extern uchar cfr1[4]; //cfr1������
int32_t main(void)
{
//	GPIO_PinRemapConfig()
	Init_ad9910();
//			cfr1[0] = 0x00;		 //RAM ʧ��
//			cfr2[1] = 0x00;		 //DRG ʧ��
//			Txcfr();			 //����cfrx������
//			Amp_convert(500);	//д����(��λmV)�����뷶Χ��1-650 mV
//			Freq_convert(1000); //дƵ��(��λHz)�����뷶Χ��1-400 000 000Hz
//			Amp_convert(500);			//д���ȣ����뷶Χ��1-650 mV
	Square_wave(272888); //����������ʱ�������뷶Χ��4*(1~65536)ns
			//ɨƵ������Ƶ�ʣ�����Ƶ�ʣ�Ƶ�ʲ�������λ��Hz��������ʱ��������λ��us��
//			SweepFre(100, 1000000, 50, 20000); //����ʱ�䷶Χ����4*(1~65536)ns
//	Sawtooth_wave(30214); //��ݲ�������ʱ�������뷶Χ��4*(1~65536)ns
    while (1);                           
	
}
