/******************************************
**File Name  :  Flash.c
**Description:  子文件，flash存储
******************************************/
#include "stm32f10x.h"
#include "tlc2543.h"
#include "flash.h"
#include "MultiRotor_systime.H"
#include "led.h"
#include "usart.h"
#include "stm32_flash.h"

/* 添加程序 */
u32 MAX_ADDR=0x200000;//flash芯片的最大地址，读ID可得
/******************************************
**Function Name :  Write_Flash 
**Description   :  写flash 
**Input         :  要写入的flash首地址、写入的数据指针、写入的数据长度
**Return        ： void
******************************************/
void sst25_write(u32 flash_start_addr,u8* WriteBuffer,u16 size)
{
	df_write_open(flash_start_addr);    /* 打开要写的初始地址 */
	df_write((u8*)WriteBuffer,size); //将WriteBuffer指向的size个字节写入flash
	df_write_close();
//	delay1ms(20);
} 
/******************************************
**Function Name :  Read_Flash 
**Description   :  读flash 
**Input         :  要读出的flash首地址、读出的数据指针、读出的数据长度
**Return        ： void
******************************************/
void sst25_read(u32 flash_start_addr,u8* ReadBuffer,u16 size)
{
	df_read_open(flash_start_addr);
	df_read((u8*)ReadBuffer, size);
	df_read_close();
//	delay1ms(20);
}

/* 以下为移植程序 */


/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : 初始化控制SSI的管脚
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
* Description    : 通过硬件SPI发送一个字节到SST25VF016B
* Input          : - data: 发送的数据
* Output         : None
* Return         : SST25VF016B 返回的数据
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


/* 以下函数在移植时无需修改 */
/*******************************************************************************
* Function Name  : SSTF016B_RD
* Description    : SST25VF016B的读函数,可选择读ID和读数据操作
* Input          : - Dst: 目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
*                  - RcvBufPt: 接收缓存的指针
*                  - NByte: 要读取的数据字节数	
* Output         : 操作成功则返回OK,失败则返回ERROR
* Return         : SST25VF016B 返回的数据
* Attention		 : 若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
*******************************************************************************/
u8 SSTF016B_RD(u32 Dst, u8* RcvBufPt ,u32 NByte)
{
	u32 i = 0;
	if ((Dst+NByte > MAX_ADDR)||(NByte == 0))	return (ERROR);	 /*	检查入口参数 */
	
  SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(0x0B); 						/* 发送读命令 */
	Flash_ReadWriteByte(((Dst & 0xFFFFFF) >> 16));	/* 发送地址信息:该地址由3个字节组成	*/
	Flash_ReadWriteByte(((Dst & 0xFFFF) >> 8));
	Flash_ReadWriteByte(Dst & 0xFF);
	Flash_ReadWriteByte(0xFF);						/* 发送一个哑字节以读取数据	*/
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
* Description    : SST25VF016B的读ID函数,可选择读ID和读数据操作
* Input          : - IDType: ID类型。用户可在Jedec_ID,Dev_ID,Manu_ID三者里选择
* Output         : - RcvbufPt: 存储ID变量的指针
* Return         : 操作成功则返回OK,失败则返回ERROR
* Attention		 : 若填入的参数不符合要求，则返回ERROR
*******************************************************************************/
u8 SSTF016B_RdID(idtype IDType,u32* RcvbufPt)
{
	u32 temp = 0;
              
	if (IDType == Jedec_ID)
	{
		SPI_FLASH_CS_LOW();	
				
		Flash_ReadWriteByte(0x9F);		 		         /* 发送读JEDEC ID命令(9Fh)	*/
    	        
        temp = (temp | Flash_ReadWriteByte(0x00)) << 8;  /* 接收数据 */
		temp = (temp | Flash_ReadWriteByte(0x00)) << 8;	
        temp = (temp | Flash_ReadWriteByte(0x00)); 	     /* 在本例中,temp的值应为0xBF2541 */

        SPI_FLASH_CS_HIGH();

		*RcvbufPt = temp;
		return (ENABLE);
	}
	
	if ((IDType == Manu_ID) || (IDType == Dev_ID) )
	{
	    SPI_FLASH_CS_LOW();	
		
		Flash_ReadWriteByte(0x90);				/* 发送读ID命令 (90h or ABh) */
    	Flash_ReadWriteByte(0x00);				/* 发送地址	*/
		Flash_ReadWriteByte(0x00);				/* 发送地址	*/
		Flash_ReadWriteByte(IDType);		    /* 发送地址 - 不是00H就是01H */
		temp = Flash_ReadWriteByte(0x00);	    /* 接收获取的数据字节 */

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
* Description    : SST25VF016B的写函数，可写1个和多个数据到指定地址
* Input          : - Dst: 目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
*                  - SndbufPt: 发送缓存区指针
*                  - NByte: 要写的数据字节数
* Output         : None
* Return         : 操作成功则返回OK,失败则返回ERROR
* Attention		 : 若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
*******************************************************************************/
u8 SSTF016B_WR(u32 Dst, u8* SndbufPt,u32 NByte)
{
	u8 temp = 0,StatRgVal = 0;
	u32 i = 0;
	if (( (Dst+NByte-1 > MAX_ADDR)||(NByte == 0) ))
	{
		return (ERROR);	 /*	检查入口参数 */
	}

	
	SPI_FLASH_CS_LOW();				 
	Flash_ReadWriteByte(0x05);							    /* 发送读状态寄存器命令	*/
	temp = Flash_ReadWriteByte(0xFF);					    /* 保存读得的状态寄存器值 */
	SPI_FLASH_CS_HIGH();								

	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x50);							    /* 使状态寄存器可写	*/
	SPI_FLASH_CS_HIGH();	
		
	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x01);							    /* 发送写状态寄存器指令 */
	Flash_ReadWriteByte(0);								    /* 清0BPx位，使Flash芯片全区可写 */
	SPI_FLASH_CS_HIGH();			
	
	for(i = 0; i < NByte; i++)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* 发送写使能命令 */
		SPI_FLASH_CS_HIGH();			

		SPI_FLASH_CS_LOW();					
		Flash_ReadWriteByte(0x02); 						    /* 发送字节数据烧写命令	*/
		Flash_ReadWriteByte((((Dst+i) & 0xFFFFFF) >> 16));  /* 发送3个字节的地址信息 */
		Flash_ReadWriteByte((((Dst+i) & 0xFFFF) >> 8));
		Flash_ReadWriteByte((Dst+i) & 0xFF);
		Flash_ReadWriteByte(SndbufPt[i]);					/* 发送被烧写的数据	*/
		SPI_FLASH_CS_HIGH();			

		do
		{

		  SPI_FLASH_CS_LOW();					 
			Flash_ReadWriteByte(0x05);					    /* 发送读状态寄存器命令 */
			StatRgVal = Flash_ReadWriteByte(0xFF);			/* 保存读得的状态寄存器值 */
			SPI_FLASH_CS_HIGH();							
  		}
		while (StatRgVal == 0x03 );		          /* 一直等待，直到芯片空闲	*/

	}

	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(0x06);							    /* 发送写使能命令 */
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(0x50);							    /* 使状态寄存器可写	*/
	SPI_FLASH_CS_HIGH();
			
	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x01);							    /* 发送写状态寄存器指令 */
	Flash_ReadWriteByte(temp);						     	/* 恢复状态寄存器设置信息 */
	SPI_FLASH_CS_HIGH();

	return (ENABLE);		
}


/*******************************************************************************
* Function Name  : SSTF016B_Erase
* Description    : 根据指定的扇区号选取最高效的算法擦除
* Input          : - sec1: 起始扇区号,范围(0~511)
*                  - sec2: 终止扇区号,范围(0~511)
* Output         : None
* Return         : 操作成功则返回OK,失败则返回ERROR
* Attention		 : None
*******************************************************************************/
u8 SSTF016B_Erase(u32 sec1, u32 sec2)
{
	u8  temp1 = 0,temp2 = 0,StatRgVal = 0;
  u32 SecnHdAddr = 0;	  			
	u32 no_SecsToEr = 0;				   			    /* 要擦除的扇区数目 */
	u32 CurSecToEr = 0;	  						    /* 当前要擦除的扇区号 */
	
	/*  检查入口参数 */
	if ((sec1 > SEC_MAX)||(sec2 > SEC_MAX))	
	{
		return (ERROR);	
	}
   	
  SPI_FLASH_CS_LOW();			 
	Flash_ReadWriteByte(0x05);								/* 发送读状态寄存器命令	*/
	temp1 = Flash_ReadWriteByte(0x00);						/* 保存读得的状态寄存器值 */
	SPI_FLASH_CS_HIGH();								

	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x50);								/* 使状态寄存器可写	*/
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();								  	
	Flash_ReadWriteByte(0x01);								/* 发送写状态寄存器指令	*/
	Flash_ReadWriteByte(0);									/* 清0BPx位，使Flash芯片全区可写 */
	SPI_FLASH_CS_HIGH();
	
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x06);								/* 发送写使能命令 */
	SPI_FLASH_CS_HIGH();			

	/* 如果用户输入的起始扇区号大于终止扇区号，则在内部作出调整 */
	if (sec1 > sec2)
	{
	   temp2 = sec1;
	   sec1  = sec2;
	   sec2  = temp2;
	} 
	/* 若起止扇区号相等则擦除单个扇区 */
	if (sec1 == sec2)	
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* 发送写使能命令 */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * sec1;				          /* 计算扇区的起始地址	*/
	    SPI_FLASH_CS_LOW();	
    	Flash_ReadWriteByte(0x20);							  /* 发送扇区擦除指令 */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* 发送3个字节的地址信息 */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* 发送读状态寄存器命令 */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* 保存读得的状态寄存器值	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);		              /* 一直等待，直到芯片空闲	*/
		return (ENABLE);			
	}
	
    /* 根据起始扇区和终止扇区间距调用最快速的擦除功能 */	
	
	if (sec2 - sec1 == SEC_MAX)	
	{
		SPI_FLASH_CS_LOW();			
		Flash_ReadWriteByte(0x60);							  /* 发送芯片擦除指令(60h or C7h) */
		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* 发送读状态寄存器命令 */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* 保存读得的状态寄存器值	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* 一直等待，直到芯片空闲	*/
   		return (ENABLE);
	}
	
	no_SecsToEr = sec2 - sec1 +1;					          /* 获取要擦除的扇区数目 */
	CurSecToEr  = sec1;								          /* 从起始扇区开始擦除	*/
	
	/* 若两个扇区之间的间隔够大，则采取8扇区擦除算法 */
	while (no_SecsToEr >= 8)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* 发送写使能命令 */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * CurSecToEr;			          /* 计算扇区的起始地址 */
	    SPI_FLASH_CS_LOW();	
	    Flash_ReadWriteByte(0x52);							  /* 发送32KB擦除指令 */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* 发送3个字节的地址信息 */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* 发送读状态寄存器命令 */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* 保存读得的状态寄存器值	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* 一直等待，直到芯片空闲	*/
		CurSecToEr  += 8;
		no_SecsToEr -=  8;
	}
	/* 采用扇区擦除算法擦除剩余的扇区 */
	while (no_SecsToEr >= 1)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* 发送写使能命令 */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * CurSecToEr;			          /* 计算扇区的起始地址 */
	    SPI_FLASH_CS_LOW();	
    	Flash_ReadWriteByte(0x20);							  /* 发送扇区擦除指令 */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* 发送3个字节的地址信息 */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{

		  SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* 发送读状态寄存器命令 */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* 保存读得的状态寄存器值	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* 一直等待，直到芯片空闲 */
		CurSecToEr  += 1;
		no_SecsToEr -=  1;
	}
    /* 擦除结束,恢复状态寄存器信息 */
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x06);								  /* 发送写使能命令 */
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x50);								  /* 使状态寄存器可写 */
	SPI_FLASH_CS_HIGH();			
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x01);								  /* 发送写状态寄存器指令 */
	Flash_ReadWriteByte(temp1);								  /* 恢复状态寄存器设置信息 */
	SPI_FLASH_CS_HIGH();    
	return (ENABLE);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_Test
* Description    : 读取SST25VF016B ID 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
0x00BF258E 查看ChipID的值是否0xBF258E
*******************************************************************************/
u8 SPI_FLASH_Test(void)
{
    u32  ChipID = 0;
    u16  temp   = 0;
  	SSTF016B_RdID(Jedec_ID, &ChipID);                                   /*  单步运行到此处时, 在Watch里*/

	ChipID &= ~0xff000000;						                        /*  仅保留低24位数据            */
	if (ChipID != 0x00BF2541)
  {											/*  ID不正确进入死循环          */
     return (ERROR);
  }
	temp=(u16)(((ChipID>>8)&0x0000ff00)+(0x000000ff&ChipID));
	//添加
	switch(temp)
	{	
//Winbond			
		case 0xEF17:		//W25Q128	   EF 17 16M  字节    0xF0 0000 
			MAX_ADDR = 0xF00000;
			break;
		case 0xEF16:		//W25Q64 	   EF 16 8M   字节    0x80 0000
			MAX_ADDR = 0x800000;
			break;
		case 0xEF15:		//W25Q32 	   EF 15 4M   字节    0x40 0000
			MAX_ADDR = 0x400000;
			break;
		case 0xEF14:		//W25Q16 	   EF 14 2M   字节    0x20 0000
			MAX_ADDR = 0x200000;
			break;
		case 0xEF13:		//W2580 EF 13           0x10 0000
			MAX_ADDR = 0x100000;
			break;  
		case 0xEF12:		//W2540 EF 12           0x08 0000
			MAX_ADDR = 0x80000;
			break; 			

//sst	

		case 0xBF4B:		//SST25VF064 BF 4B 8M   字节    0x80 0000
			MAX_ADDR = 0x800000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF4A:		//SST25VF032 BF 4A 4M   字节    0x40 0000
			MAX_ADDR = 0x400000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF41:		//SST25VF016 BF 41 2M   字节    0x20 0000
			MAX_ADDR = 0x200000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF8E:		//SST25VF080 BF 8E 1M   字节    0x10 0000
			MAX_ADDR = 0x100000;
			//W25P_Write_StatusReg(0);
			break;
		case 0xBF8D:		//SST25VF040 BF 8D 512K 字节    0x08 0000
			MAX_ADDR = 0x80000;
			//W25P_Write_StatusReg(0);
			break;
		default:
			MAX_ADDR = 0x80000;
			//W25P_Write_StatusReg(0);
		break;
	}
	return(ENABLE);
	//结束
}


/* Private variables ---------------------------------------------------------*/
static u32 CurReadAddr;	/* 当前读的地址 */
static u32 CurWriteAddr;	/* 当前写页地址	*/

/*******************************************************************************
* Function Name  : df_read_open
* Description    : 读初始化功能函数
* Input          : - addr: 打开后读到的初始地址
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read_open(u32 addr)
{
  CurReadAddr=addr;	/* 当前读的地址	*/
}


/*******************************************************************************
* Function Name  : df_write_open
* Description    : 写初始化功能函数
* Input          : - addr: 要写的初始地址
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write_open(u32 addr)
{
	CurWriteAddr=addr;	/* 当前写地址 */
}

/*******************************************************************************
* Function Name  : df_read
* Description    : 读FLASH函数
* Input          : - buf: 接受数据的指针
*                  - size: 读取数据的大小
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
* Description    : 写FLASH函数
* Input          : - buf: 写数据的指针
*                  - size: 要写数据的大小
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
* Description    : 调整读取FLASH的地址	
* Input          : - addr: 新的地址
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
* Description    : 调整写FLASH的地址
* Input          : - addr: 新的地址
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
 /* 此处不做任何处理 */
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
用户函数
*******************************************************************************/
/*
保存配置信息
*/
void Flash_addr_write(u32 s_addr,u16 s_sector)//保存当前flash 写地址和扇区号
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
	sst25_write(0x1ff000,f_addr,8); //写入到 第511扇区
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
保存飞行数据记录
*/
u32 flash_addr;					//flash存储地址
u16 sector;     				//扇区地址 0--511 共512个扇区，每个扇区0x1000=4096字节
u8 curtime2[8];					//64位时间戳数组 8字节 FLASH
void Flash_save_Transaction(u32 add,u8 *buf,u8 length)
{
	static u8 seccout;
	u16 sector1;
	static u32 adress=0;  //地址偏移量
		
		
//	flash_addr=flash_addr+length+8;//加8字节时间戳
	sector1=flash_addr/0x1000;
	sst25_init();
	if(sector>=450)								//超出容量 扇区回 零 使用450扇区存储数据450*4096/60/512=60分钟数据
	{
		flash_addr=0;
		sector=0;
		add=0;
		SSTF016B_Erase(0,0);				//擦除新扇区
	}
	if(sector1>sector)
	{
		sector=sector1;
		SSTF016B_Erase(sector,sector);			//擦除新扇区
	}
	seccout++;
	sst25_write((add+adress),curtime2,8);		//写时间戳
	adress+=8;
	sst25_write((add+adress),buf,length);		//写飞机数据
	adress+=length;
	if(seccout>=7)									//每秒7条数据写完，地址增加512 
	{
		LED3=0;
		flash_addr+=512;
		adress=0;
		seccout=0;
		SSTF016B_Erase(511,511);							//第500扇区存放 当前数据FLASH地址和扇区号
		Flash_addr_write(flash_addr,sector);  //保存sst25 FLASH 当前写 地址 
//		sst25_write(add,buf,length);
		LED3=1;
	}
}

/****************************End of file************************************/


