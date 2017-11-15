/* 
 * File:   pps.h
 * Author: liruya
 *
 * Created on 2017年11月14日, 上午9:50
 */

#ifndef PPS_H
#define	PPS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PPS_INPUT_RC7   0x17
#define PPS_INPUT_RC6   0x16
#define PPS_INPUT_RC5   0x15
#define PPS_INPUT_RC4   0x14
#define PPS_INPUT_RC3   0x13
#define PPS_INPUT_RC2   0x12
#define PPS_INPUT_RC1   0x11
#define PPS_INPUT_RC0   0x10
#define PPS_INPUT_RB7   0x0F
#define PPS_INPUT_RB6   0x0E
#define PPS_INPUT_RB5   0x0D
#define PPS_INPUT_RB4   0x0C
#define PPS_INPUT_RA5   0x05
#define PPS_INPUT_RA4   0x04
#define PPS_INPUT_RA3   0x03
#define PPS_INPUT_RA2   0x02
#define PPS_INPUT_RA1   0x01
#define PPS_INPUT_RA0   0x00
    
#define PPS_OUTPUT_DSM      0x01F
#define PPS_OUTPUT_CLKR     0x01E
#define PPS_OUTPUT_NCO1     0x01D
#define PPS_OUTPUT_TMR0     0x01C
#define PPS_OUTPUT_SDAT     0x019
#define PPS_OUTPUT_SCLK     0x018
#define PPS_OUTPUT_C2OUT    0x017
#define PPS_OUTPUT_C1OUT    0x016
#define PPS_OUTPUT_DT       0x015
#define PPS_OUTPUT_TX       0x013
#define PPS_OUTPUT_CWG2D    0x013
#define PPS_OUTPUT_CWG2C    0x012
#define PPS_OUTPUT_CWG2B    0x011
#define PPS_OUTPUT_CWG2A    0x010
#define PPS_OUTPUT_CCP4     0x0F
#define PPS_OUTPUT_CCP3     0x0E
#define PPS_OUTPUT_CCP2     0x0D
#define PPS_OUTPUT_CCP1     0x0C
#define PPS_OUTPUT_CWG1D    0x0B
#define PPS_OUTPUT_CWG1C    0x0A
#define PPS_OUTPUT_CWG1B    0x09
#define PPS_OUTPUT_CWG1A    0x08
#define PPS_OUTPUT_CLC4OUT  0x07
#define PPS_OUTPUT_CLC3OUT  0x06
#define PPS_OUTPUT_CLC2OUT  0x05
#define PPS_OUTPUT_CLC1OUT  0x04
#define PPS_OUTPUT_PWM6     0x03
#define PPS_OUTPUT_PWM5     0x02


#ifdef	__cplusplus
}
#endif

#endif	/* PPS_H */

