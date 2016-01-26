/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "system.h"
#include "config.h"
#include "utils.h"

void HW_init(void)
{
    // Main oscillator
    OSC_init();
    // Init IO
    GPIO_init();
    //Init ADC Channel 0 potentiometer
    ADC_init(USER_ANALOG_INPUT);
    //Channel 1, 115200 bauds
    USART_init(SERIAL, 115200);
    IRQ_init();
    I2C_init(1);
}

void OSC_init(void)
{
    //PLL On (4x)
    //Fosc = 64MHz
    //Fosc/4 = 16MHz
    //Internal Oscillator Block enabled
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    PLLEN = 1;
}

void VREF_init(void)
{
    //ADC Vref = 4.096V
    VREFCON0bits.FVRS0 = 1;
    VREFCON0bits.FVRS1 = 1;
    VREFCON0bits.FVREN = 1;
}

void GPIO_init(void)
{
    //Digital
    //Inputs
    TRISCbits.RC5 = 1;

    //Outputs
    //PWM output
    TRISEbits.RE2 = 0;
    //CCP4 output
    TRISBbits.RB0 = 0;

    //Analog
    //Inputs

    //A5 -> Channel AN0
    TRISAbits.RA0 = 1;
    //A4 -> Channel AN1
    TRISAbits.RA1 = 1;
    //A3 -> Channel AN2
    TRISAbits.RA2 = 1;
    //A2 -> Channel AN3
    TRISAbits.RA3 = 1;
    //A1 -> Channel AN4
    TRISAbits.RA5 = 1;
    //A0 -> Channel AN5
    TRISEbits.RE0 = 1;

    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;
    ANSELAbits.ANSA2 = 1;
    ANSELAbits.ANSA3 = 1;
    ANSELAbits.ANSA5 = 1;
    ANSELEbits.ANSE0 = 1;

    
    //I2C
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
    //Achtuuuuuuuuuuuunnnnnnnnnnnnnng!
    ANSELC = 0x00;
}

void IRQ_init(void)
{
    GIE = 1;
    PEIE = 1;
    IPEN = 1;

    RC1IE = 1;
    
}

void TMR_init(unsigned int channel)
{
    switch(channel)
    {
        case 0:
            //T0CONbits.TMR0ON = 1;
            break;
        case 1:
            //T1CONbits.TMR1ON = 1;
            break;
        case 2:
            //On Fosc/4 = 8MHz
            //prescaler 1:4 (2MHz)
            T2CONbits.T2CKPS0 = 1;
            T2CONbits.T2CKPS1 = 0;

            //postscaler 1:10
            T2CONbits.T2OUTPS0 = 1;
            T2CONbits.T2OUTPS1 = 0;
            T2CONbits.T2OUTPS2 = 0;
            T2CONbits.T2OUTPS3 = 1;

            // 1kHz interrupts
            // PR2 = 50;
            PR2 = 200;
            PIE1bits.TMR2IE = 1;
            T2CONbits.TMR2ON = 1;
            break;
        case 4:

//            //On Fosc/4 = 8MHz
//            //prescaler 1:4 (2MHz)
//            T2CONbits.T2CKPS0 = 1;
//            T2CONbits.T2CKPS1 = 0;
//
//            //postscaler 1:10
//            T2CONbits.T2OUTPS0 = 1;
//            T2CONbits.T2OUTPS1 = 0;
//            T2CONbits.T2OUTPS2 = 0;
//            T2CONbits.T2OUTPS3 = 1;
//
//            // 1kHz interrupts
//            // PR2 = 50;
//            PR2 = 200;
//            PIE1bits.TMR2IE = 1;
//            T2CONbits.TMR2ON = 1;
            break;
        default:
            break;
    }
}

void ADC_init(unsigned int channel)
{
    ADCON0 = (unsigned char)(channel<<2);
    //A/D VREF+ -> AVdd
    //A/D VREF- -> AVss
    ADCON1 = 0x00;
    //Right justified
    //4 TAD
    ADCON2bits.ADFM = 1;
    ADCON2bits.ACQT0 = 0;
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT2 = 0;

    // 1MHz
    ADCON2bits.ADCS0 = 1;
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS2 = 1;

    //PIE1bits.ADIE = 1;
}

void USART_init(unsigned int channel, unsigned int baudrate)
{
    unsigned int baudConfig=0;
    RCIE = 1;
    switch(baudrate)
    {
        case 9600:
            baudConfig = 103;
            break;
        case 19200:
            baudConfig = 51;
            break;
        case 57600:
            baudConfig = 16;
            break;
        case 115200:
            baudConfig = 8;
            break;
        default:
            break;
    }
   switch(channel)
   {
       case 1:
            //TX
            TRISCbits.RC6 = 1;
            //RX
            TRISCbits.RC7 = 1;
            ANSELCbits.ANSC6 = 0;
            ANSELCbits.ANSC7 = 0;


            TXSTA1bits.SYNC = 0;
            RCSTA1bits.SPEN = 1;

            PIE1bits.RC1IE = 1;
            //PIE1bits.TX1IE = 1;
            TXSTA1bits.BRGH = 0;
            BAUDCON1bits.BRG16 = 0;
            SPBRG1 = baudConfig;
            TXSTA1bits.TXEN = 1;
            RCSTA1bits.CREN = 1;
            break;
        case 2:
            //TX
            TRISBbits.RB6 = 1;
            //RX
            TRISBbits.RB7 = 1;

            //Baudrate
            RCSTA2bits.SPEN = 1;


            PIE3bits.RC2IE = 1;
            //PIE3bits.TX2IE = 1;

            TXSTA2bits.SYNC = 0;
            TXSTA2bits.BRGH = 0;

            BAUDCON2bits.BRG16 = 0;
            SPBRG2 = baudConfig;
            TXSTA2bits.TXEN = 1;
            RCSTA2bits.CREN = 1;
            break;
        default:
            break;
   }
}

void I2C_init(unsigned int channel)
{

    switch(channel)
    {
        case 1:
            TRISCbits.RC3 = 1;
            TRISCbits.RC4 = 1;
            SSP1STAT = 0xC0;
            SSP1CON1 = 0x28;
            // FOSC / (4 * (SSPxADD+1))
            //400kHz @ 64MHz
            SSP1ADD = 9;
            //1000MHz
            //SSP1ADD = 3;
            break;
        case 2:
            TRISBbits.RB1 = 1;
            TRISBbits.RB2 = 1;
            SSP2STAT |= 0x80;
            SSP2CON1 = 0x28;
            // FOSC / (4 * (SSPxADD+1))
            //100kHz @ 64MHz
            SSP2ADD = 39;
            break;
        default:
            break;
    }
}

void PWM_init(unsigned int channel, unsigned int period)
{
   switch(channel)
    {
        case 4:
/*
 * PWM registers configuration
 * Fosc = 64000000 Hz
 * Fpwm = 10000.00 Hz (Requested : 10000 Hz)
 * Duty Cycle = 20 %
 * Resolution is 10 bits
 * Prescaler is 16
 * Ensure that your PWM pin is configured as digital output
 * see more details on http://www.micro-examples.com/
 * this source code is provided 'as is',
 * use it at your own risks
 */
PR4 = 0b01100011 ;
T4CON = 0b00000111 ;
CCPR1L = 0b00010011 ;
CCP1CON = 0b00111100 ;
            break;
        case 6:
            //PR6
            break;
        default:
            break;
    }
}

void EEPROM_init(unsigned int flash)
{
    // 1 = Flash
    // 0 = eeprom
    EECON1bits.EEPGD = flash;
    // 1 = Access Configuration registers
    // 0 = Access Flash program or data EEPROM memory
    EECON1bits.CFGS = 0;
    //PIE2bits.EEIE = 1;
}

