/*
* imu.h
*
*  Created on: Apr 26, 2025
*      Author: ofirkeres
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_OKDRONE_IMU_H
#define INC_OKDRONE_IMU_H

/* Includes ------------------------------------------------------------------*/
#include <math.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
float calc_roll(float accl_y, float accl_z);
float calc_pitch(float accl_x, float accl_y, float accl_z);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

#endif /* INC_OKDRONE_IMU_H */
