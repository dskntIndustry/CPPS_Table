#include "i2c.h"
#include "usart.h"
#include "config.h"
#include "system.h"



void I2C_start(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            I2C_wait(channel);
            SSP1CON2bits.SEN = 1;
            break;
        case 2:
            SSP2CON2bits.SEN2 = 1;
            while(SSP2CON2bits.SEN2);
            break;
        default:
            break;
    }
}

void I2C_restart(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            I2C_wait(channel);
            SSP1CON2bits.RSEN1 = 1;
            break;
        case 2:
            SSP2CON2bits.RSEN2 = 1;
            while(SSP2CON2bits.RSEN2);
            break;
        default:
            break;
    }
}

void I2C_stop(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            I2C_wait(channel);
            SSP1CON2bits.PEN1 = 1;
            break;
        case 2:
            SSP2CON2bits.PEN2 = 1;
            while(SSP2CON2bits.PEN2);
            break;
        default:
            break;
    }
}

void I2C_ack(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            SSP1CON2bits.ACKDT1 = 0;
            SSP1CON2bits.ACKEN1 = 1;
            //while(SSP1CON2bits.ACKEN1);
            break;
        case 2:
            SSP2CON2bits.ACKDT2 = 0;
            SSP2CON2bits.ACKEN2 = 1;
            //while(SSP2CON2bits.ACKEN2);
            break;
        default:
            break;
    }
}

void I2C_nack(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            SSP1CON2bits.ACKDT1 = 1;
            SSP1CON2bits.ACKEN1 = 1;
            //while(SSP1CON2bits.ACKEN1);
            break;
        case 2:
            SSP2CON2bits.ACKDT2 = 1;
            SSP2CON2bits.ACKEN2 = 1;
            //while(SSP2CON2bits.ACKEN2);
            break;
        default:
            break;
    }
}

void I2C_wait(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            while((SSP1CON2 & 0x1F)||(SSP1STAT & 0x04));
            break;
        case 2:
            while((SSP2CON2 & 0x1F)||(SSP2STAT & 0x04));
            break;
        default:
            break;
    }
}

void I2C_writeByte(char b, unsigned int channel)
{
    switch(channel)
    {
        case 1:
            I2C_wait(channel);
            SSP1BUF = b;
            
            break;
        case 2:
            SSP2BUF = b;
            while(SSP2STATbits.BF2);
            I2C_wait(channel);
            break;
        default:
            break;
    }
}

unsigned char I2C_readByte(unsigned int channel, unsigned char ack)
{
    unsigned char temp;
    switch(channel)
    {
        case 1:

            I2C_wait(channel);
            SSP1CON2bits.RCEN1 = 1;
            I2C_wait(channel);
            temp = SSP1BUF;
            I2C_wait(channel);

            if(ack)
            {
                I2C_ack(channel);
            }
            else
            {
                I2C_nack(channel);
            }
            //I2C_stop(channel);
            return temp;
        case 2:
            SSP2CON2bits.RCEN2 = 1;
            I2C_wait(channel);
            temp = SSP2BUF;
            I2C_wait(channel);
            return temp;
        default:
            return 99;
    }
}

void I2C_putByteAtAddress(unsigned int channel, unsigned char device_address, unsigned char page, unsigned int address, unsigned char byte)
{

    I2C_start(channel);
    device_address |= (page<<2);
    I2C_writeByte(device_address<<1, channel);
    // Alignment padding 0
    //High byte
    I2C_writeByte((address & 0xFF00)>>8, channel);
    //Low byte
    I2C_writeByte((unsigned char)(address & 0x00FF), channel);
    I2C_writeByte(byte, channel);
    I2C_stop(channel);
}

void I2C_putBytesPage(unsigned int channel, unsigned char device_address, unsigned char page, unsigned int address, unsigned char byte)
{

    I2C_start(channel);
    device_address |= (page<<2);
    I2C_writeByte(device_address<<1, channel);
    // Alignment padding 0
    //High byte
    I2C_writeByte((address & 0xFF00)>>8, channel);
    //Low byte
    I2C_writeByte((unsigned char)(address & 0x00FF), channel);
    I2C_writeByte(byte, channel);
    //I2C_stop(channel);
}

//void I2C_putWordAtAddress(unsigned int channel, unsigned char device_address, unsigned int address, unsigned int word)
//{
//    I2C_start(channel);
//    I2C_writeByte(device_address<<1, channel);
//    // Alignment padding 0
//    I2C_writeByte(address & 0xFF00, channel);
//    I2C_writeByte(address & 0x00FF, channel);
//    I2C_writeByte(word & 0xFF00, channel);
//    I2C_stop(channel);
//
//    address++;
//    I2C_start(channel);
//    I2C_writeByte(device_address<<1, channel);
//    // Alignment padding 0
//    I2C_writeByte(address & 0xFF00, channel);
//    I2C_writeByte(address & 0x00FF, channel);
//    I2C_writeByte(word & 0x00FF, channel);
//    I2C_stop(channel);
//}

void I2C_writeEEPROMPage(unsigned char b0)
{
    USART_putLine("Filling EEPROM with data...", SERIAL);
//    for(unsigned long i = (b0<<5); i < (0x0FFFF+(b0<<5)); i++, data++)
//    {
    for(unsigned long i = 0; i < 0x0FFFF; i++)
    {
       //I2C_putByteAtAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, b0, i, 97);
       I2C_putBytesPage(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, b0, i, 97);
       //__delay_us(100);
    }
    I2C_stop(EXT_EEPROM_I2C_CHANNEL);
}

void I2C_readEEPROMPage(unsigned char b0)
{
    USART_putLine("Reading data from EEPROM...", SERIAL);
//    for(unsigned long i = (b0<<5); i < (0x0FFFF+(b0<<5)); i++, data++)
//    {
//    for(unsigned long i = 0; i < 0x0FFFF; i++, data++)
//    {
        //i2cread = I2C_getByteFromAddress(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, b0, i);
        i2cread = I2C_getBytesPage(EXT_EEPROM_I2C_CHANNEL, EXT_EEPROM_I2C_ADD, b0, 0);
//        __delay_us(10000);
//        sprintf(str, "%llu : %c", i, i2cread);
        sprintf(str, "%c", i2cread);
        USART_putLine(str, SERIAL);
//    }
    I2C_stop(EXT_EEPROM_I2C_CHANNEL);
}

unsigned char I2C_getBytesPage(unsigned int channel, unsigned char device_address, unsigned char page, unsigned int address)
{
    unsigned char b;
    I2C_start(channel);
    device_address |= (page<<2);
    //Address
    I2C_writeByte(device_address<<1, channel);
    //EE data address H
    I2C_writeByte((address & 0xFF00)>>8, channel);
    I2C_writeByte((unsigned char)(address & 0x00FF), channel);


    I2C_start(channel);
    I2C_writeByte((device_address<<1)+1, channel);

    b = I2C_readByte(channel, 0);
    //I2C_stop(channel);
    I2C_ack(channel);
    return b;
}

unsigned char I2C_getByteFromAddress(unsigned int channel, unsigned char device_address, unsigned char page, unsigned int address)
{
    unsigned char b;
    I2C_start(channel);
    device_address |= (page<<2);
    //Address
    I2C_writeByte(device_address<<1, channel);
    //EE data address H
    I2C_writeByte((address & 0xFF00)>>8, channel);
    I2C_writeByte((unsigned char)(address & 0x00FF), channel);


    I2C_start(channel);
    I2C_writeByte((device_address<<1)+1, channel);

    b = I2C_readByte(channel, 0);
    I2C_stop(channel);
    return b;
}

//unsigned int I2C_getWordFromAddress(unsigned int channel, unsigned char device_address, unsigned int address)
//{
//    return 0;
//}