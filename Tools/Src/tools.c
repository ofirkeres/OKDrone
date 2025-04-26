/*
 * tools.c
 *
 *  Created on: Apr 15, 2025
 *      Author: ofirkeres
 */

/* Includes ------------------------------------------------------------------*/
#include "tools.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
#define UART_DEBUG &huart3
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/* printf Implementation */
int __io_putchar(int ch) {
    HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(UART_DEBUG, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}

/* scanf Implementation */
int _read(int file, char *ptr, int len)
{
    int ch = 0;
    HAL_UART_Receive(UART_DEBUG, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);

    if(ch == 13)
    {
        ch = 10;
        HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
    }
    else if(ch == 8)
    {
        ch = 0x30;
        HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
    }

    *ptr = ch;

    return 1;
}
