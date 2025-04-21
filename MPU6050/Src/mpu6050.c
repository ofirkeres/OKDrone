/*
 * mpu6050.c
 *
 *  Created on: Jun 18, 2024
 *      Author: ofirkeres
 */

#include "mpu6050.h"
#include "mpu6050_regs.h"
#include <limits.h>

#define MPU6050_DEV_ADDR   0xD0
#define WHO_AM_I_ADDR      (MPU6050_DEV_ADDR >> 1)
#define RDWR_TIMEOUT       1000
#define AXIS_SIZE          sizeof(int16_t)
#define AXES_NUM           3
#define AXES_BUFFER_SIZE   (AXIS_SIZE * AXES_NUM)

#define X_AXES_IDX         (0 * sizeof(int16_t))
#define Y_AXES_IDX         (1 * sizeof(int16_t))
#define Z_AXES_IDX         (2 * sizeof(int16_t))

#define ACCL_GAIN_2G       (float)16384.0 /* Accel Full Scale Range +-2 Sensitivity LSB/g */
#define ACCL_GAIN_4G       (float)8192.0  /* Accel Full Scale Range +-4 Sensitivity LSB/g */
#define ACCL_GAIN_8G       (float)4096.0  /* Accel Full Scale Range +-8 Sensitivity LSB/g */
#define ACCL_GAIN_16G      (float)2048.0  /* Accel Full Scale Range +-16 Sensitivity LSB/g */

#define GYRO_GAIN_250DPS   (float)131.0 /* Gyro Full Scale Range +-250 Degree/Sec Sensitivity LSB/g */
#define GYRO_GAIN_500DPS   (float)65.5  /* Gyro Full Scale Range +-500 Degree/Sec Sensitivity LSB/g */
#define GYRO_GAIN_1000DPS  (float)32.8  /* Gyro Full Scale Range +-1000 Degree/Sec Sensitivity LSB/g */
#define GYRO_GAIN_2000DPS  (float)16.4  /* Gyro Full Scale Range +-2000 Degree/Sec Sensitivity LSB/g */

#define ACCL_GAIN          ACCL_GAIN_2G
#define GYRO_GAIN          GYRO_GAIN_250DPS

typedef struct axes_16 {
    int16_t x;
    int16_t y;
    int16_t z;
} axes_16_t;

static HAL_StatusTypeDef mpu6050_write(uint16_t reg_addr, uint8_t* data, uint8_t size);
static HAL_StatusTypeDef mpu6050_read(uint16_t reg_addr, uint8_t* data, uint8_t size);
static int16_t read_int16_be(const uint8_t* data);

static I2C_HandleTypeDef* mpu_i2c = NULL;

static HAL_StatusTypeDef mpu6050_write(uint16_t reg_addr, uint8_t* data, uint8_t size)
{
    return HAL_I2C_Mem_Write(mpu_i2c, MPU6050_DEV_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, size, RDWR_TIMEOUT);
}

static HAL_StatusTypeDef mpu6050_read(uint16_t reg_addr, uint8_t* data, uint8_t size)
{
    return HAL_I2C_Mem_Read(mpu_i2c, MPU6050_DEV_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, size, RDWR_TIMEOUT);
}

static int16_t read_int16_be(const uint8_t* data)
{
    return (int16_t)(((uint16_t)data[0] << (sizeof(data[0]) * CHAR_BIT)) | data[1]);
}

uint8_t mpu6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t who_am_i, value, rtnval = 1;
    HAL_StatusTypeDef read_status;

    // Save a local pointer to the mpu 6050 i2c handler
    mpu_i2c = hi2c;

    read_status = mpu6050_read(REG_WHO_AM_I, &who_am_i, sizeof(who_am_i));

    if (read_status == HAL_OK) {
        if (who_am_i != WHO_AM_I_ADDR) {
            rtnval = 1;
        }
        else {
            /* Wake up the sensor - zero power management register. */
            value = 0x00;
            mpu6050_write(REG_PWR_MGMT_1, &value, sizeof(value));

            /* Set data output rate (sample rate) to 1KHz */
            value = 0x07;
            mpu6050_write(REG_SMPLRT_DIV, &value, sizeof(value));

            /* Set Accelerometer configuration in REG_ACCL_CONFIG register. */
            value = 0x00; // XA_ST=0, YA_ST=0, ZA_ST=0, FS_SEL=0 -> +- 2g
            mpu6050_write(REG_ACCL_CONFIG, &value, sizeof(value));

            /* Set Gyroscope configuration in REG_GYRO_CONFIG register. */
            value = 0x00; // XG_ST=0, YG_ST=0, ZG_ST=0, FS_SEL=0 -> +- 250 deg/s
            mpu6050_write(REG_GYRO_CONFIG, &value, sizeof(value));

            rtnval = 0;
        }
    }
    return rtnval;
}

void mpu6050_read_data(mpu6050_t* mpu)
{
    mpu6050_read_acc(&mpu->acc);
    mpu6050_read_gyro(&mpu->gyro);
}

void mpu6050_read_acc(axes_float_t* acc)
{
    uint8_t buffer[AXES_BUFFER_SIZE] = {0};
    axes_16_t raw_acc;

    mpu6050_read(REG_ACCL_XOUT_H, buffer, AXES_BUFFER_SIZE);

    /* Adding 2 bytes into 16 bit integer. */
    raw_acc.x = read_int16_be(buffer + X_AXES_IDX);
    raw_acc.y = read_int16_be(buffer + Y_AXES_IDX);
    raw_acc.z = read_int16_be(buffer + Z_AXES_IDX);

    acc->x = (float)raw_acc.x / ACCL_GAIN;
    acc->y = (float)raw_acc.y / ACCL_GAIN;
    acc->z = (float)raw_acc.z / ACCL_GAIN;
}

void mpu6050_read_gyro(axes_float_t* gyro)
{
    uint8_t buffer[AXES_BUFFER_SIZE] = {0};
    axes_16_t raw_gyro;

    mpu6050_read(REG_GYRO_XOUT_H, buffer, AXES_BUFFER_SIZE);

    raw_gyro.x = read_int16_be(buffer + X_AXES_IDX);
    raw_gyro.y = read_int16_be(buffer + Y_AXES_IDX);
    raw_gyro.z = read_int16_be(buffer + Z_AXES_IDX);

    gyro->x = (float)raw_gyro.x / GYRO_GAIN;
    gyro->y = (float)raw_gyro.y / GYRO_GAIN;
    gyro->z = (float)raw_gyro.z / GYRO_GAIN;
}