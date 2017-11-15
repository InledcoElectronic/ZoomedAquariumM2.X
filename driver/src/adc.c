/*
 * File:   adc.c
 * Author: liruya
 *
 */

#include "../inc/adc.h"

volatile unsigned int adc_result;

/**
 * right align, clk source fosc/16, no trigger
 */
void ADC_Initialize_Default ( )
{
	ADCON0 = 0x00;
	ADCON1 = ADCON1_ADFM_RIGHT | ADCON1_ADCS_FOSC_16;
	ADACT = ADACT_NONE;
	ADRESH = 0x00;
	ADRESL = 0x00;
}

uint16_t ADC_Conversion ( uint8_t chn )
{
	ADCON0bits.CHS = chn;
	ADCON0bits.ADON = 1;
	__delay_us ( 4 );
	ADCON0bits.GO_nDONE = 1;
	while ( !PIR1bits.ADIF );
	PIR1bits.ADIF = 0;
	return ADRES;
}


