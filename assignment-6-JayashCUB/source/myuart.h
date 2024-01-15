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
 * @brief - contains function declarations of uart initialization and __sys_write and __sys_read
 *
 * @author Jayash Arun Raulkar
 * @date   11 November 2023
 *
 * @reference
 * https://community.nxp.com/t5/LPCXpresso-IDE-FAQs/Using-printf/m-p/474799
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
 * @brief- To retarget Redlib's putchar() or printf(), implemented my own of the function __sys_write():
 *
 * param- Handle, the pointer to data, and its size
 *
 * return- Function returns number of unwritten bytes if error, otherwise 0 for success.
 */
int __sys_write(int handle, char *buf, int size);



/**
 * @brief- To retarget Redlib's getchar() or scanf(), implemented my own of the function __sys_read():
 *
 * param- none
 *
 * return- Function returns character read
 */
int __sys_readc(void);

#endif // _MYUART_H_
