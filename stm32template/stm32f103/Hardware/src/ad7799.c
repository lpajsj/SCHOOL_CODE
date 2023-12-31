#include "ad7799.h"
#include "ange_systick.h"
#include "stdio.h"

#if Sofeware_SPI
void AD7799_GPIO_Init(void)//AD7799引脚初始化
{
	RCC_APB2PeriphClockCmd(AD_RCC,ENABLE);//开启GPIO的时钟
	
	GPIO_InitTypeDef AD7799_GPIO_InitStruction;
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//定义CS为推挽输出
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_CS_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_CS_GPIO,&AD7799_GPIO_InitStruction);
	
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//定义DI为推挽输出
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_DI_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_DI_GPIO,&AD7799_GPIO_InitStruction);
	
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//定义SCK为推挽输出
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_SCK_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_SCK_GPIO,&AD7799_GPIO_InitStruction);	

	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IN_FLOATING;//定义DO为悬空输入
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_DO_PIN;
	GPIO_Init(AD_SCK_GPIO,&AD7799_GPIO_InitStruction);	
}
/*****************************************************************************************************
作用：使AD7799的管脚处于默认状态
说明：使用AD7799前要将CS清零，DI置1
*****************************************************************************************************/
void spi_ad7799_init(void)
{
	AD_CS_0();
	AD_DI_1();
	AD_SCK_1();
	delayms_ad7799(10);
}
/*****************************************************************************************************
作用：向AD7799写数据
参数：*buf-要写入的数据数组，num-要写入的数据个数
说明：AD7799一次接收一字节，高电平采样数据，低电平要将数据稳定。且先发送高位
*****************************************************************************************************/
void AD7799_Write(uint8_t *buf,uint8_t num)
{
	uint8_t dat;
	uint8_t i,j;
	
	AD_SCK_1();
	__nop();
//	AD_CS_1();  在写数据中不需要对CS的操作
//	__nop();
//	AD_CS_0();
	__nop();
	
	for(j=0;j<num;j++)
	{
		dat=*(buf+j);
		for(i=0;i<8;i++)
		{
			AD_SCK_0();
			if(0x80 == (dat & 0x80))
			AD_DI_1();
			else
			AD_DI_0();
			__nop();
			AD_SCK_1();
			__nop();
			dat<<=1;
		}
	}
//	AD_CS_1();//关闭片选放在最后
}
/*****************************************************************************************************
作用：读AD7799数据
参数：*buf-读出数据的存放数组，num-要读的数据个数
说明：AD7799低电平输出数据，高电平稳定数据，先读取高位
*****************************************************************************************************/
void AD7799_Read(uint8_t *buf,uint8_t num)//读AD7799数据
{
	uint8_t dat=0,temp=0;
	
	uint8_t i,j;	
	
	AD_SCK_1();
	__nop();
//	AD_CS_1();
//	__nop();
//	AD_CS_0();	
	
	for(j=0;j<num;j++)
	{
		for(i=0;i<8;i++)
		{
			AD_SCK_0();
			dat<<=1;//注意左移放前面
			temp=AD_DO;
			if(temp==1)
				dat|=1;			
			AD_SCK_1();
			__nop();
		}
		*(buf+j)=dat;
	}
//	AD_CS_1();	
}
#endif
#if Hardware_SPI
void AD7799_GPIO_Init(void)
{
	AD7799_SPI_GPIO_APBxClock_FUN(AD7799_SPI_GPIO_CLK,ENABLE);//初始化SPI引脚的时钟	
	AD7799_SPI_APBxClock_FUN(RCC_APB1Periph_SPI2,ENABLE);//初始化SPI的时钟
	
/*-------------------GPIO初始化-----------------------------------------------*/		
	//32的SPI时钟，设置为复用推挽输出
	GPIO_InitTypeDef AD7799_GPIO_InitStructure;
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_SCK_PIN;
	AD7799_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD7799_SPI_SCK_PORT,&AD7799_GPIO_InitStructure);
	//32的SPI输出引脚（SOMI），设置为复用推挽输出
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_MOSI_PIN;
	AD7799_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD7799_SPI_MOSI_PORT,&AD7799_GPIO_InitStructure);	
	//32的SPI输入引脚（SOMO），设置为悬浮输入
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_MISO_PIN;
	GPIO_Init(AD7799_SPI_MISO_PORT,&AD7799_GPIO_InitStructure);	

	//初始化CS引脚，使用软件控制，所以直接设置成推挽输出
	AD7799_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	AD7799_GPIO_InitStructure.GPIO_Pin=AD7799_SPI_CS_PIN;
	GPIO_Init(AD7799_SPI_CS_PORT,&AD7799_GPIO_InitStructure);		

/*-------------------SPI初始化-----------------------------------------------*/		
	SPI_InitTypeDef  AD7799_SPI_InitStructure;
	AD7799_SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;//波特率的分频，这里的时钟为APB1，所有分频后时18M,这里最低4分频才可以
	AD7799_SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;//第二个边沿采样
	AD7799_SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;//空闲时SCK为高电平
	AD7799_SPI_InitStructure.SPI_CRCPolynomial=0;//不使用CRC功能，数值随便写
	AD7799_SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//数据位为8位
	AD7799_SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//双线全双工
	AD7799_SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//高位先行
	AD7799_SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//主模式
	AD7799_SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//CS位用软件控制
	SPI_Init(AD7799_SPIx,&AD7799_SPI_InitStructure);//写入配置到寄存器
	SPI_Cmd(AD7799_SPIx,ENABLE);//使能SPI
}
uint8_t AD7799_Data[3]={0};
uint8_t AD7799_SendData[3]={0};
void AD7799_DMA(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//开启DMA1的时钟
	/*-------------------接收DMA初始化-----------------------------------------------*/
	DMA_InitTypeDef ADC_DMA_InitStruction;
	ADC_DMA_InitStruction.DMA_BufferSize=3;//一次传输3个
	ADC_DMA_InitStruction.DMA_DIR=DMA_DIR_PeripheralSRC;//外设为源
	ADC_DMA_InitStruction.DMA_M2M=DMA_M2M_Disable;//关闭存储到存储
	ADC_DMA_InitStruction.DMA_MemoryBaseAddr=(uint32_t)AD7799_Data;//存储器的地址
	ADC_DMA_InitStruction.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;//8位
	ADC_DMA_InitStruction.DMA_MemoryInc=DMA_MemoryInc_Enable;//地址自增
	ADC_DMA_InitStruction.DMA_Mode=DMA_Mode_Circular;//开启循环发数
	ADC_DMA_InitStruction.DMA_PeripheralBaseAddr=(uint32_t)(&(SPI2->DR));//ADC数据地址
	ADC_DMA_InitStruction.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//8位
	ADC_DMA_InitStruction.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址自增
	ADC_DMA_InitStruction.DMA_Priority=DMA_Priority_High;//高优先级
	DMA_Init(DMA1_Channel4,&ADC_DMA_InitStruction);
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
	/*-------------------发送DMA初始化-----------------------------------------------*/
	ADC_DMA_InitStruction.DMA_BufferSize=3;//一次传输3个
	ADC_DMA_InitStruction.DMA_DIR=DMA_DIR_PeripheralDST;//外设为源
	ADC_DMA_InitStruction.DMA_M2M=DMA_M2M_Disable;//关闭存储到存储
	ADC_DMA_InitStruction.DMA_MemoryBaseAddr=(uint32_t)AD7799_SendData;//存储器的地址
	ADC_DMA_InitStruction.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;//8位
	ADC_DMA_InitStruction.DMA_MemoryInc=DMA_MemoryInc_Enable;//地址自增
	ADC_DMA_InitStruction.DMA_Mode=DMA_Mode_Circular;//开启循环发数
	ADC_DMA_InitStruction.DMA_PeripheralBaseAddr=(uint32_t)(&(SPI2->DR));//ADC数据地址
	ADC_DMA_InitStruction.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//8位
	ADC_DMA_InitStruction.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址自增
	ADC_DMA_InitStruction.DMA_Priority=DMA_Priority_High;//高优先级
	DMA_Init(DMA1_Channel5,&ADC_DMA_InitStruction);
	SPI_I2S_DMACmd(AD7799_SPIx,SPI_I2S_DMAReq_Tx|SPI_I2S_DMAReq_Rx,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);	
	
}
/*****************************************************************************************************
作用：向AD7799写数据
参数：*buf-要写入的数据数组，num-要写入的数据个数
说明：AD7799一次接收一字节，高电平采样数据，低电平要将数据稳定。且先发送高位
*****************************************************************************************************/
static u8 SPIByte(u8 byte)
{
	while(SPI_I2S_GetFlagStatus(AD7799_SPIx,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(AD7799_SPIx,byte);
	
	while(SPI_I2S_GetFlagStatus(AD7799_SPIx,SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(AD7799_SPIx);
}
void AD7799_Write(u8 * buffer,u8 num)
{
	int i=0;
	for(i=0;i<num;i++)
	SPIByte(buffer[i]);
}
/*****************************************************************************************************
作用：读AD7799数据
参数：*buf-读出数据的存放数组，num-要读的数据个数
说明：AD7799低电平输出数据，高电平稳定数据，先读取高位
*****************************************************************************************************/
void AD7799_Read(u8 * buffer,u8 size)
{
	int i=0;
	for(i=0;i<size;i++)
	buffer[i]=SPIByte(0x00);
}
#endif
/*****************************************************************************************************
作用：写AD7799寄存器
参数：regAddress-寄存器地址，regValue-写入的数据，size-写入的数据的字节数
说明：先AD7799写寄存器，首先要先写通信寄存器，写入通信寄存器的数据决定要写入的寄存器
*****************************************************************************************************/
void AD7799_SetRegisterValue(uint8_t regAddress,uint32_t regValue,uint8_t size)//写AD7799寄存器
{
	uint8_t data[5]={0};//30
	data[0]=data[0] = AD7799_COMM_WRITE |  AD7799_COMM_ADDR(regAddress);//通信寄存器的数据
	if(size==1)
	{
		data[1] = (uint8_t)regValue;
	}
	else if(size == 2)
	{
		data[1] = (uint8_t)((regValue&0x00ff00)>>8);
		data[2] = (uint8_t)(regValue&0x0000ff);
	}
	else
	{
		data[1] = (uint8_t)((regValue & 0xFF0000) >> 16);	
		data[2] = (uint8_t)((regValue & 0x00FF00) >> 8);
    data[3] = (uint8_t)((regValue & 0x0000FF) >> 0);    	
	}
	AD_CS_1();
	AD_CS_0();
	AD7799_Write(data,size+1);//因为要先写通信寄存器，所以写入的数据+1
	AD_CS_1();
}	
/*****************************************************************************************************
作用：读AD7799寄存器
参数：regAddress-寄存器地址，size-读取的数据的字节数
说明：读AD7799写寄存器，首先要先写通信寄存器，写入通信寄存器的数据决定要读取的寄存器
*****************************************************************************************************/
uint32_t AD7799_GetRegisterValue(uint8_t regAddress, uint8_t size)   //读AD7799寄存器
{
	uint8_t corresspond_data=0;//通信寄存器数据
	uint8_t data[4]={0};//读出的数据
	uint32_t receivedData = 0x00;//最后返回的数据
	corresspond_data = AD7799_COMM_READ |  AD7799_COMM_ADDR(regAddress);
	
	AD_CS_1();
	AD_CS_0();	
	AD7799_Write(&corresspond_data,1);//1.先写通信寄存器
	AD7799_Read(data,size);//2.读寄存器的值
	AD_CS_1();////////////////////////
	
	if(size == 1)
	{
		receivedData = data[0];
	}
	else if(size == 2)
	{
		receivedData |= (data[0] << 8);
		receivedData |= (data[1] << 0);
	}
	else
	{
		receivedData |= (data[0] << 16);
		receivedData |= (data[1] << 8);
		receivedData |= (data[2] << 0);
	}
	 return receivedData;
}
/*****************************************************************************************************
作用：读AD7799的ID
说明：AD7799的ID为0xx9
返回值：如果是0xx9，则返回success，否则返回ERROR
*****************************************************************************************************/
uint8_t AD7799_Init(void)//读AD7799的ID
{
	uint8_t status = 0x1;
	uint8_t ID;
	ID=AD7799_GetRegisterValue(AD7799_REG_ID,1);
	printf("%d\r\n",ID);
	if((ID&0x0f)!=AD7799_ID)
		status= 0x0;
	return status;
}
/*****************************************************************************************************
作用：复位AD7799
说明：发送32位的1复位AD7799
*****************************************************************************************************/
void AD7799_Reset(void)//复位AD7799
{
	uint8_t dataToSend[4] = {0xff, 0xff, 0xff, 0xff};
	AD_CS_1();
	AD_CS_0();		
	AD7799_Write(dataToSend,4);
	AD_CS_1();
}
/*****************************************************************************************************
作用：读状态寄存器中的RDY位
说明：如果RDY为1，则转换未完成，RDY为0，则转换完成
返回值：转换完成-1，转换未完成-0
*****************************************************************************************************/
uint8_t AD7799_Ready(void)//读状态寄存器中的RDY位
{
	uint8_t rdy = 0;
	rdy=(AD7799_GetRegisterValue( AD7799_REG_STAT,1) & 0x80);   
	return(!rdy);
}
/*****************************************************************************************************
作用：设置AD7799的模式
参数：mode-模式寄存器的MD2 MD1 MD0（13-15位），选择模式
*****************************************************************************************************/
void AD7799_SetMode(uint16_t mode)//设置AD7799的模式
{
	uint16_t command;
	command = AD7799_GetRegisterValue(AD7799_REG_MODE,2);//读取原先模式寄存器的数据
	command &= ~AD7799_MODE_SEL(0xFF);//将高13-15位清零，低位保持不变
	command |= AD7799_MODE_SEL(mode);//将高13-15位改为要写入的模式
  AD7799_SetRegisterValue(AD7799_REG_MODE, command,2);//写入模式寄存器	
}

/*****************************************************************************************************
作用：挑选AD7799的通道位
参数：channel-配置寄存器的HD2 HD1 HD0（0-2位）
*****************************************************************************************************/
void AD7799_SetChannel(uint16_t channel)//挑选AD7799的通道位
{
   uint16_t command;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//读取配置寄存器的两个字节的数据
    command &= ~AD7799_CONF_CHAN(0xFF);//将低0-2位清零，高位保持不变
    command |= AD7799_CONF_CHAN(channel);////将低0-2位改为要写入的通道
    AD7799_SetRegisterValue(AD7799_REG_CONF, command,2);//写入配置寄存器
}
/*****************************************************************************************************
作用：设置AD7799增益
参数：gain-配置寄存器的G2 G1 G0（8-10位）
说明：对应的放大倍数参考手册
*****************************************************************************************************/
void AD7799_SetGain(uint16_t gain)//设置AD7799增益
{
    uint16_t command;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//读取配置寄存器的两个字节的数据
    command &= ~AD7799_CONF_GAIN(0xFF);//将低8-10位（增益选择位）清零，高位保持不变
    command |= AD7799_CONF_GAIN(gain);//将低8-10位（增益选择位）改为要放大的增益
    AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);//写入配置寄存器 
}
/*****************************************************************************************************
作用：启动或禁用参考保护功能
参数：state-1-开启，state-0-关闭
说明：当参考电压断路或者小于0.5V时，状态寄存器的NOREF给出指示。
*****************************************************************************************************/
void AD7799_SetReference(uint16_t state)//启动或禁用参考保护功能
{
    uint16_t command = 0;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//读取配置寄存器的两个字节的数据
    command &= ~AD7799_CONF_REFDET(1);//将第5位（参考保护使能位）清零，其他位保持不变
    command |= AD7799_CONF_REFDET(state);//将第5位（参考保护使能位）改为开启或禁止状态
    AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);//写入配置寄存器			
}


/*****************************************************************************************************
作用：通道校准
参数：t-通道
说明：
*****************************************************************************************************/
void AD7799_Calibrate(u8 t)//通道校准
{
	u16 command,x;
	x=AD7799_GetRegisterValue(AD7799_REG_MODE,2);
	delayms_ad7799(5);////////////////////
	AD7799_SetChannel(t);
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(4);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);delayms_ad7799(5);//内部零刻度校验
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(5);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);delayms_ad7799(5);//内部满刻度校验
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(6);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);delayms_ad7799(5);//系统零刻度校验
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(7);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);delayms_ad7799(5);//系统满刻度校验
	AD7799_SetRegisterValue(AD7799_REG_IO,0,1);//设置通道3 为ad输入
}
/*****************************************************************************************************
作用：速度配置
参数：x-各速度的代码
*****************************************************************************************************/
void AD7799_Speed(u8 x) //16.7hz是10
{
	u16 command;
	command=AD7799_GetRegisterValue(AD7799_REG_MODE,2);
	command&=~AD7799_MODE_RATE(0xff);
	command|=AD7799_MODE_RATE(x);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
}
/*****************************************************************************************************
作用：连续读模式的相应代码
参数：x-各速度的代码
说明：开启连续读模式后，不能再给AD7799送数据，只能直接读数据
如需连续转换直接调用下函数完成初始化
AD7799_CReadMode(0)

转换通道用以下代码：
AD7799_CReadMode(0);
ad1=AD7799_CRead();

AD7799_CReadMode(1);
ad2=AD7799_CRead();
	
AD7799_CReadMode(2);
ad3=AD7799_CRead();
不转换直接读：
ad1=AD7799_CRead();
*****************************************************************************************************/
void AD7799_CReadMode(uint8_t CH)//启动连续读模式
{
	
	uint8_t corresspond_data=0;
	
	AD7799_REG_Init(CH);//因为进入了连续模式就退不出，所以干脆复位初始化
	
	AD_CS_1();
	AD_CS_0();	
	corresspond_data=0x5c;
	AD7799_Write(&corresspond_data,1);//连续读模式
}
uint8_t AD7799_Date[3]={0};
uint16_t AD7799_CRead(void)//连续读模式的读取AD7799
{
	uint8_t times=5;
	uint16_t ad=0;
	while(times--)
	{
		if(AD_DO==0)//如果D0脚为低电平则转换完成
		{
			AD7799_Read(AD7799_Date,3);//读取数据
			ad=AD7799_Date[0];
			ad=ad*256;//乘比左移快了0.03us
			ad+=AD7799_Date[1];
			return ad;
		}
		delayms_ad7799(59);
	}	
	return 0;
}
void AD7799_TUIRead(void)//退出连续读模式，但是不管用
{
	uint8_t corresspond_data=0x58;
	AD7799_Write(&corresspond_data,1);
}
/*****************************************************************************************************
作用：单次转换读模式的读取
参数：x-各速度的代码
*****************************************************************************************************/
uint32_t AD7799_SRead(void)//单次转换读模式的读取
{
	uint32_t times=5,ad=0;
	u16 command=0x200a;//16.7HZ,单次转换命名
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
	while(times--)
	{
		if(AD7799_Ready())
		{
			ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
			return ad;
		}
		delayms_ad7799(60);
	}	
	return 0;
}
/*****************************************************************************************************
作用：AD7799功能初始化
*****************************************************************************************************/
void AD7799_REG_Init(uint8_t CH) //配置寄存器开启烧毁电流 单双极性 缓冲模式
{
	u16 command=0;
		////psw置一，电源
#if Sofeware_SPI	
	spi_ad7799_init();	
#endif	
	AD7799_Reset();
	command|=AD7799_MODE_PSW;
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
	command=AD7799_GetRegisterValue(AD7799_REG_CONF,2);
	//单极性，缓冲保护
	command&=~(AD7799_CONF_UNIPOLAR(1)|AD7799_CONF_BUF);
	command|=(AD7799_CONF_UNIPOLAR(1)|AD7799_CONF_BUF);
	AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);
	//启动参考保护功能
	AD7799_SetReference(1);
	 //采集速度设置
	AD7799_Speed(10);
	 //AD7799增益设置
	AD7799_SetGain(AD7799_GAIN_1); 
	 //AD7799通道校准
	AD7799_Calibrate(0);
	AD7799_Calibrate(1);
	AD7799_Calibrate(2);   
	AD7799_SetChannel(CH);
	//模式设置，连续转换模式
	AD7799_SetMode(AD7799_MODE_CONT); 
}
/*****************************************************************************************************
作用：读取单次AD7799
返回值：16位的数据
*****************************************************************************************************/
uint32_t readad1(void)//单次读AD7799函数
{
	uint32_t times=10,ad=0;//五个周期读不出来就不读了
	while(times--)
	{
		if(AD7799_Ready())
		{
			ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
			ad=ad/256;
			return ad;
		}
		delayms_ad7799(60);//延时一个转换周期
	}
	AD7799_REG_Init(1);//当连续读不出来是就是卡死了，进行复位,只能解决一部分问题
	times=10;
	while(times--)//读不出来很有可能就卡死了，所以复位
	{
		if(AD7799_Ready())
		{
			ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
			ad=ad/256;
			return ad;
		}
		delayms_ad7799(60);
	}
	return 0;
}
/*****************************************************************************************************
作用：16次平均滤波程序
返回值：16位的数据
*****************************************************************************************************/
u16 readad16(void)//AD779916次滤波函数
{
	uint32_t times=1000,i=0,ad;
	u32 sum=0;
	for(i=0;i<16;i++)
	{
		times=1000;
		while(times--)
		{
			if(AD7799_Ready())
			{
				ad=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
				ad>>=8;
				times=0;
				sum+=ad;
			}
			else
			{
			}
			delayms_ad7799(1);
		}	
	}
	sum=sum/16;
	return sum;
}


/********************
fir 滤波
返回值即为滤波值
但在刚开始数据个数无法满足，可以用标志位fir_b判断,仅返回当前收到数据平均值
		AD7799_SetChannel(0);
		while(!AD7799_Ready());
		AD=AD7799_GetRegisterValue(AD7799_REG_DATA,3);
		AD7799_ProcessValue=fir_lvbo(AD,1);
		if(fir_b1==1)	
		{
			printf("通道1：%lf  \n",AD7799_ProcessValue*5/16777215);
		} 
*****************/
#define fir_cishu 10
double fir_jilu1[fir_cishu];//1通道数据的数组
u8 fir_jishu1=0;//1通道的数据
u8 fir_b1=0;//1通道完成FIR滤波的标志
/////////
double fir_jilu2[fir_cishu];//2通道数据的数组
u8 fir_jishu2=0;//2通道的数据
u8 fir_b2=0;//2通道完成FIR滤波的标志
///////
double fir_jilu3[fir_cishu];//3通道数据的数组
u8 fir_jishu3=0;//3通道的数据
u8 fir_b3=0;//3通道完成FIR滤波的标志

double fir_lvbo(uint32_t x,u8 t)
{
	u8 i;
	double sum=0;
	if(t==1)  //通道1的FIR滤波
	{
		fir_jilu1[fir_jishu1]=x;//数据数组赋值
		fir_jishu1++;//次数加加
		if(fir_jishu1==fir_cishu)//如果次数为10，置位标志
		{
			fir_jishu1=0;
			fir_b1=1;
		}
		if(fir_b1==1)//如果次数超过10
		{
			for(i=0;i<fir_cishu;i++)
			{
				sum+=fir_jilu1[i];
			}
			return sum/fir_cishu;//输出FIR滤波后的值
		}
		else
		{
			for(i=0;i<fir_jishu1;i++)
			{
				sum+=fir_jilu1[i];
			}
			return sum/fir_jishu1;//输出FIR滤波前的值
		}
  }
	else if(t==2)
	{
		fir_jilu2[fir_jishu2]=x;
		fir_jishu2++;
		if(fir_jishu2==fir_cishu)
		{
			fir_jishu2=0;
			fir_b2=1;
		}
		if(fir_b2==1)
		{
			for(i=0;i<fir_cishu;i++)
			{
				sum+=fir_jilu2[i];
			}
			return sum/fir_cishu;
		}
		else
		{
			for(i=0;i<fir_jishu2;i++)
			{
				sum+=fir_jilu2[i];
			}
			return sum/fir_jishu2;
		}
  }
	else
	{
		fir_jilu3[fir_jishu3]=x;
		fir_jishu3++;
		if(fir_jishu3==fir_cishu)
		{
			fir_jishu3=0;
			fir_b3=1;
		}
		if(fir_b3==1)
		{
			for(i=0;i<fir_cishu;i++)
			{
				sum+=fir_jilu3[i];
			}
			return sum/fir_cishu;
		}
		else
		{
			for(i=0;i<fir_jishu3;i++)
			{
				sum+=fir_jilu3[i];
			}
			return sum/fir_jishu3;
		}
  }
}
/******************
iir滤波 返回值就是滤波结果
****************/
double iir_jilu;
u8 iir_b=0;
double iir_lvbo(double x)
{
	if(iir_b==0)
	{
		iir_b=1;
	  iir_jilu=x;
		return x;
	}
	else
	{
		iir_jilu=iir_jilu/2+x/2;
		return iir_jilu;
	}
}
/*******************
平均滤波+fir 使用时
average_fir_lvbo(x);
if(average_fir_fb)
{
average_fir_fb=0;
//取值
y=average_fir_zhi;
}
*********************/
#define average_fir_acishu 16  //平均次数
#define average_fir_fcishu 4  //fir次数
double average_fir_asum=0;    //平均和变量
double average_fir_fjilu[average_fir_fcishu]; //每次的平均值记录，作为fir滤波的值
u8 average_fir_ab=0;  //第一次数据个数达到标志
u16 average_fir_ajishu=0; ///平均次数计数
u8 average_fir_fb=0;   //fir次数达到标志、、作为最终判断标志
u16 average_fir_fjishu=0; //fir次数计数
double average_fir_zhi;  //最终fir值
void average_fir_lvbo(double x)
{
	u8 i;
	double sum=0;
	average_fir_asum+=x; //平均值求和
	average_fir_ajishu++; //平均计数加一
	if(average_fir_ab==0)
	{
		if(average_fir_ajishu==average_fir_acishu) //到达平均次数
		{
			average_fir_ajishu=0;  //平均计数清零
			average_fir_fjilu[average_fir_fjishu]=average_fir_asum/average_fir_acishu; //求平均值记录
			average_fir_fjishu++;  //fir数据计数+1  
			average_fir_asum=0;   //平均和清零
			if(average_fir_fjishu==average_fir_fcishu)  //到达fir数据个数
			{
				average_fir_fjishu=0;   //fir数据清零
				for(i=0;i<average_fir_fcishu;i++)
				{
					sum+=average_fir_fjilu[i];   //求fir数据之和
				}
				average_fir_zhi=sum/average_fir_fcishu;  //求得最终数据
				average_fir_fb=1;  //置一最终数据更新标志位
				average_fir_ab=1;
			}
		}
  }
	else if(average_fir_ab==1)
	{
		if(average_fir_ajishu==average_fir_acishu) //到达平均次数
		{
			average_fir_ajishu=0;  //平均计数清零
			average_fir_fjilu[average_fir_fjishu]=average_fir_asum/average_fir_acishu; //求平均值记录
			average_fir_fjishu++;  //fir数据计数+1  
			average_fir_asum=0;   //平均和清零
			if(average_fir_fjishu==average_fir_fcishu)  //到达fir数据个数
			{
				average_fir_fjishu=0;   //fir数据清零
			}
			for(i=0;i<average_fir_fcishu;i++)
			{
				sum+=average_fir_fjilu[i];   //求fir数据之和
			}
			average_fir_zhi=sum/average_fir_fcishu;  //求得最终数据
			average_fir_fb=1;  //置一最终数据更新标志位
		}
	}
}
/**************************************************************************************
作用：无滤波
参数：*AD-获取的AD7799的值
说明：使用double可以精确到小数点后15位，电压范围为0-5V
***************************************************************************************/
void Non_Filter(uint32_t *AD)//无滤波
{
	static double ADD_AD=0;
	ADD_AD=*AD;
	ADD_AD=ADD_AD*5/16777215;
	printf("无滤波%.16f\n",ADD_AD);
}
/*****************************************************************************************************
作用：四次平均滤波
参数：*AD-获取的AD7799的值
说明：使用double可以精确到小数点后15位，电压范围为0-5V
*****************************************************************************************************/
void Average_Filter(uint32_t *AD)//四次平均滤波
{
	static uint8_t times=0;
	static double ADD_AD=0;
	times++;
	ADD_AD=ADD_AD+(*AD);
	if(times==4)
	{
		times=0;
		ADD_AD=ADD_AD*5/16777215/4;
		printf("平均滤波%.16f\n",ADD_AD);
		ADD_AD=0;
	}
}
/**************************************************************************************
作用：FIR十阶滤波
参数：*AD-获取的AD7799的值
说明：使用double可以精确到小数点后15位，电压范围为0-5V
FIRFilter_Flag 第一次的十个数据不处理，第11个数据开始处理的标志位
FIR_times 接收次数
两个参数在退出FIR滤波后记得清零
***************************************************************************************/
FunctionalState FIRFilter_Flag=DISABLE;
uint8_t FIR_times=0;
void FIR_Filter(uint32_t *AD)//FIR十阶滤波
{
	
	static uint32_t FIR_Buf[10]={0};
	static double ADD_AD=0;
	
	FIR_Buf[FIR_times]=*AD;
	FIR_times++;
	
	if((FIR_times==10)&&(FIRFilter_Flag==DISABLE))
	{
		FIR_times=0;
		FIRFilter_Flag=ENABLE;
	}
	else if(FIRFilter_Flag==ENABLE)
	{
		ADD_AD=FIR_Buf[0]+FIR_Buf[1]+FIR_Buf[2]+FIR_Buf[3]+FIR_Buf[4]+FIR_Buf[5]+FIR_Buf[6]+FIR_Buf[7]+FIR_Buf[8]+FIR_Buf[9];
		ADD_AD=ADD_AD*5/16777215/10;
		printf("FIR滤波%.16f\n",ADD_AD);
		if(FIR_times==10)
			FIR_times=0;
	}
}
/**************************************************************************************
作用：IIR二阶滤波
参数：*AD-获取的AD7799的值
说明：使用double可以精确到小数点后15位，电压范围为0-5V
IIR_ADD_AD 读取的转换值之和
IIR_times 接收次数
两个参数在退出IIR滤波后记得清零
***************************************************************************************/
double IIR_ADD_AD=0;
uint8_t IIR_times=0;
void IIR_Filter(uint32_t *AD)//IIR二阶滤波
{
	static double ADToVolitage=0;
	if(IIR_times<2)
	{
		IIR_times++;
		IIR_ADD_AD=IIR_ADD_AD+(*AD);
	}
	else if(IIR_times==2)
	{
		IIR_times++;
		IIR_ADD_AD=IIR_ADD_AD/2;
		IIR_ADD_AD=(IIR_ADD_AD+(*AD))/2; //??????
		ADToVolitage=IIR_ADD_AD*5/16777215;
		printf("IIR滤波：%.16f\n",ADToVolitage);
	}
	else
	{
		IIR_ADD_AD=(IIR_ADD_AD+(*AD))/2;
		ADToVolitage=IIR_ADD_AD*5/16777215;
		printf("IIR滤波：%.16f\n",ADToVolitage);
	}
	
}
