/* 
 * File:   tmr0.h
 * Author: liruya
 *
 */

#ifndef TMR0_H
#define	TMR0_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "chip_16f18345.h"

    //T0CON0
#define T0CON0_EN               0x80
#define T0CON0_16BIT            0x10
#define T0CON0_OUTPS_1          0x00     
#define T0CON0_OUTPS_2          0x01     
#define T0CON0_OUTPS_3          0x02     
#define T0CON0_OUTPS_4          0x03     
#define T0CON0_OUTPS_5          0x04     
#define T0CON0_OUTPS_6          0x05     
#define T0CON0_OUTPS_7          0x06     
#define T0CON0_OUTPS_8          0x07     
#define T0CON0_OUTPS_9          0x08     
#define T0CON0_OUTPS_10         0x09     
#define T0CON0_OUTPS_11         0x0A     
#define T0CON0_OUTPS_12         0x0B     
#define T0CON0_OUTPS_13         0x0C     
#define T0CON0_OUTPS_14         0x0D     
#define T0CON0_OUTPS_15         0x0E     
#define T0CON0_OUTPS_16         0x0F 

    //T0CON1
#define T0CON1_CS_T0CKI         0x00
#define T0CON1_CS_T0CKI_INVERT  0x20
#define T0CON1_CS_FOSC_4        0x40
#define T0CON1_CS_HFINTOSC      0x60
#define T0CON1_CS_LFINTOSC      0x80
#define T0CON1_CS_RESERVED      0xA0
#define T0CON1_CS_SOSC          0xC0
#define T0CON1_CS_CLC1          0xE0
#define T0CON1_ASYNC            0x10
#define T0CON1_SYNC             0x00    
#define T0CON1_CKPS_1           0x00
#define T0CON1_CKPS_2           0x01
#define T0CON1_CKPS_4           0x02
#define T0CON1_CKPS_8           0x03
#define T0CON1_CKPS_16          0x04
#define T0CON1_CKPS_32          0x05
#define T0CON1_CKPS_64          0x06
#define T0CON1_CKPS_128         0x07
#define T0CON1_CKPS_256         0x08
#define T0CON1_CKPS_512         0x09
#define T0CON1_CKPS_1024        0x0A
#define T0CON1_CKPS_2048        0x0B
#define T0CON1_CKPS_4096        0x0C
#define T0CON1_CKPS_8192        0x0D
#define T0CON1_CKPS_16384       0x0E
#define T0CON1_CKPS_32768       0x0F

    typedef void ( *TMR0_InterruptHandler_t) ();

    /*TMR0 APIs*/
    extern void TMR0_Initialize_Default();
    extern void TMR0_StartTimer();
    extern void TMR0_StopTimer();
    extern void TMR0_ISR();
    extern void TMR0_SetInterruptHandler(TMR0_InterruptHandler_t handler);

#ifdef	__cplusplus
}
#endif

#endif	/* TMR0_H */

