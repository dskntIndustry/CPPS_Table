/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif
#include "system.h"
#include "usart.h"
#include "config.h"
#include "i2c.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{

unsigned char t;
    HW_init();
    __delay_us(10000);
    
    USART_putLine("Welcome to the Seismic table SW", SERIAL);
//    I2C_writeEEPROMPage(1);
//    I2C_readEEPROMPage(1);
//    I2C_writeEEPROMPage(0);
//    I2C_readEEPROMPage(0);
    USART_putLine("--------------------", SERIAL);
//    I2C_writeEEPROMPage(1);
//    I2C_readEEPROMPage(1);

//    I2C_putByteAtAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, 1, 0, 'B');
//    USART_putCharLine(I2C_getByteFromAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, 1, 0), SERIAL_OUT);
    while(1)
    {
        //USART_putLine(USART_getLine(SERIAL), SERIAL);
        //USART_getLine(SERIAL);
        //USART_getLine(SERIAL);
        //USART_putLine("Interrupt sent", SERIAL);
        //USART_putCharLine('a', SERIAL);
        //USART_putLine("dasd", SERIAL);
        //USART_putLine(USART_getLine(SERIAL), SERIAL);
        ///USART_putLine(USART_getLine(SERIAL), SERIAL);
        //I2C_putByteAtAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, 1, 1, 'B');
        for(int i = 0; i < 1000; i++)
        {
             __delay_ms(5);
        }
//
//        //USART_putLine(currentLine, SERIAL);
//

        USART_putLine("Reading filled EEPROM", SERIAL);
        for(unsigned int i = 0; i < 0x1000; i++)
        {
            t = I2C_getByteFromAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, 0, i);
            USART_putChar(t, SERIAL);
            __delay_ms(5);
        }
        USART_putLine("Reading successful", SERIAL);
        //USART_putCharLine(I2C_getByteFromAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, 1, 1), SERIAL_OUT);
    }
}

