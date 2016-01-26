#include "eeprom.h"
#include "config.h"
#include "usart.h"

char EEPROM_readByte(unsigned int addr)
{
    // 1 = Flash
    // 0 = eeprom
    EECON1bits.EEPGD = 0;
    // 1 = Access Configuration registers
    // 0 = Access Flash program or data EEPROM memory
    EECON1bits.CFGS = 0;
    EEADRH = (unsigned char)(addr&0x3);
    EEADR = (unsigned char)addr;
    EECON1bits.RD = 1;
    return EEDATA;
}

unsigned int EEPROM_readWord(unsigned int addr)
{
    return 0;
}

void EEPROM_writeByte(char b, unsigned int addr)
{
    EEADRH = (unsigned char)(addr&0x3);
    EEADR = (unsigned char)addr;
    EEDATA = (unsigned char)b;
    // 1 = Flash
    // 0 = eeprom
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    di();
    EECON1bits.WREN = 1;

    // Mandatory write/erase sequence
    EECON2 = 0x55;
    EECON2 = 0x0AA;

    EECON1bits.WR = 1;
    while(EECON1bits.WR);
    ei();
}

void EEPROM_writeWord(int w, unsigned int addr)
{
    char wl = (w&0x00FF);
    char wh = (w&0xFF00);
    if(addr < 0x3FF)
    {
        EEPROM_writeByte(wl,addr);
        EEPROM_writeByte(wh, addr+1);
    }
    else
    {
        USART_putLine("You try to access an address which doesn't exist.",SERIAL);
        USART_putLine("EEPROM write process failed.",SERIAL);
    }
}

