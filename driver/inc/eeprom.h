/* 
 * File:   eeprom.h
 * Author: liruya
 *
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "chip_16f18345.h"

    extern void DATAEE_WriteByte(uint16_t addr, uint8_t byte);
    extern uint8_t DATAEE_ReadByte(uint16_t addr);
    extern void DATAEE_WriteBuffer(uint16_t addr, uint8_t *buf, uint8_t len);
    extern void DATAEE_ReadBuffer(uint16_t addr, uint8_t *buf, uint8_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

