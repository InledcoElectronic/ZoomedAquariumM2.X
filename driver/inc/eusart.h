/* 
 * File:   eusart.h
 * Author: liruya
 *
 */

#ifndef EUSART_H
#define	EUSART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
    
    //TX1STA
#define TX1STA_CSRC_BRG     0x80
#define TX1STA_CSRC_EXT     0x00
#define TX1STA_TX9          0x40
#define TX1STA_TXEN         0x20
#define TX1STA_SYNC         0x10
#define TX1STA_SENDB        0x08
#define TX1STA_BRGH         0x04
#define TX1STA_TX9D         0x01
    
    //RC1STA
#define RC1STA_SPEN         0x80
#define RC1STA_RX9          0x40
#define RC1STA_SREN         0x20
#define RC1STA_CREN         0x10
#define RC1STA_ADDEN        0x08
    
    //BAUD1CON
#define BAUD1CON_SCKP_IDLE_LOW      0x10
#define BAUD1CON_SCKP_IDLE_HIGH     0x00
#define BAUD1CON_BRG16              0x08
#define BAUD1CON_WUE                0x02
#define BAUD1CON_ABDEN              0x01
    
#define BAUDRATE_16M_9600   0x01A0
    
    typedef void ( *EUSART_ReceiveInterruptHandler_t ) ( uint8_t rcv );
    
extern void EUSART_Initialize_Default();
extern uint8_t EUSART_Write( uint8_t byte );
extern void EUSART_Receive_ISR();
extern void EUSART_Transmit_ISR();

#ifdef	__cplusplus
}
#endif

#endif	/* EUSART_H */

