#include "ange_flash.h"
#include "ange_usart.h"
void ange_flash_write32(u32 adress,u32 *x,u32 number)
{
	u32 numpage,i;
	//要初始化值要不然不会进入循环，for循环先判断
	FLASH_Status flashstatus=FLASH_COMPLETE;
	//解锁
	FLASH_Unlock();
	//清除标志位
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
	//计算要擦除的页数
	numpage=4*number/ange_flash_size+1;
	//擦除页
	for(i=0;(i<numpage)&&(flashstatus==FLASH_COMPLETE);i++)
	{
		flashstatus=FLASH_ErasePage((u32)(adress+ange_flash_size*i));
	}
	//写入数据
	for(i=0;(i<number)&&(flashstatus==FLASH_COMPLETE);i++)
	{
		flashstatus=FLASH_ProgramWord((adress+4*i),*x);
		x++;
	}
	//
  FLASH_Lock();
}
//读取flash的内容，
/*
输入参量：
flash地址-
数组变量地址
读取的数量
*/
void ange_flash_read32(u32 adress,u32 *x,u32 number)
{
	u32 i;
	for(i=0;i<number;i++)
	{
		*x=*(u32*)(adress);
		x++;
		adress+=4;
	}
}
void ange_flash_write16(u32 adress,__IO u16 x[],u32 number)
{
	u32 numpage,i;
	//要初始化值要不然不会进入循环，for循环先判断
	FLASH_Status flashstatus=FLASH_COMPLETE;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
	numpage=2*number/ange_flash_size+1;
	for(i=0;(i<numpage)&&(flashstatus==FLASH_COMPLETE);i++)
	{
		flashstatus=FLASH_ErasePage((u32)(adress+ange_flash_size*i));
	}
	for(i=0;(i<number)&&(flashstatus==FLASH_COMPLETE);i++)
	{
		flashstatus=FLASH_ProgramHalfWord((adress+2*i),x[i]);
//		x++;
	}
  FLASH_Lock();
}
void ange_flash_read16(u32 adress,u16 *x,u32 number)
{
	u32 i;
	for(i=0;i<number;i++)
	{
		*x=*(u16*)(adress);
		x++;
		adress+=2;
	}
}
//读写保护
/*
  * @param  FLASH_Pages: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg For @b STM32_Low-density_devices: value between FLASH_WRProt_Pages0to3 and FLASH_WRProt_Pages28to31  
  *     @arg For @b STM32_Medium-density_devices: value between FLASH_WRProt_Pages0to3
  *       and FLASH_WRProt_Pages124to127
  *     @arg For @b STM32_High-density_devices: value between FLASH_WRProt_Pages0to1 and
  *       FLASH_WRProt_Pages60to61 or FLASH_WRProt_Pages62to255
  *     @arg For @b STM32_Connectivity_line_devices: value between FLASH_WRProt_Pages0to1 and
  *       FLASH_WRProt_Pages60to61 or FLASH_WRProt_Pages62to127    
  *     @arg For @b STM32_XL-density_devices: value between FLASH_WRProt_Pages0to1 and
  *       FLASH_WRProt_Pages60to61 or FLASH_WRProt_Pages62to511
  *     @arg FLASH_WRProt_AllPages
0是解除写保护，擦除选项字节会将RDP中写入0xA5从而解除读保护
*/
void ange_flash_writeprotect(uint32_t FLASH_Pages)
{
	FLASH_Unlock();
	//擦除选项字节,会将RDP中写入0xA5从而解除读保护
	FLASH_EraseOptionBytes();
	//使能写保护
	FLASH_EnableWriteProtection(FLASH_Pages);
	//软件复位
	NVIC_SystemReset();
}
/*
在运行这里时会自动解除写保护
*/
void ange_flash_readprotect(FunctionalState NewState)
{
	FLASH_Unlock();
	//擦除选项字节
	FLASH_EraseOptionBytes();
	//解除读保护会擦除所有flash数据
	FLASH_ReadOutProtection(NewState);
	//上电复位
}
//输出当前FLASH保护状态
void ange_flash_examine()
{
	if(FLASH_GetReadOutProtectionStatus()==SET)
		printf("芯片处于读保护\n");
	else
		printf("芯片无读保护");
	if(FLASH_GetWriteProtectionOptionByte()!=0xffffffff)
		printf("芯片处于写保护");
		else
		printf("芯片无写保护");
}





