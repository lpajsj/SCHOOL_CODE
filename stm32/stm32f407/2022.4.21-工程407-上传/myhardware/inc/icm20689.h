#ifndef _MPU9250_H
#define _MPU9250_H
#include "stm32f4xx.h"
#define Delay_ms_icm20689 SysTick_delayms
#define Delay_us_icm20689 SysTick_delayus
#define SPI2_ReadWriteByte ange_SPI2_sendbyte
#define M_PI  (float)3.1415926535
//an添加的spi驱动

// 定义MPU9250内部地址
/***************************************************/
#define MPU9250_RA_PWR_MGMT_1       0x6B//电源管理1 典型值为0x00 正常启用
#define MPU9250_RA_SMPLRT_DIV       0x19 //陀螺仪采样率，典型值：0x07(125Hz) 1000/(1+7)=125HZ
#define MPU9250_RA_ACCEL_CONFIG     0x1C //加速计自检、测量范围及高通滤波频率，0X18 正负16g，典型值：0x01(不自检，2G，5Hz)
#define MPU9250_RA_GYRO_CONFIG      0x1B //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)

#define MPU9250_RA_CONFIG           0x1A //低通滤波频率，典型值：0x06(5Hz)
#define MPU9250_RA_ACCEL_CONFIG_2   0x1D //加速度计低通滤波器 0X06(5hz)
#define MPU9250_RA_WHO_AM_I         0x75//器件ID (默认数值0x71,只读)//IIC地址寄存器(默认数值0x68，只读)

//--------------------i2c slv0-------------------------------//
#define MPU9250_RA_I2C_SLV0_REG     0x26//
#define MPU9250_RA_I2C_SLV0_ADDR    0x25//
#define MPU9250_RA_I2C_SLV0_DO      0x63//output reg

//--------------------9axis  reg addr-----------------------//
//加速度计
#define MPU9250_RA_ACCEL_XOUT_H     0x3B//加速度的X轴高位
#define MPU9250_RA_ACCEL_XOUT_L     0x3C//加速度的X轴低位
#define MPU9250_RA_ACCEL_YOUT_H     0x3D
#define MPU9250_RA_ACCEL_YOUT_L     0x3E
#define MPU9250_RA_ACCEL_ZOUT_H     0x3F
#define MPU9250_RA_ACCEL_ZOUT_L     0x40

//温度
#define MPU9250_RA_TEMP_OUT_H       0x41//温度计输出数据
#define MPU9250_RA_TEMP_OUT_L       0x42

#define MPU9250_RA_GYRO_XOUT_H      0x43//陀螺仪的X轴高位
#define MPU9250_RA_GYRO_XOUT_L      0x44//陀螺仪的X轴低位
#define MPU9250_RA_GYRO_YOUT_H      0x45
#define MPU9250_RA_GYRO_YOUT_L      0x46
#define MPU9250_RA_GYRO_ZOUT_H      0x47
#define MPU9250_RA_GYRO_ZOUT_L      0x48

//磁力计
#define MPU9250_RA_MAG_XOUT_L		0x03//磁力计的X轴低位
#define MPU9250_RA_MAG_XOUT_H		0x04//磁力计的X轴高位
#define MPU9250_RA_MAG_YOUT_L		0x05
#define MPU9250_RA_MAG_YOUT_H		0x06
#define MPU9250_RA_MAG_ZOUT_L		0x07
#define MPU9250_RA_MAG_ZOUT_H		0x08

/**********************Init SLV0 i2c**********************************/
#define MPU9250_RA_INT_PIN_CFG         0x37// 
#define MPU9250_RA_I2C_MST_CTRL        0x24//
#define MPU9250_RA_USER_CTRL           0x6A//用户配置当为0X10时使用SPI模式
#define MPU9250_RA_I2C_MST_DELAY_CTRL  0x67//
#define MPU9250_RA_I2C_SLV0_CTRL       0x27//

/**********************参数设置**********************************/
#define MPU9250_WHOAMI          0x71//ID值
#define MPU9250_MODE_RESET      0x80//设置电源激活复位 
#define MPU9250_MODE_SLEEP      0x40//进入睡眠模式
#define MPU_CLK_SEL_AUTO		0x01

//陀螺仪设置速度值
#define MPU9250_GYRO_RATE_8000       0//gyro_rate =  8000hz
#define MPU9250_GYRO_RATE_4000       1//gyro_rate =  4000hz
#define MPU9250_GYRO_RATE_2000       3//gyro_rate =  2000hz
#define MPU9250_GYRO_RATE_1600       4//gyro_rate =  1600hz
#define MPU9250_GYRO_RATE_1000       7//gyro_rate =  1000hz
#define MPU9250_GYRO_RATE_800        9//gyro_rate =   800hz
#define MPU9250_GYRO_RATE_500       15//gyro_rate =   500hz

//陀螺仪设置范围
#define MPU9250_GYRO_RANGE_2000     0X18//gyro_range =  2000°/s
#define MPU9250_GYRO_RANGE_1000     0X10//gyro_range =  1000°/s
#define MPU9250_GYRO_RANGE_500      0X08//gyro_range =   500°/s
#define MPU9250_GYRO_RANGE_250      0X00//gyro_range =   250°/s

//陀螺仪灵敏度
#define MPU9250_GYRO_SENS_2000      16.4//2000灵敏度
#define MPU9250_GYRO_SENS_1000      32.8//1000灵敏度
#define MPU9250_GYRO_SENS_500       65.5// 500灵敏度
#define MPU9250_GYRO_SENS_250        131// 250灵敏度

//加速度计设置速度值
#define MPU9250_ACC_RATE_1130       0x00//acc_rate = 1130hz
#define MPU9250_ACC_RATE_460        0x08//acc_rate =  460hz
#define MPU9250_ACC_RATE_184        0x09//acc_rate =  184hz
#define MPU9250_ACC_RATE_92         0x0A//acc_rate =   92hz
#define MPU9250_ACC_RATE_41         0x0B//acc_rate =   41hz
#define MPU9250_ACC_RATE_20         0x0C//acc_rate =   20hz
#define MPU9250_ACC_RATE_10         0x0D//acc_rate =   10hz
#define MPU9250_ACC_RATE_5          0x0F//acc_rate =    5hz

//加速度计设置范围
#define MPU9250_ACC_RANGE_16g     0X18//gyro_range = ±16g
#define MPU9250_ACC_RANGE_8g      0X10//gyro_range =  ±8g
#define MPU9250_ACC_RANGE_4g      0X08//gyro_range =  ±4g
#define MPU9250_ACC_RANGE_2g      0X00//gyro_range =  ±2g

//加速度计灵敏度
#define MPU9250_ACC_SENS_16g      2.048//16g灵敏度
#define MPU9250_ACC_SENS_8g       4.096// 8g灵敏度
#define MPU9250_ACC_SENS_4g       8.192// 4g灵敏度
#define MPU9250_ACC_SENS_2g      16.384// 2g灵敏度

//--------------------AK8963 reg addr------------------------//
#define MPU9250_AK8963_ADDR 0x0C//AKM addr
#define AK8963_WHOAMI_REG   0x00//AKM ID addr
#define AK8963_WHOAMI_ID    0x48//ID
#define AK8963_ST1_REG      0x02  //Data Status1
#define AK8963_ST2_REG      0x09  //Data reading end register & check Magnetic sensor overflow occurred
#define AK8963_ST1_DOR      0x02
#define AK8963_ST1_DRDY     0x01 //Data Ready
#define AK8963_ST2_BITM     0x10
#define AK8963_ST2_HOFL     0x08 // Magnetic sensor overflow 
#define AK8963_CNTL1_REG    0x0A
#define AK8963_CNTL2_REG    0x0B
#define AK8963_CNTL2_SRST   0x01 //soft Reset
#define AK8963_ASAX         0x10 //X轴灵敏度调整值//X-axis sensitivity adjustment value 
#define AK8963_ASAY         0x11 //Y轴灵敏度调整值//Y-axis sensitivity adjustment value
#define AK8963_ASAZ         0x12 //Z轴灵敏度调整值//Z-axis sensitivity adjustment value

//--------------------other reg addr-----------------------//
#define MPU9250_RA_EXT_SENS_DATA_00 0x49 //MPU9250 IIC???????????00
#define MPU9250_RA_EXT_SENS_DATA_01 0x4A //MPU9250 IIC???????????01
#define MPU9250_RA_EXT_SENS_DATA_02 0x4B //MPU9250 IIC???????????02
#define MPU9250_RA_EXT_SENS_DATA_03 0x4C //MPU9250 IIC???????????03

/************Reg ***********************/
#define MPU9250_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU9250_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU9250_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU9250_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
#define MPU9250_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
#define MPU9250_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
#define MPU9250_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define MPU9250_RA_XA_OFFS_L_TC     0x07
#define MPU9250_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define MPU9250_RA_YA_OFFS_L_TC     0x09
#define MPU9250_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define MPU9250_RA_ZA_OFFS_L_TC     0x0B
#define MPU9250_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define MPU9250_RA_XG_OFFS_USRL     0x14
#define MPU9250_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define MPU9250_RA_YG_OFFS_USRL     0x16
#define MPU9250_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define MPU9250_RA_ZG_OFFS_USRL     0x18
#define MPU9250_RA_LP_ACCEL_ODR     0x1E
#define MPU9250_RA_MOT_THR          0x1F
#define MPU9250_RA_MOT_DUR          0x20
#define MPU9250_RA_ZRMOT_THR        0x21
#define MPU9250_RA_ZRMOT_DUR        0x22
#define MPU9250_RA_FIFO_EN          0x23
#define MPU9250_RA_I2C_SLV1_ADDR    0x28
#define MPU9250_RA_I2C_SLV1_REG     0x29
#define MPU9250_RA_I2C_SLV1_CTRL    0x2A
#define MPU9250_RA_I2C_SLV2_ADDR    0x2B
#define MPU9250_RA_I2C_SLV2_REG     0x2C
#define MPU9250_RA_I2C_SLV2_CTRL    0x2D
#define MPU9250_RA_I2C_SLV3_ADDR    0x2E
#define MPU9250_RA_I2C_SLV3_REG     0x2F
#define MPU9250_RA_I2C_SLV3_CTRL    0x30
#define MPU9250_RA_I2C_SLV4_ADDR    0x31
#define MPU9250_RA_I2C_SLV4_REG     0x32
#define MPU9250_RA_I2C_SLV4_DO      0x33
#define MPU9250_RA_I2C_SLV4_CTRL    0x34
#define MPU9250_RA_I2C_SLV4_DI      0x35
#define MPU9250_RA_I2C_MST_STATUS   0x36
#define MPU9250_RA_INT_ENABLE       0x38
#define MPU9250_RA_DMP_INT_STATUS   0x39
#define MPU9250_RA_INT_STATUS       0x3A

#define MPU9250_RA_EXT_SENS_DATA_04 0x4D
#define MPU9250_RA_EXT_SENS_DATA_05 0x4E
#define MPU9250_RA_EXT_SENS_DATA_06 0x4F
#define MPU9250_RA_EXT_SENS_DATA_07 0x50
#define MPU9250_RA_EXT_SENS_DATA_08 0x51
#define MPU9250_RA_EXT_SENS_DATA_09 0x52
#define MPU9250_RA_EXT_SENS_DATA_10 0x53
#define MPU9250_RA_EXT_SENS_DATA_11 0x54
#define MPU9250_RA_EXT_SENS_DATA_12 0x55
#define MPU9250_RA_EXT_SENS_DATA_13 0x56
#define MPU9250_RA_EXT_SENS_DATA_14 0x57
#define MPU9250_RA_EXT_SENS_DATA_15 0x58
#define MPU9250_RA_EXT_SENS_DATA_16 0x59
#define MPU9250_RA_EXT_SENS_DATA_17 0x5A
#define MPU9250_RA_EXT_SENS_DATA_18 0x5B
#define MPU9250_RA_EXT_SENS_DATA_19 0x5C
#define MPU9250_RA_EXT_SENS_DATA_20 0x5D
#define MPU9250_RA_EXT_SENS_DATA_21 0x5E
#define MPU9250_RA_EXT_SENS_DATA_22 0x5F
#define MPU9250_RA_EXT_SENS_DATA_23 0x60
#define MPU9250_RA_MOT_DETECT_STATUS    0x61
#define MPU9250_RA_I2C_SLV1_DO          0x64
#define MPU9250_RA_I2C_SLV2_DO          0x65
#define MPU9250_RA_I2C_SLV3_DO          0x66
#define MPU9250_RA_SIGNAL_PATH_RESET    0x68//I2C的地址
#define MPU9250_RA_MOT_DETECT_CTRL      0x69

#define MPU9250_RA_PWR_MGMT_2           0x6C//电源管理2 典型值为0x00
#define MPU9250_RA_BANK_SEL             0x6D
#define MPU9250_RA_MEM_START_ADDR       0x6E
#define MPU9250_RA_MEM_R_W              0x6F
#define MPU9250_RA_DMP_CFG_1            0x70
#define MPU9250_RA_DMP_CFG_2            0x71
#define MPU9250_RA_FIFO_COUNTH          0x72
#define MPU9250_RA_FIFO_COUNTL          0x73
#define MPU9250_RA_FIFO_R_W             0x74

#define MPU9250_TC_PWR_MODE_BIT     7
#define MPU9250_TC_OFFSET_BIT       6
#define MPU9250_TC_OFFSET_LENGTH    6
#define MPU9250_TC_OTP_BNK_VLD_BIT  0

#define MPU9250_VDDIO_LEVEL_VLOGIC  0
#define MPU9250_VDDIO_LEVEL_VDD     1

#define MPU9250_CFG_EXT_SYNC_SET_BIT    5
#define MPU9250_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU9250_CFG_DLPF_CFG_BIT        2
#define MPU9250_CFG_DLPF_CFG_LENGTH     3

#define MPU9250_EXT_SYNC_DISABLED       0x0
#define MPU9250_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU9250_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU9250_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU9250_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU9250_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU9250_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU9250_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU9250_DLPF_BW_256         0x00
#define MPU9250_DLPF_BW_188         0x01
#define MPU9250_DLPF_BW_98          0x02
#define MPU9250_DLPF_BW_42          0x03
#define MPU9250_DLPF_BW_20          0x04
#define MPU9250_DLPF_BW_10          0x05
#define MPU9250_DLPF_BW_5           0x06

#define MPU9250_GCONFIG_FS_SEL_BIT      4
#define MPU9250_GCONFIG_FS_SEL_LENGTH   2

#define MPU9250_GYRO_FS_250         0x00
#define MPU9250_GYRO_FS_500         0x01
#define MPU9250_GYRO_FS_1000        0x02
#define MPU9250_GYRO_FS_2000        0x03

#define MPU9250_ACONFIG_XA_ST_BIT           7
#define MPU9250_ACONFIG_YA_ST_BIT           6
#define MPU9250_ACONFIG_ZA_ST_BIT           5
#define MPU9250_ACONFIG_AFS_SEL_BIT         4
#define MPU9250_ACONFIG_AFS_SEL_LENGTH      2
#define MPU9250_ACONFIG_ACCEL_HPF_BIT       2
#define MPU9250_ACONFIG_ACCEL_HPF_LENGTH    3

#define MPU9250_ACCEL_FS_2          0x00
#define MPU9250_ACCEL_FS_4          0x01
#define MPU9250_ACCEL_FS_8          0x02
#define MPU9250_ACCEL_FS_16         0x03

#define MPU9250_DHPF_RESET          0x00
#define MPU9250_DHPF_5              0x01
#define MPU9250_DHPF_2P5            0x02
#define MPU9250_DHPF_1P25           0x03
#define MPU9250_DHPF_0P63           0x04
#define MPU9250_DHPF_HOLD           0x07

#define MPU9250_TEMP_FIFO_EN_BIT    7
#define MPU9250_XG_FIFO_EN_BIT      6
#define MPU9250_YG_FIFO_EN_BIT      5
#define MPU9250_ZG_FIFO_EN_BIT      4
#define MPU9250_ACCEL_FIFO_EN_BIT   3
#define MPU9250_SLV2_FIFO_EN_BIT    2
#define MPU9250_SLV1_FIFO_EN_BIT    1
#define MPU9250_SLV0_FIFO_EN_BIT    0

#define MPU9250_MULT_MST_EN_BIT     7
#define MPU9250_WAIT_FOR_ES_BIT     6
#define MPU9250_SLV_3_FIFO_EN_BIT   5
#define MPU9250_I2C_MST_P_NSR_BIT   4
#define MPU9250_I2C_MST_CLK_BIT     3
#define MPU9250_I2C_MST_CLK_LENGTH  4

#define MPU9250_CLOCK_DIV_348       0x0
#define MPU9250_CLOCK_DIV_333       0x1
#define MPU9250_CLOCK_DIV_320       0x2
#define MPU9250_CLOCK_DIV_308       0x3
#define MPU9250_CLOCK_DIV_296       0x4
#define MPU9250_CLOCK_DIV_286       0x5
#define MPU9250_CLOCK_DIV_276       0x6
#define MPU9250_CLOCK_DIV_267       0x7
#define MPU9250_CLOCK_DIV_258       0x8
#define MPU9250_CLOCK_DIV_500       0x9
#define MPU9250_CLOCK_DIV_471       0xA
#define MPU9250_CLOCK_DIV_444       0xB
#define MPU9250_CLOCK_DIV_421       0xC
#define MPU9250_CLOCK_DIV_400       0xD
#define MPU9250_CLOCK_DIV_381       0xE
#define MPU9250_CLOCK_DIV_364       0xF

#define MPU9250_I2C_SLV_RW_BIT      7
#define MPU9250_I2C_SLV_ADDR_BIT    6
#define MPU9250_I2C_SLV_ADDR_LENGTH 7
#define MPU9250_I2C_SLV_EN_BIT      7
#define MPU9250_I2C_SLV_BYTE_SW_BIT 6
#define MPU9250_I2C_SLV_REG_DIS_BIT 5
#define MPU9250_I2C_SLV_GRP_BIT     4
#define MPU9250_I2C_SLV_LEN_BIT     3
#define MPU9250_I2C_SLV_LEN_LENGTH  4

#define MPU9250_I2C_SLV4_RW_BIT         7
#define MPU9250_I2C_SLV4_ADDR_BIT       6
#define MPU9250_I2C_SLV4_ADDR_LENGTH    7
#define MPU9250_I2C_SLV4_EN_BIT         7
#define MPU9250_I2C_SLV4_INT_EN_BIT     6
#define MPU9250_I2C_SLV4_REG_DIS_BIT    5
#define MPU9250_I2C_SLV4_MST_DLY_BIT    4
#define MPU9250_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU9250_MST_PASS_THROUGH_BIT    7
#define MPU9250_MST_I2C_SLV4_DONE_BIT   6
#define MPU9250_MST_I2C_LOST_ARB_BIT    5
#define MPU9250_MST_I2C_SLV4_NACK_BIT   4
#define MPU9250_MST_I2C_SLV3_NACK_BIT   3
#define MPU9250_MST_I2C_SLV2_NACK_BIT   2
#define MPU9250_MST_I2C_SLV1_NACK_BIT   1
#define MPU9250_MST_I2C_SLV0_NACK_BIT   0

#define MPU9250_INTCFG_INT_LEVEL_BIT        7
#define MPU9250_INTCFG_INT_OPEN_BIT         6
#define MPU9250_INTCFG_LATCH_INT_EN_BIT     5
#define MPU9250_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU9250_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU9250_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU9250_INTCFG_I2C_BYPASS_EN_BIT    1
#define MPU9250_INTCFG_CLKOUT_EN_BIT        0

#define MPU9250_INTMODE_ACTIVEHIGH  0x00
#define MPU9250_INTMODE_ACTIVELOW   0x01

#define MPU9250_INTDRV_PUSHPULL     0x00
#define MPU9250_INTDRV_OPENDRAIN    0x01

#define MPU9250_INTLATCH_50USPULSE  0x00
#define MPU9250_INTLATCH_WAITCLEAR  0x01

#define MPU9250_INTCLEAR_STATUSREAD 0x00
#define MPU9250_INTCLEAR_ANYREAD    0x01

#define MPU9250_INTERRUPT_FF_BIT            7
#define MPU9250_INTERRUPT_MOT_BIT           6
#define MPU9250_INTERRUPT_ZMOT_BIT          5
#define MPU9250_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU9250_INTERRUPT_I2C_MST_INT_BIT   3
#define MPU9250_INTERRUPT_PLL_RDY_INT_BIT   2
#define MPU9250_INTERRUPT_DMP_INT_BIT       1
#define MPU9250_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU9250_DMPINT_5_BIT            5
#define MPU9250_DMPINT_4_BIT            4
#define MPU9250_DMPINT_3_BIT            3
#define MPU9250_DMPINT_2_BIT            2
#define MPU9250_DMPINT_1_BIT            1
#define MPU9250_DMPINT_0_BIT            0

#define MPU9250_MOTION_MOT_XNEG_BIT     7
#define MPU9250_MOTION_MOT_XPOS_BIT     6
#define MPU9250_MOTION_MOT_YNEG_BIT     5
#define MPU9250_MOTION_MOT_YPOS_BIT     4
#define MPU9250_MOTION_MOT_ZNEG_BIT     3
#define MPU9250_MOTION_MOT_ZPOS_BIT     2
#define MPU9250_MOTION_MOT_ZRMOT_BIT    0

#define MPU9250_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU9250_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU9250_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU9250_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU9250_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU9250_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU9250_PATHRESET_GYRO_RESET_BIT    2
#define MPU9250_PATHRESET_ACCEL_RESET_BIT   1
#define MPU9250_PATHRESET_TEMP_RESET_BIT    0

#define MPU9250_DETECT_ACCEL_ON_DELAY_BIT       5
#define MPU9250_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define MPU9250_DETECT_FF_COUNT_BIT             3
#define MPU9250_DETECT_FF_COUNT_LENGTH          2
#define MPU9250_DETECT_MOT_COUNT_BIT            1
#define MPU9250_DETECT_MOT_COUNT_LENGTH         2

#define MPU9250_DETECT_DECREMENT_RESET  0x0
#define MPU9250_DETECT_DECREMENT_1      0x1
#define MPU9250_DETECT_DECREMENT_2      0x2
#define MPU9250_DETECT_DECREMENT_4      0x3

#define MPU9250_USERCTRL_DMP_EN_BIT             7
#define MPU9250_USERCTRL_FIFO_EN_BIT            6
#define MPU9250_USERCTRL_I2C_MST_EN_BIT         5
#define MPU9250_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU9250_USERCTRL_DMP_RESET_BIT          3
#define MPU9250_USERCTRL_FIFO_RESET_BIT         2
#define MPU9250_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU9250_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU9250_PWR1_DEVICE_RESET_BIT   7
#define MPU9250_PWR1_SLEEP_BIT          6
#define MPU9250_PWR1_CYCLE_BIT          5
#define MPU9250_PWR1_TEMP_DIS_BIT       3
#define MPU9250_PWR1_CLKSEL_BIT         2
#define MPU9250_PWR1_CLKSEL_LENGTH      3

#define MPU9250_CLOCK_INTERNAL          0x00
#define MPU9250_CLOCK_PLL_XGYRO         0x01
#define MPU9250_CLOCK_PLL_YGYRO         0x02
#define MPU9250_CLOCK_PLL_ZGYRO         0x03
#define MPU9250_CLOCK_PLL_EXT32K        0x04
#define MPU9250_CLOCK_PLL_EXT19M        0x05
#define MPU9250_CLOCK_KEEP_RESET        0x07

#define MPU9250_PWR2_LP_WAKE_CTRL_BIT       7
#define MPU9250_PWR2_LP_WAKE_CTRL_LENGTH    2
#define MPU9250_PWR2_STBY_XA_BIT            5
#define MPU9250_PWR2_STBY_YA_BIT            4
#define MPU9250_PWR2_STBY_ZA_BIT            3
#define MPU9250_PWR2_STBY_XG_BIT            2
#define MPU9250_PWR2_STBY_YG_BIT            1
#define MPU9250_PWR2_STBY_ZG_BIT            0

#define MPU9250_WAKE_FREQ_1P25      0x0
#define MPU9250_WAKE_FREQ_2P5       0x1
#define MPU9250_WAKE_FREQ_5         0x2
#define MPU9250_WAKE_FREQ_10        0x3

#define MPU9250_BANKSEL_PRFTCH_EN_BIT       6
#define MPU9250_BANKSEL_CFG_USER_BANK_BIT   5
#define MPU9250_BANKSEL_MEM_SEL_BIT         4
#define MPU9250_BANKSEL_MEM_SEL_LENGTH      5

#define MPU9250_WHO_AM_I_BIT        6
#define MPU9250_WHO_AM_I_LENGTH     6

#define MPU9250_DMP_MEMORY_BANKS        8
#define MPU9250_DMP_MEMORY_BANK_SIZE    256
#define MPU9250_DMP_MEMORY_CHUNK_SIZE   16


#define MPUREG_USER_CTRL		0x6A//
#define MPUREG_I2C_MST_CTRL		0x24

#define BIT_I2C_SLV0_NACK           0x01
#define BIT_I2C_FIFO_EN             0x40
#define BIT_I2C_MST_EN              0x20
#define BIT_I2C_IF_DIS              0x10
#define BIT_FIFO_RST                0x04
#define BIT_I2C_MST_RST             0x02
#define BIT_SIG_COND_RST            0x01

#define BIT_I2C_SLV0_EN             0x80
#define BIT_I2C_SLV0_BYTE_SW        0x40
#define BIT_I2C_SLV0_REG_DIS        0x20
#define BIT_I2C_SLV0_REG_GRP        0x10

#define BIT_I2C_MST_MULT_MST_EN     0x80
#define BIT_I2C_MST_WAIT_FOR_ES     0x40
#define BIT_I2C_MST_SLV_3_FIFO_EN   0x20
#define BIT_I2C_MST_P_NSR           0x10
#define BITS_I2C_MST_CLOCK_258HZ    0x08
#define BITS_I2C_MST_CLOCK_400HZ    0x0D

#define BIT_I2C_SLV0_DLY_EN         0x01
#define BIT_I2C_SLV1_DLY_EN         0x02
#define BIT_I2C_SLV2_DLY_EN         0x04
#define BIT_I2C_SLV3_DLY_EN         0x08

/* ak8963 register address and bit definitions */



#define AK8963_I2C_ADDR         0x0C
#define AK8963_DEVICE_ID        0x48
#define MPUREG_I2C_MST_CTRL		0x24
#define MPUREG_I2C_SLV0_ADDR		0x25
#define MPUREG_I2C_SLV0_REG		0x26
#define MPUREG_I2C_SLV0_CTRL		0x27
#define MPUREG_I2C_SLV1_ADDR		0x28
#define MPUREG_I2C_SLV1_REG		0x29
#define MPUREG_I2C_SLV1_CTRL		0x2A
#define MPUREG_I2C_SLV2_ADDR		0x2B
#define MPUREG_I2C_SLV2_REG		0x2C
#define MPUREG_I2C_SLV2_CTRL		0x2D
#define MPUREG_I2C_SLV3_ADDR		0x2E
#define MPUREG_I2C_SLV3_REG		0x2F
#define MPUREG_I2C_SLV3_CTRL		0x30
#define MPUREG_I2C_SLV4_ADDR		0x31
#define MPUREG_I2C_SLV4_REG		0x32
#define MPUREG_I2C_SLV4_DO		0x33
#define MPUREG_I2C_SLV4_CTRL		0x34
#define INT_PIN_CFG                         0x37

#define MPUREG_I2C_SLV0_D0          0x63
#define MPUREG_I2C_SLV0_D0          0x63

#define AK8963REG_WIA           0x00
#define AK8963REG_ST1           0x02
#define AK8963REG_HXL           0x03
#define AK8963REG_ASAX          0x10
#define AK8963REG_CNTL1         0x0A
#define AK8963REG_CNTL2         0x0B

#define AK8963_WIA_VALUE        0x48

#define AK8963_SINGLE_MEAS_MODE 0x01
#define AK8963_CONTINUOUS_MODE1 0x02
#define AK8963_CONTINUOUS_MODE2 0x06
#define AK8963_POWERDOWN_MODE   0x00
#define AK8963_SELFTEST_MODE    0x08
#define AK8963_FUZE_MODE        0x0F
#define AK8963_16BIT_ADC        0x10
#define AK8963_14BIT_ADC        0x00
#define AK8963_RESET            0x01

#define MPUREG_I2C_SLV0_ADDR                            0x25
#define MPUREG_EXT_SENS_DATA_00                         0x49
#define MPUREG_I2C_SLV0_DO                              0x63
#define MPUREG_I2C_MST_DELAY_CTRL                  0x67


#define EXT_SENS_DATA_00    0x49  //MPU9250 IIC外挂器件读取返回寄存器00
#define EXT_SENS_DATA_01    0x4a  //MPU9250 IIC外挂器件读取返回寄存器01
#define EXT_SENS_DATA_02    0x4b  //MPU9250 IIC外挂器件读取返回寄存器02
#define EXT_SENS_DATA_03    0x4c  //MPU9250 IIC外挂器件读取返回寄存器03


#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08

#define READ_DIR 0x80
#define WRITE_DIR 0x00

#pragma pack(push, 1)
 
#pragma pack(pop)
#define MPU92_CS  PDout(9)
void ICM20689_SPICS_init(void);
void ICM20689_Init(void);
uint8_t ICM20689_GetDeviceID(void) ;
void Get_ICM20689_Raw(int16_t *raw_data);
uint8_t MPU9250_Read_Reg(uint8_t read_reg);
void MPU9250_Write_Reg(unsigned reg, uint8_t value);
void MPU9250_Acc_Set_Range(u8 accrange);
void MPU9250_Gyro_Set_Range(u8 gyrorange);
void MPU9250_Gyro_Set_Rate(u8 gyrorate);
uint8_t ICM20689_GetDeviceID(void) ;
	
#endif
