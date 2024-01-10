#ifndef __OLED12864_H
#define __OLED12864_H
//--------------OLED参数定义---------------------在头文件中定义数组不能被包含两次
#include "stm32f10x.h"
#define delayms_OLED12864 SysTick_delayms
#define PAGE_SIZE    8
#define XLevelL		0x00
#define XLevelH		0x10
#define YLevel       0xB0
#define	Brightness	 0xFF 
#define WIDTH 	     128
#define HEIGHT 	     64	

//-------------写命令和数据定义-------------------
#define OLED_CMD     0	//写命令
#define OLED_DATA    1	//写数据 
   						  
//-----------------OLED端口定义----------------
#define OLED_CS   GPIO_Pin_11   //片选信号           PB11
#define OLED_DC   GPIO_Pin_10   //数据/命令控制信号  PB10
#define OLED_RST  GPIO_Pin_12   //复位信号           PB12

//-----------------OLED端口操作定义---------------- 
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,OLED_CS)
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,OLED_CS)

#define OLED_DC_Clr()  GPIO_ResetBits(GPIOB,OLED_DC)
#define OLED_DC_Set()  GPIO_SetBits(GPIOB,OLED_DC)
 					   
#define OLED_RST_Clr()  GPIO_ResetBits(GPIOB,OLED_RST)
#define OLED_RST_Set()  GPIO_SetBits(GPIOB,OLED_RST)
						 

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);     //写命令或者数据
void OLED_Set_Pos(unsigned char x, unsigned char y);  //定位坐标
void OLED_Display_On(void);                           //开显示
void OLED_Display_Off(void);                           //关闭显示 //
void OLED_Reset(void);                                //OLED复位
void OLED_Init_GPIO(void);	   							   		    //
void OLED_Init(void);
void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color);  //改变显示数组的值
void OLED_Display(void);                                  //将数组值显示
void OLED_Clear(unsigned dat);                   //清除显示



void GUI_DrawPoint(u8 x, u8 y, u8 color);       //画点
void GUI_Fill(u8 sx,u8 sy,u8 ex,u8 ey,u8 color);  //填充
void GUI_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2,u8 color); //划线
void GUI_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color); //画方块
void GUI_FillRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color);  //实心方块
void GUI_DrawCircle(u8 xc, u8 yc, u8 color, u8 r);          //圆
void GUI_FillCircle(u8 xc, u8 yc, u8 color, u8 r);         //实心圆
void GUI_DrawTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color);  //三角形
void GUI_FillTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color);  //实心三角形

void GUI_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 mode);        //字符显示
void GUI_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 Size,u8 mode);    //显示数字
void GUI_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size,u8 mode);  //字符串显示
void GUI_ShowFont16(u8 x,u8 y,u8 *s,u8 mode);           
void GUI_ShowFont24(u8 x,u8 y,u8 *s,u8 mode);
void GUI_ShowFont32(u8 x,u8 y,u8 *s,u8 mode);
void GUI_ShowCHinese(u8 x,u8 y,u8 hsize,u8 *str,u8 mode);
void GUI_DrawBMP(u8 x,u8 y,u8 width, u8 height, u8 BMP[], u8 mode); 




void TEST_MainPage(void);
void Test_Color(void);
void Test_Rectangular(void);
void Test_Circle(void);
void Test_Triangle(void);
void TEST_English(void);
void TEST_Number_Character(void);
void TEST_Chinese(void);
void TEST_BMP(void);
void TEST_Menu1(void);
void TEST_Menu2(void);
extern  unsigned char gImage_123[1024];
#endif


