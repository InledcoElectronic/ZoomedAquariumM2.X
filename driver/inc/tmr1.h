/* 
 * File:   tmr1.h
 * Author: liruya
 *
 */

#ifndef TMR1_H
#define	TMR1_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "chip_16f18345.h"

#define isTMR1Overflow()        (PIR1bits.TMR1IF)
#define TMR1_ResetOverflow()    (PIR1bits.TMR1IF = 0)

    //T1CON
#define T1CON_TMR1CS_LFINTOSC       0xC0
#define T1CON_TMR1CS_T1CKI_SOSC     0x80
#define T1CON_TMR1CS_FOSC           0x40
#define T1CON_TMR1CS_FOSC_4         0x00
#define T1CON_T1CKPS_1              0x00
#define T1CON_T1CKPS_2              0x10
#define T1CON_T1CKPS_4              0x20
#define T1CON_T1CKPS_8              0x30
#define T1CON_SOSC_ENABLE           0x08
#define T1CON_SOSC_DISABLE          0x00
#define T1CON_ASYNC                 0x04
#define T1CON_TMR1ON                0x01

    //T1GCON
#define T1GCON_TMR1GE               0x80
#define T1GCON_T1GPOL               0x40
#define T1GCON_T1GTM                0x20
#define T1GCON_T1GSPM               0x10
#define T1GCON_T1GGOnDONE           0x08
#define T1GCON_T1GVAL               0x04
#define T1GCON_T1GSS_CMP2           0x03     
#define T1GCON_T1GSS_CMP1           0x02 
#define T1GCON_T1GSS_TMR0           0x01 
#define T1GCON_T1GSS_T1G            0x00  


    typedef void ( *TMR1_InterruptHandler_t ) ();

    extern void TMR1_Initialize_Default();
    extern void TMR1_StartTimer();
    extern void TMR1_StopTimer();
    extern void TMR1_ISR();
    extern void TMR1_GATE_ISR();
    extern void TMR1_SetInterruptHandler(TMR1_InterruptHandler_t handler);
    extern void TMR1_Gate_SetInterruptHandler(TMR1_InterruptHandler_t handler);


#ifdef	__cplusplus
}
#endif

#endif	/* TMR1_H */

