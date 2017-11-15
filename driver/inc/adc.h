#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#define ADCON0_CHS_ANA0         0x00
#define ADCON0_CHS_ANA1         0x04
#define ADCON0_CHS_ANA2         0x08
#define ADCON0_CHS_ANA4         0x10
#define ADCON0_CHS_ANA5         0x14
#define ADCON0_CHS_ANB4         0x30
#define ADCON0_CHS_ANB5         0x34
#define ADCON0_CHS_ANB6         0x38
#define ADCON0_CHS_ANB7         0x3C
#define ADCON0_CHS_ANC0         0x40
#define ADCON0_CHS_ANC1         0x44
#define ADCON0_CHS_ANC2         0x48
#define ADCON0_CHS_ANC3         0x4C
#define ADCON0_CHS_ANC4         0x50
#define ADCON0_CHS_ANC5         0x54
#define ADCON0_CHS_ANC6         0x58
#define ADCON0_CHS_ANC7         0x5C
#define ADCON0_CHS_VSS          0xF0
#define ADCON0_CHS_TEMP         0xF4  
#define ADCON0_CHS_DAC          0xF8
#define ADCON0_CHS_FVR          0xFC
#define ADCON0_ADGO             0x02
#define ADCON0_ADON             0x01

#define ADCON1_ADFM_RIGHT       0x80
#define ADCON1_ADFM_LEFT        0x00
#define ADCON1_ADCS_ADCRC       0x70  
#define ADCON1_ADCS_FOSC_64     0x60  
#define ADCON1_ADCS_FOSC_16     0x50
#define ADCON1_ADCS_FOSC_4      0x40
#define ADCON1_ADCS_FOSC_32     0x20
#define ADCON1_ADCS_FOSC_8      0x10
#define ADCON1_ADCS_FOSC_2      0x00
#define ADCON1_ADNREF_VSS       0x00
#define ADCON1_ADNREF_VREF      0x04
#define ADCON1_ADPREF_FVR       0x03
#define ADCON1_ADPREF_VREF      0x02
#define ADCON1_ADPREF_VDD       0x00

#define ADACT_TMR5_OVF          0x11      
#define ADACT_TMR3_OVF          0x10      
#define ADACT_CCP4              0x0F      
#define ADACT_CCP3              0x0E      
#define ADACT_CCP2              0x0D      
#define ADACT_CCP1              0x0C      
#define ADACT_CLC4              0x0B      
#define ADACT_CLC3              0x0A      
#define ADACT_CLC2              0x09      
#define ADACT_CLC1              0x08      
#define ADACT_CMP2              0x07      
#define ADACT_CMP1              0x06      
#define ADACT_TMR2_MATCH        0x05      
#define ADACT_TMR1_OVF          0x04      
#define ADACT_TMR0_OVF          0x03      
#define ADACT_TMR6_MATCH        0x02      
#define ADACT_TMR4_MATCH        0x01      
#define ADACT_NONE              0x00

#define ADCHS_ANA0         0x00
#define ADCHS_ANA1         0x01
#define ADCHS_ANA2         0x02
#define ADCHS_ANA4         0x04
#define ADCHS_ANA5         0x05
#define ADCHS_ANB4         0x0C
#define ADCHS_ANB5         0x0D
#define ADCHS_ANB6         0x0E
#define ADCHS_ANB7         0x0F
#define ADCHS_ANC0         0x10
#define ADCHS_ANC1         0x11
#define ADCHS_ANC2         0x12
#define ADCHS_ANC3         0x13
#define ADCHS_ANC4         0x14
#define ADCHS_ANC5         0x15
#define ADCHS_ANC6         0x16
#define ADCHS_ANC7         0x17
#define ADCHS_VSS          0x3C
#define ADCHS_TEMP         0x3D  
#define ADCHS_DAC          0x3E
#define ADCHS_FVR          0x3F

extern void ADC_Initialize_Default ();
extern uint16_t ADC_Conversion ( uint8_t chn );

#endif