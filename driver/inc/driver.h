/* 
 * File:   driver.h
 * Author: liruya
 *
 * Created on 2017年11月14日, 上午11:21
 */

#ifndef DRIVER_H
#define	DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include "pps.h"
#include "tmr0.h"
#include "tmr1.h"
#include "tmr2.h"
#include "tmr4.h"
#include "pwm.h"
#include "eeprom.h"
#include "eusart.h"
#include "adc.h"

#define _XTAL_FREQ	16000000
    
#define GlobleInterruptDisable()        (INTCONbits.GIE = 0)
#define GlobleInterruptEnable()         (INTCONbits.GIE = 1)
#define PeripheralInterruptDisable()    (INTCONbits.PEIE = 0)
#define PeripheralInterruptEnable()     (INTCONbits.PEIE = 1)

#ifdef	__cplusplus
}
#endif

#endif	/* DRIVER_H */

