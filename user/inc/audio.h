/* 
 * File:   audio.h
 * Author: liruya
 *
 * Created on 2017年11月14日, 上午9:11
 */

#ifndef AUDIO_H
#define	AUDIO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../../driver/inc/driver.h"

#define FRAME_HEADER            0x7E
#define FRAME_END               0xEF
#define CMD_PLAY                0xAA
#define CMD_STOP                0xAB
#define CMD_VOLUME_SET          0xAE
#define CMD_SOUND               0xA1
#define CMD_MODE                0xAF
    
#define MODE_SINGLE_NOCYCLE     0x00
#define MODE_SINGLE_CYCLE       0x01
#define MODE_ALL                0x02
#define MODE_RANDOM             0x03 

#define ADCHS_AUDIO         ADCHS_ANC2
    
    extern volatile uint16_t audio_value;
    
    extern void Audio_PlaySound();
    extern void Audio_StopSound();
    extern void Audio_SelectSound(uint8_t index);
    extern void Audio_SetPlayMode(uint8_t type);
    extern void Audio_SetVolume(uint8_t vol);
    extern void Audio_GetValue();

#ifdef	__cplusplus
}
#endif

#endif	/* AUDIO_H */

