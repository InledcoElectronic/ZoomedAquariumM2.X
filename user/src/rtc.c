#include "../inc/rtc.h"

typedef struct
{
	unsigned mSec : 1;
	unsigned mMin : 1;
	unsigned mHour : 1;
	unsigned : 5;
}Status_t;

static Time_t rtc_time;
volatile Status_t rtc_status;

Time_t* RTC_GetTime ()
{
	return &rtc_time;
}

void RTC_OnSecond()
{
	rtc_time.second++;
	if( rtc_time.second > 59 )
	{
		rtc_time.second = 0;
		rtc_time.minute++;
		if( rtc_time.minute > 59 )
		{
			rtc_time.minute = 0;
			rtc_time.hour++;
			if( rtc_time.hour > 23 )
			{
				rtc_time.hour = 0;
			}
			rtc_status.mHour = 1;
		}
		rtc_status.mMin = 1;
	}
	rtc_status.mSec = 1;
}

bool RTC_SecondReady()
{
	if( rtc_status.mSec )
	{
		rtc_status.mSec = 0;
		return true;
	}
	return false;
}

bool RTC_MinuteReady()
{
	if( rtc_status.mMin )
	{
		rtc_status.mMin = 0;
		return true;
	}
	return false;
}

bool RTC_HourReady()
{
	if( rtc_status.mHour )
	{
		rtc_status.mHour = 0;
		return true;
	}
	return false;
}
