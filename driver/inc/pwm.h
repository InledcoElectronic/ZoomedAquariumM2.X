/* 
 * File:   pwm.h
 * Author: liruya
 *
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "chip_16f18345.h"

    void PWM1_Initialize();
    void PWM1_LoadDutyValue(uint16_t dutyValue);

    void PWM2_Initialize();
    void PWM2_LoadDutyValue(uint16_t dutyValue);

    void PWM3_Initialize();
    void PWM3_LoadDutyValue(uint16_t dutyValue);

    void PWM4_Initialize();
    void PWM4_LoadDutyValue(uint16_t dutyValue);

    void PWM5_Initialize();
    void PWM5_LoadDutyValue(uint16_t dutyValue);

    void PWM6_Initialize();
    void PWM6_LoadDutyValue(uint16_t dutyValue);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

