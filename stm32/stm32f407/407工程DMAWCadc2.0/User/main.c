#include "stm32f4xx.h"
#include "main.h"
#include "ange_SysTick.h"
#include "ange_USART.h"
#include "ange_rcc.h"
#include "ange_exti.h"
#include "ange_dma.h"
#include "ange_ad.h"
uint8_t Buffercmp( uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength);
 uint32_t aSRC_Const_Buffer[32]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
u32 shuju[32];
u8 us[ange_DMA_CW_BufferSize]="12345678123456781234567812345678";
#define led PAout(4)
extern u16 adc1zhi11;
u16 adcduo1[5];																	
float adcduo[5];
	
int main(void)
{
	u16 i;
	  HSI_SetSysClock(16,336,2,7);
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

		/*������������Ϊ2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		ange_USART_init(115200);
		printf("yyds");
		/*���赽�洢��ʵ��*/
		ange_DMA_WC_ADCConfig(adcduo1); //��Ҫ����˳��1
		ange_ADC_init();                //��Ҫ����˳��2
		
		led=0;
  while (1)
  {
		for(i=0;i<5;i++)
		{
			printf("%dͨ��:%f\n",i,(float)adcduo1[i]/4095*3.3);
		}
		SysTick_delayms(1000);
  }
}
void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(ange_EXTI_Line)!=RESET)
	{
		EXTI_ClearITPendingBit(ange_EXTI_Line); //EXTI_Line0
		led=!led;
		printf("yyds");
	}
}
uint8_t Buffercmp(uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* ���ݳ��ȵݼ� */
  while(BufferLength--)
  {
    /* �ж���������Դ�Ƿ��Ӧ��� */
    if(*pBuffer != *pBuffer1)
    {
      /* ��Ӧ����Դ����������˳�������������0 */
      return 0;
    }
    /* ������������Դ�ĵ�ַָ�� */
    pBuffer++;
    pBuffer1++;
  }
  /* ����жϲ��Ҷ�Ӧ������� */
  return 1;  
}
