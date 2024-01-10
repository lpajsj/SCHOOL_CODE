#include "chuankouping.h"
#include "stm32f10x.h"
#include "stdio.h"
#include "ange_usart.h"
#include "ange_systick.h"
#define USARTx USART2
///
/// ckpqx(1,0,100);
void ckpqx(u8 id,u8 t,u8 s) //串口屏曲线参数分别是 ID 通道 数据0-255
{
	char fs[20];
	sprintf(fs,"add %d,%d,%d",id,t,s);
	printf("%s",fs);
	ckpjieshu();
}
//串口屏发送字符串如发送 page y2
//ckpfasong("page y2") 
void ckpfasong(char x[]) 
{
	printf("%s",x);
	ckpjieshu();
}
//控件赋值 如赋值t0的txt文本     输入字符
//ckpxianshis("t0.txt","实验室") 也就是t0.txt="实验室"
//即让t0显示实验室
void ckpxianshis(char obj[],char shuju[])
{
	char fs[30];
		sprintf(fs,"%s=\"%s\"",obj,shuju);
	  printf("%s",fs);
	ckpjieshu();
}
//控件赋值 如赋值t0的txt文本，   可输入整数
//ckpxianshids("t0.txt",123) 也就是t0.txt="123"
//即让t0显示123
void ckpxianshids(char obj[],u32 shuju)
{
	char fs[30];
		sprintf(fs,"%s=\"%d\"",obj,shuju);
	  printf("%s",fs);
		ckpjieshu();
}
//控件赋值 输入整数 如改变控件颜色   输入数字
//ckpxianshid("bj.bc0",63488) 也就是bj.bco=63488
//即让t0显示123
void ckpxianshid(char obj[],u32 shuju)
{
	char fs[30];
		sprintf(fs,"%s=%d",obj,shuju);
	  printf("%s",fs);
		ckpjieshu();
}
//文本显示如t1显示33.333333    可输入小数
//ckpxianshifs(t1.txt,33.333333)   显示小数
//即让t1显示33.333333
void ckpxianshifs(char obj[],double shuju)
{
	char fs[30];
		sprintf(fs,"%s=\"%.6f\"",obj,shuju);
	  printf("%s",fs);
		ckpjieshu();
}
void ckpjieshu(void)
{
	USART_SendData(USARTx,0xff);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
	USART_SendData(USARTx,0xff);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
	USART_SendData(USARTx,0xff);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==0); //RESET
}
//void baudtz(u32 x) //调整串口屏波特率为当前程序波特率
//{
//		USART_Cmd(ange_USARTx,DISABLE);
//	ange_USART_init(9600);
//	ckpxianshid("baud",x);//若要立马调整波特率要加延时
//   SysTick_delayms(1);  ///////////延时一定要加上不然会少一个0xff，
//	USART_Cmd(ange_USARTx,DISABLE);
//	ange_USART_init(x);
//}

