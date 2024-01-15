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
 * @file mycmdproc.c
 * @brief - Contains function defination of various functions required for command processor
 *
 * @author Jayash Arun Raulkar
 * @date   11 November 2023
 *
 */
#include "mycmdproc.h"
#include "mysystick.h"  //for delay_ms fucntion in led command Handler
#include "mypwm.h"		//for pwm led
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>   //for toupper function
#include <stdlib.h>  //for strtol function
#include <stdbool.h>  //for in_token variable

#define one_sec_delay 1000   //for 1 sec delay
#define max_color_byte_value 0x1000000  //to check for invalid led command parameter(ie any value > 0xFFFFFF)
#define MAX_ARGS 10   //for argv[] define the maximum number of arguments

#define ENTER 0x0D		//ascii for enter
#define BACKSPACE 0x08	//ascii for backspace
void get_user_line(char* arr)
{
	int i=0;
	while(1)
	{
		char c = getchar();     //reading user line

		printf("%c",c);			//to see what is getting typed
		if(c!=ENTER && c!=BACKSPACE)  //check for ENTER or BACKSPACE
		{
			*(arr+i) = c;		//store it in arr
			i++;
		}
		else if(c==BACKSPACE)		//check if Backspace (if so overwrite with space and then move cursor back)
		{
			if(i==0)
			{
				printf(" ");	//checks if backspace happens even before anything is typed
			}else{
				printf(" ");
				printf("\b");
				i--;
			}
		}
		else
		{
			break;				//come out if ENTER is pressed
		}
	}
	*(arr+i) = '\0';			//terminate with NULL
}

// Function to convert a string to uppercase
void string_to_upper(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}


// Command table structure
typedef void (*command_handler_t)(int argc, char *argv[]);
typedef struct {
    const char *name;
    command_handler_t handler;
    const char *help_string;
} command_table_t;

// Command table
static const command_table_t commands[] = {
    {"ECHO", handle_echo, "Echoes the input string in uppercase without whitespaces"},
    {"LED", handle_led, "Lights up the LED with the given color(s)"},
    //We can add more commands as per our requirement
};

// Number of commands in the table
static const int num_commands = sizeof(commands) / sizeof(command_table_t);

// Function to process command
void process_command(char *input) {
    char *p = input;
    char *end;

    // Find end of string
    for (end = input; *end != '\0'; end++);

    // Tokenize input in place
    bool in_token = false;
    char *argv[MAX_ARGS];
    int argc = 0;
    memset(argv, 0, sizeof(argv));

    for (p = input; p < end; p++) {
    	//check for character and if not space save the address in argv, then wait for next character, finally terminate with null.
    	//thus save address of each tokens in argv pointer array, increment argc count
        if (!isspace(*p)) {
            if (!in_token) {
                argv[argc++] = p;
                in_token = true;
            }
        } else {
            if (in_token) {
                *p = '\0';
                in_token = false;
            }
        }
    }
    if (in_token) {
        *p = '\0';
    }

    //check for match in lookup table
    if (argc > 1) {
        for (int i = 0; i < num_commands; i++) {
            if (strcasecmp(argv[0], commands[i].name) == 0) {
                commands[i].handler(argc, argv);
                break;
            }
        }
    }else{
    	printf("\n\rUnknown command(%s)\n\r",argv[0]);   //if no parameters given to command (ex- led       )
    }
}

// Command handlers
void handle_echo(int argc, char *argv[]) {
	printf("\n\r");
    for (int i = 1; i < argc; i++) {
    	char* temp = argv[i];
    	string_to_upper(temp);
        printf("%s ", temp);
    }
    printf("\n\r");
}


void handle_led(int argc, char *argv[]) {
	printf("\n\rOK\n\r");
    // Convert each argument to uint32_t and pass it to led_control
    for (int i = 1; i < argc; i++) {
        uint32_t color = (uint32_t)strtol(argv[i], NULL, 0);    //strtol converts the string to a long int value and thus the typecast
        if(color<max_color_byte_value){
        	PWM_LED_control(color);
            delay_ms(one_sec_delay);  // Delay for 1 second
        }else{
        	printf(" (%X) is an Invalid Input\n\r",color);
        }

    }
}

