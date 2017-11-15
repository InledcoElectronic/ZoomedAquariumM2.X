#include "../inc/tmr0.h"

TMR0_InterruptHandler_t tmr0_isr_handler;

void TMR0_Initialize_Default ( )
{
	T0CON0 = T0CON0_OUTPS_1;
	T0CON1 = T0CON1_CS_SOSC | T0CON1_ASYNC | T0CON1_CKPS_128;

	TMR0H = 0xFF;
	TMR0L = 0x00;

	PIR0bits.TMR0IF = 0;
	PIE0bits.TMR0IE = 1;
}

void TMR0_StartTimer ( )
{
	T0CON0bits.T0EN = 1;
}

void TMR0_StopTimer ( )
{
	T0CON0bits.T0EN = 0;
}

void TMR0_ISR ( )
{
	PIR0bits.TMR0IF = 0;

	if ( tmr0_isr_handler )
	{
		tmr0_isr_handler ( );
	}
}

void TMR0_SetInterruptHandler ( TMR0_InterruptHandler_t handler )
{
	tmr0_isr_handler = handler;
}

