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

 uint8_t mpu6050_Init(I2C_HandleTypeDef *hi2c);
 void mpu6050_read_acc(axes_float_t* acc);
 void mpu6050_read_gyro(axes_float_t* gyro);

 #endif /* INC_MPU_6050_H_ */
