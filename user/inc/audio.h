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

#define FRAME_HEADER        0x7E
#define FRAME_END           0xEF
#define CMD_PLAY            0x11
#define CMD_VOLUME_INC      0x15
#define CMD_VOLUME_DEC      0x16
#define CMD_STOP            0x1E
#define CMD_VOLUME_SET      0x31
#define CMD_SOUND           0x41
#define CMD_MODE            0x33
    
#define MODE_ALL            0x00
#define MODE_FOLDER         0x01
#define MODE_SINGLE_CYCLE   0x02
#define MODE_RANDOM         0x03
#define MODE_SINGLE         0x04

#define ADCHS_AUDIO         ADCHS_ANC2
    
    extern void Audio_PlaySound();
    extern void Audio_StopSound();
    extern void Audio_SelectSound(uint8_t index);
    extern void Audio_SetPlayMode(uint8_t type);
    extern void Audio_SetVolume(uint8_t vol);

#ifdef	__cplusplus
}
#endif

#endif	/* AUDIO_H */

