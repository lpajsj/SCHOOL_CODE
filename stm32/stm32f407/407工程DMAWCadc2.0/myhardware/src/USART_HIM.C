#include "USART_HIM.H"
/***********************************************************************************************************
使用到的引脚：PB12-15

************************************************************************************************************/
void Key_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(Key1_GPIO_RCC,ENABLE);
	GPIO_InitTypeDef Key_GPIO_InitStruction;
	Key_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IPD;
	Key_GPIO_InitStruction.GPIO_Pin=Key1_GPIO_Pin;
	GPIO_Init(Key1_GPIO_PORT,&Key_GPIO_InitStruction);
	
	RCC_APB2PeriphClockCmd(Key2_GPIO_RCC,ENABLE);
	Key_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IPD;
	Key_GPIO_InitStruction.GPIO_Pin=Key2_GPIO_Pin;
	GPIO_Init(Key2_GPIO_PORT,&Key_GPIO_InitStruction);	
	
	RCC_APB2PeriphClockCmd(Key3_GPIO_RCC,ENABLE);
	Key_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IPD;
	Key_GPIO_InitStruction.GPIO_Pin=Key3_GPIO_Pin;
	GPIO_Init(Key3_GPIO_PORT,&Key_GPIO_InitStruction);	

	RCC_APB2PeriphClockCmd(Key4_GPIO_RCC,ENABLE);
	Key_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IPD;
	Key_GPIO_InitStruction.GPIO_Pin=Key4_GPIO_Pin;
	GPIO_Init(Key4_GPIO_PORT,&Key_GPIO_InitStruction);		
}

/*************************************************************************************
作用：键盘扫描
返回值：每个键对应的值1-4
*************************************************************************************/
FunctionalState KeyScanFlag=ENABLE;//键盘扫描
uint8_t KeyScan(void)
{
	if((READ_KEY1==1)||(READ_KEY2==1)||(READ_KEY3==1)||(READ_KEY4==1))
	{
		if(KeyScanFlag==ENABLE)
		{
			if(READ_KEY1==1)
			{KeyScanFlag=DISABLE;return 1;}
			else if(READ_KEY2==1)
			{KeyScanFlag=DISABLE;return 2;}				
			else if(READ_KEY3==1)
			{KeyScanFlag=DISABLE;return 3;}					
			else if(READ_KEY4==1)
			{KeyScanFlag=DISABLE;return 4;}					
			else
				return 0;
		}
		else
			return 0;
	}
	else
	{
		KeyScanFlag=ENABLE;
		return 0;
	}
	
}
/*************************************************************************************
作用：绘制曲线
参数：id-曲线id，CH-曲线通道，*buf-曲线数据，Times-发送几个数据
说明：id为1，CH可以从0-2
Draw_Curve(1,0,Curve_Data,255);
*************************************************************************************/
uint8_t Curve_Data[255]={127,133,139,145,151,157,163,169,175,181,186,192,197,202,207,212,216,221,225,229,
												232,235,239,241,244,246,248,250,251,252,253,253,253,253,253,252,251,250,248,246,
												244,241,239,235,232,229,225,221,216,212,207,202,197,192,186,181,175,169,163,157,
												151,145,139,133,127,120,114,108,102,96,90,84,78,72,67,61,56,51,46,41,37,32,28,
												24,21,18,14,12,9,7,5,3,2,1,0,0,0,0,0,1,2,3,5,7,9,12,14,18,21,24,28,32,37,41,46,
												51,56,61,67,72,78,84,90,96,102,108,114,120,127,133,139,145,151,157,163,169,175,
												181,186,192,197,202,207,212,216,221,225,229,232,235,239,241,244,246,248,250,251,
												252,253,253,253,253,253,252,251,250,248,246,244,241,239,235,232,229,225,221,216,
												212,207,202,197,192,186,181,175,169,163,157,151,145,139,133,127,120,114,108,102,
												96,90,84,78,72,67,61,56,51,46,41,37,32,28,24,21,18,14,12,9,7,5,3,2,1,0,0,0,0,0,
												1,2,3,5,7,9,12,14,18,21,24,28,32,37,41,46,51,56,61,67,72,78,84,90,96,102,108,114};

void Draw_Curve(uint8_t id,uint8_t CH,uint8_t *buf,uint8_t Times)//绘制曲线
{
	uint8_t i;
	for(i=0;i<Times;i++)
	{
		ToSendOrder("add %d,%d,%d",id,CH,buf[i]);
	}
}
/*************************************************************************************
作用：发送文本
参数：t[]-要改变的文本的名称，test[]-文本
说明：Send_Text("tm","付志捷");
*************************************************************************************/
void Send_Text(char t[],char test[])//发送文本
{
		ToSendOrder("%s.txt=\"%s\"",t,test);
}
/*************************************************************************************
作用：发送整数
参数：t[]-要改变的文本的名称，number-整数
说明：Send_Text("tm",520);
*************************************************************************************/
void Send_Number(char t[],uint32_t number)//发送整数
{
		ToSendOrder("%s.txt=\"%d\"",t,number);
}
/*************************************************************************************
作用：发送小数
参数：t[]-要改变的文本的名称，Decimal-小数
说明：Send_Text("tm",520.520);
*************************************************************************************/
void Send_Decimal(char t[],double number)//发送小数
{
		ToSendOrder("%s.txt=\"%lf\"",t,number);
}
/*************************************************************************************
作用：改变颜色
参数：t[]-要改变的文本的名称，Colour-颜色代码
说明：Send_Text("bj",63348);
*************************************************************************************/
void Send_Colour(char t[],uint16_t Colour)//改变颜色
{
		ToSendOrder("%s.bco=%d",t,Colour);
}
