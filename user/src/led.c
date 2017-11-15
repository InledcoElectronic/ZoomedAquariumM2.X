#include "../inc/led.h"
#include "../inc/rtc.h"
#include "../inc/audio.h"

static Led_LoadDutyValue_t loadDuty[CHANNEL_CNT] = { PWM5_LoadDutyValue,
	PWM3_LoadDutyValue,
	PWM4_LoadDutyValue,
	PWM2_LoadDutyValue,
	PWM1_LoadDutyValue };
volatile LedPara_t gLedPara;
volatile LedRunPara_t gLedRunPara;

void Led_InitPara ( )
{
	DATAEE_ReadBuffer ( LEDPARA_EEPROM_ADDR, ( uint8_t * ) & gLedPara, sizeof ( gLedPara ) );
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		if ( gLedPara.mBright[i] > BRIGHT_MAX )
		{
			gLedPara.mBright[i] = BRIGHT_MAX;
		}
		if ( gLedPara.mDayBright[i] > BRIGHT_MAX )
		{
			gLedPara.mDayBright[i] = BRIGHT_MAX;
		}
		if ( gLedPara.mNightBright[i] > BRIGHT_MAX )
		{
			gLedPara.mNightBright[i] = BRIGHT_MAX;
		}
		for ( uint8_t j = 0; j < CUSTOM_CNT; j++ )
		{
			if ( gLedPara.mCustom[j][i] > BRIGHT_MAX )
			{
				gLedPara.mCustom[j][i] = BRIGHT_MAX;
			}
		}
		if ( gLedPara.mMsc > MUSIC_STORM_INDEX )
		{
			gLedPara.mMsc = MUSIC_NONE_INDEX;
		}
		if ( gLedPara.mSunrise > 1439 )
		{
			gLedPara.mSunrise = 0;
		}
		if ( gLedPara.mSunset > 1439 )
		{
			gLedPara.mSunset = 0;
		}
		if ( gLedPara.mVolume > VOLUME_MAX )
		{
			gLedPara.mVolume = VOLUME_MAX;
		}
		if ( gLedPara.mVolume < VOLUME_MIN )
		{
			gLedPara.mVolume = VOLUME_MIN;
		}
	}
}

void Led_Initialize ( )
{
	Time_t ct;
	unsigned char i;
	signed char result;
	if ( !gLedPara.mAuto )
	{
		if ( !gLedPara.mOn )
		{
			Led_TurnOffRamp ( );
		}
		else
		{
			if ( gLedPara.mMsc )
			{
				initDynamicMusic ( gLedPara.fMsc );
			}
			else
			{
				Led_TurnOnRamp ( );
			}
		}
	}
	else
	{
		Led_CheckAutoStatus ( );
	}
}

void Led_SaveParaIfChanged ( )
{
	if ( gLedRunPara.mParaChanged )
	{
		gLedRunPara.mParaChanged = 0;
		DATAEE_WriteBuffer ( LEDPARA_EEPROM_ADDR, ( uint8_t * ) & gLedPara, sizeof ( gLedPara ) );
	}
}

void Led_UpdateBright ( )
{
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		loadDuty[i]( gLedRunPara.mCurrentBright[i] );
	}
}

void Led_TurnOnDirect ( )
{
	gLedPara.mOn = 1;
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		gLedRunPara.mTargetBright[i] = gLedPara.mBright[i];
		gLedRunPara.mCurrentBright[i] = gLedPara.mBright[i];
	}
}

void Led_TurnOffDirect ( )
{
	gLedPara.mOn = 0;
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		gLedRunPara.mTargetBright[i] = 0;
		gLedRunPara.mCurrentBright[i] = 0;
	}
}

void Led_TurnOnRamp ( )
{
	gLedPara.mOn = 1;
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		gLedRunPara.mTargetBright[i] = gLedPara.mBright[i];
	}
}

void Led_TurnOffRamp ( )
{
	gLedPara.mOn = 0;
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		gLedRunPara.mTargetBright[i] = 0;
	}
}

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

void Led_SetCustom ( uint8_t idx, uint16_t *pValue )
{
	uint16_t value;
	if ( idx >= CUSTOM_CNT )
	{
		return;
	}
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		value = *pValue++;
		if ( value <= BRIGHT_MAX && value >= BRIGHT_MIN )
		{
			gLedPara.mCustom[idx][i] = value;
		}
	}
}

void Led_Ramp ( )
{
	for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
	{
		if ( gLedRunPara.mCurrentBright[i] + BRIGHT_STEP_RAMP < gLedRunPara.mTargetBright[i] )
		{
			gLedRunPara.mCurrentBright[i] += BRIGHT_STEP_RAMP;
		}
		else if ( gLedRunPara.mCurrentBright[i] > gLedRunPara.mTargetBright[i] + BRIGHT_STEP_RAMP )
		{
			gLedRunPara.mCurrentBright[i] -= BRIGHT_STEP_RAMP;
		}
		else
		{
			gLedRunPara.mCurrentBright[i] = gLedRunPara.mTargetBright[i];
		}
	}
}

/**
 * CHeck auto status, run every minute
 */
void Led_CheckAutoStatus ( )
{
	uint16_t ct = RTC_GetTime ( )->hour * 60 + RTC_GetTime ( )->minute;
	uint16_t sunrise = gLedPara.mSunrise;
	uint16_t sunset = gLedPara.mSunset;
	bool result = false;
	if ( sunrise < sunset )
	{
		if ( ct >= sunrise && ct < sunset )
		{
			result = true;
		}
	}
	else if ( sunrise > sunset )
	{
		if ( ct >= sunrise || ct < sunset )
		{
			result = true;
		}
	}
	if ( result )
	{
		for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
		{
			gLedRunPara.mTargetBright[i] = gLedPara.mDayBright[i];
		}
	}
	else
	{
		for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
		{
			gLedRunPara.mTargetBright[i] = gLedPara.mNightBright[i];
		}
	}
}

/**
 * Auto mode,run every second
 */
void Led_AutoRun ( )
{
	static uint8_t state = 0;
	uint8_t step[CHANNEL_CNT] = { 4, 1, 1, 1, 1 };
	state++;
	if ( state >= 2 )
	{
		state = 0;
		for ( uint8_t i = 0; i < CHANNEL_CNT; i++ )
		{
			if ( gLedRunPara.mCurrentBright[i] + step[i] < gLedRunPara.mTargetBright[i] )
			{
				gLedRunPara.mCurrentBright[i] += step[i];
			}
			else if ( gLedRunPara.mCurrentBright[i] > gLedRunPara.mTargetBright[i] + step[i] )
			{
				gLedRunPara.mCurrentBright[i] -= step[i];
			}
			else
			{
				gLedRunPara.mCurrentBright[i] = gLedRunPara.mTargetBright[i];
			}
		}
		Led_UpdateBright ( );
	}
}

void Led_StartNotice ( uint8_t cnt )
{
	gLedRunPara.mNoticeCount = cnt;
}

void Led_Notice ( )
{
	if ( gLedRunPara.mNoticeCount )
	{
		if ( gLedRunPara.mNoticeStatus )
		{
			Led_TurnOnDirect ( );
			gLedRunPara.mNoticeCount--;
		}
		else
		{
			Led_TurnOffDirect ( );
		}
		gLedRunPara.mNoticeStatus = !gLedRunPara.mNoticeStatus;
	}
}

void Led_InitMusic ( uint8_t index )
{
	if ( index > MUSIC_NONE_INDEX && index <= MUSIC_STORM_INDEX )
	{
		gLedRunPara.music_index = index;
		gLedRunPara.music_state = 1;
	}
}
