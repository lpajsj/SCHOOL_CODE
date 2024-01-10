#include "stm32f10x.h"
#include "tlc2543.h"
#include "flash.h"

/*************************TLC2543**************************************/
void TLC2543_INIT(void)  
{  
    SPI_InitTypeDef  SPI_InitStructure;  
//    /* SPI1 configuration ???SPI??????TLC2543????*/  
		SPI_TLC2543_CS_HIGH();
	
    SPI_Cmd(SPI1, DISABLE);                                                 //?????,????MODE  
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      //?????  
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                           //?  
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;                      //16?  
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                              //???????????  
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                            //?????????????  
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               //??NSS,?????????  
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;    //128??  
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      //????  
	
    SPI_Init(SPI1, &SPI_InitStructure);  
    SPI_Cmd(SPI1, ENABLE);  
		 
}  
u8 Read_TLC2543(u16 chan)  
{  
    u8 ADCdata1;
		u16 i,ADCdata;  
    chan <<=12;  
    chan|=0x0C;   
		SPI_FLASH_CS_HIGH();
    SPI_TLC2543_CS_LOW();                            //??CS????  
    for(i=0;i<500;i++);                                                  //????,??????????  
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);   
    SPI_I2S_SendData(SPI1,chan);                                            //??????,???????????    
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET) ;    
    ADCdata=SPI_I2S_ReceiveData(SPI1);   
    for(i=0;i<500;i++);   
    ADCdata>>=4;                                                          //??????16?,????0  
    SPI_TLC2543_CS_HIGH();                              //CS?   
      
    //???????,?????????????????,?????????????????????  
    SPI_TLC2543_CS_LOW();                            //??CS????  
    for(i=0;i<500;i++);                                                  //????,??????????  
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);   
    SPI_I2S_SendData(SPI1,chan);                                            //??????,???????????    
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET) ;    
    ADCdata=SPI_I2S_ReceiveData(SPI1);   
    for(i=0;i<500;i++);   
    ADCdata>>=4;                                                          //??????16?,????0  
    SPI_TLC2543_CS_HIGH();  
		ADCdata1=ADCdata>>4;
    return ADCdata1;  
} 

