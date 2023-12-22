//bsp: board support package �弶֧�ְ�

#include "led.h"
#include "systick.h"
__IO unsigned char SMG[] ={0x82,0xee,0x07,0x46,0x6A,0x52,0x12,0xE6,0x02,0x42,0xff,0x7d,0x22,0x02,0x93,0x82,0x13,0x33,0x2A,0x9b,0x2a,0x23};
//__IO unsigned char SMG[] = {0x28,0xBD,0x58,0x19,0x8D,0x0B,0x0A,0xB9,0x08,0x09,0xFF,0xd7};
__IO unsigned char SMGpoint[10] = {0x20,0xB5,0x50,0x11,0x85,0x03,0x02,0xB1,0x00,0x01};

void LED_GPIO_Config(void)
{
	
	//��һ������GPIOʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		
	//�ڶ���������һ��GPIO��ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//������������GPIO��ʼ���ṹ���Ա
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_8 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	
	//ֻҪ����Ϊ���ģʽ��ODRĬ��Ϊ0x00000000Ĭ��Ϊ���� ������PuPd
	
	/*���Ĳ�������GPIO��ʼ��������
			�����úõĽṹ���Աд��Ĵ���*/
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
//	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
}
void output(u8 x)
{
	unsigned char x1,x2,i;
	
	x1 = SMG[(x&0x0F)];
	x2 = SMG[ (x>>4) ];
	
	for(i=0;i<8;i++)
	{
		SH0;
//		delay_us(2);
		if(x1&0x80)
		{
			DS1;
		}
		else
		{
			DS0;
		}
//		delay_us(2);
		x1<<=1;
		SH1;
		delay_us(1);
		SH0;
	}
//-------------------------------------------------	
	for(i=0;i<8;i++)
	{
		SH0;
//		delay_us(2);
		if(x2&0x80)
		{
			DS1;
		}
		else
		{
			DS0;
		}
//		delay_us(2);
		x2<<=1;
		SH1;
		delay_us(1);
		SH0;
	}
	
	
}
//void output(u8 x)
//{
//	unsigned char x1,x2;
//	
//	x1 = SMG[ (x&0x0F) ];
//	x2 = SMG[ (x>>4) ];
//	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;}	
//	SH1;
//		
//	x1<<=1;	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;}	
//	SH1;
//		
//	x1<<=1;	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;}	
//	SH1;
//	x1<<=1;	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x1<<=1;	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x1<<=1;	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x1<<=1;	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x1<<=1;	
//	SH0;
//	if( (x1&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
////-------------------------------------------------	
//		
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x2<<=1;	
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x2<<=1;	
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x2<<=1;	
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x2<<=1;	
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x2<<=1;	
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x2<<=1;	
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;
//	x2<<=1;	
//	SH0;
//	if( (x2&0x80) == 0)	{DS0;}
//		else {DS1;} 
//	SH1;	
//	SH0;
//	
//	
//}
void output_point(u8 x)
{
	unsigned char x1,x2;
	
	x1 = SMGpoint[ (x&0x0F) ];
	x2 = SMG[ (x>>4) ];
	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;}	
	SH1;
		
	x1<<=1;	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;}	
	SH1;
	x1<<=1;	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;}	
	SH1;
	x1<<=1;	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x1<<=1;	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x1<<=1;	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x1<<=1;	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x1<<=1;	
	SH0;
	if( (x1&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
//-------------------------------------------------	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x2<<=1;	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x2<<=1;	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x2<<=1;	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x2<<=1;	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x2<<=1;	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x2<<=1;	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;
	x2<<=1;	
	SH0;
	if( (x2&0x80) == 0)	{DS0;}
		else {DS1;} 
	SH1;	
	SH0;
	
	
}

