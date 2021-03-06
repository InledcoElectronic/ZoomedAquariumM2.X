/* 
 * File:   led.h
 * Author: liruya
 *
 * Created on 2017年11月14日, 下午1:41
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../../driver/inc/driver.h"

#define CHANNEL_CNT         5
#define CUSTOM_CNT          4
#define BRIGHT_MAX          1000
#define BRIGHT_MIN          0
#define VOLUME_CNT          5
#define VOLUME_MAX          4
#define VOLUME_MIN          0

#define BRIGHT_STEP_RAMP    1
#define BRIGHT_STEP_SEG     200
    
#define MUSIC_NONE_INDEX    0
#define MUSIC_DAY_INDEX     1
#define MUSIC_NIGHT_INDEX   2
#define MUSIC_FISH_INDEX    3
#define MUSIC_PLANT_INDEX   4
#define MUSIC_WAVE_INDEX    5
#define MUSIC_MOON_INDEX    6
#define MUSIC_CLOUD_INDEX   7
#define MUSIC_STORM_INDEX   8
    
#define NOTICE_CUSTOM_SET   1
#define NOTICE_ENTER_SET    1
#define NOTICE_EXIT_SET     1
#define NOTICE_TIMEOUT      2
#define NOTICE_ERROR        3
    
#define LEDPARA_EEPROM_ADDR 0x7010

    typedef struct {
        unsigned mAuto : 1;
        unsigned mOn : 1;
        unsigned mVolOn : 1;
        unsigned mMsc : 4;
        unsigned mDyn : 1;
        uint8_t mFirstPowerUp;
        uint8_t mVolume;
        uint16_t mBright[CHANNEL_CNT];                  //bright of manual mode
        uint16_t mCustom[CUSTOM_CNT][CHANNEL_CNT];      //custom light
        uint16_t mStaticDayBright[CHANNEL_CNT];               //static DayLight
        uint16_t mStaticNightBright[CHANNEL_CNT];             //static NightLight
        uint16_t mStaticFishBright[CHANNEL_CNT];              //static FishLight
        uint16_t mStaticPlantBright[CHANNEL_CNT];             //static PlantLight

        uint16_t mSunrise;                              //minutes in the day
        uint16_t mDayBright[CHANNEL_CNT];               //day light bright in auto mode
        uint16_t mSunset;                               //minutes in the day
        uint16_t mNightBright[CHANNEL_CNT];             //night light bright in auto mode
    } LedPara_t;

    typedef struct {
        uint16_t mCurrentBright[CHANNEL_CNT];
        uint16_t mTargetBright[CHANNEL_CNT];
        unsigned mParaChanged : 1;
        unsigned mNoticeStatus : 1;
        unsigned mNoticeCount : 6;
        uint8_t auto_state;
        uint16_t auto_num;
        uint8_t music_index;
        uint8_t music_state;
    } LedRunPara_t;
    
    typedef void ( *Led_LoadDutyValue_t) (uint16_t duty);
    
    extern volatile LedPara_t gLedPara;
    extern volatile LedRunPara_t gLedRunPara;
    extern const uint8_t VOLUME[VOLUME_CNT];
    
    extern void Led_InitPara();
    extern void Led_Initialize();
    extern void Led_SaveParaIfChanged();
    extern void Led_UpdateBright();
    extern void Led_SetCustom(uint8_t idx, uint16_t* pValue);
    extern void Led_TurnOnDirect();
    extern void Led_TurnOffDirect();
    extern void Led_TurnOnRamp();
    extern void Led_TurnOffRamp();
    extern void Led_Ramp();
    extern void Led_CheckAutoStatus();
    extern void Led_AutoRun();
    extern void Led_StartNotice(uint8_t cnt);
    extern void Led_Notice();
    extern void Led_Run();

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

