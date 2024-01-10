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
	OLED_Init();			         //初始化OLED  
	OLED_Clear(0);             //清屏（全黑）
	while(1) 
	{	
//		GUI_ShowString(0,y1,"123456789123456g",size,1);
//		GUI_ShowString(0,0,"123456789123456789123",8,1);
//		GUI_DrawBMP(0,0,128,64,gImage_123,1);
		GUI_ShowCHinese(0,0,24,"全动电子技术",0);
		SysTick_delayms(100);
//		GUI_ShowString(0,0,"00112233445566778899aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",8,1);
//		TEST_MainPage();         //主界面显示测试
//		OLED_Clear(0); 
//		Test_Color();            //刷屏测试
//		OLED_Clear(0); 
//		Test_Rectangular();      //矩形绘制测试
//		OLED_Clear(0); 
//		Test_Circle();           //圆形绘制测试
//		OLED_Clear(0); 
//		Test_Triangle();         //三角形绘制测试
//		OLED_Clear(0);  
//		TEST_English();          //英文显示测试
//		OLED_Clear(0); 
//		TEST_Number_Character(); //数字和符号显示测试
//		OLED_Clear(0); 
//		TEST_Chinese();          //中文显示测试
//		OLED_Clear(0); 
//		TEST_BMP();              //BMP单色图片显示测试
//		OLED_Clear(0); 
//		TEST_Menu1();            //菜单1显示测试
//		OLED_Clear(0); 
//		TEST_Menu2();            //菜单2显示测试
//		OLED_Clear(0); 
	}
}



