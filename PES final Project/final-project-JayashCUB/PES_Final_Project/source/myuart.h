/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ 2023 ​by​ Jayash Arun Raulkar
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Jayash Arun Raulkar ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file myuart.h
 * @brief - contains function declarations of uart initialization
 *
 * @author Jayash Arun Raulkar
 * @date   10 December 2023
 */

#ifndef _MYUART_H_
#define _MYUART_H_

#include <stdint.h>


/**
 * @brief- Initializes Uart0 with the baud rate given in parameter
 *
 * param- Desired baud rate.
 *
 * return- None.
 */
void Init_UART0(uint32_t baud_rate);


/**
 * @brief- function to send data via uart
 *
 * param- The pointer to data, and its size
 *
 * return- none
 */
void uart_send_data(uint8_t *buf, int size);


/**
 * @brief- function to send integer data via uart
 *
 * param- The integer data to send
 *
 * return- none
 */
void uart_send_integer(int data);


/**
 * @brief- function to receive data via uart
 *
 * param- none
 *
 * return- the read data
 */
int uart_get_data(void);

#endif // _MYUART_H_
