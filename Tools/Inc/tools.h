/*
 * tools.h
 *
 *  Created on: Apr 15, 2025
 *      Author: ofirkeres
 */

 #ifndef INC_TOOLS_H_
 #define INC_TOOLS_H_

 #include "main.h"

 extern UART_HandleTypeDef huart3;

 /* printf() */
 int __io_putchar(int ch);
 int _write(int file, char* ptr, int len);

 /* scanf() */
 int _read(int file, char* ptr, int len);

 #endif /* INC_TOOLS_H_ */
