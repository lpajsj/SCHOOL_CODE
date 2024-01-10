/******************* (C) COPYRIGHT 2016 509 Team ***************************
 * �ļ���   ��I2C.c
 * ����     ��IIC���ú���  
 * ʵ��ƽ̨ ��FK_3.0�ɿ���������@STM32F103CBT6
 * ��汾   ��ST3.5.0
 * ����     ��509 Team   
***************************************************************************/
#include "I2C.h"

/*******************************************************************************
* Function Name  : I2C_Configura
* Description    : Configration Simulation IIC GPIO
* Input          : None 
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Configura(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;              					// �ṹ�嶨��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);       // ʹ��GPIOBʱ��
  
	GPIO_InitStructure.GPIO_Pin =  SCL_PIN;    // ����SCL&&SDA�ܽ�
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   //��© GPIO_Mode_Out_PP GPIO_Mode_Out_OD
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  SDA_PIN;    // ����SCL&&SDA�ܽ�
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   //��©
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//GPIO_SetBits(GPIOB,GPIO_Pin_6);						 //PB.5 �����
	//GPIO_SetBits(GPIOB,GPIO_Pin_7);						 //PB.5 �����
	
}
/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_delay(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();//332.6ns
}
/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
u8 I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)
		return FALSE;	// SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L;
	I2C_delay();
	if(SDA_read) 
		return FALSE;	// SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L;
	I2C_delay();
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
u8 I2C_WaitAck(void) 	 // ����Ϊ:=1��ACK,=0��ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
    SCL_L;
	  I2C_delay();
      return FALSE;
	}
	SCL_L;
	I2C_delay();
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_SendByte(u8 SendByte) // ���ݴӸ�λ����λ
{
	u8 i=8;
	while(i--)
	{
		SCL_L;
		I2C_delay();
		if(SendByte&0x80)
			SDA_H;  
		else 
			SDA_L;   
		SendByte<<=1;
		I2C_delay();
		SCL_H;
		I2C_delay();
	}
	SCL_L;
}  
/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
u8 I2C_RadeByte(void)  // ���ݴӸ�λ����λ
{ 
	u8 i=8;
	u8 ReceiveByte=0;

	SDA_H;				
	while(i--)
	{
		ReceiveByte<<=1;      
		SCL_L;
		I2C_delay();
		SCL_H;
		I2C_delay();	
		if(SDA_read)
		{
			ReceiveByte|=0x01;
		}
	}
	SCL_L;
	return ReceiveByte;
} 
/*******************************************************************************
* Function Name  : Single_Write
* Description    : Master Write a Byte To Slave
* Input          : SlaveAddress REG_Address Will Send Date
* Output         : None
* Return         : TRUE or FALSE 
****************************************************************************** */
u8 Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)		     
{
	if(!I2C_Start())
		return FALSE;
	I2C_SendByte(SlaveAddress);      
	if(!I2C_WaitAck())
	{
		I2C_Stop(); 
		return FALSE;
	}
	I2C_SendByte(REG_Address );      // ���õ���ʼ��ַ      
	I2C_WaitAck();	
	I2C_SendByte(REG_data);
	I2C_WaitAck();   
	I2C_Stop(); 
	return TRUE;
}
/*******************************************************************************
* Function Name  : Single_Read
* Description    : Master Write a Byte From Slave
* Input          : SlaveAddress REG_Address 
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
u8 Single_Read(u8 SlaveAddress,u8 REG_Address)
{  
	unsigned char REG_data;
	
	if(!I2C_Start())
		return FALSE;
	I2C_SendByte(SlaveAddress);        
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return FALSE;
	}
	I2C_SendByte((u8) REG_Address);   // ���õ���ʼ��ַ      
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(SlaveAddress+1);
	I2C_WaitAck();

	REG_data= I2C_RadeByte();
	I2C_NoAck();
	I2C_Stop();
	return REG_data;
}	
/*******************************************************************************
* Function Name  : I2C_Read
* Description    : Master Write a Byte From Slave
* Input          : addr_ reg_ len buf
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
u8 I2C_Read(u8 addr_, u8 reg_, u8 len, u8 *buf)
{
	u8 i;
	// ��ʼ�ź�
	I2C_Start();
	
	// �����豸��ַ
	I2C_SendByte(addr_);   
	
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return 1;
	}
	
	// ���ʹ洢��Ԫ��ַ
	I2C_SendByte(reg_);                   
	I2C_WaitAck();
	
	// ��ʼ�ź�
	I2C_Start();

	// �����豸��ַ+���ź�
	I2C_SendByte(addr_+1);     
	I2C_WaitAck();
	for (i=0; i<len; i++)                   // ������ȡ6����ַ���ݣ��洢��BUF
	{
		*(buf+i) = I2C_RadeByte();            // BUF[0]�洢����
		if (i == len-1)		I2C_NoAck();        // ���һ��������Ҫ��NOACK
		else		I2C_Ack();                    // ��ӦACK
	}
	I2C_Stop();                             // ֹͣ�ź�
	I2C_delay();
	return 0;
}
