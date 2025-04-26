/*
 * tools.h
 *
 *  Created on: Apr 15, 2025
 *      Author: ofirkeres
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_OKDRONE_TOOLS_H
#define INC_OKDRONE_TOOLS_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart3;
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
int __io_putchar(int ch); /* printf() */
int _write(int file, char* ptr, int len);
int _read(int file, char* ptr, int len); /* scanf() */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

 #endif /* INC_OKDRONE_TOOLS_H */
