/*
  ����˵��: ��������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨(�ⲿ����12MHz) STC89C52RC��Ƭ��
  ��    ��: 2011-8-9
*/
#include "reg52.h"
#include "ange.h"
#include "onewire.h"
sbit DQ = P1^4;  //�����߽ӿ�

//��������ʱ����
void Delay_OneWire(unsigned int t)  //STC89C52RC
{
	uchar a,i=t;
	for(a=0;a<=5;a++)
	{
	while(t--);
		t=i;
	}
}

//ͨ����������DS18B20дһ���ֽ�
void write_ds18b20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
}

//��DS18B20��ȡһ���ֽ�
unsigned char read_ds18b20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}

//DS18B20�豸��ʼ��
bit init_ds18b20(void)
{
  	bit initflag = 0;
  	
  	DQ = 1;
  	Delay_OneWire(12);
  	DQ = 0;
  	Delay_OneWire(80);
  	DQ = 1;
  	Delay_OneWire(10); 
    initflag = DQ;     
  	Delay_OneWire(5);
  
  	return initflag;
}
void Delay750us()		//@12.000MHz
{
	unsigned char i, j;

	i = 9;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

uchar temget()
{
	uchar temp;
	uchar low,high;
	
	init_ds18b20();
	write_ds18b20(0xcc);
	write_ds18b20(0x44);
	 Delay750us();
	init_ds18b20();
	write_ds18b20(0xcc);
	write_ds18b20(0xbe);
	
	low=read_ds18b20();
	high=read_ds18b20();
	
	temp=high<<4;//0000 0101  =0101 0000
	temp |= (low>>4); //  1010 0110   0000 0110 | 0101 0000=0101 0110
	
	return temp;
}




