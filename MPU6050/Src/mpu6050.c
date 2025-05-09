/*
 * mpu6050.c
 *
 *  Created on: Jun 18, 2024
 *      Author: ofirkeres
 */

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <limits.h>
#include "mpu6050.h"
#include "mpu6050_regs.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/
typedef struct axes_16 {
    int16_t x;
    int16_t y;
    int16_t z;
} axes_16_t;
/* Private constants ---------------------------------------------------------*/
#define MPU6050_DEV_ADDR   0xD0
#define WHO_AM_I_ADDR      (MPU6050_DEV_ADDR >> 1)
#define RDWR_TIMEOUT       1000
#define AXIS_SIZE          sizeof(int16_t)
#define AXES_NUM           3
#define AXES_BUFFER_SIZE   (AXIS_SIZE * AXES_NUM)

#define X_AXES_IDX         (0 * sizeof(int16_t))
#define Y_AXES_IDX         (1 * sizeof(int16_t))
#define Z_AXES_IDX         (2 * sizeof(int16_t))

#define ACCL_SCALE_2G      (float)16384.0 /* Accelerometer Sensitivity +-2g  LSB/g */
#define ACCL_SCALE_4G      (float)8192.0  /* Accelerometer Sensitivity +-4g  LSB/g */
#define ACCL_SCALE_8G      (float)4096.0  /* Accelerometer Sensitivity +-8g  LSB/g */
#define ACCL_SCALE_16G     (float)2048.0  /* Accelerometer Sensitivity +-16g LSB/g */

#define GYRO_SCALE_250DPS   (float)131.0 /* Gyro Sensitivity +-250  Deg/Sec LSB/g */
#define GYRO_SCALE_500DPS   (float)65.5  /* Gyro Sensitivity +-500  Deg/Sec LSB/g */
#define GYRO_SCALE_1000DPS  (float)32.8  /* Gyro Sensitivity +-1000 Deg/Sec LSB/g */
#define GYRO_SCALE_2000DPS  (float)16.4  /* Gyro Sensitivity +-2000 Deg/Sec LSB/g */

#define ACCL_SCALE          ACCL_SCALE_2G
#define GYRO_SCALE          GYRO_SCALE_250DPS
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static I2C_HandleTypeDef* mpu_i2c = NULL;
/* Private function ----------------------------------------------------------*/
static HAL_StatusTypeDef i2c_write(uint16_t reg_addr, uint8_t* data, uint8_t size);
static HAL_StatusTypeDef i2c_read(uint16_t reg_addr, uint8_t* data, uint8_t size);
static HAL_StatusTypeDef read_accl(axes_float_t* accl);
static HAL_StatusTypeDef read_gyro(axes_float_t* gyro);
static HAL_StatusTypeDef wake_up(void);
static HAL_StatusTypeDef set_sample_rate(uint8_t divider);
static HAL_StatusTypeDef set_gyro_full_scale(uint8_t scale);
static HAL_StatusTypeDef set_accl_full_scale(uint8_t scale);
static int16_t read_int16_be(const uint8_t* buffer);


static HAL_StatusTypeDef i2c_write(uint16_t reg_addr, uint8_t* data, uint8_t size)
{
    return HAL_I2C_Mem_Write(mpu_i2c, MPU6050_DEV_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, size, RDWR_TIMEOUT);
}

static HAL_StatusTypeDef i2c_read(uint16_t reg_addr, uint8_t* data, uint8_t size)
{
    return HAL_I2C_Mem_Read(mpu_i2c, MPU6050_DEV_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, size, RDWR_TIMEOUT);
}

static int16_t read_int16_be(const uint8_t* buffer)
{
    return (int16_t)(((uint16_t)buffer[0] << (sizeof(buffer[0]) * CHAR_BIT)) | buffer[1]);
}

static HAL_StatusTypeDef set_gyro_full_scale(uint8_t scale)
{
    uint8_t data = 0;

    switch (scale)
    {
        case GYRO_FS_SEL_250:
        case GYRO_FS_SEL_500:
        case GYRO_FS_SEL_1000:
        case GYRO_FS_SEL_2000:
            break;

        default:
            scale = GYRO_FS_SEL_250;
            break;
    }

    data |= scale << GYRO_FS_SEL_POS;
    return i2c_write(REG_GYRO_CONFIG, &data, sizeof(data));
}

static HAL_StatusTypeDef set_accl_full_scale(uint8_t scale)
{
    uint8_t data = 0;

    switch (scale)
    {
        case ACCL_FS_SEL_2G:
        case ACCL_FS_SEL_4G:
        case ACCL_FS_SEL_8G:
        case ACCL_FS_SEL_16G:
            break;

        default:
            scale = ACCL_FS_SEL_2G;
            break;
    }

    data |= scale << ACCL_FS_SEL_POS;
    return i2c_write(REG_ACCL_CONFIG, &data, sizeof(data));
}

static HAL_StatusTypeDef wake_up(void)
{
    /* Wrting 0 to REG_PWR_MGMT_1 does the following:
       1. Clears SLEEP bit(since the device come up in sleep mode).
       2. Sets CLKSEL to internal 8MHz oscillator.
       3. Enable temperature sensor. */
    uint8_t data = 0x00;
    HAL_StatusTypeDef write_status = HAL_ERROR;
    static bool first_entrance = true;

    if (first_entrance) {
        first_entrance = false;
        write_status = i2c_write(REG_PWR_MGMT_1, &data, sizeof(data));
    }

    return write_status;
}

static HAL_StatusTypeDef set_sample_rate(uint8_t divider)
{
    uint8_t data = 0;
    data |= divider & 0x07; // Extract 3 LSB Bits

    return i2c_write(REG_SMPLRT_DIV, &data, sizeof(data));
}

HAL_StatusTypeDef mpu6050_init(I2C_HandleTypeDef *hi2c)
{
    uint8_t who_am_i;
    HAL_StatusTypeDef status, read_status, write_status;

    // Save a local pointer to the mpu 6050 i2c handler
    mpu_i2c = hi2c;

    if ((read_status = i2c_read(REG_WHO_AM_I, &who_am_i, sizeof(who_am_i))) != HAL_OK) {
        status = read_status;
    } else if (who_am_i != WHO_AM_I_ADDR) {
        status = HAL_ERROR;
    } else {
        if ((write_status = wake_up()) != HAL_OK) {                                   /* Wake up the sensor - zero power management register. */
            status = write_status;
        } else if ((write_status = set_sample_rate(SMPLRT_DIV_8KHz)) != HAL_OK) {     /* Set data output rate (sample rate) to 1KHz */
            status = write_status;
        } else if ((write_status = set_accl_full_scale(ACCL_FS_SEL_2G)) != HAL_OK) {  /* Set Accelerometer configuration in REG_ACCL_CONFIG register. */
            status = write_status;
        } else if ((write_status = set_gyro_full_scale(GYRO_FS_SEL_250)) != HAL_OK) { /* Set Gyroscope configuration in REG_GYRO_CONFIG register. */
            status = write_status;
        }
    }

    return status;
}

HAL_StatusTypeDef mpu6050_read_data(mpu6050_t* mpu)
{
    HAL_StatusTypeDef read_status;

    read_status = read_accl(&mpu->accl);

    if (read_status == HAL_OK) {
        read_status = read_gyro(&mpu->gyro);
    }

    return read_status;
}

static HAL_StatusTypeDef read_accl(axes_float_t* accl)
{
    uint8_t buffer[AXES_BUFFER_SIZE] = {0};
    axes_16_t raw_accl;
    HAL_StatusTypeDef read_status;

    read_status = i2c_read(REG_ACCL_XOUT_H, buffer, AXES_BUFFER_SIZE);

    if (read_status == HAL_OK) {
        /* Adding 2 bytes into 16 bit integer. */
        raw_accl.x = read_int16_be(buffer + X_AXES_IDX);
        raw_accl.y = read_int16_be(buffer + Y_AXES_IDX);
        raw_accl.z = read_int16_be(buffer + Z_AXES_IDX);

        accl->x = (float)raw_accl.x / ACCL_SCALE;
        accl->y = (float)raw_accl.y / ACCL_SCALE;
        accl->z = (float)raw_accl.z / ACCL_SCALE;
    }

    return read_status;
}

static HAL_StatusTypeDef read_gyro(axes_float_t* gyro)
{
    uint8_t buffer[AXES_BUFFER_SIZE] = {0};
    axes_16_t raw_gyro;
    HAL_StatusTypeDef read_status;

    read_status = i2c_read(REG_GYRO_XOUT_H, buffer, AXES_BUFFER_SIZE);

    if (read_status == HAL_OK) {
        raw_gyro.x = read_int16_be(buffer + X_AXES_IDX);
        raw_gyro.y = read_int16_be(buffer + Y_AXES_IDX);
        raw_gyro.z = read_int16_be(buffer + Z_AXES_IDX);

        gyro->x = (float)raw_gyro.x / GYRO_SCALE;
        gyro->y = (float)raw_gyro.y / GYRO_SCALE;
        gyro->z = (float)raw_gyro.z / GYRO_SCALE;
    }

    return read_status;
}