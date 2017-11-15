#include "../inc/util.h"

void Util_IncValue ( uint16_t *pSrc, uint16_t max, uint16_t delta )
{
	if( *pSrc + delta < max )
	{
		(*pSrc) += delta;
	}
	else
	{
		*pSrc = max;
	}
}

void Util_DecValue ( uint16_t *pSrc, uint16_t min, uint16_t delta )
{
	if( *pSrc > min + delta )
	{
		(*pSrc) -= delta;
	}
	else
	{
		*pSrc = min;
	}
}
