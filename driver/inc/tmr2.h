/* 
 * File:   tmr2.h
 * Author: liruya
 *
 */

#ifndef TMR2_H
#define	TMR2_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "chip_16f18345.h"

#define T2CON_OUTPS_16      0x78
#define T2CON_OUTPS_15      0x70
#define T2CON_OUTPS_14      0x68
#define T2CON_OUTPS_13      0x60
#define T2CON_OUTPS_12      0x58
#define T2CON_OUTPS_11      0x50
#define T2CON_OUTPS_10      0x48
#define T2CON_OUTPS_9       0x40
#define T2CON_OUTPS_8       0x38
#define T2CON_OUTPS_7       0x30
#define T2CON_OUTPS_6       0x28
#define T2CON_OUTPS_5       0x20
#define T2CON_OUTPS_4       0x18
#define T2CON_OUTPS_3       0x10
#define T2CON_OUTPS_2       0x08
#define T2CON_OUTPS_1       0x00
#define T2CON_TMR2ON        0x04
#define T2CON_CKPS_64       0x03
#define T2CON_CKPS_16       0x02
#define T2CON_CKPS_4        0x01
#define T2CON_CKPS_1        0x00

    typedef void ( *TMR2_InterruptHandler_t ) ();

    extern void TMR2_Initialize_Default();
    extern void TMR2_StartTimer();
    extern void TMR2_StopTimer();
    extern void TMR2_ISR();
    extern void TMR2_SetInterruptHandler(TMR2_InterruptHandler_t handler);
    extern void TMR2_DisableInterrupt();
    extern void TMR2_EnableInterrupt();

#ifdef	__cplusplus
}
#endif

#endif	/* TMR2_H */

