/*
* imu.c
*
*  Created on: Apr 26, 2025
*      Author: ofirkeres
*/

/* Includes ------------------------------------------------------------------*/
#include "imu.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

float calc_roll(float accl_y, float accl_z)
{
    return RAD_TO_DEG(atan2(accl_y, accl_z));
}

float calc_pitch(float accl_x, float accl_y, float accl_z)
{
    return RAD_TO_DEG(atan2(-accl_x, sqrt(accl_y * accl_y + accl_z * accl_z)));
}