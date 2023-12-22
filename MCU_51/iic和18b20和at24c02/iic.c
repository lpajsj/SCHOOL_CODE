/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "reg52.h"
#include "intrins.h"
#include "ange.h"
#include "iic.h"
#define delay_time 5
//总线引脚定义

void iic_delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
//总线启动条件
void iic_start(void)
{
    SDA = 1;
    SCL = 1;
    iic_delay(delay_time);
    SDA = 0;
    iic_delay(delay_time);
    SCL = 0;	
}

//总线停止条件
void iic_stop(void)
{
    SDA = 0;
    SCL = 1;
    iic_delay(delay_time);
    SDA = 1;
    iic_delay(delay_time);
}

//发送应答
void iic_sendack(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0：应答，1：非应答
    iic_delay(delay_time);
    SCL = 1;
    iic_delay(delay_time);
    SCL = 0; 
    SDA = 1;
    iic_delay(delay_time);
}

//等待应答
bit iic_waitack(void)
{
    bit ackbit;
	
    SCL  = 1;
    iic_delay(delay_time);
    ackbit = SDA;
    SCL = 0;
    iic_delay(delay_time);
    return ackbit;
}

//通过I2C总线发送数据
void iic_sendbyte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        iic_delay(delay_time);
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        iic_delay(delay_time);
        SCL = 1;
        byt <<= 1;
        iic_delay(delay_time);
    }
    SCL  = 0;  
}

//从I2C总线上接收数据
unsigned char iic_recbyte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL = 1;
	iic_delay(delay_time);
	da <<= 1;
	if(SDA) da |= 1;
	SCL = 0;
	iic_delay(delay_time);
    }
    return da;    
}
void write_at24c02 (uchar address,uchar date)
{
	iic_start();
	iic_sendbyte(0xa0);
	iic_waitack();
	iic_sendbyte(address);
	iic_waitack();
	iic_sendbyte(date);
	iic_waitack();
	iic_stop();
	delay(10);
	return;
}
uchar read_at24c02(uchar address)
{
	uchar a;
	iic_start();
	iic_sendbyte(0xa0);
	iic_waitack();
	iic_sendbyte(address);
	iic_waitack();
	iic_start();
	iic_sendbyte(0xa1);
	iic_waitack();
	a=iic_recbyte();
	iic_sendack(1);
	iic_stop();
	return a;
}
