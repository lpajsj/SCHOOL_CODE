#include "ad7799.h"
#include "ange_usart.h"
#include "ange_systick.h"
#include "stdio.h"
#if Sofeware_SPI
void Delay_ms(uint32_t ms) //���뼶��ʱ����
{
	uint32_t i;
	SysTick_Config(72000);
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//�ر�ϵͳ��ʱ��
}
void AD7799_GPIO_Init(void)//AD7799���ų�ʼ��
{
	RCC_APB2PeriphClockCmd(AD_RCC,ENABLE);//����GPIO��ʱ��
	
	GPIO_InitTypeDef AD7799_GPIO_InitStruction;
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//����CSΪ�������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_CS_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_CS_GPIO,&AD7799_GPIO_InitStruction);
	
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//����DIΪ�������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_DI_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_DI_GPIO,&AD7799_GPIO_InitStruction);
	
	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;//����SCKΪ�������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_SCK_PIN;
	AD7799_GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(AD_SCK_GPIO,&AD7799_GPIO_InitStruction);	

	AD7799_GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����DOΪ��������
	AD7799_GPIO_InitStruction.GPIO_Pin=AD_DO_PIN;
	GPIO_Init(AD_SCK_GPIO,&AD7799_GPIO_InitStruction);	
}
/*****************************************************************************************************
���ã�ʹAD7799�ĹܽŴ���Ĭ��״̬
˵����ʹ��AD7799ǰҪ��CS���㣬DI��1
*****************************************************************************************************/
void spi_ad7799_init(void)
{
	AD_CS_0();
	AD_DI_1();
	AD_SCK_1();
	Delay_ms(10);
}
/*****************************************************************************************************
���ã���AD7799д����
������*buf-Ҫд����������飬num-Ҫд������ݸ���
˵����AD7799һ�ν���һ�ֽڣ��ߵ�ƽ�������ݣ��͵�ƽҪ�������ȶ������ȷ��͸�λ
*****************************************************************************************************/
void AD7799_Write(uint8_t *buf,uint8_t num)
{
	uint8_t dat;
	uint8_t i,j;
	
	AD_SCK_1();
	__nop();
//	AD_CS_1();  ��д�����в���Ҫ��CS�Ĳ���
//	__nop();
//	AD_CS_0();
	__nop();
	
	for(j=0;j<num;j++)
	{
		dat=*(buf+j);
		for(i=0;i<8;i++)
		{
			AD_SCK_0();
			if(0x80 == (dat & 0x80))
			AD_DI_1();
			else
			AD_DI_0();
			__nop();
			AD_SCK_1();
			__nop();
			dat<<=1;
		}
	}
//	AD_CS_1();//�ر�Ƭѡ�������
}
/*****************************************************************************************************
���ã���AD7799����
������*buf-�������ݵĴ�����飬num-Ҫ�������ݸ���
˵����AD7799�͵�ƽ������ݣ��ߵ�ƽ�ȶ����ݣ��ȶ�ȡ��λ
*****************************************************************************************************/
void AD7799_Read(uint8_t *buf,uint8_t num)//��AD7799����
{
	uint8_t dat=0,temp=0;
	
	uint8_t i,j;	
	
	AD_SCK_1();
	__nop();
//	AD_CS_1();
//	__nop();
//	AD_CS_0();	
	
	for(j=0;j<num;j++)
	{
		for(i=0;i<8;i++)
		{
			AD_SCK_0();
			dat<<=1;//ע�����Ʒ�ǰ��
			temp=AD_DO;
			if(temp==1)
				dat|=1;			
			AD_SCK_1();
			__nop();
		}
		*(buf+j)=dat;
	}
//	AD_CS_1();	
}
/*****************************************************************************************************
���ã�дAD7799�Ĵ���
������regAddress-�Ĵ�����ַ��regValue-д������ݣ�size-д������ݵ��ֽ���
˵������AD7799д�Ĵ���������Ҫ��дͨ�żĴ�����д��ͨ�żĴ��������ݾ���Ҫд��ļĴ���
*****************************************************************************************************/
void AD7799_SetRegisterValue(uint8_t regAddress,uint32_t regValue,uint8_t size)//дAD7799�Ĵ���
{
	uint8_t data[5]={0};//30
	data[0]=data[0] = AD7799_COMM_WRITE |  AD7799_COMM_ADDR(regAddress);//ͨ�żĴ���������
	if(size==1)
	{
		data[1] = (uint8_t)regValue;
	}
	else if(size == 2)
	{
		data[1] = (uint8_t)((regValue&0x00ff00)>>8);
		data[2] = (uint8_t)(regValue&0x0000ff);
	}
	else
	{
		data[1] = (uint8_t)((regValue & 0xFF0000) >> 16);	
		data[2] = (uint8_t)((regValue & 0x00FF00) >> 8);
    data[3] = (uint8_t)((regValue & 0x0000FF) >> 0);    	
	}
	AD_CS_1();
	AD_CS_0();
	AD7799_Write(data,size+1);//��ΪҪ��дͨ�żĴ���������д�������+1
	AD_CS_1();
}	
/*****************************************************************************************************
���ã���AD7799�Ĵ���
������regAddress-�Ĵ�����ַ��size-��ȡ�����ݵ��ֽ���
˵������AD7799д�Ĵ���������Ҫ��дͨ�żĴ�����д��ͨ�żĴ��������ݾ���Ҫ��ȡ�ļĴ���
*****************************************************************************************************/
uint32_t AD7799_GetRegisterValue(uint8_t regAddress, uint8_t size)   //��AD7799�Ĵ���
{
	uint8_t corresspond_data=0;//ͨ�żĴ�������
	uint8_t data[4]={0};//����������
	uint32_t receivedData = 0x00;//��󷵻ص�����
	corresspond_data = AD7799_COMM_READ |  AD7799_COMM_ADDR(regAddress);
	
	AD_CS_1();
	AD_CS_0();	
	AD7799_Write(&corresspond_data,1);//1.��дͨ�żĴ���
	AD7799_Read(data,size);//2.���Ĵ�����ֵ
	AD_CS_1();////////////////////////
	
	if(size == 1)
	{
		receivedData = data[0];
	}
	else if(size == 2)
	{
		receivedData |= (data[0] << 8);
		receivedData |= (data[1] << 0);
	}
	else
	{
		receivedData |= (data[0] << 16);
		receivedData |= (data[1] << 8);
		receivedData |= (data[2] << 0);
	}
	 return receivedData;
}
/*****************************************************************************************************
���ã���AD7799��ID
˵����AD7799��IDΪ0xx9
����ֵ�������0xx9���򷵻�success�����򷵻�ERROR
*****************************************************************************************************/
uint8_t AD7799_Init(void)//��AD7799��ID
{
	uint8_t status = 0x1;
	uint8_t ID;
	ID=AD7799_GetRegisterValue(AD7799_REG_ID,1);
	printf("%d\r\n",ID);
	if((ID&0x0f)!=AD7799_ID)
		status= 0x0;
	return status;
}
/*****************************************************************************************************
���ã���λAD7799
˵��������32λ��1��λAD7799
*****************************************************************************************************/
void AD7799_Reset(void)//��λAD7799
{
	uint8_t dataToSend[4] = {0xff, 0xff, 0xff, 0xff};
	AD_CS_1();
	AD_CS_0();		
	AD7799_Write(dataToSend,4);
	AD_CS_1();
}
/*****************************************************************************************************
���ã���״̬�Ĵ����е�RDYλ
˵�������RDYΪ1����ת��δ��ɣ�RDYΪ0����ת�����
����ֵ��ת�����-1��ת��δ���-0
*****************************************************************************************************/
uint8_t AD7799_Ready(void)//��״̬�Ĵ����е�RDYλ
{
	uint8_t rdy = 0;
	rdy=(AD7799_GetRegisterValue( AD7799_REG_STAT,1) & 0x80);   
	return(!rdy);
}
/*****************************************************************************************************
���ã�����AD7799��ģʽ
������mode-ģʽ�Ĵ�����MD2 MD1 MD0��13-15λ����ѡ��ģʽ
*****************************************************************************************************/
void AD7799_SetMode(uint16_t mode)//����AD7799��ģʽ
{
	uint16_t command;
	command = AD7799_GetRegisterValue(AD7799_REG_MODE,2);//��ȡԭ��ģʽ�Ĵ���������
	command &= ~AD7799_MODE_SEL(0xFF);//����13-15λ���㣬��λ���ֲ���
	command |= AD7799_MODE_SEL(mode);//����13-15λ��ΪҪд���ģʽ
  AD7799_SetRegisterValue(AD7799_REG_MODE, command,2);//д��ģʽ�Ĵ���	
}
/*****************************************************************************************************
���ã���ѡAD7799��ͨ��λ
������channel-���üĴ�����HD2 HD1 HD0��0-2λ��
*****************************************************************************************************/
void AD7799_SetChannel(uint16_t channel)//��ѡAD7799��ͨ��λ
{
   uint16_t command;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//��ȡ���üĴ����������ֽڵ�����
    command &= ~AD7799_CONF_CHAN(0xFF);//����0-2λ���㣬��λ���ֲ���
    command |= AD7799_CONF_CHAN(channel);////����0-2λ��ΪҪд���ͨ��
    AD7799_SetRegisterValue(AD7799_REG_CONF, command,2);//д�����üĴ���
}
/*****************************************************************************************************
���ã�����AD7799����
������gain-���üĴ�����G2 G1 G0��8-10λ��
˵������Ӧ�ķŴ����ο��ֲ�
*****************************************************************************************************/
void AD7799_SetGain(uint16_t gain)//����AD7799����
{
    uint16_t command;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//��ȡ���üĴ����������ֽڵ�����
    command &= ~AD7799_CONF_GAIN(0xFF);//����8-10λ������ѡ��λ�����㣬��λ���ֲ���
    command |= AD7799_CONF_GAIN(gain);//����8-10λ������ѡ��λ����ΪҪ�Ŵ������
    AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);//д�����üĴ��� 
}
/*****************************************************************************************************
���ã���������òο���������
������state-1-������state-0-�ر�
˵�������ο���ѹ��·����С��0.5Vʱ��״̬�Ĵ�����NOREF����ָʾ��
*****************************************************************************************************/
void AD7799_SetReference(uint16_t state)//��������òο���������
{
    uint16_t command = 0;
    command = AD7799_GetRegisterValue(AD7799_REG_CONF,2);//��ȡ���üĴ����������ֽڵ�����
    command &= ~AD7799_CONF_REFDET(1);//����5λ���ο�����ʹ��λ�����㣬����λ���ֲ���
    command |= AD7799_CONF_REFDET(state);//����5λ���ο�����ʹ��λ����Ϊ�������ֹ״̬
    AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);//д�����üĴ���			
}

void AD7799_REG_Init() //���üĴ��������ջٵ��� ��˫���� ����ģʽ
{
	u16 command=0;
		////psw��һ����Դ
	AD7799_Reset();
	command|=AD7799_MODE_PSW;
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
	command=AD7799_GetRegisterValue(AD7799_REG_CONF,2);
	//�ջٵ����������ԣ����屣��
	command&=~(AD7799_CONF_BO_EN|AD7799_CONF_UNIPOLAR(1)|AD7799_CONF_BUF);
	command|=(AD7799_CONF_BO_EN|AD7799_CONF_UNIPOLAR(1)|AD7799_CONF_BUF);
	AD7799_SetRegisterValue(AD7799_REG_CONF,command,2);
	//�����ο���������
	AD7799_SetReference(1);
	 //�ɼ��ٶ�����
	AD7799_Speed(10);
	 //AD7799��������
	AD7799_SetGain(AD7799_GAIN_1); 
	 //AD7799ͨ��У׼
	AD7799_Calibrate(0);
	AD7799_Calibrate(1);
	AD7799_Calibrate(2);   
	AD7799_SetChannel(2);
	//ģʽ���ã�����ת��ģʽ
	AD7799_SetMode(AD7799_MODE_CONT); 
}
//ͨ��У׼
void AD7799_Calibrate(u8 t)//ͨ��У׼
{
	u16 command,x;
	x=AD7799_GetRegisterValue(AD7799_REG_MODE,2);
	Delay_ms(5);////////////////////
	AD7799_SetChannel(t);
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(4);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);Delay_ms(5);//ѡ��ת������Ϊ16.7HZ���򿪵�Դ���أ��ڲ���̶�У��
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(5);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);Delay_ms(5);//ѡ��ת������Ϊ16.7HZ���򿪵�Դ���أ��ڲ����̶�У��
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(6);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);Delay_ms(5);//ѡ��ת������Ϊ16.7HZ���򿪵�Դ���أ�ϵͳ��̶�У��
	command=x;
	command&=~(AD7799_MODE_SEL(0XFF));
	command|=AD7799_MODE_SEL(7);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);Delay_ms(5);//ѡ��ת������Ϊ16.7HZ���򿪵�Դ���أ�ϵͳ���̶�У��
	AD7799_SetRegisterValue(AD7799_REG_IO,0,1);//����ͨ��3 Ϊad����
}
void AD7799_Speed(u8 x) //16.7hz��10
{
	u16 command;
	command=AD7799_GetRegisterValue(AD7799_REG_MODE,2);
	command&=~AD7799_MODE_RATE(0xff);
	command|=AD7799_MODE_RATE(x);
	AD7799_SetRegisterValue(AD7799_REG_MODE,command,2);
}
#endif
/********************
ƽ���˲�����ʹ��ʱ
xΪ����ֵ yΪ���ֵ
average_lvbo(x);
if(average_b)
{
	average_b=0;
	y=average_zhi;
}
************************/
#define average_cishu 10
double average_sum=0;
u8 average_b=0;
u16 average_jishu=0;
double average_zhi;
void average_lvbo(double x)
{
	average_sum+=x;
	average_jishu++;
	if(average_jishu==average_cishu)
	{
		average_zhi=average_sum/average_cishu;
		average_b=1;
		average_jishu=0;
		average_sum=0;
	}
}
/********************
fir �˲�
����ֵ��Ϊ�˲�ֵ
���ڸտ�ʼ���ݸ����޷����㣬�����ñ�־λfir_b�ж�,�����ص�ǰ�յ�����ƽ��ֵ
*****************/
#define fir_cishu 16
double fir_jilu[fir_cishu];
u8 fir_jishu=0;
u8 fir_b=0;
double fir_lvbo(double x)
{
	u8 i;
	double sum=0;
	fir_jilu[fir_jishu]=x;
	fir_jishu++;
	if(fir_jishu==fir_cishu)
	{
		fir_jishu=0;
		fir_b=1;
	}
	if(fir_b==1)
	{
		for(i=0;i<fir_cishu;i++)
		{
			sum+=fir_jilu[i];
		}
		return sum/fir_cishu;
	}
	else
	{
		for(i=0;i<fir_jishu;i++)
		{
			sum+=fir_jilu[i];
		}
		return sum/fir_jishu;
	}
}
/******************
iir�˲� ����ֵ�����˲����
****************/
double iir_jilu;
u8 iir_b=0;
double iir_lvbo(double x)
{
	if(iir_b==0)
	{
		iir_b=1;
	  iir_jilu=x;
		return x;
	}
	else
	{
		iir_jilu=iir_jilu/2+x/2;
		return iir_jilu;
	}
}
/*******************
ƽ���˲�+fir ʹ��ʱ
average_fir_lvbo(x);
if(average_fir_fb)
{
average_fir_fb=0;
//ȡֵ
y=average_fir_zhi;
}
*********************/
#define average_fir_acishu 16  //ƽ������
#define average_fir_fcishu 4  //fir����
double average_fir_asum=0;    //ƽ���ͱ���
double average_fir_fjilu[average_fir_fcishu]; //ÿ�ε�ƽ��ֵ��¼����Ϊfir�˲���ֵ
u8 average_fir_ab=0;  //��һ�����ݸ����ﵽ��־
u16 average_fir_ajishu=0; ///ƽ����������
u8 average_fir_fb=0;   //fir�����ﵽ��־������Ϊ�����жϱ�־
u16 average_fir_fjishu=0; //fir��������
double average_fir_zhi;  //����firֵ
void average_fir_lvbo(double x)
{
	u8 i;
	double sum=0;
	average_fir_asum+=x; //ƽ��ֵ���
	average_fir_ajishu++; //ƽ��������һ
	if(average_fir_ab==0)
	{
	if(average_fir_ajishu==average_fir_acishu) //����ƽ������
	{
		average_fir_ajishu=0;  //ƽ����������
		average_fir_fjilu[average_fir_fjishu]=average_fir_asum/average_fir_acishu; //��ƽ��ֵ��¼
		average_fir_fjishu++;  //fir���ݼ���+1  
		average_fir_asum=0;   //ƽ��������
		if(average_fir_fjishu==average_fir_fcishu)  //����fir���ݸ���
		{
			average_fir_fjishu=0;   //fir��������
			for(i=0;i<average_fir_fcishu;i++)
			{
				sum+=average_fir_fjilu[i];   //��fir����֮��
			}
			average_fir_zhi=sum/average_fir_fcishu;  //�����������
			average_fir_fb=1;  //��һ�������ݸ��±�־λ
			average_fir_ab=1;
		}
	}
  }
	else if(average_fir_ab==1)
	{
	if(average_fir_ajishu==average_fir_acishu) //����ƽ������
	{
		average_fir_ajishu=0;  //ƽ����������
		average_fir_fjilu[average_fir_fjishu]=average_fir_asum/average_fir_acishu; //��ƽ��ֵ��¼
		average_fir_fjishu++;  //fir���ݼ���+1  
		average_fir_asum=0;   //ƽ��������
		if(average_fir_fjishu==average_fir_fcishu)  //����fir���ݸ���
		{
			average_fir_fjishu=0;   //fir��������
		}
			for(i=0;i<average_fir_fcishu;i++)
			{
				sum+=average_fir_fjilu[i];   //��fir����֮��
			}
			average_fir_zhi=sum/average_fir_fcishu;  //�����������
			average_fir_fb=1;  //��һ�������ݸ��±�־λ
	}
	}
}
/**************************************************************************************
���ã����˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
***************************************************************************************/
void Non_Filter(uint32_t *AD)//���˲�
{
	static double ADD_AD=0;
	ADD_AD=*AD;
	ADD_AD=ADD_AD*5/16777215;
	printf("���˲�%.16f\n",ADD_AD);
}
/*****************************************************************************************************
���ã��Ĵ�ƽ���˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
*****************************************************************************************************/
void Average_Filter(uint32_t *AD)//�Ĵ�ƽ���˲�
{
	static uint8_t times=0;
	static double ADD_AD=0;
	times++;
	ADD_AD=ADD_AD+(*AD);
	if(times==4)
	{
		times=0;
		ADD_AD=ADD_AD*5/16777215/4;
		printf("ƽ���˲�%.16f\n",ADD_AD);
		ADD_AD=0;
	}
}
/**************************************************************************************
���ã�FIRʮ���˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
FIRFilter_Flag ��һ�ε�ʮ�����ݲ�������11�����ݿ�ʼ����ı�־λ
FIR_times ���մ���
�����������˳�FIR�˲���ǵ�����
***************************************************************************************/
FunctionalState FIRFilter_Flag=DISABLE;
uint8_t FIR_times=0;
void FIR_Filter(uint32_t *AD)//FIRʮ���˲�
{
	
	static uint32_t FIR_Buf[10]={0};
	static double ADD_AD=0;
	
	FIR_Buf[FIR_times]=*AD;
	FIR_times++;
	
	if((FIR_times==10)&&(FIRFilter_Flag==DISABLE))
	{
		FIR_times=0;
		FIRFilter_Flag=ENABLE;
	}
	else if(FIRFilter_Flag==ENABLE)
	{
		ADD_AD=FIR_Buf[0]+FIR_Buf[1]+FIR_Buf[2]+FIR_Buf[3]+FIR_Buf[4]+FIR_Buf[5]+FIR_Buf[6]+FIR_Buf[7]+FIR_Buf[8]+FIR_Buf[9];
		ADD_AD=ADD_AD*5/16777215/10;
		printf("FIR�˲�%.16f\n",ADD_AD);
		if(FIR_times==10)
			FIR_times=0;
	}
}
/**************************************************************************************
���ã�IIR�����˲�
������*AD-��ȡ��AD7799��ֵ
˵����ʹ��double���Ծ�ȷ��С�����15λ����ѹ��ΧΪ0-5V
IIR_ADD_AD ��ȡ��ת��ֵ֮��
IIR_times ���մ���
�����������˳�IIR�˲���ǵ�����
***************************************************************************************/
double IIR_ADD_AD=0;
uint8_t IIR_times=0;
void IIR_Filter(uint32_t *AD)//IIR�����˲�
{
	static double ADToVolitage=0;
	if(IIR_times<2)
	{
		IIR_times++;
		IIR_ADD_AD=IIR_ADD_AD+(*AD);
	}
	else if(IIR_times==2)
	{
		IIR_times++;
		IIR_ADD_AD=IIR_ADD_AD/2;
		IIR_ADD_AD=(IIR_ADD_AD+(*AD))/2; //??????
		ADToVolitage=IIR_ADD_AD*5/16777215;
		printf("IIR�˲���%.16f\n",ADToVolitage);
	}
	else
	{
		IIR_ADD_AD=(IIR_ADD_AD+(*AD))/2;
		ADToVolitage=IIR_ADD_AD*5/16777215;
		printf("IIR�˲���%.16f\n",ADToVolitage);
	}
	
}
