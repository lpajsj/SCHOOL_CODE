/*********************************************************
**File Name  :  stm32_flash.c
**Author     :  ��ѧ��
**Version    :  V 1.0.0
**brief      �� V 3.5.0
**Date       :  2016/03/01
**Description:  �ڲ�flashʵ��
*********************************************************/
/***************************************************
����ı��˳�����£�
l. ���FLASH_CR��LOCK�Ƿ���������û�����Ƚ���
2. ���FLASH_SR�Ĵ�����BSYλ����ȷ��û���������ڽ��еı�̲���
3. ����FLASH_CR�Ĵ�����PGλΪ'1'
4. ��ָ���ĵ�ַд��Ҫ��̵İ���
5. �ȴ�BSYλ��Ϊ'0'
6. ����д��ĵ�ַ����֤����

STM32����ҳ��������:
����ͼ���Կ�����STM32��ҳ����˳��Ϊ��
l. ���FLASH_CR��LOCK�Ƿ���������û�����Ƚ���
2.  ���FLASH_SR�Ĵ�����BSYλ����ȷ��û���������ڽ��е��������
3.����FLASH_CR�Ĵ�����PERλΪ'1'
4.  ��FLASH_AR�Ĵ���ѡ��Ҫ������ҳ
5.  ����FLASH_CR�Ĵ�����STRTλΪ'1'
6. �ȴ�BSYλ��Ϊ'0'
7. ������������ҳ������֤
****************************************************/
#include "stm32f10x.h"
#include "stm32_flash.h"

void ID_write(u8 s_ID,u8 p_ID)
{
	u16 temp=0;
	temp=s_ID<<8;
	temp=temp+p_ID;
	STMFLASH_Unlock();
	STMFLASH_ErasePage(0x08030000);
	STMFLASH_WriteHalfWord(0x08030000, temp);
	STMFLASH_Lock();
}
	
u16 ID_read(u32 ID_addr)
{
	u16 temp=0;
	STMFLASH_Unlock();
	temp=STMFLASH_ReadHalfWord(ID_addr);
	STMFLASH_Lock();
	return(temp);
}	

//����STM32��FLASH
void STMFLASH_Unlock(void)
{
  FLASH->KEYR=FLASH_KEY1;//д���������.
  FLASH->KEYR=FLASH_KEY2;
}
//flash����
void STMFLASH_Lock(void)
{
  FLASH->CR|=1<<7;//����
}
//�õ�FLASH״̬
uint8_t STMFLASH_GetStatus(void)
{    
       uint32_t res;         
       res=FLASH->SR;
       if(res&(1<<0))return 1;     //æ
       else if(res&(1<<2))return 2;//��̴���
       else if(res&(1<<4))return 3;//д��������
       return 0;                   //�������
}
//�ȴ��������
//time:Ҫ��ʱ�ĳ���
//����ֵ:״̬.
uint8_t STMFLASH_WaitDone(uint16_t time)
{
       uint8_t res;
       do
       {
         IWDG_ReloadCounter();//ι��
              res=STMFLASH_GetStatus();
              if(res!=1)break;//��æ,����ȴ���,ֱ���˳�.delay_us(1);
               time--;             
        }while(time);
        if(time==0)res=0xff;//TIMEOUT
        return res;
}
//����ҳ
//paddr:ҳ��ַ
//����ֵ:ִ�����
uint8_t STMFLASH_ErasePage(uint32_t paddr)
{
       uint8_t res=0;
       res=STMFLASH_WaitDone(0X5FFF);//�ȴ��ϴβ�������,>20ms   
       if(res==0)
       {
              FLASH->CR|=1<<1;//ҳ����
              FLASH->AR=paddr;//����ҳ��ַ
              FLASH->CR|=1<<6;//��ʼ����           
              res=STMFLASH_WaitDone(0X5FFF);//�ȴ���������,>20ms 
              if(res!=1)//��æ
              {
                     FLASH->CR&=~(1<<1);//���ҳ������־.
              }
       }
       return res;
}
//��FLASHָ����ַд�����(�����ֽ�)
//faddr:ָ����ַ(�˵�ַ����Ϊ2�ı���!!)
//dat:Ҫд�������
//����ֵ:д������
uint8_t STMFLASH_WriteHalfWord(uint32_t faddr, uint16_t dat)
{
       uint8_t res;              
       res=STMFLASH_WaitDone(0XFF);    
       if(res==0)//OK
       {
              FLASH->CR|=1<<0;//���ʹ��
              *(vu16*)faddr=dat;//д������
              res=STMFLASH_WaitDone(0XFF);//�ȴ��������
              if(res!=1)//�����ɹ�
              {
                     FLASH->CR&=~(1<<0);//���PGλ.
              }
       }
       return res;
}
//��ȡָ����ַ�İ���(16λ����)
//faddr:����ַ
//����ֵ:��Ӧ����.
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr)
{
       return *(vu16*)faddr;
}
#if STM32_FLASH_WREN  //���ʹ����д  
//������д��
//WriteAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��  
void STMFLASH_Write_NoCheck(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite)  
{                                 
       uint16_t i;
       for(i=0;i<NumToWrite;i++)
       {
              STMFLASH_WriteHalfWord(WriteAddr,pBuffer[i]);
           WriteAddr+=2;//��ַ����2.
       } 
}
//��ָ����ַ��ʼд��ָ�����ȵ�����
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
//pBuffer:����ָ��
//NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //�ֽ�
#else
#define STM_SECTOR_SIZE      2048
#endif           
uint16_t STMFLASH_BUF[STM_SECTOR_SIZE/2];//�����2K�ֽ�
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite) 
{
       uint32_t secpos;        //������ַ
       uint16_t secoff;        //������ƫ�Ƶ�ַ(16λ�ּ���)
       uint16_t secremain; //������ʣ���ַ(16λ�ּ���)   
       uint16_t i;   
       uint32_t offaddr;   //ȥ��0X08000000��ĵ�ַ
       if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
       STMFLASH_Unlock();                                            //����
       offaddr=WriteAddr-STM32_FLASH_BASE;             //ʵ��ƫ�Ƶ�ַ.
       secpos=offaddr/STM_SECTOR_SIZE; //������ַ  0~127 for STM32F103RBT6
       secoff=(offaddr%STM_SECTOR_SIZE)/2;  //�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
       secremain=STM_SECTOR_SIZE/2-secoff;                //����ʣ��ռ��С  
       if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
       while(1)
       {    
              IWDG_ReloadCounter();//ι��
              STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
              for(i=0;i<secremain;i++)//У������
              {
                     if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����      
              }
              if(i<secremain)//��Ҫ����
              {
                     STMFLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_ASE);//�����������
                     for(i=0;i<secremain;i++) STMFLASH_BUF[i+secoff]=pBuffer[i];//����
					 //д����������                            
					 STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
 
              }
			  else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);
			  //д�Ѿ������˵�,ֱ��д������ʣ������.                              
              if(NumToWrite==secremain)break;//д�������
              else//д��δ����
              {
                     secpos++;                            //������ַ��1
                     secoff=0;                      //ƫ��λ��Ϊ0      
                   pBuffer+=secremain;    //ָ��ƫ��
                     WriteAddr+=secremain; //д��ַƫ��    
                   NumToWrite-=secremain;      //�ֽ�(16λ)���ݼ�
                     if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;
					//��һ����������д����
                     else secremain=NumToWrite;//��һ����������д����
              }    
       };   
       STMFLASH_Lock();//����
}
#endif
//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead)        
{
       uint16_t i;
       for(i=0;i<NumToRead;i++)
       {
              pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
              ReadAddr+=2;//ƫ��2���ֽ�.   
       }
}
/****************************End of file************************************/

