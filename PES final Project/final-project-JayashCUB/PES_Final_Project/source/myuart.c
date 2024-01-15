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
 * @file myuart.c
 * @brief - contains function for uart initialization, its handler and the send and recieve data function
 *
 * @author Jayash Arun Raulkar
 * @date   10 December 2023
 *
 * @reference
 * Alexander Dean github repository
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c.
 */

#include <stdio.h>
#include<string.h>
#include <mycbfifo.h>							// Header file for cbfifo
#include <MKL25Z4.H>
#include "myuart.h"								// Header file for UART

#define UART_DATA_BIT  			(1)             // For selecting the number of data bits
#define UART_PARITY 			(1)			  	// To use Parity make it 1, else 0 to disable parity
#define UART_PARITY_TYPE		(1)				// 1 for odd parity and 0 for even parity
#define UART_STOP_BIT   		(1)				// For one stop bit - put 0 and for two stop bit put 1
#define UART_OVERSAMPLE_RATE 	(16)			// oversample rate to 16
#define SYS_CLOCK				(24e6)			// system clock to 24MHz

#define ERROR			    	(-1)			// return -1 for error
#define SUCCESS      			(0)				// return 0 for success

#define SET						(1)				// Set register bit
#define CLEAR					(0)				// Clear register bit

CircularBuffer * RX_cbfifo, * TX_cbfifo;		// Declare two circular buffers for rx and tx

void Init_UART0(uint32_t baud_rate) {
	uint16_t sbr;

	// Enable UART0 and PORTA clocks
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;  //bit 10 UART0 clk enable
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;	 //bit 9 Port A clk enable

	// Disable UART0 transmitter and receiver
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Select the UART0 clock source as the FLL clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(SET);  //MCGFLLCLK clock or MCGPLLCLK/2 clock for UART0
	//SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;  // MCGPLLCLK clock with fixed divide by two

	// Configure UART0 pins
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // UART0 Rx, Set Interrupt status flag and ALT 2
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // UART0 Tx, Set Interrupt status flag and ALT 2

	// Calculate baud rate divider
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));

	// Configure baud rate
	UART0->BDH &= ~UART0_BDH_SBR_MASK;   //clear 4-0 bits
	UART0->BDH |= UART0_BDH_SBR(sbr>>8); //put 13-8 bits in baudrate register high
	UART0->BDL = UART0_BDL_SBR(sbr);	 //put 7-0 bits in baudrate register low
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1); //set oversampling ratio as 16

	// Disable Rx active edge and LIN break detect, SELECT TWO PARITY BITS by setting sbns
	UART0->BDH |= UART0_BDH_RXEDGIE(CLEAR) | UART0_BDH_SBNS(UART_STOP_BIT) | UART0_BDH_LBKDIE(CLEAR);

	//diable loopback, USE 8 BIT DATA by clearing M, ENABLE parity and set ODD PARITY
	UART0->C1 = UART0_C1_LOOPS(CLEAR) | UART0_C1_M(UART_DATA_BIT) | UART0_C1_PE(UART_PARITY) | UART0_C1_PT(UART_PARITY_TYPE);

	//dont invert transmit data and disable interrupt for errors
	UART0->C3 = UART0_C3_TXINV(CLEAR) | UART0_C3_ORIE(CLEAR)| UART0_C3_NEIE(CLEAR) | UART0_C3_FEIE(CLEAR) | UART0_C3_PEIE(CLEAR);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(SET) | UART0_S1_NF(SET) | UART0_S1_FE(SET) | UART0_S1_PF(SET);
	//UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	//send LSB First, and dont invert rx data
	UART0->S2 = UART0_S2_MSBF(CLEAR) | UART0_S2_RXINV(CLEAR);

	// Create RX and TX FIFOs
	RX_cbfifo = (CircularBuffer*)malloc(sizeof(CircularBuffer));
	TX_cbfifo = (CircularBuffer*)malloc(sizeof(CircularBuffer));
	cbfifo_init(RX_cbfifo);
	cbfifo_init(TX_cbfifo);

	// Enable UART0 interrupts in NVIC
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable UART0 receiver interrupt and transmitter
	UART0->C2 |= UART_C2_RIE(SET);
	UART0->C2 |= UART0_C2_RE(SET) | UART0_C2_TE(SET);
}


void UART0_IRQHandler(void) {
	uint32_t curr_primask = __get_PRIMASK();
	__disable_irq(); // Disable interrupts globally

	uint8_t ch;

	// Check if an error occurred
	if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		// Clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// Read the data register to clear the RDRF flag
		ch = UART0->D;
	}

	// Check if there is data to read
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// Read the data register
		ch = UART0->D;

		// Echo the character back to the sender
		//UART0->D = ch;

		// Enqueue the received character into the RX FIFO
		cbfifo_enqueue(RX_cbfifo, ch);

		// Enable TX interrupts if TX FIFO is not empty
		if (!(UART0->C2 & UART0_C2_TIE_MASK))
		{
			UART0->C2 |= UART0_C2_TIE(SET);
		}
	}

	// Check if the tx interrupt enable is set and TX register is empty i.e there is data to transmit
	if ((UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK)) {
		// Dequeue the next character to transmit
		if (TX_cbfifo->length > 0) {
			UART0->D = cbfifo_dequeue(TX_cbfifo);
		}
		else {
			// Disable TX interrupts if TX FIFO is empty
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}

	__set_PRIMASK(curr_primask);
	__enable_irq();// Enable interrupts globally
}

void uart_send_data(uint8_t *buf, int size)
{
	while((TX_cbfifo->size - TX_cbfifo->length) < size ); // Wait till there is space in the TX_cbfifo buffer

	while(*buf != '\0')
	{
		cbfifo_enqueue(TX_cbfifo, *buf);  // Enqueue each character from buffer to the TX_cbfifo buffer
		buf++;
		//ret = SUCCESS;     //return value to success
	}

	// If the TX buffer is not currently transmitting, enable transmission by setting TIE flag
	if (!(UART0->C2 & UART0_C2_TIE_MASK))
	{
		UART0->C2 |= UART0_C2_TIE(SET);
	}
}

void uart_send_integer(int data)
{
    // Convert the integer to a string
    char buffer[20];  // Adjust the buffer size based on your maximum expected integer length
    sprintf(buffer, "%d", data);

    // Send the string over UART
    uart_send_data((uint8_t*)buffer, strlen(buffer));
}


int uart_get_data(void)
 {
	while(cbfifo_is_empty(RX_cbfifo));  // Wait till RX_cbfifo gets a character
	return cbfifo_dequeue(RX_cbfifo);   // Dequeue and return the first character in the RX buffer
 }
