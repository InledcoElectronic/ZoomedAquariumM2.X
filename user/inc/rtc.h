/* 
 * File:   rtc.h
 * Author: liruya
 *
 * Created on 2017年11月14日, 下午3:08
 */

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
    
    typedef union {

        struct {
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
        };
        uint8_t time[3];
    } Time_t;
    
    extern Time_t* RTC_GetTime();
    extern void RTC_OnSecond();
    extern bool RTC_SecondReady();
    extern bool RTC_MinuteReady();
    extern bool RTC_HourReady();

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

