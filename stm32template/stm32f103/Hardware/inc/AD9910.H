/*-----------------------------------------------
  ���ƣ�AD9854��������
  ��д��Liu
  ���ڣ�2014.3
  �޸ģ���
  ���ݣ�
------------------------------------------------*/
#ifndef __AD9910_H__
#define __AD9910_H__

#include "stm32f10x.h"
#define delayms_AD9910 SysTick_delayms

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long int

//����IO
//#define SDO PAout(4)
//#define PDCLK PCout(6)//PDCLK
//#define PLL_LOCK PCout(7)//����
//#define SYNC_CLK PCout(9)//����
//#define TXENABLE PCout(11)//TXEN
//#define RSO PCout(12)//RAM-SWP-OVR
#define AD9910_PWR PBout(9) //0
#define AD9910_SDIO PDout(0)
#define DRHOLD PCout(12)
#define DROVER PDout(1)
#define UP_DAT PDout(3)
#define PROFILE1 PBout(3)
#define MAS_REST PBout(8) 
#define SCLK PAout(12)     
#define DRCTL PDout(2)    
#define OSK PDout(4)
#define PROFILE0 PDout(5)
#define PROFILE2 PDout(7)
#define CS PAout(9) 

//void Init_AD9910(void);  //INIT 9910
//void AD9910WriteByte (unsigned char commond, unsigned char *databyte,unsigned char lengh);
void AD9110_IOInit(void);
void Init_ad9910(void);
void Freq_convert(ulong Freq);            //дƵ��
void Amp_convert(unsigned int Amplitude); //д����
void Txcfr(void);
void Txramprofile(void);
void Txramdata(int wave_num);
void Square_wave(uint Sample_interval);                                                   //����;
void Sawtooth_wave(uint Sample_interval);                                                 //���ǲ�
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime); //ɨƵ

#endif
#if 0
#include "stm32_config.h"
#include "stdio.h"
//#include "led.h"
//#include "lcd.h"
#include "key.h"
#include "AD9910.h"
//#include "task_manage.h"
//#include "timer.h"

char str[30]; //��ʾ����
extern u8 _return;

extern uchar cfr2[4]; //cfr2������
extern uchar cfr1[4]; //cfr1������

int main(void)
{
	//	u16 i=0;

	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //�����жϷ���
	delay_init(72);										//��ʼ����ʱ����
	delay_ms(300);
	Init_ad9910();

//	while(1)
//	{
//		KeyRead(); //��ȡ����ֵ ���ڲ���ע���꣬���ùܣ�
//				   //		Set_PointFre(Keycode, 0);//��������
//				   //		if(_return){_return=0;LCD_Refresh_Gram();}//������ʾ

//		if (PBin(11) == 0) //��Ƶ����
//		{
//			cfr1[0] = 0x00;		 //RAM ʧ��
//			cfr2[1] = 0x00;		 //DRG ʧ��
//			Txcfr();			 //����cfrx������
//			Amp_convert(500);	//д����(��λmV)�����뷶Χ��1-650 mV
//			Freq_convert(1000); //дƵ��(��λHz)�����뷶Χ��1-400 000 000Hz
//		}

//		if (PBin(15) == 0) //ɨƵ
//		{
//			Amp_convert(500);			//д���ȣ����뷶Χ��1-650 mV
//			//ɨƵ������Ƶ�ʣ�����Ƶ�ʣ�Ƶ�ʲ�������λ��Hz��������ʱ��������λ��us��
//			SweepFre(100, 1000000, 50, 2000000); //����ʱ�䷶Χ����4*(1~65536)ns
//			delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(200);
//			cfr2[1] = 0x00;
//			Txcfr(); 
//			delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(200);
//			cfr2[1] = 0x0e; //DRG ʹ��
//			Txcfr();
//		}

//		if (PBin(14) == 0) //RAM����
//		{
			Square_wave(2621440); //����������ʱ�������뷶Χ��4*(1~65536)ns
//		}

//		if (PBin(13) == 0) //RAM��ݲ�
//		{
//			Sawtooth_wave(2621440); //��ݲ�������ʱ�������뷶Χ��4*(1~65536)ns
//		}

//		KEY_EXIT();
//	}



//	Amp_convert(500);			//д���ȣ����뷶Χ��1-650 mV
//	//ɨƵ������Ƶ�ʣ�����Ƶ�ʣ�Ƶ�ʲ�������λ��Hz��������ʱ��������λ��us��
//	SweepFre(100, 3000000, 300, 200000); //����ʱ�䷶Χ����4*(1~65536)ns

	while(1)
	{
		
//		delay_ms(1000);delay_ms(1000);
//		cfr2[1] = 0x00;
//		Txcfr(); 
//		
//		
//		delay_ms(1000);delay_ms(1000);
//		cfr2[1] = 0x0e; //DRG ʹ��
//		Txcfr();	
	}
}




#endif