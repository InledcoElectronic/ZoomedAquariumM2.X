#include "../inc/led.h"
#include "../inc/rtc.h"
#include "../inc/audio.h"
#include "../inc/ir.h"
#include "../inc/util.h"

static Led_LoadDutyValue_t loadDuty[CHANNEL_CNT] = {PWM5_LoadDutyValue,
    PWM2_LoadDutyValue,
    PWM4_LoadDutyValue,
    PWM3_LoadDutyValue,
    PWM1_LoadDutyValue};
const uint8_t VOLUME[VOLUME_CNT] = {14, 17, 20, 23, 26};
const uint8_t GAIN[VOLUME_CNT] = {7, 5, 3, 1, 0};
volatile LedPara_t gLedPara;
volatile LedRunPara_t gLedRunPara;

void Led_FirstPowerUp()
{
    if(gLedPara.mFirstPowerUp != 0x55){
        gLedPara.mFirstPowerUp = 0x55;
        for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
            gLedPara.mDayBright[i] = BRIGHT_MAX;
            gLedPara.mNightBright[i] = 0;
            gLedPara.mStaticDayBright[i] = BRIGHT_MAX;
            gLedPara.mStaticNightBright[i] = 0;
            gLedPara.mStaticFishBright[i] = BRIGHT_MAX;
            gLedPara.mStaticPlantBright[i] = BRIGHT_MAX;
        }
        gLedPara.mSunrise = 390;
        gLedPara.mSunset = 1110;
        gLedPara.mNightBright[2] = BRIGHT_MAX;
        gLedPara.mStaticNightBright[2] = BRIGHT_MAX;
        gLedPara.mStaticFishBright[0] = 0;
        gLedPara.mStaticFishBright[1] = 0;
        gLedPara.mStaticPlantBright[1] = 0; 
    }
}

void Led_InitPara() {
    DATAEE_ReadBuffer(LEDPARA_EEPROM_ADDR, (uint8_t *) & gLedPara, sizeof ( gLedPara));
    for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
        if (gLedPara.mBright[i] > BRIGHT_MAX) {
            gLedPara.mBright[i] = BRIGHT_MAX;
        }
        if (gLedPara.mDayBright[i] > BRIGHT_MAX) {
            gLedPara.mDayBright[i] = BRIGHT_MAX;
        }
        if (gLedPara.mNightBright[i] > BRIGHT_MAX) {
            gLedPara.mNightBright[i] = BRIGHT_MAX;
        }
        if (gLedPara.mStaticDayBright[i] > BRIGHT_MAX) {
            gLedPara.mStaticDayBright[i] = BRIGHT_MAX;
        }     
        if (gLedPara.mStaticNightBright[i] > BRIGHT_MAX) {
            gLedPara.mStaticNightBright[i] = BRIGHT_MAX;
        }      
        if (gLedPara.mStaticFishBright[i] > BRIGHT_MAX) {
            gLedPara.mStaticFishBright[i] = BRIGHT_MAX;
        }       
        if (gLedPara.mStaticPlantBright[i] > BRIGHT_MAX) {
            gLedPara.mStaticPlantBright[i] = BRIGHT_MAX;
        }             
        for (uint8_t j = 0; j < CUSTOM_CNT; j++) {
            if (gLedPara.mCustom[j][i] > BRIGHT_MAX) {
                gLedPara.mCustom[j][i] = BRIGHT_MAX;
            }
        }
        if (gLedPara.mMsc > MUSIC_STORM_INDEX) {
            gLedPara.mMsc = MUSIC_NONE_INDEX;
        }
        if (gLedPara.mSunrise > 1439) {
            gLedPara.mSunrise = 0;
        }
        if (gLedPara.mSunset > 1439) {
            gLedPara.mSunset = 0;
        }
        if (gLedPara.mVolume > VOLUME_MAX) {
            gLedPara.mVolume = VOLUME_MAX;
        }
#if	VOLUME_MIN > 0
        if (gLedPara.mVolume < VOLUME_MIN) {
            gLedPara.mVolume = VOLUME_MIN;
        }
#endif
    }
    Led_FirstPowerUp();
}

void Audio_Initialize(){
    __delay_ms(640);
    CLRWDT();
    Audio_StopSound();
    __delay_ms(480);
    Audio_SetVolume(gLedPara.mVolOn ? VOLUME[ gLedPara.mVolume ] : 0);
    __delay_ms(480);
    Audio_SetPlayMode(MODE_SINGLE_CYCLE);
    __delay_ms(480);
}

void Led_Initialize() {
    uint16_t ct = RTC_GetTime()->hour * 60u + RTC_GetTime()->minute;
    if (!gLedPara.mAuto) {
        if (!gLedPara.mOn) {
            Led_TurnOffRamp();
        } else {
            if (gLedPara.mMsc) {
                gLedRunPara.music_index = gLedPara.mMsc;
                gLedRunPara.music_state = 1;
                switch (gLedPara.mMsc) {
                    case MUSIC_DAY_INDEX:
                        gLedRunPara.mTargetBright[0] = gLedPara.mStaticDayBright[0];
                        gLedRunPara.mTargetBright[1] = gLedPara.mStaticDayBright[1];
                        gLedRunPara.mTargetBright[2] = gLedPara.mStaticDayBright[2];
                        gLedRunPara.mTargetBright[3] = gLedPara.mStaticDayBright[3];
                        gLedRunPara.mTargetBright[4] = gLedPara.mStaticDayBright[4];
//                        Led_UpdateBright();
                        break;
                    case MUSIC_NIGHT_INDEX:
                        gLedRunPara.mTargetBright[0] = gLedPara.mStaticNightBright[0];
                        gLedRunPara.mTargetBright[1] = gLedPara.mStaticNightBright[1];
                        gLedRunPara.mTargetBright[2] = gLedPara.mStaticNightBright[2];
                        gLedRunPara.mTargetBright[3] = gLedPara.mStaticNightBright[3];
                        gLedRunPara.mTargetBright[4] = gLedPara.mStaticNightBright[4];
//                        Led_UpdateBright();
                        break;
                    case MUSIC_FISH_INDEX:
                        gLedRunPara.mTargetBright[0] = gLedPara.mStaticFishBright[0];
                        gLedRunPara.mTargetBright[1] = gLedPara.mStaticFishBright[1];
                        gLedRunPara.mTargetBright[2] = gLedPara.mStaticFishBright[2];
                        gLedRunPara.mTargetBright[3] = gLedPara.mStaticFishBright[3];
                        gLedRunPara.mTargetBright[4] = gLedPara.mStaticFishBright[4];
//                        Led_UpdateBright();
                        break;
                    case MUSIC_PLANT_INDEX:
                        gLedRunPara.mTargetBright[0] = gLedPara.mStaticPlantBright[0];
                        gLedRunPara.mTargetBright[1] = gLedPara.mStaticPlantBright[1];
                        gLedRunPara.mTargetBright[2] = gLedPara.mStaticPlantBright[2];
                        gLedRunPara.mTargetBright[3] = gLedPara.mStaticPlantBright[3];
                        gLedRunPara.mTargetBright[4] = gLedPara.mStaticPlantBright[4];
//                        Led_UpdateBright();
                        break;
                    default:
                        break;
                }
            } else {
                Led_TurnOnRamp();
            }
        }
    } else {
        bool result = false;
        uint8_t i;
        if (gLedPara.mSunrise < gLedPara.mSunset) {
            if (ct >= gLedPara.mSunrise && ct < gLedPara.mSunset) {
                result = true;
            }
        } else if (gLedPara.mSunrise > gLedPara.mSunset) {
            if (ct >= gLedPara.mSunrise || ct < gLedPara.mSunset) {
                result = true;
            }
        }
        if (result) {
            for (i = 0; i < CHANNEL_CNT; i++) {
                gLedRunPara.mTargetBright[i] = gLedPara.mDayBright[i];
                gLedRunPara.mCurrentBright[i] = gLedPara.mDayBright[i];
            }
        } else {
            for (i = 0; i < CHANNEL_CNT; i++) {
                gLedRunPara.mTargetBright[i] = gLedPara.mNightBright[i];
                gLedRunPara.mCurrentBright[i] = gLedPara.mNightBright[i];
            }
        }
        Led_UpdateBright();
    }
}

void Led_SaveParaIfChanged() {
    if (gLedRunPara.mParaChanged) {
        gLedRunPara.mParaChanged = 0;
        DATAEE_WriteBuffer(LEDPARA_EEPROM_ADDR, (uint8_t *) & gLedPara, sizeof ( gLedPara));
    }
}

void Led_UpdateBright() {
    for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
        loadDuty[i](gLedRunPara.mCurrentBright[i]);
    }
}

void Led_TurnOnDirect() {
    CCP1CON |= 0x80;
    CCP2CON |= 0x80;
    CCP3CON |= 0x80;
    CCP4CON |= 0x80;
    PWM5CON |= 0x80;
}

void Led_TurnOffDirect() {
    CCP1CON &= 0x7F;
    CCP2CON &= 0x7F;
    CCP3CON &= 0x7F;
    CCP4CON &= 0x7F;
    PWM5CON &= 0x7F;
}

void Led_TurnOnRamp() {
    gLedPara.mOn = 1;
    for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
        gLedRunPara.mTargetBright[i] = gLedPara.mBright[i];
    }
}

void Led_TurnOffRamp() {
    gLedPara.mOn = 0;
    for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
        gLedRunPara.mTargetBright[i] = 0;
    }
}

/*
void Led_IncreaseBright ( uint8_t chn, uint8_t delta )
{
    if ( chn < CHANNEL_CNT )
    {
        if ( gLedPara.mBright[chn] + delta < BRIGHT_MAX )
        {
            gLedPara.mBright[chn] += delta;
        }
        else
        {
            gLedPara.mBright[chn] = BRIGHT_MAX;
        }
        gLedRunPara.mTargetBright[chn] = gLedPara.mBright[chn];
    }
}

void Led_DecreaseBright ( uint8_t chn, uint8_t delta )
{
    if ( chn < CHANNEL_CNT )
    {
        if ( gLedPara.mBright[chn] > BRIGHT_MIN + delta )
        {
            gLedPara.mBright[chn] -= delta;
        }
        else
        {
            gLedPara.mBright[chn] = BRIGHT_MIN;
        }
        gLedRunPara.mTargetBright[chn] = gLedPara.mBright[chn];
    }
}

void Led_SetBright ( uint8_t chn, uint16_t value )
{
    if ( chn < CHANNEL_CNT )
    {
        if ( value > BRIGHT_MAX || value < BRIGHT_MIN )
        {
            return;
        }
        gLedPara.mBright[chn] = value;
        gLedRunPara.mTargetBright[chn] = gLedPara.mBright[chn];
    }
}

void Led_SetBrights ( uint16_t *pValue )
{
    uint16_t value;
    for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
    {
        value = *pValue++;
        if ( value <= BRIGHT_MAX && value >= BRIGHT_MIN )
        {
            gLedPara.mBright[i] = value;
            gLedRunPara.mTargetBright[i] = value;
        }
    }
}
 */
void Led_SetCustom(uint8_t idx, uint16_t *pValue) {
    uint16_t value;
    if (idx >= CUSTOM_CNT) {
        return;
    }
    for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
        value = *pValue++;
#if		BRIGHT_MIN > 0
        if (value <= BRIGHT_MAX && value >= BRIGHT_MIN)
#else
        if (value <= BRIGHT_MAX)
#endif		
        {
            gLedPara.mCustom[idx][i] = value;
        }
    }
}

void Led_Ramp() {
    for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
        if (gLedRunPara.mCurrentBright[i] + BRIGHT_STEP_RAMP < gLedRunPara.mTargetBright[i]) {
            gLedRunPara.mCurrentBright[i] += BRIGHT_STEP_RAMP;
        } else if (gLedRunPara.mCurrentBright[i] > gLedRunPara.mTargetBright[i] + BRIGHT_STEP_RAMP) {
            gLedRunPara.mCurrentBright[i] -= BRIGHT_STEP_RAMP;
        } else {
            gLedRunPara.mCurrentBright[i] = gLedRunPara.mTargetBright[i];
        }
        loadDuty[i](gLedRunPara.mCurrentBright[i]);
    }
    //    Led_UpdateBright();
}

/**
 * Check auto status, run every minute
 */
//void Led_CheckAutoStatus() {
//    uint16_t ct = RTC_GetTime()->hour * 60u + RTC_GetTime()->minute;
//    uint16_t sunrise = gLedPara.mSunrise;
//    uint16_t sunset = gLedPara.mSunset;
//    bool result = false;
//    if (sunrise < sunset) {
//        if (ct >= sunrise && ct < sunset) {
//            result = true;
//        }
//    } else if (sunrise > sunset) {
//        if (ct >= sunrise || ct < sunset) {
//            result = true;
//        }
//    }
//    if (result) {
//        for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
//            gLedRunPara.mTargetBright[i] = gLedPara.mDayBright[i];
//        }
//    } else {
//        for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
//            gLedRunPara.mTargetBright[i] = gLedPara.mNightBright[i];
//        }
//    }
//}

  void Led_CheckAutoStatus() {
    uint16_t ct = RTC_GetTime()->hour * 60u + RTC_GetTime()->minute;
    uint16_t sunrise = gLedPara.mSunrise;
    uint16_t sunset = gLedPara.mSunset;
    if (sunrise == sunset) {
        for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
            gLedRunPara.mTargetBright[i] = gLedPara.mNightBright[i];
            gLedRunPara.mCurrentBright[i] = gLedPara.mNightBright[i];
        }
        gLedRunPara.auto_state = 0;
        gLedRunPara.auto_num = 0;
        Led_UpdateBright();
        return;
    }
    if (ct == sunrise) {
        for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
            gLedRunPara.mTargetBright[i] = gLedPara.mDayBright[i];
        }
        gLedRunPara.auto_state = 1;
        gLedRunPara.auto_num = 0;
        return;
    }
    if (ct == sunset) {
        for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
            gLedRunPara.mTargetBright[i] = gLedPara.mNightBright[i];
        }
        gLedRunPara.auto_state = 2;
        gLedRunPara.auto_num = 0;
        return;
    }
}

void Led_AutoRun() {
    if (gLedRunPara.auto_state == 1 && gLedRunPara.auto_num < 250) {
        Util_IncValue((uint16_t *) & gLedRunPara.mCurrentBright[0], BRIGHT_MAX, 4);
    } else if (gLedRunPara.auto_state == 2 && gLedRunPara.auto_num < 1000) {
        Util_IncValue((uint16_t *) & gLedRunPara.mCurrentBright[0], BRIGHT_MAX, 1);
    } else {
        gLedRunPara.auto_state = 0;
        if (gLedRunPara.mCurrentBright[0] < gLedRunPara.mTargetBright[0]) {
            gLedRunPara.mCurrentBright[0]++;
        } else if (gLedRunPara.mCurrentBright[0] > gLedRunPara.mTargetBright[0]) {
            gLedRunPara.mCurrentBright[0]--;
        }
    }
    gLedRunPara.auto_num++;
    if ((gLedRunPara.auto_num & 0x01) == 0) {
        for (uint8_t i = 1; i < CHANNEL_CNT; i++) {
            if (gLedRunPara.mCurrentBright[i] < gLedRunPara.mTargetBright[i]) {
                gLedRunPara.mCurrentBright[i]++;
            } else if (gLedRunPara.mCurrentBright[i] > gLedRunPara.mTargetBright[i]) {
                gLedRunPara.mCurrentBright[i]--;
            }
        }
    }
    Led_UpdateBright();
}

/**
 * Auto mode,run every second
 */
//void Led_AutoRun() {
//    static uint8_t state = 0;
//    uint8_t step[CHANNEL_CNT] = {4, 1, 1, 1, 1};
//    state++;
//    if (state >= 2) {
//        state = 0;
//        for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
//            if (gLedRunPara.mCurrentBright[i] + step[i] < gLedRunPara.mTargetBright[i]) {
//                gLedRunPara.mCurrentBright[i] += step[i];
//            } else if (gLedRunPara.mCurrentBright[i] > gLedRunPara.mTargetBright[i] + step[i]) {
//                gLedRunPara.mCurrentBright[i] -= step[i];
//            } else {
//                gLedRunPara.mCurrentBright[i] = gLedRunPara.mTargetBright[i];
//            }
//        }
//        Led_UpdateBright();
//    }
//}

void Led_StartNotice(uint8_t cnt) {
    gLedRunPara.mNoticeCount = cnt;
    TMR4_StartTimer();
}

void Led_Notice() {
    static uint8_t cnt = 0;
    if (gLedRunPara.mNoticeCount) {
        cnt++;
        if ((cnt & 0x07) == 0) {
            if (gLedRunPara.mNoticeStatus) {
                Led_TurnOnDirect();
                gLedRunPara.mNoticeCount--;
                gLedRunPara.mNoticeStatus = 0;
            } else {
                Led_TurnOffDirect();
                gLedRunPara.mNoticeStatus = 1;
            }
        }
    } else {
        TMR4_StopTimer();
        cnt = 0;
    }
}

void Led_DynamicWave(uint16_t ptp) {
    uint8_t i;
    uint16_t val = ptp * ( 6 + GAIN[gLedPara.mVolume] );
    uint16_t duty[CHANNEL_CNT] = {500, 500, 500, 200, 500};
    duty[3] += val;
    if (duty[3] > BRIGHT_MAX) {
        duty[3] = BRIGHT_MAX;
    }
    for (i = 0; i < CHANNEL_CNT; i++) {
        if (gLedRunPara.mCurrentBright[i] < duty[i]) {
            gLedRunPara.mCurrentBright[i]++;
        } else if (gLedRunPara.mCurrentBright[i] > duty[i]) {
            gLedRunPara.mCurrentBright[i]--;
        }
    }
    Led_UpdateBright();
}

void Led_DynamicMoon(uint16_t ptp) {
    uint8_t i;
    uint16_t val = ptp * ( 5 + GAIN[gLedPara.mVolume] );
    uint16_t duty[CHANNEL_CNT] = {0, 0, BRIGHT_MAX, 200, 0};
    if (duty[3] > val) {
        duty[3] -= val;
    } else {
        duty[3] = 0;
    }
    for (i = 0; i < CHANNEL_CNT; i++) {
        if (gLedRunPara.mCurrentBright[i] < duty[i]) {
            gLedRunPara.mCurrentBright[i]++;
        } else if (gLedRunPara.mCurrentBright[i] > duty[i]) {
            gLedRunPara.mCurrentBright[i]--;
        }
    }
    Led_UpdateBright();
}

void Led_DynamicCloud(uint16_t ptp) {
    uint8_t i;
    uint16_t val = ptp * ( 16 + GAIN[gLedPara.mVolume] );
    uint16_t duty[CHANNEL_CNT] = {200, 200, 400, 320, 400};
    duty[2] += val;
    if (duty[2] > BRIGHT_MAX) {
        duty[2] = BRIGHT_MAX;
    }
    if (duty[3] > val) {
        duty[3] -= val;
    } else {
        duty[3] = 0;
    }
    duty[4] += val;
    if (duty[4] > BRIGHT_MAX) {
        duty[4] = BRIGHT_MAX;
    }
    for (i = 0; i < CHANNEL_CNT; i++) {
        if (gLedRunPara.mCurrentBright[i] < duty[i]) {
            gLedRunPara.mCurrentBright[i]++;
        } else if (gLedRunPara.mCurrentBright[i] > duty[i]) {
            gLedRunPara.mCurrentBright[i]--;
        }
    }
    Led_UpdateBright();
}

void Led_DynamicStorm(uint16_t ptp) {
    uint8_t i;
    uint16_t val = ptp * ( 5 + GAIN[gLedPara.mVolume] );
    uint16_t duty[CHANNEL_CNT] = {0, 0, 600, 64, 0};
    if (duty[2] > val) {
        duty[2] -= val;
    } else {
        duty[2] = 0;
    }
    duty[3] += val;
    if( duty[3] > BRIGHT_MAX )
    {
        duty[3] = BRIGHT_MAX;
    }
    for (i = 0; i < CHANNEL_CNT; i++) {
        if (gLedRunPara.mCurrentBright[i] < duty[i]) {
            gLedRunPara.mCurrentBright[i]++;
        } else if (gLedRunPara.mCurrentBright[i] > duty[i]) {
            gLedRunPara.mCurrentBright[i]--;
        }
    }
    Led_UpdateBright();
}

void Led_RunMusic() {
    if (gLedRunPara.music_state < 32) {
        gLedRunPara.music_state++;
    } else if (gLedRunPara.music_state == 32) {
        Audio_SelectSound(gLedPara.mMsc + 0x30);
        gLedRunPara.music_state++;
    } else if (gLedRunPara.music_state < 64) {
        gLedRunPara.music_state++;
    } else if (gLedRunPara.music_state == 64) {
//        Audio_PlaySound();
        gLedRunPara.music_state++;
    }
    if (gLedPara.mDyn) {
        switch (gLedPara.mMsc) {
            case MUSIC_WAVE_INDEX:
                Led_DynamicWave(audio_value);
                break;
            case MUSIC_MOON_INDEX:
                Led_DynamicMoon(audio_value);
                break;
            case MUSIC_CLOUD_INDEX:
                Led_DynamicCloud(audio_value);
                break;
            case MUSIC_STORM_INDEX:
                Led_DynamicStorm(audio_value);
                break;
            default:
                break;
        }
    }
}

void Led_Run() {
    static uint8_t cnt = 0;
    cnt++;
    if ((cnt & 0x03) == 0x00) {
        IR_ScanLongPress();
    }
    if ((ir_state.mSet == SET_DAYLIGHT) || (ir_state.mSet == SET_NIGHTLIGHT)) {
        Led_Ramp();
    } else if (!gLedPara.mAuto) {
        if (gLedPara.mOn && gLedPara.mMsc) {
            if(gLedPara.mMsc == MUSIC_DAY_INDEX || gLedPara.mMsc == MUSIC_NIGHT_INDEX || gLedPara.mMsc == MUSIC_FISH_INDEX || gLedPara.mMsc == MUSIC_PLANT_INDEX) {
                Led_Ramp();   
            }
            Led_RunMusic();
        } else {
            Led_Ramp();
        }
    }
}