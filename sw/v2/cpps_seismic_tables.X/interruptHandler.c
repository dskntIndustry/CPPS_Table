#include "config.h"
#include "system.h"
#include "usart.h"
#include "interruptHandler.h"
#include "i2c.h"

long addr = 0;

void interrupt ISRHandler(void)
{
    if(RC1IF)
    {
        char c = USART_getChar(SERIAL);
//        USART_putChar(c, SERIAL);
//        if(c == '\r' || c == '\n')
//        {
//            USART_putLine("", SERIAL);
//            currentLine[index] = '\r';
//            index++;
//            currentLine[index] = '\r';
//        }
        currentLine[index] = c;
        index++;
        addr++;
        for(unsigned int i = 0; i < 0x1000; i++)
        {
            I2C_putByteAtAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, 0, i, currentLine[i]);
            __delay_ms(5);
        }
    }

//        char c = USART_getChar(SERIAL);
//        USART_putCharLine(c, SERIAL);
        
//        if(c != '\r')
//        {
//            currentLine[index] = c;
//            index++;
//        }
//        if(c == '\r')
//        {
//            index = 0;
//            USART_putLine(currentLine, SERIAL);
//        }
    
//    else if(RC2IF)
//    {
//        RC2IF = 0;
//        USART_putLine("Receive interrupt", SERIAL);
//    }
}