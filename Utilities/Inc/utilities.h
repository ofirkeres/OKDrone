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
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define WITHIN_RANGE(value, low, high) ((((low) <= (value)) && ((value) <= (high))) ? (1) : (0))
#define LIMIT(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))
/* Exported functions --------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

#endif /* INC_OKDRONE_UTILITIES_H */
