#ifndef _IIC_H
#define _IIC_H

void iic_start(void); 
void iic_stop(void);  
bit iic_waitack(void);  
void iic_sendack(bit ackbit); 
void iic_sendbyte(unsigned char byt); 
unsigned char iic_recbyte(void); 
void write_at24c02 (uchar address,uchar date);
uchar read_at24c02(uchar address);
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */
#endif