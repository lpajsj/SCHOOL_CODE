#include "spi.h"
#include "MultiRotor_systime.H"
#include "sys.h"
#include "tlc2543.h"
#include "flash.h"

 
//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ������SD Card/W25Q64/NRF24L01						  
//SPI�ڳ�ʼ��
//�������Ƕ�SPI2�ĳ�ʼ��

void SPI2_Init(void)
{
 	//GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	//RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2ʱ��ʹ�� 	
 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB

// 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15����

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
	
	SPI2_ReadWriteByte(0xff);//��������		 
 
}   
//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   
//SPI_BaudRatePrescaler_8   8��Ƶ   
//SPI_BaudRatePrescaler_16  16��Ƶ  
//SPI_BaudRatePrescaler_256 256��Ƶ 
  
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI2,ENABLE); 

} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
}

/***************************SPI1*************************/

void SPI1_Init(void)
{
		SPI_InitTypeDef  SPI_InitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
      
    /* PA5-SCK PA7-MOSI */  
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5 |GPIO_Pin_7 ;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    /*PA4-CS0*/  
    GPIO_SetBits(GPIOA, GPIO_Pin_4);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);	
  
	 /*PE7-CS1*/  
    GPIO_SetBits(GPIOE, GPIO_Pin_7);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_Init(GPIOE, &GPIO_InitStructure);  
		
    /*PA6-MISO*/  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    /* SPI1 configuration ???SPI??????TLC2543????*/  
    SPI_Cmd(SPI1, DISABLE);                                                 //?????,????MODE  
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      //?????  
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                           //?  
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                      //16?  
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                              //???????????  
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                            //?????????????  
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               //??NSS,?????????  
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;    //128??  
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      //????  
      
    SPI_Init(SPI1, &SPI_InitStructure);  
    SPI_Cmd(SPI1, ENABLE); 
		
		SPI_FLASH_CS_HIGH();        //sst25 CS�ź� ��
		SPI_TLC2543_CS_HIGH();			//tlc2543 CS�ź� ��
		
// 	GPIO_InitTypeDef GPIO_InitStructure;
//  SPI_InitTypeDef  SPI_InitStructure;

//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1,  ENABLE );//SPI1ʱ��ʹ�� 	
 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB

// 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15����

//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ128
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
//	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
//	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
// 
//	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
	
	SPI1_ReadWriteByte(0xff);//��������		 
}   
//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   
//SPI_BaudRatePrescaler_8   8��Ƶ   
//SPI_BaudRatePrescaler_16  16��Ƶ  
//SPI_BaudRatePrescaler_256 256��Ƶ 
  
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI1->CR1&=0XFFC7;
	SPI1->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI1,ENABLE); 

} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
//	GPIO_ResetBits(GPIOA, GPIO_Pin_4);	                          
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  		
//	GPIO_SetBits(GPIOA, GPIO_Pin_4);  
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����					    
}




/****************************MAX6675********************************/

void Init_MAX6675_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TC1_SCK ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(MAX6675_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = TC1_SO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//��������
	GPIO_Init(MAX6675_PORT, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE, GPIO_Pin_0); //CS=1;
	GPIO_SetBits(GPIOE, GPIO_Pin_1); //CS=1;
	GPIO_SetBits(GPIOE, GPIO_Pin_2); //CS=1;
	GPIO_SetBits(GPIOE, GPIO_Pin_3); //CS=1;
	GPIO_SetBits(GPIOB, GPIO_Pin_12);//CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_8); //CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_9); //CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_10);//CS=1;
	GPIO_SetBits(GPIOD, GPIO_Pin_11);//CS=1;

	GPIO_ResetBits(MAX6675_PORT, TC1_SCK );//SCK=0;
	GPIO_SetBits(MAX6675_PORT, TC1_SO);

}

unsigned char MAX6675(unsigned char channel)
{
	u16 temp=0;
	u8 i,temp1=0;
	switch(channel)
	{
		case 1:GPIO_ResetBits(GPIOE, GPIO_Pin_0); break;//CS=1;
		case 2:GPIO_ResetBits(GPIOE, GPIO_Pin_1); break;//CS=2;
		case 3:GPIO_ResetBits(GPIOE, GPIO_Pin_2); break;//CS=3;
		case 4:GPIO_ResetBits(GPIOE, GPIO_Pin_3); break;//CS=4;
		case 5:GPIO_ResetBits(GPIOB, GPIO_Pin_12);break;//CS=5;
		case 6:GPIO_ResetBits(GPIOD, GPIO_Pin_8); break;//CS=6;
		case 7:GPIO_ResetBits(GPIOD, GPIO_Pin_9); break;//CS=7;
		case 8:GPIO_ResetBits(GPIOD, GPIO_Pin_10);break;//CS=8;
		case 9:GPIO_ResetBits(GPIOD, GPIO_Pin_11);break;//CS=9;
		default: temp=0;   break;
	}
	if(DIN)	temp|=0x0001;
	Delay_us(10);
	for(i=0;i<=14;i++)
	{
		SCLK_H;									//read data SO
		Delay_us(10);
		temp<<=1;
		if(DIN)
		temp|=0x0001;
		SCLK_L;
		Delay_us(10);
	}
	temp<<=1;
	if(DIN)	temp|=0x0001;
	Delay_us(10);
	if(temp&0x0004) temp=0;
	temp=(temp>>5);
	switch(channel)
	{
		case 1:
			GPIO_SetBits(GPIOE, GPIO_Pin_0);
			temp1=(unsigned char)(temp); 				//��ȴҺ��ˮ�¶�
		break;//CS=1;
		case 2:
			GPIO_SetBits(GPIOE, GPIO_Pin_1);
			temp1=(unsigned char)(temp>>2); 		//���������¶�
		break;//CS=2;
		case 3:
			GPIO_SetBits(GPIOE, GPIO_Pin_2);
			temp1=(unsigned char)(temp>>1);			//������¶�
		break;//CS=3;
		case 4:
			GPIO_SetBits(GPIOE, GPIO_Pin_3);
			temp1=(unsigned char)(temp>>2); 		//���ͷ�¶�
		break;//CS=4;
		case 5:
			GPIO_SetBits(GPIOB, GPIO_Pin_12);
			temp1=(unsigned char)(temp);				//��ȴҺ��ˮ�¶�
		break;//CS=5;
		case 6:
			GPIO_SetBits(GPIOD, GPIO_Pin_8); 
			temp1=(unsigned char)(temp);				//�����¶�
		break;//CS=6;
		case 7:
			GPIO_SetBits(GPIOD, GPIO_Pin_9); 
			temp1=(unsigned char)(temp>>2);			//���������¶�
		break;//CS=7;
		case 8:
			GPIO_SetBits(GPIOD, GPIO_Pin_10);
			temp1=(unsigned char)(temp>>1);			//�Ҹ����¶�
		break;//CS=8;
		case 9:
			GPIO_SetBits(GPIOD, GPIO_Pin_11);
			temp1=(unsigned char)(temp>>2);			//�Ҹ�ͷ�¶�
		break;//CS=9;
		default: 
			temp1=0;   
		break;
	}
//	temp1=temp;
//	Delay_ms(2);
	return temp1;
}

