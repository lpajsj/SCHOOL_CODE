#include "AD5410.H"
/***************************************************************************************
适用单片机：STM32C8T6
经测试以及能够输出0-20mV的电流，最高方波频率可达16KHz，4V幅度。
注意事项：芯片得一次传输为多少为就写多少位，不然可能会出问题
*****************************************************************************************/
void AD5410_GPIO_Init(void)//AD5410的引脚初始化
{
	RCC_APB2PeriphClockCmd(AD5410_RCC,ENABLE);
	
	GPIO_InitTypeDef AD5410_GPIO_InitStruction;
	AD5410_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//设置AD5410数据锁存脚为推挽输出
	AD5410_GPIO_InitStruction.GPIO_Pin=AD5410_LATCH_PIN;
	AD5410_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD5410_LATCH_GPIO,&AD5410_GPIO_InitStruction);
	
	AD5410_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//设置AD5410时钟脚为推挽输出
	AD5410_GPIO_InitStruction.GPIO_Pin=AD5410_SCLK_PIN;
	AD5410_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD5410_SCLK_GPIO,&AD5410_GPIO_InitStruction);	
	
	AD5410_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//设置AD5410输入脚为推挽输出
	AD5410_GPIO_InitStruction.GPIO_Pin=AD5410_SDI_PIN;
	AD5410_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD5410_SDI_GPIO,&AD5410_GPIO_InitStruction);	

	AD5410_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IN_FLOATING;//设置AD5410输出脚为悬浮输入
	AD5410_GPIO_InitStruction.GPIO_Pin=AD5410_SDO_PIN;
	GPIO_Init(AD5410_SDO_GPIO,&AD5410_GPIO_InitStruction);		
	
	AD5410_LATCH_0;
	AD5410_SCLK_0;
}
//读取单个字节数据，先读高位，下升沿后读取数据
static uint32_t AD5410_ReadByte()
{
	uint32_t dat=0,i,temp;
	AD5410_LATCH_0;
	for(i=0;i<24;i++)
	{
		dat<<=1;
		AD5410_SCLK_0;
		
		AD5410_SDI_0;
		
		temp=READ_AD5410;
		if(temp==1)
			dat|=1;
		AD5410_SCLK_1;
		AD5410_SCLK_0;
	}
	AD5410_LATCH_1;
	AD5410_LATCH_0;	
	return dat;
}
/*********************************************************************************
功能：写操作
参数：date-要写的地址和数据，24位
说明：上升沿前将数据稳定，先送高位
无操作-0x00
数据寄存器-0x01
回读操作-0x02
控制寄存器-0x55
复位寄存器-0x56
*********************************************************************************/
void AD5410_SendDate(uint32_t date)//写操作
{
	uint8_t i;
	AD5410_LATCH_0;
	for(i=0;i<24;i++)
	{
		AD5410_SCLK_0;
		if((date&0x800000)==0x800000)
		{AD5410_SDI_1;}
		else
		{AD5410_SDI_0;}		
		AD5410_SCLK_1;
		date<<=1;	
		AD5410_SCLK_0;
	}
	AD5410_LATCH_1;
	AD5410_LATCH_0;
}
/*********************************************************************************
功能：回读操作
参数：addr-回读地址
0x020000-读取状态寄存器
0x020001-读取数据寄存器
0x020010-读取控制寄存器
*********************************************************************************/
uint32_t AD5410_ReadDate(uint32_t addr)//回读操作
{
	uint32_t AD5410_DATA;
	AD5410_SendDate(addr);
	AD5410_DATA=AD5410_ReadByte();
	return AD5410_DATA;

}

/*********************************************************************************
功能：AD5410初始化,开启输出，设置电流范围,频率
参数：Electric-电流大小
测试：打开外部电流设置电阻就输出不了电流。如果不需要那么大的压摆率的话，可以打开
压摆率控制使能，个人觉得没必要。打开压摆率理论最大512HZ，但只达到了480+Hz。
*********************************************************************************/
void AD5410_Init(void)//AD5410初始化
{
	AD5410_SendDate(0x560001);//复位AD5410
	AD5410_SendDate(0x551006);//关闭外部电流设置电阻,开启输出,时钟257730HZ,1/16步进,关闭数字压摆率控制,关闭菊花链,0-20mA电流
	AD5410_SendDate(0x018000);
}


