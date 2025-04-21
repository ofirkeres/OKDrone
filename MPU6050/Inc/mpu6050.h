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

HAL_StatusTypeDef mpu6050_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef mpu6050_read_data(mpu6050_t* mpu);
HAL_StatusTypeDef mpu6050_read_acc(axes_float_t* acc);
HAL_StatusTypeDef mpu6050_read_gyro(axes_float_t* gyro);

#endif /* INC_MPU_6050_H_ */
