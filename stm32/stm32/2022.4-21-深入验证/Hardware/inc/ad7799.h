#ifndef _AD7799_H
#define _AD7799_H
#include "stm32f10x.h"
#include "ange_systick.h"
#define delayms_ad7799 SysTick_delayms 
//定义启动AD7799的方式
#define Sofeware_SPI 0  
#define Hardware_SPI 1

/*-------------------软件SPI的AD7799宏定义-----------------------------------------------*/	
#if Sofeware_SPI   
#define  AD_RCC				 RCC_APB2Periph_GPIOB//AD7799的GPIO时钟
#define  AD_CS_PIN     GPIO_Pin_12 	//AD7799的片选引脚
#define  AD_CS_GPIO    GPIOB

#define  AD_DI_PIN     GPIO_Pin_15  	//AD7799的输入引脚
#define  AD_DI_GPIO    GPIOB

#define  AD_SCK_PIN    GPIO_Pin_13	//AD7799的时钟引脚
#define  AD_SCK_GPIO   GPIOB

#define  AD_DO_PIN     GPIO_Pin_14 	//AD7799的输出引脚
#define  AD_DO_GPIO    GPIOB
//#define  AD_CS_PIN     GPIO_Pin_14 	//AD7799的片选引脚
//#define  AD_CS_GPIO    GPIOB

//#define  AD_DI_PIN     GPIO_Pin_13  	//AD7799的输入引脚
//#define  AD_DI_GPIO    GPIOB

//#define  AD_SCK_PIN    GPIO_Pin_15	//AD7799的时钟引脚
//#define  AD_SCK_GPIO   GPIOB

//#define  AD_DO_PIN     GPIO_Pin_12 	//AD7799的输出引脚
//#define  AD_DO_GPIO    GPIOB

#define  AD_CS_0()	 GPIO_ResetBits(AD_CS_GPIO, AD_CS_PIN) 			 
#define  AD_CS_1()	 GPIO_SetBits(AD_CS_GPIO, AD_CS_PIN) 

#define  AD_DI_0()	 GPIO_ResetBits(AD_DI_GPIO, AD_DI_PIN) 			 
#define  AD_DI_1()	 GPIO_SetBits(AD_DI_GPIO, AD_DI_PIN) 

#define  AD_SCK_0()	 GPIO_ResetBits(AD_SCK_GPIO, AD_SCK_PIN) 			 
#define  AD_SCK_1()	 GPIO_SetBits(AD_SCK_GPIO, AD_SCK_PIN) 

#define  AD_DO     (GPIO_ReadInputDataBit(AD_DO_GPIO, AD_DO_PIN))

#define AD7799_CS_LOW  AD_CS_0()
#define AD7799_CS_HIGH  AD_CS_1()
#define ADC_RDY_DAT (AD_DO)
#endif
/*-------------------硬件SPI的AD7799宏定义-----------------------------------------------*/	
#if Hardware_SPI 
#define             AD7799_SPIx                               SPI2
#define             AD7799_SPI_APBxClock_FUN                  RCC_APB1PeriphClockCmd
#define             AD7799_SPI_CLK                            RCC_APB1Periph_SPI2
#define             AD7799_SPI_GPIO_APBxClock_FUN           	RCC_APB2PeriphClockCmd
#define							AD7799_SPI_GPIO_CLK												RCC_APB2Periph_GPIOB


#define             AD7799_SPI_SCK_PORT                       GPIOB   
#define             AD7799_SPI_SCK_PIN                        GPIO_Pin_13

#define             AD7799_SPI_MOSI_PORT                      GPIOB 
#define             AD7799_SPI_MOSI_PIN                       GPIO_Pin_15

#define             AD7799_SPI_MISO_PORT                      GPIOB 
#define             AD7799_SPI_MISO_PIN                       GPIO_Pin_14

#define             AD7799_SPI_CS_PORT                       	GPIOB
#define             AD7799_SPI_CS_PIN                        	GPIO_Pin_12

#define  AD_CS_0()	 GPIO_ResetBits(AD7799_SPI_CS_PORT, AD7799_SPI_CS_PIN) 			 
#define  AD_CS_1()	 GPIO_SetBits(AD7799_SPI_CS_PORT, AD7799_SPI_CS_PIN) 
#define  AD_DO     (GPIO_ReadInputDataBit(AD7799_SPI_MISO_PORT, AD7799_SPI_MISO_PIN))

#define AD7799_CS_LOW  AD_CS_0()
#define AD7799_CS_HIGH  AD_CS_1()
#endif

/*-------------------软硬件通用的寄存器地址-----------------------------------------------*/	
/*AD7799 Registers*/  //寄存器地址
#define AD7799_REG_COMM		0 /* Communications Register(WO, 8-bit) */ 
#define AD7799_REG_STAT	    0 /* Status Register	    (RO, 8-bit) */
#define AD7799_REG_MODE	    1 /* Mode Register	     	(RW, 16-bit */
#define AD7799_REG_CONF	    2 /* Configuration Register (RW, 16-bit)*/ //配置寄存器的地址
#define AD7799_REG_DATA	    3 /* Data Register	     	(RO, 16-/24-bit) */
#define AD7799_REG_ID	    4 /* ID Register	     	(RO, 8-bit) */
#define AD7799_REG_IO	    5 /* IO Register	     	(RO, 8-bit) */  //配置IO寄存器地址
#define AD7799_REG_OFFSET   6 /* Offset Register	    (RW, 24-bit */
#define AD7799_REG_FULLSALE	7 /* Full-Scale Register	(RW, 24-bit */

/* Communications Register Bit Designations (AD7799_REG_COMM) */ //通信寄存器值
#define AD7799_COMM_WEN		(1 << 7) 			/* Write Enable */
#define AD7799_COMM_WRITE	(0 << 6) 			/* Write Operation *///写使能
#define AD7799_COMM_READ    (1 << 6) 			/* Read Operation */ //读使能    				//读地址是在第六位，所以 左移6位
#define AD7799_COMM_ADDR(x)	(((x) & 0x7) << 3)	/* Register Address */  	//寄存器选择地址为3-5为，所以111左移3位
#define AD7799_COMM_CREAD	(1 << 2) 			/* Continuous Read of Data Register */ //连续读

/* Status Register Bit Designations (AD7799_REG_STAT) *///状态寄存器
#define AD7799_STAT_RDY		(1 << 7) /* Ready */  //转换完成
#define AD7799_STAT_ERR		(1 << 6) /* Error (Overrange, Underrange) */
#define AD7799_STAT_CH3		(1 << 2) /* Channel 3 */
#define AD7799_STAT_CH2		(1 << 1) /* Channel 2 */
#define AD7799_STAT_CH1		(1 << 0) /* Channel 1 */

/* Mode Register Bit Designations (AD7799_REG_MODE) */ 
#define AD7799_MODE_SEL(x)		(((x) & 0x7) << 13)	/* Operation Mode Select */ //AD7799的模式选择位（13-15位）
#define AD7799_MODE_PSW		(1 << 12)			/* Power Switch Control Bit */	
#define AD7799_MODE_RATE(x)		((x) & 0xF) 		/* Filter Update Rate Select *///更新速率

/* AD7799_MODE_SEL(x) options */  ///AD7799的模式
#define AD7799_MODE_CONT		 0 /* Continuous Conversion Mode *///连续转换模式
#define AD7799_MODE_SINGLE		1 /* Single Conversion Mode *///单次转换模式
#define AD7799_MODE_IDLE		 2 /* Idle Mode */ //空闲模式
#define AD7799_MODE_PWRDN		 3 /* Power-Down Mode *///下电模式
#define AD7799_MODE_CAL_INT_ZERO 4 /* Internal Zero-Scale Calibration *///校准
#define AD7799_MODE_CAL_INT_FULL 5 /* Internal Full-Scale Calibration */
#define AD7799_MODE_CAL_SYS_ZERO 6 /* System Zero-Scale Calibration */
#define AD7799_MODE_CAL_SYS_FULL 7 /* System Full-Scale Calibration */

/* Configuration Register Bit Designations (AD7799_REG_CONF) */
#define AD7799_CONF_BO_EN	  (1 << 13) 			/* Burnout Current Enable */
#define AD7799_CONF_UNIPOLAR(x)  ((x&0x1 )<< 12) 			/* Unipolar/Bipolar Enable *///单双极性选择1为单极性
#define AD7799_CONF_GAIN(x)	  (((x) & 0x7) << 8) 	/* Gain Select */  //增益选择位是配置寄存器的8-10位
#define AD7799_CONF_REFDET(x) (((x) & 0x1) << 5) 	/* Reference detect function */ //参考保护使能位为配置寄存器第5位
#define AD7799_CONF_BUF		  (1 << 4) 				/* Buffered Mode Enable */ 
#define AD7799_CONF_CHAN(x)	  ((x) & 0x7) 			/* Channel select */ //通道选择位为配置寄存器0-2位

/* AD7799_CONF_GAIN(x) options */
#define AD7799_GAIN_1       0
#define AD7799_GAIN_2       1
#define AD7799_GAIN_4       2
#define AD7799_GAIN_8       3
#define AD7799_GAIN_16      4
#define AD7799_GAIN_32      5
#define AD7799_GAIN_64      6
#define AD7799_GAIN_128     7

/* AD7799_CONF_REFDET(x) options */
#define AD7799_REFDET_ENA   1	
#define AD7799_REFDET_DIS   0

/* AD7799_CONF_CHAN(x) options */ //通道选择
#define AD7799_CH_AIN1P_AIN1M	0 /* AIN1(+) - AIN1(-) */
#define AD7799_CH_AIN2P_AIN2M	1 /* AIN2(+) - AIN2(-) */
#define AD7799_CH_AIN3P_AIN3M	2 /* AIN3(+) - AIN3(-) */
#define AD7799_CH_AIN1M_AIN1M	3 /* AIN1(-) - AIN1(-) */
#define AD7799_CH_AVDD_MONITOR	7 /* AVDD Monitor */

/* ID Register Bit Designations (AD7799_REG_ID) */
#define AD7799_ID			0x9
#define AD7799_ID_MASK		0xF  

/* IO (Excitation Current Sources) Register Bit Designations (AD7799_REG_IO) */
#define AD7799_IOEN			(1 << 6)
#define AD7799_IO1(x)		(((x) & 0x1) << 4)
#define AD7799_IO2(x)		(((x) & 0x1) << 5)

void AD7799_GPIO_Init(void);//AD7799引脚初始化
#if Hardware_SPI
void AD7799_DMA(void);
#endif
#if Sofeware_SPI   
void spi_ad7799_init(void);//使AD7799的管脚处于默认状态,软件模拟使用
#endif
void AD7799_Write(uint8_t *buf,uint8_t num);//向AD7799写数据
void AD7799_Read(uint8_t *buf,uint8_t num);//读AD7799数据
void AD7799_SetRegisterValue(uint8_t regAddress,uint32_t regValue,uint8_t size);//写AD7799寄存器
uint32_t AD7799_GetRegisterValue(uint8_t regAddress, uint8_t size);   //读AD7799寄存器
uint8_t AD7799_Init(void);//读AD7799的ID
void AD7799_Reset(void);//复位AD7799
uint8_t AD7799_Ready(void);//读状态寄存器中的RDY位
void AD7799_SetMode(uint16_t mode);//设置AD7799的模式
void AD7799_SetChannel(uint16_t channel);//挑选AD7799的通道位
void AD7799_SetGain(uint16_t gain);//设置AD7799增益
void AD7799_SetReference(uint16_t state);//启动或禁用参考保护功能
void AD7799_Calibrate(u8 t);//通道校准
void AD7799_Speed(u8 x); //速度配置
void AD7799_CReadMode(uint8_t CH);//启动连续读模式
uint16_t AD7799_CRead(void);//连续读模式
void AD7799_TUIRead(void);//退出连续读模式，但是不管用

uint32_t AD7799_SRead(void);//单次转换读模式的读取
void AD7799_REG_Init(uint8_t CH); //AD7799功能初始化

uint32_t readad1(void);//单次读AD7799函数

u16 readad16(void);//AD779916次滤波函数,16位的数据


//平均滤波全局变量
extern u8 average_b1;
extern double average_zhi1;
extern u8 average_b2;
extern double average_zhi2;
extern u8 average_b3;
extern double average_zhi3;
void average_lvbo(double x,u8 t);
//我的fir
extern u8 fir_b1;
extern u8 fir_b2;
extern u8 fir_b3;
double fir_lvbo(uint32_t,u8 t);
//我的iir
double iir_lvbo(double x);
//我的平均滤波加fir
extern u8 average_fir_fb;
extern double average_fir_zhi;
void average_fir_lvbo(double x);
///////////////////
void Non_Filter(uint32_t *AD);//无滤波
void Average_Filter(uint32_t *AD);//四次平均滤波
void FIR_Filter(uint32_t *AD);//FIR十阶滤波
void IIR_Filter(uint32_t *AD);//IIR二阶滤波

#endif
