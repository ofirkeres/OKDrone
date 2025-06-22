/*
* utilities.h
*
*  Created on: Jun 22, 2025
*      Author: ofirkeres
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_OKDRONE_UTILITIES_H
#define INC_OKDRONE_UTILITIES_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct thresholds_float
{
    float min;
    float max;
} thresholds_float_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define WITHIN_RANGE(value, low, high) ((((low) <= (value)) && ((value) <= (high))) ? (1) : (0))
#define LIMIT(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))
#define MEDIAN_OF_3(a, b, c) (((a) > (b)) ? \
                             (((b) > (c)) ? (b) : ((a) > (c) ? (c) : (a))) : \
                             (((a) > (c)) ? (a) : ((b) > (c) ? (c) : (b))))
/* Exported functions --------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

#endif /* INC_OKDRONE_UTILITIES_H */
