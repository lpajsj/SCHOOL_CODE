#include "oled2.h"
#include "stdlib.h"
#include "ange_systick.h"
#include "ange_spi.h"

//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PA0��SCL�� PB3
//              D1   ��PA1��SDA�� PB5
//              DC   ��PA2        PD5
//              CS1  ��PA3        PD7
//              FS0  ��PA4        PB4
//              CS2  ��PA5        PD6

/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_Init(void)
** ��������: OLED��ʼ��
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD,ENABLE);//ʹ��A�˿�ʱ��
//ģ��SPI	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����ģʽ
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	  //��ʼ��GPIOA
	

 	GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

	Delay_ms_OLED2(200);
	
	OLED_WR_Byte(0xAE,OLED_CMD); /*display off*/ 
	OLED_WR_Byte(0x02,OLED_CMD); /*set lower column address*/ 
	OLED_WR_Byte(0x10,OLED_CMD); /*set higher column address*/ 
	OLED_WR_Byte(0x40,OLED_CMD); /*set display start line*/ 
	OLED_WR_Byte(0xB0,OLED_CMD); /*set page address*/
	OLED_WR_Byte(0x81,OLED_CMD); /*contract control*/ 
	OLED_WR_Byte(0xcf,OLED_CMD); /*128*/ 
	OLED_WR_Byte(0xA1,OLED_CMD); /*set segment remap*/ 
	OLED_WR_Byte(0xA6,OLED_CMD); /*normal / reverse*/ 
	OLED_WR_Byte(0xA8,OLED_CMD); /*multiplex ratio*/ 
	OLED_WR_Byte(0x3F,OLED_CMD); /*duty = 1/64*/ 
	OLED_WR_Byte(0xad,OLED_CMD); /*set charge pump enable*/ 
	OLED_WR_Byte(0x8b,OLED_CMD); /* 0x8B �ڹ� VCC */ 
	OLED_WR_Byte(0x33,OLED_CMD); /*0X30---0X33 set VPP 9V */ 
	OLED_WR_Byte(0xC8,OLED_CMD); /*Com scan direction*/ 
	OLED_WR_Byte(0xD3,OLED_CMD); /*set display offset*/ 
	OLED_WR_Byte(0x00,OLED_CMD); /* 0x20 */ 
	OLED_WR_Byte(0xD5,OLED_CMD); /*set osc division*/ 
	OLED_WR_Byte(0x80,OLED_CMD); 
	OLED_WR_Byte(0xD9,OLED_CMD); /*set pre-charge period*/ 
	OLED_WR_Byte(0x1f,OLED_CMD); /*0x22*/ 
	OLED_WR_Byte(0xDA,OLED_CMD); /*set COM pins*/ 
	OLED_WR_Byte(0x12,OLED_CMD); 
	OLED_WR_Byte(0xdb,OLED_CMD); /*set vcomh*/ 
	OLED_WR_Byte(0x40,OLED_CMD);
	OLED_Clear();
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/
	
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	//z	qdelay_xms(200);
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_ColorTurn(u8 i)
** ��������: ���Ժ���
** ����������i
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_ColorTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xA6,OLED_CMD);//������ʾ
	}
	if(i==1)
	{
		OLED_WR_Byte(0xA7,OLED_CMD);//��ɫ��ʾ
	}
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_DisplayTurn(u8 i)
** ��������: ��ʾ��ת180��
** ����������i
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_DisplayTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xC8,OLED_CMD);//������ʾ
		OLED_WR_Byte(0xA1,OLED_CMD);
	}
	if(i==1)
	{
		OLED_WR_Byte(0xC0,OLED_CMD);//��ת��ʾ
		OLED_WR_Byte(0xA0,OLED_CMD);
	}
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_DisPlay_On(void)
** ��������: ��ʼ��ʾ
** ����������i
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x14,OLED_CMD);//������ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//������Ļ
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_DisPlay_Off(void)
** ��������: �ر���ʾ
** ����������i
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x10,OLED_CMD);//�رյ�ɱ�
	OLED_WR_Byte(0xAE,OLED_CMD);//�ر���Ļ
}


/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_WR_Byte(u8 dat,u8 cmd)
** ��������: OLEDд��һ���ֽ�
** ����������dat--���ݣ�cmd-�����������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_WR_Byte(u8 dat,u8 cmd)
{			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	Delay_us_OLED2(1);
 
	SPI3_ReadWriteByte(dat);
  Delay_us_OLED2(1);	
	OLED_CS_Set();
	OLED_DC_Set();   	  
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_Clear(void)
** ��������: ��Ļ���
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	 	 OLED_WR_Byte(0xb0+i,OLED_CMD);//����ҳ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);  //�����е�ַ�ĸ�4λ
	   OLED_WR_Byte(0x02,OLED_CMD);  //�����е�ַ�ĵ�4λ
	   for(n=0;n<128;n++)
		 {
			 OLED_WR_Byte(0x00,OLED_DATA);//�����������
		 }
  }
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_address(u8 x,u8 y)
** ��������: ������ʼ��ַ
** ���������� xy-��ʼ����
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_address(u8 x,u8 y)
{
	x+=2;
	OLED_WR_Byte(0xb0+y,OLED_CMD);              //����ҳ��ַ
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);  //�����е�ַ�ĸ�4λ
	OLED_WR_Byte((x&0x0f),OLED_CMD);            //�����е�ַ�ĵ�4λ
}

//��ʾ128x64����ͼ��
void OLED_Display_128x64(u8 *dp)
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_address(0,i);
		for(j=0;j<128;j++)
		{
			OLED_WR_Byte(*dp,OLED_DATA); //д���ݵ�OLED,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
		
			dp++;
    }
  }
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_Display_16x16(u8 x,u8 y,u8 *dp)
** ��������: ��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��
** ���������� xy-��ʼ���꣬*dp--
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void OLED_Display_16x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<16;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);  //д���ݵ�OLED,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
		  //UART4_Put_Char('A');
			dp++;

    }
		y++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_Display_8x16(u8 x,u8 y,u8 *dp)
** ��������: //��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��
** ���������� xy-��ʼ���꣬*dp--
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void OLED_Display_8x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);   //д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
			//UART4_Put_Char(*dp);
			dp++;
    }
		y++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_Display_5x7(u8 x,u8 y,u8 *dp)
** ��������: //��ʾ5*7����ͼ��ASCII, ��5x7����������ַ�������ͼ��
** ���������� xy-��ʼ���꣬*dp--
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void OLED_Display_5x7(u8 x,u8 y,u8 *dp)
{
	u8 i;
  OLED_address(x,y);
	for(i=0;i<6;i++)
	{
		OLED_WR_Byte(*dp,OLED_DATA);
		dp++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void Send_Command_to_ROM(u8 dat)
** ��������: //��ָ�����Ѷ�ֿ�IC
** ���������� dat--д������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void Send_Command_to_ROM(u8 dat)
{
	   SPI3_ReadWriteByte(dat);
}
/*::::::::::::::::::::::::::::::::::::
** ��������: u8 Get_data_from_ROM(void)
** ��������: //�Ӿ���Ѷ�ֿ�IC��ȡ���ֻ��ַ����ݣ�1���ֽڣ�
** ���������� dat--д������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

u8 Get_data_from_ROM(void)
{
	return SPI3_ReadWriteByte(0xFF);
}



/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen)
** ��������: //����ص�ַ��addrHigh����ַ���ֽ�,addrMid����ַ���ֽ�,addrLow����ַ���ֽڣ�����������DataLen���ֽڵ����ݵ� pbuff�ĵ�ַ
//������ȡ
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen)
{
	u8 i;
	OLED_ROM_CS_Clr();
	Delay_us_OLED2(5);
	Send_Command_to_ROM(0x03);
	Send_Command_to_ROM(addrHigh);
	Send_Command_to_ROM(addrMid);
	Send_Command_to_ROM(addrLow);
	for(i=0;i<DataLen;i++)
	{
		*(pbuff+i)=Get_data_from_ROM();
	//	printf("%d ",*(pbuff+i));
  }
	OLED_ROM_CS_Set();
}


/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_Display_GB2312_string(u8 x,u8 y,u8 *text)
** ��������: ��ʾGB2312����
** ����������  
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_Display_GB2312_string(u8 x,u8 y,u8 *text)
{
	u32 fontaddr=0;
	u8 i=0;
	u8 addrHigh,addrMid,addrLow;
	u8 fontbuf[32];
	while(text[i]>0x00)
	{
		if((text[i]>=0xb0)&&(text[i]<=0xf7)&&(text[i+1]>=0xa1))
		{
			//������壨GB2312�������ھ���Ѷ�ֿ�IC�еĵ�ַ�����¹�ʽ�����㣺
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//���ڵ���8λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
			fontaddr=(text[i]-0xb0)*94;
			fontaddr+=(text[i+1]-0xa1)+846;
			fontaddr=fontaddr*32;
			
			addrHigh=(fontaddr&0xff0000)>>16;   //��ַ�ĸ�8λ,��24λ
			addrMid=(fontaddr&0xff00)>>8;       //��ַ����8λ,��24λ
			addrLow=(fontaddr&0xff);            //��ַ�ĵ�8λ,��24λ
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32);
			//ȡ32���ֽڵ����ݣ��浽"fontbuf[32]"
			
			OLED_Display_16x16(x,y,fontbuf);
			//��ʾ���ֵ�LCD�ϣ�yΪҳ��ַ��xΪ�е�ַ��fontbuf[]Ϊ����
			x+=16;
			i+=2;
    }
		else if((text[i]>=0xa1)&&(text[i]<=0xa3)&&(text[i+1]>=0xa1))
		{
			
			fontaddr=(text[i]-0xa1)*94;
			fontaddr+=(text[i+1]-0xa1);
			fontaddr=fontaddr*32;
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=(fontaddr&0xff);
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32);
			OLED_Display_16x16(x,y,fontbuf);
			x+=16;
			i+=2;
    }
		else if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			unsigned char fontbuf[16];
			fontaddr=(text[i]-0x20);
			fontaddr=(unsigned long)(fontaddr*16);
			fontaddr=(unsigned long)(fontaddr+0x3cf80);
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=fontaddr&0xff;
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16);
			OLED_Display_8x16(x,y,fontbuf);
			x+=8;
			i+=1;
    }
		else 
			i++;
  }
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_Display_string_5x7(u8 x,u8 y,u8 *text)
** ��������: ��ʾGB2312����
** ����������  
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_Display_string_5x7(u8 x,u8 y,u8 *text)
{
	u32 fontaddr=0;
	u8 i=0;
	u8 addrHigh,addrMid,addrLow;
	while(text[i]>0x00)
	{
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			u8 fontbuf[8];
			fontaddr=(text[i]-0x20);
			fontaddr=(unsigned long)(fontaddr*8);
			fontaddr=(unsigned long)(fontaddr+0x3bfc0);
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=fontaddr&0xff;
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,8);
			OLED_Display_5x7(x,y,fontbuf);
			x+=6;
			i+=1;
    }
		else 
			i++;
  }
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void OLED_ShowNum(u8 x,u8 y,float num1,u8 len)
** ��������: ��ʾ2��С����float
** ����������  
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void OLED_ShowNum(u8 x,u8 y,float num1,u8 len)
{
	u8 i;
	u32 t,num;
	x=x+len*8+8;//Ҫ��ʾ��С�����λ�ĺ�����
	num=num1*100;//��С��������λ��ת��Ϊ����
	OLED_Display_GB2312_string(x-24,y,".");//��ʾС����
	for(i=0;i<len;i++)
	{
		t=num%10;//ȡ��λ������ֵ
		num=num/10;//����������һλ
		x-=8;
		if(i==2){x-=8;}//����ʾ��������С��֮�󣬿ճ�С�����λ��
		switch(t)
		{
			case 0 :OLED_Display_GB2312_string(x,y,"0");break;
			case 1 :OLED_Display_GB2312_string(x,y,"1");break;
			case 2 :OLED_Display_GB2312_string(x,y,"2");break;
			case 3 :OLED_Display_GB2312_string(x,y,"3");break;
			case 4 :OLED_Display_GB2312_string(x,y,"4");break;
			case 5 :OLED_Display_GB2312_string(x,y,"5");break;
			case 6 :OLED_Display_GB2312_string(x,y,"6");break;
			case 7 :OLED_Display_GB2312_string(x,y,"7");break;
			case 8 :OLED_Display_GB2312_string(x,y,"8");break;
			case 9 :OLED_Display_GB2312_string(x,y,"9");break;
		}
	}
}


