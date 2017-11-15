#include "../inc/pwm.h"

extern volatile unsigned short PWM5DC @ 0x617;
extern volatile unsigned short PWM6DC @ 0x61A;

void PWM1_Initialize ( void )
{
	CCP1CON = 0x8F;
	CCPR1 = 0;
	CCPTMRSbits.C1TSEL = 0x1;
}

void PWM1_LoadDutyValue ( uint16_t dutyValue )
{
	CCPR1 = dutyValue;
}

void PWM2_Initialize ( void )
{
	CCP2CON = 0x8F;
	CCPR2 = 0;
	CCPTMRSbits.C2TSEL = 0x1;
}

void PWM2_LoadDutyValue ( uint16_t dutyValue )
{
	CCPR2 = dutyValue;
}

void PWM3_Initialize ( void )
{
	CCP3CON = 0x8F;
	CCPR3 = 0;
	CCPTMRSbits.C3TSEL = 0x1;
}

void PWM3_LoadDutyValue ( uint16_t dutyValue )
{
	CCPR3 = dutyValue;
}

void PWM4_Initialize ( void )
{
	CCP4CON = 0x8F;
	CCPR4 = 0;
	CCPTMRSbits.C4TSEL = 0x1;
}

void PWM4_LoadDutyValue ( uint16_t dutyValue )
{
	CCPR4 = dutyValue;
}

void PWM5_Initialize ( void )
{
	PWM5CON = 0x80;
	PWM5DC = 0;
	PWMTMRSbits.P5TSEL = 0x1;
}

void PWM5_LoadDutyValue ( uint16_t dutyValue )
{
	PWM5DC = dutyValue << 6;
}

void PWM6_Initialize ( void )
{
	PWM6CON = 0x80;
	PWM6DC = 0;
	PWMTMRSbits.P6TSEL = 0x1;
}

void PWM6_LoadDutyValue ( uint16_t dutyValue )
{
	PWM6DC = dutyValue << 6;
}
