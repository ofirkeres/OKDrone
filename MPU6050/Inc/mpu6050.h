/*
 * mpu6050.h
 *
 *  Created on: Apr 11, 2025
 *      Author: ofirkeres
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_OKDRONE_MPU6050_H
#define INC_OKDRONE_MPU6050_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef struct axes_float {
    float x;
    float y;
    float z;
} axes_float_t;

typedef struct mpu6050 {
    axes_float_t accl;
    axes_float_t gyro;
} mpu6050_t;

typedef enum gyro_fs_sel {
    GYRO_FS_SEL_250,  // deg/s
    GYRO_FS_SEL_500,  // deg/s
    GYRO_FS_SEL_1000, // deg/s
    GYRO_FS_SEL_2000  // deg/s
} gyro_fs_sel_e;

typedef enum accl_fs_sel {
    ACCL_FS_SEL_2G,
    ACCL_FS_SEL_4G,
    ACCL_FS_SEL_8G,
    ACCL_FS_SEL_16G
} accl_fs_sel_e;

typedef enum sample_rate_div {
    SMPLRT_DIV_8KHz, // Sample Rate = Output Rate / 1 + Sample Rate Divider
    SMPLRT_DIV_7KHz, // Sample Rate = Output Rate / 1 + Sample Rate Divider
    SMPLRT_DIV_6KHz, // Sample Rate = Output Rate / 1 + Sample Rate Divider
    SMPLRT_DIV_5KHz, // Sample Rate = Output Rate / 1 + Sample Rate Divider
    SMPLRT_DIV_4KHz, // Sample Rate = Output Rate / 1 + Sample Rate Divider
    SMPLRT_DIV_3KHz, // Sample Rate = Output Rate / 1 + Sample Rate Divider
    SMPLRT_DIV_2KHz, // Sample Rate = Output Rate / 1 + Sample Rate Divider
    SMPLRT_DIV_1KHz  // Sample Rate = Output Rate / 1 + Sample Rate Divider
} sample_rate_div_e;
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
HAL_StatusTypeDef mpu6050_init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef mpu6050_read_data(mpu6050_t* mpu);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

#endif /* INC_OKDRONE_MPU6050_H */
