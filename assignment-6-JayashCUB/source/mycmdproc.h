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
 * @file mycmdproc.h
 * @brief - Contains function declaration of various functions required for command processor
 *
 * @author Jayash Arun Raulkar
 * @date   11 November 2023
 *
 */
#ifndef MYCMDPROC_H_
#define MYCMDPROC_H_


/* brief: Below is the function to get the user typed instruction
 *
 *  Parameters:
 *  character pointer where we want to store the instruction
 *
 * Returns:
 *  none
 */
void get_user_line(char* arr);



/* brief: Below is the function to convert string to uppercase
 *
 *  Parameters:
 *  character pointer of string which we want to convert
 *
 * Returns:
 *  none
 */
void string_to_upper(char *str);



/* brief: Below is the initialization function of systick timer
 *
 *  Parameters:
 *  character point of string we got from the user which we want to tokenize and inturn
 *  call the handler function for the command
 *
 * Returns:
 *  none
 */
void process_command(char *input);



/* brief: Below is the handler function for ECHO command
 *
 *  Parameters:
 *  its taker the pointer array address and the count of the tokens
 *
 * Returns:
 *  none
 */
void handle_echo(int argc, char *argv[]);



/* brief: Below is the handler function for LED command
 *
 *  Parameters:
 *  its taker the pointer array address and the count of the tokens
 *
 * Returns:
 *  none
 */
void handle_led(int argc, char *argv[]);

#endif
