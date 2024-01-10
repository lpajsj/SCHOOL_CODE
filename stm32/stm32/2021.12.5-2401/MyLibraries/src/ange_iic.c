#include "ange_iic.h"
#include "ange_USART.H"
#define ange_iic_timeout  1000
void ange_I2C_GPIO_Config()
{
	GPIO_InitTypeDef gpioinit;
	ange_I2C_GPIO_APBxClock(ange_I2C_GPIO_CLK,ENABLE); //开启I2C对应端口时钟
	ange_I2C_APBxClock(ange_I2C_CLK,ENABLE);  //开启I2C时钟
	gpioinit.GPIO_Mode=GPIO_Mode_AF_OD;      //要选择开漏输出
	gpioinit.GPIO_Pin=ange_I2C_SCL_Pin;      //
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_I2C_SCL_PORT,&gpioinit);
	gpioinit.GPIO_Mode=GPIO_Mode_AF_OD;
	gpioinit.GPIO_Pin=ange_I2C_SDA_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_I2C_SDA_PORT,&gpioinit);
}
void ange_I2C_Config()
{
	I2C_InitTypeDef i2cinit;
	i2cinit.I2C_Mode=I2C_Mode_I2C;   //I2C模式，#define I2C_Mode_I2C    I2C_Mode_SMBusDevice  I2C_Mode_SMBusHost   
	i2cinit.I2C_DutyCycle=I2C_DutyCycle_2;  //占空比 低/高
	i2cinit.I2C_OwnAddress1=ange_I2C_OwnAddress;  //本机地址1
	i2cinit.I2C_Ack=I2C_Ack_Enable;    //应答使能
	i2cinit.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit; //寻址方式
	i2cinit.I2C_ClockSpeed=ange_I2C_Speed;  //I2C速度 要小于400000
	I2C_Init(ange_I2Cx,&i2cinit);   //I2C初始化
	I2C_Cmd(ange_I2Cx,ENABLE);   //使能
}
void ange_I2C_init()
{
	ange_I2C_GPIO_Config(); //gpio初始化
	ange_I2C_Config();   //I2C初始化
}
void ange_I2C_EE_ERROR(u8 x)
{
	printf("IIc事件错误%d",x);
}
///字节写入
void ange_I2C_bytewrite(u8 d,u8 s)  //////////字节写入
{
	__IO u32 x=ange_iic_timeout;
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //发送起始信号
			///EV5： SB位0，读SR1寄存器然后将地址写入DR寄存器将清除该事件。0：未发送起始条件；1：起始条件已发送。
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((x--)==0)
 {ange_I2C_EE_ERROR(5); return;}
	}
	//发送地址
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Transmitter);
	//ADDR=1，读SR1然后读SR2将清除该事件(事件6)。   7位地址模式时，当收到地址的ACK后该位被置’1’。
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(6); return;}
	}
	//发送数据地址
	I2C_SendData(ange_I2Cx,d);
	x=ange_iic_timeout;
	//检查事件8
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(8); return;}
	}
	I2C_SendData(ange_I2Cx,s);
	/////////////////////检测到事件后会清除事件
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(8); return;}
	}
	I2C_GenerateSTOP(ange_I2Cx,ENABLE);
	return;
}
////页写入
void ange_I2C_pagewrite(u8 d,u16 n,u8 *data)
{
	__IO u32 x=ange_iic_timeout*10;
	while(I2C_GetFlagStatus(ange_I2Cx,I2C_FLAG_BUSY)==SET)
	{
		if((x--)==0)
		{
			ange_I2C_EE_ERROR(24);
			return;
		}
	}
		x=ange_iic_timeout;
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //发送起始信号
			///EV5： SB位0，读SR1寄存器然后将地址写入DR寄存器将清除该事件。0：未发送起始条件；1：起始条件已发送。
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((x--)==0)
 {ange_I2C_EE_ERROR(25); return;}
	}
	//发送地址
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Transmitter);
	//ADDR=1，读SR1然后读SR2将清除该事件(事件6)。   7位地址模式时，当收到地址的ACK后该位被置’1’。
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(26); return;}
	}
	//发送数据地址
	I2C_SendData(ange_I2Cx,d);
	x=ange_iic_timeout;
	//检查事件8
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(28); return;}
	}
	while(n--)
	{
	I2C_SendData(ange_I2Cx,*data);
	/////////////////////检测到事件后会清除事件
	data++;
	x=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		if((x--)==0) {ange_I2C_EE_ERROR(28); return;}
	}
 }
	I2C_GenerateSTOP(ange_I2Cx,ENABLE);
	return;
}
////////////
void ange_I2C_datawrite(u8 d,u16 n,u8 *data)
{
	u8 ps,pj,py,pd;
	pd=d%eeprom_pagesize;  //地址所在页的第几个地址
	ps=eeprom_pagesize-pd;  //地址所在页还有几个地址
	pj=n/eeprom_pagesize;   //数据总量够写几页
	py=n%eeprom_pagesize;//数据总量还有几个不够一页
	if(pd==0)  //如果从页地址的0号开始
	{
		if(pj==0)   //判断是否够一页，不够一页的话
		{
			ange_I2C_pagewrite(d,n,data); //直接写
			ange_I2C_waitbusy(eeprom_address);
		}
		else
		{
			while(pj--)
			{
			ange_I2C_pagewrite(d,eeprom_pagesize,data); //把整页写入完毕
				ange_I2C_waitbusy(eeprom_address); //等忙
				d+=eeprom_pagesize;  //地址和数据地址加页的大小
				data+=eeprom_pagesize;
			}
			if(py!=0)//最后不满一页的写入
			{
				ange_I2C_pagewrite(d,py,data);
				ange_I2C_waitbusy(eeprom_address);
			}
		}
	}
	else    //如果写入的页地址未对齐
	{
		if(pj==0)  //不够一页
		{
			if(ps>=n) //如果本页剩余地址可以写入完毕
			{
				ange_I2C_pagewrite(d,n,data);
				ange_I2C_waitbusy(eeprom_address);
			}
			else  //如果本页剩余地址不够写入
			{
				ange_I2C_pagewrite(d,ps,data);  //先将本页写入完毕
				ange_I2C_waitbusy(eeprom_address);
				py=n-ps;
				d+=ps;
				data+=ps;
				ange_I2C_pagewrite(d,py,data); //将剩余的在下一页写入
				ange_I2C_waitbusy(eeprom_address);
			}
		}
		else  //超过一页
		{
			pj=(n-ps)/eeprom_pagesize;  //将第一页补齐后还要写入几页
			py=(n-ps)%eeprom_pagesize;  //最终剩余量
			ange_I2C_pagewrite(d,ps,data);  //将第一页写入
			ange_I2C_waitbusy(eeprom_address); 
			d+=ps;
			data+=ps; //加地址
			while(pj--)  //写页
			{
			ange_I2C_pagewrite(d,eeprom_pagesize,data);
			ange_I2C_waitbusy(eeprom_address);
				d+=eeprom_pagesize;
				data+=eeprom_pagesize;
			}
			if(py!=0)  //写剩余量
			{
			ange_I2C_pagewrite(d,py,data);
			ange_I2C_waitbusy(eeprom_address);
			}
		}
	}
	return;
}
/////////////数据读出
void ange_I2C_dataread(u8 d,u16 n,u8 *data)  //字节读取
{
	__IO u32 t=ange_iic_timeout;
	while(I2C_GetFlagStatus(ange_I2Cx, I2C_FLAG_BUSY))
  {
    if((t--) == 0)
			{ange_I2C_EE_ERROR(0xff); return;}
   }
	t=ange_iic_timeout;
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //发送起始信号
			///EV5： SB位0，读SR1寄存器然后将地址写入DR寄存器将清除该事件。0：未发送起始条件；1：起始条件已发送。
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(15); return;}
	}
	//发送器件地址
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Transmitter);
	//ADDR=1，读SR1然后读SR2将清除该事件(事件6)。   7位地址模式时，当收到地址的ACK后该位被置’1’。
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(16); return;}
	}
//	I2C_Cmd(ange_I2Cx,ENABLE);
	I2C_SendData(ange_I2Cx,d);  //写入数据地址
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))  //等待数据发送
	{
		if((t--)==0) {ange_I2C_EE_ERROR(18); return;}
	}
	I2C_GenerateSTART(ange_I2Cx,ENABLE); //发送起始信号
			///EV5： SB位0，读SR1寄存器然后将地址写入DR寄存器将清除该事件。0：未发送起始条件；1：起始条件已发送。
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_MODE_SELECT))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(15); return;}
	}
	I2C_Send7bitAddress(ange_I2Cx,eeprom_address,I2C_Direction_Receiver); //读数据命令
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if((t--)==0) {ange_I2C_EE_ERROR(16); return;}
	}
	while(n)////////////n个数据
	{
		if(n==1)
		{
			I2C_AcknowledgeConfig(ange_I2Cx,DISABLE);
			I2C_GenerateSTOP(ange_I2Cx,ENABLE);  //在即将接收最后一个数据时先失能应答
		}
	t=ange_iic_timeout;
	while(!I2C_CheckEvent(ange_I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED))  //等待数据被接收
	{
		if((t--)==0) {ange_I2C_EE_ERROR(17); return;}
	}
	*data=I2C_ReceiveData(ange_I2Cx);
	data++;
	n--;
 }
	I2C_AcknowledgeConfig(ange_I2Cx,ENABLE);  //使能应答方便下次传输
	return;
}
////////////
void ange_I2C_waitbusy(u8 d)
{
	u16 t=ange_iic_timeout*10;
	do{
		///起始信号
	I2C_GenerateSTART(ange_I2Cx,ENABLE);
//		///读寄存器，作用未知
	I2C_ReadRegister(ange_I2Cx,I2C_Register_SR1);
		//起始位已经发送
		while(I2C_GetFlagStatus(ange_I2Cx,I2C_FLAG_SB)==RESET);
		//发送地址
		I2C_Send7bitAddress(ange_I2Cx,d,I2C_Direction_Transmitter);
		t--;
	}
	//检测addr位，
	while(I2C_GetFlagStatus(ange_I2Cx,I2C_FLAG_ADDR)==RESET&&t!=0);  //我觉得应该加上清除标志位
//	///清除发送失败标志位
//	I2C_ClearFlag(ange_I2Cx,I2C_FLAG_AF);
	///
//	I2C_Cmd(ange_I2Cx,ENABLE);
	I2C_GenerateSTOP(ange_I2Cx,ENABLE);
	return;
}
