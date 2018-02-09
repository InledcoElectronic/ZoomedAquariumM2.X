/* 
 * File:   ir.h
 * Author: liruya
 *
 * Created on 2017年11月15日, 上午8:59
 */

#ifndef IR_H
#define	IR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../../driver/inc/driver.h"
    
#define IR_USER_CODE        0x02FD
#define IR_USER_CODE_SWAP   0xFD02

#define IR_START_VALUE_MAX  2500        //4.5ms 2250
#define IR_START_VALUE_MIN  2000
#define IR_HIGH_VALUE_MAX   960         //1.68ms 840
#define IR_HIGH_VALUE_MIN   720
#define IR_LOW_VALUE_MAX    340         //0.56ms 280
#define IR_LOW_VALUE_MIN    220
#define IR_LONG_VALUE_MAX   1250        //2.25ms 1125
#define IR_LONG_VALUE_MIN   1000

#define STATE_IDLE          0
#define STATE_USER          1
#define STATE_KEY           2
#define STATE_RPT           3
#define STATE_STOP          4

#define RPT_COUNT           4

#define KEY_NONE            0xFF

#define	KEY_ONOFF			0x1C
#define KEY_AUTO            0x04
#define KEY_LINK_DAY        0x17
#define KEY_LINK_NIGHT      0x10
#define KEY_LINK_FISH       0x0F
#define KEY_LINK_PLANT      0x5D
#define KEYR_UP             0x0D
#define KEYG_UP				0x0E
#define KEYB_UP				0x1F
#define KEYW_UP				0x5E
#define KEYUV_UP            0x12
#define KEYR                0x1D
#define KEYG                0x1E
#define KEYB                0x07
#define KEYW                0x18
#define KEYUV               0x08
#define KEYR_DOWN           0x05
#define KEYG_DOWN           0x06
#define KEYB_DOWN           0x11
#define KEYW_DOWN           0x42
#define KEYUV_DOWN			0x15
#define KEY_P1				0x14
#define KEY_P2				0x0B
#define KEY_P3				0x1A
#define KEY_P4				0x03  
#define KEY_BRT_DEC         0x01
#define KEY_BRT_INC         0x1B
#define KEY_VOL_MUTE        0x40
#define KEY_VOL_DEC         0x16
#define KEY_VOL_INC         0x41   
#define KEY_LINK_WAVE       0x13
#define KEY_LINK_MOON       0x4C
#define KEY_LINK_CLOUD      0x02
#define KEY_LINK_STORM      0x4E   
#define KEY_SUNRISE         0x00
#define KEY_DAYLIGHT        0x50
#define KEY_SUNSET          0x4D
#define KEY_NIGHTLIGHT      0x43  
#define KEY_NUM_0           0x4B
#define KEY_NUM_1           0x5C
#define KEY_NUM_2           0x0C
#define KEY_NUM_3           0x0A
#define KEY_NUM_4           0x51
#define KEY_NUM_5           0x45
#define KEY_NUM_6           0x44
#define KEY_NUM_7           0x4F
#define KEY_NUM_8           0x46
#define KEY_NUM_9           0x48
#define KEY_TIME            0x47
#define KEY_SET             0x09

#define KEY_ERROR			255     //°´¼ü´íÎó
#define KEY_INVALID         0       //°´¼üÎÞÐ§
#define KEY_VALID_RUN       1       //°´¼üÔËÐÐ×´Ì¬ÓÐÐ§
#define KEY_VALID_SET       2       //°´¼üÉèÖÃ×´Ì¬ÓÐÐ§

#define KEY_SHORT           1
#define KEY_SHORT_LONG      2
#define KEY_LONG            3
    
#define SET_NONE            0
#define SET_TIME            1
#define SET_SUNRISE         2
#define SET_SUNSET          3
#define SET_DAYLIGHT        4
#define SET_NIGHTLIGHT      5

#define SET_DELAY_MAX       10

    typedef struct{ 
        unsigned mKeyRcv : 1;
        unsigned mKeyRpt : 1;
        unsigned mState : 3;
        unsigned mSet : 3;
        uint8_t tmIdx;
        uint8_t time[4];
        uint8_t mSetDelay;
    } IRState_t;
    
    extern volatile IRState_t ir_state;
    
    extern void IR_ResetIfTMR1Overflow();
    extern void IR_Decode();
    extern void IR_ScanLongPress();
    extern void IR_KeyAtionIfPressed();
    extern void IR_UpdateSetStatus();
    
#ifdef	__cplusplus
}
#endif

#endif	/* IR_H */

