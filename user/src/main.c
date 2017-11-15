#include "../../driver/inc/driver.h"

// CONFIG1
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1    // Power-up default value for COSC bits->HFINTOSC
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O or oscillator function on OSC2
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is disabled

// CONFIG2
#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR/VPP pin function is MCLR; Weak pull-up enabled
#pragma config PWRTE = ON    // Power-up Timer Enable bit->PWRT enabled
#pragma config WDTE = ON    // Watchdog Timer Enable bits->WDT enabled, SWDTEN is ignored
#pragma config LPBOREN = OFF    // Low-power BOR enable bit->ULPBOR disabled
#pragma config BOREN = OFF    // Brown-out Reset Enable bits->Brown-out Reset disabled
#pragma config BORV = HIGH    // Brown-out Reset Voltage selection bit->Brown-out voltage (Vbor) set to 2.7V
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a Reset
#pragma config DEBUG = OFF    // Debugger enable bit->Background debugger disabled

// CONFIG3
#pragma config WRT = OFF    // User NVM self-write protection bits->Write protection off
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.

// CONFIG4
#pragma config CP = OFF    // User NVM Program Memory Code Protection bit->User NVM code protection disabled
#pragma config CPD = OFF    // Data NVM Memory Code Protection bit->Data NVM code protection disabled

void main ( )
{
	SYSTEM_Initialize ( );

	while ( 1 )
	{
		CLRWDT ( );
	}
}

void OSCILLATOR_Initialize ( void )
{
	// NOSC HFINTOSC; NDIV 1; 
	OSCCON1 = 0x60;
	// CSWHOLD may proceed; SOSCPWR Low power; SOSCBE crystal oscillator; 
	OSCCON3 = 0x00;
	// LFOEN disabled; ADOEN disabled; SOSCEN enabled; EXTOEN disabled; HFOEN enabled; 
	OSCEN = 0x48;
	// HFFRQ 16_MHz; 
	OSCFRQ = 0x06;
	// HFTUN 0; 
	OSCTUNE = 0x00;
}

void PIN_Initialize ( )
{
	LATA = 0x00;
	LATB = 0x00;
	LATC = 0x00;

	TRISA = 0x20;
	TRISB = 0x80;
	TRISC = 0x05;

	ANSELC = 0x04;
	ANSELB = 0x00;
	ANSELA = 0x00;

	WPUB = 0x80;
	WPUA = 0x00;
	WPUC = 0x01;

	ODCONA = 0x00;
	ODCONB = 0x00;
	ODCONC = 0x00;

	unsigned char state = GIE;
	GIE = 0;
	PPSLOCK = 0x55;
	PPSLOCK = 0xAA;
	PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

	RC5PPSbits.RC5PPS = PPS_OUTPUT_CCP1; //RC3->CCP1;
	RC4PPSbits.RC4PPS = PPS_OUTPUT_CCP2; //RC4->CCP2;
	RC3PPSbits.RC3PPS = PPS_OUTPUT_CCP3; //RC5->CCP3;
	RC6PPSbits.RC6PPS = PPS_OUTPUT_CCP4; //RC1->CCP4;
	RA0PPSbits.RA0PPS = PPS_OUTPUT_PWM5; //RA0->PWM5;
	T1GPPSbits.T1GPPS = PPS_INPUT_RC0; //RC0->T1G; 
	RB4PPSbits.RB4PPS = PPS_OUTPUT_TX; //TX->RB4

	PPSLOCK = 0x55;
	PPSLOCK = 0xAA;
	PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

	GIE = state;
}

void SYSTEM_Initialize ( )
{
	PIN_Initialize ( );
	OSCILLATOR_Initialize ( );
	TMR0_Initialize_Default ( );
	TMR2_Initialize_Default ( );
	PWM1_Initialize ( );
	PWM2_Initialize ( );
	PWM3_Initialize ( );
	PWM4_Initialize ( );
	PWM5_Initialize ( );
	EUSART_Initialize_Default ( );
	ADC_Initialize_Default ( );
}
