#include "QMC5883.h"
#include "ange_USART.h"
#define delay_us_qmc SysTick_delayus		
void qmc5883_gpio_init()
{
	GPIO_InitTypeDef gpioinit;
	RCC_AHB1PeriphClockCmd(QMC_SCL_GPIO_CLK|QMC_SDA_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_OUT;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_UP;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=QMC_SCL_GPIO_Pin;
	GPIO_Init(QMC_SCL_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=QMC_SDA_GPIO_Pin;
	GPIO_Init(QMC_SDA_GPIO_PORT,&gpioinit);
	QMC_IIC_SCL=1;
	QMC_IIC_SDA=1;
}
//软件IIC

//产生IIC起始信号
void QMC_IIC_Start(void)
{
	QMC_SDA_OUT();     //sda线输出
	QMC_IIC_SDA=1;	  	  
	QMC_IIC_SCL=1;
	delay_us_qmc(4);
 	QMC_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us_qmc(4);
	QMC_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void QMC_IIC_Stop(void)
{
	QMC_SDA_OUT();//sda线输出
	QMC_IIC_SCL=0;
	QMC_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us_qmc(4);
	QMC_IIC_SCL=1; 
	QMC_IIC_SDA=1;//发送I2C总线结束信号
	delay_us_qmc(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 QMC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	QMC_SDA_IN();      //SDA设置为输入  
	QMC_IIC_SDA=1;delay_us_qmc(1);	   
	QMC_IIC_SCL=1;delay_us_qmc(1);	 
	while(QMC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			QMC_IIC_Stop();
			return 1;
		}
	}
	QMC_IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void QMC_IIC_Ack(void)
{
	QMC_IIC_SCL=0;
	QMC_SDA_OUT();
	QMC_IIC_SDA=0;
	delay_us_qmc(2);
	QMC_IIC_SCL=1;
	delay_us_qmc(2);
	QMC_IIC_SCL=0;
}
//不产生ACK应答		    
void QMC_IIC_NAck(void)
{
	QMC_IIC_SCL=0;
	QMC_SDA_OUT();
	QMC_IIC_SDA=1;
	delay_us_qmc(2);
	QMC_IIC_SCL=1;
	delay_us_qmc(2);
	QMC_IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void QMC_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	QMC_SDA_OUT(); 	    
    QMC_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        QMC_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us_qmc(2);   //对TEA5767这三个延时都是必须的
		QMC_IIC_SCL=1;
		delay_us_qmc(2); 
		QMC_IIC_SCL=0;	
		delay_us_qmc(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 QMC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	QMC_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        QMC_IIC_SCL=0; 
        delay_us_qmc(2);
		QMC_IIC_SCL=1;
        receive<<=1;
        if(QMC_READ_SDA)receive++;   
		delay_us_qmc(1); 
    }					 
    if (!ack)
        QMC_IIC_NAck();//发送nACK
    else
        QMC_IIC_Ack(); //发送ACK   
    return receive;
}


//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 QMC_IIC_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(QMC_IIC_Wait_Ack())	//等待应答
	{
		QMC_IIC_Stop();		 
		return 1;		
	}
    QMC_IIC_Send_Byte(reg);	//写寄存器地址
    QMC_IIC_Wait_Ack();		//等待应答
	for(i=0;i<len;i++)
	{
		QMC_IIC_Send_Byte(buf[i]);	//发送数据
		if(QMC_IIC_Wait_Ack())		//等待ACK
		{
			QMC_IIC_Stop();	 
			return 1;		 
		}		
	}    
    QMC_IIC_Stop();	 
	return 0;	
} 
//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 QMC_IIC_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(QMC_IIC_Wait_Ack())	//等待应答
	{
		QMC_IIC_Stop();		 
		return 1;		
	}
    QMC_IIC_Send_Byte(reg);	//写寄存器地址
    QMC_IIC_Wait_Ack();		//等待应答
    QMC_IIC_Start();
	QMC_IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令	
    QMC_IIC_Wait_Ack();		//等待应答 
	while(len)
	{
		if(len==1)*buf=QMC_IIC_Read_Byte(0);//读数据,发送nACK 
		else *buf=QMC_IIC_Read_Byte(1);		//读数据,发送ACK  
		len--;
		buf++; 
	}    
    QMC_IIC_Stop();	//产生一个停止条件 
	return 0;	
}
//IIC写一个字节 
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 QMC_IIC_Write_Byte(u8 addr,u8 reg,u8 data) 				 
{ 
    QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(QMC_IIC_Wait_Ack())	//等待应答
	{
		QMC_IIC_Stop();		 
		return 1;		
	}
    QMC_IIC_Send_Byte(reg);	//写寄存器地址
    QMC_IIC_Wait_Ack();		//等待应答 
	QMC_IIC_Send_Byte(data);//发送数据
	if(QMC_IIC_Wait_Ack())	//等待ACK
	{
		QMC_IIC_Stop();	 
		return 1;		 
	}		 
    QMC_IIC_Stop();	 
	return 0;
}
//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 QMC_IIC_Read_RES_Byte(u8 addr,u8 reg)
{
	u8 res;
    QMC_IIC_Start(); 
	QMC_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	QMC_IIC_Wait_Ack();		//等待应答 
    QMC_IIC_Send_Byte(reg);	//写寄存器地址
    QMC_IIC_Wait_Ack();		//等待应答
    QMC_IIC_Start();
	QMC_IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令	
    QMC_IIC_Wait_Ack();		//等待应答 
	res=QMC_IIC_Read_Byte(0);//读取数据,发送nACK 
    QMC_IIC_Stop();			//产生一个停止条件 
	return res;		
}

void qmc5883_init()
{
	u8 x;
	qmc_delayms(50);
	qmc5883_gpio_init();
	x=0x80;
	QMC_IIC_Write_Len(QMC5883_ADDR,0x0a,1,&x);
	x=0x01;
	QMC_IIC_Write_Len(QMC5883_ADDR,0x0B,1,&x);
	x=0x1d;
	QMC_IIC_Write_Len(QMC5883_ADDR,0x09,1,&x);
}
void qmc5883_get_raw_data(float *x,float *y,float *z,float *t)
{
	u8 q;
	u8 shuju[9];
	QMC_IIC_Read_Len(QMC5883_ADDR,0x06,1,&q);
	
	if(q&0x01)
	{
		QMC_IIC_Read_Len(QMC5883_ADDR,0x00,9,shuju);
		*x=(((int16_t)shuju[1]*256)+((int16_t)shuju[0]));
		*y=(((int16_t)shuju[3]*256)+((int16_t)shuju[2]));
		*z=(((int16_t)shuju[5]*256)+((int16_t)shuju[4]));
		*t=(((int16_t)shuju[8]*256)+((int16_t)shuju[7]));
	}
	QMC_IIC_Read_Len(QMC5883_ADDR,0x0d,1,&q);
	printf("%d\n",q);
}




























