/*
 * mpu6050.h
 *
 *  Created on: Apr 11, 2025
 *      Author: ofirkeres
 */

#ifndef INC_MPU_6050_H_
#define INC_MPU_6050_H_

#include "stm32f7xx_hal.h"

typedef struct axes_float {
    float x;
    float y;
    float z;
} axes_float_t;

typedef struct mpu6050 {
    axes_float_t acc;
    axes_float_t gyro;
} mpu6050_t;

typedef enum gyro_fs_sel {
    GYRO_FS_SEL_250,  // deg/s
    GYRO_FS_SEL_500,  // deg/s
    GYRO_FS_SEL_1000, // deg/s
    GYRO_FS_SEL_2000  // deg/s
} gyro_fs_sel_e;

typedef enum acc_fs_sel {
    ACCL_FS_SEL_2G,
    ACCL_FS_SEL_4G,
    ACCL_FS_SEL_8G,
    ACCL_FS_SEL_16G
} acc_fs_sel_e;

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

HAL_StatusTypeDef mpu6050_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef mpu6050_read_data(mpu6050_t* mpu);
HAL_StatusTypeDef mpu6050_read_acc(axes_float_t* acc);
HAL_StatusTypeDef mpu6050_read_gyro(axes_float_t* gyro);

#endif /* INC_MPU_6050_H_ */
