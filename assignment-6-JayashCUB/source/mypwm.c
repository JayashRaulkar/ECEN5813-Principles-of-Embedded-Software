#include "mypwm.h"

/* brief: Below is the TPM Initialization functions for PTB18 PTB19 and PTD1
 *
 *  Parameters:
 *  take PWM period value to set the MOD register in initializing TPM
 *
 * Returns:
 *  none
 *
 *  Credits:
 *  Alexander Dean
 *  source: github repo
 */
void Init_LED_PWM(uint16_t period)
{
	// Enable clock to port D and port B
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTB_MASK;

	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(3);		//Alternate function MUX value is 3 for PTB18 for using TPM2 channel 0
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(3);	//Alternate function MUX value is 3 for PTB19 for using TPM2 channel 1
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(4);	//Alternate function MUX value is 4 for PD1 for using TPM0 channel 1

	// Configure TPM clock
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK;	//setting 24th and 26th bit for clock to TPM0 and TPM2

	//set clock source for tpm: 48 MHz
	//01 MCGFLLCLK clock or MCGPLLCLK/2 | 1 MCGPLLCLK clock with fixed divide by two
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1));

	//load the counter and mod
	TPM0->MOD = period-1;
	TPM2->MOD = period-1;

	//set TPM count direction to up with a divide by 2 prescaler
	//Prescale Factor Selection divide by 2 for both TPM0 and TPM 2
	TPM0->SC =  TPM_SC_PS(1);
	TPM2->SC = TPM_SC_PS(1);

	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	// Setting the channel of TPMs as OUTPUT compare mode and in edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	// to turn LEDs off set Duty cucle as zero
	TPM0->CONTROLS[1].CnV = 0;    //red PTD1
	TPM2->CONTROLS[0].CnV = 0;    //red PTB18
	TPM2->CONTROLS[1].CnV = 0;    //red PTB19

	//Enabling the TPM
	//LPTPM counter increments on every LPTPM counter clock
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM2->SC |= TPM_SC_CMOD(1);
}


/* brief: Below is the tricolor LED control function which set the specific LED (r g & b)
 * 		  with value from param
 *
 *  Parameters:
 *  The RGB value to for lighting the tricolor with that value
 *
 * Returns:
 *  none
 */
void PWM_LED_control(uint32_t RGB_value)
{
	TPM2->CONTROLS[0].CnV = ( (RGB_value & 0xFF0000) >>16 );    //red PTB18
	TPM2->CONTROLS[1].CnV = ( (RGB_value & 0x00FF00) >>8 );    //GREEN PTB19
	TPM0->CONTROLS[1].CnV = ( (RGB_value & 0x0000FF) );   //BLUE PTD1
}

