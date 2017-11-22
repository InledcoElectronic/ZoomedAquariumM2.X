#include "../inc/audio.h"

volatile uint16_t audio_value;

void Audio_PlaySound ( )
{
	uint8_t checksum = 0x00;
	EUSART_Write ( FRAME_HEADER );
	checksum ^= EUSART_Write ( 0x03 );
	checksum ^= EUSART_Write ( CMD_PLAY );
	EUSART_Write ( checksum );
	EUSART_Write ( FRAME_END );
}

void Audio_StopSound ( )
{
	uint8_t checksum = 0x00;
	EUSART_Write ( FRAME_HEADER );
	checksum ^= EUSART_Write ( 0x03 );
	checksum ^= EUSART_Write ( CMD_STOP );
	EUSART_Write ( checksum );
	EUSART_Write ( FRAME_END );
}

void Audio_SelectSound ( uint8_t index )
{
	uint8_t checksum = 0x00;
	EUSART_Write ( FRAME_HEADER );
	checksum ^= EUSART_Write ( 0x05 );
	checksum ^= EUSART_Write ( CMD_SOUND );
	checksum ^= EUSART_Write ( 0x00 );
	checksum ^= EUSART_Write ( index );
	EUSART_Write ( checksum );
	EUSART_Write ( FRAME_END );
}

void Audio_SetPlayMode ( uint8_t type )
{
	uint8_t checksum = 0x00;
	EUSART_Write ( FRAME_HEADER );
	checksum ^= EUSART_Write ( 0x04 );
	checksum ^= EUSART_Write ( CMD_MODE );
	checksum ^= EUSART_Write ( type );
	EUSART_Write ( checksum );
	EUSART_Write ( FRAME_END );
}

void Audio_SetVolume ( uint8_t vol )
{
	uint8_t checksum = 0x00;
	EUSART_Write ( FRAME_HEADER );
	checksum ^= EUSART_Write ( 0x04 );
	checksum ^= EUSART_Write ( CMD_VOLUME_SET );
	checksum ^= EUSART_Write ( vol );
	EUSART_Write ( checksum );
	EUSART_Write ( FRAME_END );
}

void Audio_GetValue ( )
{
	static uint16_t max = 0;
	static uint16_t min = 0;
	static uint16_t cnt = 0;
	uint16_t value;

	value = ADC_Conversion ( ADCHS_AUDIO );
	if ( cnt == 0 )
	{
		max = value;
		min = value;
	}
	else
	{
		if ( max < value )
		{
			max = value;
		}
		if ( min > value )
		{
			min = value;
		}
	}
	cnt++;
	if ( cnt >= 256 )
	{
		cnt = 0;
		GlobleInterruptDisable();
		audio_value = ( audio_value * 15 + max - min ) >> 4;
		GlobleInterruptEnable();
	}
}
