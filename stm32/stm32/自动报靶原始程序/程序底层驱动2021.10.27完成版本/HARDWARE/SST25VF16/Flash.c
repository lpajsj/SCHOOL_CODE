/******************************************
**File Name  :  Flash.c
**Description:  ���ļ���flash�洢
******************************************/
#include "stm32f10x.h"
#include "tlc2543.h"
#include "flash.h"
#include "MultiRotor_systime.H"
#include "led.h"
#include "usart.h"
#include "stm32_flash.h"

/* ��ӳ��� */
u32 MAX_ADDR=0x200000;//flashоƬ������ַ����ID�ɵ�
/******************************************
**Function Name :  Write_Flash 
**Description   :  дflash 
**Input         :  Ҫд���flash�׵�ַ��д�������ָ�롢д������ݳ���
**Return        �� void
******************************************/
void sst25_write(u32 flash_start_addr,u8* WriteBuffer,u16 size)
{
	df_write_open(flash_start_addr);    /* ��Ҫд�ĳ�ʼ��ַ */
	df_write((u8*)WriteBuffer,size); //��WriteBufferָ���size���ֽ�д��flash
	df_write_close();
//	delay1ms(20);
} 
/******************************************
**Function Name :  Read_Flash 
**Description   :  ��flash 
**Input         :  Ҫ������flash�׵�ַ������������ָ�롢���������ݳ���
**Return        �� void
******************************************/
void sst25_read(u32 flash_start_addr,u8* ReadBuffer,u16 size)
{
	df_read_open(flash_start_addr);
	df_read((u8*)ReadBuffer, size);
	df_read_close();
//	delay1ms(20);
}

/* ����Ϊ��ֲ���� */


/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : ��ʼ������SSI�Ĺܽ�
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void sst25_init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  
  SPI_FLASH_CS_HIGH();
	SPI_Cmd(SPI1, DISABLE); 
  /* SPI1 Config -------------------------------------------------------------*/ 								  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
	
  SPI_Init(SPI1, &SPI_InitStructure);
   SPI_Cmd(SPI1, ENABLE); 
}


/*******************************************************************************
* Function Name  : Flash_ReadWriteByte
* Description    : ͨ��Ӳ��SPI����һ���ֽڵ�SST25VF016B
* Input          : - data: ���͵�����
* Output         : None
* Return         : SST25VF016B ���ص�����
* Attention		 : None
*******************************************************************************/
u8 Flash_ReadWriteByte(u8 SPI_TX_data)		
{
	u8 temp;
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}

  /* Send byte through the SPI2 peripheral */
  SPI_I2S_SendData(SPI1, SPI_TX_data);
    
  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){}

  /* Return the byte read from the SPI bus */
	temp=	SPI_I2S_ReceiveData(SPI1);
  return  (temp);                                             
}


/* ���º�������ֲʱ�����޸� */
/*******************************************************************************
* Function Name  : SSTF016B_RD
* Description    : SST25VF016B�Ķ�����,��ѡ���ID�Ͷ����ݲ���
* Input          : - Dst: Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��
*                  - RcvBufPt: ���ջ����ָ��
*                  - NByte: Ҫ��ȡ�������ֽ���	
* Output         : �����ɹ��򷵻�OK,ʧ���򷵻�ERROR
* Return         : SST25VF016B ���ص�����
* Attention		 : ��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
*******************************************************************************/
u8 SSTF016B_RD(u32 Dst, u8* RcvBufPt ,u32 NByte)
{
	u32 i = 0;
	if ((Dst+NByte > MAX_ADDR)||(NByte == 0))	return (ERROR);	 /*	�����ڲ��� */
	
  SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(0x0B); 						/* ���Ͷ����� */
	Flash_ReadWriteByte(((Dst & 0xFFFFFF) >> 16));	/* ���͵�ַ��Ϣ:�õ�ַ��3���ֽ����	*/
	Flash_ReadWriteByte(((Dst & 0xFFFF) >> 8));
	Flash_ReadWriteByte(Dst & 0xFF);
	Flash_ReadWriteByte(0xFF);						/* ����һ�����ֽ��Զ�ȡ����	*/
	for (i = 0; i < NByte; i++)		
	{
      RcvBufPt[i] = Flash_ReadWriteByte(0xFF);	
			Usart5_Send(&RcvBufPt[i],1);
			Delay_us(100);
	}
    SPI_FLASH_CS_HIGH();
	return (ENABLE);
}

/*******************************************************************************
* Function Name  : SSTF016B_RdID
* Description    : SST25VF016B�Ķ�ID����,��ѡ���ID�Ͷ����ݲ���
* Input          : - IDType: ID���͡��û�����Jedec_ID,Dev_ID,Manu_ID������ѡ��
* Output         : - RcvbufPt: �洢ID������ָ��
* Return         : �����ɹ��򷵻�OK,ʧ���򷵻�ERROR
* Attention		 : ������Ĳ���������Ҫ���򷵻�ERROR
*******************************************************************************/
u8 SSTF016B_RdID(idtype IDType,u32* RcvbufPt)
{
	u32 temp = 0;
              
	if (IDType == Jedec_ID)
	{
		SPI_FLASH_CS_LOW();	
				
		Flash_ReadWriteByte(0x9F);		 		         /* ���Ͷ�JEDEC ID����(9Fh)	*/
    	        
        temp = (temp | Flash_ReadWriteByte(0x00)) << 8;  /* �������� */
		temp = (temp | Flash_ReadWriteByte(0x00)) << 8;	
        temp = (temp | Flash_ReadWriteByte(0x00)); 	     /* �ڱ�����,temp��ֵӦΪ0xBF2541 */

        SPI_FLASH_CS_HIGH();

		*RcvbufPt = temp;
		return (ENABLE);
	}
	
	if ((IDType == Manu_ID) || (IDType == Dev_ID) )
	{
	    SPI_FLASH_CS_LOW();	
		
		Flash_ReadWriteByte(0x90);				/* ���Ͷ�ID���� (90h or ABh) */
    	Flash_ReadWriteByte(0x00);				/* ���͵�ַ	*/
		Flash_ReadWriteByte(0x00);				/* ���͵�ַ	*/
		Flash_ReadWriteByte(IDType);		    /* ���͵�ַ - ����00H����01H */
		temp = Flash_ReadWriteByte(0x00);	    /* ���ջ�ȡ�������ֽ� */

        SPI_FLASH_CS_HIGH();

		*RcvbufPt = temp;
		return (ENABLE);
	}
	else
	{
		return (ERROR);	
	}
}


/*******************************************************************************
* Function Name  : SSTF016B_WR
* Description    : SST25VF016B��д��������д1���Ͷ�����ݵ�ָ����ַ
* Input          : - Dst: Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��
*                  - SndbufPt: ���ͻ�����ָ��
*                  - NByte: Ҫд�������ֽ���
* Output         : None
* Return         : �����ɹ��򷵻�OK,ʧ���򷵻�ERROR
* Attention		 : ��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
*******************************************************************************/
u8 SSTF016B_WR(u32 Dst, u8* SndbufPt,u32 NByte)
{
	u8 temp = 0,StatRgVal = 0;
	u32 i = 0;
	if (( (Dst+NByte-1 > MAX_ADDR)||(NByte == 0) ))
	{
		return (ERROR);	 /*	�����ڲ��� */
	}

	
	SPI_FLASH_CS_LOW();				 
	Flash_ReadWriteByte(0x05);							    /* ���Ͷ�״̬�Ĵ�������	*/
	temp = Flash_ReadWriteByte(0xFF);					    /* ������õ�״̬�Ĵ���ֵ */
	SPI_FLASH_CS_HIGH();								

	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x50);							    /* ʹ״̬�Ĵ�����д	*/
	SPI_FLASH_CS_HIGH();	
		
	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x01);							    /* ����д״̬�Ĵ���ָ�� */
	Flash_ReadWriteByte(0);								    /* ��0BPxλ��ʹFlashоƬȫ����д */
	SPI_FLASH_CS_HIGH();			
	
	for(i = 0; i < NByte; i++)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* ����дʹ������ */
		SPI_FLASH_CS_HIGH();			

		SPI_FLASH_CS_LOW();					
		Flash_ReadWriteByte(0x02); 						    /* �����ֽ�������д����	*/
		Flash_ReadWriteByte((((Dst+i) & 0xFFFFFF) >> 16));  /* ����3���ֽڵĵ�ַ��Ϣ */
		Flash_ReadWriteByte((((Dst+i) & 0xFFFF) >> 8));
		Flash_ReadWriteByte((Dst+i) & 0xFF);
		Flash_ReadWriteByte(SndbufPt[i]);					/* ���ͱ���д������	*/
		SPI_FLASH_CS_HIGH();			

		do
		{

		  SPI_FLASH_CS_LOW();					 
			Flash_ReadWriteByte(0x05);					    /* ���Ͷ�״̬�Ĵ������� */
			StatRgVal = Flash_ReadWriteByte(0xFF);			/* ������õ�״̬�Ĵ���ֵ */
			SPI_FLASH_CS_HIGH();							
  		}
		while (StatRgVal == 0x03 );		          /* һֱ�ȴ���ֱ��оƬ����	*/

	}

	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(0x06);							    /* ����дʹ������ */
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(0x50);							    /* ʹ״̬�Ĵ�����д	*/
	SPI_FLASH_CS_HIGH();
			
	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x01);							    /* ����д״̬�Ĵ���ָ�� */
	Flash_ReadWriteByte(temp);						     	/* �ָ�״̬�Ĵ���������Ϣ */
	SPI_FLASH_CS_HIGH();

	return (ENABLE);		
}


/*******************************************************************************
* Function Name  : SSTF016B_Erase
* Description    : ����ָ����������ѡȡ���Ч���㷨����
* Input          : - sec1: ��ʼ������,��Χ(0~511)
*                  - sec2: ��ֹ������,��Χ(0~511)
* Output         : None
* Return         : �����ɹ��򷵻�OK,ʧ���򷵻�ERROR
* Attention		 : None
*******************************************************************************/
u8 SSTF016B_Erase(u32 sec1, u32 sec2)
{
	u8  temp1 = 0,temp2 = 0,StatRgVal = 0;
  u32 SecnHdAddr = 0;	  			
	u32 no_SecsToEr = 0;				   			    /* Ҫ������������Ŀ */
	u32 CurSecToEr = 0;	  						    /* ��ǰҪ������������ */
	
	/*  �����ڲ��� */
	if ((sec1 > SEC_MAX)||(sec2 > SEC_MAX))	
	{
		return (ERROR);	
	}
   	
  SPI_FLASH_CS_LOW();			 
	Flash_ReadWriteByte(0x05);								/* ���Ͷ�״̬�Ĵ�������	*/
	temp1 = Flash_ReadWriteByte(0x00);						/* ������õ�״̬�Ĵ���ֵ */
	SPI_FLASH_CS_HIGH();								

	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x50);								/* ʹ״̬�Ĵ�����д	*/
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();								  	
	Flash_ReadWriteByte(0x01);								/* ����д״̬�Ĵ���ָ��	*/
	Flash_ReadWriteByte(0);									/* ��0BPxλ��ʹFlashоƬȫ����д */
	SPI_FLASH_CS_HIGH();
	
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x06);								/* ����дʹ������ */
	SPI_FLASH_CS_HIGH();			

	/* ����û��������ʼ�����Ŵ�����ֹ�����ţ������ڲ��������� */
	if (sec1 > sec2)
	{
	   temp2 = sec1;
	   sec1  = sec2;
	   sec2  = temp2;
	} 
	/* ����ֹ���������������������� */
	if (sec1 == sec2)	
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* ����дʹ������ */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * sec1;				          /* ������������ʼ��ַ	*/
	    SPI_FLASH_CS_LOW();	
    	Flash_ReadWriteByte(0x20);							  /* ������������ָ�� */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* ����3���ֽڵĵ�ַ��Ϣ */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* ���Ͷ�״̬�Ĵ������� */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* ������õ�״̬�Ĵ���ֵ	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);		              /* һֱ�ȴ���ֱ��оƬ����	*/
		return (ENABLE);			
	}
	
    /* ������ʼ��������ֹ��������������ٵĲ������� */	
	
	if (sec2 - sec1 == SEC_MAX)	
	{
		SPI_FLASH_CS_LOW();			
		Flash_ReadWriteByte(0x60);							  /* ����оƬ����ָ��(60h or C7h) */
		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* ���Ͷ�״̬�Ĵ������� */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* ������õ�״̬�Ĵ���ֵ	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* һֱ�ȴ���ֱ��оƬ����	*/
   		return (ENABLE);
	}
	
	no_SecsToEr = sec2 - sec1 +1;					          /* ��ȡҪ������������Ŀ */
	CurSecToEr  = sec1;								          /* ����ʼ������ʼ����	*/
	
	/* ����������֮��ļ���������ȡ8���������㷨 */
	while (no_SecsToEr >= 8)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* ����дʹ������ */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * CurSecToEr;			          /* ������������ʼ��ַ */
	    SPI_FLASH_CS_LOW();	
	    Flash_ReadWriteByte(0x52);							  /* ����32KB����ָ�� */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* ����3���ֽڵĵ�ַ��Ϣ */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* ���Ͷ�״̬�Ĵ������� */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* ������õ�״̬�Ĵ���ֵ	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* һֱ�ȴ���ֱ��оƬ����	*/
		CurSecToEr  += 8;
		no_SecsToEr -=  8;
	}
	/* �������������㷨����ʣ������� */
	while (no_SecsToEr >= 1)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* ����дʹ������ */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * CurSecToEr;			          /* ������������ʼ��ַ */
	    SPI_FLASH_CS_LOW();	
    	Flash_ReadWriteByte(0x20);							  /* ������������ָ�� */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* ����3���ֽڵĵ�ַ��Ϣ */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* ���Ͷ�״̬�Ĵ������� */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* ������õ�״̬�Ĵ���ֵ	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* һֱ�ȴ���ֱ��оƬ���� */
		CurSecToEr  += 1;
		no_SecsToEr -=  1;
	}
    /* ��������,�ָ�״̬�Ĵ�����Ϣ */
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x06);								  /* ����дʹ������ */
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x50);								  /* ʹ״̬�Ĵ�����д */
	SPI_FLASH_CS_HIGH();			
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x01);								  /* ����д״̬�Ĵ���ָ�� */
	Flash_ReadWriteByte(temp1);								  /* �ָ�״̬�Ĵ���������Ϣ */
	SPI_FLASH_CS_HIGH();    
	return (ENABLE);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_Test
* Description    : ��ȡSST25VF016B ID 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
0x00BF258E �鿴ChipID��ֵ�Ƿ�0xBF258E
*******************************************************************************/
u8 SPI_FLASH_Test(void)
{
    u32  ChipID = 0;
    u16  temp   = 0;
  	SSTF016B_RdID(Jedec_ID, &ChipID);                                   /*  �������е��˴�ʱ, ��Watch��*/

	ChipID &= ~0xff000000;						                        /*  ��������24λ����            */
	if (ChipID != 0x00BF2541)
  {											/*  ID����ȷ������ѭ��          */
     return (ERROR);
  }
	temp=(u16)(((ChipID>>8)&0x0000ff00)+(0x000000ff&ChipID));
	//���
	switch(temp)
	{	
//Winbond			
		case 0xEF17:		//W25Q128	   EF 17 16M  �ֽ�    0xF0 0000 
			MAX_ADDR = 0xF00000;
			break;
		case 0xEF16:		//W25Q64 	   EF 16 8M   �ֽ�    0x80 0000
			MAX_ADDR = 0x800000;
			break;
		case 0xEF15:		//W25Q32 	   EF 15 4M   �ֽ�    0x40 0000
			MAX_ADDR = 0x400000;
			break;
		case 0xEF14:		//W25Q16 	   EF 14 2M   �ֽ�    0x20 0000
			MAX_ADDR = 0x200000;
			break;
		case 0xEF13:		//W2580 EF 13           0x10 0000
			MAX_ADDR = 0x100000;
			break;  
		case 0xEF12:		//W2540 EF 12           0x08 0000
			MAX_ADDR = 0x80000;
			break; 			

//sst	

		case 0xBF4B:		//SST25VF064 BF 4B 8M   �ֽ�    0x80 0000
			MAX_ADDR = 0x800000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF4A:		//SST25VF032 BF 4A 4M   �ֽ�    0x40 0000
			MAX_ADDR = 0x400000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF41:		//SST25VF016 BF 41 2M   �ֽ�    0x20 0000
			MAX_ADDR = 0x200000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF8E:		//SST25VF080 BF 8E 1M   �ֽ�    0x10 0000
			MAX_ADDR = 0x100000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF8D:		//SST25VF040 BF 8D 512K �ֽ�    0x08 0000
			MAX_ADDR = 0x80000;
			//W25P_Write_StatusReg(0);
			break;
		default:
			MAX_ADDR = 0x80000;
			//W25P_Write_StatusReg(0);
		break;
	}
	return(ENABLE);
	//����
}


/* Private variables ---------------------------------------------------------*/
static u32 CurReadAddr;	/* ��ǰ���ĵ�ַ */
static u32 CurWriteAddr;	/* ��ǰдҳ��ַ	*/

/*******************************************************************************
* Function Name  : df_read_open
* Description    : ����ʼ�����ܺ���
* Input          : - addr: �򿪺�����ĳ�ʼ��ַ
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read_open(u32 addr)
{
  CurReadAddr=addr;	/* ��ǰ���ĵ�ַ	*/
}


/*******************************************************************************
* Function Name  : df_write_open
* Description    : д��ʼ�����ܺ���
* Input          : - addr: Ҫд�ĳ�ʼ��ַ
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write_open(u32 addr)
{
	CurWriteAddr=addr;	/* ��ǰд��ַ */
}

/*******************************************************************************
* Function Name  : df_read
* Description    : ��FLASH����
* Input          : - buf: �������ݵ�ָ��
*                  - size: ��ȡ���ݵĴ�С
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read(u8 *buf,u16 size)
{
  if( CurReadAddr + size <= MAX_ADDR )
  {
    SSTF016B_RD(CurReadAddr,buf,size);
    CurReadAddr+=size;
  }
}

/*******************************************************************************
* Function Name  : df_write
* Description    : дFLASH����
* Input          : - buf: д���ݵ�ָ��
*                  - size: Ҫд���ݵĴ�С
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write(u8 *buf,u16 size)
{
  if( CurWriteAddr + size <= MAX_ADDR )
  {
    SSTF016B_WR(CurWriteAddr,buf,size);
    CurWriteAddr+=size;
  }
}

/*******************************************************************************
* Function Name  : df_read_seek
* Description    : ������ȡFLASH�ĵ�ַ	
* Input          : - addr: �µĵ�ַ
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read_seek(u32 addr)
{
 df_read_close();
 df_read_open(addr);
}

/*******************************************************************************
* Function Name  : df_write_seek
* Description    : ����дFLASH�ĵ�ַ
* Input          : - addr: �µĵ�ַ
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write_seek(u32 addr)
{
 df_write_close();
 df_write_open(addr); 
}

/*******************************************************************************
* Function Name  : df_read_close
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read_close(void)
{
 /* �˴������κδ��� */
}

/*******************************************************************************
* Function Name  : df_write_close
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write_close(void)
{
}

/****************************End of file************************************/



/*******************************************************************************
�û�����
*******************************************************************************/
/*
����������Ϣ
*/
void Flash_addr_write(u32 s_addr,u16 s_sector)//���浱ǰflash д��ַ��������
{
	u8  f_addr[8];
	if(s_addr>4096*511)
	{
		s_addr=4096*511;
	}
	f_addr[0]=(s_addr&0xff000000)>>24;
	f_addr[1]=(s_addr&0x00ff0000)>>16;
	f_addr[2]=(s_addr&0x0000ff00)>>8;
	f_addr[3]=(s_addr&0x000000ff);
	if(s_sector>511)
	{
		s_sector=511;
	}
	f_addr[4]=0;
	f_addr[5]=0;
	f_addr[6]=(s_sector&0xff00)>>8;
	f_addr[7]=(s_sector&0x00ff);
	sst25_init();
	sst25_write(0x1ff000,f_addr,8); //д�뵽 ��511����
}

u32 Flash_addr_read(u32 r_addr)
{
	u32 temp=0;
	u8 f_r_addr[4];
	sst25_init();
	sst25_read(r_addr,f_r_addr,4);
	temp=f_r_addr[0];
	temp<<=8;
	temp+=f_r_addr[1];
	temp<<=8;
	temp+=f_r_addr[2];
	temp<<=8;
	temp+=f_r_addr[3];
	return(temp);
}	

/*
����������ݼ�¼
*/
u32 flash_addr;					//flash�洢��ַ
u16 sector;     				//������ַ 0--511 ��512��������ÿ������0x1000=4096�ֽ�
u8 curtime2[8];					//64λʱ������� 8�ֽ� FLASH
void Flash_save_Transaction(u32 add,u8 *buf,u8 length)
{
	static u8 seccout;
	u16 sector1;
	static u32 adress=0;  //��ַƫ����
		
		
//	flash_addr=flash_addr+length+8;//��8�ֽ�ʱ���
	sector1=flash_addr/0x1000;
	sst25_init();
	if(sector>=450)								//�������� ������ �� ʹ��450�����洢����450*4096/60/512=60��������
	{
		flash_addr=0;
		sector=0;
		add=0;
		SSTF016B_Erase(0,0);				//����������
	}
	if(sector1>sector)
	{
		sector=sector1;
		SSTF016B_Erase(sector,sector);			//����������
	}
	seccout++;
	sst25_write((add+adress),curtime2,8);		//дʱ���
	adress+=8;
	sst25_write((add+adress),buf,length);		//д�ɻ�����
	adress+=length;
	if(seccout>=7)									//ÿ��7������д�꣬��ַ����512 
	{
		LED3=0;
		flash_addr+=512;
		adress=0;
		seccout=0;
		SSTF016B_Erase(511,511);							//��500������� ��ǰ����FLASH��ַ��������
		Flash_addr_write(flash_addr,sector);  //����sst25 FLASH ��ǰд ��ַ 
//		sst25_write(add,buf,length);
		LED3=1;
	}
}

/****************************End of file************************************/


