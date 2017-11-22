#include "../inc/tmr4.h"

TMR4_InterruptHandler_t tmr4_isr_handler;

//timer 4 APIs

void TMR4_Initialize_Default ( )
{
	T4CON = T4CON_CKPS_64 | T4CON_OUTPS_16;
	PR4 = 0xF9;
	TMR4 = 0x00;

	PIR2bits.TMR4IF = 0;
	PIE2bits.TMR4IE = 1;
}

void TMR4_StartTimer ( void )
{
	T4CONbits.TMR4ON = 1;
}

void TMR4_StopTimer ( void )
{
	T4CONbits.TMR4ON = 0;
}

void TMR4_ISR ( )
{
	PIR2bits.TMR4IF = 0;

	if ( tmr4_isr_handler )
	{
		tmr4_isr_handler ( );
	}
}

void TMR4_SetInterruptHandler ( TMR4_InterruptHandler_t handler )
{
	tmr4_isr_handler = handler;
}