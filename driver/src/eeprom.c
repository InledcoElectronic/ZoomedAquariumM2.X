#include "../inc/eeprom.h"

void DATAEE_WriteByte ( uint16_t addr, uint8_t byte )
{
	uint8_t GIEBitValue = INTCONbits.GIE;

	NVMADRH = addr >> 8;
	NVMADRL = addr & 0xFF;
	NVMDATL = byte;
	NVMCON1bits.NVMREGS = 1;
	NVMCON1bits.WREN = 1;
	INTCONbits.GIE = 0; // Disable interrupts
	NVMCON2 = 0x55;
	NVMCON2 = 0xAA;
	NVMCON1bits.WR = 1;
	// Wait for write to complete
	while ( NVMCON1bits.WR );

	NVMCON1bits.WREN = 0;
	INTCONbits.GIE = GIEBitValue; // restore interrupt enable
}

uint8_t DATAEE_ReadByte ( uint16_t addr )
{
	NVMADRH = addr >> 8;
	NVMADRL = addr & 0xFF;
	NVMCON1bits.NVMREGS = 1;
	NVMCON1bits.RD = 1;
	NOP ( ); // NOPs may be required for latency at high frequencies
	NOP ( );

	return ( NVMDATL );
}

/**
 * write len bytes of buf to eeprom @ addr
 * @param addr
 * @param buf
 * @param len
 */
void DATAEE_WriteBuffer ( uint16_t addr, uint8_t *buf, uint8_t len )
{
	for ( uint8_t i = len; i != 0; i-- )
	{
		DATAEE_WriteByte ( addr++, *buf++ );
	}
}

/**
 * read len bytes from eeprom @ addr to buf
 * @param addr
 * @param buf
 * @param len
 */
void DATAEE_ReadBuffer ( uint16_t addr, uint8_t *buf, uint8_t len )
{
	for ( uint8_t i = len; i != 0; i-- )
	{
		*buf++ = DATAEE_ReadByte ( addr++ );
	}
}
