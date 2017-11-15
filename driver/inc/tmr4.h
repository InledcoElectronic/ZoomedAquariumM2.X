/* 
 * File:   tmr4.h
 * Author: liruya
 *
 */

#ifndef TMR4_H
#define	TMR4_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#define T4CON_OUTPS_16      0x78
#define T4CON_OUTPS_15      0x70
#define T4CON_OUTPS_14      0x68
#define T4CON_OUTPS_13      0x60
#define T4CON_OUTPS_12      0x58
#define T4CON_OUTPS_11      0x50
#define T4CON_OUTPS_10      0x48
#define T4CON_OUTPS_9       0x40
#define T4CON_OUTPS_8       0x38
#define T4CON_OUTPS_7       0x30
#define T4CON_OUTPS_6       0x28
#define T4CON_OUTPS_5       0x20
#define T4CON_OUTPS_4       0x18
#define T4CON_OUTPS_3       0x10
#define T4CON_OUTPS_2       0x08
#define T4CON_OUTPS_1       0x00
#define T4CON_TMR4ON        0x04
#define T4CON_CKPS_64       0x03
#define T4CON_CKPS_16       0x02
#define T4CON_CKPS_4        0x01
#define T4CON_CKPS_1        0x00

    typedef void ( *TMR4_InterruptHandler_t) ();

    extern void TMR4_Initialize_Default();
    extern void TMR4_StartTimer();
    extern void TMR4_StopTimer();
    extern void TMR4_ISR();
    extern void TMR4_SetInterruptHandler(TMR4_InterruptHandler_t handler);


#ifdef	__cplusplus
}
#endif

#endif	/* TMR4_H */

