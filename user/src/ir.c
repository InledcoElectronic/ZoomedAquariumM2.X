#include "../inc/ir.h"
#include "../inc/util.h"
#include "../inc/led.h"
#include "../inc/rtc.h"
#include "../inc/audio.h"

volatile IRState_t ir_state;
volatile uint8_t keyValue;

uint8_t IR_GetIndex(uint8_t keynum) {
    uint8_t idx = 0xFF;
    switch (keynum) {
        case KEYR_UP:
        case KEYR_DOWN:
        case KEY_P1:
            idx = 0;
            break;
        case KEYG_UP:
        case KEYG_DOWN:
        case KEY_P2:
            idx = 1;
            break;
        case KEYB_UP:
        case KEYB_DOWN:
        case KEY_P3:
            idx = 2;
            break;
        case KEYW_DOWN:
        case KEYW_UP:
        case KEY_P4:
            idx = 3;
            break;
        case KEYUV_UP:
        case KEYUV_DOWN:
            idx = 4;
            break;
        case KEY_LINK_DAY:
        case KEY_LINK_NIGHT:
        case KEY_LINK_FISH:
        case KEY_LINK_PLANT:
            idx = keynum - KEY_LINK_DAY + 1;
            break;
        case KEY_LINK_WAVE:
        case KEY_LINK_MOON:
        case KEY_LINK_CLOUD:
        case KEY_LINK_STORM:
            idx = keynum - KEY_LINK_WAVE + 5;
            break;
        case KEY_NUM_0:
        case KEY_NUM_1:
        case KEY_NUM_2:
        case KEY_NUM_3:
            idx = keynum - KEY_NUM_0;
            break;
        case KEY_NUM_4:
        case KEY_NUM_5:
        case KEY_NUM_6:
        case KEY_NUM_7:
            idx = keynum - KEY_NUM_4 + 4;
            break;
        case KEY_NUM_8:
        case KEY_NUM_9:
            idx = keynum - KEY_NUM_8 + 8;
            break;
        default:
            break;
    }
    return idx;
}

bool IR_IsValidTime(uint8_t *tm, uint8_t len) {
    bool result = false;
    uint8_t hour = 0;
    uint8_t min = 0;

    switch (len) {
        case 1:
            if ((*tm) < 3) {
                result = true;
            }
            break;
        case 2:
            hour = (*tm)*10 + (*(tm + 1));
            if (hour < 24) {
                result = true;
            }
            break;
        case 3:
            hour = (*tm)*10 + (*(tm + 1));
            if (hour < 24 && (*(tm + 2)) < 6) {
                result = true;
            }
            break;
        case 4:
            hour = (*tm)*10 + (*(tm + 1));
            min = (*(tm + 2))*10 + (*(tm + 3));
            if (hour < 24 && min < 60) {
                result = true;
            }
            break;
        default:
            break;
    }
    return result;
}

uint8_t IR_GetKeyType(uint8_t keynum) {
    uint8_t result = KEY_INVALID;
    if (ir_state.mSet == SET_NONE) {
        if (keynum == KEY_AUTO || keynum == KEY_ONOFF) {
            result = KEY_SHORT;
        } else if (keynum == KEY_SUNRISE || keynum == KEY_DAYLIGHT
                || keynum == KEY_SUNSET || keynum == KEY_NIGHTLIGHT
                || keynum == KEY_TIME) {
            result = KEY_LONG;
        } else if (gLedPara.mOn) {
            switch (keynum) {
                case KEY_LINK_DAY:
                case KEY_LINK_NIGHT:
                case KEY_LINK_FISH:
                case KEY_LINK_PLANT:
                case KEY_LINK_WAVE:
                case KEY_LINK_MOON:
                case KEY_LINK_CLOUD:
                case KEY_LINK_STORM:
                    result = KEY_SHORT;
                    break;
                case KEY_BRT_INC:
                case KEY_BRT_DEC:
                    if (gLedPara.mAuto || gLedPara.mMsc == 0 || gLedPara.mMsc == MUSIC_DAY_INDEX || gLedPara.mMsc == MUSIC_NIGHT_INDEX 
                            || gLedPara.mMsc == MUSIC_FISH_INDEX || gLedPara.mMsc == MUSIC_PLANT_INDEX) {
                        result = KEY_SHORT;
                    }
                    break;
                case KEY_VOL_DEC:
                case KEY_VOL_INC:
                    if (!gLedPara.mAuto && gLedPara.mMsc) {
                        result = KEY_SHORT;
                    }
                    break;
                case KEY_P1:
                case KEY_P2:
                case KEY_P3:
                case KEY_P4:
                    if (gLedPara.mAuto || gLedPara.mMsc) {
                        result = KEY_SHORT;
                    } else {
                        result = KEY_SHORT_LONG;
                    }
                    break;
                case KEYR_UP:
                case KEYG_UP:
                case KEYB_UP:
                case KEYW_UP:
                case KEYUV_UP:
                case KEYR_DOWN:
                case KEYG_DOWN:
                case KEYB_DOWN:
                case KEYW_DOWN:
                case KEYUV_DOWN:
                    if (gLedPara.mAuto || gLedPara.mMsc == 0) {
                        result = KEY_SHORT_LONG;
                    }
                    break;
                default:
                    break;
            }
        }
    } else if (ir_state.mSet == SET_DAYLIGHT || ir_state.mSet == SET_NIGHTLIGHT) {
        switch (keynum) {
            case KEYR_UP:
            case KEYG_UP:
            case KEYB_UP:
            case KEYW_UP:
            case KEYUV_UP:
            case KEYR_DOWN:
            case KEYG_DOWN:
            case KEYB_DOWN:
            case KEYW_DOWN:
            case KEYUV_DOWN:
                result = KEY_SHORT_LONG;
                break;
            case KEY_P1:
            case KEY_P2:
            case KEY_P3:
            case KEY_P4:
            case KEY_SET:
                result = KEY_SHORT;
                break;
            default:
                result = KEY_ERROR;
                break;
        }
    } else if (ir_state.mSet == SET_TIME || ir_state.mSet == SET_SUNRISE || ir_state.mSet == SET_SUNSET) {
        switch (keynum) {
            case KEY_NUM_0:
            case KEY_NUM_1:
            case KEY_NUM_2:
            case KEY_NUM_3:
            case KEY_NUM_4:
            case KEY_NUM_5:
            case KEY_NUM_6:
            case KEY_NUM_7:
            case KEY_NUM_8:
            case KEY_NUM_9:
                result = KEY_SHORT;
                break;
            default:
                result = KEY_ERROR;
                break;
        }
    }
    return result;
}

void IR_ResetIfTMR1Overflow() {
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1_StopTimer();
        TMR1 = 0;
        ir_state.mState = STATE_IDLE;
        if (!ir_state.mKeyRpt) {
            switch (keyValue) {
                case KEYR_UP:
                case KEYG_UP:
                case KEYB_UP:
                case KEYW_UP:
                case KEYUV_UP:
                case KEYR_DOWN:
                case KEYG_DOWN:
                case KEYB_DOWN:
                case KEYW_DOWN:
                case KEYUV_DOWN:
                case KEY_P1:
                case KEY_P2:
                case KEY_P3:
                case KEY_P4:
                    ir_state.mKeyRcv = 1;
                    break;
                default:
                    break;
            }
        } else {
            ir_state.mKeyRpt = 0;
        }
        TMR2_EnableInterrupt();
        TMR1_StartTimer();
    }
}

void IR_Decode() {
    uint8_t keyNum = 0;
    uint8_t revKeyNum = 0;
    uint16_t hVal = TMR1;
    static uint16_t codeVal = 0;
    static uint8_t nBit = 0;
    static uint8_t rptCnt = 0;

    TMR1 = 0;

    switch (ir_state.mState) {
        case STATE_IDLE:
            if (hVal > IR_START_VALUE_MIN && hVal < IR_START_VALUE_MAX) {
                ir_state.mState = STATE_USER;
                codeVal = 0;
                nBit = 0;
                TMR2_DisableInterrupt();
            }
            break;

        case STATE_USER:
        case STATE_KEY:
            if (hVal > IR_LOW_VALUE_MIN && hVal < IR_LOW_VALUE_MAX) {
                nBit++;
            } else if (hVal > IR_HIGH_VALUE_MIN && hVal < IR_HIGH_VALUE_MAX) {
                codeVal |= (1 << nBit);
                nBit++;
            } else {
                ir_state.mState = STATE_IDLE;
            }
            if (nBit >= 16) {
                if (ir_state.mState == STATE_USER) {
                    if (codeVal == IR_USER_CODE_SWAP) {
                        ir_state.mState = STATE_KEY;
                    } else {
                        ir_state.mState = STATE_IDLE;
                    }
                } else if (ir_state.mState == STATE_KEY) {
                    TMR2_EnableInterrupt();
                    keyNum = codeVal & 0xFF;
                    revKeyNum = codeVal >> 8;
                    if (keyNum ^ revKeyNum == 0xFF) 
                    {
                        uint8_t type = IR_GetKeyType(keyNum);
                        if (type == KEY_ERROR) {
                            keyValue = KEY_ERROR;
                            ir_state.mKeyRcv = 1;
                            ir_state.mState = STATE_IDLE;
                        } else if (type == KEY_SHORT) {
                            keyValue = keyNum;
                            ir_state.mKeyRcv = 1;
                            ir_state.mState = STATE_IDLE;
                        } else if (type == KEY_LONG || type == KEY_SHORT_LONG) {
                            keyValue = keyNum;
                            ir_state.mState = STATE_RPT;
                            rptCnt = 0;
                        } else {
                            ir_state.mState = STATE_IDLE;
                        }
                    } else {
                        ir_state.mState = STATE_IDLE;
                    }
                }
                codeVal = 0;
                nBit = 0;
            }
            break;

        case STATE_RPT:
            if (hVal > IR_LONG_VALUE_MIN && hVal < IR_LONG_VALUE_MAX) {
                if (rptCnt < RPT_COUNT) {
                    rptCnt++;
                } else {
                    ir_state.mKeyRpt = 1;
                }
            }
            break;

        default:
            ir_state.mState = STATE_IDLE;
            break;
    }
}

void IR_ScanLongPress() {
    static uint16_t cnt = 0;
    uint8_t idx = 0;
    if (!ir_state.mKeyRpt) {
        cnt = 0;
        return;
    }
    switch (keyValue) {
        case KEYR_UP:
        case KEYG_UP:
        case KEYB_UP:
        case KEYW_UP:
        case KEYUV_UP:
            idx = IR_GetIndex(keyValue);
            Util_IncValue((uint16_t*) & gLedRunPara.mTargetBright[idx], BRIGHT_MAX, BRIGHT_STEP_RAMP);
            if (ir_state.mSet == SET_NONE) {
                gLedPara.mBright[idx] = gLedRunPara.mTargetBright[idx];
            }
            break;
        case KEYR_DOWN:
        case KEYG_DOWN:
        case KEYB_DOWN:
        case KEYW_DOWN:
        case KEYUV_DOWN:
            idx = IR_GetIndex(keyValue);
            Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[idx], BRIGHT_MIN, BRIGHT_STEP_RAMP);
            if (ir_state.mSet == SET_NONE) {
                gLedPara.mBright[idx] = gLedRunPara.mTargetBright[idx];
            }
            break;
        case KEY_P1:
        case KEY_P2:
        case KEY_P3:
        case KEY_P4:
            cnt++;
            if (cnt == 0x200) {
                ir_state.mKeyRpt = 0;
                idx = IR_GetIndex(keyValue);
                Led_SetCustom(idx, (uint16_t*) gLedRunPara.mTargetBright);
                Led_StartNotice(NOTICE_CUSTOM_SET);
                gLedRunPara.mParaChanged = 1;
            }
            break;

        case KEY_SUNRISE:
            cnt++;
            if (cnt == 0x200) {
                ir_state.mKeyRpt = 0;
                ir_state.mSet = SET_SUNRISE;
                ir_state.tmIdx = 0;
                Led_StartNotice(NOTICE_ENTER_SET);
            }
            break;
            
        case KEY_SUNSET:
            cnt++;
            if (cnt == 0x200) {
                ir_state.mKeyRpt = 0;
                ir_state.mSet = SET_SUNSET;
                ir_state.tmIdx = 0;
                Led_StartNotice(NOTICE_ENTER_SET);
            }
            break;

        case KEY_DAYLIGHT:
            cnt++;
            if (cnt == 0x200) {
                ir_state.mKeyRpt = 0;
                ir_state.mSet = SET_DAYLIGHT;
                for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                    gLedRunPara.mTargetBright[i] = gLedPara.mDayBright[i];
                }
                Led_StartNotice(NOTICE_ENTER_SET);
            }
            break;
        case KEY_NIGHTLIGHT:
            cnt++;
            if (cnt == 0x200) {
                ir_state.mKeyRpt = 0;
                ir_state.mSet = SET_NIGHTLIGHT;
                for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                    gLedRunPara.mTargetBright[i] = gLedPara.mNightBright[i];
                }
                Led_StartNotice(NOTICE_ENTER_SET);
            }
            break;
        case KEY_TIME:
            cnt++;
            if (cnt == 0x200) {
                ir_state.mKeyRpt = 0;
                ir_state.mSet = SET_TIME;
                ir_state.tmIdx = 0;
                Led_StartNotice(NOTICE_ENTER_SET);
            }
            break;
        default:
            break;
    }
}

void IR_ExitSet() {
    ir_state.mSet = SET_NONE;
    ir_state.tmIdx = 0;
    ir_state.mSetDelay = 0;
    Led_StartNotice(NOTICE_EXIT_SET);
    Led_Initialize();
}

void IR_ExitTimeout() {
    ir_state.mSet = SET_NONE;
    ir_state.tmIdx = 0;
    ir_state.mSetDelay = 0;
    Led_StartNotice(NOTICE_TIMEOUT);
    Led_Initialize();
}

void IR_KeyAction() {
    uint8_t idx;
    ir_state.mKeyRcv = 0;
    TMR2_DisableInterrupt();
    switch (keyValue) {
        case KEY_LINK_DAY:
//            Audio_StopSound();
            gLedPara.mMsc = MUSIC_DAY_INDEX;
            gLedPara.mDyn = 0;
            gLedPara.mAuto = 0;
            gLedRunPara.music_index = MUSIC_DAY_INDEX;
            gLedRunPara.mParaChanged = 1;
            Led_Initialize();
            break;
        case KEY_LINK_NIGHT:
//            Audio_StopSound();
            gLedPara.mMsc = MUSIC_NIGHT_INDEX;
            gLedPara.mDyn = 0;
            gLedPara.mAuto = 0;
            gLedRunPara.music_index = MUSIC_NIGHT_INDEX;
            gLedRunPara.mParaChanged = 1;
            Led_Initialize();
            break;
        case KEY_LINK_FISH:
//            Audio_StopSound();
            gLedPara.mMsc = MUSIC_FISH_INDEX;
            gLedPara.mDyn = 0;
            gLedPara.mAuto = 0;
            gLedRunPara.music_index = MUSIC_FISH_INDEX;
            gLedRunPara.mParaChanged = 1;
            Led_Initialize();
            break;
        case KEY_LINK_PLANT:
//            Audio_StopSound();
            gLedPara.mMsc = MUSIC_PLANT_INDEX;
            gLedPara.mDyn = 0;
            gLedPara.mAuto = 0;
            gLedRunPara.music_index = MUSIC_PLANT_INDEX;
            gLedRunPara.mParaChanged = 1;
            Led_Initialize();
            break;
        case KEY_LINK_WAVE:
        case KEY_LINK_MOON:
        case KEY_LINK_CLOUD:
        case KEY_LINK_STORM:
//            Audio_StopSound();
            gLedPara.mMsc = IR_GetIndex(keyValue);
            gLedPara.mDyn = 1;
            gLedPara.mAuto = 0;
            gLedRunPara.mParaChanged = 1;
            gLedRunPara.music_index = gLedPara.mMsc;
            Led_Initialize();
            break;
        case KEY_ONOFF:
            Audio_StopSound();
            gLedPara.mOn = !gLedPara.mOn;
            gLedPara.mAuto = 0;
            gLedRunPara.mParaChanged = 1;
            Led_Initialize();
            break;
        case KEY_AUTO:
            if(!gLedPara.mAuto)
            {
                Audio_StopSound();
                gLedPara.mOn = 1;
                gLedPara.mAuto = 1;
                gLedRunPara.mParaChanged = 1;
                Led_Initialize();
                for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                    gLedRunPara.mCurrentBright[i] = gLedRunPara.mTargetBright[i];
                }
            }
            break;
        case KEYR_UP:
        case KEYG_UP:
        case KEYB_UP:
        case KEYW_UP:
        case KEYUV_UP:
            Audio_StopSound();
            idx = IR_GetIndex(keyValue);
            Util_IncValue((uint16_t*) & gLedRunPara.mTargetBright[idx], BRIGHT_MAX, BRIGHT_STEP_SEG);
            if (ir_state.mSet == SET_NONE) {
                gLedPara.mAuto = 0;
                gLedPara.mMsc = 0;
                gLedPara.mDyn = 0;
                gLedPara.mBright[idx] = gLedRunPara.mTargetBright[idx];
                gLedRunPara.mParaChanged = 1;
            } else {
                ir_state.mSetDelay = 0;
            }
            break;
        case KEYR_DOWN:
        case KEYG_DOWN:
        case KEYB_DOWN:
        case KEYW_DOWN:
        case KEYUV_DOWN:
            Audio_StopSound();
            idx = IR_GetIndex(keyValue);
            Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[idx], BRIGHT_MIN, BRIGHT_STEP_SEG);
            if (ir_state.mSet == SET_NONE) {
                gLedPara.mAuto = 0;
                gLedPara.mMsc = 0;
                gLedPara.mDyn = 0;
                gLedPara.mBright[idx] = gLedRunPara.mTargetBright[idx];
                gLedRunPara.mParaChanged = 1;
            } else {
                ir_state.mSetDelay = 0;
            }
            break;
        case KEY_P1:
        case KEY_P2:
        case KEY_P3:
        case KEY_P4:
            Audio_StopSound();
            idx = IR_GetIndex(keyValue);
            for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                gLedRunPara.mTargetBright[i] = gLedPara.mCustom[idx][i];
            }
            if (ir_state.mSet == SET_NONE) {
                gLedPara.mAuto = 0;
                gLedPara.mMsc = 0;
                gLedPara.mDyn = 0;
                for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                    gLedPara.mBright[i] = gLedPara.mCustom[idx][i];
                }
                gLedRunPara.mParaChanged = 1;
            } else {
                ir_state.mSetDelay = 0;
            }
            break;
        case KEY_BRT_INC:
//            Audio_StopSound();
            if(gLedPara.mMsc == MUSIC_NONE_INDEX) {
                for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                    Util_IncValue((uint16_t*) & gLedRunPara.mTargetBright[i], BRIGHT_MAX, BRIGHT_STEP_SEG);
                    gLedPara.mBright[i] = gLedRunPara.mTargetBright[i];
                }
            } else {
                if(gLedPara.mMsc == MUSIC_DAY_INDEX) {
                    for(uint8_t i = 0;i < CHANNEL_CNT; i++) {
                        Util_IncValue((uint16_t*) & gLedRunPara.mTargetBright[i], BRIGHT_MAX, BRIGHT_STEP_SEG);
                        gLedPara.mStaticDayBright[i] = gLedRunPara.mTargetBright[i];
                    }
                } else if (gLedPara.mMsc == MUSIC_NIGHT_INDEX) {
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[2],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    gLedPara.mStaticNightBright[2] = gLedRunPara.mTargetBright[2];
                } else if (gLedPara.mMsc == MUSIC_FISH_INDEX) {
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[2],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[3],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[4],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    gLedPara.mStaticFishBright[2] = gLedRunPara.mTargetBright[2];
                    gLedPara.mStaticFishBright[3] = gLedRunPara.mTargetBright[3];
                    gLedPara.mStaticFishBright[4] = gLedRunPara.mTargetBright[4];
                } else if (gLedPara.mMsc == MUSIC_PLANT_INDEX) {
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[0],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[2],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[3],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    Util_IncValue((uint16_t *) & gLedRunPara.mTargetBright[4],BRIGHT_MAX,BRIGHT_STEP_SEG);
                    gLedPara.mStaticPlantBright[0] = gLedRunPara.mTargetBright[0];
                    gLedPara.mStaticPlantBright[2] = gLedRunPara.mTargetBright[2];
                    gLedPara.mStaticPlantBright[3] = gLedRunPara.mTargetBright[3];
                    gLedPara.mStaticPlantBright[4] = gLedRunPara.mTargetBright[4];
                }  
            }     
            gLedPara.mAuto = 0;
//            gLedPara.mMsc = 0;
            gLedPara.mDyn = 0;
            gLedRunPara.mParaChanged = 1;
            break;
        case KEY_BRT_DEC:
//            Audio_StopSound();
            if(gLedPara.mMsc == MUSIC_NONE_INDEX) {
                for(uint8_t i = 0;i < CHANNEL_CNT; i++) {
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[i], BRIGHT_MIN, BRIGHT_STEP_SEG);
                    gLedPara.mBright[i] = gLedRunPara.mTargetBright[i];
                }
            } else {
                if(gLedPara.mMsc == MUSIC_DAY_INDEX) {
                    for(uint8_t i = 0;i < CHANNEL_CNT; i++) {
                        Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[i], 100, BRIGHT_STEP_SEG);
                        gLedPara.mStaticDayBright[i] = gLedRunPara.mTargetBright[i];
                    }
                } else if (gLedPara.mMsc == MUSIC_NIGHT_INDEX) {
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[2], 100, BRIGHT_STEP_SEG);
                    gLedPara.mStaticNightBright[2] = gLedRunPara.mTargetBright[2];
                } else if (gLedPara.mMsc == MUSIC_FISH_INDEX) {
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[2], 100, BRIGHT_STEP_SEG);
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[3], 100, BRIGHT_STEP_SEG);
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[4], 100, BRIGHT_STEP_SEG);
                    gLedPara.mStaticFishBright[2] = gLedRunPara.mTargetBright[2];
                    gLedPara.mStaticFishBright[3] = gLedRunPara.mTargetBright[3];
                    gLedPara.mStaticFishBright[4] = gLedRunPara.mTargetBright[4];
                } else if (gLedPara.mMsc == MUSIC_PLANT_INDEX) {
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[0], 100, BRIGHT_STEP_SEG);
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[2], 100, BRIGHT_STEP_SEG);
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[3], 100, BRIGHT_STEP_SEG);
                    Util_DecValue((uint16_t*) & gLedRunPara.mTargetBright[4], 100, BRIGHT_STEP_SEG);
                    gLedPara.mStaticPlantBright[0] = gLedRunPara.mTargetBright[0];
                    gLedPara.mStaticPlantBright[2] = gLedRunPara.mTargetBright[2];
                    gLedPara.mStaticPlantBright[3] = gLedRunPara.mTargetBright[3];
                    gLedPara.mStaticPlantBright[4] = gLedRunPara.mTargetBright[4];
                } 
            }                
            gLedPara.mAuto = 0;
//            gLedPara.mMsc = 0;
            gLedPara.mDyn = 0;
            gLedRunPara.mParaChanged = 1;
            break;
        case KEY_VOL_DEC:
            Util_DecValue((uint16_t*) & gLedPara.mVolume, VOLUME_MIN, 1);
            Audio_SetVolume(VOLUME[ gLedPara.mVolume ]);
            gLedRunPara.mParaChanged = 1;
            break;
        case KEY_VOL_INC:
            Util_IncValue((uint16_t*) & gLedPara.mVolume, VOLUME_MAX, 1);
            Audio_SetVolume(VOLUME[ gLedPara.mVolume ]);
            gLedRunPara.mParaChanged = 1;
            break;
        case KEY_NUM_0:
        case KEY_NUM_1:
        case KEY_NUM_2:
        case KEY_NUM_3:
        case KEY_NUM_4:
        case KEY_NUM_5:
        case KEY_NUM_6:
        case KEY_NUM_7:
        case KEY_NUM_8:
        case KEY_NUM_9:
            if (ir_state.tmIdx < 4) {
                ir_state.time[ir_state.tmIdx++] = IR_GetIndex(keyValue);
            } else {
                ir_state.tmIdx = 0;
            }
            if (IR_IsValidTime((uint8_t*) & ir_state.time[0], ir_state.tmIdx) == false) {
                Led_StartNotice(NOTICE_ERROR);
                IR_ExitSet();
            } else if (ir_state.tmIdx == 4) {
                if (ir_state.mSet == SET_TIME) {
                    RTC_GetTime()->hour = ir_state.time[0]*10 + ir_state.time[1];
                    RTC_GetTime()->minute = ir_state.time[2]*10 + ir_state.time[3];
                    if (gLedPara.mAuto) {
                        Led_Initialize();
                    }
                } else if (ir_state.mSet == SET_SUNRISE) {
                    gLedPara.mSunrise = ir_state.time[0]*600 + ir_state.time[1]*60 + ir_state.time[2]*10 + ir_state.time[3];
                    gLedRunPara.mParaChanged = 1;
                    if (gLedPara.mAuto) {
                        Led_Initialize();
                    }
                } else if (ir_state.mSet == SET_SUNSET) {
                    gLedPara.mSunset = ir_state.time[0]*600 + ir_state.time[1]*60 + ir_state.time[2]*10 + ir_state.time[3];
                    gLedRunPara.mParaChanged = 1;
                    if (gLedPara.mAuto) {
                        Led_Initialize();
                    }
                }
                IR_ExitSet();
            }
            ir_state.mSetDelay = 0;
            break;
        case KEY_SET:
            if (ir_state.mSet == SET_DAYLIGHT) {
                for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                    gLedPara.mDayBright[i] = gLedRunPara.mTargetBright[i];
                }
                gLedRunPara.mParaChanged = 1;
                IR_ExitSet();
            } else if (ir_state.mSet == SET_NIGHTLIGHT) {
                for (uint8_t i = 0; i < CHANNEL_CNT; i++) {
                    gLedPara.mNightBright[i] = gLedRunPara.mTargetBright[i];
                }
                gLedRunPara.mParaChanged = 1;
                IR_ExitSet();
            }
            break;
        case KEY_ERROR:
            ir_state.mSet = SET_NONE;
            ir_state.tmIdx = 0;
            ir_state.mSetDelay = 0;
            Led_StartNotice(NOTICE_ERROR);
            break;
        default:
            break;
    }
    TMR2_EnableInterrupt();
    keyValue = KEY_NONE;
}

void IR_KeyAtionIfPressed() {
    if (ir_state.mKeyRcv) {
        IR_KeyAction();
    }
}

/**
 * run every second
 */
void IR_UpdateSetStatus() {
    if (ir_state.mSet) {
        ir_state.mSetDelay++;
        if (ir_state.mSetDelay > SET_DELAY_MAX) {
            IR_ExitTimeout();
        }
    }
}
