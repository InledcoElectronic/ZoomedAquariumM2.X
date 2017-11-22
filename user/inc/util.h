/* 
 * File:   util.h
 * Author: liruya
 *
 * Created on 2017年11月15日, 上午10:56
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

    extern void Util_IncValue(uint16_t *pSrc, uint16_t max, uint16_t delta);
    extern void Util_DecValue(uint16_t *pSrc, uint16_t min, uint16_t delta);
    

#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */

