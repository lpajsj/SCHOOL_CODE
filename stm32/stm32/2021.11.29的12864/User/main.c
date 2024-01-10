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
#include "ange_rcc.h"
#include "OLED12864.h"
u8 x1=16,y1=16,len=4,size=16,mode=1;
u32 num=1234;

int32_t main(void)
{
	OLED_Init();			         //��ʼ��OLED  
	OLED_Clear(0);             //������ȫ�ڣ�
	while(1) 
	{	
//		GUI_ShowString(0,y1,"123456789123456g",size,1);
//		GUI_ShowString(0,0,"123456789123456789123",8,1);
//		GUI_DrawBMP(0,0,128,64,gImage_123,1);
		GUI_ShowCHinese(0,0,24,"ȫ�����Ӽ���",0);
		SysTick_delayms(100);
//		GUI_ShowString(0,0,"00112233445566778899aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",8,1);
//		TEST_MainPage();         //��������ʾ����
//		OLED_Clear(0); 
//		Test_Color();            //ˢ������
//		OLED_Clear(0); 
//		Test_Rectangular();      //���λ��Ʋ���
//		OLED_Clear(0); 
//		Test_Circle();           //Բ�λ��Ʋ���
//		OLED_Clear(0); 
//		Test_Triangle();         //�����λ��Ʋ���
//		OLED_Clear(0);  
//		TEST_English();          //Ӣ����ʾ����
//		OLED_Clear(0); 
//		TEST_Number_Character(); //���ֺͷ�����ʾ����
//		OLED_Clear(0); 
//		TEST_Chinese();          //������ʾ����
//		OLED_Clear(0); 
//		TEST_BMP();              //BMP��ɫͼƬ��ʾ����
//		OLED_Clear(0); 
//		TEST_Menu1();            //�˵�1��ʾ����
//		OLED_Clear(0); 
//		TEST_Menu2();            //�˵�2��ʾ����
//		OLED_Clear(0); 
	}
}



