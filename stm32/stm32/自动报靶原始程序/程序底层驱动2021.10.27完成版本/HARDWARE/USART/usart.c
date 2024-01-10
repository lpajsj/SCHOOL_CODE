#include "usart.h" 
#include "MultiRotor_systime.H"
#include "led.h"

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0x40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif

//��ʼ��IO ����1 
//bound:������

u8 data1[58];            //��̬���ݰ� ���� �����ѹ��ת�١�PWM�������ǡ����������  200ms��һ��
u8 data2[22];            //��ѹ�¶����ݰ� ��������λ�á������ѹ���������¶Ȳ���    1s��һ��
u8 data3[48];            //GPS���ݰ�  ������γ�ȡ����١�ʱ���GPS��ȡ�Ĳ���         1s��һ��

u8 sys_ID=0;
u8 par_ID=0;
u8 Write_ID=0;
u16 recoad_min;
u8 curtime[8];
void Usart1_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
	
}

u8 Tx1Buffer[255];
u8 Rx1Buffer[100];
u8 TxCounter1=0;
u8 xtbuff[10]={"www.usr.cn"};
u8 count1=0;
u8 Rx1count;
u8 comminflag;
void USART1_IRQHandler(void)//����1�жϷ������
{
	//ORE�ж� ������� (Overrun error)
	if(USART1->SR & USART_SR_ORE)
	{
		u8 com_data = USART1->DR;
		USART_ClearFlag(USART1,USART_IT_ORE);
	}
	//���ͣ�������λ���ж�
	if((USART1->SR & (1<<7))&&(USART1->CR1 & USART_CR1_TXEIE))//�������ݼĴ���Ϊ�� && �����жϴ���
	{
		USART1->DR = Tx1Buffer[TxCounter1++]; //дDR����жϱ�־ 
		if(TxCounter1 == count1)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;	  //�ر�TXE�ж�
		}
	}
	//�����ж�
	if(USART1->SR & (1<<5))//if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)    
	{
		u8 i;
		u8 com_data = USART1->DR;
		Rx1Buffer[Rx1count]=com_data;
		Rx1count++;
		if(Rx1count==10)
		{
			Rx1count=0;
//			Usart5_Send(Rx1Buffer,10);
			for(i=0;i<10;i++)
			{
				if(Rx1Buffer[i]!=xtbuff[i])
				{
					comminflag=0;
				}
				else 
				{
					comminflag=1;         //�������ݰ����ձ�־ 10�ֽ�
				}
			}
		}
		//ANO_DT_Data_Receive_Prepare(com_data);
	}
//	LED2=1;
} 

void Usart1_Send(unsigned char *DataToSend , u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)//��Ҫ���͵����ݽ��л��δ洢
	{
		Tx1Buffer[count1++] = *(DataToSend+i);
	}
	
	if(!(USART1->CR1 & USART_CR1_TXEIE))//�� USART_SR �Ĵ����� TXE=1 ʱ������ USART �жϡ�
	{
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}
}

//u8 Uart1_4G_init(void)
//{
//	u8 TxBuffer1[100];
//	TxBuffer1[0]=0x41;
//	TxBuffer1[1]=0x54;
//	TxBuffer1[2]=0x0d;
//	TxBuffer1[3]=0x0a;
//	Usart1_Send(TxBuffer1,4);
//	Delay_ms(200);
//	
//	return(comminflag);
//}



///////////////////////////����2//////////////////////////////
void Usart2_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//USART1_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}

u8 Tx2Buffer[255];
u8 TxCounter2=0;
u8 count2=0; 
void USART2_IRQHandler(void)//����2�жϺ���
{
	//ORE�ж� ������� (Overrun error)
	if(USART2->SR & USART_SR_ORE)
	{
		u8 com_data = USART2->DR;
		USART_ClearFlag(USART2,USART_IT_ORE);
	}
	//���ͣ�������λ���ж�
	if((USART2->SR & (1<<7))&&(USART2->CR1 & USART_CR1_TXEIE))//�������ݼĴ���Ϊ�� && �����жϴ���
	{
		USART2->DR = Tx2Buffer[TxCounter2++]; //дDR����жϱ�־ 
		if(TxCounter2 == count2)
		{
			USART2->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�
		}
	}
	//�����ж�
	if(USART2->SR & (1<<5))//if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)    
	{
		u8 com_data = USART2->DR;
		//Ultra_Get(com_data);
		//GPS_Receive_Anl(com_data);
	}
}

void Usart2_Send(unsigned char *DataToSend ,u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)//��Ҫ���͵����ݽ��л��δ洢
	{
		Tx2Buffer[count2++] = *(DataToSend+i);
	}

	if(!(USART2->CR1 & USART_CR1_TXEIE))//�� USART_SR �Ĵ����� TXE=1 ʱ������ USART �жϡ�
	{
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}
}


///////////////////////////����3///////////////////////////////
void Usart3_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//USART1_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOB.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���1 

}

u8 Tx3Buffer[255];
u8 Rx3Buffer[100];
u8 TxCounter3=0;
u8 count3=0; 
u16 count=0;
u32 temp;
u32 latitude;        //γ��
u32 longitude;       //����

void USART3_IRQHandler(void)//����3�жϺ���  �жϽ���GPS����  latitude   longitude
{
	//ORE�ж� ������� (Overrun error)
	if(USART3->SR & USART_SR_ORE)//USART6->SR��״̬�Ĵ���
	{
		u8 com_data = USART3->DR;
		USART_ClearFlag(USART3,USART_IT_ORE);
	}
	//���ͣ�������λ���ж�
	if((USART3->SR & (1<<7))&&(USART3->CR1 & USART_CR1_TXEIE))//�������ݼĴ���Ϊ�� && �����жϴ���
	{
		USART3->DR = Tx3Buffer[TxCounter3++]; //дDR����жϱ�־    USART6->DR�����ݼĴ���    
		if(TxCounter3 == count3)
		{
			USART3->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�  USART6->CR1�����ƼĴ���1
		}
	}
	//�����ж�
	if(USART3->SR & (1<<5))//if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)    
	{
		u8 i;
		u8 com_data = USART3->DR;
		Rx3Buffer[count3]=com_data;
		count3++;
		if(Rx3Buffer[0]==0x3f)
		{
			if(count3>=4)
			{
				if((Rx3Buffer[2]==0x81)&&(Rx3Buffer[3]==0x54))
				{
					if(count3==6)
					{
						count=Rx3Buffer[4];//
						if(count==0) count3=0;
						else;;
					}
					else if (count3>=7)
					{
						count--;
						if(count==0)
						{
								count3=0;
								for(i=0;i<Rx3Buffer[4];i++)  //���յ�GPS��Ϣת�浽���ͻ�����
											{
												data3[i+6]=Rx3Buffer[i+6];
//												data3[6]=Rx3Buffer[9];
//												data3[7]=Rx3Buffer[8];
//												data3[8]=Rx3Buffer[7];
//												data3[9]=Rx3Buffer[6];
//												
//												data3[10]=Rx3Buffer[13];
//												data3[11]=Rx3Buffer[12];
//												data3[12]=Rx3Buffer[11];
//												data3[13]=Rx3Buffer[10];
											}
//									else if(Rx3Buffer[3]==0x57)
//									{
//										for(i=0;i<(Rx3Buffer[4]-2);i++)
//										{
//											data3[i+46]=Rx3Buffer[i+6];
//											
//										}
//									}
						}
						else ;;
					}
					else;;
				}
				else count3=0;
			}
			else ;;
		}
		else count3=0;
		
		//Ultra_Get(com_data);
	}
}

void Usart3_Send(unsigned char *DataToSend ,u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)//��Ҫ���͵����ݽ��л��δ洢
	{
		Tx3Buffer[count3++] = *(DataToSend+i);
	}

	if(!(USART3->CR1 & USART_CR1_TXEIE))//�� USART_SR �Ĵ����� TXE=1 ʱ������ USART �жϡ�
	{
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}
}

///////////////////////////����4///////////////////////////////
void Usart4_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//ʹ��USART4��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//USART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO C.10
   
  //USART4_RX	  GPIOC.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.11  

  //Usart4 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(UART4, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���1 

}

u8 Tx4Buffer[255];
u8 Rx4Buffer[20];
u8 TxCounter4=0;
u8 count4=0; 
u8 RX_count4=0;
u16 high;

void UART4_IRQHandler(void)//����4�жϺ���   �жϽ��ܸ߶�����  high
{
	//ORE�ж� ������� (Overrun error)
	if(UART4->SR & USART_SR_ORE)//USART6->SR��״̬�Ĵ���
	{
		u8 com_data = UART4->DR;
		USART_ClearFlag(UART4,USART_IT_ORE);
	}
	//���ͣ�������λ���ж�
	if((UART4->SR & (1<<7))&&(UART4->CR1 & USART_CR1_TXEIE))//�������ݼĴ���Ϊ�� && �����жϴ���
	{
		UART4->DR = Tx4Buffer[TxCounter4++]; //дDR����жϱ�־    USART6->DR�����ݼĴ���    
		if(TxCounter4 == count4)
		{
			UART4->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�  USART6->CR1�����ƼĴ���1
		}
	}
	//�����ж�
	if(UART4->SR & (1<<5))//if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)    
	{
		u8 com_data = UART4->DR;
		Rx4Buffer[RX_count4]=com_data;
		if(Rx4Buffer[0]==0x24)
		{
			RX_count4++;
			if((Rx4Buffer[RX_count4-2]==0x0d)&&(Rx4Buffer[RX_count4-1]==0x0a))			//
			{
				
				if((Rx4Buffer[1]==0x6c)&&(Rx4Buffer[2]==0x64)&&(Rx4Buffer[3]==0x66)&&(Rx4Buffer[4]==0x2c)&&(Rx4Buffer[5]==0x31)&&(Rx4Buffer[6]==0x3a))
				{
						high= (Rx4Buffer[RX_count4-4]-0x30);
						high= high+(Rx4Buffer[RX_count4-5]-0x30)*10;
						high= high+(Rx4Buffer[RX_count4-7]-0x30)*100;
						if(RX_count4==15)
						{
							high=high+(Rx4Buffer[RX_count4-8]-0x30)*1000;
						}
						else if(RX_count4==16)
						{
							high=high+(Rx4Buffer[RX_count4-8]-0x30)*1000+(Rx4Buffer[RX_count4-9]-0x30)*10000;
						}
						else ;;
						RX_count4=0;
			  }
				else RX_count4=0;
			}
		}
	}
}

void Usart4_Send(unsigned char *DataToSend ,u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)//��Ҫ���͵����ݽ��л��δ洢
	{
		Tx4Buffer[count4++] = *(DataToSend+i);
	}

	if(!(UART4->CR1 & USART_CR1_TXEIE))//�� USART_SR �Ĵ����� TXE=1 ʱ������ USART �жϡ�
	{
		USART_ITConfig(UART4, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}
}



///////////////////////////����5///////////////////////////////
void Usart5_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//ʹ��USART1��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	///SDIO_CMD/USART5_RX//TIM3_ETR/PD2��Ҫ���ö˿�
	//GPIO_PinRemapConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);
	
	//USART1_TX   GPIOC.12
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOD.2��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(UART5, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ���1 

}

u8 Tx5Buffer[255];
u8 Rx5Buffer[10];

u8 TxCounter5=0;
u8 RxCounter5=0;
u8 count5=0; 
void UART5_IRQHandler(void)//����5�жϺ���
{
	//ORE�ж� ������� (Overrun error)
	if(UART5->SR & USART_SR_ORE)//USART6->SR��״̬�Ĵ���
	{
		u8 com_data = UART5->DR;
		USART_ClearFlag(UART5,USART_IT_ORE);
	}
	//���ͣ�������λ���ж�
	if((UART5->SR & (1<<7))&&(UART5->CR1 & USART_CR1_TXEIE))//�������ݼĴ���Ϊ�� && �����жϴ���
	{
		UART5->DR = Tx5Buffer[TxCounter5++]; //дDR����жϱ�־    USART6->DR�����ݼĴ���    
		if(TxCounter5 == count5)
		{
			UART5->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�  USART6->CR1�����ƼĴ���1
		}
	}
	//�����ж�
	if(UART5->SR & (1<<5))//if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)    
	{
		u8 temp;
		u8 com_data = UART5->DR;
		Rx5Buffer[RxCounter5]=com_data;
		if(Rx5Buffer[0]==0xfc)
		{
			RxCounter5++;
			if(RxCounter5==0x04)
			{
				temp=Rx5Buffer[0]+Rx5Buffer[1]+Rx5Buffer[2];
				if(temp==Rx5Buffer[3])
				{
					sys_ID=Rx5Buffer[1];
					par_ID=Rx5Buffer[2];
					Write_ID=1;
				}
			RxCounter5=0;
			}
		}
		else if(Rx5Buffer[0]==0xfd)
		{
			RxCounter5++;
			if(RxCounter5==0x03)
			{
				temp=Rx5Buffer[0]+Rx5Buffer[1];
				if(temp==Rx5Buffer[2])
				{
					recoad_min=Rx5Buffer[1];
					if(recoad_min>=60)   						//���60����
					{
						recoad_min=60;
					}
					Write_ID=2;
				}
				RxCounter5=0;
			}
		}
		else if(Rx5Buffer[0]==0xfe)
		{
			RxCounter5++;
			if(RxCounter5==0x0a)
			{
				temp=Rx5Buffer[0]+Rx5Buffer[1]+Rx5Buffer[2]+Rx5Buffer[3]+Rx5Buffer[4]+Rx5Buffer[5]+Rx5Buffer[6]+Rx5Buffer[7]+Rx5Buffer[8];
				if(temp==Rx5Buffer[9])
				{
					curtime[0]=Rx5Buffer[1];
					curtime[1]=Rx5Buffer[2];
					curtime[2]=Rx5Buffer[3];
					curtime[3]=Rx5Buffer[4];
					curtime[4]=Rx5Buffer[5];
					curtime[5]=Rx5Buffer[6];
					curtime[6]=Rx5Buffer[7];
					curtime[7]=Rx5Buffer[8];
					Write_ID=3;
				}
				RxCounter5=0;					
			}
		}
		else ;;
	}
}

void Usart5_Send(unsigned char *DataToSend ,u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)//��Ҫ���͵����ݽ��л��δ洢
	{
		Tx5Buffer[count5++] = *(DataToSend+i);
	}

	if(!(UART5->CR1 & USART_CR1_TXEIE))//�� USART_SR �Ĵ����� TXE=1 ʱ������ USART �жϡ�
	{
		USART_ITConfig(UART5, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}
}

