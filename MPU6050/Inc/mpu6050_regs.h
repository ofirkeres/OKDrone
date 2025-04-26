/*
 * mpu6050_regs.h
 *
 *  Created on: Apr 11, 2025
 *      Author: ofirkeres
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_OKDRONE_MPU6050_REGS_H
#define INC_OKDRONE_MPU6050_REGS_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define REG_SELF_TEST_X         0x000D
#define REG_SELF_TEST_Y         0x000E
#define REG_SELF_TEST_Z         0x000F
#define REG_SELF_TEST_A         0x0010

#define REG_SMPLRT_DIV          0x0019

#define REG_CONFIG              0x001A
#define REG_GYRO_CONFIG         0x001B
#define REG_ACCL_CONFIG         0x001C

#define REG_MOT_THR             0x001F
#define REG_FIFO_EN             0x0023

#define REG_I2C_MST_CTRL        0x0024

#define REG_I2C_SLVO_ADDR       0x0025
#define REG_I2C_SLVO_REG        0x0026
#define REG_I2C_SLVO_CTRL       0x0027

#define REG_I2C_SLV1_ADDR       0x0028
#define REG_I2C_SLV1_REG        0x0029
#define REG_I2C_SLV1_CTRL       0x002A

#define REG_I2C_SLV2_ADDR       0x002B
#define REG_I2C_SLV2_REG        0x002C
#define REG_I2C_SLV2_CTRL       0x002D

#define REG_I2C_SLV3_ADDR       0x002E
#define REG_I2C_SLV3_REG        0x002F
#define REG_I2C_SLV3_CTRL       0x0030

#define REG_I2C_SLV4_ADDR       0x0031
#define REG_I2C_SLV4_REG        0x0032
#define REG_I2C_SLV4_DO         0x0033
#define REG_I2C_SLV4_CTRL       0x0034
#define REG_I2C_SLV4_DI         0x0035

#define REG_I2C_MST_STATUS      0x0036

#define REG_INT_PIN_CFG         0x0037
#define REG_INT_ENABLE          0x0038
#define REG_INT_STATUS          0x003A

#define REG_ACCL_XOUT_H         0x003B
#define REG_ACCL_XOUT_L         0x003C
#define REG_ACCL_YOUT_H         0x003D
#define REG_ACCL_YOUT_L         0x003E
#define REG_ACCL_ZOUT_H         0x003F
#define REG_ACCL_ZOUT_L         0x0040

#define REG_TEMP_OUT_H          0x0041
#define REG_TEMP_OUT_L          0x0042

#define REG_GYRO_XOUT_H         0x0043
#define REG_GYRO_XOUT_L         0x0044
#define REG_GYRO_YOUT_H         0x0045
#define REG_GYRO_YOUT_L         0x0046
#define REG_GYRO_ZOUT_H         0x0047
#define REG_GYRO_ZOUT_L         0x0048

#define REG_EXT_SENS_DATA_00    0x0049
#define REG_EXT_SENS_DATA_01    0x004A
#define REG_EXT_SENS_DATA_02    0x004B
#define REG_EXT_SENS_DATA_03    0x004C
#define REG_EXT_SENS_DATA_04    0x004D
#define REG_EXT_SENS_DATA_05    0x004E
#define REG_EXT_SENS_DATA_06    0x004F
#define REG_EXT_SENS_DATA_07    0x0050
#define REG_EXT_SENS_DATA_08    0x0051
#define REG_EXT_SENS_DATA_09    0x0052
#define REG_EXT_SENS_DATA_10    0x0053
#define REG_EXT_SENS_DATA_11    0x0054
#define REG_EXT_SENS_DATA_12    0x0055
#define REG_EXT_SENS_DATA_13    0x0056
#define REG_EXT_SENS_DATA_14    0x0057
#define REG_EXT_SENS_DATA_15    0x0058
#define REG_EXT_SENS_DATA_16    0x0059
#define REG_EXT_SENS_DATA_17    0x005A
#define REG_EXT_SENS_DATA_18    0x005B
#define REG_EXT_SENS_DATA_19    0x005C
#define REG_EXT_SENS_DATA_20    0x005D
#define REG_EXT_SENS_DATA_21    0x005E
#define REG_EXT_SENS_DATA_22    0x005F
#define REG_EXT_SENS_DATA_23    0x0060

#define REG_I2C_SLVO_DO         0x0063
#define REG_I2C_SLV1_DO         0x0064
#define REG_I2C_SLV2_DO         0x0065
#define REG_I2C_SLV3_DO         0x0066

#define REG_I2C_MST_DELAY_CTRL  0x0067
#define REG_SIGNAL_PATH_RESET   0x0068
#define REG_MOT_DETECT_CTRL     0x0069
#define REG_USER_CTRL           0x006A

#define REG_PWR_MGMT_1          0x006B
#define REG_PWR_MGMT_2          0x006C

#define REG_FIFO_COUNTH         0x0072
#define REG_FIFO_COUNTL         0x0073
#define REG_FIFO_R_W            0x0074

#define REG_WHO_AM_I            0x0075

#define GYRO_FS_SEL_POS          3
#define ACCL_FS_SEL_POS          3
#define SLEEP_MODE_POS           6
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/


#endif /* INC_OKDRONE_MPU6050_REGS_H */