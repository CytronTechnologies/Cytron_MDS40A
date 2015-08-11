/*******************************************************************************
*
* THIS SOFTWARE IS PROVIDED IN AN ¡°AS IS¡± CONDITION. NO WARRANTY AND SUPPORT
* IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
* DAMAGES, FOR ANY REASON WHATSOEVER.
*
********************************************************************************
*
* SMARTDRIVE40 SAMPLE SOURCE CODE (SIGN-MAGNITUDE PWM MODE)
*
*
*
* DESCRIPTION:
*
* This is the sample source code to control the SmartDrive40 with PIC16F877A.
* In this example, SW1 and SW2 are used to control the motor:
* SW1	- Forward in full speed.
* SW2	- Reverse in full speed.
*
* Motor stops when no switch is pressed.
*
*
*
* CONNECTION:
*
* SmartDrive40		PIC16F877A
* ============		==========
* IN1				RC2
* IN2				RC1
*
*
*
* DIP SWITCH SETTINGS: 10010001
*
*
*
* AUTHOR   : Kong Wai Weng
* COMPANY  : Cytron Technologies Sdn Bhd
* REVISION : 1.0
* DATE     : 21/02/2012
*
*******************************************************************************/



#include <htc.h>



/*******************************************************************************
* DEVICE CONFIGURATION WORDS                                                   *
*******************************************************************************/

__CONFIG(FOSC_HS &		// High Speed Crystal.
		 WDTE_OFF &		// Disable Watchdog Timer.
		 PWRTE_ON &		// Enable Power Up Timer.
		 BOREN_OFF &	// Disable Brown Out Reset.
		 LVP_OFF);		// Disable Low Voltage Programming.



/*******************************************************************************
* PRIVATE CONSTANT DEFINITION                                                  *
*******************************************************************************/

// Oscillator Frequency.
#define	_XTAL_FREQ		20000000

// IO Connection.
#define LED1			PORTBbits.RB6
#define LED2			PORTBbits.RB7

#define SW1				PORTBbits.RB0
#define SW2				PORTBbits.RB1

#define MDS40A_IN1		PORTCbits.RC2
#define MDS40A_IN2		PORTCbits.RC1
#define PWM				CCPR1L



/*******************************************************************************
* MAIN FUNCTION                                                                *
*******************************************************************************/
int main(void)
{
	// Set all pins on Port A as digital IO.
	ADCON1 = 0x06;
	
	// Initialize the I/Os.
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;
	TRISBbits.TRISB6 = 0;
	TRISBbits.TRISB7 = 0;
	
	TRISCbits.TRISC1 = 0;
	TRISCbits.TRISC2 = 0;
	
	
	
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	
	
	// Stop the motor in sign-magnitude mode.
	// Duty cycle = 0%;
	PWM = 0;
	
	// Setting PWM frequency = 19.52khz and turn on Timer 2.
	PR2 = 0xff;
	T2CONbits.TMR2ON = 1;
	
	// Set to operate in PWM mode.
	CCP1CONbits.CCP1M = 0b1100;
	
	
	
	
	// PWM Mode (Sign-Magnitude).
	// The DIP switch must be set to 10010001.
	while (1) {
		// If switch 1 is pressed, forward motor at full speed.
		if (SW1 == 0) {
			MDS40A_IN2 = 0;
			PWM = 255;		// Duty cycle = 100%.
		}	
		
		// If switch 2 is pressed, reverse motor at full speed.
		else if (SW1 == 0) {
			MDS40A_IN2 = 1;
			PWM = 255;		// Duty cycle = 100%.
		}	
		
		// If no switch is pressed, stop the motor.
		else {
			PWM = 0;		// Duty cycle = 0%.
		}	
	}	
}
